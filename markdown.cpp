#include "markdown.h"
#include "cmark-gfm-core-extensions.h"
#include "cmark-gfm.h"

QString convert_markdown_to_html(QString markdown) {
  /*
   * TODO: actually using the github extensions is a bit more work
   * see cmark/src/{blocks.c,main.c}
   * parser = cmark_parser_new(options)
   * cmark_parser_attach_syntax_extension(parser, syntax_extension)
   * S_parser_feed(parser, buffer, len, true)
   * document = cmark_parser_finish(parser)
   * cmark_parser_free(parser)
   * result = cmark_render_html(document, options, parser->syntax_extensions)
   * cmark_node_free(document)
   * return result
   */
  qInfo("converting markdown:");
  char *html;
  QByteArray to_convert = markdown.toUtf8();
  qInfo("%s", to_convert.constData());
  qInfo("to HTML:");
  html = cmark_markdown_to_html(to_convert.constData(), to_convert.size(),
                                CMARK_OPT_DEFAULT);
  QString ret = QString::fromUtf8(html);
  qInfo("%s", html);
  free(html);
  qInfo("%s", ret.toUtf8().constData());
  return ret;
}
