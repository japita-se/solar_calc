#include "mymath.h"
#include "assert.h"
#include <cstdlib>
#include "math.h"
#include <QDebug>
#include <QObject>
#include <QPolygonF>
#include <QMessageBox>
#include <QPointF>
#include <QtCore>
#include <cstdlib>
#include "math.h"
#include <cmath>
#define pi 3.14159
#define Go 1367
#define ABS(x) ((x) < 0 ? -(x) : (x))


MyMath::MyMath()
{
}
bool MyMath::isEtero(const QStringList &input)
{
    QString pivot;
    if (input.size()>1)
    {
    pivot = input.at(0);
    for(int i=1;i<input.size();i++)
    {
        if (input.at(i)!=pivot)
            return true;
    }
    return false;
}
}

int MyMath::countCross(const QPolygonF &a)
/* Count the number oz zero crossing */
{
    int c = 0;
    if (a.size()>1){
        for(int i=1;i<a.size();i++)
            if (a.at(i).y() * a.at(i-1).y() < 0)
                c++;

    }
    else
        return 0;
    return c;
}
int MyMath::npvCross(const QPolygonF &a)
/* Check if a, intended as NPV vector, cross the zero */
{
    for(int i=0;i<a.size();i++)
        if (a.at(i).y()>0)
            return i;
    return -1;
}
int MyMath::findPoint(loc localita, const QVector<int> &index,const QPolygonF & region,int rSize)
        /* Find the near point in a cube in R^n */
{
   // qDebug()<<"MYMATH index"<<index;
    double minDistance=9999999;
    double latMed,distance;
    int firstId = index.at(0);
    for (int i=0; i<rSize;i++) {
            latMed = (pi/180*localita.lat+ region.at(i).x())/2;
            distance = sqrt( pow( (pi/180*localita.lat-region.at(i).x()),2)
            + pow( cos(latMed)*(pi/180*localita.lon-region.at(i).y()) ,2));
              //  qDebug()<<"DISTANCES "<<i<<distance<<index.at(i);
            if (distance < minDistance) {
                    minDistance = distance;
                    firstId = index.at(i);
                    }
    }
    if (minDistance==9999999)
            firstId = -1;

    return firstId;
}

QVector<double> MyMath::seekInFile(const QString file,qint64 pos,int length)
{
    QVector<double> o;
    QFile f(file);
    QStringList s;
    QString line;
    bool a;
     if (f.open(QIODevice::ReadOnly)){
    QTextStream in(&f);

    a = in.seek(pos * length);
    line = in.readLine();
    s = line.split(" ");
    o = toVectorDouble(s);
    qDebug()<<"MYMATH seekFile"<<s<<o<<file<<pos * length << a<<line;
}
    else
       qDebug()<<"MYMATH seekFile error "<<o<<file;
    return  o;
}
QPolygonF MyMath::subtract(const QPolygonF &a,const QPolygonF &b)
{
    QPolygonF o;
    int s;
    if (a.size()!=b.size())
        s = min((double)(a.size()),(double)(b.size()));
    else
        s = a.size();
    for (int i=0;i<s;i++)
        o <<QPointF(i, a.at(i).y() - b.at(i).y());
    return o;
}
QPolygonF MyMath::add(const QPolygonF &a,const QPolygonF &b)
{
    QPolygonF o;
    int s;
    if (a.size()!=b.size())
        s = min((double)(a.size()),(double)(b.size()));
    else
        s = a.size();
    for (int i=0;i<s;i++)
        o <<QPointF(i, a.at(i).y() + b.at(i).y());
    return o;
}
double MyMath::inflate(int year,double rate,double value)
        /*rate must be lessthan 1 */
{
    if (rate>1)
    {
        qDebug()<<"MYMATH WARNING INFLATION RATE >1"<<rate;
        rate = 0;
    }

    return value * pow((1+rate),year);
}






QVector<int> MyMath::numOfWeekendsAndRests(QDate a,int day)
/* Returns the number of weekends in a month and the number of rest days given a day in a week */
/* o(0) = # of saturdays, o(1) = #num of sundays, o(2) = # num of closing dasy*/
{
	
	QVector<int> o;
        int dw,fineMese;
	o.fill(0,3);
        fineMese = a.daysInMonth();
        for(int i=1;i<=fineMese;i++){

		dw =a.dayOfWeek(); 
                if (dw==6){
			o[0]++;

                    }
		if (dw==7)
			o[1]++;
		if (dw==day)
			o[2]++;
// 		qDebug()<<"MYAMT DATE"<<a<<dw;
		a = a.addDays(1);
	}
	return o;
}
void MyMath::scale(QVector<double> &a,double value)
{
	for(int i=0;i<a.size();i++)
		a.replace(i,a.at(i)*value);
}
void MyMath::scale(QPolygonF &a,double value)
{
	for(int i=0;i<a.size();i++)
		a.replace(i,QPointF(i,a.at(i).y()*value));
}

bool MyMath::exportToText(QString& fileName,QVector<double>& data)
        {
                QFile file(fileName);
                if( file.open(QFile::WriteOnly)){
                        QTextStream out(&file);
                        for(int i=0;i<data.size();i++)
                        out<<i<<"\t"<<data.at(i)<<"\n";
                        return true;
                }
                else
                        return false;
        }
bool MyMath::exportToText(QString& fileName,QPolygonF& data)
{
	QFile file(fileName);
	if( file.open(QFile::WriteOnly)){
		QTextStream out(&file);
		for(int i=0;i<data.size();i++)
                    out<<data.at(i).x()<<"\t"<<data.at(i).y()<<"\n";
                out.flush();
		return true;
	}
	else
		return false;
}
bool MyMath::exportToText(QString& fileName,double* data,int size)
{
	QFile file(fileName);
	if( file.open(QFile::WriteOnly)){
		QTextStream out(&file);
		for(int i=0;i<size;i++)
		out<<data[i]<<"\t"<<data[i]<<"\n";
                out.flush();
		return true;
	}
	else
		return false;
}
double MyMath::W_1(double hour, double T)
{
	double s = pow((hour/T),2);
	if ( (s-1)>0.0000000002 )
	return 0;
	else
	return 4/pi * sqrt(1- pow((hour/T),2));

}
QVector<double> MyMath::toVectorDouble(const QStringList &a)
{
        QVector<double> t;
        bool ok;
        double temp;
        for(int i = 0;i<a.size();i++)
                {
                temp = a.at(i).toDouble(&ok);
                if (ok)
                    t.append(a.at(i).toDouble());
                else
                    t.append(-1);

               // qDebug()<<"MYMATH TO VECTOR"<<a.at(i).toInt();
                }
        return t;
}
QVector<int> MyMath::toVector(const QStringList &a)
{
	QVector<int> t;
	for(int i = 0;i<a.size();i++)
		{
                t.append(a.at(i).toInt());
               // qDebug()<<"MYMATH TO VECTOR"<<a.at(i).toInt();
		}
	return t;
}
QString MyMath::toString(const QVector<double> &a,QString &s)
        /*Transform a Vecotr in a string */
        /* made of all elements*/
{
    QStringList o;
    for(int i=0; i< a.size(); i++)
        o << QString::number(a.at(i)) ;
    return o.join(s);
}
QString MyMath::toString(const QPolygonF &a,QString &s)
        /*Transform a PolygonF in a string */
        /* made of all elementer of points */
{
    QStringList o;
    for(int i=0; i< a.size(); i++)
        o << QString::number(a.at(i).x()) << QString::number(a.at(i).y());
    return o.join(s);
}

QStringList MyMath::toStringList(const QVector<int> &a)
{
	QStringList t;
	for(int i = 0;i<a.size();i++)
		{
		t.append(QString::number(a.at(i)));
		}
	return t;
}
QStringList MyMath::toStringList( double *a,int size)
{
    QStringList o;
    for (int i=0;i<size;i++)
        o << QString::number(a[i]);
    return o;
}

QStringList MyMath::toStringList(const QVector<double> &a)
{
        QStringList t;
        for(int i = 0;i<a.size();i++)
                {
                t.append(QString::number(a.at(i)));
                }
        return t;
}
int MyMath::refMonthDay(int m)
{

	switch (m){
case 0: return 17; break;
case 1: return 16; break;
case 2: return 16; break;
case 3: return 15;break;
case 4: return 15;break;
case 5: return 21; break;
case 6: return 17;break;
case 7: return 15;break;
case 8: return 15;break;
case 9: return 15;break;
case 10: return 14;break;
case 11: return 10;break;
default: return 0; break;
}
}

int MyMath::refDay(int m)
{
	switch (m){
case 0: return 17; break;
case 1: return 47; break;
case 2: return 75; break;
case 3: return 105;break;
case 4: return 135;break;
case 5: return 172; break;
case 6: return 198;break;
case 7: return 228;break;
case 8: return 255;break;
case 9: return 288;break;
case 10: return 318;break;
case 11: return 344;break;
}
}
void MyMath::tiltedRiseSet(double tilt,double decl,double azimuth,double latitude,double os ,double *out)
{	
	/* altra via per calcolare il tramonto e l'alba vera E/ Anderson*/

        double A,B,app,sco,c1,c2;
        c1 = c2 = A = B =0;
	if (fabs(tilt)>0.0002 & fabs(azimuth) >0.0002)
	{
		A = cos(latitude)/(sin(-azimuth)*tan(tilt)) + sin(latitude)/tan(-azimuth);
		B = tan(decl)*(cos(latitude)/tan(-azimuth) - sin(latitude)/(sin(-azimuth)*tan(tilt)));
		if (azimuth>0.00002)
		{
		/* West  of South*/
                     c1 =(A*B + sqrt((pow(A,2) - pow(B,2) +1)))/(pow(A,2)+1);
                     c2 =(A*B - sqrt((pow(A,2) - pow(B,2) +1)))/(pow(A,2)+1);
                        app = -acos(c1);
                        sco =  acos(c2);
                        if (c1>1)
                            app = pi;
                        if (c1<-1)
                            app = -pi;
                        if (c2>1)
                            sco = pi;
                        if (c2<-1)
                            sco = -pi;
		}
		else
		{
		/* East of South */
                    c1 =(A*B + sqrt((pow(A,2) - pow(B,2) +1)))/(pow(A,2)+1);
                    c2 =(A*B - sqrt((pow(A,2) - pow(B,2) +1)))/(pow(A,2)+1);
                         app  = -acos(c2);
                         sco  =acos(c1);
		}
	/* Compare with omegas */
	if (0.00002>  (app + os ))   app   = -os ;	
	if ((os  -sco)< 0.00002)  sco  = os ;
// 	qDebug()<<"OptimimPlot TiltedSurface if";
	}
	else
	{
// 		qDebug()<<"OptimimPlot TiltedSurface else";
			app = -os;
			sco = os;
	}
	
        //Check//
        //TODO: double appearance of the sun in the sky for steep slope//
        if (app > sco)
            app = sco; /* ALWAYS SHADED */


        out[0] = std::isnan(app) ? 99999 : app;
        out[1] = std::isnan(sco) ? 99999 : sco;
	
}

QVector<double> MyMath::tiltedRiseSet(double tilt,double azimuth,double latitude,int month)
/* input in radiants*/
{	
	/* altra via per calcolare il tramonto e l'alba vera E/ Anderson*/
	QVector<double> out;
        double A,B,app,sco,os,c1,c2;
        c1 = c2 = A = B =0;
	int n=refDay(month);
	double decl = 23.45*pi/180 * sin(2*pi*(284+n)/365);
	double tempArg = tan(latitude-tilt)*tan(decl);
		if (fabs(tempArg)>1)
			/* The sun never rise/set*/
			
			os = pi;
		else

        		os = acos(-tempArg);//rad

	if (fabs(tilt)>0.0002 & fabs(azimuth) >0.0002)
	{
		A = cos(latitude)/(sin(-azimuth)*tan(tilt)) + sin(latitude)/tan(-azimuth);
		B = tan(decl)*(cos(latitude)/tan(-azimuth) - sin(latitude)/(sin(-azimuth)*tan(tilt)));
		if (azimuth>0.00002)
                {
                /* West  of South*/
                     c1 =(A*B + sqrt((pow(A,2) - pow(B,2) +1)))/(pow(A,2)+1);
                     c2 =(A*B - sqrt((pow(A,2) - pow(B,2) +1)))/(pow(A,2)+1);
                        app = -acos(c1);
                        sco =  acos(c2);
                        if (app > sco)
                            app = sco; /* ALWAYS SHADED */
                        if (c1>1)
                            app = pi;
                        if (c1<-1)
                            app = -pi;
                        if (c2>1)
                            sco = pi;
                        if (c2<-1)
                            sco = -pi;
                }
                else
                {
                /* East of South */
                    c1 =(A*B + sqrt((pow(A,2) - pow(B,2) +1)))/(pow(A,2)+1);
                    c2 =(A*B - sqrt((pow(A,2) - pow(B,2) +1)))/(pow(A,2)+1);
                         app  = -acos(c2);
                         sco  =acos(c1);
                }
	/* Compare with omegas */
	if (0.00002>  (app + os ))   app   = -os ;	
	if ((os  -sco)< 0.00002)  sco  = os ;
// 	qDebug()<<"OptimimPlot TiltedSurface if";
	}
	else
	{
// 		qDebug()<<"OptimimPlot TiltedSurface else";
			app = -os;
			sco = os;
	}

        //Check//
        //TODO: double appearance of the sun in the sky for steep slope//

        app = std::isnan(app) ? 99999 : app;
        sco = std::isnan(sco) ? 99999 : sco;
	out<< app << sco;
	return out;
	
}

QVector<double> MyMath::rb(double lat,double tilt,double azi,int month,int year,int mode)
{
// All input in radians!
        double d,omegas_,omegasH_,omega_app_,omega_sco_, tempArg,tempArg2;
        double a[2],T,Uh,U,V,Th,Hbh_,Hb_,Rb_,RbBiAx_,localIncl;
	int n;
	//Tutti gli angoli in rad(i)ianti
	 
        localIncl = lat>=0 ? tilt : -tilt;
        



	double x,totalDayLen;
	/* Mode 0: representative day of a month
	/* Mode 1: all days in the year */
	if (mode==0)
		n=refDay(month);
	if (mode==1)
		n = month;/*it is a day!*/

	d = 23.45*pi/180 * sin(2*pi*(284+n)/365);

        T = sin(d)*( sin(lat)*cos(localIncl) -cos(lat)*sin(localIncl)*cos(azi) );
	Th = sin(d)*(sin(lat));
        U = cos(d)*( cos(lat)*cos(localIncl) + sin(lat)*sin(localIncl)*cos(azi));
	Uh = cos(d)*(cos(lat));
        V = cos(d)*(sin(localIncl)*sin(azi));

// Irradiazione extra atmosferica sul piano orizzontale in MJ/m2giorno (media mensile)
//Serve per calcolare Kt = Hg/Hho;
	double r =(1+0.033*cos(2*pi*n/365));



		/* Here we do not modify class variable */
		//angolo d(i)el tramonto astronomico
		 tempArg = tan(lat-localIncl)*tan(d);
		if (fabs(tempArg)>1)
			/* The sun never rise/set*/
			
			omegas_ = pi;
		else

        		omegas_ = acos(-tempArg);//rad

		tempArg2 = tan(lat)*tan(d);
		if (fabs(tempArg2)>1)
			/* The sun never rise/set*/
			omegasH_ = pi;
		else
        		omegasH_ = acos(-tempArg2);//rad	

		
		tiltedRiseSet(localIncl,d,azi,lat,omegas_,a);
		omega_app_  = a[0];
		omega_sco_ = a[1];
		if ((fabs(omega_app_)>pi) || (fabs(omega_sco_)>pi)){
 			totalDayLen = 24;
			/* The sun never rise/set */
		}
		else{
 		
	// 		totalDayLen.append( 12*(sco_ - app_)/pi); 
			totalDayLen = 12*(omegasH_/pi);
		}

		 
	
		Hbh_ = (omegasH_>pi) ? 0 :
		3.6*(24/(2*pi))*0.001*2*r*Go*(Th*omegasH_+Uh*sin(omegasH_));

		Hbh_  = Hbh_ <0 ? 0 : Hbh_; /* The sun never rise */

		Hb_=  ((omega_sco_>pi) || (omega_app_)>pi) ? 0 :
		3.6*(24/(2*pi))*r* 0.001 * Go *( T*(omega_sco_ - omega_app_) + U*(sin(omega_sco_) - sin(omega_app_)) - V*(cos(omega_sco_)-cos(omega_app_)) );

//		 if (localIncl<0.0000000002) {  Hb_=Hbh_;}
                if (Hbh_<0.0000002)  {
				#ifdef DEBUG
				qDebug()<<"MM  MYMATH rb, sun never rise ";
				#endif
				Rb_	    = 0;
				}

  		else
  		Rb_ =  Hb_/Hbh_;
// 		assert(Hbh_!=0);
		
		RbBiAx_ = (Hbh_<0.00000000002)? 0 : ((3.6*24/pi) * Go*0.001* r * omegasH_)/ Hbh_;
                          #ifdef DEBUG
                qDebug()<<"MyMATH rb (mode=0,tilt local), (tilt,mese)"<<Rb_<<localIncl*180/pi<<month<<"T="<<T<<"Th="<<Th<<"Hb="<<Hb_<<"Hho="<<"Hbh="<<Hbh_<<omegas_<<omegas_<<omega_app_<<omegasH_<<omega_sco_<<omega_app_;
                         #endif
		  x = acos((Th*( omega_sco_- omega_app_)+Uh*(sin(omega_sco_)-sin(omega_app_)))*(1/(2*pi)));/*this is the angle of tracker */
// 			dailyVarTilt <<QPointF(i,x);
	return QVector<double>()<<Rb_<<Hbh_<<RbBiAx_<<totalDayLen<<omega_sco_<<omega_app_<<omegas_<<omegasH_<<x;
	
	 
	 
 	
  
}

double MyMath::mean(const QVector<double>& a)
{	
	double s;
	s=0;
	for(int i=0;i<a.size();i++){
		s+=a.at(i);
// 		qDebug()<<"MMATH "<<s;
}
	return (a.size()==0) ? 0 :s/a.size();
}
double MyMath::mean(const QPolygonF& a)
{	
	double s;
	s=0;
	for(int i=0;i<a.size();i++){
		s+=a.at(i).y();
// 		qDebug()<<"MMATH "<<s;
}
	return (a.size()==0) ? 0 :s/a.size();
}
double MyMath::realNoct(double t,int mounting,double mountingHeight)
{
	switch (mounting) {
		case rack:
			return t-3;
			break;
		case direct:
			return t+18;
			break;
		case standoff:
			return t + MyMath::linear(2.5,11.0,7.5,2.0,mountingHeight); /* INOCT values, h=2.5;7.5, x=11;2 degree C */
		break;
	default:
	return t;
	}
}
QStringList MyMath::listOfNumber(int start, int stop)
{
	QStringList a;
	for(int i=start;i<=stop;i++)
		a<<QString::number(i);
	return a;
}
QStringList MyMath::nullList()
{
	return QStringList()<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0;
}
double MyMath::uniform()
{
// 	qDebug()<<"MM uniform"<<1.0*rand()/RAND_MAX;
	return 1.0*rand()/RAND_MAX;
}
double MyMath::pwf(double D, int n)
{
	if (fabs(D)<0.000000002)
	{
		return n;
	}
	else
		return (1-pow((1+D),-n))/D;
}
double MyMath::var(const QVector<double> &a)
{
	double m =0;
	double v=0;
	for(int i=0;i<a.size();i++)
		m +=a.at(i)/a.size();
	for(int j=0;j<a.size();j++)
		v +=pow((a.at(j)-m),2)/(a.size()-1);
	return v;
}
double MyMath::randn()
{
	double x1, x2, w, y1, y2;
 	w =0;
         while ( w >= 1.0 || w==0) {
                 x1 = 2.0 * uniform() - 1.0;
                 x2 = 2.0 * uniform() - 1.0;
                 w = x1 * x1 + x2 * x2;
// 		qDebug()<<"MM randn"<<w;
         }  

         w = sqrt( (-2.0 * log( w ) ) / w );
         y1 = x1 * w;
         y2 = x2 * w;
// 	qDebug()<<"MM randn"<<y1;
	return y1;

}
double MyMath::cumSum(const QPolygonF &a)
{
        double o;
        o=0;
        for(int i=0;i<a.size();i++){
// 		qDebug()<<"MyMath cumSum "<<a.size()<<a[i];
                o += a.at(i).y();
        }
        return o;
}
int MyMath::cumSum(QVector<int> a)
{
	int o;
	o=0;
	for(int i=0;i<a.size();i++){
// 		qDebug()<<"MyMath cumSum "<<a.size()<<a[i];
                o += a.at(i);
	}
	return o;
}
double MyMath::cumSum(QVector<double> a)
{
	double o;
	o=0;
	for(int i=0;i<a.size();i++){
// 		qDebug()<<"MyMath cumSum "<<a.size()<<a[i];
                o += a.at(i);
	}
	return o;
}
double MyMath::cumSum(QVector<double> a, int start,int stop)
{
	double o;
	int rs,rst;
	o=0;
	if (start<stop) 
		return 0;

	if (stop>a.size())
		rs = a.size();
	else
		rs = stop;
	if (start>a.size())
		rst = a.size();
	else
		rst = start;

	for(int i=rs;i<=rst;i++){
// 		qDebug()<<"MyMath cumSum "<<a.size()<<a[i];
                o += a.at(i);
	}
	return o;
}
QStringList MyMath::stringSerie(int start,int stop)
{
	QStringList a;
	for(int i=start;i<=stop;i++)
		a<<QString::number(i);
	return a;
}
bool  MyMath::clockWise(double after,double before)
/* This function returns true if the angle b follow a in a clockwise fashion*/

{
	
	int a = pos(after);
	int b = pos(before);
//  	qDebug()<<"pos(after)<pos(before)"<<a<<b<<after<<before<<(a<b)<<(a==b)<<(a>b);
	if  (a<b)
			return true; 
	if (a>b)
	{
		if ( a==4 && b==1) 
		 
			return true;
		else
			return false;
	}
// 	if (a>b)
// 			return false;
	
	if ((a==b) && (after-before>=0.00000002))
				return false;
		else
				return true;
	
}
int MyMath::pos(double value)
/* This function returns the quadrant number  of an angle */
{
	double c = cos(value);
	double s = sin(value);
	if (c>=0.0000002 && s>=0.0000002) {  return 1;}
	if (c<0 && s>=0.0000002) { return 2;}
	if (c<0 && s<0) { return 3;}
	if (c>=0.00000002 && s<0) { return 4;}
	return 1;
}
double MyMath::convertCoFromDegree(double lat,double min,double sec)
{
        return (lat + min/60 + sec/3600.0);
}
double MyMath::convertCoFromDegree(int lat,int min,int sec)
{
        return (lat + min/60 + sec/3600.0);
}
int MyMath::sign(double a)
{
	return a>0 ? 1 : (a<0 ? -1:0); 
}
int MyMath::degree(double a)
{
	return (int)(a);
}
double MyMath::minute(double a)
{
        double t,intpart;
        double o;
        o = decimal(a) * 60.0;
        t = modf(o , &intpart);

        return intpart;
}
double MyMath::seconds(double a)
/* a is a geolocation in sessagesimal degress */
{

        double m = (decimal(a) * 60.0);
        double s =  decimal(m) * 60.0;
        s = s < 0.00000000002 ? 0 : s;

        return  s;
}

double MyMath::decimal(double m)
{	double integral,t;
if (fabs(ceil(m) -m) <0.00000002 || fabs(floor(m) - m) < 0.0000002)
    return 0;
        t = modf(m,&integral);
        t = t< 0.000000002 ? 0 : t;

        return t;
}
double MyMath::min(const QVector<double>& a)
{
double m;
    if (a.size()==0)
        return 0;
    if (a.size()==1)
        return a.at(0);
    m = a.at(0);
    for(int i=1;i<a.size();i++)
        m = m > a.at(i) ? a.at(i) : m;
    return m;
}
double MyMath::min(const QPolygonF& a)
{
double m;
    if (a.size()==0)
        return 0;
    if (a.size()==1)
        return a.at(0).y();
    m = a.at(0).y();
    for(int i=1;i<a.size();i++)
        m = m > a.at(i).y() ? a.at(i).y() : m;
    return m;
}
double MyMath::min(double *a,int size)
{
	double min = a[0];
// 	int size = sizeof(a)/sizeof(double);
	
	for(int i=0;i<size;i++) { min = a[i] < min ? a[i] : min; }	
// 	qDebug()<<size<<" " << min;
	return min;
}
double MyMath::max(double a,double b)
{
    return ((a-b)>=0.0000000002? a:b);
}
double MyMath::max(const QVector<double>& a)
{
	if (a.size()>0){
	double m=a.at(0);
	for(int i=0;i<a.size();i++)
		m = (m-a.at(i))<0.000000002 ? a.at(i) : m;
	return m;
	}
	else
	return 0;
}

double MyMath::max(const QPolygonF& a)
{
	if (a.size()>0){
	double m=a.at(0).y();
	for(int i=0;i<a.size();i++)
		m = (m-a.at(i).y())<0.000000002 ? a.at(i).y() : m;
	return m;
	}
	else
	return 0;
}
double MyMath::max(double *a,int size)
{
	double max = a[0];
// 	int size = sizeof(a)/sizeof(a[0]);
	for(int i=0;i<size;i++) { max = a[i] > max ? a[i] : max; }	
	return max;
}

double MyMath::cumSum(double *a,int size)
{
	double cumSum = a[0];
// 	int size = sizeof(a)/sizeof(a[0]);
	for(int i=1;i<size;i++) { cumSum+=a[i]; }	
	return cumSum;
}
double MyMath::cumSumMonthly(double *a,int size)
{
	double cumSum = a[0];
	int ddend;
// 	int size = sizeof(a)/sizeof(a[0]);
	for(int i=0;i<size;i++) { 
		
		 	if (i==1)
			{
				ddend=29;
			} 
			else
			{
				if (i>=7)
				{
					if (!(i%2))   ddend=30;
					if (!((i+1)%2)) ddend=31 ;
				}
				else {
	
					if (!(i%2))   ddend=31;
					if (!((i+1)%2)) ddend=30 ;
					
					
				}
			}
		cumSum+=a[i]*ddend;//we suppose that a[i] is the mean value inside a month
//
	}
	return cumSum;
}
QPolygonF MyMath::cumulative(const QPolygonF &a)
{
    QPolygonF o;
    double sum = 0;
    for(int i=0;i<a.size();i++){
        sum +=a.at(i).y();
        o << QPointF(a.at(i).x(),sum);
        }
        return o;

}

double MyMath::min(double a, double b)
{
	return a<=b ? a : b;
}


/* return a point on a line */
double  MyMath::linear(double x1,double y1,double x2,double y2, double x)
{
	double  y,m,c;
	m = (y2-y1)/(x2-x1);
	c = y1 - (m*x1);
	y = m*x +c;
// 	qDebug()<<"Interpolation "<<y;
	return y;
}

/* Geometrical functions */
bool MyMath::isOrdered(const QPolygonF &polygon)
{
	double temp = polygon.at(0).x();
	for(int i=1;i<polygon.size();i++) {
		if ( polygon.at(i).x()< temp)
			return false;
		else
		        temp = polygon.at(i).x();
	}
	return true;
}
double MyMath::rightValue(const QPolygonF &polygon)
{
	double m;
	m = polygon.at(0).x();
	for(int i=0;i<polygon.size();i++)
		m = polygon.at(i).x() > m ? polygon.at(i).x() : m;
	return m;
}
double MyMath::leftValue(const QPolygonF &polygon)
{
	double m;
	m = polygon.at(0).x();
	for(int i=0;i<polygon.size();i++)
		m = polygon.at(i).x() < m ? polygon.at(i).x() : m;
	return m;
}
QVector<double> MyMath::convertToDegree(QVector<double> vec)
{

        QVector<double> out;
       // qDebug()<<"MYMATH "<<vec.size();
        for(int i=0;i<vec.size();i++){
                out << vec.at(i)*180.0/pi;


            }
        return out;
}
void MyMath::convertToDegree(double* vec,int size)
{
	for(int i=0;i<size;i++)
		vec[i] = vec[i]*180/pi;
}
bool MyMath::lessThanPoint(const QPointF &p1, const QPointF &p2)
{
//   	if (fabs((p1.x()-p2.x()))<0.000001)
  		/* Punti con la stessa ascissa */
//   		return ( p1.y()<p2.y() );
	return ( p1.x() < p2.x() );
			
}
int MyMath::yearEnd(int i)
{
    if (QDate::isLeapYear(i))
	{
		return 366;
	qDebug()<<"LEAP YEAR";
	}
	else
        {
		return 365;
            }
}

bool MyMath::leapYear(int anno)
{
	return ((anno % 4 == 0 && anno % 100 != 0) || anno % 400 == 0);	
}

int MyMath::monthEnd(int mm,int year)

{
	int ddend;
	// Calendario gregoriano, 1<=mm<=12
			if (mm==2)
			{
                            if (QDate::isLeapYear(year))
				ddend=29;
				else
				ddend=28;
			} 
			else 
			{
				if ((mm>=8))
				{
					if (!(mm%2))   ddend=31;
					if (!((mm+1)%2)) ddend=30 ;
				}
				else
				{
				
					if (!(mm%2))   ddend=30;
					if (!((mm+1)%2)) ddend=31 ;
					
					
				}
			}
return ddend;
}
int MyMath::dayOfYear(int year,int month, int day)
{
	int d =0;
	for(int i=1;i<=12;i++)
	{
		if (i==month)
		{
		d+=day;
		return d;
		}
		else
		d+=monthEnd(i,year);
	}

}
QString MyMath::checkFormat(const QString &source, const QString &format)
{
	QString out;
	QStringList a;
	a = source.split(".");
	if (a.size()>1)
		if ( (a.lastIndexOf(format)) == (a.size()-1) ) 
			out = source;
		else
			out = source + "." + format;
	else
	    out = source + "." + format;
	return out;

}
QString MyMath::monthsIta(int i)
{
    switch (i) {
            case 1:
            return "Gen";
            break;
            case 2:
            return "Feb";
            break;
            case 3:
            return "Mar";
            break;
            case 4:
            return "Apr";
            break;
            case 5:
            return "Mag";
            break;
            case 6:
            return "Giu";
            break;
            case 7:
            return "Lug";
            break;
            case 8:
            return "Ago";
            break;
            case 9:
            return "Set";
            break;
            case 10:
            return "Ott";
            break;
            case 11:
            return "Nov";
            break;
            case 12:
            return "Dic";
            break;
            default:
            return QString();

    }
}

QString MyMath::months(int i)
{
	switch (i) {
		case 1:
		return QObject::tr("Gen");
		break;
		case 2:
		return QObject::tr("Feb");
		break;
		case 3:
		return QObject::tr("Mar");
		break;
		case 4:
		return QObject::tr("Apr");
		break;
		case 5:
		return QObject::tr("Mag");
		break;
		case 6:
		return QObject::tr("Giu");
		break;
		case 7:
		return QObject::tr("Lug");
		break;
		case 8:
		return QObject::tr("Ago");
		break;
		case 9:
		return QObject::tr("Set");
		break;
		case 10:
		return QObject::tr("Ott");
		break;
		case 11:
		return QObject::tr("Nov");
		break;
		case 12:
		return QObject::tr("Dic");
		break;
		default:
		return QString();
	
	}
}
QStringList MyMath::monthFull()
{
	return  QStringList()<<QObject::tr("Gennaio")<<
QObject::tr("Febbraio")<<
QObject::tr("Marzo")<<
QObject::tr("Aprile")<<
QObject::tr("Maggio")<<
QObject::tr("Giugno")<<
QObject::tr("Luglio")<<
QObject::tr("Agosto")<<
QObject::tr("Settembre")<<
QObject::tr("Ottobre")<<
QObject::tr("Novembre")<<
QObject::tr("Dicembre");
}
QStringList MyMath::monthsList()
{
	QStringList a;
	for(int i=1;i<=12;i++)
	a<<months(i);
	return a;
		
}
QVector<int> MyMath::serie(int start, int stop)
{
	QVector<int> q;
	if (start<stop){
		for(int i=start;i<stop;i++)
			q<<i;
	return q;
	}
	else
	return QVector<int>();
}
QString  MyMath::serieCellTable(int start, int stop)
{
	QString q="";
	if (start<stop){
		for(int i=start;i<stop;i++)
			q+="<td>" + QString::number(i) + "</td>";
	return q;
	}
	else
	return QString();
}

double MyMath::convertToDouble(const QString &input)
{
    double iPart, r;
    int l;
    QStringList comb;
    QString dPivot;

    comb = input.split(".");

    iPart = comb.size()>0 ? comb.at(0).toDouble(): input.toDouble();

    if (comb.size()>1){
        dPivot = comb.at(1);
        l = dPivot.size();
        r = 0;
        for(int i=0;i<l;i++)
        {
           // qDebug()<<"MYMATH decimals"<<dPivot.at(i);
                r += QString(dPivot.at(i)).toDouble()/pow(10,i+1);
        }
}
    r = iPart + r;

    return r;
}
