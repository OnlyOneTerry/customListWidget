#ifndef ListViewMainWidget_H
#define ListViewMainWidget_H

#include <QWidget>
#include "CustomListWidget.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMap>
namespace Ui {
class ListViewMainWidget;
}
class DataBaseManager;
class ListViewMainWidget : public QWidget
{
    Q_OBJECT
public:
    enum SearchOpeationType
    {
        LOADNEW,
        SELECTALL,
        SELECTFNISHED,
        SELECTUNANNO,
        SELECTANNOING,
        INVALID
    };
public:
    explicit ListViewMainWidget(QWidget *parent = 0);
    ~ListViewMainWidget();
    void initUI();
    void chaKan(QString path);
    bool checkDirIsValid(QString dirPath);
    void getValidDir();
public slots:
    void slotUpdateNavBtns();//用于删除时更新导航按钮
private slots:

    void on_uploadBtn_clicked();

    void on_selectAllBtn_clicked();

    void on_finishedBtn_clicked();

    void on_annoingBtn_clicked();

    void on_unAnnoBtn_clicked();

    void on_importFinishedBtn_clicked();

    void on_searchBtn_clicked();

private:
    Ui::ListViewMainWidget *ui;
    CustomListWidget* _listWidgt = nullptr;
    //数据库操作相关
    QSqlDatabase database;
    QSqlQuery sql_query;
    QStringList _dirlist;//记录文件夹地址
    QMap<QString,QString> _dirPathAndDirNameMap;//文件夹路径和文件夹名称(序列编号)关联容器
    QList<ViewData> _dataList;//缓存数据
    int _recurseTime  = 0;//递归次数3次
    DataBaseManager* _dataManager =nullptr;
    SearchOpeationType _operationType =INVALID;
};

#endif // ListViewMainWidget_H
