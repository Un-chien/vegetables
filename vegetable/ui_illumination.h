/********************************************************************************
** Form generated from reading UI file 'illumination.ui'
**
** Created: Fri Oct 7 23:25:51 2022
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ILLUMINATION_H
#define UI_ILLUMINATION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDial>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Illumination
{
public:
    QDial *dial;
    QPushButton *pushButton;

    void setupUi(QWidget *Illumination)
    {
        if (Illumination->objectName().isEmpty())
            Illumination->setObjectName(QString::fromUtf8("Illumination"));
        Illumination->resize(567, 400);
        dial = new QDial(Illumination);
        dial->setObjectName(QString::fromUtf8("dial"));
        dial->setGeometry(QRect(300, 170, 251, 201));
        pushButton = new QPushButton(Illumination);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 10, 281, 41));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        pushButton->setFont(font);

        retranslateUi(Illumination);

        QMetaObject::connectSlotsByName(Illumination);
    } // setupUi

    void retranslateUi(QWidget *Illumination)
    {
        Illumination->setWindowTitle(QApplication::translate("Illumination", "Form", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Illumination", "Transmittance of light:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Illumination: public Ui_Illumination {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ILLUMINATION_H
