#include "ListViewMainWidget.h"
#include "ui_ListViewMainWidget.h"
#include <QDebug>
#include <QDir>
#include <QDateTime>
#include <QFileDialog>
#include <QMessageBox>
#include "DataBaseManager.h"

ListViewMainWidget::ListViewMainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListViewMainWidget)
{
    ui->setupUi(this);
    //    initDatabase();
    _dataManager = new DataBaseManager;
    initUI();
}

ListViewMainWidget::~ListViewMainWidget()
{
    delete ui;
}

void ListViewMainWidget::initDatabase()
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

void ListViewMainWidget::initUI()
{
    _listWidgt = new CustomListWidget;
    ui->rightListWidget->layout()->addWidget(_listWidgt);
    _listWidgt->updateHeaderWid();
    ui->lineEdit->setAttribute(Qt::WA_InputMethodEnabled, false);
    connect(ui->lineEdit,&CustomLineEdit::sigFocusIn,this,[=](){
        ui->lineEdit->setText("");
        ui->iconWidget->hide();
        ui->lineEdit->setFixedWidth(325);
        //清除被索行的背景色
        _listWidgt->setSearchedItemAt(-1);
    });
    connect(ui->lineEdit,&CustomLineEdit::sigFocusOut,this,[=](){

    });
}

void ListViewMainWidget::chaKan(QString path)
{
    //递归遍历3层
    if(_recurseTime>=4)
    {
        _recurseTime = 0;
        return;
    }
    _recurseTime++;
    QDir dir(path);
    foreach (auto mfi, dir.entryInfoList()) {
        if(mfi.isFile())
        {
            continue;
            //  qDebug()<<"file :"<<mfi.fileName();
        }else{
            if(mfi.fileName()=="."||mfi.fileName()=="..")continue;
            //qDebug()<<"Entry absoluteFilePath is"<<mfi.absoluteFilePath();
            qDebug()<<"Entry dir name  is"<<mfi.baseName();
            _dirlist.append(mfi.absoluteFilePath());
            _dirPathAndDirNameMap.insert(mfi.absoluteFilePath(),mfi.baseName());
            chaKan(mfi.absoluteFilePath());
        }
    }
}

bool ListViewMainWidget::checkDirIsValid(QString dirPath)
{
    QDir dir(dirPath);

    foreach (auto mfi, dir.entryInfoList()) {//若文件夹中包含.dicom文件则此文件夹为有效文件夹
        if(mfi.isFile()&&mfi.fileName().contains(".dicom"))
        {
            return true;
        }
    }
    return false;
}

void ListViewMainWidget::getValidDir()
{
    foreach (auto path, _dirlist) {
        bool isValid = checkDirIsValid(path);
        if(!isValid){
            _dirlist.removeOne(path);
            _dirPathAndDirNameMap.remove(path);
        }
    };
#if 1
    QDateTime current_date_time =  QDateTime::currentDateTime();
    QString importTime =  current_date_time.toString("yyyy/MM/dd hh:mm");

    //获取有效文件夹地址相关信息：完成时间，序列号，标注状态
    for(auto iter = _dirPathAndDirNameMap.begin();iter!=_dirPathAndDirNameMap.end();iter++)
    {
        static int count = 0;
        count++;
        //        insertToTable(iter.value(),iter.key(),count%3,"--/--/--",importTime,"");
        _dataManager->insertToViewTable(iter.value(),iter.key(),count%3,"--/--/--",importTime,"");
    }
#endif
}

void ListViewMainWidget::insertToTable(QString id, QString address, int statusType, QString finishTime, QString importTime, QString result)
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

void ListViewMainWidget::selectByStatusType(int statusType)
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
    _listWidgt->appendData(_dataList);
}

void ListViewMainWidget::delById(QString id)
{

}

void ListViewMainWidget::selectAll()
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
            qDebug()<<"selectall finishTime is -----"<<data._finishTime<<"importTiem is ---------"<<data._importTime;
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
    _listWidgt->appendData(_dataList);
}

void ListViewMainWidget::on_uploadBtn_clicked()
{
    QString dirpath = QFileDialog::getExistingDirectory(this,"chose dir","./",QFileDialog::ShowDirsOnly);
    if(!dirpath.isEmpty())
    {
        chaKan(dirpath);
    }
    //将获取的有效序列文件夹导入数据库
    getValidDir();
    //将有效的序列数据送入listveiw显示
    _dataManager->selectAllFromViewTable();
    _listWidgt->appendData(std::move(_dataManager->_dataList));
    qDebug()<<"DataBaseManager dataList size is --------"<<_dataList.size();
}


void ListViewMainWidget::on_selectAllBtn_clicked()
{
    _dataManager->selectAllFromViewTable();
    _listWidgt->appendData(std::move(_dataManager->_dataList));
}

void ListViewMainWidget::on_finishedBtn_clicked()
{
    _dataManager->selectByStatusTypeFromViewTable(0);
    _listWidgt->appendData(std::move(_dataManager->_dataList));
}

void ListViewMainWidget::on_annoingBtn_clicked()
{
    _dataManager->selectByStatusTypeFromViewTable(1);
    _listWidgt->appendData(std::move(_dataManager->_dataList));
}

void ListViewMainWidget::on_unAnnoBtn_clicked()
{
    _dataManager->selectByStatusTypeFromViewTable(2);
    _listWidgt->appendData(std::move(_dataManager->_dataList));
}

void ListViewMainWidget::on_importFinishedBtn_clicked()
{

}

void ListViewMainWidget::on_searchBtn_clicked()
{
    QString serisId = ui->lineEdit->text();
    qDebug()<<"search id is --"<<serisId;
    int idex = _listWidgt->serchSpecifySeris(serisId);
    if(idex>=0)
    {
        //跳转到指定的序列
        _listWidgt->moveToSpecifySeris(idex);
    }else{
        QMessageBox::information(this,"information",QString("not found...."));
    }
}
