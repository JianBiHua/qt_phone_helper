#ifndef SMMYVIDEO_H
#define SMMYVIDEO_H

#include <QWidget>
#include "smbase.h"
#include "phonehandler.h"

namespace Ui {
class SMMyVideo;
}

class SMMyVideo : public SMBase
{
    Q_OBJECT

public:
    explicit SMMyVideo(QWidget *parent = 0);
    ~SMMyVideo();

private slots:
    void on_tbShuaxin_clicked();

    void on_videos_changed() ;


private:
    Ui::SMMyVideo *ui;

private:
    void optionToolButtons ();
    void optionTableWidget ();
};

#endif // SMMYVIDEO_H
