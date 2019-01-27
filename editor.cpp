#include "editor.h"

Editor::Editor(QObject *parent)
    : QObject(parent), current_artefact_url(QUrl()), new_artefact_url(QUrl()) {}
