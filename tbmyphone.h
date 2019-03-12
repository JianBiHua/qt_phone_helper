#ifndef TBMYPHONE_H
#define TBMYPHONE_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class TBMyPhone;
}

class TBMyPhone : public QWidget
{
    Q_OBJECT

public:
    explicit TBMyPhone(QWidget *parent = 0);
    ~TBMyPhone();

signals:
    void onMyPhoneDidSelected (int type);

private slots:
    void on_pbFresh_clicked();

    void on_pbScreenShot_clicked();

    void on_pbScreenShot_connect(bool success);

    void slotConnectionChanged(int type,QString msg);

    void on_listwidget_clicked(QListWidgetItem* item) ;

    void on_back_home ();

private:
    Ui::TBMyPhone *ui;

private:
    void optionListWidget ();
    void showHome (bool s);

    void showFileDialog () ;
    void showAddressBook (int type) ;

protected:
    void mousePressEvent(QMouseEvent *ev);

public:
    void reset ();
};

#endif // TBMYPHONE_H
