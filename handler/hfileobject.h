#ifndef HFILEOBJECT_H
#define HFILEOBJECT_H

#include <QObject>
#include <QVector>

class HFileObject : public QObject
{
    Q_OBJECT
public:
    explicit HFileObject(QObject *parent = 0);

signals:

public slots:

public:
    QString name;
    bool isDirecory;
    QString size;
    QString date;

    //子目录
    QVector<HFileObject *> listFlies;
};

#endif // HFILEOBJECT_H
