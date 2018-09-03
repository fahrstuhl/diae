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
  virtual void loadFromFile(const QUrl &fileUrl);
  virtual void createNewFile(const QUrl &fileUrl);
  virtual void createTempFile();
  virtual void setFile(QFile *file);
  virtual void saveToFile();
  virtual void readFromFile();
  void fromUrl(const QUrl &fileUrl);
  void fromTemp();
  bool fileExists(const QUrl &fileUrl);
  QUrl m_fileUrl;
  QFile *m_file;
};

#endif // ARTEFACT_H
