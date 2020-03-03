#ifndef CLIENTDATARECODER_H
#define CLIENTDATARECODER_H

#include <QObject>
#include "TaskManager/TaskManager.h"
/*******************************
 *
 * 处理接收到的http数据内容
 *
********************************/

class ClientDataRecoder : public QObject
{
    Q_OBJECT
public:
    explicit ClientDataRecoder(QObject *parent = 0);
    ~ClientDataRecoder();
signals:

public slots:
    void slot_poolClientInfo(QByteArray info);
private:
    //线程池
    SThreadPool *s_threadPool;
};

#endif // CLIENTDATARECODER_H
