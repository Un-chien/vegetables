#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logwidget.h"
#include "server/api.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    // 通过指针创建登录界面类的对象
    m_log = new Logwidget;
    // 调用登录窗口的show()函数显示登录界面
    m_log->show();
    // 建立信号槽，到接收到登录界面发来的login()信号后，调用主窗口的show()函数。
    connect(m_log,SIGNAL(login()),this,SLOT(show()));

    // 定时器
    ui->lcdNumber->setDigitCount(8);
    QTimer *timer = new QTimer(this);
    //connect(timer, &QTimer::timeout, this, &MainWindow::on_Timer);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_Timer()));
    timer->start();

    QDate date = QDate::currentDate();
    ui->datepushButton->setText(date.toString());

//    connect(ui->monitoraction, &QAction::triggered, this, &MainWindow::monitor);
//    connect(ui->temandhhumaction, &QAction::triggered, this, &MainWindow::temandhum);
//    connect(ui->illuminationaction, &QAction::triggered, this, &MainWindow::illumination);
//    connect(ui->CO2action, &QAction::triggered, this, &MainWindow::co2);
    connect(ui->monitoraction, SIGNAL(triggered()), this, SLOT(monitor()));
    connect(ui->temandhhumaction, SIGNAL(triggered()), this, SLOT(temandhum()));
    connect(ui->illuminationaction, SIGNAL(triggered()), this, SLOT(illumination()));
    connect(ui->CO2action, SIGNAL(triggered()), this, SLOT(co2()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Timer()
{
    QTime time = QTime::currentTime();
    ui->lcdNumber->display(time.toString());
}


void MainWindow::monitor()
{
    m = new Monitor;
    m->show();
}


void MainWindow::temandhum()
{
    t = new TemandHum;
    t->show();
}


void MainWindow::illumination()
{
    i = new Illumination;
    i->show();
}


void MainWindow::co2()
{
    c = new CO2;
    c->show();
}
