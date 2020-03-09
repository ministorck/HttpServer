#ifndef RESPONSELOCALDATAINTERFACE_H
#define RESPONSELOCALDATAINTERFACE_H
#include "plugininterface.h"

class ResponseLocalDataInterface:public PluginInterface
{
public:
    virtual ~ResponseLocalDataInterface() {}

    virtual bool openLocalFile(QString path) = 0;
    virtual bool readCurData(QByteArray &byte) = 0;

protected:
    QString m_localPath;
};

#endif // RESPONSELOCALDATAINTERFACE_H
