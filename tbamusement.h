#ifndef TBAMUSEMENT_H
#define TBAMUSEMENT_H

#include <QWidget>
#include "tbplaygame.h"

class TBAmusement : public TBPlayGame
{
    Q_OBJECT
public:
    explicit TBAmusement(QWidget *parent = 0);

signals:

public slots:
};

#endif // TBAMUSEMENT_H
