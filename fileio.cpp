#include "fileio.h"
#include "markdown.h"
#include <QFile>
#include <QTextStream>
#include <QtDebug>

QString readTextFromFile(QFile &file) {
  QString text = QString();
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream t(&file);
    text = t.readAll();
    file.close();
  } else {
    qInfo() << "Could not open file to read:" << file.fileName();
  }
  return text;
}

void saveTextToFile(QString &text, QFile &file) {

  if (!file.open(QIODevice::WriteOnly | QIODevice::Text |
                 QIODevice::Truncate)) {
    qInfo() << "Could not open file to write:" << file.fileName();
  } else {

    QTextStream out(&file);
    out << text << endl;

    file.close();
  }
}

FileIO::FileIO(QObject *parent) : QObject(parent) {}

QString FileIO::read() {
  if (mSource.isEmpty()) {
    emit error("source is empty");
    return QString();
  }

  QFile file(mSource);
  QString fileContent;
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream t(&file);
    fileContent = t.readAll();
    file.close();
  } else {
    emit error("Unable to open the file");
    return QString();
  }
  qInfo("%s", mSource.toUtf8().constData());
  return convert_markdown_to_html(fileContent);
}

bool FileIO::write(const QString &data) {
  if (mSource.isEmpty())
    return false;

  QFile file(mSource);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    return false;

  QTextStream out(&file);
  out << data << endl;

  file.close();

  return true;
}
