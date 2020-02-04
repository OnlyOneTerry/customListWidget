#include "DataForm.h"
#include "ui_DataForm.h"
#pragma execution_character_set("utf-8")
DataForm::DataForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataForm)
{
    ui->setupUi(this);
}

DataForm::~DataForm()
{
    delete ui;
}

void DataForm::setSerisId(int id)
{
    ui->lableSerisId->setText(QString("%1").arg(id));
}

void DataForm::setStatus(Data::AnnoStatus type)
{
    switch (type) {
    case Data::AnnoStatus::ANNOFINISHED:
        ui->labelStatus->setText("标注已完成");
        break;
    case Data::AnnoStatus::ANNOTAINGING:
        ui->labelStatus->setText("标注中");
        break;
    case Data::AnnoStatus::UNANNOTATION:
        ui->labelStatus->setText("未标注");
        break;
    default:
        break;
    }
}

void DataForm::setFinishTime(QString time)
{
    ui->labelFinishTime->setText(time);
}

void DataForm::setSelected(bool selected)
{
    if(selected)
    {
        this->setStyleSheet("#DateForm{background-color:green;border:2px solid red;}");
    }
    else
    {
        this->setStyleSheet("#DateForm{border:none;}");
    }
}
