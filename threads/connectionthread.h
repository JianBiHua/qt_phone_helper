#include <QProcess>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QImage>
#include <QTcpSocket>
#include <QThread>
#include <QIcon>
#include <QDebug>
#include <QDateTime>
#include <QTextCodec>

#define DISCONNECTED 0
#define DEVICE 1
#define RECOVERY 2
#define FASTBOOT 3


class ConnectionThread : public QThread
{
    Q_OBJECT
public:
    void run();

    QTcpSocket *socket;
signals:
    void connectionChanged(int,QString);
};
