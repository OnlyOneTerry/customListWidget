#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "CommonDataDefine.h"
#include <QList>

class DataBaseManager
{
public:
    static DataBaseManager* getInstance();
     void initDatabase();
    //显示列表相关操作
     void insertToViewTable(QString id, QString address, int statusType, QString finishTime,QString importTime, QString result);
     void selectByStatusTypeFromViewTable(int statusType);
     void delByIdFromViewTable(QString id);
     void selectAllFromViewTable();
public:
    DataBaseManager();
private:
    static DataBaseManager* _instance;
    //数据库操作相关
    QSqlDatabase database;
    QSqlQuery sql_query;
public:
    QList<ViewData> _dataList;//缓存数据
};

#endif // DATABASEMANAGER_H
