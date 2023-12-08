#include "monitor.h"
#include "ui_monitor.h"

Monitor::Monitor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Monitor)
{
    ui->setupUi(this);
}

Monitor::~Monitor()
{
    delete ui;
}

void Monitor::on_ricepushButton_clicked()
{
    QPixmap *ricepixmap = new QPixmap(":/image/rice.jpg");
    ui->piclabel->setScaledContents(true);
    ui->piclabel->setPixmap(*ricepixmap);
}


void Monitor::on_wheatpushButton_clicked()
{
    QPixmap *wheatpixmap = new QPixmap(":/image/wheat.jpg");
    ui->piclabel->setScaledContents(true);
    ui->piclabel->setPixmap(*wheatpixmap);
}


void Monitor::on_potatopushButton_clicked()
{
    QPixmap *potatopixmap = new QPixmap(":/image/potato.jpg");
    ui->piclabel->setScaledContents(true);
    ui->piclabel->setPixmap(*potatopixmap);
}

