#include "mutualthread.h"
#include <QProcess>
#include "cmdthread.h"

// adb 所在路径,如果错了,命令就执行不对了.
QString MutualThread::adbPath () {
    ///Users/Yueer/Documents/SourceCode/QTProjects/build-PhoneHandler-Desktop_Qt_5_8_0_clang_64bit-Release
    return QString("/Users/Yueer/Documents/SourceCode/QTProjects/PhoneHandler/tools/adb");
}

void MutualThread::commandNoResult (QString cmd) {
    qDebug () << "commandNoResult: " << cmd;
    QProcess *phone=new QProcess(this);
    phone->start(cmd);
    phone->waitForFinished(-1);
}

void MutualThread::run()
{
#if 0
    this->socket = new QTcpSocket();

    // connected
    connect( this->socket, SIGNAL(connected()), this, SLOT(socketConnected()) );
    connect( this->socket, SIGNAL(disconnected()), this, SLOT(socketDisConnected()) );

    this->socket->connectToHost("127.0.0.1",5000,QTcpSocket::ReadWrite);
    bool connected = this->socket->waitForConnected ();//waitForConnected();

    qDebug () << "waitForConnected: " << connected;
    if (connected) {
        while (true)
        {
            if (cmdList.size () > 0) {
                Cmd * cmd = cmdList.at (0);
                QString result = "";
                qDebug () << "flage: " << cmd->flag ;

                this->socket->write(cmd->cmd.toUtf8 ());

                while (true) {
                    this->socket->waitForReadyRead ();
                    qDebug () << "waitForReadyRead" ;
                    char buffer[1024*10];
                    memset (buffer, 0, 1024*10);
                    int s = this->socket->read (buffer, 1024*10);
                    if (s == 0) {
                        qDebug () << "flag: " << cmd->flag << " break...." ;
                        break;
                    }
                    result.append (QString (buffer));

                }
                qDebug () << "QTcpSocket.end: " << result;
                emit onMutualReadData (cmd->flag, result);

                // 删除第一个
                cmdList.remove (0);
            }
        }
    }
#else

    while (true) {
        if (cmdList.size () > 0) {
            Cmd * cmd = cmdList.at (0);
//            CmdThread * thread = new CmdThread(0, cmd);
//            connect (thread, SIGNAL(onCmdThreadDidRecvData(int,QString)), this, SIGNAL (onMutualReadData (int,QString)));
//            thread->start ();

            QTcpSocket * socket = new QTcpSocket();
            QString result = "";
            socket->connectToHost("127.0.0.1",5000,QTcpSocket::ReadWrite);
            qDebug()<<"11111111";
            if (socket->waitForConnected ())//waitForConnected();
            {
                // 发送消息
                socket->waitForBytesWritten ();
                socket->write(cmd->cmd.toUtf8 ());

                qDebug()<<"2222";
                //读消息
                while (true) {
                    socket->waitForReadyRead ();
                    char buffer[1024*10];
                    memset (buffer, 0, 1024*10);
                    qDebug()<<"333";
                    int s = socket->read (buffer, 1024*10);
                    if (s == 0) {
                        break;
                    }

                    qDebug()<<"444";
                    result.append (QString (buffer));
                }

                qDebug()<<"55555";
                emit onMutualReadData (cmd->flag, result);
            }

            qDebug()<<"6666";
            socket->disconnect ();

            cmdList.remove (0);
        }
    }


#endif
}

void MutualThread::socketConnected()
{
       qDebug () << "socketConnect";
}

/**
 * @brief HNClient::socketDisconnect
 * 功能接口
 */
void MutualThread::socketDisConnected()
{
    qDebug () << "socketDisconnect";
}

//getaddressbook
//getsms
//getapps
//getsysapps
//getcalllog
//getfilelist:/sdcard
//getvideos
//getphotos
//getaudios
void MutualThread::sendCommand (int flag, QString param) {
    switch (flag) {
    case CMD_GET_ADDRESSBOOK:
        cmdList.append (new Cmd (0, QString("getaddressbook"), flag));
        break;
    case CMD_GET_SMS:
        cmdList.append (new Cmd (0, QString("getsms"), flag));
        break;
    case CMD_GET_APPS:
        cmdList.append (new Cmd (0, QString("getapps"), flag));
        break;
    case CMD_GET_SYSAPPS:
        cmdList.append (new Cmd (0, QString("getsysapps"), flag));
        break;
    case CMD_GET_CALL_LOG:
        cmdList.append (new Cmd (0, QString("getcalllog"), flag));
        break;
    case CMD_GET_FILELIST:
        cmdList.append (new Cmd (0, QString("getfilelist:" + param), flag));
        break;
    case CMD_GET_VIDEOS:
        cmdList.append (new Cmd (0, QString("getvideos"), flag));
        break;
    case CMD_GET_PHOTOS:
        cmdList.append (new Cmd (0, QString("getphotos"), flag));
        break;
    case CMD_GET_AUDIOS:
        cmdList.append (new Cmd (0, QString("getaudios"), flag));
        break;
      }
}

void MutualThread::test () {
        cmdList.append (new Cmd (0, QString("getaddressbook"), CMD_GET_ADDRESSBOOK));
}
