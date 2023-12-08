#include "logwidget.h"
#include "ui_logwidget.h"
#include "softkey.h"

extern QString m_string;
extern int flag;

Logwidget::Logwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Logwidget)
{
    ui->setupUi(this);

    m_key = new SoftKey;

//    QAction *act1 = new QAction(this);
//    act1->setIcon(QIcon(":/image/background.jpg"));
//    ui->namelineEdit->addAction(act1,QLineEdit::TrailingPosition);
//    connect(act1,SIGNAL(tirggered(boll)),this,SLOT(keyshow()));

//    QAction *act2 = new QAction(this);
//    act2->setIcon(QIcon(":/image/background.jpg"));
//    ui->passwordlineEdit->addAction(act1,QLineEdit::TrailingPosition);

    QPixmap pixmap(":/image/background.jpg");
    QPalette pale;
    pale.setBrush(QPalette::Background,pixmap);
    this->setPalette(pale);

    // connect 3个信号槽
    // 触发重置按钮的信号槽连接
    connect(ui->resetpushButton,SIGNAL(clicked()),this,SLOT(on_resetpushButton_clicked()));
    // 触发登录按钮的信号槽连接
    connect(ui->longonpushButton,SIGNAL(clicked()),this,SLOT(on_longonpushButton_clicked()));
    // 发出信号后关闭登录窗口的信号槽连接
    connect(this,SIGNAL(close_window()),this,SLOT(close()));
    ui->passwordlineEdit->setEchoMode(QLineEdit::Password);//输入的时候就显示圆点
    m_username = "20202793";
    m_password = "20202793";
    // 读取json文件
    //read_json();
}


//void Logwidget::read_json()
//{
//    qDebug() << QApplication::applicationDirPath();
//    //打开文件
//    QFile file(QApplication::applicationDirPath()+"/config.json");
//    if(!file.open(QIODevice::ReadOnly)) {
//        qDebug() << "File open failed!";
//    } else {
//        qDebug() <<"File open successfully!";
//    }
//    QJsonDocument jdc(QJsonDocument::fromJson(file.readAll()));
//    QJsonObject obj = jdc.object();
//    QString save_name_flag=obj.value("SAVE_NAME").toString();
//    QString save_password_flag=obj.value("SAVE_PASSWORD").toString();
//    message_init(save_name_flag,save_password_flag);
//}


// 更新json文件
//void Logwidget::write_json()
//{
//    QFile file(QApplication::applicationDirPath()+"/config.json");
//    if(!file.open(QIODevice::WriteOnly)) {
//        qDebug() << "File open failed!";
//    } else {
//        qDebug() <<"File open successfully!";
//    }
//    QJsonObject obj;
//    bool flag = ui->namecheckBox->isChecked();
//    if(flag == true)
//    {
//        obj["SAVE_NAME"] = "1";
//    }
//    else
//        obj["SAVE_NAME"] = "0";
//    flag = ui->passwordcheckBox->isChecked();
//    if(flag == true)
//    {
//        obj["SAVE_PASSWORD"] = "1";
//    }
//    else
//        obj["SAVE_PASSWORD"] = "0";
//    QJsonDocument jdoc(obj);
//    file.write(jdoc.toJson());
//    file.flush();
//}


//根据json内容决定是否填充输入框
//void Logwidget::message_init(QString flag1,QString flag2)
//{
//    //qDebug() << flag1 << "^^^" << flag2 ;
//    if (flag1 == "1")
//    {
//        ui->namelineEdit->setText("20202793");
//        ui->namecheckBox->setChecked(true);
//    }
//    if(flag2 == "1")
//    {
//        ui->passwordlineEdit->setText("20202793");
//        ui->passwordcheckBox->setChecked(true);
//    }
//}


Logwidget::~Logwidget()
{
    delete ui;
}


void Logwidget::on_longonpushButton_clicked()
{
    QString name = ui->namelineEdit->text();
    QString password = ui->passwordlineEdit->text();
    if(name == m_username && password == m_password)
    {
        emit login();
        //write_json();
        emit close_window();
    }
    else // 账号或密码错误
    QMessageBox::information(this, "Warning","Username or Password is wrong !");

}


void Logwidget::on_resetpushButton_clicked()
{
    ui->namelineEdit->clear();
    ui->passwordlineEdit->clear();
}


void Logwidget::on_namepushButton_clicked()
{
    flag = 1;
    m_key->show();
    connect(m_key,SIGNAL(Send1()),this,SLOT(namereceive()));
}


void Logwidget::on_passwordpushButton_clicked()
{
    flag = 2;
    m_key->show();
    connect(m_key,SIGNAL(Send2()),this,SLOT(passwordreceive()));
}


void Logwidget::namereceive()
{
    ui->namelineEdit->setText(m_string);
}


void Logwidget::passwordreceive()
{
    ui->passwordlineEdit->setText(m_string);
}
