#ifndef MARKDOWN_ARTEFACT_H
#define MARKDOWN_ARTEFACT_H

#include "artefact.h"

class MarkdownArtefact : public Artefact {
  Q_OBJECT
public:
  explicit MarkdownArtefact(const QUrl &fileUrl, QObject *parent = nullptr);
  explicit MarkdownArtefact(QObject *parent = nullptr);
  ~MarkdownArtefact();
  Q_PROPERTY(bool isFree READ isFree NOTIFY isFreeChanged)
  Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
  bool isFree() { return m_isFree; };
  QString text() { return m_text; };

public slots:
  void setText(const QString &text);
signals:
  void isFreeChanged(const bool &isFree);
  void textChanged(const QString &text);

protected:
  void loadFromFile(const QUrl &fileUrl);
  void createNewFile(const QUrl &fileUrl);
  void createTempFile();
  void setFile(QFile *file);

private:
  void saveToFile();
  void readFromFile();
  bool m_isFree;
  QString m_text;
};

#endif // MARKDOWN_ARTEFACT_H
