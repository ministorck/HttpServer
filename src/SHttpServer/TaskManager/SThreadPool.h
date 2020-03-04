#ifndef STHREADPOOL_H
#define STHREADPOOL_H
#include "TaskQueue.h"
#include "SThread.h"
#include <QMap>
#include <QObject>
#include "PublicStruct.h"
#include "../PublicStruct.h"

typedef QMap<void*,SThread*> AllThread;


class SThreadPool:public QObject
{
    Q_OBJECT
public:
    SThreadPool(TaskQueue* task,QObject* parent = Q_NULLPTR);
    ~SThreadPool();

    void sendAllThreadState();

signals:
    void sig_ThreadState(const ThreadModelStruct,const SAction);

    void sig_poolfullData(QByteArray data,TaskTypeBase *monitor);

    void sig_poolClientInfo(QString info);

private slots:
    void slot_updateSthread(void* thread_id,SAction action);
private:
    TaskQueue *s_taskQueue;
    AllThread s_allThread;
};

#endif // STHREADPOOL_H
