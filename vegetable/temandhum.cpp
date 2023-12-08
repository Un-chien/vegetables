#include "temandhum.h"
#include "ui_temandhum.h"

#include <QDebug>
#include <QKeyEvent>
#include <QFile>
#include <unistd.h>
#include <math.h>
#include "server/api.h"
int gprs_fg = 0;


extern QString m_string;
extern int flag;

int temmin = 0;
int temmax = 50;
int hummin = 0;
int hummax = 100;


TemandHum::TemandHum(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TemandHum)
{
    ui->setupUi(this);

    m_key = new SoftKey;

//    QAction *temact = new QAction(this);
//    temact->setIcon(QIcon(":/image/keyboard.jpg"));
//    ui->temlineEdit->addAction(temact,QLineEdit::TrailingPosition);
//    connect(temact,SIGNAL(triggered()),this,SLOT(temkeyboard()));

//    QAction *humact = new QAction(this);
//    humact->setIcon(QIcon(":/image/keyboard.jpg"));
//    ui->humlineEdit->addAction(humact,QLineEdit::TrailingPosition);
//    connect(humact,SIGNAL(triggered()),this,SLOT(humkeyboard()));

            ui->pushButton_light->setFlat(true);

            char *ipaddr="192.168.12.26";//连接本地服务器，端口号是7838
            int port=7838;
            cliect_thread = new Cliect();
            cliect_thread->GetConnect(ipaddr,port);
            //建立相关的信号槽
            connect(ui->pushButton_light,SIGNAL(clicked()),this,SLOT(pushButton_light_clicked()));//开关灯
            connect(cliect_thread,SIGNAL(sendTempHum(unsigned long )),this,SLOT(show_TempHum(unsigned long )));//显示温湿度
            connect(cliect_thread,SIGNAL(Sim(int )),this,SLOT(Set_Sim(int)));
            connect(cliect_thread,SIGNAL(Send(int)),this,SLOT(Set_Send(int)));

            connect(this,SIGNAL(SendLight()),this,SLOT(pushButton_light_clicked()));


            cliect_thread->start();
            zb_thread = new ZigbeeTopo();

            light_state=0;
            Sim_state=0;
            //ui->state_sim->setText(QString::fromUtf8("未初始化"));
            cliect_thread->Api_Cliect_GetGPRSSignal();

}



TemandHum::~TemandHum()
{
    delete ui;
}

void TemandHum::on_refreshpushButton_clicked()
{
    qsrand(QTime::currentTime().msec());	//设置种子，该种子作为qrand生成随机数的起始值，RAND_MAX为32767，即随机数在种子值到32767之间
    int tem = qrand()%50;
    if(temmin > temmax || hummin > hummax)
    {
        QMessageBox::information(this, "Warning","Please re-enter the data if the data is incorrect!");
    }
        ui->temlineEdit->setText(QString::number(tem));
    if(tem < temmin)
    {
        QMessageBox::information(this, "Warning","The current temperature is too low!");
    }
    if(tem > temmax)
    {
        QMessageBox::information(this, "Warning","The current temperature is too high!");
    }
    int hum = qrand()%100;
        ui->humlineEdit->setText(QString::number(hum));
    if(hum < hummin)
    {
        QMessageBox::information(this, "Warning","The current humidity is too low!");
    }
    if(hum > hummax)
    {
        QMessageBox::information(this, "Warning","The current temperature is too high!");
    }

}

void TemandHum::on_temminButton_clicked()
{
    flag = 3;
    m_key->show();
    connect(m_key,SIGNAL(Send3()),this,SLOT(temminreceive()));
}

void TemandHum::temminreceive()
{
    temmin = m_string.toInt();
    ui->temminButton->setText(m_string);
}


void TemandHum::on_temmaxButton_clicked()
{
    flag = 4;
    m_key->show();
    connect(m_key,SIGNAL(Send4()),this,SLOT(temmaxreceive()));
}

void TemandHum::temmaxreceive()
{
    temmax = m_string.toInt();
    ui->temmaxButton->setText(m_string);
}


void TemandHum::on_humminButton_clicked()
{
    flag = 5;
    m_key->show();
    connect(m_key,SIGNAL(Send5()),this,SLOT(humminreceive()));
}

void TemandHum::humminreceive()
{
    hummin = m_string.toInt();
    ui->humminButton->setText(m_string);
}


void TemandHum::on_hummaxButton_clicked()
{
    flag = 6;
    m_key->show();
    connect(m_key,SIGNAL(Send6()),this,SLOT(hummaxreceive()));
}

void TemandHum::hummaxreceive()
{
    hummax = m_string.toInt();
    ui->hummaxButton->setText(m_string);
}



void TemandHum::show_TempHum(unsigned long x){

        char temp[5],humi[5],data[4];
        char *pTemp,*pHumi;
        pTemp = temp;
        pHumi = humi;
        int return_t=0;
        data[0]=BREAK_UINT32( x,3 );
        data[1]=BREAK_UINT32( x,2 );
        data[2]=BREAK_UINT32( x,1 );
        data[3]=BREAK_UINT32( x,0 );
        return_t=getsht11(data, pTemp, pHumi);
    if(return_t){
      ui->temlineEdit->setText(pTemp);
      QString stemp(pTemp);
      float ftemp = stemp.toFloat();
      if(ftemp < temmin)
      {
          emit SendLight();
          QMessageBox::information(this, "Warning","The current temperature is too low!");
      }
      if(ftemp > temmax)
      {
          emit SendLight();
          QMessageBox::information(this, "Warning","The current temperature is too high!");
      }
      ui->humlineEdit->setText(pHumi);
      QString shumi(pHumi);
      float fhumi = shumi.toFloat();
      if(fhumi < hummin)
      {
          QMessageBox::information(this, "Warning","The current humidity is too low!");
      }
      if(fhumi > hummax)
      {
          QMessageBox::information(this, "Warning","The current temperature is too high!");
      }
      ui->temlineEdit->update();
      ui->humlineEdit->update();
    }
}

void TemandHum::Set_Sim(int sim)
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
void TemandHum::Set_Send(int sim)
{
    if(sim==1)
                sim=0;
}
void TemandHum::pushButton_light_clicked(){
        NodeInfo *pSensorDesp=pNodeInfo2;
        while(pSensorDesp)
        {
                if(pSensorDesp->devinfo->status)
                if(pSensorDesp->devinfo->sensortype == 0x5)
                break;
                pSensorDesp=pSensorDesp->next;
        }
        if(pSensorDesp)
        {

   if(light_state==0)
   {
        cliect_thread->Api_Cliect_SetSensorStatus(pSensorDesp->devinfo->nwkaddr,1);
                ui->pushButton_light->setFlat(true);
                ui->pushButton_light->update();
  }
        else
                {
                cliect_thread->Api_Cliect_SetSensorStatus(pSensorDesp->devinfo->nwkaddr,0);
                        ui->pushButton_light->setFlat(true);
                        ui->pushButton_light->update();
        }
    light_state++;
    if(light_state>1)
        light_state=0;
        }

}


int TemandHum::calc_sth11(float *p_humidity ,float *p_temperature)
{
        int ret= 0;

        const float C1=-4.0; // for 12 Bit
        const float C2= 0.0405; // for 12 Bit
        const float C3=-0.0000028; // for 12 Bit
        const float T1=0.01; // for 14 Bit @ 5V
        const float T2=0.00008; // for 14 Bit @ 5V

        float rh=*p_humidity; // rh: Humidity [Ticks] 12 Bit
        float t=*p_temperature; // t: Temperature [Ticks] 14 Bit
        float rh_lin; // rh_lin: Humidity linear
        float rh_true; // rh_true: Temperature compensated humidity
        float t_C; // t_C : Temperature [C]
        t_C=t*0.01 - 42; //calc. Temperature from ticks to [C]
        rh_lin=C3*rh*rh + C2*rh + C1; //calc. Humidity from ticks to [%RH]
        rh_true=(t_C-25)*(T1+T2*rh)+rh_lin; //calc. Temperature compensated humidity [%RH]
        if(rh_true>100)rh_true=100; //cut if the value is outside of
        if(rh_true<0.1)rh_true=0.1; //the physical possible range
        *p_temperature=t_C; //return temperature [C]
        *p_humidity=rh_true; //return humidity[%RH]

        if (t_C>0)return ret = 1;
        return ret;
}

int TemandHum:: getsht11(char *rData, char *&pTemp, char *&pHumi)
{
                int i=0,j=0;
                float temp,humi;
                uint8 tlen,hlen;
                int calcret=0;
                char Temp_t[16];


                i = rData[1] * 256 + rData[0];
                j = rData[3] * 256 + rData[2];


                temp = (float)j;
                humi = (float)i;
                calcret = calc_sth11(&humi,&temp);
                //qDebug("\rtemp=%f\t humi=%f\r",temp,humi);
                if( ((int)temp) > 0  && 0 <= humi <= 100 && calcret) {
                        tlen = sprintf(pTemp, "%d.%d",(int)temp,(int)((temp-(int)temp)*10));
                        hlen = sprintf(pHumi, "%d.%d",(int)humi,(int)((humi-(int)humi)*10));
                        //qDebug("\rTEMP=%s\tHUMI=%s\r",pTemp,pHumi);
                        return 1;
                }
                return 0;

}
