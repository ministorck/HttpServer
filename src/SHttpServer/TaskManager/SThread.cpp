#include "SThread.h"
#include "globaldata.h"

SThread::SThread(int n,TaskQueue* taskQueue,QObject* parent):QThread(parent)
{
    QString strLog;
    strLog.sprintf("创建线程类！%d,%p",n,this);
    s_printLog->writeLog(strLog);
    s_threadStatus.s_id = this;
    s_bThrStatus = false;
    s_threadNum = n;
    s_taskQueue = taskQueue;
    s_isRun = true;
    s_taskTypeBase = Q_NULLPTR;
    start();
}

SThread::~SThread()
{
    wait();
    if(Q_NULLPTR != s_taskTypeBase)
    {
        delete s_taskTypeBase;
    }
    s_taskTypeBase = Q_NULLPTR;
    QString strLog = QString("删除线程类！%1").arg(s_threadNum);
    s_printLog->writeLog(strLog);
}

void SThread::stopnThread()
{//停止线程
    s_isRun = false;
    if(Q_NULLPTR != s_taskTypeBase)
        s_taskTypeBase->stopWork();

}

const ThreadModelStruct &SThread::getThreadState()
{
    s_threadStatus.s_state = s_bThrStatus;
    s_threadStatus.s_explain.clear();
    if(Q_NULLPTR != s_taskTypeBase)
        s_threadStatus.s_explain = s_taskTypeBase->s_taskName;
    return s_threadStatus;
}

void SThread::run()
{
    while(s_isRun)
    {
        s_taskTypeBase = s_taskQueue->deQueueTask();
        if(s_taskTypeBase != Q_NULLPTR)
        {
            connect(s_taskTypeBase,SIGNAL(sig_fullData(QByteArray)),this,SIGNAL(sig_fullData(QByteArray)));
            connect(s_taskTypeBase,SIGNAL(sig_ClientInfo(QString)),this,SIGNAL(sig_strClientInfo(QString)));
            s_printLog->writeLog("获取到任务");
            s_bThrStatus = true;
            //获取到新任务后发送消息,更新线程管理界面
            emit sig_updateState(this,SAction_Update);
            s_taskTypeBase->working(this);
            if(s_taskTypeBase->s_isLoop)
            {
                this->exec();
                s_taskTypeBase->workEnd(this);
            }
            disconnect(s_taskTypeBase,SIGNAL(sig_ClientInfo(QString)),this,SIGNAL(sig_strClientInfo(QString)));
            delete s_taskTypeBase;
            s_bThrStatus = false;
            emit sig_updateState(this,SAction_Update);
        }
        else
        {
            s_printLog->writeLog("未获取到任务");
        }
        s_taskTypeBase = Q_NULLPTR;
    }
}
