#ifndef HAPPOBJECT_H
#define HAPPOBJECT_H

#include <QObject>

class HAppObject : public QObject
{
    Q_OBJECT
public:
    explicit HAppObject(QObject *parent = 0);

signals:

public slots:

public:
    QString name;
    QString package;
    QString version;
    QString versionCode;
    QString size;
    // 安装位置.
    QString location;
    // 应用类型
    QString type;
};

#endif // HAPPOBJECT_H
