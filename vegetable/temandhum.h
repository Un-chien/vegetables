#ifndef TEMANDHUM_H
#define TEMANDHUM_H
#include "zigbeetopo.h"
#include"server/cliect_td.h"
#include "server/api.h"

#include <QWidget>
#include <QtGlobal>
#include <QTime>
#include <QAction>
#include <softkey.h>
#include <QMessageBox>
#include <QSignalMapper>
#include <QList>
#include <QPushButton>
#include <QString>

namespace Ui {
class TemandHum;
}
typedef signed   char   int8;
typedef unsigned char   uint8;
typedef unsigned char   byte;
typedef signed   short  int16;
typedef unsigned short  uint16;

typedef signed   long   int32;
typedef unsigned long   uint32;
#define BREAK_UINT32( var, ByteNum ) \
          (byte)((uint32)(((var) >>((ByteNum) * 8)) & 0x00FF))


class TemandHum : public QWidget
{
    Q_OBJECT

public:
    explicit TemandHum(QWidget *parent = 0);
    ~TemandHum();

       //char *phone_num,*phone_data;
       int calc_sth11(float *p_humidity ,float *p_temperature);
       int getsht11(char *rData, char *&pTemp, char *&pHumi);
       // MyLabelHtu *smog_label,*int_label,*irda_label;
       ZigbeeTopo *zb_thread;
       Cliect *cliect_thread;

       int light_state;
       int Sim_state;
       QSignalMapper *signalMapper;
       QList<QPushButton *> allNumButtons;


signals:
    void SendLight();


private slots:
    void on_refreshpushButton_clicked();
    //void temkeyboard();
    //void humkeyboard();
    void temminreceive();
    void humminreceive();
    void temmaxreceive();
    void hummaxreceive();

    void on_temminButton_clicked();

    void on_temmaxButton_clicked();

    void on_humminButton_clicked();

    void on_hummaxButton_clicked();



    void pushButton_light_clicked();

    void show_TempHum(unsigned long x);

    void Set_Sim(int sim);
    void Set_Send(int sim);

private:
    Ui::TemandHum *ui;

    SoftKey *m_key;
};

#endif // TEMANDHUM_H
