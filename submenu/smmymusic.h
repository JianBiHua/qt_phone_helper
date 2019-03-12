#ifndef SMMYMUSIC_H
#define SMMYMUSIC_H

#include <QWidget>
#include "smbase.h"
#include "phonehandler.h"

namespace Ui {
class SMMyMusic;
}

class SMMyMusic : public SMBase
{
    Q_OBJECT

public:
    explicit SMMyMusic(QWidget *parent = 0);
    ~SMMyMusic();

private slots:
    void on_tbShuaxin_clicked();

    void on_audios_changed() ;

private:
    Ui::SMMyMusic *ui;


private:
    void optionToolButtons ();
    void optionTableWidget ();
};

#endif // SMMYMUSIC_H
