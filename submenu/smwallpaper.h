#ifndef SMWALLPAPER_H
#define SMWALLPAPER_H

#include <QWidget>
#include "smbase.h"

namespace Ui {
class SMWallpaper;
}

class SMWallpaper : public SMBase
{
    Q_OBJECT

public:
    explicit SMWallpaper(QWidget *parent = 0);
    ~SMWallpaper();

private:
    Ui::SMWallpaper *ui;

private:
    void optionToolButtons ();
};

#endif // SMWALLPAPER_H
