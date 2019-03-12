#ifndef TBPCGAME_H
#define TBPCGAME_H

#include <QWidget>
#include "tbtodaynews.h"

class TBPCGame : public TBTodayNews
{
    Q_OBJECT

public:
    explicit TBPCGame(QWidget *parent = 0);
    ~TBPCGame();
};

#endif // TBPCGAME_H
