#include "editor.h"
#include "diae_application.h"
#include <QDesktopServices>

Editor::Editor(QObject *parent)
    : QObject(parent), current_artefact_url(QUrl()), new_artefact_url(QUrl()) {}

QUrl Editor::getPath() {
  QString path = current_artefact_url.toLocalFile();
  path = path.section("/", 0, -2);
  return QUrl().fromLocalFile(path);
}

void Editor::handleClickedLink(const QUrl &url) {
  QUrl full_url = url;
  if (url.isRelative()) {
    QUrl current_path = current_artefact_url.adjusted(QUrl::RemoveFilename);
    full_url = current_path.resolved(url);
  }
  if (isMyArtefactType(full_url)) {
    openArtefact(full_url);
  } else {
    QDesktopServices::openUrl(full_url);
  }
}

void Editor::openArtefact(const QUrl &fileUrl) {}

void Editor::openArtefact() {}

void Editor::artefactOpened(const QUrl &fileUrl,
                            QSharedPointer<Artefact> artefact) {}

bool Editor::isMyArtefactType(const QUrl &fileUrl) {}
