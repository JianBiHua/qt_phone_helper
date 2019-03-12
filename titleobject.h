#ifndef TITLEOBJECT_H
#define TITLEOBJECT_H

#include <QObject>
#include <QIcon>

class TitleObject : public QObject
{
    Q_OBJECT
public:
    explicit TitleObject(QObject *parent = 0, QString t = "", bool i = false, QString u="");

signals:

public slots:

public:
    QString title;
    // 是不是标题类
    bool isTitle;
    QString userInfo;
};

#endif // TITLEOBJECT_H
