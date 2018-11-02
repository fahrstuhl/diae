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

void MarkdownArtefact::loadFromFile(const QUrl &fileUrl) {
  setFile(new QFile(fileUrl.path(), this));
  readFromFile();
};
void MarkdownArtefact::createNewFile(const QUrl &fileUrl) {
  setFile(new QFile(fileUrl.path(), this));
};
void MarkdownArtefact::createTempFile() {
  QTemporaryFile *file = new QTemporaryFile(this);
  file->open(); // generates unique filename
  file->close();
  setFile(file);
};
void MarkdownArtefact::setFile(QFile *file) {
  // TODO: handle many cases when changing file
  // there won't be any changing files of a single artefact,
  // it can only be moved on a rename
  m_file = file;
}

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
