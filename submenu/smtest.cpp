#include "smtest.h"
#include "ui_smtest.h"

SMTest::SMTest(QWidget *parent) :
    SMBase(parent),
    ui(new Ui::SMTest)
{
    ui->setupUi(this);

    ui->backgroundWidget->setStyleSheet ("border-image: url(:/images/myphone_check.jpg)");
}

SMTest::~SMTest()
{
    delete ui;
}
