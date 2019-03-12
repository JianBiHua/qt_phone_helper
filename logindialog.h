#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private slots:
    void on_pbLogin_clicked();

    void on_pbClose_clicked();

    void on_pbRegister_clicked();

    void on_pbFindPsw_clicked();

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
