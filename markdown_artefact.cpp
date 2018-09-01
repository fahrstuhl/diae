#include "markdown_artefact.h"
#include <QTemporaryFile>

MarkdownArtefact::MarkdownArtefact(const QUrl &fileUrl, QObject *parent)
    : Artefact(fileUrl, parent), m_isFree(true), m_text(QString("test")) {}

MarkdownArtefact::MarkdownArtefact(QObject *parent)
    : Artefact(parent), m_isFree(true), m_text(QString("empty")) {}

MarkdownArtefact::~MarkdownArtefact() {}

void MarkdownArtefact::loadFromFile(const QUrl &fileUrl) {
  setFile(new QFile(fileUrl.path(), this));
};
void MarkdownArtefact::createNewFile(const QUrl &fileUrl) {
  setFile(new QFile(fileUrl.path(), this));
};
void MarkdownArtefact::createTempFile() { setFile(new QTemporaryFile(this)); };
void MarkdownArtefact::setFile(QFile *file) {
  // TODO: handle many cases when changing file
  m_file = file;
}
