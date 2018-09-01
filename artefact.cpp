#include "artefact.h"
#include <QFileInfo>

Artefact::Artefact(const QUrl &fileUrl, QObject *parent)
    : QObject(parent), m_file(new QFile(this)) {
  m_fileUrl = fileUrl;
  if (fileExists(m_fileUrl)) {
    loadFromFile(m_fileUrl);
  } else {
    createNewFile(m_fileUrl);
  }
}

Artefact::Artefact(QObject *parent) : QObject(parent), m_file(new QFile(this)) {
  createTempFile();
  m_fileUrl = QUrl::fromLocalFile(m_file->fileName());
}

Artefact::~Artefact() {}

bool Artefact::fileExists(const QUrl &fileUrl) {
  return QFileInfo::exists(fileUrl.path());
}

void Artefact::loadFromFile(const QUrl &fileUrl){};
void Artefact::createNewFile(const QUrl &fileUrl){};
void Artefact::createTempFile(){};
void Artefact::setFile(QFile *file){};
void Artefact::renameTo(const QUrl &newUrl){};
