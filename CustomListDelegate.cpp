#include "CustomListDelegate.h"
#include <QPainter>
#include <QApplication>
#include <QStyleOptionViewItem>
#include <QDebug>
#include <QMouseEvent>
#include <QToolTip>
#include <QEvent>

#pragma execution_character_set("utf-8")

CustomListDelegate::CustomListDelegate(CustomListModel *model, QObject *parent):
    QStyledItemDelegate(parent),
    _pScanButton(new QPushButton("查看")),
    _pEditButton(new QPushButton("编辑")),
    _pAnnButton(new QPushButton("去标注")),
    _pDelButton(new QPushButton("删除")),
    _pOpenDirButton(new QPushButton("打开文件位置")),
    _pSerisIdLabel(new QLabel),
    _pStatusLabel(new QLabel),
    _pTimeLabel(new QLabel),
    _nSpacing(30),
    _nWidth(40),
    _nHeight(36),
    _type(DELEGATE_RBK),
    _model(model)
{

    // 设置按钮正常、划过、按下样式
    _pScanButton->setStyleSheet("{border: 2px solid; background-color: black; image:url(:/Images/open);} \
                                QPushButton:hover {image:url(:/Images/openHover);} \
                                QPushButton:pressed {image:url(:/Images/openPressed);}");

                                _pEditButton->setStyleSheet("QPushButton {border: none; background-color: black; image:url(:/Images/delete);} \
                                                            QPushButton:hover {image:url(:/Images/deleteHover);} \
                                                            QPushButton:pressed {image:url(:/Images/deletePressed);}");
                                                            _pAnnButton->setStyleSheet("QPushButton {border: none; background-color: black; image:url(:/Images/delete);} \
                                                                                       QPushButton:hover {image:url(:/Images/deleteHover);} \
                                                                                       QPushButton:pressed {image:url(:/Images/deletePressed);}");
                                                                                       _list<< tr("to Ann") << tr("Scan")<<tr("edit")<<tr("delete")<<tr("open Location");
}

CustomListDelegate::~CustomListDelegate()
{

}

void CustomListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
#if 0
    Data* data =_model->findAt(index.row());
    if(data)
    {

        _form->setSerisId(static_cast<int>(data->_serisId));
        _form->setStatus(data->ANNOFINISHED);
        _form->setFinishTime(data->_finishTime);
        _form->resize(option.rect.width(), option.rect.height());
        qDebug()<<"width is "<<option.rect.width()<<"   height is"<<option.rect.height();
        if (option.state & QStyle::State_Selected)
        {
            _form->setSelected(true);
            qDebug()<<"item is selected....";
        }
        else
        {
            _form->setSelected(false);
            qDebug()<<"item is not selected....";
        }
        QPixmap pixmap=_form->grab();
        painter->drawPixmap(option.rect, pixmap);
        //        QApplication::style()->drawControl(QStyle::CE_ItemViewItem,  &button, painter, pWidget);
    }
    QStyledItemDelegate::paint(painter, option, index);
#endif
    //绘制背景色
    if(index.row()%2==0){
        painter->fillRect(option.rect,QBrush(QColor(23,32,37)));

    }else {
        painter->fillRect(option.rect,QBrush(QColor(12,17,20)));
    }
    //搜索到的行
    if((-1 != _SelectedRow)&&index.row()==_SelectedRow)
    {
        painter->fillRect(option.rect,QBrush(QColor(18,54,81)));
    }

#if 1
    //计算按钮显示区域
    int nCount = _list.count();
    qreal nHalf = (option.rect.width() - _nWidth * nCount - _nSpacing * (nCount - 1)) / 2.0;
    qreal nTop = (option.rect.height() - _nHeight) / 2.0;

    //    qDebug()<<"option.rect.width() is "<<option.rect.width()<<"  height is "<<option.rect.height()<<"nHalf is "<<nHalf;
    //计算label显示区域
    ViewData* data =_model->findAt(index.row());
    QPalette pal;
    pal.setBrush(QPalette::Active,QPalette::Text,QBrush(Qt::green));
    pal.setColor(QPalette::WindowText, QColor(255,255,255));
    QApplication::style()->drawItemText(painter,QRect(option.rect.left()+50,option.rect.top(),120,45),Qt::AlignVCenter ,pal,false,QString("%1").arg(data->_serisId),QPalette::Foreground);
    QString status ;
    switch (data->_annotStatus) {
    case ViewData::AnnoStatus::ANNOFINISHED:
        status = "已完成标注";
        pal.setColor(QPalette::WindowText, QColor(67,140,148));
        QApplication::style()->drawItemText(painter,QRect(option.rect.left()+option.rect.width()/6.0,option.rect.top(),120,45),Qt::AlignVCenter ,pal,false,status,QPalette::Foreground);
        break;
    case ViewData::AnnoStatus::ANNOTAINGING:
        status = "标注中";
        pal.setColor(QPalette::WindowText, QColor(231,157,33));
        QApplication::style()->drawItemText(painter,QRect(option.rect.left()+option.rect.width()/6.0,option.rect.top(),120,45),Qt::AlignVCenter ,pal,false,status,QPalette::Foreground);
        break;
    case ViewData::AnnoStatus::UNANNOTATION:
        status = "未标注";
        pal.setColor(QPalette::WindowText, QColor(255,255,255));
        QApplication::style()->drawItemText(painter,QRect(option.rect.left()+option.rect.width()/6.0,option.rect.top(),120,45),Qt::AlignVCenter ,pal,false,status,QPalette::Foreground);
        break;
    }
    pal.setColor(QPalette::WindowText, QColor(255,255,255));
    QApplication::style()->drawItemText(painter,QRect(option.rect.left()+option.rect.width()/3.0,option.rect.top(),145,45),Qt::AlignVCenter ,pal,false,QString("%1").arg(data->_finishTime),QPalette::Foreground);

    pal.setColor(QPalette::WindowText, QColor(255,255,255));
    QApplication::style()->drawItemText(painter,QRect(option.rect.left()+option.rect.width()*1/2.0,option.rect.top(),145,45),Qt::AlignVCenter ,pal,false,QString("%1").arg(data->_importTime),QPalette::Foreground);


    if(data->_annotStatus == ViewData::AnnoStatus::UNANNOTATION)
    {
#if 0
        // 绘制按钮.
        QStyleOptionButton button;

        button.rect = QRect(option.rect.left() + nHalf*2,
                            option.rect.top() + nTop,  _nWidth, _nHeight);
        button.state |= QStyle::State_Enabled;

        if (button.rect.contains(_mousePoint))
        {
            if (_nType == 0)
            {
                button.state |= QStyle::State_MouseOver;//hover
            }
            else if (_nType == 1)
            {
                button.state |= QStyle::State_Sunken;//press
            }
        }
        //        QWidget *pWidget =  _pAnnButton.data();
        //        QApplication::style()->drawControl(QStyle::CE_PushButton, &button, painter, pWidget);
        pal.setColor(QPalette::WindowText, QColor(59,121,129));
        QApplication::style()->drawItemText(painter,button.rect,Qt::AlignHCenter|Qt::AlignVCenter ,pal,false,QString("去标注"),QPalette::Foreground);

#endif
        for (int i = 0; i < 3; ++i)
        {
            // 绘制按钮.
            QStyleOptionButton button;

            if(i==0){
                button.rect = QRect(option.rect.left() + nHalf*2 + _nWidth * (i-2) + _nSpacing * i,
                                    option.rect.top() + nTop,  _nWidth+15, _nHeight);
//                button.rect = QRect(option.rect.left() + nHalf*2 + _nWidth * (i-1) + _nSpacing * 1,
//                                    option.rect.top() + nTop,  _nWidth+15, _nHeight);
            }else if(i == 1){
                button.rect = QRect(option.rect.left() + nHalf*2 + _nWidth*(i-1) + _nSpacing*i*2,
                                    option.rect.top() + nTop,  _nWidth, _nHeight);
            }else if(i==2)
            {
                button.rect = QRect(option.rect.left() + nHalf*2 + _nWidth*(i-1) + _nSpacing*3,
                                    option.rect.top() + nTop,  _nWidth*2+30, _nHeight);
            }
            button.state |= QStyle::State_Enabled;
            if (button.rect.contains(_mousePoint))
            {
                if (_nType == 0)
                {
                    button.state |= QStyle::State_MouseOver;//hover
                }
                else if (_nType == 1)
                {
                    button.state |= QStyle::State_Sunken;//press
                }
            }
            switch (i) {
            case 0:
            {
                if(_buttonIndex==0&&_currentPressRow == index.row()){
                    pal.setColor(QPalette::WindowText, QColor(255,255,255));
                }else{
                    pal.setColor(QPalette::WindowText, QColor(59,121,129));
                }
                QApplication::style()->drawItemText(painter,button.rect,Qt::AlignHCenter|Qt::AlignVCenter ,pal,false,QString("去标注"),QPalette::Foreground);
            }
                break;
            case 1:
            {
                if(_buttonIndex==1&&_currentPressRow == index.row()){
                    pal.setColor(QPalette::WindowText, QColor(255,255,255));
                }else{
                    pal.setColor(QPalette::WindowText, QColor(86,88,89));
                }
                QApplication::style()->drawItemText(painter,button.rect,Qt::AlignLeft|Qt::AlignVCenter ,pal,false,QString("删除"),QPalette::Foreground);
            }
                break;
            case 2:
            {
                if(_buttonIndex==2&&_currentPressRow == index.row()){
                    pal.setColor(QPalette::WindowText, QColor(255,255,255));
                }else{
                    pal.setColor(QPalette::WindowText, QColor(86,88,89));
                }
                QApplication::style()->drawItemText(painter,button.rect,Qt::AlignLeft|Qt::AlignVCenter ,pal,false,QString("打开所在位置"),QPalette::Foreground);
            }
                break;
            default:
                break;
            }
        }

    }
    else if(data->_annotStatus == ViewData::AnnoStatus::ANNOFINISHED||data->_annotStatus == ViewData::AnnoStatus::ANNOTAINGING)
    {
        for (int i = 0; i < 4; ++i)
        {
            // 绘制按钮.
            QStyleOptionButton button;
            if(i<3){
                button.rect = QRect(option.rect.left() + nHalf*2 + _nWidth * (i-2) + _nSpacing * i,
                                    option.rect.top() + nTop,  _nWidth, _nHeight);

            }else if(i==3){
                button.rect = QRect(option.rect.left() + nHalf*2 + _nWidth * (i-2) + _nSpacing * i,
                                    option.rect.top() + nTop,  _nWidth*2+30, _nHeight);
            }
            button.state |= QStyle::State_Enabled;
            if (button.rect.contains(_mousePoint))
            {
                if (_nType == 0)
                {
                    button.state |= QStyle::State_MouseOver;//hover
                }
                else if (_nType == 1)
                {
                    button.state |= QStyle::State_Sunken;//press
                }
            }

            switch (i) {
            case 0:
            {
                if(data->_annotStatus==ViewData::AnnoStatus::ANNOTAINGING) continue;
                if(_buttonIndex==3&&_currentPressRow == index.row()){
                    pal.setColor(QPalette::WindowText, QColor(255,255,255));
                }else{
                    pal.setColor(QPalette::WindowText, QColor(86,88,89));
                }
                QApplication::style()->drawItemText(painter,button.rect,Qt::AlignLeft|Qt::AlignVCenter ,pal,false,QString("查看"),QPalette::Foreground);
            }
                break;
            case 1:
            {
                if(_buttonIndex==4&&_currentPressRow == index.row()){
                    pal.setColor(QPalette::WindowText, QColor(255,255,255));
                }else{
                    pal.setColor(QPalette::WindowText, QColor(86,88,89));
                }
                QApplication::style()->drawItemText(painter,button.rect,Qt::AlignLeft|Qt::AlignVCenter ,pal,false,QString("编辑"),QPalette::Foreground);
            }
                break;
            case 2:
            {
                if(_buttonIndex==5&&_currentPressRow == index.row()){
                    pal.setColor(QPalette::WindowText, QColor(255,255,255));
                }else{
                    pal.setColor(QPalette::WindowText, QColor(86,88,89));
                }
                QApplication::style()->drawItemText(painter,button.rect,Qt::AlignLeft|Qt::AlignVCenter ,pal,false,QString("删除"),QPalette::Foreground);
            }
                break;
            case 3:
            {
                if(_buttonIndex==6&&_currentPressRow == index.row()){
                    pal.setColor(QPalette::WindowText, QColor(255,255,255));
                }else{
                    pal.setColor(QPalette::WindowText, QColor(86,88,89));
                }
                QApplication::style()->drawItemText(painter,button.rect,Qt::AlignLeft|Qt::AlignVCenter ,pal,false,QString("打开所在位置"),QPalette::Foreground);
            }
                break;
            default:
                break;
            }
        }

    }
    QStyledItemDelegate::paint(painter, option, index);
#endif
}

bool CustomListDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    qDebug()<<"---------------editorEvent-------------"<<index.row();
    _currentPressRow = index.row();
    _nType = -1;
    QMouseEvent *pEvent = static_cast<QMouseEvent *> (event);
    _mousePoint = pEvent->pos();

    int nCount = _list.count();
    int nHalf = (option.rect.width() - _nWidth * nCount - _nSpacing * (nCount - 1)) / 2;
    int nTop = (option.rect.height() - _nHeight) / 2;

    //还原鼠标光标
    emit sigChangeCursor(false);

    //计算label显示区域
    ViewData* data =_model->findAt(index.row());
    if(data->_annotStatus == ViewData::AnnoStatus::UNANNOTATION)
    {
#if 0
        QStyleOptionButton button;
        button.rect = QRect(option.rect.left() + nHalf*2 + _nWidth * 0 + _nSpacing * 0,
                            option.rect.top() + nTop,  _nWidth, _nHeight);
        // 鼠标不在按钮之上.
        if (!button.rect.contains(_mousePoint))
        {
            return false;
        }
        // 鼠标位于按钮之上.
        switch (event->type())
        {
        // 鼠标滑过.
        case QEvent::MouseMove:
        {
            _nType = 0;
            // 设置鼠标样式为手型
            //            QApplication::setOverrideCursor(Qt::PointingHandCursor);
            //             QToolTip::showText(pEvent->globalPos(), _list.at(0));
            break;
        }
        case QEvent::HoverEnter:
        {
            emit sigChangeCursor(true);
            qDebug()<<"----hover enter...";
            break;
        }
            // 鼠标按下.
        case QEvent::MouseButtonPress:
        {
            _nType = 1;
            break;
        }
            // 鼠标释放.
        case QEvent::MouseButtonRelease:
        {
            //去标注
            emit sigAnnData(index);
            qDebug()<<"go to ann....";
            break;
        }

        default:
            break;
        }
        return true;
#endif
        //标注和删除
#if 1
        for (int i = 0; i < 3; ++i)
        {
            QStyleOptionButton button;
            if(i==0){
                button.rect = QRect(option.rect.left() + nHalf*2 + _nWidth *(i-2) + _nSpacing * i,
                                    option.rect.top() + nTop,  _nWidth, _nHeight);
//                button.rect = QRect(option.rect.left() + nHalf*2 + _nWidth *(i-1) + _nSpacing * 1,
//                                    option.rect.top() + nTop,  _nWidth, _nHeight);
            }else if(i == 1){
                button.rect = QRect(option.rect.left() + nHalf*2 + _nWidth *(i-1) + _nSpacing *i*2,
                                    option.rect.top() + nTop,  _nWidth, _nHeight);
            }else if(i == 2)
            {
                button.rect = QRect(option.rect.left() + nHalf*2 + _nWidth*(i-1) + _nSpacing*3,
                                    option.rect.top() + nTop,  _nWidth*2+30, _nHeight);
            }
            // 鼠标不在按钮之上.
            if (!button.rect.contains(_mousePoint))
            {
                if(QToolTip::isVisible()){
                    QToolTip::hideText();
                }
                continue;
            }

            // 鼠标位于按钮之上.
            switch (event->type())
            {
            // 鼠标滑过.
            case QEvent::MouseMove:
            {
                _nType = 0;
                // 设置鼠标样式为手型
                emit sigChangeCursor(true);
                break;
            }
                // 鼠标按下.
            case QEvent::MouseButtonPress:
            {
                _buttonIndex = i;//记录未标注的按钮 0 1 2
                _nType = 1;
                break;
            }
                // 鼠标释放.
            case QEvent::MouseButtonRelease:
            {
                _buttonIndex = -1;//复位
                if (i == 0)
                {
                    qDebug()<<"go to edit...."<<index.row();
                    emit sigEditData(index.row());
                }
                else if(i == 1)
                {
                    qDebug()<<"go to delete...."<<index.row();
                    emit sigDelData(index.row());
                }else if(i == 2)
                {
                    qDebug()<<"go to open Dir...."<<index.row();
                    emit sigOpenDir(index.row());
                }
                break;
            }

            default:
                break;
            }
            return true;
        }
#endif

    }
    else if(data->_annotStatus == ViewData::AnnoStatus::ANNOFINISHED||data->_annotStatus == ViewData::AnnoStatus::ANNOTAINGING){

        for (int i = 0; i < 4; ++i)
        {
            QStyleOptionButton button;
            if(i<3){
                button.rect = QRect(option.rect.left() + nHalf*2 + _nWidth * (i-2) + _nSpacing * i,
                                    option.rect.top() + nTop,  _nWidth, _nHeight);
            }else{
                button.rect = QRect(option.rect.left() + nHalf*2 + _nWidth * (i-2) + _nSpacing * i,
                                    option.rect.top() + nTop,  _nWidth*2+30, _nHeight);
            }
            // 鼠标不在按钮之上.
            if (!button.rect.contains(_mousePoint))
            {
                if(QToolTip::isVisible()){
                    QToolTip::hideText();
                }
                continue;
            }

            // 鼠标位于按钮之上.
            switch (event->type())
            {
            // 鼠标滑过.
            case QEvent::MouseMove:
            {
                _nType = 0;
                // 设置鼠标样式为手型
                if(data->_annotStatus==ViewData::AnnoStatus::ANNOTAINGING) continue;
                emit sigChangeCursor(true);
                break;
            }
                // 鼠标按下.
            case QEvent::MouseButtonPress:
            {
                _buttonIndex = i+3;//记录已标注的按钮 3 4 5 6
                _nType = 1;
                break;
            }
                // 鼠标释放.
            case QEvent::MouseButtonRelease:
            {
                _buttonIndex = -1;//复位
                if (i == 0)
                {
                    if(data->_annotStatus==ViewData::AnnoStatus::ANNOTAINGING) continue;
                    qDebug()<<"go to scan...."<<index.row();
                    emit sigCheck(index.row());
                }
                else if(i == 1)
                {
                    qDebug()<<"go to edit...."<<index.row();
                    emit sigEditData(index.row());
                }else if(i == 2)
                {
                    qDebug()<<"go to delete...."<<index.row();
                    emit sigDelData(index.row());
                }else if(i == 3)
                {
                    qDebug()<<"go to open dir...."<<index.row();
                    emit sigOpenDir(index.row());
                }
                break;
            }

            default:
                break;
            }
            return true;
        }
    }

    return false;
}

void CustomListDelegate::setType(CustomListDelegate::Type type)
{

}

void CustomListDelegate::setButtonList(const QList<QPushButton *> &value)
{

}

void CustomListDelegate::setSelectedRow(int selectedRow)
{
    _SelectedRow = selectedRow;
}
