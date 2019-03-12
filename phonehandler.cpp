#include "phonehandler.h"
#include <QProcess>
#include <qDebug>
#include <qdir.h>
#include <QCoreApplication>
#include <QXmlStreamReader>
#include "./threads/mutualthread.h"

PhoneHandler *PhoneHandler::instance = 0;

//case ADB_UNINSTALL:
//    command = adbpath + " shell pm uninstall -k " + adbargv;
//    qDebug()<<"Phone::getFileList() - "<< command;
//    phone->start(command);
//    phone->waitForFinished(-1);
//    outputLines=phone->readAll();
//    if (outputLines.contains("Success"))
//    {
//        phone->terminate();
//        emit adbresult(cmdtype,adbcount,SUCCESS);
//    }else{
//        emit adbresult(cmdtype,adbcount,FAILURE);
//    }
//    cmdtype = 0;
//    break;

//case ADB_INSTALL:
//    command = adbpath + " install -r " + adbargv;
//    qDebug()<<"Phone::getFileList() - "<< command;
//    phone->start(command);

//    phone->waitForFinished(-1);
//    outputLines=phone->readAll();
//    if (outputLines.contains("Success"))
//    {
//        phone->terminate();
//        emit adbresult(cmdtype, adbcount,SUCCESS);
//    }else{
//        emit adbresult(cmdtype, adbcount,FAILURE);
//    }

//    cmdtype = 0;

// adb命令:
// 完全使用adb，aapt 获取已安装apk的各种信息
// http://blog.csdn.net/victoryckl/article/details/8951113
// 读取通讯录
// https://zhidao.baidu.com/question/876835128455688412.html
//
//

//int Daemon::checkapp()
//{
//	QProcess *phone=new QProcess;
//	QString outputLines;

//	phone->start("./bin/adb shell ls /data/app/ | grep com.acanoe.phonemanager");
//	phone->waitForFinished(30000);
//	outputLines = phone->readAll();
//	if (outputLines.contains("com.acanoe.phonemanager"))
//	{
//		qDebug() << "app version correct" << outputLines;
//		outputLines = "";
//		return 1;
//	}else {
//		qDebug() << outputLines;
//		phone->start("./bin/adb  install ./bin/phonemanager.apk");
//		phone->waitForFinished(30000);
//		c_delay(2);
//		outputLines = phone->readAll();
//		if (outputLines.contains("Success"))
//		{
//			c_delay(2);
//			qDebug() << outputLines;
//			outputLines = "";
//			return 1;
//		} else {
//			qDebug() << outputLines;
//			outputLines = "";
//			return 0;
//		}
//		outputLines = "";
//		return 1;
//	}

//}
//PhoneHandler::PhoneHandler(QObject *parent) : QObject(parent)
//{
//}

void PhoneHandler::start () {
    mutualThread = new MutualThread;
    //转发的关键代码
    mutualThread->commandNoResult (QString(mutualThread->adbPath () + " forward tcp:5000 tcp:13000"));
    qDebug () << QString(mutualThread->adbPath () + " forward tcp:5000 tcp:13000");
    mutualThread->start ();
    qDebug () << "PhoneHandler>> ";

    //
    connect (mutualThread, SIGNAL(onMutualReadData(int,QString)), this, SLOT(on_mutual_readData (int, QString)));

   // mutualThread->test () ;
}

void PhoneHandler::on_mutual_readData (int flag, QString result) {
    qDebug () << "on_mutual_readData: " << flag << ", result: " << result;
    // 解析
    switch (flag) {
    case CMD_GET_ADDRESSBOOK:
        parseAddressBook (result);
        break;
    case CMD_GET_APPS:
        parseApps (result);
        break;
    case CMD_GET_SYSAPPS:
        parseSysApps (result);
        break;
    case CMD_GET_AUDIOS:
        parseAudios (result);
        break;
    case CMD_GET_CALL_LOG:
        parseCallLog (result);
        break;
    case CMD_GET_FILELIST:
        parseFileList (result);
        break;
    case CMD_GET_PHOTOS:
        parsePhotos (result);
        break;
    case CMD_GET_SMS:
        parseSms (result);
        break;
    case CMD_GET_VIDEOS:
        parseVideos (result);
        break;
    }
}

void PhoneHandler::resetVideos () {
    mutualThread->sendCommand (CMD_GET_VIDEOS, NULL);
}

void PhoneHandler::resetApps () {
    mutualThread->sendCommand (CMD_GET_APPS, NULL);
}

void PhoneHandler::resetSysApps () {
    mutualThread->sendCommand (CMD_GET_SYSAPPS, NULL);
}

void PhoneHandler::resetAddressBook () {
    mutualThread->sendCommand (CMD_GET_ADDRESSBOOK, NULL);
}

void PhoneHandler::resetCallLog () {
    mutualThread->sendCommand (CMD_GET_CALL_LOG, NULL);
}

void PhoneHandler::resetFileList (QString path) {
    mutualThread->sendCommand (CMD_GET_FILELIST, path);
}

void PhoneHandler::resetSms () {
    mutualThread->sendCommand (CMD_GET_SMS, NULL);
}

void PhoneHandler::resetAudios () {
    mutualThread->sendCommand (CMD_GET_AUDIOS, NULL);
}

void PhoneHandler::resetPhotos () {
    mutualThread->sendCommand (CMD_GET_PHOTOS, NULL);
}


void PhoneHandler::parseApps (QString result) {
    listApps.clear ();

    QXmlStreamReader * reader = new QXmlStreamReader(result);
    while(!reader->atEnd() && !reader->hasError()) {
         QXmlStreamReader::TokenType token = reader->readNext();
         if(token == QXmlStreamReader::StartDocument) {
             continue;
         }

         if (reader->isStartElement() && reader->name() == "app") {
            listApps.append (new HAppObject);
         } else if (reader->isStartElement() && reader->name() == "location") {
             QString location = reader->readElementText();
             listApps.last ()->location = location=="0"?"手机卡":"SD卡";
         } else if (reader->isStartElement() && reader->name() == "type") {
             listApps.last ()->type = reader->readElementText();
         } else if (reader->isStartElement() && reader->name() == "name") {
             listApps.last ()->name = reader->readElementText();
         } else if (reader->isStartElement() && reader->name() == "package") {
             listApps.last ()->package = reader->readElementText();
         } else if (reader->isStartElement() && reader->name() == "version") {
             listApps.last ()->version = reader->readElementText();
         } else if (reader->isStartElement() && reader->name() == "versionCode") {
             listApps.last ()->versionCode = reader->readElementText();
         }
     }

    emit onAppsChanged ();
}

void PhoneHandler::parseSysApps (QString result) {
    listSysApps.clear ();

    QXmlStreamReader * reader = new QXmlStreamReader(result);
    while(!reader->atEnd() && !reader->hasError()) {
         QXmlStreamReader::TokenType token = reader->readNext();
         if(token == QXmlStreamReader::StartDocument) {
             continue;
         }

         if (reader->isStartElement() && reader->name() == "app") {
            listSysApps.append (new HAppObject);
         } else if (reader->isStartElement() && reader->name() == "location") {
             QString location = reader->readElementText();
             listSysApps.last ()->location = location=="0"?"手机卡":"SD卡";
         } else if (reader->isStartElement() && reader->name() == "type") {
             listSysApps.last ()->type = reader->readElementText();
         } else if (reader->isStartElement() && reader->name() == "name") {
             listSysApps.last ()->name = reader->readElementText();
         } else if (reader->isStartElement() && reader->name() == "package") {
             listSysApps.last ()->package = reader->readElementText();
         } else if (reader->isStartElement() && reader->name() == "version") {
             listSysApps.last ()->version = reader->readElementText();
         } else if (reader->isStartElement() && reader->name() == "versionCode") {
             listSysApps.last ()->versionCode = reader->readElementText();
         }
     }

    emit onSysAppsChanged ();
}

void PhoneHandler::parseVideos (QString result) {
    listVideos.clear ();

    qDebug () << "into listVideos";
    QXmlStreamReader * reader = new QXmlStreamReader(result);
    while(!reader->atEnd() && !reader->hasError()) {
         QXmlStreamReader::TokenType token = reader->readNext();
         if(token == QXmlStreamReader::StartDocument ||
                 !reader->isStartElement()) {
             qDebug () << "continue";
             continue;
         }
         if (reader->isStartElement() && reader->name() == "video") {
            listVideos.append (new HVideoObject);
         } else if (reader->isStartElement() && reader->name() == "title") {
             listVideos.last ()->name = reader->readElementText();
         } else if (reader->isStartElement() && reader->name() == "path") {
             listVideos.last ()->path = reader->readElementText();
         } else if (reader->isStartElement() && reader->name() == "size") {
             listVideos.last ()->size = reader->readElementText()+"M";
         }
     }
    qDebug () << "end listVideos";

    emit onVideosChanged ();
}

void PhoneHandler::parseAudios (QString result) {
    listAudio.clear ();

    qDebug () << "into parseAudios";
    QXmlStreamReader * reader = new QXmlStreamReader(result);
    while(!reader->atEnd() && !reader->hasError()) {
         QXmlStreamReader::TokenType token = reader->readNext();
         if(token == QXmlStreamReader::StartDocument ||
                 !reader->isStartElement()) {
             qDebug () << "continue";
             continue;
         }
         if (reader->isStartElement() && reader->name() == "audio") {
            listAudio.append (new HAudioObject);
         } else if (reader->isStartElement() && reader->name() == "title") {
             listAudio.last ()->name = reader->readElementText();
         } else if (reader->isStartElement() && reader->name() == "path") {
             listAudio.last ()->path = reader->readElementText();
         } else if (reader->isStartElement() && reader->name() == "size") {
             listAudio.last ()->size = reader->readElementText()+"M";
         }
     }
    qDebug () << "end parseAudios";

    emit onAudiosChanged ();
}

void PhoneHandler::parseAddressBook (QString result) {
    listAddresss.clear ();

    qDebug () << "into parseAddressBook";
    QXmlStreamReader * reader = new QXmlStreamReader(result);
    while(!reader->atEnd() && !reader->hasError()) {
         QXmlStreamReader::TokenType token = reader->readNext();
         if(token == QXmlStreamReader::StartDocument) {
             qDebug () << "continue";
             continue;
         }
         if (reader->isStartElement() && reader->name() == "Phone") {
            listAddresss.append (new HAddressObject);
         } else if (reader->isStartElement() && reader->name() == "name") {
             QString name = reader->readElementText();
             qDebug () << "app.name = " << name;
             listAddresss.last ()->name = name;
         } else if (reader->isStartElement() && reader->name() == "number") {
             QString number = reader->readElementText();
             qDebug () << "app.number = " << number;
             listAddresss.last ()->phone = number;
         }
     }
    qDebug () << "end parseAddressBook";

    emit onAddressBookChanged ();
}

void PhoneHandler::parseSms (QString result) {
    listSms.clear ();
    QVector<HSmsObject *> list;

    qDebug () << "into parseSms";
    QXmlStreamReader * reader = new QXmlStreamReader(result);
    while(!reader->atEnd() && !reader->hasError()) {
         QXmlStreamReader::TokenType token = reader->readNext();
         if(token == QXmlStreamReader::StartDocument ||
                 !reader->isStartElement()) {
             qDebug () << "continue";
             continue;
         }
         if (reader->isStartElement() && reader->name() == "sms") {
            list.append (new HSmsObject);
         } else if (reader->isStartElement() && reader->name() == "name") {
             list.last ()->name = reader->readElementText();
         } else if (reader->isStartElement() && reader->name() == "phoneNumber") {
             list.last ()->phone = reader->readElementText();
         } else if (reader->isStartElement() && reader->name() == "smsbody") {
             list.last ()->body = reader->readElementText();
         } else if (reader->isStartElement() && reader->name() == "date") {
             list.last ()->date = reader->readElementText();
         } else if (reader->isStartElement() && reader->name() == "type") {
             list.last ()->type = reader->readElementText();
         }
     }
    groupSms (list);
    qDebug () << "end parseSms";

    emit onSmsChanged ();
}

HSmsObject* PhoneHandler::exsitSms (HSmsObject * obj) {
    for (int i = 0; i < listSms.size (); i++) {
        HSmsObject * sms = listSms.at (i);

        if (sms->phone == obj->phone) {
            return sms;
        }
    }

    return NULL;
}
//
void PhoneHandler::groupSms (QVector<HSmsObject *> list) {
    for (int i = 0; i < list.size (); i++) {
        HSmsObject * sms = list.at (i);

        HSmsObject* old = exsitSms (sms);
        if (old) {
            old->subSms.append (sms);
        } else {
            HSmsObject * so = new HSmsObject;
            so->phone = sms->phone;
            so->subSms.append (sms);

            listSms.append (so);
        }
    }
}

void PhoneHandler::parseFileList (QString result) {
}

void PhoneHandler::parseCallLog (QString result) {
    listCalls.clear ();

    qDebug () << "into parseCallLog";
    QXmlStreamReader * reader = new QXmlStreamReader(result);
    while(!reader->atEnd() && !reader->hasError()) {
         QXmlStreamReader::TokenType token = reader->readNext();
         if(token == QXmlStreamReader::StartDocument ||
                 !reader->isStartElement()) {
             qDebug () << "continue";
             continue;
         }
         if (reader->isStartElement() && reader->name() == "PhoneRecord") {
            listCalls.append (new HCallObject);
         } else if (reader->isStartElement() && reader->name() == "phone") {
             listCalls.last ()->phone = reader->readElementText();
         } else if (reader->isStartElement() && reader->name() == "date") {
             listCalls.last ()->date = reader->readElementText();
         } else if (reader->isStartElement() && reader->name() == "duration") {
             listCalls.last ()->duration = reader->readElementText();
         } else if (reader->isStartElement() && reader->name() == "type") {
             listCalls.last ()->type = reader->readElementText();
         }
     }
    qDebug () << "end parseCallLog";

    emit onCallLogsChanged ();
}

void PhoneHandler::parsePhotos (QString result) {
    listPhotos.clear ();

    qDebug () << "into parsePhotos";
    QXmlStreamReader * reader = new QXmlStreamReader(result);
    while(!reader->atEnd() && !reader->hasError()) {
         QXmlStreamReader::TokenType token = reader->readNext();
         if(token == QXmlStreamReader::StartDocument ||
                 !reader->isStartElement()) {
             qDebug () << "continue";
             continue;
         }
         if (reader->isStartElement() && reader->name() == "photo") {
            listPhotos.append (new HPhotoObject);
         } else if (reader->isStartElement() && reader->name() == "title") {
             listPhotos.last ()->name = reader->readElementText();
         } else if (reader->isStartElement() && reader->name() == "path") {
             listPhotos.last ()->path = reader->readElementText();
         } else if (reader->isStartElement() && reader->name() == "mime_type") {
             listPhotos.last ()->mime_type = reader->readElementText();
         } else if (reader->isStartElement() && reader->name() == "size") {
             listPhotos.last ()->size = reader->readElementText()+"M";
         }
     }
    qDebug () << "end parsePhotos";

    emit onPhotosChanged ();
}

void PhoneHandler::install (QString path) {
    mutualThread->commandNoResult (QString(mutualThread->adbPath () + " install -r %1").arg (path));
    qDebug () << "";
}

void PhoneHandler::uninstall (QString package) {
    mutualThread->commandNoResult (QString(mutualThread->adbPath () + " shell pm uninstall -k %1").arg (package));
}
