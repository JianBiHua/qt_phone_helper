#ifndef HCALLOBJECT_H
#define HCALLOBJECT_H

#include <QObject>

class HCallObject : public QObject
{
    Q_OBJECT
public:
    explicit HCallObject(QObject *parent = 0);

signals:

public slots:

public:
    QString phone;
    QString date;
    QString duration;
    QString type;
};

#endif // HCALLOBJECT_H
