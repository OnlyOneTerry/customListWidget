#include "DataBaseManager.h"
#include <QDebug>
#include <QSqlRecord>
DataBaseManager* DataBaseManager::_instance = nullptr;

DataBaseManager::DataBaseManager()
{
    initDatabase();
}

DataBaseManager *DataBaseManager::getInstance()
{
    if(_instance==nullptr)
    {
        _instance = new DataBaseManager;
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
    if(res)
    {
        _insertNumThisTime++;
    }
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
    //查询数据
    if(!database.open())
    {
        qDebug()<<"Error:Failed to connect database to delete."<<database.lastError();
    }
    else{
        qDebug()<<"successed to connect database to delete.";
    }
    QString delete_sql = "delete from annotationTab where serisId =:id";
    sql_query.prepare(delete_sql);
    sql_query.bindValue(":id",id);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        qDebug()<<"deleted!";
    }
}

void DataBaseManager::selectByLikeIdFromViewTable(QString likeId)
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
    QString sqlString = "select * from annotationTab where  serisId LIKE'%"+likeId+ "%'";
    sql_query.exec(sqlString);
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
//            qDebug()<<"selectall finishTime is -----"<<data._finishTime<<"importTiem is ---------"<<data._importTime<<"\n";
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
//            qDebug()<<"selectall finishTime is -----"<<data._finishTime<<"importTiem is ---------"<<data._importTime<<"\n";
            _dataList.append(data);
#if 1
            QString id = sql_query.value(0).toString();
            QString address = sql_query.value(1).toString();
            int statusType = sql_query.value(2).toInt();
            QString finishTime = sql_query.value(3).toString();
            QString importTime = sql_query.value(4).toString();
            QString annoResult = sql_query.value(5).toString();
//            qDebug()<<QString("id:%1    address:%2    statusType:%3 finishTime:%4 importTime:%5 annoResult:%6").arg(id).arg(address).arg(statusType).arg(finishTime).arg(importTime).arg(annoResult);
#endif
        }
    }
}

void DataBaseManager::setInsertNumThisTime(int count)
{
    _insertNumThisTime = count;
}

int DataBaseManager::getInsertNumThisTime()
{
    return _insertNumThisTime;
}

void DataBaseManager::removeTempData(QString id)
{
  for(int i = 0;i<_dataList.size();i++)
  {
      if(_dataList.at(i)._serisId==id)
      {
          _dataList.removeAt(i);
          break;
      }
  }
}

QString DataBaseManager::getAnnoResult(QString serisId)
{
    //查询数据
    if(!database.open())
    {
        qDebug()<<"Error:Failed to connect database."<<database.lastError();
    }
    else{
        qDebug()<<"successed to connect database.";
    }
    QString delete_sql = "select result from annotationTab where serisId =:id";
    sql_query.prepare(delete_sql);
    sql_query.bindValue(":id",serisId);
    QString annoResult ="";
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next()){
            annoResult = sql_query.value(0).toString();
            qDebug()<<"get result is -------"<<annoResult;
            return annoResult;
        }
    }
    return annoResult;
}

void DataBaseManager::updateAnnoResult(QString serisId, QString newResult)
{
    if(!database.open())
    {
        qDebug()<<"Error:Failed to connect database."<<database.lastError();
    }
    else{
        qDebug()<<"successed to connect database.";
    }

    //修改数据
    QString alterResult_sql = "update  annotationTab set result =:newResult where serisId =:id";
    sql_query.prepare(alterResult_sql);
    sql_query.bindValue(":id",serisId);
    sql_query.bindValue(":newResult",newResult);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        qDebug() << "updated result!";
    }
}

void DataBaseManager::updateAnnoFinishedTime(QString serisId, QString finishTime)
{
    if(!database.open())
    {
        qDebug()<<"Error:Failed to connect database."<<database.lastError();
    }
    else{
        qDebug()<<"successed to connect database.";
    }

    //修改数据
    QString alterFinishTime_sql = "update  annotationTab set finishTime =:newTime where serisId =:id";
    sql_query.prepare(alterFinishTime_sql);
    sql_query.bindValue(":id",serisId);
    sql_query.bindValue(":newTime",finishTime);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        qDebug() << "updated finishTime!";
    }
}

void DataBaseManager::updateAnnoStatus(QString serisId, int newStatus)
{
    if(!database.open())
    {
        qDebug()<<"Error:Failed to connect database."<<database.lastError();
    }
    else{
        qDebug()<<"successed to connect database.";
    }

    //修改数据
    QString alterStatus_sql = "update  annotationTab set annoStatus =:newStatus where serisId =:id";
    sql_query.prepare(alterStatus_sql);
    sql_query.bindValue(":id",serisId);
    sql_query.bindValue(":newStatus",newStatus);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        qDebug() << "updated status!";
    }
}

int DataBaseManager::getEmptyCount()
{
    if(!database.open())
    {
        qDebug()<<"Error:Failed to connect database."<<database.lastError();
    }
    else{
        qDebug()<<"successed to connect database.";
    }

    int emptyCount = 1;
    //获取空数据
    QString alterStatus_sql = "select * from  annotationTab  where annoStatus =:status";
    sql_query.prepare(alterStatus_sql);
    sql_query.bindValue(":status",-1);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next()){
            emptyCount++;
        }
        qDebug() << "insert emptyCount is "<<emptyCount;
    }
    return emptyCount;
}

void DataBaseManager::deleteEmptyRows()
{
    //查询数据
    if(!database.open())
    {
        qDebug()<<"Error:Failed to connect database to delete."<<database.lastError();
    }
    else{
        qDebug()<<"successed to connect database to delete.";
    }
#if 0
    QString delete_sql = "delete from annotationTab where annoStatus =:status";
    sql_query.prepare(delete_sql);
    sql_query.bindValue(":status",-1);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        qDebug()<<"deleted!";
    }
#endif

    if(!sql_query.exec("delete from annotationTab where annoStatus = -1"))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        qDebug()<<"deleted!";
    }
}



