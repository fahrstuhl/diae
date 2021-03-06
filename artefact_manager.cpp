#include "artefact_manager.h"
#include "markdown_artefact.h"
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QSharedPointer>

ArtefactManager::ArtefactManager(QObject *parent) : QObject(parent) {}

void ArtefactManager::loadArtefact(const QUrl &fileUrl) {
  qInfo() << "loading file " << fileUrl;
  if (isValidArtefactURL(fileUrl)) {
    QString extension = getExtension(fileUrl);
    if (extension == "md") {
      QSharedPointer<MarkdownArtefact> artefact =
          QSharedPointer<MarkdownArtefact>::create(fileUrl);
      artefact_dict[fileUrl] = artefact;
    } else {
      qInfo() << "invalid file extension: " << extension;
      // TODO: emit error
      return;
    }
  } else {
    qInfo() << "invalid URL: " << fileUrl;
    // TODO: emit error
    return;
  }
}

bool ArtefactManager::isValidArtefactURL(const QUrl &fileUrl) {
  if (isValidFile(fileUrl)) {
    QString extension = getExtension(fileUrl);
    return isValidArtefactType(extension);
  } else {
    return false;
  }
}

QString ArtefactManager::getExtension(const QUrl &fileUrl) {
  QFileInfo fileInfo = QFileInfo(fileUrl.path());
  QString extension = fileInfo.suffix();
  return extension;
}

bool ArtefactManager::isValidArtefactType(const QString extension) {
  // TODO: more generic artefact type handling
  return extension == "md";
}

void ArtefactManager::getArtefact(const QUrl &fileUrl) {
  if (not artefact_dict.contains(fileUrl)) {
    loadArtefact(fileUrl);
  }
  if (artefact_dict.contains(fileUrl)) {
    emit artefactLoaded(fileUrl, artefact_dict[fileUrl]);
  } else {
    // TODO: emit error
  }
}

QUrl ArtefactManager::createArtefact(const QString extension) {
  qInfo() << "creating new artefact with extension: " << extension;
  if (extension == "md") {
    QSharedPointer<MarkdownArtefact> artefact =
        QSharedPointer<MarkdownArtefact>::create();
    const QUrl fileUrl = artefact->url();
    artefact_dict[fileUrl] = artefact;
    qInfo() << "markdown artefact with url: " << fileUrl << " created.";
    return fileUrl;
  } else {
    qInfo() << "invalid file extension: " << extension;
    // TODO: emit error
    return QUrl();
  }
}

bool ArtefactManager::isValidFile(const QUrl &fileUrl) {
  if (fileUrl.isLocalFile() or fileUrl.isRelative()) {
    QFileInfo fileInfo = QFileInfo(fileUrl.path());
    QDir directory = QDir(fileInfo.canonicalPath());
    if (directory.exists()) {
      return true;
    }
  }
  return false;
}
