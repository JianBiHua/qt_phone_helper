#include "tbapp.h"

TBApp::TBApp(QWidget *parent) :
    TBTodayNews(parent)
{
    //
    showUrl ("http://openbox.mobilem.360.cn/appfun/index?from=client&ver=2.5.1.1630");
}

TBApp::~TBApp()
{
}
