#ifndef APPTABLEWIDGET_H
#define APPTABLEWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QDragEnterEvent>
#include <QMouseEvent>
#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>

class AppTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit AppTableWidget(QWidget *parent = 0);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

signals:

public slots:
};

#endif // APPTABLEWIDGET_H
