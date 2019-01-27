#ifndef ARTEFACT_H
#define ARTEFACT_H

#include <QFile>
#include <QObject>
#include <QSharedPointer>
#include <QUrl>

class Artefact : public QObject {
  Q_OBJECT
public:
  virtual ~Artefact();
  Q_PROPERTY(QUrl url READ url NOTIFY urlChanged)
  QUrl url() { return m_fileUrl; };

public slots:
  void renameTo(const QUrl &newUrl);

signals:
  void urlChanged(const QUrl &oldUrl, const QUrl &newUrl);

protected:
  explicit Artefact(const QUrl &fileUrl, QObject *parent = nullptr);
  explicit Artefact(QObject *parent = nullptr);
  void loadFromFile(const QUrl &fileUrl);
  void createNewFile(const QUrl &fileUrl);
  void createTempFile();
  void setFile(QFile *file);
  virtual void saveToFile() = 0;
  virtual void readFromFile() = 0;
  virtual void fromUrl(const QUrl &fileUrl);
  virtual void fromTemp();
  bool fileExists(const QUrl &fileUrl);
  QUrl m_fileUrl;
  QFile *m_file;
};

#endif // ARTEFACT_H
