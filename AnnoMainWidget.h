#ifndef ANNOMAINWIDGET_H
#define ANNOMAINWIDGET_H

#include <QWidget>
#include "CustomListWidget.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMap>
namespace Ui {
class AnnoMainWidget;
}

class AnnoMainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AnnoMainWidget(QWidget *parent = 0);
    ~AnnoMainWidget();
    void initDatabase();
    void initUI();
    void chaKan(QString path);
    bool checkDirIsValid(QString dirPath);
    void getValidDir();
    void insertToTable(QString id, QString address, int statusType, QString finishTime, QString result);
    void selectByStatusType(int statusType);
    void delById(QString id);
    void selectAll();
private slots:
    void on_uploadBtn_clicked();

    void on_selectAllBtn_clicked();

    void on_finishedBtn_clicked();

    void on_annoingBtn_clicked();

    void on_unAnnoBtn_clicked();

    void on_importFinishedBtn_clicked();

    void on_searchBtn_clicked();

private:
    Ui::AnnoMainWidget *ui;
    CustomListWidget* _listWidgt = nullptr;
    //数据库操作相关
    QSqlDatabase database;
    QSqlQuery sql_query;
    QStringList _dirlist;//记录文件夹地址
    QMap<QString,QString> _dirPathAndDirNameMap;//文件夹路径和文件夹名称(序列编号)关联容器
};

#endif // ANNOMAINWIDGET_H
