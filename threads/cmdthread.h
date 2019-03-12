#ifndef CMDTHREAD_H
#define CMDTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include "mutualthread.h"

class CmdThread : public QThread
{
    Q_OBJECT
public:
    explicit CmdThread(QWidget *parent = 0, Cmd *c = NULL): cmd (c) {

    };
    void run();

private:
    Cmd * cmd;

signals:
    void onCmdThreadDidRecvData (int flag, QString result);

public slots:
};

#endif // CMDTHREAD_H
