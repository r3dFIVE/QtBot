/**
 *
 *
 * Original credit to https://github.com/lagner/QGumboParser
 *
 * DOMParsing code borrows _heavily_ from here!
 */

#ifndef HTMLTAG_H
#define HTMLTAG_H

#include <QObject>

#include <gumbo.h>



class HtmlTag : public QObject
{
    Q_OBJECT

public:
    enum Tag
    {
      HTML		= GUMBO_TAG_HTML,
      HEAD,
      TITLE,
      BASE,
      LINK,
      META,
      STYLE,
      SCRIPT,
      NOSCRIPT,
      TEMPLATE,
      BODY,
      ARTICLE,
      SECTION,
      NAV,
      ASIDE,
      H1,
      H2,
      H3,
      H4,
      H5,
      H6,
      HGROUP,
      HEADER,
      FOOTER,
      ADDRESS,
      P,
      HR,
      PRE,
      BLOCKQUOTE,
      OL,
      UL,
      LI,
      DL,
      DT,
      DD,
      FIGURE,
      FIGCAPTION,
      MAIN,
      DIV,
      A,
      EM,
      STRONG,
      SMALL,
      S,
      CITE,
      Q,
      DFN,
      ABBR,
      DATA,
      TIME,
      CODE,
      VAR,
      SAMP,
      KBD,
      SUB,
      SUP,
      I,
      B,
      U,
      MARK,
      RUBY,
      RT,
      RP,
      BDI,
      BDO,
      SPAN,
      BR,
      WBR,
      INS,
      DEL,
      IMAGE,
      IMG,
      IFRAME,
      EMBED,
      OBJECT,
      PARAM,
      VIDEO,
      AUDIO,
      SOURCE,
      TRACK,
      CANVAS,
      MAP,
      AREA,
      MATH,
      MI,
      MO,
      MN,
      MS,
      MTEXT,
      MGLYPH,
      MALIGNMARK,
      ANNOTATION_XML,
      SVG,
      FOREIGNOBJECT,
      DESC,
      TABLE,
      CAPTION,
      COLGROUP,
      COL,
      TBODY,
      THEAD,
      TFOOT,
      TR,
      TD,
      TH,
      FORM,
      FIELDSET,
      LEGEND,
      LABEL,
      INPUT,
      BUTTON,
      SELECT,
      DATALIST,
      OPTGROUP,
      OPTION,
      TEXTAREA,
      KEYGEN,
      OUTPUT,
      PROGRESS,
      METER,
      DETAILS,
      SUMMARY,
      MENU,
      MENUITEM,
      APPLET,
      ACRONYM,
      BGSOUND,
      DIR,
      FRAME,
      FRAMESET,
      NOFRAMES,
      ISINDEX,
      LISTING,
      XMP,
      NEXTID,
      NOEMBED,
      PLAINTEXT,
      RB,
      STRIKE,
      BASEFONT,
      BIG,
      BLINK,
      CENTER,
      FONT,
      MARQUEE,
      MULTICOL,
      NOBR,
      SPACER,
      TT,
      RTC,
      UNKNOWN,
      LAST,
    };
    Q_ENUM(Tag)
};

static_assert(int(HtmlTag::LAST) == int(GUMBO_TAG_LAST),
              "HtmlTag should be identical with GUMBO_TAG, "
              "may be you use incompatible version of gumbo-parser");

Q_DECLARE_METATYPE(HtmlTag::Tag)

#endif // HTMLTAG_H
