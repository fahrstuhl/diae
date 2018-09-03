#include "markdown_editor.h"
#include "diae_application.h"
#include <QDebug>

MarkdownEditor::MarkdownEditor(QObject *parent)
    : Editor(parent),
      current_artefact(QSharedPointer<MarkdownArtefact>::create()) {
  openArtefact();
}

MarkdownEditor::~MarkdownEditor() {}

void MarkdownEditor::openArtefact() {
  QUrl fileUrl = diaeApp->artefact_manager->createArtefact("md");
  openArtefact(fileUrl);
}

void MarkdownEditor::openArtefact(const QUrl &fileUrl) {
  new_artefact_url = fileUrl;
  connect(diaeApp->artefact_manager, &ArtefactManager::artefactLoaded, this,
          &MarkdownEditor::artefactOpened);
  diaeApp->artefact_manager->getArtefact(fileUrl);
}

void MarkdownEditor::artefactOpened(const QUrl &fileUrl,
                                    QSharedPointer<Artefact> artefact) {
  if (fileUrl == new_artefact_url) {
    current_artefact_url = new_artefact_url;
    disconnect(current_artefact.data(), &MarkdownArtefact::textChanged, this,
               &MarkdownEditor::artefactTextChanged);
    current_artefact = qSharedPointerCast<MarkdownArtefact>(artefact);
    disconnect(diaeApp->artefact_manager, &ArtefactManager::artefactLoaded,
               this, &MarkdownEditor::artefactOpened);
    connect(current_artefact.data(), &MarkdownArtefact::textChanged, this,
            &MarkdownEditor::artefactTextChanged);
    emit urlChanged(current_artefact_url);
    qInfo() << "artefact opened with text: " << text();
  }
}
