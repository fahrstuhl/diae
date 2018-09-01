#ifndef DIAE_APPLICATION_H
#define DIAE_APPLICATION_H
#ifndef diaeApp
#define diaeApp qobject_cast<DiaeApplication *>(QCoreApplication::instance())
#endif
#include "artefact_manager.h"
#include <QGuiApplication>

class DiaeApplication : public QGuiApplication {
  Q_OBJECT
public:
  DiaeApplication(int &argc, char **argv);
  ArtefactManager *const artefact_manager;
};

#endif // DIAE_APPLICATION_H
