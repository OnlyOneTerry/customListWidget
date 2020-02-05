/********************************************************************************
** Form generated from reading UI file 'DataForm.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAFORM_H
#define UI_DATAFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataForm
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *lableSerisId;
    QSpacerItem *horizontalSpacer_2;
    QLabel *labelStatus;
    QSpacerItem *horizontalSpacer;
    QLabel *labelFinishTime;
    QPushButton *goAnnoBtn;
    QPushButton *scanBtn;
    QPushButton *eidtBtn;

    void setupUi(QWidget *DataForm)
    {
        if (DataForm->objectName().isEmpty())
            DataForm->setObjectName(QString::fromUtf8("DataForm"));
        DataForm->resize(287, 62);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DataForm->sizePolicy().hasHeightForWidth());
        DataForm->setSizePolicy(sizePolicy);
        DataForm->setMinimumSize(QSize(0, 0));
        DataForm->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout = new QVBoxLayout(DataForm);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lableSerisId = new QLabel(DataForm);
        lableSerisId->setObjectName(QString::fromUtf8("lableSerisId"));

        horizontalLayout->addWidget(lableSerisId);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        labelStatus = new QLabel(DataForm);
        labelStatus->setObjectName(QString::fromUtf8("labelStatus"));

        horizontalLayout->addWidget(labelStatus);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        labelFinishTime = new QLabel(DataForm);
        labelFinishTime->setObjectName(QString::fromUtf8("labelFinishTime"));

        horizontalLayout->addWidget(labelFinishTime);

        goAnnoBtn = new QPushButton(DataForm);
        goAnnoBtn->setObjectName(QString::fromUtf8("goAnnoBtn"));
        goAnnoBtn->setMinimumSize(QSize(0, 60));

        horizontalLayout->addWidget(goAnnoBtn);

        scanBtn = new QPushButton(DataForm);
        scanBtn->setObjectName(QString::fromUtf8("scanBtn"));
        scanBtn->setMinimumSize(QSize(0, 60));

        horizontalLayout->addWidget(scanBtn);

        eidtBtn = new QPushButton(DataForm);
        eidtBtn->setObjectName(QString::fromUtf8("eidtBtn"));
        eidtBtn->setMinimumSize(QSize(0, 60));

        horizontalLayout->addWidget(eidtBtn);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(DataForm);

        QMetaObject::connectSlotsByName(DataForm);
    } // setupUi

    void retranslateUi(QWidget *DataForm)
    {
        DataForm->setWindowTitle(QApplication::translate("DataForm", "Form", nullptr));
        lableSerisId->setText(QString());
        labelStatus->setText(QString());
        labelFinishTime->setText(QString());
        goAnnoBtn->setText(QApplication::translate("DataForm", "\345\216\273\346\240\207\346\263\250", nullptr));
        scanBtn->setText(QApplication::translate("DataForm", "\346\237\245\347\234\213", nullptr));
        eidtBtn->setText(QApplication::translate("DataForm", "\347\274\226\350\276\221", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DataForm: public Ui_DataForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAFORM_H
