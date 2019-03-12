#ifndef SMBASE_H
#define SMBASE_H

#include <QWidget>
#include <QToolButton>

class SMBase : public QWidget
{
    Q_OBJECT
public:
    explicit SMBase(QWidget *parent = 0);

signals:

public slots:

protected:
    void optionToolsBackGound (QWidget * wiget);
    void optionToolButton (QToolButton * tb, QIcon icon, QString text);
};

#endif // SMBASE_H
