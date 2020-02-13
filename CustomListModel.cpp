
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

    const ViewData *data = m_data[row];
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
    m_serisIdlist.clear();
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


void CustomListModel::resetModel(const QString &id, const QString &finishTime, const QString &importTime, ViewData::AnnoStatus status, QString address, QString result)
{
    beginResetModel();
    for(int i = 0;i<m_data.size();i++){
        if(m_data.at(i)->_serisId == id){
            ViewData* tempData =new ViewData(id,finishTime,importTime,status,address,result);
            m_data.replace(i,tempData);
        }
    }
    endResetModel();
}

void CustomListModel::insert(int index , ViewData *data)
{
    if(index < 0 || index > m_data.count()){
        return;
    }
    if(m_serisIdlist.contains(data->_serisId))return;
    m_serisIdlist.append(data->_serisId);
    m_data.insert(index,data);
}

void CustomListModel::remove(int index)
{
    qDebug()<<"remove index is --------------"<<index<<"m_data list size is ---------"<<m_data.count() ;
    if(index < 0 || index >= m_data.count()){
        return;
    }

    beginRemoveRows(QModelIndex(),index,index);
    ViewData* data = m_data.at(index);
    m_data.removeAt(index);
    m_serisIdlist.removeAt(index);
    //deleteIndexFile(data->_address);//删除文件夹中的数据
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

void CustomListModel::append(const QString &id, const QString &finishTime, const QString &importTime, ViewData::AnnoStatus state, QString address, QString result)
{
    insert(m_data.count(),new ViewData(id,finishTime,importTime,state,address,result));
    qDebug()<<"insert data finishtime is -------"<<finishTime<<"importTime is --------"<<importTime;
}


bool CustomListModel::checkFileExist(int index)
{
    QString id = m_data.at(index)->_serisId;
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

ViewData *CustomListModel::findAt(int index)
{
    if(index>m_data.size()) return nullptr;
    return m_data[index];
}

int CustomListModel::getIndexById(QString serisID)
{
    for(int i = 0;i<m_data.size();i++)
    {
        if(m_data[i]->_serisId == serisID)
        {
            qDebug()<<"serisId is ---"<<m_data[i]->_serisId;
            return i;
        }
    }
    return -1;
}





