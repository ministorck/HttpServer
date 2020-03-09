#ifndef DATABASEPLUGIN_H
#define DATABASEPLUGIN_H

#include <QGenericPlugin>
#include <databaseinterface.h>
#include <QMap>



class DatabasePlugin : public QObject,public DatabaseInterface
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.DatabasePlugin" FILE "databaseplugin.json")
#endif // QT_VERSION >= 0x050000
    Q_INTERFACES(PluginInterface)

public:
    DatabasePlugin(QObject *parent = 0);

    void insert(QString str);
    // 测试方法1：通过接收到数据进行解析，直接返回http数据内容。
    QByteArray responseData(QByteArray byte);

    // 方法2：通过接收到数据，解析完成后，在插件管理器中调取响应插件解析进行结果反馈。
    // 步骤为：先解析数据->解析成功后管理器根据请求类型进行分别处理相应功能反馈。
    bool analyzingData(QByteArray byte);

    Method_ GetMethod();

    QString GetUrl(){return requestUrl_;}

    QString GetRequestData(){return requestData_;}

    QByteArray GetResPonseData(QByteArray data);

private:
    QByteArray inspectionBufferSetup();

    QByteArray get_();

    QByteArray put_();

    QByteArray post_();

    QByteArray patch_();

    QByteArray delete_();

    QByteArray error_();
private:
    QMap<void *,QByteArray> m_map;

    QByteArray buffer_;
    QByteArray responseData_;

    QString requestMethod_;
    QString requestSource_;
    QString requestUrl_;
    QString requestCrlf_;
    QString requestData_;

    QMap< QString, QString > requestHeader_;

    qint64 contentLength_ = -1;

};

#endif // DATABASEPLUGIN_H
