#include "SPrintLog.h"
#include <QDebug>
#include <QMutexLocker>
#include <QDateTime>


void SPrintLog::closeLogFile()
{
    s_isRun = false;
    wait();
    if(NULL != s_pLogFile)
    {
        s_pLogFile->close();
        delete s_pLogFile;
    }
    s_pLogFile = NULL;
}

void SPrintLog::writeLog(const QString &msg)
{
    QString msgLog = QString("%1 %2\n").arg(QDateTime::currentDateTime().toString("yyyy年MM月dd日 hh:mm:ss:zzz")).arg(msg);
    qDebug()<<msgLog;
    if(NULL != s_pLogFile)
    {
        QMutexLocker lock(&s_mutex);
        s_msgQueue.enqueue(msgLog);
    }

}

void SPrintLog::openRecord()
{
    if(NULL != s_pLogFile)
        this->start();
    else
        qDebug()<<"打开日志文件失败！";
}

SPrintLog::SPrintLog(const QString& name,QObject* parent) : QThread(parent)
{
    s_isRun = true;
    QString logName = QString("../log/%1%2.txt").arg(name).arg(QDateTime::currentDateTime().toString("yyyyMMdd"));
    openLogFile(logName);

}

SPrintLog::~SPrintLog()
{

}

const QString SPrintLog::pushLog()
{
    QMutexLocker lock(&s_mutex);
    return s_msgQueue.dequeue();
}

void SPrintLog::openLogFile(const QString &name)
{
    QString msgLog;
    s_pLogFile = new QFile(name);
    if(s_pLogFile->open(QFile::WriteOnly | QFile::Append | QFile::Text))
    {
        msgLog = QString("打开文件：%1，成功！").arg(name);
        writeLog(msgLog);
    }
    else
    {
        msgLog = QString("打开文件：%1，失败！").arg(name);
        delete s_pLogFile;
        s_pLogFile = NULL;
        writeLog(msgLog);
    }

}

void SPrintLog::run()
{
    while(s_isRun || !s_msgQueue.isEmpty())
    {
        while(!s_msgQueue.isEmpty() && NULL != s_pLogFile)
        {
            QByteArray logStr = pushLog().toLocal8Bit();
            int n = s_pLogFile->write(logStr);
            s_pLogFile->flush();
        }
        sleep(5);
    }
}
