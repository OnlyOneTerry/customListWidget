#include "CustomListWidget.h"
#include "ui_CustomListWidget.h"
#include <QDateTime>
#include <QScrollBar>
#include <QDebug>
#include <QSpacerItem>
#include <QMessageBox>

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
    //设置当listView为编辑状态
    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    connect(ui->listView,&QListView::clicked,this,[&](QModelIndex index){
        Data* data =_model->findAt(index.row());
        _currentId = data->_serisId;
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

        }else if(value -_oldValue<0){//向上滑动
#if 1
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

    for(int i = 0;i<1000;i++)
    {
        if(i%2==0)
        {
            _model->append(QString("%1").arg(i),finishtTime,importTime,Data::AnnoStatus::UNANNOTATION,"./","{}");

        }else if(i%3==0){
            _model->append(QString("%1").arg(i),finishtTime,importTime,Data::AnnoStatus::ANNOFINISHED,"./","{}");
        }else {

            _model->append(QString("%1").arg(i),finishtTime,importTime,Data::AnnoStatus::ANNOTAINGING,"./","{}");
        }
    }
    int dicomDirsNum = 1000;

    if(dicomDirsNum%15==0)//每页包含15行序列信息
    {
        _amountPage = dicomDirsNum/15;
    }
    else{
        _amountPage = dicomDirsNum/15+1;
    }

    _navBtns = new NavigateWidget(_amountPage);
    QSpacerItem* horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    ui->navLayout->addWidget(_navBtns);
    ui->navLayout->addSpacerItem(horizontalSpacer);
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
         QMessageBox::information(this,"title",QString("id is %1").arg(_currentId));
    }
}

int CustomListWidget::serchSpecifySeris(QString sersiId)
{
    return _model->getIndexById(sersiId);
}

void CustomListWidget::moveToSpecifySeris(int idex)
{
    ui->listView->verticalScrollBar()->setValue(idex);
}

void CustomListWidget::setSelectedItemAt(int idex)
{

}
