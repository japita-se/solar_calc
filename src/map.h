#ifndef HEADER_H
#define HEADER_H

#include <QWebView>
#include <QNetworkProxy>
 
class QNetworkAccessManager;

class Map : public QWebView 
{
	Q_OBJECT
public:
        Map(QWidget *parent=0);
	QPointF getCoordinates();
        void setProxy(const QNetworkProxy &y);
        void reset();

public slots:
	QString getName();
	void waitPage( );
	void examinePage();
	void test();
	void setValues(const QString &latitude, const QString &longitud, const QString &n);
	void populateJavaScriptWindowObject();
	void replyFinished(QNetworkReply*); 
        void loadCoordinates();
        void loadCoordinatesSignal();
        void loadCoordinates( double a,   double b);
        void geoCode(QString a,int mode);
        void clearCoordinates();

signals:
        void reloadMap();
        void reload();
	void coordinatesReady(double a,double b,QString &s);

private:
        QNetworkAccessManager *manager;
        QList<QPointF> coordinates;
	QStringList coordinateStrList ;
        int pendingRequests;
	double lat, lon;
        QString name,address,cityname,streetname,statename,numbername,adminname;
	int mode;
	enum {
	numeric,
	textCity
	};
	
};
	

#endif 