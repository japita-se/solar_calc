#ifndef SUPPORT_H
#define SUPPORT_H
#include <QtGui>
#include <QNetworkProxy>

class QWebView;
class Map;
class Support:public QWidget
{
	Q_OBJECT;
public:
	Support(QWidget* parent=0);
        void reset();
	QString googleName();
        void setProxy(const QNetworkProxy &y);
	void showWarn(bool a);
	void showWarn(bool a,const QString &g);
	void setCity(QString name);
        void setCo(  double Latitude,   double Longitude);
	QString cityLocal();
	QSize minimumSizeHint() const;
	QPointF coordinates();
private slots:
	void setCoordinates();
	void updatePoint(double a, double b,QString& s);
signals:
	void coordinatesValid();
	void pointChanged(double a,double b,QString& c);
private:
	QLabel *warn;
	Map *map;
	QString city;
	QPointF co;
	bool wait;
	int mode;
	double lat,lon;
	enum {
	numeric,
	textCity
	};
	QString locName;
protected:
 void paintEvent(QPaintEvent* event) ;
};
#endif
