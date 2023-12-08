/********************************************************************************
** Form generated from reading UI file 'logwidget.ui'
**
** Created: Fri Oct 7 23:25:51 2022
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGWIDGET_H
#define UI_LOGWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Logwidget
{
public:
    QLabel *logonlabel;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLineEdit *namelineEdit;
    QLineEdit *passwordlineEdit;
    QLabel *namelabel;
    QLabel *passwordlabel;
    QPushButton *namepushButton;
    QPushButton *passwordpushButton;
    QHBoxLayout *horizontalLayout;
    QCheckBox *namecheckBox;
    QCheckBox *passwordcheckBox;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *longonpushButton;
    QPushButton *resetpushButton;

    void setupUi(QWidget *Logwidget)
    {
        if (Logwidget->objectName().isEmpty())
            Logwidget->setObjectName(QString::fromUtf8("Logwidget"));
        Logwidget->setEnabled(true);
        Logwidget->resize(860, 420);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Logwidget->sizePolicy().hasHeightForWidth());
        Logwidget->setSizePolicy(sizePolicy);
        Logwidget->setMinimumSize(QSize(860, 420));
        Logwidget->setMaximumSize(QSize(860, 420));
        logonlabel = new QLabel(Logwidget);
        logonlabel->setObjectName(QString::fromUtf8("logonlabel"));
        logonlabel->setGeometry(QRect(0, 10, 861, 131));
        sizePolicy.setHeightForWidth(logonlabel->sizePolicy().hasHeightForWidth());
        logonlabel->setSizePolicy(sizePolicy);
        logonlabel->setScaledContents(false);
        layoutWidget = new QWidget(Logwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(50, 150, 761, 271));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, -1, 100, -1);
        namelineEdit = new QLineEdit(layoutWidget);
        namelineEdit->setObjectName(QString::fromUtf8("namelineEdit"));
        QFont font;
        font.setPointSize(14);
        namelineEdit->setFont(font);

        gridLayout->addWidget(namelineEdit, 0, 1, 1, 1);

        passwordlineEdit = new QLineEdit(layoutWidget);
        passwordlineEdit->setObjectName(QString::fromUtf8("passwordlineEdit"));
        passwordlineEdit->setFont(font);

        gridLayout->addWidget(passwordlineEdit, 1, 1, 1, 1);

        namelabel = new QLabel(layoutWidget);
        namelabel->setObjectName(QString::fromUtf8("namelabel"));

        gridLayout->addWidget(namelabel, 0, 0, 1, 1);

        passwordlabel = new QLabel(layoutWidget);
        passwordlabel->setObjectName(QString::fromUtf8("passwordlabel"));

        gridLayout->addWidget(passwordlabel, 1, 0, 1, 1);

        namepushButton = new QPushButton(layoutWidget);
        namepushButton->setObjectName(QString::fromUtf8("namepushButton"));

        gridLayout->addWidget(namepushButton, 0, 2, 1, 1);

        passwordpushButton = new QPushButton(layoutWidget);
        passwordpushButton->setObjectName(QString::fromUtf8("passwordpushButton"));

        gridLayout->addWidget(passwordpushButton, 1, 2, 1, 1);

        gridLayout->setColumnStretch(0, 1);

        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(100);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(200, -1, 100, -1);
        namecheckBox = new QCheckBox(layoutWidget);
        namecheckBox->setObjectName(QString::fromUtf8("namecheckBox"));

        horizontalLayout->addWidget(namecheckBox);

        passwordcheckBox = new QCheckBox(layoutWidget);
        passwordcheckBox->setObjectName(QString::fromUtf8("passwordcheckBox"));

        horizontalLayout->addWidget(passwordcheckBox);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(100);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(150, 0, 150, -1);
        longonpushButton = new QPushButton(layoutWidget);
        longonpushButton->setObjectName(QString::fromUtf8("longonpushButton"));

        horizontalLayout_2->addWidget(longonpushButton);

        resetpushButton = new QPushButton(layoutWidget);
        resetpushButton->setObjectName(QString::fromUtf8("resetpushButton"));

        horizontalLayout_2->addWidget(resetpushButton);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalLayout->setStretch(0, 2);
        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 1);

        retranslateUi(Logwidget);

        QMetaObject::connectSlotsByName(Logwidget);
    } // setupUi

    void retranslateUi(QWidget *Logwidget)
    {
        Logwidget->setWindowTitle(QApplication::translate("Logwidget", "Form", 0, QApplication::UnicodeUTF8));
        logonlabel->setText(QApplication::translate("Logwidget", "<html><head/><body><p align=\"center\"><span style=\" font-size:24pt; font-weight:600;\">Login</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        namelabel->setText(QApplication::translate("Logwidget", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt;\">User:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        passwordlabel->setText(QApplication::translate("Logwidget", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt;\">Password:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        namepushButton->setText(QApplication::translate("Logwidget", "keyboard", 0, QApplication::UnicodeUTF8));
        passwordpushButton->setText(QApplication::translate("Logwidget", "keyboard", 0, QApplication::UnicodeUTF8));
        namecheckBox->setText(QApplication::translate("Logwidget", "RememberU", 0, QApplication::UnicodeUTF8));
        passwordcheckBox->setText(QApplication::translate("Logwidget", "RememberP", 0, QApplication::UnicodeUTF8));
        longonpushButton->setText(QApplication::translate("Logwidget", "login", 0, QApplication::UnicodeUTF8));
        resetpushButton->setText(QApplication::translate("Logwidget", "reset", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Logwidget: public Ui_Logwidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGWIDGET_H
