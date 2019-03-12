#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPaintEvent>

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = 0);

signals:

public slots:

public:
    void setBackgroundMode (int m);

private:
    void paintBackGroundMode0 ();
    void paintBackGroundMode1 ();
    void paintBackGroundMode2 ();

private:
    int backgroundMode;

protected:
    void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent * event) ;
};

#endif // PAINTWIDGET_H
