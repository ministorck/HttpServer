#ifndef STCPSOCKETCLIENT_H
#define STCPSOCKETCLIENT_H
#include "../TaskTypeBase.h"
#include <QTcpSocket>
#include <QObject>

class STcpSocketClient : public TaskTypeBase
{
    Q_OBJECT
public:
    STcpSocketClient(qintptr handle,QObject* parent = Q_NULLPTR);
    ~STcpSocketClient();
    void writeData(QByteArray byte);
    QTcpSocket *GetTcpSocket(){if(s_tcpSocket != NULL) return s_tcpSocket;}
protected:
    void working(QThread* thread);
    void workEnd(QThread* thread);

private slots:
    void tcpReceiveClient_slots();

    void tcpDisConnected();

private:
    bool initTcpSocket(QThread* thread);

private:
    QTcpSocket* s_tcpSocket;

    qintptr s_handle;
};

#endif // STCPSOCKETCLIENT_H
