#include "markdown_artefact.h"
#include "fileio.h"
#include "markdown.h"
#include <QTemporaryFile>

MarkdownArtefact::MarkdownArtefact(const QUrl &fileUrl, QObject *parent)
    : Artefact(fileUrl, parent), m_isFree(true), m_text(QString("test")) {
  fromUrl(fileUrl);
}

MarkdownArtefact::MarkdownArtefact(QObject *parent)
    : Artefact(parent), m_isFree(true), m_text(QString("empty")) {
  fromTemp();
}

MarkdownArtefact::~MarkdownArtefact() {}

void MarkdownArtefact::setText(const QString &text) {
  m_text = text;
  qInfo("%s", m_text.toUtf8().constData());
  saveToFile();
  emit textChanged(m_text);
}
void MarkdownArtefact::saveToFile() { saveTextToFile(m_text, *m_file); }

void MarkdownArtefact::readFromFile() {
  QString text = readTextFromFile(*m_file);
  setText(text);
}

QString MarkdownArtefact::toHTML() { return convert_markdown_to_html(m_text); }
