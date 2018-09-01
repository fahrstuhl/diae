#include "artefact_manager.h"
#include "markdown_artefact.h"
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QSharedPointer>

ArtefactManager::ArtefactManager(QObject *parent) : QObject(parent) {}

void ArtefactManager::loadArtefact(const QUrl &fileUrl) {
  qInfo() << "loading file " << fileUrl;
  if (isValidFile(fileUrl)) {
    QFileInfo fileInfo = QFileInfo(fileUrl.path());
    QString extension = fileInfo.suffix();
    if (extension == "md") {
      QSharedPointer<Artefact> artefact =
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
    const QUrl fileUrl = artefact->fileUrl();
    artefact_dict[fileUrl] = artefact;
    return fileUrl;
  } else {
    qInfo() << "invalid file extension: " << extension;
    // TODO: emit error
    return QUrl();
  }
}

bool ArtefactManager::isValidFile(const QUrl &fileUrl) {
  bool isFileUrl = fileUrl.scheme() == "file://";
  if (isFileUrl or fileUrl.isRelative()) {
    QFileInfo fileInfo = QFileInfo(fileUrl.path());
    QDir directory = QDir(fileInfo.canonicalPath());
    if (directory.exists()) {
      return true;
    }
  }
  return false;
}
