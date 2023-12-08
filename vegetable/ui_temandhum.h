/********************************************************************************
** Form generated from reading UI file 'temandhum.ui'
**
** Created: Fri Oct 7 23:25:51 2022
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEMANDHUM_H
#define UI_TEMANDHUM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TemandHum
{
public:
    QLineEdit *temlineEdit;
    QLineEdit *humlineEdit;
    QLabel *temlabel;
    QLabel *humlabel;
    QPushButton *temminButton;
    QPushButton *humminButton;
    QPushButton *refreshpushButton;
    QLabel *label;
    QLabel *label_2;
    QPushButton *temmaxButton;
    QPushButton *hummaxButton;
    QPushButton *pushButton_light;

    void setupUi(QWidget *TemandHum)
    {
        if (TemandHum->objectName().isEmpty())
            TemandHum->setObjectName(QString::fromUtf8("TemandHum"));
        TemandHum->resize(795, 503);
        temlineEdit = new QLineEdit(TemandHum);
        temlineEdit->setObjectName(QString::fromUtf8("temlineEdit"));
        temlineEdit->setGeometry(QRect(290, 160, 271, 41));
        QFont font;
        font.setPointSize(10);
        temlineEdit->setFont(font);
        humlineEdit = new QLineEdit(TemandHum);
        humlineEdit->setObjectName(QString::fromUtf8("humlineEdit"));
        humlineEdit->setGeometry(QRect(290, 280, 271, 41));
        humlineEdit->setFont(font);
        temlabel = new QLabel(TemandHum);
        temlabel->setObjectName(QString::fromUtf8("temlabel"));
        temlabel->setGeometry(QRect(0, 150, 291, 41));
        humlabel = new QLabel(TemandHum);
        humlabel->setObjectName(QString::fromUtf8("humlabel"));
        humlabel->setGeometry(QRect(0, 270, 291, 41));
        temminButton = new QPushButton(TemandHum);
        temminButton->setObjectName(QString::fromUtf8("temminButton"));
        temminButton->setGeometry(QRect(580, 170, 41, 21));
        humminButton = new QPushButton(TemandHum);
        humminButton->setObjectName(QString::fromUtf8("humminButton"));
        humminButton->setGeometry(QRect(580, 290, 41, 21));
        refreshpushButton = new QPushButton(TemandHum);
        refreshpushButton->setObjectName(QString::fromUtf8("refreshpushButton"));
        refreshpushButton->setGeometry(QRect(220, 410, 101, 31));
        label = new QLabel(TemandHum);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(620, 170, 31, 16));
        label_2 = new QLabel(TemandHum);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(620, 290, 31, 16));
        temmaxButton = new QPushButton(TemandHum);
        temmaxButton->setObjectName(QString::fromUtf8("temmaxButton"));
        temmaxButton->setGeometry(QRect(650, 170, 41, 21));
        hummaxButton = new QPushButton(TemandHum);
        hummaxButton->setObjectName(QString::fromUtf8("hummaxButton"));
        hummaxButton->setGeometry(QRect(650, 290, 41, 21));
        pushButton_light = new QPushButton(TemandHum);
        pushButton_light->setObjectName(QString::fromUtf8("pushButton_light"));
        pushButton_light->setGeometry(QRect(520, 410, 101, 31));

        retranslateUi(TemandHum);

        QMetaObject::connectSlotsByName(TemandHum);
    } // setupUi

    void retranslateUi(QWidget *TemandHum)
    {
        TemandHum->setWindowTitle(QApplication::translate("TemandHum", "Form", 0, QApplication::UnicodeUTF8));
        temlabel->setText(QApplication::translate("TemandHum", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt;\">temperature:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        humlabel->setText(QApplication::translate("TemandHum", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt;\">humidity:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        temminButton->setText(QApplication::translate("TemandHum", "min", 0, QApplication::UnicodeUTF8));
        humminButton->setText(QApplication::translate("TemandHum", "min", 0, QApplication::UnicodeUTF8));
        refreshpushButton->setText(QApplication::translate("TemandHum", "refresh", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("TemandHum", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">~</span></p><p align=\"center\"><br/></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("TemandHum", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">~</span></p><p align=\"center\"><br/></p></body></html>", 0, QApplication::UnicodeUTF8));
        temmaxButton->setText(QApplication::translate("TemandHum", "max", 0, QApplication::UnicodeUTF8));
        hummaxButton->setText(QApplication::translate("TemandHum", "max", 0, QApplication::UnicodeUTF8));
        pushButton_light->setText(QApplication::translate("TemandHum", "light", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TemandHum: public Ui_TemandHum {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEMANDHUM_H
