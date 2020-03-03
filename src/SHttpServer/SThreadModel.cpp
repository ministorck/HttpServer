#include "SThreadModel.h"

SThreadModel::SThreadModel(QObject* parent): QAbstractTableModel(parent)
{
    s_header<<"线程ID"<<"线程状态"<<"线程任务";
}

SThreadModel::~SThreadModel()
{

}

QVariant SThreadModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    switch (role) {
    case Qt::TextAlignmentRole:
        return int(Qt::AlignVCenter | Qt::AlignHCenter);
    case Qt::DisplayRole:
        switch (index.column()) {
        case 0:
        {
            QString str;
            str.sprintf("%p",s_showData.at(index.row()).s_id);
            return str;
        }
        case 1:
            return s_showData.at(index.row()).s_state ? "运行":"停止";
        case 2:
            return s_showData.at(index.row()).s_explain;
        default:
            return QVariant();
        }
    default:
        return QVariant();
    }
}

QVariant SThreadModel::headerData(int section, Qt::Orientation orientation, int role) const
{
     if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
         return s_header.at(section);
     return QAbstractTableModel::headerData(section,orientation,role);
}

int SThreadModel::rowCount(const QModelIndex &parent) const
{
    return s_allThreadData.size();
}

int SThreadModel::columnCount(const QModelIndex &parent) const
{
    return s_header.size();
}

void SThreadModel::slot_updateData(const ThreadModelStruct data,const SAction action)
{
    beginResetModel();
    switch (action) {
    case SAction_Add://添加数据
    {
        s_allThreadData[data.s_id] = data;
        s_showData.append(data);
        break;
    }
    case SAction_Del://删除数据
    {
        AllThreadData::iterator iter = s_allThreadData.find(data.s_id);
        if(iter != s_allThreadData.end())
        {
            s_allThreadData.remove(data.s_id);
            s_showData = s_allThreadData.values();
        }
    }
        break;
    case SAction_Update://更新数据
    {
        s_allThreadData[data.s_id] = data;
        s_showData = s_allThreadData.values();
    }
    }
    endResetModel();
}
