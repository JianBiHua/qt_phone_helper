#ifndef DOWNLOADDIALOG_H
#define DOWNLOADDIALOG_H

#include <QDialog>
#include <QToolButton>

namespace Ui {
class DownLoadDialog;
}

class DownLoadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DownLoadDialog(QWidget *parent = 0);
    ~DownLoadDialog();

private slots:
    void on_pbClose_clicked();

    void on_tbGoOn_clicked();

    void on_pushbtn_clicked ();

private:
    Ui::DownLoadDialog *ui;

private:
    void optionToolButton (QToolButton * tb, QIcon icon, QString text) ;
    void optionTableWidget ();

    QWidget *cellWidget1();
    QWidget *cellWidget2();
    QWidget *cellWidget3();
    QWidget *cellWidget4();
};

#endif // DOWNLOADDIALOG_H
