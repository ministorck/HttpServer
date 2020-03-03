#ifndef TASKQUEUE_H
#define TASKQUEUE_H
#include <QQueue>
#include "TaskTypeBase.h"
#include <QMutex>
#include <QWaitCondition>

typedef QQueue<TaskTypeBase*> AllTaskQueue;
/**
 * @brief The TaskQueue class
 * @date 20190824
 * 任务队列
 */
class TaskQueue
{
public:
    TaskQueue();
    ~TaskQueue();

    void enQueueTask(TaskTypeBase* task);

    TaskTypeBase* deQueueTask();

    void stopThread();

private:
    QMutex s_mutex;
    AllTaskQueue s_allTaskQueue;
    QWaitCondition *s_waitCondition;
};

#endif // TASKQUEUE_H
