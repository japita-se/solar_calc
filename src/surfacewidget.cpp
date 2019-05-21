#include "surfacewidget.h"
#include <QSvgWidget>
#include <QtGui>
SurfaceWidget::SurfaceWidget(QWidget* parent): QWidget(parent)
{
// 	 li = new QLabel(this);
	azimuth << 0;
	setBackgroundRole(QPalette::Base);
	resize(200,100);
       setAutoFillBackground(true);
	tilt << 0;
	
	h= 25;
	l=50;
 
	tiltType = fixed;
	
	
	
}
void  SurfaceWidget::setTiltType(int m)
{
        if (m<4)
            tiltType = m;
	else
            tiltType = fixed;
//         qDebug()<<"SW tilttype"<<tiltType<<m;
	repaint();
}
void SurfaceWidget::setAzimuth(QVector<double> &a)
{
	azimuth = a;
	 
}
void SurfaceWidget::setTilt(QVector<double> &a)
{
	tilt = a;
	 
}

void SurfaceWidget::paintEvent(QPaintEvent* /*event*/)
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
void SurfaceWidget::draw(QPainter * painter)
{	
	QRect rect;
	QLinearGradient linearGradient;
        
	QBrush brush;
	
	painter->setFont(QFont("Helvetica [Cronyx]", 6));
	if ((type==rack || type==direct || type==array)&& (tiltType!=1)) {
		painter->setRenderHint(QPainter::Antialiasing,true);
		painter->setPen(QPen(Qt::black,1 ,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));

                painter->drawText(QRect(-85,-50,100,100),Qt::TextWordWrap,tr(" VISTA DALL'ALTO") );
		/*draw axis*/
			QPointF v1(-80,-28);
			QPointF v2(-80,-13);
			QPointF h1(-80,-28);
			QPointF h2(-68,-28);
			
			painter->drawLine(v1,v2);
			painter->drawLine(h1,h2);
			/* Draw arrows*/
			painter->setPen(QPen(Qt::black,0.5 ,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
	// 		painter->setBrush(QBrush(Qt::black,Qt::SolidPattern));
			QPolygonF vArrow,hArrow;
                        vArrow<<QPointF(-80,-9)<<QPointF(-78 ,-13)<<QPointF(-82  ,-13);
			hArrow<<QPointF(-68,-26)<<QPointF(-64 ,-28)<<QPointF(-68  ,-30);
			painter->drawPolygon(vArrow,Qt::OddEvenFill);
			painter->drawPolygon(hArrow,Qt::OddEvenFill);
			painter->setFont(QFont("Helvetica [Cronyx]", 4));
			painter->drawText(QPointF(-84,-5),  tr("SUD"));
			painter->drawText(QPointF(-68,-32),  tr("EST"));
		for(int i=0;i<azimuth.size();i++){
		
			rect = QRect(-25,25,h,l*cos(tilt.at(i)*3.14/180));/*the rect representing the panel*/
			
			rect.moveCenter(QPoint(-40+i*50,0));
			
			painter->save();
			painter->translate(-40+i*50, 0);
				
			painter->rotate(azimuth.at(i));
			painter->translate(+40-i*50, 0);

			linearGradient.setStart(QPointF(i*50,0));
			linearGradient.setFinalStop(QPointF(-l+i*50,0));
			linearGradient.setColorAt(0, Qt::black);
			linearGradient.setColorAt(1, Qt::white);
			brush = QBrush(linearGradient);
			brush.setTextureImage(QImage(":/images/panel.jpg"));
			painter->setPen(QPen(Qt::black,1 ,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
			painter->setBrush(brush);
			painter->drawRect(rect);
			
 			painter->restore();
	

			
		}
		painter->setFont(QFont("Helvetica [Cronyx]", 6));
			 
		
		}
		/* draw array */
		if ((type==array) && tiltType!=multiple && tiltType!=biax)
		{
			painter->save();
			painter->translate(-50, 0);

			QPolygon shape;
			shape<<QPoint(65,0)<<QPoint(90,-30)<<QPoint(90,0)<<QPoint(105,0)<<QPoint(130,-30)<<QPoint(130,0)<<QPoint(150,0)<<QPoint(60,0);
			painter->drawPolygon(shape,Qt::OddEvenFill);
			painter->setPen(QPen(Qt::blue,1 ,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
			painter->drawLine(QPoint(65,14),QPoint(79,14));
			painter->drawLine(QPoint(87,14),QPoint(105,14));
			painter->drawText(QPoint(79,15),tr("a"));
			drawLeftArrow(*painter,QPoint(65,14));
			drawRightArrow(*painter,QPoint(105,14));	
			painter->restore();
		}

		if (type==rack && tiltType!=multiple && tiltType!=biax ) {
		painter->translate(-50, 20);
		QPolygonF bipv,bipv2, bipv4;
		bipv<<QPointF(65,0)<<QPointF(127,-62)<<QPointF(126,-64)<<QPointF(63,-2);
		bipv2<<QPointF(74,-13)<<QPointF(104,-43)<<QPointF(102,-45)<<QPointF(72,-15);
		bipv4<<QPointF(63,2)<<QPointF(129,2)<<QPointF(129,-64);
		painter->drawPolygon(bipv);
		brush = QBrush();
		brush.setTextureImage(QImage(":/images/panel.jpg"));
		painter->setBrush(brush);
		painter->drawPolygon(bipv2);
		painter->setBrush(QBrush());
		painter->drawPolygon(bipv4);

		}

		/* draw BIPV*/
                if ((type==direct) && tiltType!=multiple && tiltType!=biax) {

		painter->translate(-50, 20);
		QPolygonF bipv,bipv2,bipv3,bipv4;
		bipv<<QPointF(65,0)<<QPointF(75,-10)<<QPointF(73,-12)<<QPointF(63,-2);
		bipv2<<QPointF(76,-11)<<QPointF(106,-41)<<QPointF(104,-43)<<QPointF(74,-13);
		bipv3<<QPointF(107,-42)<<QPointF(127,-62)<<QPointF(126,-64)<<QPointF(106,-44);
		bipv4<<QPointF(63,2)<<QPointF(129,2)<<QPointF(129,-64);
		painter->drawPolygon(bipv);
		brush = QBrush();
		brush.setTextureImage(QImage(":/images/panel.jpg"));
		painter->setBrush(brush);
		painter->drawPolygon(bipv2);
		painter->setBrush(QBrush());
		painter->drawPolygon(bipv3);
		painter->drawPolygon(bipv4);
	
		
		}

		/* Draw trackers arrays */
		if (tiltType==1)

                {

                        painter->translate(-50, 0);
			painter->setPen(QPen(Qt::black,2 ,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
			painter->drawLine(QPoint(0,20),QPoint(0,-0));
			painter->drawLine(QPoint(-20,-20),QPoint(20,20));
			painter->drawLine(QPoint(100,20),QPoint(100,-30));
			painter->drawLine(QPoint(80,-50),QPoint(120, -10));
			
			painter->setPen(QPen(Qt::black,1 ,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
			/*base*/
			painter->drawLine(QPoint(-40,20),QPoint(140,20));
			/*arrows*/
			painter->drawLine(QPoint(0,40),QPoint(100,40));
			drawLeftArrow(*painter,QPoint(0,40));
			drawRightArrow(*painter,QPoint(100,40));
			painter->drawText(QPoint(50,30),tr("a"));	

			/*vertical arrow*/
                        painter->drawLine(QPoint(70,0),QPoint(70,-30));
			drawUpArrow(*painter,QPoint(70,-30));
                        drawDownArrow(*painter,QPoint(70,0));
			painter->drawText(QPoint(55,-5),tr("h"));	
			


 			painter->translate(QPoint(-50,0));



			 
		 
		}


}
QSize SurfaceWidget::minimumSizeHint() const
 {
     return QSize(200, 200);
 }
void SurfaceWidget::drawUpArrow(QPainter& painter,QPoint start)
{
	QPolygon a;
	a<<start<<QPoint(start.x()-5,start.y()+5)<<QPoint(start.x()+5,start.y()+5)<<(start);
	painter.drawPolygon(a);
}
void SurfaceWidget::drawDownArrow(QPainter& painter,QPoint start)
{
	QPolygon a;
	a<<start<<QPoint(start.x()-5,start.y()-5)<<QPoint(start.x()+5,start.y()-5)<<(start);
	painter.drawPolygon(a);
}
void SurfaceWidget::drawLeftArrow(QPainter& painter,QPoint start)
{
	QPolygon a;
	a<<start<<QPoint(start.x()+5,start.y()-5)<<QPoint(start.x()+5,start.y()+5)<<(start);
	painter.drawPolygon(a);
}
void SurfaceWidget::drawRightArrow(QPainter& painter,QPoint start)
{
	QPolygon a;
	a<<start<<QPoint(start.x()-5,start.y()-5)<<QPoint(start.x()-5,start.y()+5)<<(start);
	painter.drawPolygon(a);
}	 
 
void SurfaceWidget::setType(int i)
// The type of converter, fixed or tracker
{
	type = i;
 	
	repaint();
}
void SurfaceWidget::setH(double d)
{
	h = d;
}
void SurfaceWidget::setL(double d)
{
	l = d;
}
void SurfaceWidget::swap()
{
	double temp;
	temp = h;
	h = l;
	l = temp;
	 
	update();
}
void SurfaceWidget::mousePressEvent(QMouseEvent* /*event*/)
{
	swap();
        emit swapped();
	 
}
