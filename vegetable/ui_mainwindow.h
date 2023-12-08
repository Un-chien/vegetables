/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Fri Oct 7 23:25:51 2022
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *temandhhumaction;
    QAction *illuminationaction;
    QAction *CO2action;
    QAction *monitoraction;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLCDNumber *lcdNumber;
    QPushButton *datepushButton;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(671, 501);
        temandhhumaction = new QAction(MainWindow);
        temandhhumaction->setObjectName(QString::fromUtf8("temandhhumaction"));
        illuminationaction = new QAction(MainWindow);
        illuminationaction->setObjectName(QString::fromUtf8("illuminationaction"));
        CO2action = new QAction(MainWindow);
        CO2action->setObjectName(QString::fromUtf8("CO2action"));
        monitoraction = new QAction(MainWindow);
        monitoraction->setObjectName(QString::fromUtf8("monitoraction"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lcdNumber = new QLCDNumber(centralwidget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));

        verticalLayout->addWidget(lcdNumber);

        datepushButton = new QPushButton(centralwidget);
        datepushButton->setObjectName(QString::fromUtf8("datepushButton"));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        datepushButton->setFont(font);

        verticalLayout->addWidget(datepushButton);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 671, 25));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addAction(monitoraction);
        menu->addAction(temandhhumaction);
        menu->addAction(illuminationaction);
        menu->addAction(CO2action);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        temandhhumaction->setText(QApplication::translate("MainWindow", "temandhum", 0, QApplication::UnicodeUTF8));
        illuminationaction->setText(QApplication::translate("MainWindow", "illumination", 0, QApplication::UnicodeUTF8));
        CO2action->setText(QApplication::translate("MainWindow", "CO2", 0, QApplication::UnicodeUTF8));
        monitoraction->setText(QApplication::translate("MainWindow", "monitor", 0, QApplication::UnicodeUTF8));
        datepushButton->setText(QString());
        menu->setTitle(QApplication::translate("MainWindow", "vegetables", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
