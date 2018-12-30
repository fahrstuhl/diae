#ifndef EDITOR_H
#define EDITOR_H

#include <QDebug>
#include <QDir>
#include <QObject>
#include <QUrl>

class Editor : public QObject {
  Q_OBJECT
public:
  explicit Editor(QObject *parent = nullptr);
  Q_PROPERTY(QUrl url READ url NOTIFY urlChanged)
  QUrl url() { return current_artefact_url; };

signals:
  void urlChanged(const QUrl &url);

public slots:
  QUrl getPath() {
    QString path = current_artefact_url.toLocalFile();
    path = path.section("/", 0, -2);
    return QUrl().fromLocalFile(path);
  };

protected:
  QUrl current_artefact_url;
  QUrl new_artefact_url;
};

#endif // EDITOR_H
