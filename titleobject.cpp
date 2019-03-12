#include "titleobject.h"

TitleObject::TitleObject(QObject *parent, QString t, bool i, QString u) :
    QObject(parent),
    title(t),
    isTitle(i),
    userInfo(u)
{
}
