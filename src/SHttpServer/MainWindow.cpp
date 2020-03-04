#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>
#include "globaldata.h"

MainWindow::MainWindow(TaskManager* task,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    s_taskManager = task;
    s_tcpPort = ui->curPort->value();
    initThreadModel();
    initHttpServer();
    s_printLog->writeLog("创建窗口");
    //开启TCP监听任务
    s_taskManager->slot_changeTcpPort(s_tcpPort);
    //发送TCP监听端口改变消息
    connect(this,SIGNAL(sig_ChangeTcpPort(ushort)),s_taskManager,SLOT(slot_changeTcpPort(ushort)));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete s_threadModel;
    disconnect(s_taskManager->getThreadPool(),SIGNAL(sig_poolClientInfo(QString)),this,SLOT(on_showClientInfo(QString)));

    disconnect(this,SIGNAL(sig_ChangeTcpPort(ushort)),s_taskManager,SLOT(slot_changeTcpPort(ushort)));
}

void MainWindow::on_changeBtn_clicked()
{
    if(s_tcpPort != ui->curPort->value())
        if(QMessageBox::Ok == QMessageBox::information(this,"修改TCP端口","确定要修改吗？",QMessageBox::Ok | QMessageBox::Cancel,QMessageBox::Cancel))
        {
            s_tcpPort = ui->curPort->value();
            emit sig_ChangeTcpPort(s_tcpPort);
        }
}

void MainWindow::on_showClientInfo(QString info)
{
    ui->clientInfo->append(info);
}

void MainWindow::initThreadModel()
{
    s_threadModel = new SThreadModel;
    ui->threadStatus->setModel(s_threadModel);
    //填充整个屏幕
    ui->threadStatus->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(s_taskManager->getThreadPool(),SIGNAL(sig_poolClientInfo(QString)),this,SLOT(on_showClientInfo(QString)));
    //接收线程更新消息
    connect(s_taskManager->getThreadPool(),SIGNAL(sig_ThreadState(ThreadModelStruct,SAction)),s_threadModel,SLOT(slot_updateData(ThreadModelStruct,SAction)));
    //获取所有线程状态
    s_taskManager->getThreadPool()->sendAllThreadState();
}

void MainWindow::initHttpServer()
{
    s_clienDataRecoder = new ClientDataRecoder(this);
}
