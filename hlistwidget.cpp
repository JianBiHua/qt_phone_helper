#include "hlistwidget.h"
#include <QComboBox>
#include <QLabel>
#include <qdebug.h>
#include "hlistwidgettitle.h"

HListWidget::HListWidget(QWidget *parent) : QListWidget(parent)
{
    oldIndex = -1;
    this->setSelectionMode (NoSelection);
    this->setMouseTracking(true);
    //connect(this, SIGNAL(itemEntered(QListWidgetItem *)), this,
    //        SLOT(on_item_entered(QListWidgetItem *)));
    connect(this, SIGNAL(itemClicked(QListWidgetItem *)), this,
            SLOT(on_item_clicked(QListWidgetItem *)));
}

void HListWidget::show (QVector<TitleObject*> l){
    //list = l;
    list = l;

    // 刷新界面
    for (int i = 0; i < l.size(); ++i) {
        TitleObject* to = l.at(i);

        QListWidgetItem *item = new QListWidgetItem(this);
        item->setSizeHint(QSize(150, 35));  //每次改变Item的高度
        if (to->isTitle) {
            item->setBackgroundColor (QColor(241, 243, 245));
            this->setItemWidget(item, titleListWidgetItem (to));
        } else {
            item->setBackgroundColor (QColor(253, 253, 253));
            this->setItemWidget(item, cellListWidgetItem (to));
        }
    }

    // 默认选中第二项
    this->itemClicked (item (1));
    // 这个是不是重刷新???
    //this->reset ();
}

HListWidgetTitle * HListWidget::titleListWidgetItem (TitleObject * to) {
    HListWidgetTitle * t = new HListWidgetTitle;
    t->show (to);
    return t;
}

QWidget * HListWidget::cellListWidgetItem (TitleObject * to) {
    QLabel * label = new QLabel;
    label->setText (to->title);
    label->setAlignment (Qt::AlignCenter);
    label->setGeometry (0, 0, this->width (), 35);
    return label;
}

void HListWidget::on_item_entered(QListWidgetItem * item) {

    int index = this->row (item);
    TitleObject* to = list.at(index);

    qDebug () <<"on_item_entered: " << index;
    if (to->isTitle) {
        //标题栏
        item->setBackgroundColor (QColor(241, 243, 245));
    } else {
        item->setBackgroundColor (QColor(253, 253, 253));
    }
}

void HListWidget::on_item_clicked(QListWidgetItem * item) {
    int index = this->row (item);
    TitleObject* to = list.at(index);

    if (to->isTitle) {
        //标题栏
        item->setBackgroundColor (QColor(241, 243, 245));
    } else {
        item->setBackgroundColor (QColor(66, 183, 106));
        // 只有点击子项,才有信号.
        emit onHListWidgetItemPress (to);
    }

    // 只有点击的是子项, 而不是菜单项时,恢复状态
    if (!to->isTitle) {
        if (oldIndex >= 0  && oldIndex != index) {
            to = list.at(oldIndex);
            if (to->isTitle) {
                //标题栏
                this->item (oldIndex)->setBackgroundColor (QColor(241, 243, 245));
            } else {
                this->item (oldIndex)->setBackgroundColor (QColor(253, 253, 253));
            }
        }

        oldIndex = index;
    }
}
