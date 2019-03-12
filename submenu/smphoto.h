#ifndef SMPHOTO_H
#define SMPHOTO_H

#include <QWidget>
#include "smbase.h"
#include "phonehandler.h"

namespace Ui {
class SMPhoto;
}

class SMPhoto : public SMBase
{
    Q_OBJECT

public:
    explicit SMPhoto(QWidget *parent = 0);
    ~SMPhoto();

private slots:
    void on_tbShaxin_clicked();

    void on_photos_changed() ;

private:
    Ui::SMPhoto *ui;

private:
    void optionToolButtons ();
};

#endif // SMPHOTO_H
