#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <logwidget.h>
#include <monitor.h>
#include <temandhum.h>
#include <illumination.h>
#include <co2.h>
#include <QTimer>
#include <QTime>
#include <QDate>
#include"zigbeetopo.h"
#include"server/cliect_td.h"

//QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
//QT_END_NAMESPACE

typedef signed   char   int8;
typedef unsigned char   uint8;
typedef unsigned char   byte;
typedef signed   short  int16;
typedef unsigned short  uint16;

typedef signed   long   int32;
typedef unsigned long   uint32;
#define BREAK_UINT32( var, ByteNum ) \
          (byte)((uint32)(((var) >>((ByteNum) * 8)) & 0x00FF))

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void on_Timer();// 事件
    void monitor();
    void temandhum();
    void illumination();
    void co2();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Logwidget *m_log;
    Monitor *m;
    TemandHum *t;
    Illumination *i;
    CO2 *c;
};
#endif // MAINWINDOW_H
