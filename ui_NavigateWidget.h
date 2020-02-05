/********************************************************************************
** Form generated from reading UI file 'NavigateWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NAVIGATEWIDGET_H
#define UI_NAVIGATEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NavigateWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnBefore;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    QPushButton *btn4;
    QPushButton *btn5;
    QPushButton *btnHides;
    QPushButton *btnLast;
    QPushButton *btnNext;

    void setupUi(QWidget *NavigateWidget)
    {
        if (NavigateWidget->objectName().isEmpty())
            NavigateWidget->setObjectName(QString::fromUtf8("NavigateWidget"));
        NavigateWidget->resize(420, 44);
        NavigateWidget->setMinimumSize(QSize(400, 40));
        NavigateWidget->setMaximumSize(QSize(420, 44));
        NavigateWidget->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"  max-height:40;\n"
"  max-width:40;\n"
"  min-height:40;\n"
"  min-width:40;\n"
"  background-color:#172025;\n"
"  color:#616266;\n"
"}"));
        verticalLayout = new QVBoxLayout(NavigateWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnBefore = new QPushButton(NavigateWidget);
        btnBefore->setObjectName(QString::fromUtf8("btnBefore"));

        horizontalLayout->addWidget(btnBefore);

        btn1 = new QPushButton(NavigateWidget);
        btn1->setObjectName(QString::fromUtf8("btn1"));
        btn1->setStyleSheet(QString::fromUtf8("background-color: rgb(23, 32, 37);"));

        horizontalLayout->addWidget(btn1);

        btn2 = new QPushButton(NavigateWidget);
        btn2->setObjectName(QString::fromUtf8("btn2"));
        btn2->setMinimumSize(QSize(42, 42));
        btn2->setMaximumSize(QSize(42, 42));

        horizontalLayout->addWidget(btn2);

        btn3 = new QPushButton(NavigateWidget);
        btn3->setObjectName(QString::fromUtf8("btn3"));

        horizontalLayout->addWidget(btn3);

        btn4 = new QPushButton(NavigateWidget);
        btn4->setObjectName(QString::fromUtf8("btn4"));

        horizontalLayout->addWidget(btn4);

        btn5 = new QPushButton(NavigateWidget);
        btn5->setObjectName(QString::fromUtf8("btn5"));

        horizontalLayout->addWidget(btn5);

        btnHides = new QPushButton(NavigateWidget);
        btnHides->setObjectName(QString::fromUtf8("btnHides"));

        horizontalLayout->addWidget(btnHides);

        btnLast = new QPushButton(NavigateWidget);
        btnLast->setObjectName(QString::fromUtf8("btnLast"));

        horizontalLayout->addWidget(btnLast);

        btnNext = new QPushButton(NavigateWidget);
        btnNext->setObjectName(QString::fromUtf8("btnNext"));

        horizontalLayout->addWidget(btnNext);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(NavigateWidget);

        QMetaObject::connectSlotsByName(NavigateWidget);
    } // setupUi

    void retranslateUi(QWidget *NavigateWidget)
    {
        NavigateWidget->setWindowTitle(QApplication::translate("NavigateWidget", "NavigateWidget", nullptr));
        btnBefore->setText(QApplication::translate("NavigateWidget", "<", nullptr));
        btn1->setText(QApplication::translate("NavigateWidget", "1", nullptr));
        btn2->setText(QApplication::translate("NavigateWidget", "2", nullptr));
        btn3->setText(QApplication::translate("NavigateWidget", "3", nullptr));
        btn4->setText(QApplication::translate("NavigateWidget", "4", nullptr));
        btn5->setText(QApplication::translate("NavigateWidget", "5", nullptr));
        btnHides->setText(QApplication::translate("NavigateWidget", "...", nullptr));
        btnLast->setText(QApplication::translate("NavigateWidget", "last", nullptr));
        btnNext->setText(QApplication::translate("NavigateWidget", ">", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NavigateWidget: public Ui_NavigateWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NAVIGATEWIDGET_H
