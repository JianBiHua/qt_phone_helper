#ifndef PHONEHANDLER_H
#define PHONEHANDLER_H

#include <QObject>
#include <QVector>
#include "threads/mutualthread.h"
#include "handler/haddressobject.h"
#include "handler/happobject.h"
#include "handler/haudioobject.h"
#include "handler/hcallobject.h"
#include "handler/hfileobject.h"
#include "handler/hphotoobject.h"
#include "handler/hsmsobject.h"
#include "handler/hvideoobject.h"

/**
* 实现方法:
*   第一种. 开发一个手机端程序,通过手机段程序将手机上的相关信息读取到,然后通过tcp等方式,发会到
*           电脑客户端(我想360手机助手就是这种方式)
*   第二种. 仅供学习只用. 手机信息放在(/data/data/com.android.providers.contacts/databases/contacts2.db)中,
*           讲该文件adb pull 到本地进行解析, 自己解析比较麻烦,号多东西不知道意思.
*
*/

class PhoneHandler : public QObject
{
    Q_OBJECT
public:
    static PhoneHandler* getInstance()
    {
           static QMutex mutex;
           if (!instance)
           {
               QMutexLocker locker(&mutex);
               instance = new PhoneHandler;
               instance->start ();
            }

           return instance;
    }

signals:
    void onAppsChanged();
    void onSysAppsChanged();
    void onVideosChanged();
    void onAudiosChanged();
    void onRingsChanged();
    void onPhotosChanged();
    void onCallLogsChanged();
    void onFileListChanged();
    void onSmsChanged();
    void onAddressBookChanged();

public slots:
    void on_mutual_readData (int flag, QString result) ;

private:
    MutualThread * mutualThread;
    static PhoneHandler* instance;

public:
    QVector<HAppObject *> listApps;
    QVector<HAppObject *> listSysApps;
    QVector<HAddressObject *> listAddresss;
    QVector<HAudioObject *> listAudio;
    QVector<HCallObject *> listCalls;
    QVector<HFileObject *> listFiles;
    QVector<HPhotoObject *> listPhotos;
    QVector<HSmsObject *> listSms;
    QVector<HVideoObject *> listVideos;

public:
    void start ();

    void resetVideos ();
    void resetApps ();
    void resetSysApps ();
    void resetAddressBook ();
    void resetCallLog ();
    void resetFileList (QString path);
    void resetSms () ;
    void resetAudios () ;
    void resetPhotos () ;

    void parseApps (QString result);
    void parseSysApps (QString result);
    void parseVideos (QString result);
    void parseAudios (QString result);
    void parseAddressBook (QString result);
    void parseSms (QString result);
    void parseFileList (QString result);
    void parseCallLog (QString result);
    void parsePhotos (QString result);

    void test ();

    void install (QString path);
    void uninstall (QString package);

private:
    void groupSms (QVector<HSmsObject *> list);
    HSmsObject* exsitSms (HSmsObject * obj);
};

#endif // PHONEHANDLER_H
