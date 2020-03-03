#include "MainWindow.h"
#include <QApplication>
#include "globaldata.h"
#include "TaskManager/TaskManager.h"


int main(int argc, char *argv[])
{
    //打开日志记录功能
    s_printLog->openRecord();
    s_printLog->writeLog("服务器启动！");
    QApplication a(argc, argv);
    TaskManager* task = TaskManager::GetInstance();
    MainWindow *w = new MainWindow(task);
    w->show();

    int v = a.exec();

    delete w;
    task->release();
    s_printLog->writeLog("服务器关闭！\n\n");
    //关闭日志记录
    s_printLog->closeLogFile();
    delete s_printLog;

    return v;
}
