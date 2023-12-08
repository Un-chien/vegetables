#ifndef SOFTKEY_H
#define SOFTKEY_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class SoftKey;
}

class SoftKey : public QWidget
{
    Q_OBJECT

public:
    explicit SoftKey(QWidget *parent = 0);
    ~SoftKey();

signals:
    void Send1();
    void Send2();
    void Send3();
    void Send4();
    void Send5();
    void Send6();

private slots:
    void on_onepushButton_clicked();

    void on_twopushButton_clicked();

    void on_threepushButton_clicked();

    void on_fourpushButton_clicked();

    void on_fivepushButton_clicked();

    void on_sixpushButton_clicked();

    void on_sevenpushButton_clicked();

    void on_eightpushButton_clicked();

    void on_ninepushButton_clicked();

    void on_zeropushButton_clicked();

    void on_deletepushButton_clicked();

    void on_confirmpushButton_clicked();

private:
    Ui::SoftKey *ui;
};

#endif // SOFTKEY_H
