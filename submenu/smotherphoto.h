#ifndef SMOTHERPHOTO_H
#define SMOTHERPHOTO_H

#include <QWidget>
#include "smbase.h"

namespace Ui {
class SMOtherPhoto;
}

class SMOtherPhoto : public SMBase
{
    Q_OBJECT

public:
    explicit SMOtherPhoto(QWidget *parent = 0);
    ~SMOtherPhoto();

private:
    Ui::SMOtherPhoto *ui;

private:
    void optionToolButtons ();
};

#endif // SMOTHERPHOTO_H
