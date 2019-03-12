#include "screenshotwidget.h"
#include "ui_screenshotwidget.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <qdebug.h>
#include <qdesktopwidget.h>
#include <QScreen>

ScreenshotWidget::ScreenshotWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenshotWidget)
{
    ui->setupUi(this);
    takeScreenshot();
}

ScreenshotWidget::~ScreenshotWidget()
{
    delete ui;
}


void ScreenshotWidget::takeScreenshot()
{
    threadScreenshot.widthScreen = this->ui->QLb_screens->width();
    threadScreenshot.heightScreen = this->ui->QLb_screens->height();
    threadScreenshot.start();
    connect(&threadScreenshot, SIGNAL(gotScreenshot(QImage, int, int)), this, SLOT(showScreenshot(QImage, int, int)));
    connect(&threadScreenshot, SIGNAL(gotScreenshotError()), this, SLOT(showScreenshotError()));
}

// 截图
bool ScreenshotWidget::screenshotPhoto () {
    //--！！！！！！注意 writableLocation（）函数
    if (!this->screenshot.isNull ())
    {
        QString fileName = QFileDialog::getSaveFileName(this,"Save File", QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
        this->screenshot.save(fileName, "JPG");
        qDebug () << fileName;
        qDebug () << this->screenshot;

        return true;
    }

    return false;
}

void ScreenshotWidget::showScreenshot(QImage image, int width, int height)
{
    qDebug () << "showScreenshot11";
    //
    emit onScreenshotConnect (true);

    QSize scaledSize = QSize(width, height);
    scaledSize.scale(this->size(), Qt::KeepAspectRatio);
    this->screenshot = QPixmap::fromImage(image, Qt::AutoColor);
    this->ui->QLb_screens->setPixmap(this->screenshot.scaled(this->ui->QLb_screens->size(),
                                                             Qt::KeepAspectRatio,
                                                             Qt::SmoothTransformation));
    disconnect(this, SLOT(showScreenshot(QImage,int,int)));
}

void ScreenshotWidget::showScreenshotError () {
    emit onScreenshotConnect (false);
}
