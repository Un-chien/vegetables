/********************************************************************************
** Form generated from reading UI file 'softkey.ui'
**
** Created: Fri Oct 7 23:25:51 2022
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOFTKEY_H
#define UI_SOFTKEY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SoftKey
{
public:
    QGridLayout *gridLayout;
    QPushButton *onepushButton;
    QPushButton *eightpushButton;
    QPushButton *fourpushButton;
    QPushButton *twopushButton;
    QPushButton *threepushButton;
    QPushButton *sixpushButton;
    QPushButton *fivepushButton;
    QPushButton *sevenpushButton;
    QPushButton *ninepushButton;
    QPushButton *confirmpushButton;
    QLineEdit *mylineEdit;
    QPushButton *deletepushButton;
    QPushButton *zeropushButton;

    void setupUi(QWidget *SoftKey)
    {
        if (SoftKey->objectName().isEmpty())
            SoftKey->setObjectName(QString::fromUtf8("SoftKey"));
        SoftKey->resize(284, 312);
        gridLayout = new QGridLayout(SoftKey);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        onepushButton = new QPushButton(SoftKey);
        onepushButton->setObjectName(QString::fromUtf8("onepushButton"));

        gridLayout->addWidget(onepushButton, 1, 0, 1, 1);

        eightpushButton = new QPushButton(SoftKey);
        eightpushButton->setObjectName(QString::fromUtf8("eightpushButton"));

        gridLayout->addWidget(eightpushButton, 3, 1, 1, 1);

        fourpushButton = new QPushButton(SoftKey);
        fourpushButton->setObjectName(QString::fromUtf8("fourpushButton"));

        gridLayout->addWidget(fourpushButton, 2, 0, 1, 1);

        twopushButton = new QPushButton(SoftKey);
        twopushButton->setObjectName(QString::fromUtf8("twopushButton"));

        gridLayout->addWidget(twopushButton, 1, 1, 1, 1);

        threepushButton = new QPushButton(SoftKey);
        threepushButton->setObjectName(QString::fromUtf8("threepushButton"));

        gridLayout->addWidget(threepushButton, 1, 2, 1, 1);

        sixpushButton = new QPushButton(SoftKey);
        sixpushButton->setObjectName(QString::fromUtf8("sixpushButton"));

        gridLayout->addWidget(sixpushButton, 2, 2, 1, 1);

        fivepushButton = new QPushButton(SoftKey);
        fivepushButton->setObjectName(QString::fromUtf8("fivepushButton"));

        gridLayout->addWidget(fivepushButton, 2, 1, 1, 1);

        sevenpushButton = new QPushButton(SoftKey);
        sevenpushButton->setObjectName(QString::fromUtf8("sevenpushButton"));

        gridLayout->addWidget(sevenpushButton, 3, 0, 1, 1);

        ninepushButton = new QPushButton(SoftKey);
        ninepushButton->setObjectName(QString::fromUtf8("ninepushButton"));

        gridLayout->addWidget(ninepushButton, 3, 2, 1, 1);

        confirmpushButton = new QPushButton(SoftKey);
        confirmpushButton->setObjectName(QString::fromUtf8("confirmpushButton"));

        gridLayout->addWidget(confirmpushButton, 4, 2, 1, 1);

        mylineEdit = new QLineEdit(SoftKey);
        mylineEdit->setObjectName(QString::fromUtf8("mylineEdit"));

        gridLayout->addWidget(mylineEdit, 0, 0, 1, 2);

        deletepushButton = new QPushButton(SoftKey);
        deletepushButton->setObjectName(QString::fromUtf8("deletepushButton"));

        gridLayout->addWidget(deletepushButton, 0, 2, 1, 1);

        zeropushButton = new QPushButton(SoftKey);
        zeropushButton->setObjectName(QString::fromUtf8("zeropushButton"));

        gridLayout->addWidget(zeropushButton, 4, 0, 1, 2);


        retranslateUi(SoftKey);

        QMetaObject::connectSlotsByName(SoftKey);
    } // setupUi

    void retranslateUi(QWidget *SoftKey)
    {
        SoftKey->setWindowTitle(QApplication::translate("SoftKey", "Form", 0, QApplication::UnicodeUTF8));
        onepushButton->setText(QApplication::translate("SoftKey", "1", 0, QApplication::UnicodeUTF8));
        eightpushButton->setText(QApplication::translate("SoftKey", "8", 0, QApplication::UnicodeUTF8));
        fourpushButton->setText(QApplication::translate("SoftKey", "4", 0, QApplication::UnicodeUTF8));
        twopushButton->setText(QApplication::translate("SoftKey", "2", 0, QApplication::UnicodeUTF8));
        threepushButton->setText(QApplication::translate("SoftKey", "3", 0, QApplication::UnicodeUTF8));
        sixpushButton->setText(QApplication::translate("SoftKey", "6", 0, QApplication::UnicodeUTF8));
        fivepushButton->setText(QApplication::translate("SoftKey", "5", 0, QApplication::UnicodeUTF8));
        sevenpushButton->setText(QApplication::translate("SoftKey", "7", 0, QApplication::UnicodeUTF8));
        ninepushButton->setText(QApplication::translate("SoftKey", "9", 0, QApplication::UnicodeUTF8));
        confirmpushButton->setText(QApplication::translate("SoftKey", "OK", 0, QApplication::UnicodeUTF8));
        deletepushButton->setText(QApplication::translate("SoftKey", "Del", 0, QApplication::UnicodeUTF8));
        zeropushButton->setText(QApplication::translate("SoftKey", "0", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SoftKey: public Ui_SoftKey {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOFTKEY_H
