#include "STcpSocketClient.h"
#include "globaldata.h"

STcpSocketClient::STcpSocketClient(qintptr handle,QObject* parent): TaskTypeBase(parent)
{
    s_handle = handle;
    s_taskName = "与客户端通信";
}

STcpSocketClient::~STcpSocketClient()
{

}

void STcpSocketClient::working(QThread *thread)
{
    if(initTcpSocket(thread))
    {
        QByteArray data("服务器");
        int l = s_tcpSocket->write(data);
        QString strLog = QString("写入长度：%1").arg(QString::number(l));
        s_printLog->writeLog(strLog);

        //打开消息循环
        openLoop();
    }
}

void STcpSocketClient::workEnd(QThread *thread)
{
    if(Q_NULLPTR != s_tcpSocket)
    {
        disconnect(s_tcpSocket,SIGNAL(readyRead()),this,SLOT(tcpReceiveClient_slots()));
        disconnect(s_tcpSocket,SIGNAL(disconnected()),this,SLOT(tcpDisConnected()));
        s_tcpSocket->close();
        delete s_tcpSocket;
    }
    s_tcpSocket = Q_NULLPTR;
}

void STcpSocketClient::tcpReceiveClient_slots()
{
    while(s_tcpSocket->bytesAvailable() > 0)
    {
        QByteArray data = s_tcpSocket->readAll();
        // 处理消息
        emit sig_fullData(data);
        QString str(data);
        s_printLog->writeLog(str);
        QString info;
        info.sprintf("线程：%p收到消息：",s_thread);
        info += str;
        emit sig_ClientInfo(info);
    }
}

void STcpSocketClient::tcpDisConnected()
{
    stopWork();
}

bool STcpSocketClient::initTcpSocket(QThread *thread)
{
    QString strLog;
    s_thread = thread;
    s_tcpSocket = new QTcpSocket(thread->parent());
    if(s_tcpSocket->setSocketDescriptor(s_handle))
    {
        connect(s_tcpSocket,SIGNAL(readyRead()),this,SLOT(tcpReceiveClient_slots()));
        connect(s_tcpSocket,SIGNAL(disconnected()),this,SLOT(tcpDisConnected()));
        s_printLog->writeLog( "TcpSocket创建成功！");
        return true;
    }
    else
    {
        delete s_tcpSocket;
        s_tcpSocket = Q_NULLPTR;
        s_printLog->writeLog("TcpSocket创建失败！");
        return false;
    }
}
