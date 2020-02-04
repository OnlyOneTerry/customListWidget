
#include <QDebug>
#include <QFileInfoList>
#include <QDir>
#include <QSize>
#include "CustomListModel.h"

CustomListModel::CustomListModel(QObject *parent)
    : QAbstractListModel(parent), m_RobotCount(0)
{

}

CustomListModel::~CustomListModel()
{
    clear();
}


QVariant CustomListModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row <0 || row >= m_data.count()){
        return QVariant();
    }

    const Data *data = m_data[row];
    switch (role) {
    case  SerisId:
        return data->_serisId;
    case SerisStatus:
        return data->_annotStatus;
    case SerisFinishTime:
        return data->_finishTime;
    case SerisImportTime:
        return data->_importTime;
    case SerisAddress:
        return data->_address;
    case SerisAnnoResult:
        return data->_annResult;
    case Qt::SizeHintRole:
        return QSize(0, 40);

    default:
        break;
    }
    return QVariant();
}

int CustomListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}

void CustomListModel::clear()
{
    m_data.clear();
}

QHash<int, QByteArray> CustomListModel::roleNames() const
{
    QHash<int, QByteArray> roles; //设置列表的角色，即所有属性字段
    roles[SerisId] = "serisId";
    roles[SerisStatus] = "status";
    roles[SerisFinishTime] = "finisTime";
    roles[SerisImportTime] = "importTime";
    roles[SerisAddress] = "address";
    roles[SerisAnnoResult] = "result";
    return roles;
}


void CustomListModel::resetModel(const quint32 &id, const QString &finishTime, const QString &importTime, Data::AnnoStatus status, QString address, QString result)
{
    beginResetModel();
    for(int i = 0;i<m_data.size();i++){
        if(m_data.at(i)->_serisId == id){
            Data* tempData =new Data(id,finishTime,importTime,status,address,result);
            m_data.replace(i,tempData);
        }
    }
    endResetModel();
}

void CustomListModel::insert(int index , Data *data)
{
    if(index < 0 || index > m_data.count()){
        return;
    }
//    emit  beginInsertRows(QModelIndex(),index,index);
    if(m_serisIdlist.contains(data->_serisId))return;
    m_serisIdlist.append(data->_serisId);
    m_data.insert(index,data);
//    emit endInsertRows();
}

void CustomListModel::remove(int index)
{
    qDebug()<<"remove index is --------------"<<index<<"m_data list size is ---------"<<m_data.count() ;
    if(index < 0 || index >= m_data.count()){
        return;
    }

    beginRemoveRows(QModelIndex(),index,index);
    Data* data = m_data.at(index);
    m_data.removeAt(index);
    m_serisIdlist.removeAt(index);
    //    deleteIndexFile("All/"+data._serisId);
    deleteIndexFile(data->_address);
    endRemoveRows();
}

bool CustomListModel::deleteIndexFile(QString path)
{

    if (path.isEmpty())
    {
        return false;
    }

    QDir dir(path);
    if(!dir.exists())
    {
        return true;
    }

    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    foreach (QFileInfo fi, fileList)
    {
        if (fi.isFile())
        {
            fi.dir().remove(fi.fileName());
        }
        else
        {
            deleteIndexFile(fi.absoluteFilePath());
        }
    }
    return dir.rmpath(dir.absolutePath());
}

void CustomListModel::append(const quint32 &id, const QString &finishTime, const QString &importTime, Data::AnnoStatus state, QString address, QString result)
{

    insert(m_data.count(),new Data(id,finishTime,importTime,state,address,result));

}


bool CustomListModel::checkFileExist(int index)
{
    quint32 id = m_data.at(index)->_serisId;
    QString address = m_data.at(index)->_address;
    QFileInfo fi(address);

    if(fi.exists()){

        qDebug()<<"file path is 0000000-0-0-0-0-0-0"<<address<<"-------true";
        return true;
    }
    else{
        qDebug()<<"file path is 0000000-0-0-0-0-0-0"<<address<<"-------false";
        return false;
    }
}

Data *CustomListModel::findAt(int index)
{
    return m_data[index];
}





