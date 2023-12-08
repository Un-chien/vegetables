#ifndef MONITOR_H
#define MONITOR_H

#include <QWidget>

namespace Ui {
class Monitor;
}

class Monitor : public QWidget
{
    Q_OBJECT

public:
    explicit Monitor(QWidget *parent = 0);
    ~Monitor();

private slots:
    void on_ricepushButton_clicked();

    void on_wheatpushButton_clicked();

    void on_potatopushButton_clicked();

private:
    Ui::Monitor *ui;
};

#endif // MONITOR_H
