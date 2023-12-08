#include "co2.h"
#include "ui_co2.h"

#include <QDebug>
#include <QKeyEvent>
#include <QFile>
#include <unistd.h>
#include <math.h>
#include "server/api.h"
extern int gprs_fg;
CO2::CO2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CO2)
{
    ui->setupUi(this);

    {
        int_flag=0;
        smog_flag=0;
        irda_flag=0;
        connect(int_label,SIGNAL(clicked()),this,SLOT(int_show()));
        connect(smog_label,SIGNAL(clicked()),this,SLOT(smog_show()));
        connect(irda_label,SIGNAL(clicked()),this,SLOT(irda_show()));
    }


    char *ipaddr="192.168.12.26";//连接本地服务器，端口号是7838
    int port=7838;
    cliect_thread = new Cliect();
    cliect_thread->GetConnect(ipaddr,port);
//建立相关的信号槽
    connect(cliect_thread,SIGNAL(Int_StateChanged_1()),this,SLOT(Int_change_1()));//门磁传感器异常
    connect(cliect_thread,SIGNAL(Irda_StateChanged_1()),this,SLOT(Irda_change_1()));//红外对射传感器异常
    connect(cliect_thread,SIGNAL(Smog_StateChanged_1()),this,SLOT(Smog_change_1()));//烟雾传感器异常
    connect(cliect_thread,SIGNAL(Int_StateChanged_0()),this,SLOT(Int_change_0()));//门磁传感器正常
    connect(cliect_thread,SIGNAL(Irda_StateChanged_0()),this,SLOT(Irda_change_0()));//红外对射传感器正常
    connect(cliect_thread,SIGNAL(Smog_StateChanged_0()),this,SLOT(Smog_change_0()));//烟雾传感器正常
    connect(cliect_thread,SIGNAL(Sim(int )),this,SLOT(Set_Sim(int)));
    connect(cliect_thread,SIGNAL(Send(int)),this,SLOT(Set_Send(int)));

    connect(this,SIGNAL(Int_StateChanged_1()),this,SLOT(Int_change_1()));
    connect(this,SIGNAL(Irda_StateChanged_1()),this,SLOT(Irda_change_1()));
    connect(this,SIGNAL(Smog_StateChanged_1()),this,SLOT(Smog_change_1()));
    connect(this,SIGNAL(Int_StateChanged_0()),this,SLOT(Int_change_0()));
    connect(this,SIGNAL(Irda_StateChanged_0()),this,SLOT(Irda_change_0()));
    connect(this,SIGNAL(Smog_StateChanged_0()),this,SLOT(Smog_change_0()));

    cliect_thread->start();
    zb_thread = new ZigbeeTopo();

    Sim_state=0;
    //ui->state_sim->setText(QString::fromUtf8("未初始化"));
    cliect_thread->Api_Cliect_GetGPRSSignal();

}

CO2::~CO2()
{
    delete ui;
}
void CO2::int_show(){
        if(int_flag)
                {
                        ui->style_value_3->setText(QString::fromUtf8("门磁传感器"));
                        ui->state_value->setText(QString::fromUtf8("报警"));

                        ui->label_warn->update();
                        ui->style_value_3->update();
                        ui->state_value->update();
                        }
                else
                        {
                                ui->style_value_3->setText(QString::fromUtf8("门磁传感器"));
                                ui->state_value->setText(QString::fromUtf8("正常"));

                                ui->label_warn->update();
                                ui->style_value_3->update();
                                ui->state_value->update();
                                }
}
void CO2::smog_show(){
        if(smog_flag)
                {
                        ui->style_value_3->setText(QString::fromUtf8("烟雾传感器"));
                        ui->state_value->setText(QString::fromUtf8("报警"));

                        ui->label_warn->update();
                        ui->style_value_3->update();
                        ui->state_value->update();
                        }
                else
                        {
                                ui->style_value_3->setText(QString::fromUtf8("烟雾传感器"));
                                ui->state_value->setText(QString::fromUtf8("正常"));

                                ui->label_warn->update();
                                ui->style_value_3->update();
                                ui->state_value->update();
                                }
}
void CO2::irda_show(){
        if(irda_flag)
                {
                        ui->style_value_3->setText(QString::fromUtf8("红外对射传感器"));
                        ui->state_value->setText(QString::fromUtf8("报警"));

                        ui->label_warn->update();
                        ui->style_value_3->update();
                        ui->state_value->update();
                        }
                else
                        {
                                ui->style_value_3->setText(QString::fromUtf8("红外对射传感器"));
                                ui->state_value->setText(QString::fromUtf8("正常"));

                                ui->label_warn->update();
                                ui->style_value_3->update();
                                ui->state_value->update();
                                }
}
void CO2::Int_change_1(){
        int_flag=1;
        //printf("-------------------------------Int_change 1----------------------------------\n");

        ui->style_value_3->setText(QString::fromUtf8("门磁传感器"));
        ui->state_value->setText(QString::fromUtf8("报警"));

        int_label->update();
        ui->label_warn->update();
        ui->style_value_3->update();
        ui->state_value->update();
        //Api_Cliect_ClearIntlock();
}
void CO2::Smog_change_1(){
        smog_flag=1;

        //printf("-------------------------------Smog_change 1----------------------------------\n");

        ui->style_value_3->setText(QString::fromUtf8("烟雾传感器"));
        ui->state_value->setText(QString::fromUtf8("报警"));

        smog_label->update();
        ui->label_warn->update();
        ui->style_value_3->update();
        ui->state_value->update();
//Api_Cliect_ClearIntlock();
}
void CO2::Irda_change_1(){
        irda_flag=1;
        //printf("-------------------------------Irda_change 1----------------------------------\n");

        ui->style_value_3->setText(QString::fromUtf8("红外对射传感器"));
        ui->state_value->setText(QString::fromUtf8("报警"));


        irda_label->update();
        ui->label_warn->update();
        ui->style_value_3->update();
        ui->state_value->update();
//Api_Cliect_ClearIntlock();

}

void CO2::Int_change_0(){
        int_flag=0;
        printf("Int_change 0\n");

        ui->style_value_3->setText(QString::fromUtf8("门磁传感器"));
        ui->state_value->setText(QString::fromUtf8("正常"));

        int_label->update();
        ui->label_warn->update();
        ui->style_value_3->update();
        ui->state_value->update();
        //Api_Cliect_ClearIntlock();
        //ui->send_msg->setText("Not send!");

}

void CO2::Smog_change_0(){
printf("Smog_change 0\n");
        smog_flag=0;

        ui->style_value_3->setText(QString::fromUtf8("烟雾传感器"));
        ui->state_value->setText(QString::fromUtf8("正常"));

        smog_label->update();
        ui->label_warn->update();

        ui->style_value_3->update();
        ui->state_value->update();
        //Api_Cliect_ClearIntlock();
        //ui->send_msg->setText("Not send!");
}
void CO2::Irda_change_0(){
        printf("Irda_change 0\n");
        irda_flag=0;

        ui->style_value_3->setText(QString::fromUtf8("红外对射传感器"));
        ui->state_value->setText(QString::fromUtf8("正常"));

        irda_label->update();
        ui->label_warn->update();

        ui->style_value_3->update();
        ui->state_value->update();
        //ui->send_msg->setText("Not send!");
        //Api_Cliect_ClearIntlock();
}

void CO2::Set_Sim(int sim)
{
    if(sim==0)
    {
        Sim_state=0;
    }
    else if(sim==1)
    {
        Sim_state=1;
    }
}
void CO2::Set_Send(int sim)
{
    if(sim==1)
                sim=0;
}

