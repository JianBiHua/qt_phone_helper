#ifndef SMUPGRADE_H
#define SMUPGRADE_H

#include <QWidget>
#include "smbase.h"

namespace Ui {
class SMUpgrade;
}

class SMUpgrade : public SMBase
{
    Q_OBJECT

public:
    explicit SMUpgrade(QWidget *parent = 0);
    ~SMUpgrade();

private:
    Ui::SMUpgrade *ui;

private:
    void optionToolButtons ();
    void optionTableWidget () ;
};

#endif // SMUPGRADE_H
