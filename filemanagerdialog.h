#ifndef FILEMANAGERDIALOG_H
#define FILEMANAGERDIALOG_H

#include <QDialog>
#include <QToolButton>
#include <QTreeWidget>
#include <QTableWidget>

namespace Ui {
class FileManagerDialog;
}

class FileManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileManagerDialog(QWidget *parent = 0);
    ~FileManagerDialog();

private slots:
    void on_pbClose_clicked();

private:
    Ui::FileManagerDialog *ui;
    QTreeWidget * treeWidget;
    QTableWidget * tableWidget;

private:
    void optionMainWidget ();
    void optionToolButtons ();
    void optionToolButton (QToolButton * tb, QIcon icon, QString text);
    void optionTreeWidget ();
    void optionTableWidget ();
};

#endif // FILEMANAGERDIALOG_H
