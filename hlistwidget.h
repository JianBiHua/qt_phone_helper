#ifndef HLISTWIDGET_H
#define HLISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QVector>
#include "titleobject.h"
#include "HListWidgetTitle.h"

class HListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit HListWidget(QWidget *parent = 0);

signals:
    void onHListWidgetItemPress (TitleObject * to) ;

public slots:
    void on_item_entered(QListWidgetItem * item);

    void on_item_clicked(QListWidgetItem * item);

private:
    QVector<TitleObject *> list;
    int oldIndex;

public:
    void show (QVector<TitleObject *> l);

private:
    HListWidgetTitle * titleListWidgetItem (TitleObject * to);
    QWidget * cellListWidgetItem (TitleObject * to);
};

#endif // HLISTWIDGET_H
