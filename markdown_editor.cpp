#include "markdown_editor.h"
#include "diae_application.h"
#include <QDebug>

MarkdownEditor::MarkdownEditor(QObject *parent)
    : Editor(parent),
      current_artefact(QSharedPointer<MarkdownArtefact>::create()) {
  openArtefact();
}

MarkdownEditor::~MarkdownEditor() {}

void MarkdownEditor::openArtefact(const QUrl &fileUrl) {
  current_artefact_url = fileUrl;
  connect(diaeApp->artefact_manager, &ArtefactManager::artefactLoaded, this,
          &MarkdownEditor::artefactOpened);
  diaeApp->artefact_manager->getArtefact(fileUrl);
}

void MarkdownEditor::artefactOpened(const QUrl &fileUrl,
                                    QSharedPointer<Artefact> artefact) {
  if (fileUrl == current_artefact_url) {
    current_artefact = qSharedPointerCast<MarkdownArtefact>(artefact);
    disconnect(diaeApp->artefact_manager, &ArtefactManager::artefactLoaded,
               this, &MarkdownEditor::artefactOpened);
    qInfo() << "artefact opened with text: " << text();
  }
}

void MarkdownEditor::openArtefact() {
  QUrl fileUrl = diaeApp->artefact_manager->createArtefact("md");
  openArtefact(fileUrl);
}
