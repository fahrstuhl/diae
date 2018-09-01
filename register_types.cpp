#include "register_types.h"
#include "fileio.h"
#include "markdown_artefact.h"
#include "markdown_editor.h"
#include <QQmlApplicationEngine>

void register_types() {
  qmlRegisterType<FileIO, 1>("FileIO", 1, 0, "FileIO");
  qmlRegisterType<MarkdownArtefact, 1>("MarkdownArtefact", 1, 0,
                                       "MarkdownArtefact");
  qmlRegisterType<MarkdownEditor, 1>("MarkdownEditor", 1, 0, "MarkdownEditor");
}
