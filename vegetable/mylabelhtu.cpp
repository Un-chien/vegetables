#include "mylabelhtu.h"
MyLabelHtu::MyLabelHtu(QWidget *parent)
: QLabel(parent)
{
	

}
void MyLabelHtu::mouseReleaseEvent(QMouseEvent *ev)
{
	Q_UNUSED(ev)
	emit clicked();
}
