#ifndef SMMYBOOK_H
#define SMMYBOOK_H

#include <QWidget>
#include "smbase.h"

namespace Ui {
class SMMyBook;
}

class SMMyBook : public SMBase
{
    Q_OBJECT

public:
    explicit SMMyBook(QWidget *parent = 0);
    ~SMMyBook();

private:
    Ui::SMMyBook *ui;

private:
    void optionToolButtons ();
};

#endif // SMMYBOOK_H
