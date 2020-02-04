#ifndef CUSTOMLISTDELEGATE_H
#define CUSTOMLISTDELEGATE_H
#include <QStyledItemDelegate>
#include <QPushButton>
#include <QListView>
#include <QLabel>
#include "DataForm.h"
#include "CustomListModel.h"
#include "StudentForm.h"


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
signals:
    void sigScan(const QModelIndex &index);//查看
    void sigEditData(const QModelIndex &index);//编辑
    void sigAnnData(const QModelIndex &index);//去标注
    void sigDelData(const QModelIndex& index);//去删除
    void sigChangeCursor(bool flag); //true means handCursor else means arrowCursor
private:
    QPoint _mousePoint;  // 鼠标位置.
    QScopedPointer<QPushButton> _pScanButton;//查看
    QScopedPointer<QPushButton> _pEditButton;//编辑
    QScopedPointer<QPushButton> _pAnnButton;//去标注
    QScopedPointer<QPushButton> _pDelButton;//去删除
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

    CustomListModel *_model=nullptr;
    DataForm* _form;
};


#endif // CUSTOMLISTDELEGATE_H
