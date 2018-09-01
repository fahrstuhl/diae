#include "diae_application.h"

DiaeApplication::DiaeApplication(int &argc, char **argv)
    : QGuiApplication(argc, argv),
      artefact_manager(new ArtefactManager(qGuiApp)) {}
