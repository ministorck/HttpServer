#ifndef STCPSERVER_H
#define STCPSERVER_H

#include <QTcpServer>
#include "../TaskQueue.h"

/**
 * @brief The STcpServer class
 * 重写TCP实现监听功能
 */
class STcpServer:public QTcpServer
{
public:
    STcpServer(TaskQueue* taskQue,QObject* parent = Q_NULLPTR);

protected:
    void incomingConnection(qintptr handle);

    TaskQueue* s_taskQueue;

};

#endif // STCPSERVER_H
