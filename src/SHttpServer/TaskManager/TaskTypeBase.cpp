#include "TaskTypeBase.h"


TaskTypeBase::TaskTypeBase(QObject* parent):QObject(parent),s_taskName("新任务"),s_isRun(true),s_isLoop(false),
    s_thread(Q_NULLPTR)
{

}

TaskTypeBase::~TaskTypeBase()
{

}

void TaskTypeBase::stopWork()
{
    //线程中开启消息循环时，该参数无效
    s_isRun = false;
    s_isLoop = false;
    //线程开启消息循环时，有效。
    if(Q_NULLPTR != s_thread)
        s_thread->quit();
}

void TaskTypeBase::workEnd(QThread *thread)
{
    thread->wait(0);
}

void TaskTypeBase::openLoop()
{
    s_isLoop = true;
}
