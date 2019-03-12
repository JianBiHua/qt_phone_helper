#-------------------------------------------------
#
# Project created by QtCreator 2017-03-01T16:01:31
#
#-------------------------------------------------

QT       += core gui webenginewidgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 360手机助手
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    tbmyphone.cpp \
    tbtodaynews.cpp \
    tbplaygame.cpp \
    tbfindapp.cpp \
    tbapp.cpp \
    tbamusement.cpp \
    tbsmallapp.cpp \
    tbpcgame.cpp \
    logindialog.cpp \
    downloaddialog.cpp \
    searchwidget.cpp \
    hlistwidget.cpp \
    titleobject.cpp \
    hlistwidgettitle.cpp \
    aboutdialog.cpp \
    updatedialog.cpp \
    settingdialog.cpp \
    screenshotwidget.cpp \
    threads/screenshotthread.cpp \
    threads/connectionthread.cpp \
    tbmyphonemanager.cpp \
    questiondialog.cpp \
    filemanagerdialog.cpp \
    addressbookdialog.cpp \
    paintwidget.cpp \
    submenu/smtest.cpp \
    submenu/smclear.cpp \
    submenu/smmyapp.cpp \
    submenu/smupgrade.cpp \
    submenu/smsysapp.cpp \
    submenu/smphoto.cpp \
    submenu/smotherphoto.cpp \
    submenu/smwallpaper.cpp \
    submenu/smmyvideo.cpp \
    submenu/smmymusic.cpp \
    submenu/smmyring.cpp \
    submenu/smmybook.cpp \
    submenu/smbase.cpp \
    phonehandler.cpp \
    threads/mutualthread.cpp \
    handler/hsmsobject.cpp \
    handler/hvideoobject.cpp \
    handler/hphotoobject.cpp \
    handler/haudioobject.cpp \
    handler/happobject.cpp \
    handler/hfileobject.cpp \
    handler/haddressobject.cpp \
    handler/hcallobject.cpp \
    threads/cmdthread.cpp \
    apptablewidget.cpp

HEADERS  += mainwindow.h \
    tbmyphone.h \
    tbtodaynews.h \
    tbplaygame.h \
    tbfindapp.h \
    tbapp.h \
    tbamusement.h \
    tbsmallapp.h \
    tbpcgame.h \
    logindialog.h \
    downloaddialog.h \
    searchwidget.h \
    hlistwidget.h \
    titleobject.h \
    hlistwidgettitle.h \
    aboutdialog.h \
    updatedialog.h \
    settingdialog.h \
    screenshotwidget.h \
    threads/screenshotthread.h \
    threads/connectionthread.h \
    tbmyphonemanager.h \
    questiondialog.h \
    filemanagerdialog.h \
    addressbookdialog.h \
    paintwidget.h \
    submenu/smtest.h \
    submenu/smclear.h \
    submenu/smmyapp.h \
    submenu/smupgrade.h \
    submenu/smsysapp.h \
    submenu/smphoto.h \
    submenu/smotherphoto.h \
    submenu/smwallpaper.h \
    submenu/smmyvideo.h \
    submenu/smmymusic.h \
    submenu/smmyring.h \
    submenu/smmybook.h \
    submenu/smbase.h \
    phonehandler.h \
    threads/mutualthread.h \
    handler/hsmsobject.h \
    handler/hvideoobject.h \
    handler/hphotoobject.h \
    handler/haudioobject.h \
    handler/happobject.h \
    handler/hfileobject.h \
    handler/haddressobject.h \
    handler/hcallobject.h \
    threads/cmdthread.h \
    apptablewidget.h

FORMS    += mainwindow.ui \
    tbmyphone.ui \
    tbtodaynews.ui \
    tbplaygame.ui \
    logindialog.ui \
    downloaddialog.ui \
    hlistwidgettitle.ui \
    aboutdialog.ui \
    updatedialog.ui \
    settingdialog.ui \
    screenshotwidget.ui \
    tbmyphonemanager.ui \
    questiondialog.ui \
    filemanagerdialog.ui \
    addressbookdialog.ui \
    submenu/smtest.ui \
    submenu/smclear.ui \
    submenu/smmyapp.ui \
    submenu/smupgrade.ui \
    submenu/smsysapp.ui \
    submenu/smphoto.ui \
    submenu/smotherphoto.ui \
    submenu/smwallpaper.ui \
    submenu/smmyvideo.ui \
    submenu/smmymusic.ui \
    submenu/smmyring.ui \
    submenu/smmybook.ui

DISTFILES += \
    qss/styles.qss \
    icon.rc \
    icon.ico \
    tools/adb

RESOURCES += \
    resources.qrc

#图标设置
#如果不能设置成功，请删除编译文件，如build-PPCAServer-Desktop_Qt_5_4_1_clang_64bit-release
#http://blog.csdn.net/lifang303166/article/details/8840234
RC_FILE += icon.rc
ICON = icon.ico
