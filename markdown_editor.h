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
  static inline const QStringList supported_extensions = {"txt", "md"};
  Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
  Q_PROPERTY(QString html READ html)
  QString text() { return current_artefact->text(); };
  QString html() { return current_artefact->html(); };

public slots:
  void openArtefact(const QUrl &fileUrl);
  void openArtefact();
  void artefactOpened(const QUrl &fileUrl, QSharedPointer<Artefact> artefact);
  bool isMyArtefactType(const QUrl &fileUrl);
  void setText(const QString &text) { current_artefact->setText(text); }
  void artefactTextChanged() {
    qInfo() << "artefact text changed to: " << text()
            << ", emitting textChanged.";
    emit textChanged(text());
  }

signals:
  void textChanged(const QString &text);

private:
  QSharedPointer<MarkdownArtefact> current_artefact;
};

#endif // MARKDOWN_EDITOR_H
