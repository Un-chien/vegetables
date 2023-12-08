#include "illumination.h"
#include "ui_illumination.h"

Illumination::Illumination(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Illumination)
{
    ui->setupUi(this);

    ui->dial->setNotchesVisible(true);
    ui->dial->setMinimum(0);
    ui->dial->setMaximum(255);
    ui->dial->setPageStep(5);
    //ui->dial->setNotchTarget(1);
}

Illumination::~Illumination()
{
    delete ui;
}

void Illumination::on_dial_actionTriggered()
{
    QString set_win_color;
    QString color_r(QString::number(255-ui->dial->value()));//获取dial刻度值并转化  QString
    QString color_g(QString::number(255-ui->dial->value()));
    QString color_b(QString::number(255-ui->dial->value()));
    //拼接得到qss语句，语句内容设置背景颜色
    set_win_color= QString("background-color:rgb(%1,%2,%3);").arg(color_r).arg(color_g).arg(color_b);
    color_r.clear();//清空 存储rgb颜色值的QString 语句
    color_g.clear();
    color_b.clear();
    this->setStyleSheet(set_win_color);//通过调用setStyleSheet()设置背景颜色
}

