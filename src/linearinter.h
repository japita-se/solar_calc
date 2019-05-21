#ifndef __linearinter_h
#define __linearinter_h
#include <vector>
#include <QPolygonF>
class LinearInter {

public:
	LinearInter();
	~LinearInter();
	
public:
	void setPoints(const QPolygonF &data);
	double value(double x);
private:
	double interpolate(const QPointF &i1,const QPointF& i2,double x);
private:
	QPolygonF data;
	
};
#endif
