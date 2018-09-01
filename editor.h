#ifndef EDITOR_H
#define EDITOR_H

#include <QObject>

class Editor : public QObject
{
    Q_OBJECT
public:
    explicit Editor(QObject *parent = nullptr);

signals:

public slots:
};

#endif // EDITOR_H