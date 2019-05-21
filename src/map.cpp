#include "map.h"
#include "mymath.h"
// #include "ui_showmap.h"
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDomDocument>
#include <QDomElement>
#include <QWebFrame>
#include <QWebPage>
#include <QEventLoop>
#include <QApplication>
#include <QDebug>
#include <QPushButton>
#include <QVBoxLayout>
#include <math.h>
#include <QTimer>
#include <sstream>
#include <iostream>
#include <iomanip>


using namespace std;

Map::Map(QWidget *parent) : QWebView(parent), pendingRequests(0)
{
	
	 
	manager = new QNetworkAccessManager(this);

        this->page()->mainFrame()->addToJavaScriptWindowObject("map", this);
	
// 	connect(this->page(),SIGNAL(loadFinished(bool)),SLOT(waitPage()));
	connect(this,SIGNAL(urlChanged(const QUrl&)),SLOT(waitPage()));
        connect(page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),
            this, SLOT(populateJavaScriptWindowObject()));

	connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
        connect(this,SIGNAL(reloadMap()), this,SLOT(loadCoordinatesSignal()));
	 
}
void Map::setProxy(const QNetworkProxy &p)
{
//qDebug()<<"MAP SETPROXY";
    manager->setProxy(p);
   // qDebug()<<"MPA PROXY"<<manager->proxy().hostName();

}

void Map::waitPage( )
{
// 	QTimer::singleShot(5000,this,SLOT(examinePage()));
}
void Map::examinePage()
{
    //double latInt,lonInt;
    //double latDec,lonDec;
    std::string a,b;
    std::istringstream stmla,stmlo;
    std::setprecision(15);



   QString javascript = QString("getLat()");
           a = (page()->currentFrame()->evaluateJavaScript(javascript).toString().toStdString());
            stmla.str(a);
            stmla >> std::setprecision(15)>>lat ;
         javascript = QString("getLng()");
           b   = page()->currentFrame()->evaluateJavaScript(javascript).toString().toStdString();
           stmlo.str(b);
           stmlo >> std::setprecision(15)>>lon ;
         javascript = QString("getName()");
          address = page()->currentFrame()->evaluateJavaScript(javascript).toString();


          lat = MyMath::convertToDouble(QString::fromStdString(a));
          lon = MyMath::convertToDouble(QString::fromStdString(b));
          qDebug()<<"MAP new coord point " <<lat<<lon<<address<<cityname<<QString::fromStdString(a)<<QString::fromStdString(b);

	if (lat>=-180 && lat <=180 && lon>=-180 && lon<=180)
		emit coordinatesReady(lat,lon,address);

}
void Map::geoCode(QString local, int i )
{
	mode = i;
	clearCoordinates();
        //qDebug()<<"MAP   geoCode"<<local;
       //  qDebug()<<"Map finding......."<<local;
        QString requestStr( tr("http://maps.googleapis.com/maps/api/geocode/xml?address=%1&sensor=%2")
			.arg(local)
                        .arg("false"));


	manager->get( QNetworkRequest(requestStr) );
	++pendingRequests;
      qDebug()<<"MAP SUPPORT query"<<requestStr;
	if (mode==numeric){
		QStringList cc = local.split(",");
		lat  = cc.at(0).toDouble();
		if (cc.size()>1)
		lon  = cc.at(1).toDouble();
		else
		lon  = 0;
	}
}
void Map::replyFinished(QNetworkReply *reply)
{
    QString replyStr( reply->readAll() );

    // Read the XML as Google API v3 returns XML data

QDomDocument doc;
doc.setContent(replyStr);
QString lat = doc.documentElement().firstChildElement("result").firstChildElement("geometry").firstChildElement("location").firstChildElement("lat").text();
QString lng = doc.documentElement().firstChildElement("result").firstChildElement("geometry").firstChildElement("location").firstChildElement("lng").text();


    {
        QPointF coordinate( lat.toFloat(),lng.toFloat() );
        coordinates << coordinate;
    }
	
   // qDebug()<<"MAP replyFinished"<<coordinateStrList<<coordinates;
    --pendingRequests;
    if( pendingRequests<1  )
    {
	
        emit( reloadMap() ); 
    }

}
void Map::loadCoordinatesSignal()
{
    loadCoordinates();
   // qDebug()<<"MAP loadCoordinatesSignal Coordinates map"<<coordinates;
    emit reload();
}

void Map::loadCoordinates()
{
	this->page()->mainFrame()->evaluateJavaScript(QString("clearO()") );
	if (mode==textCity){
        foreach(QPointF point ,coordinates)
			{
            this->page()->mainFrame()->evaluateJavaScript(
            QString("Open(%1,%2)").arg(point.x()).arg(point.y()) );
            qDebug()<<"MAP Coordinates map----------------------------------------------------------------"<<coordinates;
			}
	}
	if (mode==numeric)	
			this->page()->mainFrame()->evaluateJavaScript( 
							QString("Open(%1,%2)").arg(lat ).arg(lon  ) );
}
void Map::loadCoordinates( double la,   double lo)
{
	this->page()->mainFrame()->evaluateJavaScript(QString("clearO()") );
         //qDebug()<<" MAP loadCoordinates Coordinates QUA"<<coordinates<<QString::number(la,'f',8)<<QString::number(lo,'f',8);
//	foreach(QPointF point ,coordinates)
//    {
		this->page()->mainFrame()->evaluateJavaScript( 
                                QString("Open(%1,%2)").arg(la,0,'f',8).arg(lo,0,'f',8) );

//    }
}
QPointF Map::getCoordinates()
{	
// 	qDebug()<<"MAP getCoordinates"<<coordinates;
	if (coordinates.size()>0  )
	return coordinates.at(0);
	else
	return QPointF();
  
}
QString Map::getName()
{
	if (coordinateStrList.size()>4  ){
		if (coordinateStrList.at(1)=="6")
			{
// 			qDebug()<<"MAP 1"<<coordinateStrList;
			return coordinateStrList.at(2)+","+coordinateStrList.at(3);
			}
		else
			{
// 			qDebug()<<"MAP 2"<<coordinateStrList;
			return QString("");
			}
			
	}
      //  qDebug()<<"MAP getName 3"<<coordinateStrList;
	return QString();
}
void Map::clearCoordinates()
{
    coordinates.clear();
}

void Map::populateJavaScriptWindowObject()
{
	this->page()->mainFrame()->addToJavaScriptWindowObject("Map", this);

}
void Map::setValues(const QString &latitude, const QString &longitude, const QString &n)
{
// 	lat = latitude.toDouble();
// 	lon = longitude.toDouble();
// 	name = n;
// 	qDebug()<<"MAP new values available";
}
void Map::test()
{
	qDebug()<<"test finished";
}
void Map::reset()
{
    QString javascript = QString("initialize()");
    page()->currentFrame()->evaluateJavaScript(javascript);
}
