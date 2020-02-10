#ifndef CUSTOMLINEEDIT_H
#define CUSTOMLINEEDIT_H
#include <QLineEdit>
#include <QMouseEvent>

class CustomLineEdit: public QLineEdit
{
public:
    CustomLineEdit(QWidget *parent = nullptr);
    void focusInEvent(QFocusEvent *e);
};

#endif // CUSTOMLINEEDIT_H
