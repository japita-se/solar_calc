#include "support.h"
#include "map.h"
#include <QWebView>

void Support::setProxy(const QNetworkProxy &a)
{
   // qDebug()<<"SETPROXY SUPPORT";
    map->setProxy(a);

}

void Support::showWarn(bool a)
{
	if (a)
		warn->setVisible(true);
	else
		warn->setVisible(false);
}
void Support::showWarn(bool a,const QString &b)
{
	if (a){
		warn->setVisible(true);
		warn->setText(b);
		}
	else
		warn->setVisible(false);
}
Support::Support(QWidget* parent): QWidget(parent)
{
 
	locName ="";
	map = new Map(this);
  	QPushButton *ok = new QPushButton(tr("Applica"),this);
	ok->setToolTip(tr("<p>Dopo aver scelto un punto sulla mappa con il mouse, clicca per applicare il nuovo sito al sistema attuale</p>"));
	warn = new QLabel( tr("<font color=\"red\">Servizio di mappatura non disponibile. Controlla la connessione</font>"),this); 
	warn->setWordWrap(true);
	warn->setVisible(false);
	warn->setGeometry( QRect(this->geometry().width()/2,this->geometry().height()/2,100,100));

	ok->setGeometry( 190,25, 97, 25);

	 #ifdef Q_WS_X11
  	 map->setUrl(QUrl("file:///://"));
	 #endif
         qDebug()<<"MAP DIRP"<<QCoreApplication::applicationDirPath()+"/index.html";
         map->load(QUrl(QCoreApplication::applicationDirPath()+"/index.html") ) ;
         connect(map,SIGNAL(reload()),SLOT(setCoordinates()));
	connect(ok,SIGNAL(clicked()),map,SLOT(examinePage()));
	connect(map,SIGNAL(coordinatesReady(double,double,QString&)),SLOT(updatePoint(double,double,QString&)));
  	 wait = true;
	mode = textCity;
	lat =-999;
	lon =-999;//invalid coordinate;
  	co = QPointF(lat,lon);
	
}
void Support::setCoordinates()
{
	if (!map->getCoordinates().isNull())
		co = map->getCoordinates();
	else
		if (mode==numeric)
			co = QPointF(lat,lon);
		else
			co = QPointF();

	wait = false;
	locName = map->getName();
      //  qDebug()<<"SUPPORT setCoordinates COORINDATES VALID"<<co<<locName;
	emit coordinatesValid();
   
}
void Support::setCity(QString name)
{
	mode = textCity;
	wait = true;
	city = name;
        //qDebug()<<"SUPPORT setCity"<<name;
	map->clearCoordinates();
	map->geoCode(name,mode );

	
	
	
}
void Support::reset()
{
    map->reset();
}

QString Support::googleName()
{
	return locName;
}
void Support::setCo(double  l, double  lo)
{
	wait = true;
	mode = numeric;
	map->clearCoordinates();
       qDebug()<<"SUPPORT SETCO geoCode coord"<<QString::number(l,'f',8)<<lo;
        map->geoCode(QString::number(l,'f',8) + "," + QString::number(lo,'f',8),mode );

	lat = l; 
	lon = lo;
	
	map->loadCoordinates(l,lo);
	
}
QSize  Support::minimumSizeHint() const
 {
     return QSize(200, 500);
 }
void  Support::paintEvent(QPaintEvent* /*event*/)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing,true);
// 	int side = qMin(width(),height());
// 	
// 	int x = (width() - side / 2);
//  	int y = (height() - side / 2);
// 	painter.setViewport(x, y, side, side);
	 
  
//          qDebug()<<"Support";
// 	painter.setWindow(-50,-50,50,50);
	
}
QString Support::cityLocal()
{
	return city;
}
QPointF Support::coordinates()

{
	 
		return co;

}
void Support::updatePoint(double a, double b,QString& s)
{
	lat = a;
	lon = b;
         qDebug()<<"SUPPORT updatePoint "<<QString::number(lat,'f',8)<<QString::number(lon,'f',8)<<s;
	emit pointChanged(lat,lon,s);
}
