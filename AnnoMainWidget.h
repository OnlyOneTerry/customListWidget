#ifndef ANNOMAINWIDGET_H
#define ANNOMAINWIDGET_H

#include <QWidget>
#include "CustomListWidget.h"

namespace Ui {
class AnnoMainWidget;
}

class AnnoMainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AnnoMainWidget(QWidget *parent = 0);
    ~AnnoMainWidget();

private:
    Ui::AnnoMainWidget *ui;
    CustomListWidget* _listWidgt = nullptr;
};

#endif // ANNOMAINWIDGET_H
