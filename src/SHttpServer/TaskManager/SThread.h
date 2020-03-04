#ifndef STHREAD_H
#define STHREAD_H
#include <QThread>
#include "TaskQueue.h"
#include "TaskTypeBase.h"
#include "../PublicStruct.h"

class SThread : public QThread
{
    Q_OBJECT
public:
    SThread(int n,TaskQueue* taskQueue,QObject* parent = Q_NULLPTR);
    ~SThread();

    void stopnThread();

    const ThreadModelStruct& getThreadState();
signals:

    /**
     * @brief sig_updateState
     * @param id
     * @param action
     * 线程状态改变时发送
     */
    void sig_updateState(void* id,SAction action);

    void sig_fullData(QByteArray data,TaskTypeBase *monitor);

    void sig_strClientInfo(QString info);

private:
    void run();

private:
    bool s_isRun;
    TaskQueue* s_taskQueue;
    TaskTypeBase* s_taskTypeBase;
    //线程编号
    int s_threadNum;
    //线程状态
    bool s_bThrStatus;
    //线程运行情况
    ThreadModelStruct s_threadStatus;
};

#endif // STHREAD_H
