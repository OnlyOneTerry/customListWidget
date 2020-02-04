#include "StudentForm.h"
#include "ui_StudentForm.h"

StudentForm::StudentForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudentForm)
{
    ui->setupUi(this);
}

StudentForm::~StudentForm()
{
    delete ui;
}

void StudentForm::setName(const QString &name)
{
    ui->textEdit->setText(name);
}

void StudentForm::setSelected(bool selected)
{
    if(selected)
    {
        this->setStyleSheet("#StudentFrame{border:2px solid red;}");
    }
    else
    {
        this->setStyleSheet("#StudentFrame{border:none;}");
    }
}
