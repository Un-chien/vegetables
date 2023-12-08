#ifndef CO2_H
#define CO2_H
#include "zigbeetopo.h"
#include"server/cliect_td.h"
#include "server/api.h"
#include "mylabelhtu.h"
#include <QWidget>
#include <QSignalMapper>
#include <QList>
#include <QPushButton>
#include <QMessageBox>

namespace Ui {
class CO2;
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

class CO2 : public QWidget
{
    Q_OBJECT

public:
    explicit CO2(QWidget *parent = 0);
    ~CO2();

    MyLabelHtu *smog_label,*int_label,*irda_label;
    ZigbeeTopo *zb_thread;
    Cliect *cliect_thread;

int int_flag,smog_flag,irda_flag,light_state;
int Sim_state;



signals:
void Irda_StateChanged_1(void);//duishe
void Smog_StateChanged_1(void);//
void Int_StateChanged_1(void);//door
void Irda_StateChanged_0(void);//duishe
void Smog_StateChanged_0(void);//
void Int_StateChanged_0(void);//door

public slots:

void Smog_change_1();
void Int_change_1();
void Irda_change_1();
void Smog_change_0();
void Int_change_0();
void Irda_change_0();
void int_show();
void smog_show();
void irda_show();

void Set_Sim(int sim);
void Set_Send(int sim);

private:
    Ui::CO2 *ui;
};

#endif // CO2_H
