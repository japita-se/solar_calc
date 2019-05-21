#include "newlabel.h"
newLabel::newLabel(QWidget *parent, Qt::WindowFlags f): QLabel(parent)
{

}

newLabel::newLabel( const QString &a,QWidget* parent,Qt::WindowFlags f) : QLabel(parent)
{
    setText(a);
}
void newLabel::mousePressEvent(QMouseEvent *event)
{
    if (event->button()==Qt::LeftButton)
        emit clicked();
}


