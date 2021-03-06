#ifndef ARTEFACT_MANAGER_H
#define ARTEFACT_MANAGER_H

#include "artefact.h"
#include <QHash>
#include <QObject>

class ArtefactManager : public QObject {
  Q_OBJECT
public:
  explicit ArtefactManager(QObject *parent = nullptr);
  QUrl createArtefact(const QString extension);
  static bool isValidArtefactURL(const QUrl &fileUrl);
  static QString getExtension(const QUrl &fileUrl);
signals:
  void artefactLoaded(const QUrl &fileUrl, QSharedPointer<Artefact> &artefact);

public slots:
  void loadArtefact(const QUrl &fileUrl);
  void getArtefact(const QUrl &fileUrl);

private:
  QHash<QUrl, QSharedPointer<Artefact>> artefact_dict;
  static bool isValidFile(const QUrl &fileUrl);
  static bool isValidArtefactType(QString extension);
};

#endif // ARTEFACT_MANAGER_H
