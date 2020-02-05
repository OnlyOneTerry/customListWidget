/********************************************************************************
** Form generated from reading UI file 'CustomListWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMLISTWIDGET_H
#define UI_CUSTOMLISTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CustomListWidget
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *headerWidget;
    QLabel *labelSerisId;
    QLabel *labelStatus;
    QLabel *labelTime;
    QLabel *labelOperation;
    QLabel *labelImportTime;
    QListView *listView;
    QWidget *navWidget;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *navLayout;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *CustomListWidget)
    {
        if (CustomListWidget->objectName().isEmpty())
            CustomListWidget->setObjectName(QString::fromUtf8("CustomListWidget"));
        CustomListWidget->resize(800, 680);
        CustomListWidget->setMinimumSize(QSize(800, 680));
        CustomListWidget->setAutoFillBackground(false);
        CustomListWidget->setStyleSheet(QString::fromUtf8("QWidget#CustomListWidget\n"
"{\n"
"  background-color:#000000;\n"
"}\n"
"\n"
"QWidget#headerWidget\n"
"{\n"
"  background-color:#0C1114;\n"
"  border-left: 1px solid gray;\n"
"  border-right: 1px solid gray;\n"
"  border-top: 0px solid gray;\n"
"  border-bottom: 0px solid gray;\n"
"}\n"
"\n"
"QLabel{\n"
" color:#FFFFFF\n"
"}\n"
"\n"
"QListView{\n"
"  border-left: 1px solid gray;\n"
"  border-right: 1px solid gray;\n"
"  border-top: 0px solid #172025;\n"
"  border-bottom: 1px solid gray;\n"
"  background-color:#172025;\n"
"}\n"
"\n"
"QScrollBar:vertical{\n"
"  background-color:black;\n"
"  width:8px;\n"
"}\n"
"QScrollBar::handle:vertical{\n"
"   background: white;\n"
"   min-height: 60px;\n"
"}\n"
"\n"
"QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {\n"
"     border: 0px solid grey;\n"
"     width: 0px;\n"
"     height: 0px;\n"
" }\n"
""));
        verticalLayout = new QVBoxLayout(CustomListWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        headerWidget = new QWidget(CustomListWidget);
        headerWidget->setObjectName(QString::fromUtf8("headerWidget"));
        headerWidget->setMinimumSize(QSize(0, 40));
        headerWidget->setMaximumSize(QSize(16777215, 40));
        labelSerisId = new QLabel(headerWidget);
        labelSerisId->setObjectName(QString::fromUtf8("labelSerisId"));
        labelSerisId->setGeometry(QRect(0, 0, 36, 16));
        labelSerisId->setWordWrap(false);
        labelStatus = new QLabel(headerWidget);
        labelStatus->setObjectName(QString::fromUtf8("labelStatus"));
        labelStatus->setGeometry(QRect(202, 0, 24, 16));
        labelTime = new QLabel(headerWidget);
        labelTime->setObjectName(QString::fromUtf8("labelTime"));
        labelTime->setGeometry(QRect(403, 0, 72, 16));
        labelOperation = new QLabel(headerWidget);
        labelOperation->setObjectName(QString::fromUtf8("labelOperation"));
        labelOperation->setGeometry(QRect(605, 0, 24, 16));
        labelImportTime = new QLabel(headerWidget);
        labelImportTime->setObjectName(QString::fromUtf8("labelImportTime"));
        labelImportTime->setGeometry(QRect(500, 0, 72, 15));

        verticalLayout->addWidget(headerWidget);

        listView = new QListView(CustomListWidget);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setMaximumSize(QSize(16777215, 600));
        listView->setAutoFillBackground(true);
        listView->setStyleSheet(QString::fromUtf8("QListView::item{\n"
" height:60px;\n"
"}"));
        listView->setLineWidth(0);
        listView->setModelColumn(0);
        listView->setBatchSize(50);
        listView->setSelectionRectVisible(true);

        verticalLayout->addWidget(listView);

        navWidget = new QWidget(CustomListWidget);
        navWidget->setObjectName(QString::fromUtf8("navWidget"));
        navWidget->setMinimumSize(QSize(0, 0));
        navWidget->setMaximumSize(QSize(16777215, 100));
        horizontalLayout = new QHBoxLayout(navWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        navLayout = new QHBoxLayout();
        navLayout->setSpacing(6);
        navLayout->setObjectName(QString::fromUtf8("navLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        navLayout->addItem(horizontalSpacer);


        horizontalLayout->addLayout(navLayout);


        verticalLayout->addWidget(navWidget);


        retranslateUi(CustomListWidget);

        QMetaObject::connectSlotsByName(CustomListWidget);
    } // setupUi

    void retranslateUi(QWidget *CustomListWidget)
    {
        CustomListWidget->setWindowTitle(QApplication::translate("CustomListWidget", "CustomListWidget", nullptr));
        labelSerisId->setText(QApplication::translate("CustomListWidget", "\345\272\217\345\210\227\345\217\267", nullptr));
        labelStatus->setText(QApplication::translate("CustomListWidget", "\347\212\266\346\200\201", nullptr));
        labelTime->setText(QApplication::translate("CustomListWidget", "\346\240\207\346\263\250\345\256\214\346\210\220\346\227\266\351\227\264", nullptr));
        labelOperation->setText(QApplication::translate("CustomListWidget", "\346\223\215\344\275\234", nullptr));
        labelImportTime->setText(QApplication::translate("CustomListWidget", "\345\257\274\345\205\245\346\227\266\351\227\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CustomListWidget: public Ui_CustomListWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMLISTWIDGET_H
