#include "CustomListWidget.h"
#include "ui_CustomListWidget.h"
#include <QDateTime>
#include <QScrollBar>
#include <QDebug>
#include <QSpacerItem>
#include <QMessageBox>
#include <QDesktopServices>
#include <QClipboard>
#include <QListView>

CustomListWidget::CustomListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomListWidget)
{
    ui->setupUi(this);
    _model = new CustomListModel();
    _model->setHeaderData(0,Qt::Orientation::Horizontal,"序列号",Qt::DisplayRole);
    _model->setHeaderData(1,Qt::Orientation::Horizontal,"状态",Qt::DisplayRole);
    _model->setHeaderData(2,Qt::Orientation::Horizontal,"标注完成时间",Qt::DisplayRole);
    _model->setHeaderData(3,Qt::Orientation::Horizontal,"操作",Qt::DisplayRole);
    _delegate = new CustomListDelegate(_model);
    ui->listView->setModel(_model);
    ui->listView->setItemDelegate(_delegate);
    ui->listView->setUniformItemSizes(true);
    connect(_delegate,&CustomListDelegate::sigAnnData,this,&CustomListWidget::slotToAnno);
    connect(_delegate,&CustomListDelegate::sigDelData,this,&CustomListWidget::slotDel);
    connect(_delegate,&CustomListDelegate::sigEditData,this,&CustomListWidget::slotToAnno);
    connect(_delegate,&CustomListDelegate::sigOpenDir,this,&CustomListWidget::slotOpenDir);
    connect(_delegate,&CustomListDelegate::sigCheck,this,&CustomListWidget::slotCheck);
    //设置当listView为编辑状态
    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    connect(ui->listView,&QListView::clicked,this,[&](QModelIndex index){
        ViewData* data =_model->findAt(index.row());
        _currentId = data->_serisId;
        _delegate->setSelectedRow(-1);//当切换选中行时，取消被搜索行的背景色
        qDebug()<<"current index id is ---------"<<data->_serisId ;
    });
    connect(_delegate,&CustomListDelegate::sigChangeCursor,this,[=](bool flg){
        if(flg){
            this->setCursor(Qt::PointingHandCursor);
        }else {

            this->setCursor(Qt::ArrowCursor);
        }
    });

    int scrossBarValue = ui->listView->verticalScrollBar()->value();
    _oldValue = scrossBarValue;
    if(scrossBarValue%15==0)//每页包含15行序列信息
    {
        _oldIndex = scrossBarValue/15;
    }
    else{
        _oldIndex = scrossBarValue/15+1;
    }

    connect(ui->listView->verticalScrollBar(),&QScrollBar::valueChanged,this,[=](int value){
        if(_isClickBtnToChange) return;
        qDebug()<<"verticalScrollBar value is ...."<<value;
        //判断是向上滑动还是向下滑动
        if(value-_oldValue>0){//向下滑动
            if(_amountPage<=7){

                if(value+15>=_amountNum)//总数据行数
                {
                    _navBtns->setCurrentPos(_amountPage,true);
                    _oldIndex = _amountPage;
                }else{
                    int idex = 0;
                    idex = value/15+1;//计算当前属于第几页
                    if(idex == _oldIndex) return;
                    qDebug()<<"index is -------"<<idex;
                    _navBtns->setCurrentPos(idex,true);
                    _oldIndex = idex;
                }
            }else{
                //由于最后一页可能不足15个，且listview最后一页显示的第一行并不是紧接着上一页的最后一行，而是包含了上一页的好几行
                //所以要特殊处理
                if(value+15>=_amountNum)//总数据行数
                {
                    _navBtns->setCurrentPos(7,true);
                    _oldIndex = _amountPage;
                }else{
                    int idex = 0;
                    idex = value/15+1;//计算当前属于第几页
                    if(idex == _oldIndex) return;
                    //大于3的时idex = 4,
                    qDebug()<<"index is -------"<<idex;
                    if(idex <=3)
                    {
                        _navBtns->setCurrentPos(idex,true);
                    }
                    if(idex >3){
                        //如果idex >= 总页数-3
                        if(idex <=_amountPage-3){
                            _navBtns->setCurrentPos(4,true);
                        }else{
                            if(idex == _amountPage -2)
                            {
                                _navBtns->setCurrentPos(5,true);
                            }
                            if(idex == _amountPage-1)
                            {
                                _navBtns->setCurrentPos(6,true);
                            }
                            else if(idex == _amountPage)
                            {
                                _navBtns->setCurrentPos(7,true);
                            }

                        }
                    }
                    _oldIndex = idex;
                }
            }

        }else if(value -_oldValue<0){//向上滑动
#if 1
            if(_amountPage<=7)//如果总页数小于或等于7
            {
                int idex = 0;
                if(value==14) {
                    idex = 1;
                }else{
                    idex = value/15+1;
                }
                if(idex == _oldIndex) return;
                _navBtns->setCurrentPos(idex,true);
                _oldIndex = idex;
            }else{
                int idex = 0;
                if(value==14) {
                    idex = 1;
                }else{
                    idex = value/15+1;
                }
                if(idex == _oldIndex) return;
                //大于3的时idex = 2 ,
                if(idex <=2)
                {
                    _navBtns->setCurrentPos(idex,true);
                }
                qDebug()<<"idex is ------------"<<idex;
                if(idex >2){
                    //如果当前在最后页
                    if(idex == _amountPage-1)
                    {
                        _navBtns->setCurrentPos(6,true);
                    }
                    else if(idex == _amountPage-2)
                    {
                        _navBtns->setCurrentPos(5,true);
                    }
                    else if(idex == _amountPage-3)
                    {
                        _navBtns->setCurrentPos(4,true);
                    }
                    else if(idex == _amountPage-4)
                    {
                        _navBtns->setCurrentPos(3,true);
                    }else
                    {
                        _navBtns->setCurrentPos(2,true);
                    }
                }
                _oldIndex = idex;
            }
#endif
        }

        _oldValue = value;
    });
    initUI();
    setListViewFont();
}

CustomListWidget::~CustomListWidget()
{
    delete ui;
}

void CustomListWidget::initUI()
{
    QDateTime current_date_time =  QDateTime::currentDateTime();
    QString importTime =  current_date_time.toString("yyyy/MM/dd hh:mm");
    QString finishtTime =  "--/--/--";

    for(int i = 0;i<104;i++)
    {
        if(i%2==0)
        {
            _model->append(QString("%1").arg(i),finishtTime,importTime,ViewData::AnnoStatus::UNANNOTATION,"./","{}");

        }else if(i%3==0){
            _model->append(QString("%1").arg(i),finishtTime,importTime,ViewData::AnnoStatus::ANNOFINISHED,"./","{}");
        }else {

            _model->append(QString("%1").arg(i),finishtTime,importTime,ViewData::AnnoStatus::ANNOTAINGING,"./","{}");
        }
    }
    int dicomDirsNum = 104;

    if(dicomDirsNum%15==0)//每页包含15行序列信息
    {
        _amountPage = dicomDirsNum/15;
    }
    else{
        _amountPage = dicomDirsNum/15+1;
    }

    _navBtns = new NavigateWidget(_amountPage);
    ui->containerLayout->addWidget(_navBtns);
    connect(_navBtns,&NavigateWidget::signalClickeIndex,this,[&](int index){
        _isClickBtnToChange = true;
        ui->listView->verticalScrollBar()->setValue(15*(index-1));
        _isClickBtnToChange = false;
        if(index == _amountPage){
            _oldValue = ui->listView->verticalScrollBar()->value();//获取最后一页的起始编号
        }else{
            _oldValue = 15*(index-1);
        }
        _oldIndex = index;
        //        qDebug()<<"_oldValue is "<<_oldValue;
        //        qDebug()<<"_oldIndex is "<<_oldIndex;
    });
}


void CustomListWidget::appendData(QList<ViewData> &datalist)
{
    _model->clear();
    ui->listView->update();
    ui->listView->reset();
    if(_navBtns){
        delete _navBtns;
        _navBtns = nullptr;
    }
    //获取总数量
    _amountNum = datalist.size();

    for(int i = 0;i<datalist.size();i++)
    {
        if(i%2==0)
        {
            _model->append(QString("%1").arg(datalist.at(i)._serisId),datalist.at(i)._finishTime,datalist.at(i)._importTime,datalist.at(i)._annotStatus,datalist.at(i)._address,datalist.at(i)._annResult);

        }else if(i%3==0){
            _model->append(QString("%1").arg(datalist.at(i)._serisId),datalist.at(i)._finishTime,datalist.at(i)._importTime,datalist.at(i)._annotStatus,datalist.at(i)._address,datalist.at(i)._annResult);
        }else {

            _model->append(QString("%1").arg(datalist.at(i)._serisId),datalist.at(i)._finishTime,datalist.at(i)._importTime,datalist.at(i)._annotStatus,datalist.at(i)._address,datalist.at(i)._annResult);
        }
    }
    int dicomDirsNum = datalist.size();

    if(dicomDirsNum%15==0)//每页包含15行序列信息
    {
        _amountPage = dicomDirsNum/15;
    }
    else{
        _amountPage = dicomDirsNum/15+1;
    }

    _navBtns = new NavigateWidget(_amountPage);
    ui->containerLayout->addWidget(_navBtns);
    connect(_navBtns,&NavigateWidget::signalClickeIndex,this,[&](int index){
        _isClickBtnToChange = true;
        ui->listView->verticalScrollBar()->setValue(15*(index-1));
        _isClickBtnToChange = false;
        if(index == _amountPage){
            _oldValue = ui->listView->verticalScrollBar()->value();//获取最后一页的起始编号
        }else{
            _oldValue = 15*(index-1);
        }
        _oldIndex = index;
        qDebug()<<"_oldValue is "<<_oldValue;
        qDebug()<<"_oldIndex is "<<_oldIndex;
    });

    int scrossBarValue = ui->listView->verticalScrollBar()->value();
    _oldValue = scrossBarValue;
    if(scrossBarValue%15==0)//每页包含15行序列信息
    {
        _oldIndex = scrossBarValue/15;
    }
    else{
        _oldIndex = scrossBarValue/15+1;
    }
}


void CustomListWidget::setListViewFont()
{
    QFont font;
    font.setWeight(15);
    font.setPixelSize(14);//设置字体大小
    ui->listView->setFont(font);
}

void CustomListWidget::updateHeaderWid()
{
    int headerWidth = ui->headerWidget->width()-ui->listView->verticalScrollBar()->width();
    int headerHeight = ui->headerWidget->height();
    int headerX = ui->headerWidget->rect().x();
    int headerY = ui->headerWidget->rect().y();
    ui->labelSerisId->setGeometry(headerX+50,headerY,120,headerHeight);
    ui->labelStatus->setGeometry(headerX+headerWidth/6,headerY,120,headerHeight);
    ui->labelTime->setGeometry(headerX+headerWidth/3,headerY,120,headerHeight);
    ui->labelImportTime->setGeometry(headerX+headerWidth*1/2,headerY,120,headerHeight);
    // qreal nHalf = (option.rect.width() - _nWidth * nCount - _nSpacing * (nCount - 1)) / 2.0;
    // button.rect = QRect(option.rect.left() + nHalf*2, option.rect.top() + nTop,  _nWidth, _nHeight);
    qreal nHalf = headerWidth-40*3-9*2;//此处要与delegate绘制的各个控件位置对应
    ui->labelOperation->setGeometry(headerX+nHalf,headerY,120,headerHeight);
}

void CustomListWidget::resizeEvent(QResizeEvent *event)
{

    updateHeaderWid();
}

void CustomListWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_C)
    {
        QClipboard *clipboard = QApplication::clipboard();   //获取系统剪贴板指针
        clipboard->setText(_currentId);
        QMessageBox box(QMessageBox::Information,tr("copy id"),_currentId);
        box.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
        box.button(QMessageBox::Cancel)->hide();
        int ret = box.exec();
    }
}

int CustomListWidget::serchSpecifySeris(QString sersiId)
{
    return _model->getIndexById(sersiId);
}

void CustomListWidget::moveToSpecifySeris(int idex)
{
    ui->listView->verticalScrollBar()->setValue(idex);
    setSearchedItemAt(idex);//设置搜索的行的背景
    //    QModelIndex modelIndex  = ui->listView->model()->index(idex,0);
    //    ui->listView->scrollTo(modelIndex);
}

void CustomListWidget::setSearchedItemAt(int idex)
{
    _delegate->setSelectedRow(idex);//设置搜索的行的背景
}

void CustomListWidget::slotOpenDir(int idex)
{
    ViewData* data =_model->findAt(idex);
    if(!data) return;
    QString serisDirPath = data->_address;
    qDebug()<<"dirpaht is ----"<<serisDirPath;
    bool ok = QDesktopServices::openUrl(QUrl(serisDirPath));

}

void CustomListWidget::slotCheck(int idex)
{

}

void CustomListWidget::slotDel(int idex)
{

}

void CustomListWidget::slotToAnno(int idex)
{

}
