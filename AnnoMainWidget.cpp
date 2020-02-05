#include "AnnoMainWidget.h"
#include "ui_AnnoMainWidget.h"

AnnoMainWidget::AnnoMainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnnoMainWidget)
{
    ui->setupUi(this);
    _listWidgt = new CustomListWidget;
    ui->rightListWidget->layout()->addWidget(_listWidgt);
    _listWidgt->updateHeaderWid();
}

AnnoMainWidget::~AnnoMainWidget()
{
    delete ui;
}
