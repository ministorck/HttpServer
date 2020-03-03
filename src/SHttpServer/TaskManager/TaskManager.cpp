#include "TaskManager.h"
#include <QMutex>
TaskManager *TaskManager::m_instance = NULL;
QMutex TaskManager::m_mutex;
TaskManager::TaskManager(QObject * prent):QObject(prent)
{
    //注册新类型，接收线程状态
    qRegisterMetaType<ThreadModelStruct>("ThreadModelStruct");
    qRegisterMetaType<SAction>("SAction");
    s_tcpPort = 0;
    s_tcpServerFrom = Q_NULLPTR;
    init();
}

TaskManager::~TaskManager()
{
    delete s_threadPool;
    s_threadPool = Q_NULLPTR;

    delete s_taskQueue;
    s_taskQueue = Q_NULLPTR;

}

TaskManager *TaskManager::GetInstance()
{
    if(m_instance == NULL)
    {
        QMutexLocker lock(&m_mutex);
        if(m_instance == NULL)
        {
            m_instance = new TaskManager;
        }
    }
    return m_instance;
}

void TaskManager::release()
{
    if(m_instance != NULL)
    {
        delete m_instance;
        m_instance = NULL;
    }
}

SThreadPool *TaskManager::getThreadPool()
{
    return s_threadPool;
}


void TaskManager::slot_changeTcpPort(const ushort port)
{
    if(port == 0)
        return;
    s_tcpPort = port;
    //结束原任务，原任务对象在线程中被删除
    if(Q_NULLPTR != s_tcpServerFrom)
    {
        s_tcpServerFrom->stopWork();
    }
        //创建新任务，放入任务队列中
    s_tcpServerFrom = new STcpServerForm(s_taskQueue,s_tcpPort);
    s_taskQueue->enQueueTask(s_tcpServerFrom);
}

void TaskManager::init()
{
    //创建任务队列
    s_taskQueue = new TaskQueue();
    //创建线程池，从任务队列中读取任务
    s_threadPool = new SThreadPool(s_taskQueue);
    //ＴＣＰ监听任务

}
