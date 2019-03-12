#ifndef TBPLAYGAME_H
#define TBPLAYGAME_H

#include <QWidget>
#include "titleobject.h"

namespace Ui {
class TBPlayGame;
}

class TBPlayGame : public QWidget
{
    Q_OBJECT

public:
    explicit TBPlayGame(QWidget *parent = 0);
    ~TBPlayGame();

private:
    Ui::TBPlayGame *ui;

private:
    void showListWidget (QVector<TitleObject*> list) ;

public slots:
    void on_hlistwidget_item_clicked(TitleObject * to);
};

#endif // TBPLAYGAME_H
