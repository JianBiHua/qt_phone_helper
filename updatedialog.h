#ifndef UPDATEDIALOG_H
#define UPDATEDIALOG_H

#include <QDialog>

namespace Ui {
class UpdateDialog;
}

class UpdateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateDialog(QWidget *parent = 0);
    ~UpdateDialog();

private slots:
    void on_pushButton_clicked();

    void on_pbClose_clicked();

private:
    Ui::UpdateDialog *ui;
};

#endif // UPDATEDIALOG_H
