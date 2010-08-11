#! /usr/bin/env perl

#############################################################################
#
#                            M D E P E N D
#
# GENERAL DESCRIPTION
#   Merge dependencies generated by getdep.pl into the real makefile.
#
#   The makefile is searched for a line beginning with
#    # DO NOT EDIT BELOW THIS LINE
#   All lines below this line are removed and the dependencies are
#   placed at this point.
#
# INVOCATION
#   perl mdepend.pl target.mak TARGET
#
# Copyright (c) 1998, 1999 by QUALCOMM Incorporated.  All Rights Reserved.
#############################################################################
#
#                        EDIT HISTORY FOR FILE
#
# $PVCSPath:  L:/src/asw/MSM6050/vcs/mdepend.plv   1.0   23 Oct 2001 15:28:10   donb  $
# $Header: //depot/asic/msmshared/tools/jflash/JFLASH.03.00/mdepend.pl#1 $ $DateTime: 2007/03/02 18:20:12 $ $Author: rtilak $
#
# when       who     what, where, why
# --------   ---     --------------------------------------------------------
# 02/06/03   pg      Moved from ASWP402 server to ASWP401 server.
# 10/13/98   dlb     Initial version.
#
#############################################################################

die "Usage: perl mdepend.pl target.mak TARGET\n"
    unless $#ARGV == 1;


$makefile = $ARGV[0];
$target   = $ARGV[1];

############################################################
# Begin by copying the normal part of the makefile.
############################################################

$found_line = 0;

open (IN, "<$makefile") || die "Can't read makefile\n";
while (<IN>) {
  if (/^\# DO NOT EDIT BELOW THIS LINE/) {
    print;
    $found_line = 1;
    last;
  }
  print;
}
close (IN);

die "No '# DO NOT EDIT BELOW THIS LINE' found in makefile\n"
    unless $found_line;

############################################################
# Now merge in the dependencies.
############################################################

for $name (<$target/*.dep>) {
  open (IN, "<$name") || die "Can't read file: $name";
  print "\n";
  while (<IN>) {
    print;
  }
  close IN;
}

print "\n# End of auto generated dependencies.\n";

###########################################################################
# End of Perl script.
###########################################################################
