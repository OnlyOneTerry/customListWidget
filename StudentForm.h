#ifndef STUDENTFORM_H
#define STUDENTFORM_H

#include <QWidget>

namespace Ui {
class StudentForm;
}

class StudentForm : public QWidget
{
    Q_OBJECT

public:
    explicit StudentForm(QWidget *parent = nullptr);
    ~StudentForm();
    void setName(const QString &name);

    void setSelected(bool selected);

private:
    Ui::StudentForm *ui;
};

#endif // STUDENTFORM_H
