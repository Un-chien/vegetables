#include "QLabel"
class MyLabelHtu : public QLabel
{
	Q_OBJECT
 
public:
	MyLabelHtu(QWidget *parent=0);

private:

protected:

	virtual void mouseReleaseEvent(QMouseEvent *ev);
signals:
	void clicked(void);

};
