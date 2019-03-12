#ifndef MUTUALTHREAD_H
#define MUTUALTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QVector>


#define CMD_GET_ADDRESSBOOK 0
#define CMD_GET_SMS 1
#define CMD_GET_APPS 2
#define CMD_GET_CALL_LOG 3
#define CMD_GET_FILELIST 4
#define CMD_GET_VIDEOS  5
#define CMD_GET_PHOTOS  6
#define CMD_GET_AUDIOS  7
#define CMD_GET_SYSAPPS 8

class Cmd : public QObject {

    Q_OBJECT
public:
    explicit Cmd(QWidget *parent = 0, QString c = "", int f = 0):cmd(c), flag (f) {
    };

    int flag;
    QString cmd;
};

class MutualThread : public QThread
{
    Q_OBJECT
public:
    void run();

    QTcpSocket *socket;

public:
    QString adbPath () ;
    void commandNoResult (QString cmd);

signals:
    void onMutualReadData (int flag, QString result);

    //
private slots:
    void socketConnected();
    void socketDisConnected();

public:
    //
    void sendCommand (int flag, QString param);
    void test ();

private:
    QVector<Cmd*> cmdList;
};

#endif // MUTUALTHREAD_H
