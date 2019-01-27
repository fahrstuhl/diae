#include "artefact.h"
#include <QFileInfo>
#include <QTemporaryFile>

Artefact::Artefact(const QUrl &fileUrl, QObject *parent)
    : QObject(parent), m_fileUrl(fileUrl), m_file(new QFile(this)) {}

Artefact::Artefact(QObject *parent)
    : QObject(parent), m_file(new QFile(this)) {}

Artefact::~Artefact() {}

void Artefact::fromUrl(const QUrl &fileUrl) {
  m_fileUrl = fileUrl;
  if (fileExists(m_fileUrl)) {
    loadFromFile(m_fileUrl);
  } else {
    createNewFile(m_fileUrl);
  }
}

void Artefact::fromTemp() {
  createTempFile();
  m_fileUrl = QUrl::fromLocalFile(m_file->fileName());
}

bool Artefact::fileExists(const QUrl &fileUrl) {
  return QFileInfo::exists(fileUrl.path());
}

void Artefact::loadFromFile(const QUrl &fileUrl) {
  setFile(new QFile(fileUrl.path(), this));
  readFromFile();
};
void Artefact::createNewFile(const QUrl &fileUrl) {
  setFile(new QFile(fileUrl.path(), this));
};
void Artefact::createTempFile() {
  QTemporaryFile *file = new QTemporaryFile(this);
  file->open(); // generates unique filename
  file->close();
  setFile(file);
};
void Artefact::setFile(QFile *file) {
  // TODO: handle many cases when changing file
  // there won't be any changing files of a single artefact,
  // it can only be moved on a rename
  m_file = file;
};
void Artefact::renameTo(const QUrl &newUrl){
    // TODO: move file on rename and setFile to new file
};
void Artefact::readFromFile(){};
void Artefact::saveToFile(){};
