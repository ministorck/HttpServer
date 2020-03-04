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
    void slot_poolClientInfo(QByteArray info,TaskTypeBase *manager);
private:
    bool processRequest(TaskTypeBase *manager,QString type,QString url);
    bool processapi(TaskTypeBase *manager,QString type);
    bool makeResponse(QString &inPut,QString &outPut);
private:
    //线程池
    SThreadPool *s_threadPool;
};

#endif // CLIENTDATARECODER_H
