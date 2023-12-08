/********************************************************************************
** Form generated from reading UI file 'monitor.ui'
**
** Created: Fri Oct 7 23:25:51 2022
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MONITOR_H
#define UI_MONITOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Monitor
{
public:
    QLabel *piclabel;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *wheatpushButton;
    QPushButton *ricepushButton;
    QPushButton *potatopushButton;

    void setupUi(QWidget *Monitor)
    {
        if (Monitor->objectName().isEmpty())
            Monitor->setObjectName(QString::fromUtf8("Monitor"));
        Monitor->resize(628, 398);
        piclabel = new QLabel(Monitor);
        piclabel->setObjectName(QString::fromUtf8("piclabel"));
        piclabel->setGeometry(QRect(170, 50, 261, 251));
        layoutWidget = new QWidget(Monitor);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(130, 350, 357, 29));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(50);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        wheatpushButton = new QPushButton(layoutWidget);
        wheatpushButton->setObjectName(QString::fromUtf8("wheatpushButton"));

        horizontalLayout->addWidget(wheatpushButton);

        ricepushButton = new QPushButton(layoutWidget);
        ricepushButton->setObjectName(QString::fromUtf8("ricepushButton"));

        horizontalLayout->addWidget(ricepushButton);

        potatopushButton = new QPushButton(layoutWidget);
        potatopushButton->setObjectName(QString::fromUtf8("potatopushButton"));

        horizontalLayout->addWidget(potatopushButton);


        retranslateUi(Monitor);

        QMetaObject::connectSlotsByName(Monitor);
    } // setupUi

    void retranslateUi(QWidget *Monitor)
    {
        Monitor->setWindowTitle(QApplication::translate("Monitor", "Form", 0, QApplication::UnicodeUTF8));
        piclabel->setText(QString());
        wheatpushButton->setText(QApplication::translate("Monitor", "wheat", 0, QApplication::UnicodeUTF8));
        ricepushButton->setText(QApplication::translate("Monitor", "rice", 0, QApplication::UnicodeUTF8));
        potatopushButton->setText(QApplication::translate("Monitor", "potato", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Monitor: public Ui_Monitor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MONITOR_H
