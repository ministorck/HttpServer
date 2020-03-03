#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "TaskQueue.h"
#include "SThreadPool.h"
#include <QObject>
#include "TCP/STcpServerForm.h"

class TaskManager : public QObject
{
    Q_OBJECT
public:
    static TaskManager *GetInstance();
    void release();
    SThreadPool* getThreadPool();
public slots:
    /**
     * @brief slot_changeTcpPort
     * @param port
     *
     * 接收到TCP端口改变后，停止原监听任务，重新创建TCP监听任务
     */
    void slot_changeTcpPort(const ushort port);

private:
    TaskManager(QObject * prent = Q_NULLPTR);
    ~TaskManager();
    void init();

private:
    static QMutex m_mutex;
    static TaskManager *m_instance;
    //任务队列
    TaskQueue *s_taskQueue;
    //线程池
    SThreadPool *s_threadPool;

    STcpServerForm* s_tcpServerFrom;

    ushort s_tcpPort;
};

#endif // TASKMANAGER_H
