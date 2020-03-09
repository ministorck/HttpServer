#include "ResponseLocalData.h"
#include <QDir>
#include <QDebug>
ResponseLocalData::ResponseLocalData(QObject *parent) :
    QObject(parent)
{
    m_localPath = "../data";
    if(QDir(m_localPath).exists())
        qDebug() << "m_localPath is exists!!!!";
}

bool ResponseLocalData::openLocalFile(QString path)
{
    QString localPath = m_localPath + path;
    m_file.setFileName(localPath);
    if(!m_file.exists())
        return false;
    if(!m_file.open(QIODevice::ReadWrite))
        return false;
    return true;
}

bool ResponseLocalData::readCurData(QByteArray& byte)
{
    if(!m_file.isOpen())
        return false;
    byte = m_file.readAll();
    return true;
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(responseLocalData, ResponseLocalData)
#endif // QT_VERSION < 0x050000
