/********************************************************************************
** Form generated from reading UI file 'co2.ui'
**
** Created: Fri Oct 7 23:25:51 2022
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CO2_H
#define UI_CO2_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CO2
{
public:
    QLabel *label_warn;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *style_value_3;
    QLabel *state_value;

    void setupUi(QWidget *CO2)
    {
        if (CO2->objectName().isEmpty())
            CO2->setObjectName(QString::fromUtf8("CO2"));
        CO2->resize(664, 437);
        label_warn = new QLabel(CO2);
        label_warn->setObjectName(QString::fromUtf8("label_warn"));
        label_warn->setGeometry(QRect(210, 60, 231, 51));
        label_2 = new QLabel(CO2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(80, 170, 121, 61));
        label_3 = new QLabel(CO2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(80, 250, 121, 61));
        style_value_3 = new QLabel(CO2);
        style_value_3->setObjectName(QString::fromUtf8("style_value_3"));
        style_value_3->setGeometry(QRect(290, 170, 151, 61));
        state_value = new QLabel(CO2);
        state_value->setObjectName(QString::fromUtf8("state_value"));
        state_value->setGeometry(QRect(290, 250, 151, 61));

        retranslateUi(CO2);

        QMetaObject::connectSlotsByName(CO2);
    } // setupUi

    void retranslateUi(QWidget *CO2)
    {
        CO2->setWindowTitle(QApplication::translate("CO2", "Form", 0, QApplication::UnicodeUTF8));
        label_warn->setText(QApplication::translate("CO2", "<html><head/><body><p align=\"center\"><span style=\" font-size:28pt;\">Warning</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("CO2", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt;\">Style:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("CO2", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt;\">State:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        style_value_3->setText(QApplication::translate("CO2", "<html><head/><body><p align=\"center\"><br/></p></body></html>", 0, QApplication::UnicodeUTF8));
        state_value->setText(QApplication::translate("CO2", "<html><head/><body><p align=\"center\"><br/></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CO2: public Ui_CO2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CO2_H
