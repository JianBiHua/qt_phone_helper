#ifndef TBSMALLAPP_H
#define TBSMALLAPP_H

#include <QWidget>
#include "tbtodaynews.h"

class TBSmallApp : public TBTodayNews
{
    Q_OBJECT

public:
    explicit TBSmallApp(QWidget *parent = 0);
    ~TBSmallApp();
};

#endif // TBSMALLAPP_H
