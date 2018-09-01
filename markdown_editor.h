#ifndef MARKDOWN_EDITOR_H
#define MARKDOWN_EDITOR_H

#include "editor.h"
#include "markdown_artefact.h"

class MarkdownEditor : public Editor {
  Q_OBJECT
public:
  explicit MarkdownEditor(QObject *parent = nullptr);
  ~MarkdownEditor();
  Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
  QString text() { return current_artefact->text(); };

public slots:
  void openArtefact(const QUrl &fileUrl);
  void openArtefact();
  void artefactOpened(const QUrl &fileUrl, QSharedPointer<Artefact> artefact);
  void setText(const QString &text) { current_artefact->setText(text); }

signals:
  void textChanged(const QString &text);

private:
  QSharedPointer<MarkdownArtefact> current_artefact;
  QUrl current_artefact_url;
};

#endif // MARKDOWN_EDITOR_H
