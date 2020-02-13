#include "CustomLineEdit.h"
#include <QDebug>

CustomLineEdit::CustomLineEdit(QWidget *parent):QLineEdit(parent)
{
    setText(QStringLiteral("请输入要查询的序列号"));
}

void CustomLineEdit::focusInEvent(QFocusEvent *e)
{
    qDebug()<<"---------focusInEvent----------";
    emit sigFocusIn();
    QLineEdit::focusInEvent(e);
}

void CustomLineEdit::focusOutEvent(QFocusEvent *e)
{
    qDebug()<<"---------focusOutEvent----------";
    emit sigFocusOut();
    QLineEdit::focusOutEvent(e);
}
