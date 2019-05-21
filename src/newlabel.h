#ifndef NEWLABEL
#define NEWLABEL
#include <QLabel>
#include <QMouseEvent>
class newLabel : public QLabel
{

Q_OBJECT;
public:
     newLabel(QWidget * parent = 0, Qt::WindowFlags f = 0);
     newLabel(const QString &t,QWidget* parent=0,Qt::WindowFlags f = 0);
signals:
    void clicked();
protected:
    void mousePressEvent( QMouseEvent * event)
            ;

};



#endif
