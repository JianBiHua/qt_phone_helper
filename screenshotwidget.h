#ifndef SCREENSHOTWIDGET_H
#define SCREENSHOTWIDGET_H

#include <QWidget>
#include "threads/screenshotthread.h"

namespace Ui {
class ScreenshotWidget;
}

class ScreenshotWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenshotWidget(QWidget *parent = 0);
    ~ScreenshotWidget();
    QPixmap screenshot;

private:
    Ui::ScreenshotWidget *ui;
    ThreadScreenshot threadScreenshot;
public slots:
    void takeScreenshot();

signals:
    // 连接状态.
    void onScreenshotConnect (bool success);

private slots:
    void showScreenshot(QImage, int, int);
    void showScreenshotError ();

public :
    bool screenshotPhoto ();
};

#endif // SCREENSHOTWIDGET_H
