#ifndef TASKTYPEBASE_H
#define TASKTYPEBASE_H
#include <QString>
#include <QThread>
#include <QObject>

class SThread;

class TaskTypeBase: public QObject
{
    Q_OBJECT
public:
    TaskTypeBase(QObject* parent = Q_NULLPTR);
    virtual ~TaskTypeBase();
    void stopWork();

    friend class SThread;

signals:
    void sig_ClientInfo(QString info);

protected:
    /**
     * @brief working 在线程中要做的工作
     * @param thread
     */

    virtual void working(QThread* thread) = 0;

    /**
     * @brief workEnd 事件循环结束后收尾工作
     * @param thread
     */
    virtual void workEnd(QThread* thread);

    /**
     * @brief openLoop 打开事件循环
     */
    void openLoop();

protected:
    QString s_taskName;
    bool s_isRun;
    //是否开启事件处理
    bool s_isLoop;

    //本任务所在线程
    QThread* s_thread;
};

#endif // TASKTYPEBASE_H
