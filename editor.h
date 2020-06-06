#ifndef EDITOR_H
#define EDITOR_H

#include "artefact.h"
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
  QUrl getPath();
  virtual void openArtefact(const QUrl &fileUrl);
  virtual void openArtefact();
  virtual void artefactOpened(const QUrl &fileUrl,
                              QSharedPointer<Artefact> artefact);
  virtual bool isMyArtefactType(const QUrl &fileUrl);
  void handleClickedLink(const QUrl &url);

protected:
  QUrl current_artefact_url;
  QUrl new_artefact_url;
};

#endif // EDITOR_H
