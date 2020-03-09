#ifndef DATABASEINTERFACE_H
#define DATABASEINTERFACE_H

#include "plugininterface.h"

enum Method_
{
    Method_Error,
    Method_Get,
    Method_Put,
    Method_Post,
    Method_Patch,
    Method_Delete
};

class DatabaseInterface:public PluginInterface
{
public:
    virtual ~DatabaseInterface() {}
    virtual void insert(QString)=0;
    virtual QByteArray responseData(QByteArray byte)=0;
    virtual bool analyzingData(QByteArray byte) = 0;
    virtual Method_ GetMethod() = 0;
    virtual QString GetUrl() = 0;
    virtual QString GetRequestData()=0;
    virtual QByteArray GetResPonseData(QByteArray data)=0;
};

#endif // DATABASEINTERFACE_H
