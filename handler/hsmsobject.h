#ifndef HSMSOBJECT_H
#define HSMSOBJECT_H

#include <QObject>
#include <QVector>

class HSmsObject : public QObject
{
    Q_OBJECT
public:
    explicit HSmsObject(QObject *parent = 0);

signals:

public slots:

public :
    QString name;
    QString phone;
    QString body;
    QString date;
    QString type;

    QVector <HSmsObject *> subSms;
};

#endif // HSMSOBJECT_H
