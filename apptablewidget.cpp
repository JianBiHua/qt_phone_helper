#include "apptablewidget.h"
#include <QMimeData>
#include <qdebug.h>

AppTableWidget::AppTableWidget(QWidget *parent) : QTableWidget(parent)
{
     setAcceptDrops(true);
     setDragDropMode(QAbstractItemView::DragDrop);
     setDragEnabled(true);
     setDropIndicatorShown(true);
     setDragEnabled(true);
    //   setViewMode(QTableWidget::IconMode);
    //   setIconSize(QSize(m_PieceSize, m_PieceSize));
     //  setSpacing(10);
       setAcceptDrops(true);
       setDropIndicatorShown(true);
}

void AppTableWidget::dragEnterEvent(QDragEnterEvent*event){
    qDebug() << "dragEnterEvent: ";
    //如果类型是apk才能接受拖动。
    //这里的compare字符串比较函数，相等的时候返回0，所以要取反
   if(!event->mimeData()->urls()[0].fileName().right(3).compare("apk"))
       //event->acceptProposedAction();
         event->accept ();
    else {
       event->ignore();//否则不接受鼠标事件

   }
   QTableWidget::dragEnterEvent(event);
}

//放下事件
void AppTableWidget::dropEvent(QDropEvent*event){
    qDebug() << "dropEvent: ";

    QTableWidget::dropEvent(event);

    const QMimeData*qm=event->mimeData();//获取MIMEData
    //QPixmapqp(qm->urls()[0].toLocalFile());//.toLocalFile()是获取拖动文件的本地路径。
    //ui->label->resize(qp.width(),qp.height());//让label大小契合图片实际大小
    //ui->label->setPixmap(qp);//显示图片
}
