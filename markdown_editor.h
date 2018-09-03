#ifndef MARKDOWN_EDITOR_H
#define MARKDOWN_EDITOR_H

#include "editor.h"
#include "markdown_artefact.h"
#include <QtDebug>

class MarkdownEditor : public Editor {
  Q_OBJECT
public:
  explicit MarkdownEditor(QObject *parent = nullptr);
  ~MarkdownEditor();
  Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
  Q_PROPERTY(QUrl url READ url NOTIFY urlChanged)
  QString text() { return current_artefact->text(); };
  QUrl url() { return current_artefact_url; };

public slots:
  void openArtefact(const QUrl &fileUrl);
  void openArtefact();
  void artefactOpened(const QUrl &fileUrl, QSharedPointer<Artefact> artefact);
  void setText(const QString &text) { current_artefact->setText(text); }
  void artefactTextChanged() {
    qInfo() << "artefact text changed to: " << text()
            << ", emitting textChanged.";
    emit textChanged(text());
  }

signals:
  void textChanged(const QString &text);
  void urlChanged(const QUrl &url);

private:
  QSharedPointer<MarkdownArtefact> current_artefact;
  QUrl current_artefact_url;
  QUrl new_artefact_url;
};

#endif // MARKDOWN_EDITOR_H
