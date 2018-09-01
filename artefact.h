#ifndef ARTEFACT_H
#define ARTEFACT_H

#include <QFile>
#include <QObject>
#include <QSharedPointer>
#include <QUrl>

class Artefact : public QObject {
  Q_OBJECT
public:
  explicit Artefact(const QUrl &fileUrl, QObject *parent = nullptr);
  explicit Artefact(QObject *parent = nullptr);
  virtual ~Artefact();
  QUrl fileUrl() { return m_fileUrl; };

public slots:
  void renameTo(const QUrl &newUrl);

signals:
  void urlChanged(const QUrl &oldUrl, const QUrl &newUrl);

protected:
  void loadFromFile(const QUrl &fileUrl);
  void createNewFile(const QUrl &fileUrl);
  void createTempFile();
  void setFile(QFile *file);
  bool fileExists(const QUrl &fileUrl);
  QUrl m_fileUrl;
  QFile *m_file;
};

#endif // ARTEFACT_H
