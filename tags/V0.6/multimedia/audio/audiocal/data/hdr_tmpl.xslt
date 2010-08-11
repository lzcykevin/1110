<?xml version="1.0" encoding="utf-16"?>

<xsl:stylesheet version="1.0"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

  <!--ENUM Template -->
  <xsl:template match="ENUM">
    <xsl:text>&#xa;&#xa;typedef enum { &#xa;</xsl:text>
    <xsl:for-each select="*">
      <xsl:call-template name="FEATURISATION"/>
      <xsl:call-template name="ENUM_ELEMENT"/>
    </xsl:for-each>
    <xsl:text>&#xa;}</xsl:text>
    <xsl:value-of select="@name"/>
    <xsl:text>;&#xa;</xsl:text>
  </xsl:template>

  <!-- ENUM_ELEMENT Template -->
  <xsl:template name="ENUM_ELEMENT">
    <xsl:if test="name(current()) = 'ENUM_ELEMENT'">
      <xsl:text>&#x9;</xsl:text>
      <xsl:value-of select="@name"/>
      <xsl:if test="count(parent::FEATURE_IF | 
                          parent::FEATURE_ELIF | 
                          parent::FEATURE_ELSE |
                          parent::FEATURE_IF_BINARY | 
                          parent::FEATURE_ELIF_BINARY) > 0">
        <xsl:if test="position() = last()">
          <xsl:text>, &#xa;</xsl:text>
        </xsl:if>
      </xsl:if>
      <xsl:if test="position()!=last()">
        <xsl:text>, &#xa;</xsl:text>
      </xsl:if>
    </xsl:if>
  </xsl:template>

  <!-- STRUCTTYPE Template -->
  <xsl:template match="STRUCTTYPE">
    <xsl:text>&#xa;typedef struct {&#xa;</xsl:text>
    <xsl:for-each select="*">
      <xsl:call-template name="FEATURISATION"/>
      <xsl:call-template name="STRUCT_ELEMENT"/>
    </xsl:for-each>
    <xsl:text>&#xa;}</xsl:text>
    <xsl:value-of select="@name"/>
    <xsl:text>;&#xa;</xsl:text>
  </xsl:template>

  <!-- STRUCT_ELEMENT Template-->
  <xsl:template name="STRUCT_ELEMENT">
    <xsl:if test="name(current()) = 'STRUCT_ELEMENT'">
      <xsl:text>&#x9;</xsl:text>
      <xsl:value-of select="@typequalifier"/>
      <xsl:text> </xsl:text>
      <xsl:value-of select="@datatype"/>
      <xsl:text> </xsl:text>
      <xsl:if test="@vartype = string('PTR')">
        <xsl:text>*</xsl:text>
      </xsl:if>
      <xsl:if test="@vartype = string('PTR2PTR')">
        <xsl:text>**</xsl:text>
      </xsl:if>
      <xsl:value-of select="@name"/>
      <xsl:text>;&#xa;</xsl:text>
    </xsl:if>
  </xsl:template>

  <!-- FEATURE_IF Template -->
  <xsl:template match="FEATURE_IF">
    <xsl:text>#ifdef </xsl:text>
    <xsl:value-of select="@name"/>
    <xsl:text>&#xa;</xsl:text>
    <xsl:call-template name="process_types"/>
  </xsl:template>

  <!-- FEATURE_ELIF Template -->
  <xsl:template match="FEATURE_ELIF">
    <xsl:text>#elif </xsl:text>
    <xsl:value-of select="@name"/>
    <xsl:text>&#xa;</xsl:text>
    <xsl:call-template name="process_types"/>
  </xsl:template>

  <!-- FEATURE_IF_BINARY Template -->
  <xsl:template match="FEATURE_IF_BINARY">
    <xsl:variable name="OPR">
      <xsl:value-of select="BINARY_OPERATION/@opr"/>
    </xsl:variable>
    <xsl:text>#if </xsl:text>
    <xsl:for-each select="BINARY_OPERATION/OPERAND">
      <xsl:text>defined (</xsl:text>
      <xsl:value-of select="@name"/>
      <xsl:text>)</xsl:text>
      <xsl:if test="position() != last()">
        <xsl:if test="string($OPR)=string('OR')">
          <xsl:text disable-output-escaping="yes"> || </xsl:text>
        </xsl:if>
        <xsl:if test="string($OPR)=string('AND')">
          <xsl:text disable-output-escaping="yes"> &amp;&amp; </xsl:text>
        </xsl:if>
      </xsl:if>
    </xsl:for-each>
    <xsl:text>&#xa;</xsl:text>
    <xsl:call-template name="process_types"/>
  </xsl:template>

  <!-- FEATURE_ELIF_BINARY Template -->
  <xsl:template match="FEATURE_ELIF_BINARY">
    <xsl:variable name="OPR">
      <xsl:value-of select="BINARY_OPERATION/@opr"/>
    </xsl:variable>
    <xsl:text>#elif </xsl:text>
    <xsl:for-each select="BINARY_OPERATION/OPERAND">
      <xsl:text>defined (</xsl:text>
      <xsl:value-of select="@name"/>
      <xsl:text>)</xsl:text>
      <xsl:if test="position() != last()">
        <xsl:if test="string($OPR)=string('OR')">
          <xsl:text disable-output-escaping="yes"> || </xsl:text>
        </xsl:if>
        <xsl:if test="string($OPR)=string('AND')">
          <xsl:text disable-output-escaping="yes"> &amp;&amp; </xsl:text>
        </xsl:if>
      </xsl:if>
    </xsl:for-each>
    <xsl:text>&#xa;</xsl:text>
    <xsl:call-template name="process_types"/>
  </xsl:template>

  <!-- FEATURE_ELSE Template -->
  <xsl:template match="FEATURE_ELSE">
    <xsl:text>#else </xsl:text>
    <xsl:text>&#xa;</xsl:text>
    <xsl:call-template name="process_types"/>
  </xsl:template>

  <!-- Process Types Template -->
  <xsl:template name="process_types">
    <xsl:for-each select="*">
      <xsl:call-template name="FEATURISATION"/>
      <!--Process STRUCT_ELEMENT -->
      <xsl:call-template name="STRUCT_ELEMENT"/>
      <!--Process ENUM_ELEMENT -->
      <xsl:call-template name="ENUM_ELEMENT"/>
    </xsl:for-each>
    <xsl:apply-templates select="ENUM"/>
    <xsl:apply-templates select="STRUCTTYPE"/>
  </xsl:template>

  <xsl:template name="FEATURISATION">
    <xsl:if test="name(current()) = 'FEATURISATION'">
      <xsl:apply-templates select="FEATURE_IF"/>
      <xsl:apply-templates select="FEATURE_IF_BINARY"/>
      <xsl:apply-templates select="FEATURE_ELIF"/>
      <xsl:apply-templates select="FEATURE_ELIF_BINARY"/>
      <xsl:apply-templates select="FEATURE_ELSE"/>
      <xsl:text>#endif/* </xsl:text>
      <xsl:value-of select="child::*/attribute::name"/>
      <xsl:variable name="OPR">
        <xsl:value-of select="child::FEATURE_IF_BINARY/BINARY_OPERATION/@opr"/>
      </xsl:variable>
      <xsl:for-each select="child::FEATURE_IF_BINARY/BINARY_OPERATION/OPERAND">
        <xsl:text>(</xsl:text>
        <xsl:value-of select="@name"/>
        <xsl:text>)</xsl:text>
        <xsl:if test="position() != last()">
          <xsl:if test="string($OPR)=string('OR')">
            <xsl:text disable-output-escaping="yes"> || </xsl:text>
          </xsl:if>
          <xsl:if test="string($OPR)=string('AND')">
            <xsl:text disable-output-escaping="yes"> &amp;&amp; </xsl:text>
          </xsl:if>
        </xsl:if>
      </xsl:for-each>
      <xsl:text> */&#xa;</xsl:text>
    </xsl:if>
  </xsl:template>

</xsl:stylesheet> 
