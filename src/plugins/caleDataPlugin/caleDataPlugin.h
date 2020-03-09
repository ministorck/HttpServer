#ifndef CALEDATAPLUGIN_H
#define CALEDATAPLUGIN_H

#include <QGenericPlugin>
#include <caledatainterface.h>

class caleDataPlugin :public QObject, public CaleDataInterface
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QGenericPluginFactoryInterface" FILE "caleDataPlugin.json")
#endif // QT_VERSION >= 0x050000
    Q_INTERFACES(PluginInterface)
public:
    caleDataPlugin(QObject *parent = 0);

    int addValue(int i1, int i2){return i1+i2;}
};

#endif // CALEDATAPLUGIN_H
