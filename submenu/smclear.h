#ifndef SMCLEAR_H
#define SMCLEAR_H

#include <QWidget>
#include "smbase.h"

namespace Ui {
class SMClear;
}

class SMClear : public SMBase
{
    Q_OBJECT

public:
    explicit SMClear(QWidget *parent = 0);
    ~SMClear();

private:
    Ui::SMClear *ui;
};

#endif // SMCLEAR_H
