#include "ClientDataRecoder.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "globaldata.h"
#include "utils/URLEncodeUtil.h"
#include "TaskManager/TCP/STcpSocketClient.h"

ClientDataRecoder::ClientDataRecoder(QObject *parent) : QObject(parent)
{
    s_threadPool = TaskManager::GetInstance()->getThreadPool();
    connect(s_threadPool,SIGNAL(sig_poolfullData(QByteArray,TaskTypeBase *)),this,SLOT(slot_poolClientInfo(QByteArray,TaskTypeBase *)));
}

ClientDataRecoder::~ClientDataRecoder()
{

}

void ClientDataRecoder::slot_poolClientInfo(QByteArray info, TaskTypeBase *manager)
{
    QString str(info);
    QStringList list = str.split("\r\n");
    if(list.size()<=2)
        return;

    QString line1 = list.first();
    QStringList line1s = line1.split(" ");
    QString type,url,http;
    if(line1s.size() <= 3)
    {
        type = line1s.first();
        url = line1s.at(1);
        http = line1s.at(2);
    }
    if(!processRequest(manager,type,url))
    {
        s_printLog->writeLog(QString("handle http request error, from: %1")
                             .arg(static_cast<STcpSocketClient *>(manager)->GetTcpSocket()->localPort()));
    }
}

bool ClientDataRecoder::processRequest(TaskTypeBase *manager, QString type, QString url)
{
    if(url.isEmpty())
        return false;
    bool b = false;
    if(url == "/api/import-devices")
    {
        b = processapi(manager,type);
    }
    else
        return false;
    return b;
}

bool ClientDataRecoder::processapi(TaskTypeBase *manager, QString type)
{
    QString resigData;
    QJsonObject obj;
    obj.insert("id",QJsonValue("1"));
    obj.insert("device-id",QJsonValue("8001"));
    obj.insert("press",QJsonValue("100"));
    obj.insert("velocity",QJsonValue("1000"));
    QJsonArray array;
    array.append(QJsonValue(obj));
    QJsonObject obj2;
    obj2.insert("pump",QJsonValue(array));
    QJsonObject obj3;
    obj3.insert("data",QJsonValue(obj2));
    QJsonDocument document;
    document.setObject(obj3);
    QByteArray byte = document.toJson(QJsonDocument::Compact);
    QString retData(byte);
    if(retData.isEmpty())
        return false;
    makeResponse(retData,resigData);
    static_cast<STcpSocketClient *>(manager)->writeData(resigData.toLatin1());
    return false;
}

bool ClientDataRecoder::makeResponse(QString &inPut, QString &outPut)
{
    outPut.append( "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length:");
    outPut.append(inPut.length());
    outPut.append("\r\n\r\n");
    outPut.append(inPut);
    return true;
}
