#ifndef LISTITEMFORM_H
#define LISTITEMFORM_H

#include <QWidget>

namespace Ui {
class LIstItemForm;
}

class LIstItemForm : public QWidget
{
    Q_OBJECT

public:
    explicit LIstItemForm(QWidget *parent = 0);
    ~LIstItemForm();

private:
    Ui::LIstItemForm *ui;
};

#endif // LISTITEMFORM_H
