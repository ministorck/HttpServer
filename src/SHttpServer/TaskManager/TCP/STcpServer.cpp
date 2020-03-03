#include "STcpServer.h"
#include <QThread>
#include "STcpSocketClient.h"
#include "../../globaldata.h"

STcpServer::STcpServer(TaskQueue* taskQue,QObject* parent):QTcpServer(parent)
{
    s_taskQueue = taskQue;
}

void STcpServer::incomingConnection(qintptr handle)
{
    QString str;
    str.sprintf("%p",QThread::currentThread());
    QString strLog = QString("接收到ＴＣＰ连接！%1").arg(str);
    s_printLog->writeLog(strLog);

    STcpSocketClient* tcpSocket = new STcpSocketClient(handle);
    s_taskQueue->enQueueTask(tcpSocket);
}
