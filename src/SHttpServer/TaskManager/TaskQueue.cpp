#include "TaskQueue.h"
#include "globaldata.h"

TaskQueue::TaskQueue()
{
    s_waitCondition = new QWaitCondition();
}

TaskQueue::~TaskQueue()
{
    s_printLog->writeLog("删除任务队列!");
    //清空未处理的任务
    while(!s_allTaskQueue.isEmpty())
        delete s_allTaskQueue.dequeue();
    if(s_waitCondition)
        delete s_waitCondition;
    s_waitCondition = nullptr;
}

void TaskQueue::enQueueTask(TaskTypeBase *task)
{
    s_mutex.lock();
    s_printLog->writeLog("添加任务");
    if(task != NULL)
        s_allTaskQueue.enqueue(task);
    s_waitCondition->wakeOne();
    s_mutex.unlock();
}

TaskTypeBase *TaskQueue::deQueueTask()
{
    s_mutex.lock();
    s_waitCondition->wait(&s_mutex);
    TaskTypeBase* base;
    if(s_allTaskQueue.isEmpty())
        base = Q_NULLPTR;
    else
        base = s_allTaskQueue.dequeue();
    s_mutex.unlock();
    return base;
}

void TaskQueue::stopThread()
{
    s_mutex.lock();
    s_waitCondition->wakeAll();
    s_mutex.unlock();
}
