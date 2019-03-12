#include "smbase.h"
#include <QAction>

SMBase::SMBase(QWidget *parent) : QWidget(parent)
{
}

void SMBase::optionToolsBackGound (QWidget * wiget) {
    wiget->setStyleSheet ("background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #F1F1F1, stop:1 #FDFDFD");
}

void SMBase::optionToolButton (QToolButton * tb, QIcon icon, QString text)
{
    QAction *pAction = new QAction(this);
    pAction->setText(text);
    pAction->setIcon(icon);
    tb->setIconSize(QSize(20, 20));
    tb->setDefaultAction(pAction);
    tb->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    tb->setStyleSheet ("border:none;");
}
