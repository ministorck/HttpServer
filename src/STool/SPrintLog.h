#ifndef SPRINTLOG_H
#define SPRINTLOG_H

#include <QThread>
#include <QQueue>
#include <QMutex>
#include "stool_global.h"
#include <QFile>


/**
 * @brief The SPrintLog class
 * 打印输出和写日志
 */
class STOOLSHARED_EXPORT SPrintLog : public QThread
{

public:
    SPrintLog(const QString& name, QObject* parent = Q_NULLPTR);
    ~SPrintLog();

    /**
     * @brief closeLogFile
     * 程序结束时调用
     */
    void closeLogFile();
    void writeLog(const QString& msg);

    /**
     * @brief openRecord
     * 开始记录
     */
    void openRecord();
private:


    const QString pushLog();

    void openLogFile(const QString& name);

protected:
    void run();

private:
    QQueue<QString> s_msgQueue;
    QMutex s_mutex;

    bool s_isRun;
    QFile *s_pLogFile;
};

#endif // SPRINTLOG_H
