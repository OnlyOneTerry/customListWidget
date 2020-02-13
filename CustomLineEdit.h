#ifndef CUSTOMLINEEDIT_H
#define CUSTOMLINEEDIT_H
#include <QLineEdit>
#include <QMouseEvent>

class CustomLineEdit: public QLineEdit
{
    Q_OBJECT
public:
    CustomLineEdit(QWidget *parent = nullptr);
    void focusInEvent(QFocusEvent *e);
    void focusOutEvent(QFocusEvent *e);
signals:
    void sigFocusIn();
    void sigFocusOut();
};

#endif // CUSTOMLINEEDIT_H
