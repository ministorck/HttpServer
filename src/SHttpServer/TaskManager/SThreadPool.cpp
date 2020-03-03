#include "SThreadPool.h"

SThreadPool::SThreadPool(TaskQueue* task,QObject* parent): QObject(parent)
{
    s_taskQueue = task;

    SThread *thread;
    // 先创建10个线程
    for(int n = 0;n<10;n++)
    {
        thread =new SThread(n,s_taskQueue);
        connect(thread,SIGNAL(sig_fullData(QByteArray)),this,SIGNAL(sig_poolfullData(QByteArray)));
        connect(thread,SIGNAL(sig_strClientInfo(QString)),this,SIGNAL(sig_poolClientInfo(QString)));

        s_allThread.insert(thread,thread);
        connect(thread,SIGNAL(sig_updateState(void*,SAction)),this,SLOT(slot_updateSthread(void*,SAction)));
    }
}

SThreadPool::~SThreadPool()
{
    AllThread::iterator iter1 = s_allThread.begin();
    while(iter1 != s_allThread.end())
    {
        disconnect(iter1.value(),SIGNAL(sig_strClientInfo(QString)),this,SIGNAL(sig_poolClientInfo(QString)));
        disconnect(iter1.value(),SIGNAL(sig_updateState(void*,SAction)),this,SLOT(slot_updateSthread(void*,SAction)));
        iter1.value()->stopnThread();
        iter1++;
    }
    //唤醒所有线程，并结束线程
    s_taskQueue->stopThread();
    AllThread::iterator iter = s_allThread.begin();
    while(iter != s_allThread.end())
    {
        delete iter.value();
        iter++;
    }
    s_allThread.clear();
}

void SThreadPool::sendAllThreadState()
{
    AllThread::iterator iter = s_allThread.begin();
    while(iter != s_allThread.end())
    {
        ThreadModelStruct threadState = iter.value()->getThreadState();
        emit sig_ThreadState(threadState,SAction_Add);
        iter++;
    }
}

void SThreadPool::slot_updateSthread(void *thread_id, SAction action)
{
    AllThread::iterator iter = s_allThread.find(thread_id);
    if(iter != s_allThread.end())
    {
        ThreadModelStruct threadState = iter.value()->getThreadState();
        emit sig_ThreadState(threadState,action);
    }
}


