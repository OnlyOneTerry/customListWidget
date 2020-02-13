#include "DataBaseManager.h"
#include <QDebug>
DataBaseManager* DataBaseManager::_instance = nullptr;

DataBaseManager::DataBaseManager()
{
//   initDatabase();
}

DataBaseManager *DataBaseManager::getInstance()
{
    if(_instance==nullptr)
    {
        return new DataBaseManager;
    }
    return _instance;
}

void DataBaseManager::initDatabase()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("AnnoDataBase.db");
    sql_query = QSqlQuery::QSqlQuery(database);
    if(!database.open())
    {
        qDebug()<<"Error:Failed to connect database."<<database.lastError();
    }
    else{
        qDebug()<<"successed to connect database.";
    }

    //创建表格
    if(!sql_query.exec("create table annotationTab(serisId text primary key,address text,annoStatus int, finishTime text,importTime text,result text)"))
    {
        qDebug()<<"Error:Failed to create table."<<sql_query.lastError();
    }
    else{
        qDebug()<<"Table created!";
    }
}

void DataBaseManager::insertToViewTable(QString id, QString address, int statusType, QString finishTime, QString importTime, QString result)
{
    if(!database.open())
    {
        qDebug()<<"Error:Failed to connect database."<<database.lastError();
    }
    else{
        qDebug()<<"successed to connect database.";
    }
    sql_query.prepare("insert into annotationTab(serisId,address,annoStatus,finishTime,importTime,result)VALUES(:id,:dirpath,:status,:time,:impTime,:result)");
    sql_query.bindValue(":id",id);
    sql_query.bindValue(":dirpath",address);
    sql_query.bindValue(":status",statusType);
    sql_query.bindValue(":time",finishTime);
    sql_query.bindValue(":impTime",importTime);
    sql_query.bindValue(":result",result);
    bool res = sql_query.exec();
    qDebug()<<"operation result is--------------- "<<res;
}

void DataBaseManager::selectByStatusTypeFromViewTable(int statusType)
{
    if(!database.open())
    {
        qDebug()<<"Error: failed to connect database."<<database.lastError();
    }
    else{
        qDebug()<<"successed to connect database.";
    }
    _dataList.clear();

    //动态查询
    sql_query.prepare("select * from annotationTab where annoStatus =:type");
    sql_query.bindValue(":type",statusType);
    //sql_query.exec("select * from annotationTab where statusType = 2");
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }else{
        while(sql_query.next())
        {
            ViewData data;
            data._serisId = sql_query.value(0).toString();
            data._address = sql_query.value(1).toString();
            data._annotStatus = (ViewData::AnnoStatus)sql_query.value(2).toInt();
            data._finishTime = sql_query.value(3).toString();
            data._importTime = sql_query.value(4).toString();
            data._annResult = sql_query.value(5).toString();
            _dataList.append(data);
#if 0
            QString id = sql_query.value(0).toString();
            QString address = sql_query.value(1).toString();
            int statusType = sql_query.value(2).toInt();
            QString finishTime = sql_query.value(3).toString();
            QString importTime = sql_query.value(4).toString();
            QString annoResult = sql_query.value(5).toString();
            qDebug()<<QString("id:%1    address:%2    statusType:%3 finishTime:%4 importTime:%5 annoResult:%6").arg(id).arg(address).arg(statusType).arg(finishTime).arg(importTime).arg(annoResult);
#endif
        }
    }
}

void DataBaseManager::delByIdFromViewTable(QString id)
{

}

void DataBaseManager::selectAllFromViewTable()
{
    //查询数据
    if(!database.open())
    {
        qDebug()<<"Error:Failed to connect database."<<database.lastError();
    }
    else{
        qDebug()<<"successed to connect database.";
    }
    _dataList.clear();
    sql_query.exec("select * from annotationTab");
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            ViewData data;
            data._serisId = sql_query.value(0).toString();
            data._address = sql_query.value(1).toString();
            data._annotStatus = (ViewData::AnnoStatus)sql_query.value(2).toInt();
            data._finishTime = sql_query.value(3).toString();
            data._importTime = sql_query.value(4).toString();
            data._annResult = sql_query.value(5).toString();
            qDebug()<<"selectall finishTime is -----"<<data._finishTime<<"importTiem is ---------"<<data._importTime<<"\n";
            _dataList.append(data);
#if 1
            QString id = sql_query.value(0).toString();
            QString address = sql_query.value(1).toString();
            int statusType = sql_query.value(2).toInt();
            QString finishTime = sql_query.value(3).toString();
            QString importTime = sql_query.value(4).toString();
            QString annoResult = sql_query.value(5).toString();
            qDebug()<<QString("id:%1    address:%2    statusType:%3 finishTime:%4 importTime:%5 annoResult:%6").arg(id).arg(address).arg(statusType).arg(finishTime).arg(importTime).arg(annoResult);
#endif
        }
    }
}

