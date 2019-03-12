#ifndef HADDRESSOBJECT_H
#define HADDRESSOBJECT_H

#include <QObject>

class HAddressObject : public QObject
{
    Q_OBJECT
public:
    explicit HAddressObject(QObject *parent = 0);

signals:

public slots:

public:
    QString name;
    QString phone;

};

#endif // HADDRESSOBJECT_H
