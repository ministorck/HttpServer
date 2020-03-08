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
    QByteArray responseData(QByteArray byte);
private:
    QByteArray inspectionBufferSetup();

    QByteArray get_();

    QByteArray put_();

    QByteArray post_();

    QByteArray patch_();

    QByteArray delete_();
private:
    QMap<void *,QByteArray> m_map;

    QByteArray buffer_;

    QString requestSource_;
    QString requestMethod_;
    QString requestUrl_;
    QString requestCrlf_;

    QMap< QString, QString > requestHeader_;

    qint64 contentLength_ = -1;

};

#endif // DATABASEPLUGIN_H
