#ifndef STHREADMODEL_H
#define STHREADMODEL_H
#include <QAbstractTableModel>
#include "PublicStruct.h"
#include <QMap>

typedef QMap<void* ,ThreadModelStruct> AllThreadData;

class SThreadModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    SThreadModel(QObject* parent = Q_NULLPTR);
    ~SThreadModel();
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

public slots:
    void slot_updateData(const ThreadModelStruct data,const SAction action);
private:
    QStringList s_header;
    AllThreadData s_allThreadData;
    QList<ThreadModelStruct> s_showData;
};

#endif // STHREADMODEL_H
