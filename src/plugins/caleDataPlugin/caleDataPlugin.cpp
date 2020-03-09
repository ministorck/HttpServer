#include "caleDataPlugin.h"


caleDataPlugin::caleDataPlugin(QObject *parent) :
    QObject(parent)
{
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(caleDataPlugin, caleDataPlugin)
#endif // QT_VERSION < 0x050000
