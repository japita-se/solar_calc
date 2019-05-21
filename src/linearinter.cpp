#include "linearinter.h"
#include <QPointF>
#include <QDebug>
#include <cmath>
using namespace std;
LinearInter::LinearInter()
{
}
void LinearInter::setPoints(const QPolygonF &points)
{
	if (points.size()<2) 
	{	
           //     qDebug()<<"POCHI PUNTI IN LINEAR INTE"<<points.size();
		return;
	}
	else
	{
	data = points;
     //   qDebug()<<"Ho settato i punti in LINEAR INTER..."<<data.size();
	 
	}
}

double LinearInter::value(double x)
{
	double x1,x2,y1,y2,val;
	/* Cerco prima l'intervallo giusto */
	x1 = data.at(0).x();
	y1 = data.at(0).y();

	/* Se il punto e' fuori, ritorno 0*/
	if (x>data.last().x()){
                //qDebug()<<"X fuori intervallo..."<<x<<data.last().x();
		return 0;
	}
	for(int i=1;i<data.size();i++) {
                if (fabs((data.at(i).x() - x))<=0.00001)
		{
                        //qDebug()<<"Esco da lineae"<<data.at(i).x()<<x;
                        return data.at(i).y();
		}
		x2 = data.at(i).x();
		y2 = data.at(i).y();
		if (x2>x)	{
				
			/* Ho trovato l'intervallo, interpolo e esco */
			val = interpolate(QPointF(x1,y1),QPointF(x2,y2),x);
			return val;
		}
		else
  		{	
//   			qDebug()<<"LINEAR:Proseguo"<<x1<<x2<<x<<i;
			x1 = x2;
			y1 = y2;
		}
	}
}
double LinearInter::interpolate(const QPointF &i1,const QPointF &i2,double x)
{
	
	double x1,x2,y2,y1,m,c,y;
	x1 = i1.x();
	y1 = i1.y();
	x2 = i2.x();
	y2 = i2.y();
	/* Costruisce una retta fra due punti */
	if (x2!=x1)
		m = (y2-y1)/(x2-x1);
	else
		m = 0;
	c = y1 - (m*x1);
	y = m*x +c;
        //qDebug()<<"Ho interpolato....y="<<y<<x1<<x2;
	return y;
}
LinearInter::~LinearInter()
{
}
