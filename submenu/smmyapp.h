#ifndef SMMYAPP_H
#define SMMYAPP_H

#include <QWidget>
#include "smbase.h"
#include "phonehandler.h"

namespace Ui {
class SMMyApp;
}

class SMMyApp : public SMBase
{
    Q_OBJECT

public:
    explicit SMMyApp(QWidget *parent = 0);
    ~SMMyApp();

private slots:
    void on_tbShuaxin_clicked();

    void on_apps_changed() ;

    void on_tbAnzhuang_clicked();

    void on_uninstall_pb_clicked(bool b);

private:
    Ui::SMMyApp *ui;


private:
    void optionToolButtons ();
    void optionTableWidget ();
};

#endif // SMMYAPP_H
