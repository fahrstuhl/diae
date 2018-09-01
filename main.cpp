#include "diae_application.h"
#include "register_types.h"
#include <QQmlApplicationEngine>
#include <QQuickStyle>

int main(int argc, char *argv[]) {
  DiaeApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  DiaeApplication app(argc, argv);

  QQmlApplicationEngine engine;
  QQuickStyle::setStyle("Material");
  register_types();
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
