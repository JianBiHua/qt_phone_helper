#include "paintwidget.h"
#include <QPainter>

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
    // 默认模式
    backgroundMode = 0;
    this->setMouseTracking (true);
}

void PaintWidget::setBackgroundMode (int m) {
    backgroundMode = m;
    // 重新绘制
    update ();
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    if (backgroundMode == 0 ||
            backgroundMode == -1) {
        paintBackGroundMode0 ();
    } else if (backgroundMode == 1) {
        paintBackGroundMode1 ();
    } else if (backgroundMode == 2) {
        paintBackGroundMode2 ();
    }
}

void PaintWidget::paintBackGroundMode0 () {
    QPainter painter(this);

    // 反走样
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(QPen(QColor(0x00,0xff,0x00,0x00)));
    painter.setBrush(QBrush(QColor(0xF1, 0xF1, 0xF1, 0xFF)));

    // 各个点的坐标
    static const QPointF points[4] = {QPointF(0, 0),
                                      QPointF(this->width (), 0),
                                      QPointF(this->width (), this->height ()),
                                      QPointF(0, this->height ())};

    // 绘制多边形
    painter.drawPolygon(points, 4);

    //
    // 设置画笔颜色
    QPainter painter2(this);

    // 反走样
    painter2.setRenderHint(QPainter::Antialiasing, true);

    painter2.setPen(QColor(0xDB, 0xDB, 0xDB));
    //绘制直线
    painter2.drawLine(QPointF(width ()-1, 0),
                     QPointF(width()-1, height()));
}

void PaintWidget::paintBackGroundMode1 () {
    QPainter painter(this);

    // 反走样
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 设置画笔颜色
    painter.setPen(QColor(0x00,0xff,0x00,0x00));
    //painter.setPen(QPen(Qt::white,1,Qt::SolidLine,Qt::RoundCap));
    painter.setBrush(QBrush(QColor(0x42, 0xB7, 0x6A)));

    // 各个点的坐标
    static const QPointF points[7] = {QPointF(0, 0),
                                      QPointF(this->width (), 0),
                                      QPointF(this->width (),10),
                                      QPointF(this->width ()-5, 14),
                                      QPointF(this->width (), 18),
                                      QPointF(this->width (), 28),
                                      QPointF(0, 28)};

    // 绘制多边形
    painter.drawPolygon(points, 7);
}

void PaintWidget::paintBackGroundMode2 () {
    QPainter painter(this);

    // 反走样
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(QPen(QColor(0x00,0xff,0x00,0x00)));
    painter.setBrush(QBrush(QColor(0xA9, 0xF2, 0xC2, 0xFF)));

    // 各个点的坐标
    static const QPointF points[4] = {QPointF(0, 0),
                                      QPointF(this->width (), 0),
                                      QPointF(this->width (), this->height ()),
                                      QPointF(0, this->height ())};

    // 绘制多边形
    painter.drawPolygon(points, 4);

    //
    // 设置画笔颜色
    QPainter painter2(this);

    // 反走样
    painter2.setRenderHint(QPainter::Antialiasing, true);

    painter2.setPen(QColor(0xDB, 0xDB, 0xDB));
    //绘制直线
    painter2.drawLine(QPointF(width ()-1, 0),
                     QPointF(width()-1, height()));
}

void PaintWidget::enterEvent(QEvent * event)//进入事件
{
    if (backgroundMode != 1 &&
            backgroundMode != -1) {
        backgroundMode = 2;
        update ();
    }
}

void PaintWidget::leaveEvent(QEvent * event) {
    if (backgroundMode != 1 &&
            backgroundMode != -1) {
        backgroundMode = 0;
        update ();
    }
}
