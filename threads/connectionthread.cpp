#include "connectionthread.h"
#include <QSettings>
#include <QTextCodec>
#include <qdebug.h>

void ConnectionThread::run()
{
	int dataLength;
	bool ok, first = true;
	int serialLength=0;
	QString data,serialNumber,tmp;

	QProcess *phone=new QProcess(this);
	QString adbpath = "./bin/adb";
	QString command;
	command = adbpath + " start-server";
	phone->start(command);

    qDebug () << "run111";
	this->socket = new QTcpSocket();
	this->socket->connectToHost("127.0.0.1",5037,QTcpSocket::ReadWrite);
	if (this->socket->waitForConnected(2000))
	{
        qDebug () << "run222";


		this->socket->write("0012host:track-devices");
		this->socket->waitForReadyRead(2000);
		data = this->socket->read(4);
		if (data == "OKAY")
		{

            qDebug() << data;
			while (true)
			{
			
				qDebug() << "int connect while";
				if (!first)
					this->socket->waitForReadyRead(-1);
				first = false;

				data = this->socket->read(4);
				tmp=data;
				if (data == "")
					continue;
				dataLength = data.toInt(&ok, 16);
				if (dataLength == 0)
				{
					emit this->connectionChanged(FASTBOOT,"");
				}
				else
				{
					data = this->socket->read(dataLength);

					if (data.contains("device"))
						serialLength = tmp.toInt(&ok, 16) - 8;
					if (data.contains("recovery"))
						serialLength = tmp.toInt(&ok, 16) - 10;

					serialNumber = data;

					qDebug() << "connect ::" <<  data;

					serialNumber = serialNumber.left(serialLength);
					if (data.contains("device"))
						emit this->connectionChanged(DEVICE,serialNumber);
					if (data.contains("recovery"))
						emit this->connectionChanged(RECOVERY,serialNumber);
					if (data.contains("offline"))
						emit this->connectionChanged(FASTBOOT,serialNumber);
				}
			}
		}
		else
		{
            qDebug () << "run3333";

			emit this->connectionChanged(-1,"");
			return;
		}
	}
	else
	{
        qDebug () << "run444";

		emit this->connectionChanged(-1,"");
		return;
	}

    qDebug () << "run555";

}
