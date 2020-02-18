#include "ListViewMainWidget.h"
#include "ui_ListViewMainWidget.h"
#include <QDebug>
#include <QDir>
#include <QDateTime>
#include <QFileDialog>
#include <QMessageBox>
#include "DataBaseManager.h"
#include "ProgressDialog.h"

ListViewMainWidget::ListViewMainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListViewMainWidget)
{
    ui->setupUi(this);
    _dataManager = new DataBaseManager;
    initUI();
}

ListViewMainWidget::~ListViewMainWidget()
{
    delete ui;
}

void ListViewMainWidget::initUI()
{
    _listWidgt = new CustomListWidget;
    connect(_listWidgt,&CustomListWidget::sigToAnno,this,[=](QString id,QString path){

    });
    connect(_listWidgt,&CustomListWidget::sigToEdit,this,[=](QString id,QString path){

    });
    connect(_listWidgt,&CustomListWidget::sigToDeleteById,this,[=](QString id){
        _dataManager->delByIdFromViewTable(id);
    });
    connect(_listWidgt,&CustomListWidget::sigUpdateNavBtns,this,[=](){
        slotUpdateNavBtns();
        qDebug()<<"----slotUpdateNavBtns --- ";
    });
    connect(_listWidgt,&CustomListWidget::sigToCheckById,this,[=](QString id,QString path){

    });
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
    //初始化时加载数据库中已存在的数据
    on_selectAllBtn_clicked();
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
        //获取有效文件夹下，第一个dicom文件的文件名作为序列号
        QString serisId = getDicomName(iter.key());//入参是文件夹名称
        _dataManager->insertToViewTable(iter.value(),iter.key(),count%3,"--/--/--",importTime,"");
    }
#endif
}

QString ListViewMainWidget::getDicomName(QString dicomDirPath)
{
    QString dicmName;
    QDir dir(dicomDirPath);
    //获取文件夹下第一个dicom
    QFileInfoList mfi = dir.entryInfoList();
    QFileInfo first =  mfi.first();
    //parse first dicom file to get name
    return dicmName;
}

void ListViewMainWidget::slotUpdateNavBtns()
{
    //通过重新加载该类型的数据更新导航按钮
    qDebug()<<"_peration type is --------"<<_operationType;
    switch (_operationType) {
    case SELECTALL:
        _dataManager->selectAllFromViewTable();
        _listWidgt->appendData(std::move(_dataManager->_dataList));
        break;
    case SELECTFNISHED:
        _dataManager->selectByStatusTypeFromViewTable(0);
        _listWidgt->appendData(std::move(_dataManager->_dataList));
        break;
    case SELECTUNANNO:
        _dataManager->selectByStatusTypeFromViewTable(2);
        _listWidgt->appendData(std::move(_dataManager->_dataList));
        break;
    case SELECTANNOING:
        _dataManager->selectByStatusTypeFromViewTable(1);
        _listWidgt->appendData(std::move(_dataManager->_dataList));
        break;
    default:
        break;
    }
}

void ListViewMainWidget::on_uploadBtn_clicked()
{
    QString dirpath = QFileDialog::getExistingDirectory(this,"chose dir","./",QFileDialog::ShowDirsOnly);
    if(!dirpath.isEmpty())
    {
        ProgressDialog& processDialog = ProgressDialog::getGlobalDialog();
        processDialog.show();
        processDialog.setMessage("正在上传序列数据...");
        chaKan(dirpath);
    }
    //将获取的有效序列文件夹导入数据库
    getValidDir();
    //将有效的序列数据送入listveiw显示
    _dataManager->selectAllFromViewTable();
    _listWidgt->appendData(std::move(_dataManager->_dataList));
    //关闭等待提示窗
    ProgressDialog::getGlobalDialog().safeCloseDialog();
    QString num="insert num :"+ QString("%1").arg(_dataManager->getInsertNumThisTime());
    _dataManager->setInsertNumThisTime(0);//复位
    QMessageBox::information(this,"information",num);
}


void ListViewMainWidget::on_selectAllBtn_clicked()
{
    if(_operationType==SELECTALL) return;
    _dataManager->selectAllFromViewTable();
    _listWidgt->appendData(std::move(_dataManager->_dataList));
    _operationType = SELECTALL;
}

void ListViewMainWidget::on_finishedBtn_clicked()
{
    if(_operationType==SELECTFNISHED) return;
    _dataManager->selectByStatusTypeFromViewTable(0);
    _listWidgt->appendData(std::move(_dataManager->_dataList));
    _operationType = SELECTFNISHED;
}

void ListViewMainWidget::on_annoingBtn_clicked()
{
    if(_operationType==SELECTANNOING) return;
    _dataManager->selectByStatusTypeFromViewTable(1);
    _listWidgt->appendData(std::move(_dataManager->_dataList));
    _operationType = SELECTANNOING;
}

void ListViewMainWidget::on_unAnnoBtn_clicked()
{
    if(_operationType==SELECTUNANNO) return;
    _dataManager->selectByStatusTypeFromViewTable(2);
    _listWidgt->appendData(std::move(_dataManager->_dataList));
    _operationType = SELECTUNANNO;
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
