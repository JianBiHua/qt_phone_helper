#include "smclear.h"
#include "ui_smclear.h"

SMClear::SMClear(QWidget *parent) :
    SMBase(parent),
    ui(new Ui::SMClear)
{
    ui->setupUi(this);

    ui->backgroundWidget->setStyleSheet (QString("border-image: url(:/images/myphone_weixinclear.png)"));
}

SMClear::~SMClear()
{
    delete ui;
}
