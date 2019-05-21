#include "immagine.h"
#include <QtGui>
Immagine::Immagine(QWidget* parent) : QWidget(parent)
{
}
void Immagine::paintEvent(QPaintEvent* /*event*/)
{
	int side = qMin(width(),height());
	QPainter painter(this);
	painter.translate(width()/2,height()/2);
 	painter.scale(side/100.0,side/100.0);
	painter.setRenderHint(QPainter::Antialiasing,true);
	
// 	int side = qMin(width(),height());
// 	
// 	int x = (width() - side / 2);
//  	int y = (height() - side / 2);
// 	painter.setViewport(x, y, side, side);
	 
  
//          qDebug()<<"Surface"<<width()<<height();
// 	painter.setWindow(-50,-50,50,50);
	draw(&painter);
}
void Immagine::draw(QPainter * painter)
{
	QPixmap tracker(":/images/inverter2.png"); 
// 	painter->scale(4,4);
	painter->translate(QPoint(-50,-50));
	painter->drawPixmap(QPoint(-50,-50),tracker);
}
