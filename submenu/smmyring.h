#ifndef SMMYRING_H
#define SMMYRING_H

#include <QWidget>
#include "smbase.h"
#include "phonehandler.h"

namespace Ui {
class SMMyRing;
}

class SMMyRing : public SMBase
{
    Q_OBJECT

public:
    explicit SMMyRing(QWidget *parent = 0);
    ~SMMyRing();

private:
    Ui::SMMyRing *ui;

private:
    void optionToolButtons ();
    void optionTableWidget ();

private slots:
    void on_rings_changed() ;
};

#endif // SMMYRING_H
