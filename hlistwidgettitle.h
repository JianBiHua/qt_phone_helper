#ifndef HLISTWIDGETTITLE_H
#define HLISTWIDGETTITLE_H

#include <QWidget>
#include "titleobject.h"

namespace Ui {
class HListWidgetTitle;
}

class HListWidgetTitle : public QWidget
{
    Q_OBJECT

public:
    explicit HListWidgetTitle(QWidget *parent = 0);
    ~HListWidgetTitle();

private:
    Ui::HListWidgetTitle *ui;

public:
    void show (TitleObject * to);

    void shadow ();
};

#endif // HLISTWIDGETTITLE_H
