#ifndef DATAFORM_H
#define DATAFORM_H

#include <QWidget>
#include "CommonDataDefine.h"

namespace Ui {
class DataForm;
}

class DataForm : public QWidget
{
    Q_OBJECT

public:
    explicit DataForm(QWidget *parent = nullptr);
    ~DataForm();
    void setSerisId(int id);
    void setStatus(Data::AnnoStatus type);
    void setFinishTime(QString time);
    void setSelected(bool selected);
private:
    Ui::DataForm *ui;
};

#endif // DATAFORM_H
