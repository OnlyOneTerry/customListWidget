#ifndef CUSTOMLISTDELEGATE_H
#define CUSTOMLISTDELEGATE_H
#include <QStyledItemDelegate>
#include <QPushButton>
#include <QListView>
#include <QLabel>
#include "CustomListModel.h"

class CustomListDelegate: public QStyledItemDelegate
{
    Q_OBJECT
public:
    enum Type
    {
        DELEGATE_LOCAL,
        DELEGATE_RBK
    };
public:
    CustomListDelegate(CustomListModel *model, QObject *parent = nullptr);
    virtual ~CustomListDelegate();
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index);
    void setType(Type type);
    void setButtonList(const QList<QPushButton *> &value);
    void setSelectedRow(int selectedRow);
signals:
    void sigCheck(int row);//查看
    void sigEditData(int row);//编辑
    void sigAnnData(int row);//去标注
    void sigDelData(int row);//去删除
    void sigOpenDir(int row);//打开文件所在位置
    void sigChangeCursor(bool flag); //true means handCursor else means arrowCursor
private:
    QPoint _mousePoint;  // 鼠标位置.
    QScopedPointer<QPushButton> _pScanButton;//查看
    QScopedPointer<QPushButton> _pEditButton;//编辑
    QScopedPointer<QPushButton> _pAnnButton;//去标注
    QScopedPointer<QPushButton> _pDelButton;//去删除
    QScopedPointer<QPushButton> _pOpenDirButton;//打开文件夹路径
    QScopedPointer<QLabel> _pSerisIdLabel;
    QScopedPointer<QLabel> _pStatusLabel;
    QScopedPointer<QLabel> _pTimeLabel;
    QStringList _list;
    QList<QPushButton*>_buttonList;
    int _nSpacing;  // 按钮之间的间距.
    int _nWidth;  // 按钮宽度.
    int _nHeight;  // 按钮高度.
    int _nType;  // 按钮状态-1：划过 2：按下.
    Type _type;
    int _SelectedRow=-1;//当前搜索到的行
    CustomListModel *_model=nullptr;
    int  _buttonIndex = -1;//记录按下的是第几个按钮
    int  _currentPressRow = -1;
};


#endif // CUSTOMLISTDELEGATE_H
