#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QWidget>
#include <QMessageBox>
//#include <QJsonDocument>
//#include <QFile>
#include <QDebug>
//#include <QJsonObject>
#include <QByteArray>
#include <QPalette>
#include <QPixmap>
#include <softkey.h>

namespace Ui {
class Logwidget;
}

class Logwidget : public QWidget
{
    Q_OBJECT

public:
    explicit Logwidget(QWidget *parent = 0);
    ~Logwidget();

//    void form_init(); //格式初始化
//    void func_init(); //功能初始化
//    void read_json(); //读json
//    void write_json();//写json
//    void message_init(QString flag1,QString flag2);//根据json内容决定是否填充输入框


signals:
    void login(); //登录主界面信号
    void close_window(); //关闭登录界面信号

private slots:
    void on_longonpushButton_clicked();
    void on_resetpushButton_clicked();
    void on_namepushButton_clicked();
    void on_passwordpushButton_clicked();
    void namereceive();
    void passwordreceive();

private:
    Ui::Logwidget *ui;
    QString m_username;  // 自己设定的账号
    QString m_password;  // 自己设定的密码

    SoftKey *m_key;
};

#endif // LOGWIDGET_H
