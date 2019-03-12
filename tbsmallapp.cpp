#include "tbsmallapp.h"

TBSmallApp::TBSmallApp(QWidget *parent) :
    TBTodayNews(parent)
{
    //
    showUrl ("http://openbox.mobilem.360.cn/LiteApp/?ver=2.5.1.1630");
}

TBSmallApp::~TBSmallApp()
{
}
