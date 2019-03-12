#ifndef SMTEST_H
#define SMTEST_H

#include <QWidget>
#include "smbase.h"

namespace Ui {
class SMTest;
}

class SMTest : public SMBase
{
    Q_OBJECT

public:
    explicit SMTest(QWidget *parent = 0);
    ~SMTest();

private:
    Ui::SMTest *ui;
};

#endif // SMTEST_H
