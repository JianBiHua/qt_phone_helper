#ifndef HAUDIOOBJECT_H
#define HAUDIOOBJECT_H

#include <QObject>

class HAudioObject : public QObject
{
    Q_OBJECT
public:
    explicit HAudioObject(QObject *parent = 0);

signals:

public slots:
public:
    QString id;
    QString path;
    QString name;
    QString size;
};

#endif // HAUDIOOBJECT_H
