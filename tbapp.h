#ifndef TBAPP_H
#define TBAPP_H

#include <QWidget>
#include "tbtodaynews.h"

namespace Ui {
class TBApp;
}

class TBApp : public TBTodayNews
{
    Q_OBJECT

public:
    explicit TBApp(QWidget *parent = 0);
    ~TBApp();
};

#endif // TBAPP_H
