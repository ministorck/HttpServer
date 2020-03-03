#ifndef STCPSERVERFORM_H
#define STCPSERVERFORM_H
#include <QTcpServer>
#include "../TaskTypeBase.h"
#include "STcpServer.h"
#include "../TaskQueue.h"

/**
 * @brief The STcpServerForm class 监听接入的ＴＣＰ
 *
 * 当接收到ＴＣＰ连接时创建socket,并放入任务队列中，并唤醒线程来处理新任务
 */
class STcpServerForm :public TaskTypeBase
{
public:
    STcpServerForm(TaskQueue* taskque,const ushort& port,QObject* parent = Q_NULLPTR);
    ~STcpServerForm();
protected:
    void working(QThread* thread);

    //当打开消息循环时，才用该函数
    void workEnd(QThread* thread);

private:
    STcpServer* s_tcpServer;
    TaskQueue* s_taskQueue;

    ushort s_tcpPort;


};

#endif // STCPSERVERFORM_H
