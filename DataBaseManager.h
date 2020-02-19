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
     void setInsertNumThisTime(int count);
     int getInsertNumThisTime();
     //根据序列号模糊查询
     void selectByLikeIdFromViewTable(QString likeId);
     //通过序列id获取标注结果
     QString getAnnoResult(QString serisId);
     //通过序列id修改标注结果
     void  updateAnnoResult(QString serisId,QString newResult);
     //通过序列号更新完成时间
     void  updateAnnoFinishedTime(QString serisId,QString finishTime);
     //通过序列号更新标注状态
     void updateAnnoStatus(QString serisId, int newStatus);
public:
    DataBaseManager();
private:
    static DataBaseManager* _instance;
    //数据库操作相关
    QSqlDatabase database;
    QSqlQuery sql_query;
public:
    QList<ViewData> _dataList;//缓存数据
    int _insertNumThisTime= 0;//本次插入的数量
};

#endif // DATABASEMANAGER_H
