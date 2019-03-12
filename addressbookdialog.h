#ifndef ADDRESSBOOKDIALOG_H
#define ADDRESSBOOKDIALOG_H

#include <QDialog>
#include <QToolButton>
#include <QVector>
#include <QTableWidgetItem>
#include <QListWidgetItem>
#include "phonehandler.h"
#include <QLabel>


namespace Ui {
class AddressBookDialog;
}

class AddressBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddressBookDialog(QWidget *parent = 0);
    ~AddressBookDialog();

private slots:
    void on_pbClose_clicked();

    void on_lianxiren_item_clicked(QListWidgetItem* item);

    void on_smslistwidget_clicked(QListWidgetItem* item);

    void on_tbShaxin1_clicked();

    void on_tbShaxin_clicked();

    void on_addressbook_changed ();

    void on_sms_changed ();

private:
    Ui::AddressBookDialog *ui;
    int oldAddressIndex;

public:
    void setType (int type);

private:
    void optionLianxiren ();
    void optionDuanxin ();
    void optionToolButton (QToolButton * tb, QIcon icon, QString text);
    void optionTreeWidget ();
    void optionLianxirenTableWidget ();
    void optionSmsListWidget () ;
    QWidget * getLianxirenCell (HAddressObject * ao);
    void updateAddressInfo (HAddressObject * ao);

    void optionsmsItemListWidget (int row);

    QSize labelSize (QLabel * lb);
};

#endif // ADDRESSBOOKDIALOG_H
