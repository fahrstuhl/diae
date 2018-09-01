#include "markdown.h"
#include "cmark.h"

QString convert_markdown_to_html(QString markdown) {
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
