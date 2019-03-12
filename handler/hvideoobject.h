#ifndef HVIDEOOBJECT_H
#define HVIDEOOBJECT_H

#include <QObject>

class HVideoObject : public QObject
{
    Q_OBJECT
public:
    explicit HVideoObject(QObject *parent = 0);

signals:

public slots:

public:
    QString id;
    QString path;
    QString name;
    QString size;
};

#endif // HVIDEOOBJECT_H
