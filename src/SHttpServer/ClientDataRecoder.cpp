#include "ClientDataRecoder.h"
#include <QDebug>
#include "Http.h"
ClientDataRecoder::ClientDataRecoder(QObject *parent) : QObject(parent)
{
    s_threadPool = TaskManager::GetInstance()->getThreadPool();
    connect(s_threadPool,SIGNAL(sig_poolfullData(QByteArray)),this,SLOT(slot_poolClientInfo(QByteArray)));
}

ClientDataRecoder::~ClientDataRecoder()
{

}

void ClientDataRecoder::slot_poolClientInfo(QByteArray info)
{
    Http::Post(info);
}
