#include "NavigateWidget.h"
#include "ui_NavigateWidget.h"
#include <QDebug>

NavigateWidget::NavigateWidget(int amount, QWidget *parent) :
    QWidget(parent),
    _amount(amount),
    ui(new Ui::NavigateWidget)
{
    ui->setupUi(this);
    //用于管理按钮
    _pBtnList.append(ui->btn1);
    _pBtnList.append(ui->btn2);
    _pBtnList.append(ui->btn3);
    _pBtnList.append(ui->btn4);
    _pBtnList.append(ui->btn5);
    _pBtnList.append(ui->btnHides);
    _pBtnList.append(ui->btnLast);
    initUI();
    selectItemChanged(1);//默认第一个选中
}

NavigateWidget::~NavigateWidget()
{
    delete ui;
}

void NavigateWidget::initUI()
{
    //判断当前总数量
    if(_amount>7)
    {
        ui->btnLast->setText(QString("%1").arg(_amount));
    }
    if(_amount==7)
    {
        ui->btnHides->setText("6");
        ui->btnLast->setText("7");
    }
    if(_amount==6)
    {
        ui->btnHides->setText("6");
        ui->btnLast->hide();
    }
    if(_amount<=5){

        //若总数小于等于5
        //显示相应数量
        //先隐藏
        foreach(auto var,_pBtnList)
        {
            var->hide();
        }
        for(int i =0;i<_amount;i++)
        {
            if(_pBtnList.at(i)->text().toInt()==i+1)
            {
                _pBtnList.at(i)->show();
            }
        }

    }
    //设置按钮颜色
    for(int i = 0;i<_pBtnList.size();i++)
    {
        _pBtnList.at(i)->setStyleSheet(QString("background-color:#172025;color:#616266"));

    }
}

void NavigateWidget::moveBtnDisplayTextNum(int moveStep)
{
    for(int i = 0;i<_pBtnList.size();i++)
    {
        int btnDisplayNum = _pBtnList.at(i)->text().toInt();

        int afterMoveDisplayNum= btnDisplayNum+moveStep;

        _pBtnList.at(i)->setText(QString("%1").arg(afterMoveDisplayNum));
    }
}

void NavigateWidget::setCurrentBtnHighLight(int currentIndex)
{
    qDebug()<<"highLight index is "<<currentIndex;
    for(int i = 0;i<_pBtnList.size();i++)
    {
        _pBtnList.at(i)->setStyleSheet(QString("background-color:#172025;color:#616266"));
        if(_pBtnList.at(i)->text().toInt()==currentIndex)
        {
            _pBtnList.at(i)->setStyleSheet(QString("background-color:#043B4F;color:white"));
            _currentHighLightIndex = i+1;
        }
    }
}

void NavigateWidget::btn1Clicked()
{
    _currentIndex  = ui->btn1->text().toInt();

    if(_amount<=7)
    {

    }else{
        if(ui->btn1->text().toInt()==1)
        {
            //不做移动
        }

        if(ui->btn1->text().toInt()==2)
        {
            //向后移动一个
            moveBtnDisplayTextNum(-1);
            //重置最后一个和倒数第二个
            ui->btnHides->setText("...");
            ui->btnLast->setText(QString("%1").arg(_amount));
        }

        if(ui->btn1->text().toInt()>=3)
        {
            //向后移动两个
            moveBtnDisplayTextNum(-2);
            //重置最后一个和倒数第二个
            ui->btnHides->setText("...");
            ui->btnLast->setText(QString("%1").arg(_amount));
        }
    }

    //移动后设置当前高亮
    setCurrentBtnHighLight(_currentIndex);


}

void NavigateWidget::btn2Clicked()
{
    _currentIndex  = ui->btn2->text().toInt();
    if(_amount<=7)
    {
    }
    else {
        if(ui->btn2->text().toInt()==2)
        {
            //不移动
        }

        if(ui->btn2->text().toInt()>=3)
        {
            //向后移动一个
            moveBtnDisplayTextNum(-1);
            //重置最后一个和倒数第二个
            ui->btnHides->setText("...");
            ui->btnLast->setText(QString("%1").arg(_amount));
        }
    }

    //移动后设置当前高亮
    setCurrentBtnHighLight(_currentIndex);
}

void NavigateWidget::btn3Clicked()
{
    _currentIndex  = ui->btn3->text().toInt();
    setCurrentBtnHighLight(_currentIndex);
    //不移动
}

void NavigateWidget::btn4Clicked()
{
    _currentIndex  = ui->btn4->text().toInt();

    if(_amount<=7)
    {

    }else {
        if(_amount-_currentIndex==3)
        {
            //不移动
            //重置最后一个和倒数第二个
            ui->btnHides->setText(QString("%1").arg(_amount-1));
            ui->btnLast->setText(QString("%1").arg(_amount));
        }

        if(_amount-_currentIndex==4)
        {
            //向前移一位
            moveBtnDisplayTextNum(1);
            //重置最后一个和倒数第二个
            ui->btnHides->setText(QString("%1").arg(_amount-1));
            ui->btnLast->setText(QString("%1").arg(_amount));
        }

        if(_amount-_currentIndex>4)
        {
            //向前移一位
            moveBtnDisplayTextNum(1);
            //重置最后一个和倒数第二个
            ui->btnHides->setText("...");
            ui->btnLast->setText(QString("%1").arg(_amount));
        }
    }


    //移动后设置当前高亮
    setCurrentBtnHighLight(_currentIndex);

}

void NavigateWidget::btn5Clicked()
{
    _currentIndex  = ui->btn5->text().toInt();

    if(_amount<=7)
    {


    }else{
        if(_amount-_currentIndex<=2)
        {
            //不移动
        }

        if(_amount-_currentIndex==3)
        {
            //向前移动一位
            moveBtnDisplayTextNum(1);
            //重置最后一个和倒数第二个
            ui->btnHides->setText(QString("%1").arg(_amount-1));
            ui->btnLast->setText(QString("%1").arg(_amount));
        }


        if(_amount-_currentIndex==4)
        {
            //向前移动两位
            moveBtnDisplayTextNum(2);
            //重置最后一个和倒数第二个
            ui->btnHides->setText(QString("%1").arg(_amount-1));
            ui->btnLast->setText(QString("%1").arg(_amount));
        }

        if(_amount-_currentIndex>4)
        {
            //向前移动两位
            moveBtnDisplayTextNum(2);
            //重置最后一个和倒数第二个
            ui->btnHides->setText("...");
            ui->btnLast->setText(QString("%1").arg(_amount));
        }
    }

    //移动后设置当前高亮
    setCurrentBtnHighLight(_currentIndex);
}

void NavigateWidget::btnHidesClicked()
{
    if(ui->btnHides->text()=="...")
    {
        return;
    }

    _currentIndex = ui->btnHides->text().toInt();
    setCurrentBtnHighLight(_currentIndex);
}

void NavigateWidget::btnLastClicked()
{
    _currentIndex  = ui->btnLast->text().toInt();
    setCurrentBtnHighLight(_currentIndex);
    if(ui->btnHides->text()=="...")
    {
        for(int i = 0;i<_pBtnList.size();i++)
        {
            _pBtnList.at(i)->setText(QString("%1").arg(_amount-6+i));
        }
    }
}

void NavigateWidget::selectItemChanged(int idex, bool isScrollBarChange)
{
    switch (idex) {
    case 1:
        btn1Clicked();
        break;
    case 2:
        btn2Clicked();
        break;
    case 3:
        btn3Clicked();
        break;
    case 4:
        btn4Clicked();
        break;
    case 5:
        btn5Clicked();
        break;
    case 6:
        btnHidesClicked();
        break;
    case 7:
        btnLastClicked();
        break;
    default:
        break;
    }
    if(!isScrollBarChange){//如果是点击按钮切换
        emit signalClickeIndex(_currentIndex);
    }
}

void NavigateWidget::setCurrentPos(int index, bool isScrollBarChange)
{
    if(isScrollBarChange)
    {
        selectItemChanged(index,isScrollBarChange);
    }
}

void NavigateWidget::on_btnBefore_clicked()
{
    _currentPressIndex--;
    if(_currentPressIndex<=1)
    {
        _currentPressIndex =1;
    }
    if(_amount>2){

        if(_currentHighLightIndex==3)//当前高亮在第三个按钮
        {
            _currentPressIndex = 2;
        }
    }
    qDebug()<<"before index is ----"<<_currentPressIndex;
    selectItemChanged(_currentPressIndex);
}

void NavigateWidget::on_btn1_clicked()
{
//    btn1Clicked();
    selectItemChanged(1);
    _currentPressIndex = 1;
}

void NavigateWidget::on_btn2_clicked()
{
//    btn2Clicked();
    selectItemChanged(2);
    _currentPressIndex = 2;
}

void NavigateWidget::on_btn3_clicked()
{
//    btn3Clicked();
    selectItemChanged(3);
    _currentPressIndex = 3;
}

void NavigateWidget::on_btn4_clicked()
{
//    btn4Clicked();
    selectItemChanged(4);
    _currentPressIndex = 4;
}

void NavigateWidget::on_btn5_clicked()
{

//    btn5Clicked();
    selectItemChanged(5);
    _currentPressIndex = 5;
}

void NavigateWidget::on_btnHides_clicked()
{
//    btnHidesClicked();
    selectItemChanged(6);
    _currentPressIndex = 6;
}

void NavigateWidget::on_btnLast_clicked()
{
//    btnLastClicked();
    selectItemChanged(7);
    _currentPressIndex = 7;
}

void NavigateWidget::on_btnNext_clicked()
{
    _currentPressIndex++;

    if(_amount>=7)
    {
        if(_currentPressIndex>=4)
        {
            if(ui->btnHides->text()=="...")
            {
                _currentPressIndex = 4;
            }else{
                //判断当前高亮在第三个按钮则仍需设置为4
                if(_currentHighLightIndex == 3)
                {
                    _currentPressIndex = 4;
                }
            }

            if(_currentPressIndex>=7)
            {
                _currentPressIndex = 7;
            }
        }

        qDebug()<<"_currentPressIndex is "<<_currentPressIndex<<ui->btnHides->text();
        selectItemChanged(_currentPressIndex);
    }else{
        if(_currentPressIndex>=_amount)
        {
            _currentPressIndex=_amount;
        }
        selectItemChanged(_currentPressIndex);
    }
}
