#include "LIstItemForm.h"
#include "ui_LIstItemForm.h"

LIstItemForm::LIstItemForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LIstItemForm)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
}

LIstItemForm::~LIstItemForm()
{
    delete ui;
}
