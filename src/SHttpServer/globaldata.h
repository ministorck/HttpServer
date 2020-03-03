#ifndef GLOBALDATA_H
#define GLOBALDATA_H


#include "SPrintLog.h"

extern SPrintLog *s_printLog;

enum ErrorCode
{
    NetworkException,
    Success,
};

struct BookInfo
{
    int keyid;
    QString type;
};


#endif // GLOBALDATA_H
