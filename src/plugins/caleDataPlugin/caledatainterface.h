#ifndef CALEDATAINTERFACE_H
#define CALEDATAINTERFACE_H


#include "plugininterface.h"

class CaleDataInterface:public PluginInterface
{
public:
    virtual ~CaleDataInterface() {}

    virtual int addValue(int i1,int i2) = 0;
};


#endif // CALEDATAINTERFACE_H
