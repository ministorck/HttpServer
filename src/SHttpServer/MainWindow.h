#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TaskManager/TaskManager.h"
#include "SThreadModel.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(TaskManager* task,QWidget *parent = 0);
    ~MainWindow();

signals:
    void sig_ChangeTcpPort(const ushort port);

private slots:
    void on_changeBtn_clicked();

    void on_showClientInfo(QString info);

private:
    void initThreadModel();

    void initHttpServer();

private:
    Ui::MainWindow *ui;

    SThreadModel* s_threadModel;

    TaskManager* s_taskManager;

    ushort s_tcpPort;
};

#endif // MAINWINDOW_H
