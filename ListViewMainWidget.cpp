#include "ListViewMainWidget.h"
#include "ui_ListViewMainWidget.h"
#include <QDebug>
#include <QDir>
#include <QDateTime>
#include <QFileDialog>
#include <QMessageBox>
#include "DataBaseManager.h"
#include "ProgressDialog.h"
#include <QAxObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QIODevice>

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
    //加载当前文件夹
    _dirlist.append(path);
    QString dirName = getParseDirName(path);
    _dirPathAndDirNameMap.insert(path,dirName);
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

    foreach (auto mfi, dir.entryInfoList()) {//若文件夹中包含.dcm文件则此文件夹为有效文件夹
        if(mfi.isFile()&&mfi.fileName().contains(".dcm"))
        {
            return true;
        }
    }
    return false;
}

QString ListViewMainWidget::getParseDirName(QString dirPath)
{
    int idex = dirPath.lastIndexOf("/");
    QString dirName = dirPath.right(dirPath.length()-idex-1);
    return dirName;
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
        QString tempResultJson = readJsonFile("D:/1.json");//临时测试代码读取json格式的字符串
        _dataManager->insertToViewTable(iter.value(),iter.key(),count%3,"--/--/--",importTime,tempResultJson);
    }
#endif
}

QString ListViewMainWidget::readJsonFile(QString path)
{
    QString result="";
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly) )
    {
        qDebug()<<"failed to open file";

    }
    result = file.readAll();
    file.close();
    return result;
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

void ListViewMainWidget::on_exportFinishedBtn_clicked()
{

    QString filepath=QFileDialog::getSaveFileName(NULL,QObject::tr("Save orbit"),"/untitled.xlsx",QObject::tr("Microsoft Office 2007 (*.xlsx)"));//获取保存路径
    QList<QVariant> allRowsData;//保存所有行数据
    allRowsData.clear();
    if(!filepath.isEmpty()){
        //提示窗
        ProgressDialog& processDialog = ProgressDialog::getGlobalDialog();
        processDialog.show();
        processDialog.setMessage("正在导出数据...");

        //获取已完成数据
        _dataManager->selectByStatusTypeFromViewTable(0);
        QList<ViewData> dataList = std::move(_dataManager->_dataList);

        //导出主体功能
        QAxObject *excel = new QAxObject("Excel.Application");//连接Excel控件
        excel->dynamicCall("SetVisible (bool Visible)",false);//不显示窗体
        excel->setProperty("DisplayAlerts", true);//不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示
        QAxObject *workbooks = excel->querySubObject("WorkBooks");//获取工作簿集合
        workbooks->dynamicCall("Add");//新建一个工作簿
        QAxObject *workbook  = excel->querySubObject("ActiveWorkBook");//获取当前工作簿
        QAxObject *worksheets = workbook->querySubObject("Sheets");//获取工作表集合
        QAxObject *worksheet = worksheets->querySubObject("Item(int)",1);//获取工作表集合的工作表1，即sheet1、
        QStringList header;
        header<<"serisID"<<"path"<<"finishTiem"<<"1zhifang"<<"1xianwei"<<"1gaihua"<<"1chuxue"<<"2zhifang"<<"2xianwei"<<"2gaihua"<<"2chuxue"<<"3zhifang"<<"3xianwei"<<"3gaihua"<<"3chuxue"<<"diagnostic";
        allRowsData.append(QVariant(header));
        for(int row = 0; row < dataList.size(); row++)
        {
            QStringList aRowData;
            QString annoResult = dataList.at(row)._annResult;
            QJsonParseError parseJsonErr;
            QJsonDocument doc = QJsonDocument::fromJson(annoResult.toUtf8(),&parseJsonErr);
            if(!(parseJsonErr.error==QJsonParseError::NoError))
            {
                qDebug()<<tr("parse error");
                return;
            }

            aRowData<<dataList.at(row)._serisId<<dataList.at(row)._address<<dataList.at(row)._finishTime;//先获取序列号，地址，完成时间

            QJsonObject jsonObject = doc.object();
            int diagnostic = jsonObject.value("diagnosic").toInt();
            QJsonArray list = jsonObject.value("list").toArray();
            foreach (auto var, list) {
                QJsonObject  item = var.toObject();
                QJsonObject  fiber = item.value("fiber").toObject();//纤维 2
                double fiberS = fiber.value("area").toDouble();
                QJsonObject  calcification = item.value("calcification").toObject();//钙化 3
                double calS = calcification.value("area").toDouble();
                QJsonObject  fat = item.value("fat").toObject();//脂肪 1
                double fatS = fat.value("area").toDouble();
                QJsonObject  bleeding = item.value("bleeding").toObject();//出血 4
                double bleedingS = bleeding.value("area").toDouble();
                aRowData<<QString("%1").arg(fatS)<<QString("%1").arg(fiberS)<<QString("%1").arg(calS)<<QString("%1").arg(bleedingS);
                qDebug()<<"fiber is"<<fiberS<<"cal is"<<calS<<"fat is"<<fatS<<"bleeding is"<<bleedingS;
            }

            aRowData<<QString("%1").arg(diagnostic);//诊断结果

            //解析annoResult获取诊断结果和各指标
            allRowsData.append(QVariant(aRowData));
        }
        QAxObject *range = worksheet->querySubObject("Range(const QString )", "A1:P"+QString("%1").arg(10));//A-P单元格存放所需的字段
        range->dynamicCall("SetValue(const QVariant&)",QVariant(allRowsData));//存储所有数据到 excel 中,批量操作,速度极快
        range->querySubObject("Font")->setProperty("Size", 10);//设置字号

        //        QAxObject *cell = worksheet->querySubObject("Range(QVariant, QVariant)","A1");//获取单元格
        //        cell = worksheet->querySubObject("Cells(int, int)", 1, 1);//等同于上一句
        //        cell->dynamicCall("SetValue(const QVariant&)",QVariant(123));//存储一个 int 数据到 excel 的单元格中
        //        cell->dynamicCall("SetValue(const QVariant&)",QVariant("abc"));//存储一个 string 数据到 excel 的单元格中
        //        QString str = cell->dynamicCall("Value2()").toString();//读取单元格中的值
        //        cout<<"\nThe value of cell is "<<str.toStdString()<<endl;
        worksheet->querySubObject("Range(const QString&)", "1:1")->setProperty("RowHeight", 60);//调整第一行行高
        workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(filepath));//保存至filepath，注意一定要用QDir::toNativeSeparators将路径中的"/"转换为"\"，不然一定保存不了。
        workbook->dynamicCall("Close()");//关闭工作簿
        excel->dynamicCall("Quit()");//关闭excel
        delete excel;
        excel=NULL;
        //关闭提示窗
        processDialog.safeCloseDialog(1);
    }
}

void ListViewMainWidget::on_searchBtn_clicked()
{
    _operationType = SELECTBYLIKEID;
    QString serisId = ui->lineEdit->text();
    qDebug()<<"search id is --"<<serisId;

    _dataManager->selectByLikeIdFromViewTable(serisId);
    _listWidgt->appendData(std::move(_dataManager->_dataList));

    //    int idex = _listWidgt->serchSpecifySeris(serisId);
    //    if(idex>=0)
    //    {
    //        //跳转到指定的序列
    //        _listWidgt->moveToSpecifySeris(idex);
    //    }else{
    //        QMessageBox::information(this,"information",QString("not found...."));
    //    }
}
