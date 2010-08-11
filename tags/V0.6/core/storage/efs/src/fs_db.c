/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                   File System Database Code

General Description
  Database Code

Copyright (c) 2002 -- 2009 by QUALCOMM, Incorporated.  All Rights Reserved.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*===========================================================================

                           Edit History

$Header: //source/qcom/qct/core/storage/efs/main/latest/src/fs_db.c#3 $ $DateTime: 2009/05/20 16:03:23 $ $Author: richardp $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
05/18/09    rp     Removed obsolete feature FS_FEATURE_RMTEFS_SERVER
11/03/08    rp     Introduce device abstraction.
12/28/07    yg     Updated tag names and hint names.
10/18/07    rp     Featurized QEFS2.
08/22/07    yg     Grand parent merge.
06/29/07   sch     Passed in data tag to write_wire
06/22/07   sch     Pass hint to write_wire to read cluster from flash
01/10/07   dlb     Fix gid update with >16 database nodes.
12/14/06    sh     Lint changes.
08/31/06   dlb     Fix 'gid' usage, and add in-place upgrade code.
04/13/06   dlb     Add 'const' to some pointers.
04/07/06   dlb     Add query for iterator value.
01/11/06   nrs     Fixed Copyright header
12/23/05   nrs     Fixed bad declartion of node data
12/09/05   dlb     Avoid memcpy to NULL.
10/26/05    sh     Lint cleanup.
10/18/05   nrs     Added uid hooks to db and removed erroneous gid parameter
10/11/05   nrs     Remove FS_ALLOC_SOFT and FS_ALLOC_HARD
09/21/05   nrs     Add checks for quota limit exceeded
08/25/05   nrs     Implent buffer accounting for quotas and reservations
05/26/05   sd      Compilation fixes for L4.
04/26/05   dlb     Add 2K page support.
03/07/05   nrs     Ignore irrelevant lint warnings
10/15/04   dlb     Update copyright line.
01/09/04   dlb     Fix update operation.
06/17/03   jkl     Clean up code.
05/01/03   dlb     Improved database algorithm.
02/28/03   jkl     Clean Up code.
===========================================================================*/

#include "fs_efs2_cust.h"

#ifdef FEATURE_EFS_QEFS2

#ifdef FS_UNIT_TEST
#error code not present
#endif

#include "assert.h"

#include <string.h>
#include <stdlib.h>

#include "fs_sys_types.h"
#include "fs_err.h"

#include "fs_buffer.h"
#include "fs_db.h"
#include "fs_errno.h"

#include "fs_upgrade.h"

#include "msg.h"

#ifdef FS_UNIT_TEST
#error code not present
#endif

/* There are two types of nodes in the database, leaf and interior nodes.
 * Both have different characteristics:
 *
 * Leaf nodes contain both keys and data.  Each key is associated with a
 * since piece of data, and there is no data before the first key.  Both
 * the key and the data are variable length.
 *
 * The key and value pairs are stored in the data region of the node.  Each
 * pair has a 2 byte header, which is the length (in bytes) of the key, and
 * the length (in bytes) of the value.  After this, are the immediate bytes
 * of the key and the value.  The header for the next element immediately
 * follows this.
 *
 * Interior nodes contain keys and cluster_ids.  There is one more
 * cluster_id than there are keys (there is a cluster_id before the first
 * id).
 *
 * The data region begins with an ID_SIZEd (4 bytes at the time of
 * implementation) cluster_id for the leftmost child.  This is followed by
 * pairs of key's and cluster_ids.  Since the values here are fixed size,
 * no length is stored for them.  Also, the keys in the interior nodes are
 * partial, only enough characters from the key is used to distinguish them
 * one from another.
 */

/* Active clusters.
 * The database has the potential to look at, and manipulate a large number
 * of clusters.  The active clusters structures (clust, node) keep track of
 * cluster number and wired pointers for each of these nodes.  Leaf nodes
 * are always manipulated at level zero, so this is fairly easy.  Inserts
 * can touch at most 3 clusters per level, while deletes can touch 4.
 * Only two need to stay wired, however.  So, for each level, we have a
 * pair of clusters available to hold the wire in place.  There are also
 * two aux clusters that are used during inserts and deletes (the left
 * pointer afterward needs to be modified).
 *
 * The down_find search sets pos[] to the offset in the data area of the
 * node where the appropriate index point is.  'matched' is only set on
 * leaf nodes (since it isn't important in the interior).
 */

/* Some convenient names for longer symbols. */
#define AUX1      FS_DB_AUX1

/* Operations used to modify nodes. */
#define OP_ADD          1
#define OP_REPLACE      2
#define OP_REMOVE       3

#define NODE_DATA_SIZE   (EFS_PAGE_SIZE-3*4-2-2-4)

#ifdef FS_UNIT_TEST
#error code not present
#endif

/* These are guesses about what are good points to try combining data.  The
 * check threshold is the limit above which the combine isn't even
 * considered.  Then the check threshold is the point at which a combine
 * will be done (if the combined node is less than this size). */
#define COMBINE_THRESHOLD  (NODE_DATA_SIZE*2/3)
#define COMBINE_CHECK_THRESHOLD  (NODE_DATA_SIZE/3)

/* This is the format of a given node. */
struct node_data {
  fs_cluster_id left;
  fs_cluster_id right;
  uint16        used;
  uint32        gid;
  uint8         bogus_count;
  uint8         level;
  uint8         data[NODE_DATA_SIZE];
};

#define ID_SIZE ((int) sizeof (fs_cluster_id))

/* Since the cluster ID's are misaligned in the data, use these two
 * routines to fetch and store them.  These always store little endian. */
static void
put_id (uint8 *place, fs_cluster_id id)
{
  int i;
  for (i = 0; i < ID_SIZE; i++) {
    place[i] = id & 0xFF;
    id >>= 8;
  }
}

static fs_cluster_id
get_id (uint8 *place)
{
  fs_cluster_id res = 0;
  int i;

  for (i = ID_SIZE - 1; i >= 0; i--) {
    res <<= 8;
    res |= place[i];
  }

  return res;
}

/**********************************************************************
 * Utilities for wiring and unwiring clusters.  These are short, and should
 * inline nicely.
 */

/* Wire down a specific cluster. */
static void
db_read_wire (fs_db_t db, int num)
{
  db->node[num] = db->buf->read_wire (db->buf, db->clust[num]);
}

/* Wire for writing. */
static void
db_write_wire (fs_db_t db, int num, fs_read_hint read_hint)
{
  db->node[num] = db->buf->write_wire (db->buf, db->clust[num], read_hint,
                                       FS_DATA_TAG_DB);
}

/* Free a specified wire.  Clears the pointer, but the cluster number is
 * still valid. */
static void
db_unwire (fs_db_t db, int num)
{
  if (db->node[num] != NULL) {
    db->buf->free_wire (db->buf, db->clust[num]);
    db->node[num] = NULL;
  }
}

/* Unwire all of the clusters that are still wired down. */
static void
db_unwire_all (fs_db_t db)
{
  int i;

  for (i = 0; i < FS_DB_ACTIVE_CLUSTERS; i++) {
    db_unwire (db, i);
  }
}

/**********************************************************************
 * Utilities for manipulating the left/right cluster chain at each level.
 */

/* Insert a new node into a chain.  'new_node' is inserted to the right of
 * 'left'.  'old_right' can be used to wire down the old right (it should
 * not be wired yet).  left, and new_node must both already be write wired.
 */
static void
chain_insert (fs_db_t db, int left, int new_node, int old_right)
{
  node_t l = db->node[left];
  node_t n = db->node[new_node];
  node_t r;

  /* Update the three pointers already wired. */
  n->right = l->right;
  n->left = db->clust[left];
  l->right = db->clust[new_node];

  /* If there is a right sibling, its 'left' pointer needs to be adjusted
   * to point to the new_node. */
  if (n->right != FS_INVALID_CLUSTER_ID) {
    db->clust[old_right] = n->right;
    db_write_wire (db, old_right, FS_BUF_READ_CLUSTER);
    r = db->node[old_right];
    r->left = db->clust[new_node];

    /* Unwire the right pointer, since it won't get used any more. */
    db_unwire (db, old_right);
  }
}

/* Delete a node in a chain.  Left is the left node, drop is the node to
 * drop, and right is an (unwired) node that may need to be modified to do
 * the delete.  This will change the chain from left->drop->right to
 * left->right.  Drop can be unallocated once this is finished.  Left
 * should be write wired, drop doesn't matter, and right is not wired at
 * all.  The drop node will also be unwired, and deallocated. */
static void
chain_delete (fs_db_t db, int left, int drop, int right)
{
  fs_cluster_id clust;

  node_t l = db->node[left];
  node_t d = db->node[drop];

  uint32 gid = d->gid;

  l->right = d->right;

  if (l->right != FS_INVALID_CLUSTER_ID) {
    db->clust[right] = l->right;
    db_write_wire (db, right, FS_BUF_READ_CLUSTER);

    db->node[right]->left = d->left;

    db_unwire (db, right);
  }

  clust = db->clust[drop];
  db_unwire (db, drop);
  db->buf->deallocate (db->buf, clust, gid);
}

/* Initialize a new nodes fields. Set it up according to the specified
 * level. */
static void
erase_node (node_t n, int level, uint32 gid)
{
  n->left = FS_INVALID_CLUSTER_ID;
  n->right = FS_INVALID_CLUSTER_ID;
  n->used = 0;
  /* n->count = 0; */
  n->level = level;
  n->gid = gid;

#ifdef FS_UNIT_TEST
#error code not present
#endif
}

/* Compare two keys.  Lots of room for optimization, but don't bother
 * unless we waste a lot of time in here. */
static int
compare_keys (const uint8 *left, unsigned left_length,
    const uint8 *right, unsigned right_length)
{
  unsigned pos = 0;

  while (1) {
    if (pos == left_length && pos == right_length)
      return 0;

    if (pos == left_length)
      return -1;

    if (pos == right_length)
      return 1;

    if (left[pos] < right[pos])
      return -1;

    if (left[pos] > right[pos])
      return 1;

    pos++;
  }
}

/* Scan the "active" cluster for the given key.  db->pos will be left
 * pointing to the first key that is greater than the given key.
 * db->matched will be set iff db->pos points to a key that exactly matches
 * the given key. */
static void
scan (fs_db_t db, const uint8 *key, unsigned key_length)
{
  unsigned pos = 0;
  node_t n = db->node[db->active];

  if (n->level == 0) {
    db->matched = 0;
    pos = 0;
    while (pos < n->used) {
      unsigned len = n->data[pos];
      int res = compare_keys (key, key_length, &n->data[pos+2], len);
      if (res == 0) {
        db->matched = 1;
        break;
      } else if (res < 0) {
        break;
      }

      pos += len + n->data[pos+1] + 2;
    }
  } else {
    db->matched = 0;
    pos = ID_SIZE;
    while (pos < n->used) {
      unsigned len = n->data[pos];
      int res = compare_keys (key, key_length, &n->data[pos+1], len);
      if (res == 0) {
        /* In index nodes, equal moves it to the right. */
        pos += len + 1 + ID_SIZE;
        break;
      } else if (res < 0) {
        break;
      }

      pos += len + 1 + ID_SIZE;
    }
  }

  db->pos[n->level] = pos;
}

/* Given two strings that are lexographically sorted, determine the minimal
 * prefix of string 'b' that is needed to distinguish them.  If the strings
 * are improperly lexigraphically sorted, the assertion will fail. */
static unsigned
find_unique_length (uint8 *a, unsigned alen, uint8 *b, unsigned blen)
{
  unsigned len = 0;

  while (1) {
    ASSERT (len < blen);

    if (len >= alen)
      return len + 1;

    if (a[len] != b[len])
      return len + 1;

    len++;
  }
}

static void index_expand (fs_db_t db, int level,
    uint8 *key, uint8 key_length, uint32 gid);

/* Adjust the after its children have been modified.  The 'op' should
 * either be OP_ADD to indicate a new field to be added, and OP_REMOVE to
 * indicate a field to be removed.  'pos' should point to the beginning of
 * a key in the index node (meaning we can't delete the first pointer).  If
 * OP_ADD, then the given key and new_pointer will be inserted at this
 * point.
 */
static void
index_adjust (fs_db_t db, int level, int op,
    unsigned pos, uint8 *key, unsigned key_length,
    fs_cluster_id new_ptr, uint32 gid)
{
  int base = level * FS_DB_CLUSTERS_PER_LEVEL;
  node_t node;
  node_t n2 = NULL;
  uint8 *src[5];
  int slen[5];
  uint8 *dest;
  unsigned dlen;
  int nspans;
  unsigned new_length;
  int i;
  int tmp;
  unsigned spoint = 0;
  int do_split = 0;
  uint8 *split_key = NULL;
  int do_combine = 0;
  int phase;
  int result;

  db_write_wire (db, base, FS_BUF_READ_CLUSTER);

  node = db->node[base];

  /* Place the tmp key into the buffer.  It is important to do this in such
   * a way that if it is already there, it won't be bothered. */
  if (key != NULL && key != db->tmp_key + 1) {
    db->tmp_key[0] = key_length;
    memcpy (&db->tmp_key[1], key, key_length);
  }
  put_id (&db->tmp_key[1] + key_length, new_ptr);

#ifdef FS_UNIT_TEST
#error code not present
#endif

  /* For simplicity, copy all of the data into a tmp buffer, and then copy
   * it back as needed. */
  memcpy (db->tmp_buf[0], &node->data[0], node->used);

  src[0] = &db->tmp_buf[0][0];
  slen[0] = pos;

  /* ADD */
  if (op == OP_ADD) {
    src[1] = &db->tmp_key[0];
    slen[1] = 1 + ID_SIZE + key_length;
  } else {
    ASSERT (pos < node->used);

    /* Skip the key to remove. */
    src[1] = NULL;
    slen[1] = 0;

    pos += db->tmp_buf[0][pos] + 1 + ID_SIZE;
  }

  src[2] = &db->tmp_buf[0][pos];
  slen[2] = node->used - pos;

  nspans = 3;

  new_length = 0;
  for (i = 0; i < nspans; i++) {
    new_length += slen[i];
  }

  if (new_length > NODE_DATA_SIZE) {
    /* The node must be split.  The split point will be roughly half of the
     * new length. */
    spoint = new_length / 2;
    do_split = 1;

    /* Create the new node. */
    result = db->buf->allocate (db->buf, gid,
        &db->clust[base+1]);
    if (result < 0)
    {
      db_unwire_all (db);
      if (result == -ENOSPC)
        FS_RAISE (-ENOSPC, "Space exhausted", 0, 0, 0);
      else
        FS_RAISE (-EDQUOT, "Quota limit exceeded", 0, 0, 0);
    }
    db_write_wire (db, base+1, FS_BUF_DO_NOT_READ_CLUSTER);

    n2 = db->node[base+1];
    erase_node (n2, node->level, gid);
  } else if (op != OP_ADD && new_length < COMBINE_CHECK_THRESHOLD
      && node->right != FS_INVALID_CLUSTER_ID
      && db->pos[level+1] < db->node[base + FS_DB_CLUSTERS_PER_LEVEL]->used)
  {
    node_t parent;
    /* Check for the possible need/benefit of combining with our right
     * neighbor.  To combine index nodes, we must take the key from the
     * parent index node and insert it. */

    db->clust[base+1] = node->right;
    db_read_wire (db, base+1);

    n2 = db->node[base+1];

    parent = db->node[base + FS_DB_CLUSTERS_PER_LEVEL];
    if (new_length + n2->used + parent->data[db->pos[level+1]] + 1
        < COMBINE_THRESHOLD)
    {
      do_combine = 1;
      src[3] = &parent->data[db->pos[level+1]];
      slen[3] = parent->data[db->pos[level+1]] + 1;
      src[4] = &n2->data[0];
      slen[4] = n2->used;

      nspans = 5;
    } else {
      /* Not necessary to combine. */
      db_unwire (db, base + 1);

      n2 = NULL;
    }
  }

  dest = &node->data[0];
  dlen = 0;

  phase = 0; /* Start copying an ID. */

  for (i = 0; i < nspans; i++) {
    while (slen[i] > 0) {
      if (phase == 0) {
        ASSERT (slen[i] >= ID_SIZE);
        memcpy (dest, src[i], ID_SIZE);
        dest += ID_SIZE;
        dlen += ID_SIZE;
        src[i] += ID_SIZE;
        slen[i] -= ID_SIZE;

        phase = 1;
      } else {
        /* If we are splitting, check if it is time to move to the other
         * node. */
        if (do_split == 1 && dlen > spoint) {
          do_split = 2;
          spoint = dlen;  /* Adjust the split point. */

          split_key = &src[i][0];
          node->used = dlen;
          dest = &n2->data[0];

          /* To split the index, the split key will be inserted above us.
           * Its data value becomes the leftmost pointer in the new node. */
          tmp = src[i][0] + 1;
          src[i] += tmp;
          slen[i] -= tmp;
          dlen = 0;
        } else {
          /* Otherwise, just copy over a single key. */
          tmp = 1 + src[i][0];
          memcpy (&dest[0], &src[i][0], tmp);
          src[i] += tmp;
          slen[i] -= tmp;
          dlen += tmp;
          dest += tmp;
        }

        phase = 0;
      }
    }
  }

#ifdef FS_UNIT_TEST
#error code not present
#endif

  /* Special check for removing the top node in the tree. */
  if (new_length == ID_SIZE && node->level == db->top_level
      && !do_combine)
  {
    fs_cluster_id clust;
    uint32 dealloc_gid = node->gid;

    ASSERT (!do_split);
    db->top = get_id (&node->data[0]);
    db->buf->set_field (db->buf, FS_FIELD_DB_ROOT, db->top);
    db->top_level = level - 1;

    clust = db->clust[base];
    db_unwire (db, base);
    db->buf->deallocate (db->buf, clust, dealloc_gid);

    return;
  }

  if (do_split) {
    n2->used = dlen;
    chain_insert (db, base, base+1, AUX1);
  } else {
    node->used = dlen;
  }

#ifdef FS_UNIT_TEST
#error code not present
#endif

  if (do_split) {
    /* The split must be propagated. */

    if (split_key != db->tmp_key)
      memcpy (db->tmp_key, split_key, split_key[0] + 1);

    if (level + 1 > db->top_level) {
      index_expand (db, level + 1, &db->tmp_key[1], db->tmp_key[0], gid);
    } else {
      index_adjust (db, level + 1, OP_ADD, db->pos[level + 1],
          &db->tmp_key[1], db->tmp_key[0], db->clust[base+1], gid);
    }
  }

  if (do_combine) {
    chain_delete (db, base, base + 1, AUX1);
    index_adjust (db, level + 1, OP_REMOVE, db->pos[level + 1],
        0, 0, 0, gid);
  }
}

/* Expand the current index up one level.  The tree will be re-rooted at
 * this point. */
static void
index_expand (fs_db_t db, int level, uint8 *key, uint8 key_length, uint32 gid)
{
  int base = level * FS_DB_CLUSTERS_PER_LEVEL;
  node_t n;
  int result;

  if (level >= FS_DB_MAX_DEPTH) {
    FS_ERR_FATAL ("Database tree is not deep enough", 0, 0, 0);
  }

  result = db->buf->allocate (db->buf, gid, &db->clust[base]);
  if (result < 0)
  {
    db_unwire_all (db);
    if (result == -ENOSPC)
      FS_RAISE (-ENOSPC, "Space exhausted", 0, 0, 0);
    else
      FS_RAISE (-EDQUOT, "Quota limit exceeded", 0, 0, 0);
  }
  db_write_wire (db, base, FS_BUF_DO_NOT_READ_CLUSTER);
  n = db->node[base];

  erase_node (n, level, gid);

  /* Fill it in, appropriately, with the specified key. */
  n->used = ID_SIZE + key_length + 1 + ID_SIZE;
  put_id (&n->data[0], db->clust[base - FS_DB_CLUSTERS_PER_LEVEL]);
  n->data[ID_SIZE] = key_length;
  memcpy (&n->data[ID_SIZE + 1], key, key_length);
  put_id (&n->data[ID_SIZE + key_length + 1],
      db->clust[base - FS_DB_CLUSTERS_PER_LEVEL + 1]);

  /* Re-root the database tree. */
  db->top = db->clust[base];
  db->buf->set_field (db->buf, FS_FIELD_DB_ROOT, db->top);
  db->top_level = level;

#ifdef FS_UNIT_TEST
#error code not present
#endif
}

/* Modify a leaf node, possibly splitting it, or combining it with one of
 * its neighbors.  The operation must be one of OP_ADD, to add a new
 * key/value pair at the marked position, OP_REMOVE to remove a key/value
 * pair at the position, or OP_REPLACE to replace the key value pair with a
 * different value.  For OP_REMOVE, the given key/value are not used.  For
 * OP_REPLACE, the key is not used.
 *
 * If the modification results in a split or combine of two leaf nodes,
 * index_adjust will be called to fixup the index.
 *
 * Any iterators that are live in this page will be adjusted to continue to
 * be valid.
 *
 * This will use the [node] index into the active clusters.  If an
 * additional node is needed [node+1] will be used.  AUX1 might also be
 * used.
 */
static void
leaf_modify (fs_db_t db, fs_cluster_id ind, int op, int pos,
    const uint8 *key, unsigned key_length,
    const uint8 *value, unsigned value_length,
    uint32 gid, uint32 uid)
{
  node_t node;
  node_t n2 = NULL;
  int new_length;
  uint8 *src[4];
  int    slen[4];
  int dlen;
  uint8 *dest;
  uint8 *pre_key = NULL;
  uint8 *post_key = NULL;
  int nspans;
  int i;
  int tmp;
  int spoint = 0;
  int do_split = 0;
  int do_combine = 0;
  int uni_len;
  int slide;
  int old_used;
  int result;

  /* XXX: Use this parameter to implement UID's in the future if needed */
  (void) uid;
  db_write_wire (db, ind, FS_BUF_READ_CLUSTER);

  node = db->node[ind];

  old_used = node->used;

#ifdef FS_UNIT_TEST
#error code not present
#endif

  /* For simplicity, copy all of the data into a tmp buffer, and then copy
   * it back as needed. */
  memcpy (db->tmp_buf[0], &node->data[0], node->used);

  /* Determine the spans to copy over. */
  src[0] = &db->tmp_buf[0][0];
  slen[0] = pos;

  /* If we are replacing, set the key argument appropriately to avoid
   * having to check elsewhere. */
  if (op == OP_REPLACE) {
    key = &db->tmp_buf[0][pos+2];
    key_length = db->tmp_buf[0][pos];
  }

  if (op == OP_ADD || op == OP_REPLACE) {
    db->tmp_key[0] = key_length;
    db->tmp_key[1] = value_length;
    memcpy (&db->tmp_key[2], key, key_length);
    memcpy (&db->tmp_key[2 + key_length], value, value_length);

    src[1] = &db->tmp_key[0];
    slen[1] = 2 + key_length + value_length;
  } else {
    src[1] = NULL;
    slen[1] = 0;
  }

  src[2] = &db->tmp_buf[0][pos];
  slen[2] = node->used - pos;
  if (op != OP_ADD) {
    tmp = 2 + node->data[pos] + node->data[pos+1];
    src[2] += tmp;
    slen[2] -= tmp;
  }

  /* Slide is the amount of adjustment to make to the iterators if they are
   * past pos. */
  if (op != OP_REMOVE)
    slide = 2 + key_length + value_length;
  else
    slide = 0;
  if (op != OP_ADD)
    slide -= 2 + node->data[pos] + node->data[pos+1];

  nspans = 3;

  new_length = 0;
  for (i = 0; i < nspans; i++) {
    new_length += slen[i];
  }

  if (new_length > NODE_DATA_SIZE) {
    /* The node must be split.  The split point will be roughly half of the
     * new length. */
    spoint = new_length / 2;
    do_split = 1;

    /* Create the new node. */
    result = db->buf->allocate (db->buf, gid,
        &db->clust[ind+1]);
    if (result < 0)
    {
      db_unwire_all (db);
      if (result == -ENOSPC)
        FS_RAISE (-ENOSPC, "Space exhausted", 0, 0, 0);
      else
        FS_RAISE (-EDQUOT, "Quota limit exceeded", 0, 0, 0);
    }
    db_write_wire (db, ind+1, FS_BUF_DO_NOT_READ_CLUSTER);

    n2 = db->node[ind+1];
    erase_node (n2, node->level, gid);

  } else if (op != OP_ADD && new_length < COMBINE_CHECK_THRESHOLD
      && node->right != FS_INVALID_CLUSTER_ID
      && db->pos[1] < db->node[ind + FS_DB_CLUSTERS_PER_LEVEL]->used)
  {

    if (db->pos[1] == db->node[ind + FS_DB_CLUSTERS_PER_LEVEL]->used)
      FS_ERR_FATAL ("Note, handle this", 0, 0, 0);

    /* The last check prevents us from merging two nodes if the
     * distinguishing key is not in our parent (the pos should point to the
     * distinguishing key. */

    /* If the new node is under the check threshold for combination with
     * our right neighbor.  We only check the right neighbor, because it
     * makes the propatagion up the tree much simpler. */

    db->clust[ind+1] = node->right;
    db_read_wire (db, ind+1);

    n2 = db->node[ind+1];

    if (new_length + n2->used < COMBINE_THRESHOLD) {
      do_combine = 1;

      /* The first source is the entire left node. */
      src[3] = &n2->data[0];
      slen[3] = n2->used;

      nspans = 4;
    } else {
      /* Not necessary to combine. */
      db_unwire (db, ind+1);

      n2 = NULL;
    }
  }

  /* Note, that at the cost of making this code significantly more
   * complicated, the data could be copied less.  This should only be done
   * if profiling indicates we spend noticeable time here. */

  dest = &node->data[0];
  dlen = 0;
  for (i = 0; i < nspans; i++) {
    while (slen[i] > 0) {
      /* Copy over one key/value pair. */
      tmp = 2 + src[i][0] + src[i][1];
      memcpy (&dest[0], &src[i][0], tmp);
      src[i] += tmp;
      slen[i] -= tmp;
      dlen += tmp;
      dest += tmp;

      /* If we are splitting, check if it is time to move to the other
       * node. */
      if (do_split == 1 && dlen > spoint) {
        do_split = 2;  /* Make sure we don't split again. */
        spoint = dlen;  /* Adjust the split point. */

        pre_key = dest - tmp;
        node->used = dlen;
        dest = &n2->data[0];
        dlen = 0;
        post_key = dest;
      }
    }
  }

  if (do_split) {
    n2->used = dlen;
    chain_insert (db, ind, ind+1, AUX1);
  } else {
    node->used = dlen;
  }

#ifdef FS_UNIT_TEST
#error code not present
#endif

  /* Adjust all of the iterators, as necessary. */
  if (db->iter_count > 0) {
    fs_cluster_id a;
    int tmp_pos;

    a = db->clust[ind];

    for (i = 0; i < FS_DB_ACTIVE_ITERATORS; i++) {
      if (db->iters[i].cluster == a) {
        tmp_pos = db->iters[i].pos;

        if (slide >= 0 ? tmp_pos >= pos : tmp_pos > pos) {
          db->iters[i].pos += slide;
        }

        if (do_split && db->iters[i].pos >= spoint) {
          db->iters[i].pos -= spoint;
          db->iters[i].cluster = db->clust[ind+1];
        }
      }

      if (do_combine && db->iters[i].cluster == db->clust[ind+1]) {
        db->iters[i].pos += old_used + slide;
        db->iters[i].cluster = a;
      }

      if (slide < 0 && db->iters[i].cluster == a
          && db->iters[i].pos == node->used
          && node->right != FS_INVALID_CLUSTER_ID)
      {
        db->iters[i].pos = 0;
        db->iters[i].cluster = node->right;
      }
    }
  }

  if (do_split) {
    /* The split must be propagated, figure out our distinguished key. */
    uni_len = find_unique_length (pre_key+2, pre_key[0],
        post_key+2, post_key[0]);

    if (1 > db->top_level) {
      index_expand (db, 1, post_key+2, uni_len, gid);
    } else {
      index_adjust (db, 1, OP_ADD, db->pos[1],
          post_key+2, uni_len, db->clust[ind+1], gid);
    }
  }

  if (do_combine) {
    chain_delete (db, ind, ind + 1, AUX1);
    index_adjust (db, 1, OP_REMOVE, db->pos[1], 0, 0, 0, node->gid);
  }

  /* If there was a split or a combine, adjust the index above. */
}

/* Search the tree and find the leaf node which either contains the given
 * key, or contains the insertion point where this key should be inserted.
 * When finished, db->active will be 0, and node[0] will be read wired to
 * the appropriate cluster.  db->pos will be set to the index in this
 * cluster where the key belongs, and db->matched will be set, if this key
 * matches the one pointed to by db->pos. */
static void
down_find (fs_db_t db, const uint8 *key, unsigned key_length)
{
  int level;
  int dest;
  fs_cluster_id next_cluster;

  next_cluster = db->top;

  for (level = db->top_level; level >= 0; level--) {
    dest = FS_DB_CLUSTERS_PER_LEVEL * level;
    ASSERT (dest < FS_DB_ACTIVE_CLUSTERS);

    db->active = dest;
    db->clust[dest] = next_cluster;
    db_read_wire (db, dest);

    ASSERT (level == db->node[dest]->level);

    scan (db, key, key_length);

    /* For interior nodes, get the appropriate next node. */
    if (level > 0) {
      ASSERT (db->pos[level] >= ID_SIZE);
      next_cluster = get_id (&db->node[dest]->data[db->pos[level] - ID_SIZE]);
    }
  }
}

/**********************************************************************
 * Previous versions of this code erroneously handled the 'gid' field.  In
 * order to upgrade from these versions, we set all of the 'gid' fields to
 * FS_GROUP_ZERO.  This can cause space leaks of db nodes, but it is better
 * than the assertion failures caused by the corrupt 'gid' fields.
 */

static void upgrade_one_node (fs_db_t db, unsigned *transaction_count);
static void
fs_db_upgrade_gids (fs_db_t db)
{
  fs_cluster_id clust;
  fs_cluster_id nclust;
  node_t n;
  fs_cluster_id next_level = db->top;
  unsigned transaction_count = 0;

  MSG_HIGH ("Upgrading database node gid fields", 0, 0, 0);

  while (next_level != FS_INVALID_CLUSTER_ID) {
    clust = next_level;

    db->clust[0] = clust;
    db_read_wire (db, 0);
    n = (node_t) db->node[0];

    if (n->level > 0)
      next_level = get_id (&n->data[0]);
    else
      next_level = FS_INVALID_CLUSTER_ID;

    upgrade_one_node (db, &transaction_count);
    n = (node_t) db->node[0];
    // dump_node (db, clust, n);

    while (n->right != FS_INVALID_CLUSTER_ID) {
      db_unwire (db, 0);

      nclust = n->right;
      clust = nclust;

      db->clust[0] = clust;
      db_read_wire (db, 0);
      n = (node_t) db->node[0];

      upgrade_one_node (db, &transaction_count);
      n = (node_t) db->node[0];
      // dump_node (db, clust, n);
    }
    db_unwire (db, 0);
  }

  if (transaction_count > 0) {
    db->buf->end_transaction (db->buf);
  }

  MSG_HIGH ("Done gid upgrade", 0, 0, 0);
}

/* Performs an upgrade of a single database node.  If the transaction count
 * is zero, will start a transaction.  If it is non-zero after return, a
 * transaction is open.
 * May rewire the node as a write wire, so be sure to use the updated node
 * pointer. */
static void
upgrade_one_node (fs_db_t db, unsigned *transaction_count)
{
  node_t n = (node_t) db->node[0];

  // MSG_HIGH ("Upgrade 0x%x", db->clust[0], 0, 0);
  if (n->gid != FS_GROUP_ZERO) {
    if (*transaction_count == 0) {
      db->buf->start_transaction (db->buf);
    }

    db_write_wire (db, 0, FS_BUF_READ_CLUSTER);
    n = (node_t) db->node[0];
    n->gid = FS_GROUP_ZERO;
    (*transaction_count)++;
    db_unwire (db, 0);
    db_read_wire (db, 0);

    if (*transaction_count > 16) {
      db_unwire (db, 0);
      db->buf->end_transaction (db->buf);
      *transaction_count = 0;
      db_read_wire (db, 0);
    }
  }
}

/**********************************************************************
 * Public interface
 */

void
fs_db_init (fs_db_t db, fsb_t buf)
{
  node_t n;
  int i;
  int result;

#ifdef FS_UNIT_TEST
#error code not present
#endif

  db->buf = buf;

  db->top = buf->get_field (buf, FS_FIELD_DB_ROOT);

  if (db->top == FS_INVALID_CLUSTER_ID) {
    buf->start_transaction (buf);
    result = buf->allocate (buf, 0, &db->top);

    if (result < 0)
    {
      FS_ERR_FATAL ("Not enough space to create initial DB", 0, 0, 0);
    }
    n = (node_t) buf->write_wire (buf, db->top, FS_BUF_DO_NOT_READ_CLUSTER,
                                  FS_DATA_TAG_DB);
    erase_node (n, 0, FS_GROUP_ZERO);
    buf->free_wire (buf, db->top);
    buf->set_field (buf, FS_FIELD_DB_ROOT, db->top);
    buf->end_transaction (buf);
  }

  /* Clear out all of the wired clusters. */
  for (i = 0; i < FS_DB_ACTIVE_CLUSTERS; i++) {
    db->clust[i] = FS_INVALID_CLUSTER_ID;
    db->node[i] = NULL;
  }
  db->active = 0;

  /* Setup the iterators. */
  db->iter_count = 0;
  for (i = 0; i < FS_DB_ACTIVE_ITERATORS; i++) {
    db->iters[i].db = db;
    db->iters[i].index = i;
    db->iters[i].cluster = FS_INVALID_CLUSTER_ID;
    db->iters[i].pos = 0;
  }

  /* Determine the level of the top of the tree. */
  n = (node_t) buf->read_wire (buf, db->top);
  db->top_level = n->level;
  buf->free_wire (buf, db->top);

  /* Perform a bug-fix upgrade of the database if needed. */
  if (fs_upgrade_check (FS_UPGRADE_DBGID_FIX)) {
    fs_db_upgrade_gids (db);
    fs_upgrade_finished (FS_UPGRADE_DBGID_FIX);
  }
}

int
fs_db_add (fs_db_t db, const void *key, unsigned key_length,
    const void *value, unsigned value_length, uint32 gid, uint32 uid)
{
  int result = 0;

  down_find (db, key, key_length);

  if (!db->matched) {
    leaf_modify (db, 0, OP_ADD,
        db->pos[0], key, key_length, value, value_length, gid, uid);
  } else {
    /* This key is already present. */
    result = -1;
  }

  db_unwire_all (db);

  return result;
}

/* Search for the node and replace it.  The replacement does not need to be
 * the same length as the original data. */
int
fs_db_update (fs_db_t db, const void *key, unsigned key_length,
    const void *value, unsigned value_length, uint32 gid, uint32 uid)
{
  int result = 0;

  down_find (db, key, key_length);

  if (db->matched) {
    leaf_modify (db, 0, OP_REPLACE,
        db->pos[0], 0, 0, value, value_length, gid, uid);
  } else {
    result = -1;
  }

  db_unwire_all (db);

  return result;
}

/* Delete an entry from the database. */
int
fs_db_delete (fs_db_t db, void *key, unsigned key_length)
{
  int result = 0;

  down_find (db, key, key_length);

  if (db->matched) {
    leaf_modify (db, 0, OP_REMOVE,
        db->pos[0], 0, 0, 0, 0, FS_GROUP_ZERO, FS_CURR_UID);
    /* Pass in bogus GID to be set in leaf_modify */
  } else {
    result = -1;
  }

  db_unwire_all (db);

  return result;
}

int
fs_db_lookup (fs_db_t db, const void *key, unsigned key_length,
    void *value, unsigned *value_length)
{
  int result = 0;
  unsigned vlen;
  unsigned klen;
  int pos;
  node_t n;

  down_find (db, key, key_length);
  pos = db->pos[0];

  if (db->matched) {
    n = db->node[0];

    /* Check the size of the user's buffer.  If there isn't room, just
     * error. */
    vlen = n->data[pos + 1];
    if (vlen <= *value_length) {
      klen = n->data[pos];
      memcpy (value, &n->data[pos + 2 + klen], vlen);
      *value_length = vlen;
    } else {
      /* It doesn't fit, copy over as much as there is room for, and then
       * indicate the error condition. */
      klen = n->data[pos];
      memcpy (value, &n->data[pos + 2 + klen], *value_length);
      *value_length = vlen;
      result = -ENAMETOOLONG;
    }
  } else {
    /* The key wasn't found, so this is also an error. */
    result = -ENOENT;
  }

  /* Free any used wires. */
  db_unwire_all (db);

  return result;
}

/**********************************************************************
 * Database iteration.
 *
 * The iterators themselves don't worry about the database being modified.
 * Each routine that modifies leaf nodes will check the iterators and
 * update any pointers if they have changed.
 */
fs_db_iter_t
fs_db_iter_start (fs_db_t db, void *key, unsigned key_length)
{
  int i;
  fs_db_iter_t iter;

  /* Is there an available iterator? */
  if (db->iter_count == FS_DB_ACTIVE_ITERATORS)
    return NULL;

  /* Scan for the active one. */
  for (i = 0; i < FS_DB_ACTIVE_ITERATORS; i++) {
    if (db->iters[i].cluster == FS_INVALID_CLUSTER_ID)
      break;
  }

  ASSERT (i < FS_DB_ACTIVE_ITERATORS);

  iter = &db->iters[i];
  db->iter_count++;

  /* Search for the appropriate cluster.  The iterator doesn't check for an
   * exact match, so it doesn't matter if the key was found. */
  down_find (db, key, key_length);
  iter->cluster = db->clust[0];
  iter->pos = db->pos[0];

  /* If the position is at the end of a cluster, and there are more
   * clusters to our right, advance it to the beginning of the next
   * cluster. */
  if (iter->pos == db->node[0]->used &&
      db->node[0]->right != FS_INVALID_CLUSTER_ID)
  {
    iter->pos = 0;
    iter->cluster = db->node[0]->right;
  }

  db_unwire_all (db);

  return iter;
}

void
fs_db_iter_free (fs_db_iter_t iter)
{
  if (iter->cluster == FS_INVALID_CLUSTER_ID)
    return;

  iter->db->iter_count--;
  iter->cluster = FS_INVALID_CLUSTER_ID;
  iter->pos = 0;
}

/* XXX: Should have distinct return values that indicate between there
 * being no more, and this key not fitting. */
int
fs_db_iter_get_key (fs_db_iter_t iter, void *key, unsigned *key_length)
{
  int result;
  fs_db_t db = iter->db;
  unsigned len;

  ASSERT (iter->cluster != FS_INVALID_CLUSTER_ID);

  /* Get the cluster and wire it down. */
  db->clust[0] = iter->cluster;
  db_read_wire (db, 0);

  if (iter->pos == db->node[0]->used) {
    /* EOF. */
    result = -EEOF;
  } else if (db->node[0]->data[iter->pos] > *key_length) {
    /* Key doesn't fit. */
    result = -2; /* Hmm. */
  } else {
    len = db->node[0]->data[iter->pos];

    *key_length = len;
    memcpy (key, &db->node[0]->data[iter->pos + 2], len);
    result = 0;
  }

  db_unwire (db, 0);

  return result;
}

int
fs_db_iter_get_value (fs_db_iter_t iter, void *value, unsigned *value_length)
{
  int result;
  fs_db_t db = iter->db;
  unsigned len;
  unsigned pos;

  ASSERT (iter->cluster != FS_INVALID_CLUSTER_ID);

  /* Get the cluster and wire it down. */
  db->clust[0] = iter->cluster;
  db_read_wire (db, 0);

  if (iter->pos == db->node[0]->used) {
    /* EOF. */
    result = -EEOF;
  } else if (db->node[0]->data[iter->pos + 1] > *value_length) {
    /* Key doesn't fit. */
    result = -2; /* Hmm. */
  } else {
    len = db->node[0]->data[iter->pos + 1];
    pos = iter->pos + 2 + db->node[0]->data[iter->pos];

    *value_length = len;
    memcpy (value, &db->node[0]->data[pos], len);
    result = 0;
  }

  db_unwire (db, 0);

  return result;
}

int
fs_db_iter_next (fs_db_iter_t iter)
{
  int result;

  fs_db_t db = iter->db;

  ASSERT (iter->cluster != FS_INVALID_CLUSTER_ID);

  /* Get the current cluster and wire it down. */
  db->clust[0] = iter->cluster;
  db_read_wire (db, 0);

  if (iter->pos == db->node[0]->used) {
    /* We're already at the end. */
    result = -1;
  } else {
    iter->pos += db->node[0]->data[iter->pos] +
      db->node[0]->data[iter->pos + 1] + 2;

    /* If we reach the end, go on. */
    if (iter->pos == db->node[0]->used &&
        db->node[0]->right != FS_INVALID_CLUSTER_ID)
    {
      iter->pos = 0;
      iter->cluster = db->node[0]->right;

      /* Need to skip empty nodes. */
      while (1) {
        db_unwire (db, 0);
        db->clust[0] = iter->cluster;
        db_read_wire (db, 0);

        if (db->node[0]->right == FS_INVALID_CLUSTER_ID ||
            db->node[0]->used != 0)
          break;

        iter->cluster = db->node[0]->right;
      }
    }

    result = 0;
  }

  db_unwire (db, 0);

  return result;
}

#ifdef FS_UNIT_TEST
#error code not present
#endif

#endif /* FEATURE_EFS_QEFS2 */
