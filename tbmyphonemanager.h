#ifndef TBMYPHONEMANAGER_H
#define TBMYPHONEMANAGER_H

#include <QWidget>
#include <QListWidgetItem>
#include <QStackedWidget>

#include "TitleObject.h"
#include "phonehandler.h"
#include "threads/mutualthread.h"
#include "submenu/smtest.h"
#include "submenu/smclear.h"
#include "submenu/smmyapp.h"
#include "submenu/smupgrade.h"
#include "submenu/smsysapp.h"
#include "submenu/smphoto.h"
#include "submenu/smotherphoto.h"
#include "submenu/smwallpaper.h"
#include "submenu/smmyvideo.h"
#include "submenu/smmymusic.h"
#include "submenu/smmyring.h"
#include "submenu/smmybook.h"

namespace Ui {
class tbMyPhoneManager;
}

class tbMyPhoneManager : public QWidget
{
    Q_OBJECT

public:
    explicit tbMyPhoneManager(QWidget *parent = 0);
    ~tbMyPhoneManager();

private:
    Ui::tbMyPhoneManager *ui;
    QVector<TitleObject*> list;
    int oldIndex ;
    QStackedWidget * stackedWidget;

    SMMyApp * myApp;
    SMSysApp * sysApp;
    SMPhoto * photo;
    SMMyVideo * video;
    SMMyMusic * music;

signals:
    void onBackHome ();

private slots:
    void on_item_clicked(QListWidgetItem * item);

private:
    void optionListWidget () ;
    QWidget * titleListWidgetItem (TitleObject * to);
    QWidget * cellListWidgetItem (TitleObject * to) ;

    void optionStackedWidget ();
    void setTabWidgetCurrentIndex (int type);

    void showFileDialog () ;
    void showAddressBook ();

    int indexOf (int row);

public:
    void setInitType (int type);
};

#endif // TBMYPHONEMANAGER_H
