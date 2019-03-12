#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QLineEdit;

class SearchWidget : public QWidget
{
    Q_OBJECT

public:
    SearchWidget(QWidget *parent = 0);
    ~SearchWidget();

private slots:
    void search();

private:
    QLineEdit *m_pSearchLineEdit;
};

#endif // WIDGET_H
