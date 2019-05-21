#ifndef SURFACEWIDGET_H
#define SURFACEWIDGET_H
 #include <QPixmap>
 #include <QWidget>
#include <QBrush>
#include <QPen>
#include <QtGui>
class QPainter;
class QSvgWidget;
class SurfaceWidget : public QWidget
{
	Q_OBJECT
public:
	SurfaceWidget(QWidget* parent=0);
	void setTiltType(int m);
	void setH(double h);	
	void setL(double l);
	void swap();
	
	void setTilt(QVector<double> &a);
	void setAzimuth(QVector<double> &a);
	void draw(QPainter* painter);
	QSize minimumSizeHint() const;
signals:
        void swapped( );
public slots:
	 
	void setType(int i);
protected:
	void drawUpArrow(QPainter& painter,QPoint start);
	void drawDownArrow(QPainter& painter,QPoint start);
	void drawLeftArrow(QPainter& p,QPoint start);
	void drawRightArrow(QPainter& p,QPoint start);
	void paintEvent(QPaintEvent* event) ;
	void mousePressEvent(QMouseEvent* /*event*/);
	
	
private:
	QVector<double> azimuth,tilt;
	double h,l;
	int tiltType,type;
	QLabel* li;
QSvgWidget* svg;

	enum {
		rack,
		direct,
		array,
		standoff,
			
	};
	enum{
	fixed,
	biax,
	multiple
	};
	
};
#endif