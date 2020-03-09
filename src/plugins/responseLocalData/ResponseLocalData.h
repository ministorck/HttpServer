#ifndef RESPONSELOCALDATA_H
#define RESPONSELOCALDATA_H

#include <QGenericPlugin>
#include <responselocaldatainterface.h>
#include <QFile>

class ResponseLocalData : public QObject,public ResponseLocalDataInterface
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QGenericPluginFactoryInterface" FILE "responseLocalData.json")
#endif // QT_VERSION >= 0x050000
    Q_INTERFACES(PluginInterface)
public:
    ResponseLocalData(QObject *parent = 0);
    bool openLocalFile(QString path);
    bool readCurData(QByteArray& byte);
private:
    QFile m_file;
};

#endif // RESPONSELOCALDATA_H
