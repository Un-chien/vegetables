#include "softkey.h"
#include "ui_softkey.h"

QString string;
QString m_string;
int flag;

SoftKey::SoftKey(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SoftKey)
{
    ui->setupUi(this);
}

SoftKey::~SoftKey()
{
    delete ui;
}

void SoftKey::on_onepushButton_clicked()
{
    string += "1";
    ui->mylineEdit->setText(string);
}


void SoftKey::on_twopushButton_clicked()
{
    string += "2";
    ui->mylineEdit->setText(string);
}


void SoftKey::on_threepushButton_clicked()
{
    string += "3";
    ui->mylineEdit->setText(string);
}


void SoftKey::on_fourpushButton_clicked()
{
    string += "4";
    ui->mylineEdit->setText(string);
}


void SoftKey::on_fivepushButton_clicked()
{
    string += "5";
    ui->mylineEdit->setText(string);
}


void SoftKey::on_sixpushButton_clicked()
{
    string += "6";
    ui->mylineEdit->setText(string);
}


void SoftKey::on_sevenpushButton_clicked()
{
    string += "7";
    ui->mylineEdit->setText(string);
}


void SoftKey::on_eightpushButton_clicked()
{
    string += "8";
    ui->mylineEdit->setText(string);
}


void SoftKey::on_ninepushButton_clicked()
{
    string += "9";
    ui->mylineEdit->setText(string);
}


void SoftKey::on_zeropushButton_clicked()
{
    string += "0";
    ui->mylineEdit->setText(string);
}


void SoftKey::on_deletepushButton_clicked()
{
    string = string.left(string.size() - 1);
    ui->mylineEdit->setText(string);
}


void SoftKey::on_confirmpushButton_clicked()
{
    m_string = string;
    //qDebug() << m_string;
    string.clear();
    ui->mylineEdit->clear();
    close();
    if(flag == 1)
    {
        emit Send1();
    }
    else if(flag == 2)
    {
        emit Send2();
    }
    else if(flag == 3)
    {
        emit Send3();
    }
    else if(flag == 4)
    {
        emit Send4();
    }
    else if(flag == 5)
    {
        emit Send5();
    }
    else
    {
        emit Send6();
    }
}

