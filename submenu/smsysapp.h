#ifndef SMSYSAPP_H
#define SMSYSAPP_H

#include <QWidget>
#include "smbase.h"
#include "phonehandler.h"

namespace Ui {
class SMSysApp;
}

class SMSysApp : public SMBase
{
    Q_OBJECT

public:
    explicit SMSysApp(QWidget *parent = 0);
    ~SMSysApp();

private slots:
    void on_tbShuaxin_clicked();

    void on_sys_apps_changed() ;


private:
    Ui::SMSysApp *ui;

private:
    void optionToolButtons ();
    void optionTableWidget () ;
};

#endif // SMSYSAPP_H
