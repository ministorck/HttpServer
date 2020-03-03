#include "STcpServerForm.h"
#include "globaldata.h"


STcpServerForm::STcpServerForm(TaskQueue* taskque,const ushort& port,QObject* parent):TaskTypeBase(parent)
{
    s_taskName =  QString("TCP监听任务,监听端口： %1").arg(port);
    s_printLog->writeLog(s_taskName);
    s_taskQueue = taskque;
    s_tcpPort = port;
}

STcpServerForm::~STcpServerForm()
{
    s_printLog->writeLog("删除TCP监听类");
}

void STcpServerForm::working(QThread *thread)
{

    s_tcpServer = new STcpServer(s_taskQueue,thread->parent());
    if(s_tcpServer->listen(QHostAddress::Any,s_tcpPort))
    {
        s_thread = thread;

    //打消息循环
        openLoop();
    }
    else
    {
        s_printLog->writeLog("ＴＣＰ监听失败！");
        s_tcpServer->close();
        delete s_tcpServer;
    }
}

void STcpServerForm::workEnd(QThread *thread)
{
    s_tcpServer->close();
    delete s_tcpServer;
    s_tcpServer = Q_NULLPTR;
}

