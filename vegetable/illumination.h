#ifndef ILLUMINATION_H
#define ILLUMINATION_H

#include <QWidget>
#include <QDial>
#include <QString>

namespace Ui {
class Illumination;
}

class Illumination : public QWidget
{
    Q_OBJECT

public:
    explicit Illumination(QWidget *parent = 0);
    ~Illumination();

private slots:
    void on_dial_actionTriggered();

private:
    Ui::Illumination *ui;
};

#endif // ILLUMINATION_H
