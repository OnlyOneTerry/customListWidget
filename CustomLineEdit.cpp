#include "CustomLineEdit.h"
#include <QDebug>

CustomLineEdit::CustomLineEdit(QWidget *parent):QLineEdit(parent)
{
    setText(QStringLiteral("请输入要查询的序列号"));
}

void CustomLineEdit::focusInEvent(QFocusEvent *e)
{
    this->selectAll();
    qDebug()<<"---------focusInEvent----------";
    QLineEdit::focusInEvent(e);
}
