#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QStackedWidget>
#include <QListWidgetItem>

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = 0);
    ~SettingDialog();

private slots:
    void on_pbClose_clicked();

    void on_pbEnter_clicked();

    void on_pbCancel_clicked();

    void on_listwidget_selected(QListWidgetItem * item) ;

private:
    Ui::SettingDialog *ui;
    QStackedWidget * stackedWidget;

private:
    void optionListWidget ();
    void optionStackedWidget ();
};

#endif // SETTINGDIALOG_H
