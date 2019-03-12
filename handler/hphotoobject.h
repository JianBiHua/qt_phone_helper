#ifndef HPHOTOOBJECT_H
#define HPHOTOOBJECT_H

#include <QObject>

class HPhotoObject : public QObject
{
    Q_OBJECT
public:
    explicit HPhotoObject(QObject *parent = 0);

signals:

public slots:

public:
    QString id;
    QString path;
    QString name;
    QString mime_type;
    QString size;
};

#endif // HPHOTOOBJECT_H
