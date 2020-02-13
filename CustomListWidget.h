#ifndef CUSTOMLISTWIDGET_H
#define CUSTOMLISTWIDGET_H

#include <QWidget>
#include "CustomListDelegate.h"
#include "CustomListModel.h"
#include "NavigateWidget.h"
#include <QResizeEvent>
#include <QKeyEvent>
#include <QSpacerItem>

namespace Ui {
class CustomListWidget;
}

class CustomListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CustomListWidget(QWidget *parent = nullptr);
    ~CustomListWidget();
    void initUI();
    void appendData(QList<ViewData>& datalist);
    void setListViewFont();
    void updateHeaderWid();
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *event);
    //search specify serisId
    int serchSpecifySeris(QString sersiId);
    void moveToSpecifySeris(int idex);
    void setSearchedItemAt(int idex);//设置当前inde项选中
signals:
    void sigToDeleteById(QString serisId);
    void sigToCheckById(QString serisId,QString serisDirPath);
    void sigToAnno(QString serisId,QString serisDirPath);
    void sigToEdit(QString serisId,QString serisDirPath);
public slots:
    void slotOpenDir(int idex);
    void slotEdit(int idex);
    void slotCheck(int idex);
    void slotDel(int idex);
    void slotToAnno(int idex);
private:
    Ui::CustomListWidget *ui;
    CustomListDelegate* _delegate;
    CustomListModel* _model;
    NavigateWidget* _navBtns;
    int _oldIndex = 0;
    int _oldValue = 0;//用于判断当前是value是增大还是减小（滚动条是向上滑动还是向下）
    bool _isClickBtnToChange = false;
    int _amountPage = 0;//总页数
    int _amountNum = 104;//总行数
    QString _currentId = 0;
};

#endif // CUSTOMLISTWIDGET_H
