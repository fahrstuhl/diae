#include "diae_application.h"
#include <QSettings>

DiaeApplication::DiaeApplication(int &argc, char **argv)
    : QGuiApplication(argc, argv),
      artefact_manager(new ArtefactManager(qGuiApp)) {
  QSettings settings;
  settings.setValue("base/directory", "/home/fahrstuhl/diae/");
}
