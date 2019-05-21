 // #define DEBUG
#include "assert.h"
#include "settings.h"
#include <QtGui>
#include <QSvgGenerator>
#include <qwt_picker.h>
#include <qwt_plot_picker.h>
#include "optimumplot.h"
#include <qwt_plot.h>
#include <qwt_plot_canvas.h>
#include <qwt_scale_draw.h>
#include <qwt_scale_widget.h>
#include <qwt_painter.h>
#include <qwt_plot_grid.h>
#include "mymath.h"
#include <qwt_plot_curve.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
// #include <qwt_data.h>
#include <qwt_text.h>
#include <cmath>

#define sign MyMath::sign
#define pi 3.14159
#define Go 1367
OptimumPlot::OptimumPlot(QWidget* parent): QwtPlot(parent)
{
	
	setWindowIcon(QIcon(":/images/app.png"));
	setWindowTitle("SolarCalc - Radiazione diretta ideale");
	this->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this,SIGNAL(customContextMenuRequested(const QPoint &  )),this,SLOT(popUpMenu(const QPoint &)));
	
        u<<tr("[MJ/m2]")<<tr("[kWh/m2]");
	
	// SOME INITIALIZATION
	 
	 QwtPainter::setDeviceClipping(false);
       
// 	#ifdef Q_WS_X11
//     /*
//        Qt::WA_PaintOnScreen is only supported for X11, but leads
//        to substantial bugs with Qt 4.2.x/Windows
//      */
//     canvas()->setAttribute(Qt::WA_PaintOnScreen, true);
// 	#endif
  	  alignScales();

	// Reference days
	m_[0] = 17;
	m_[1] = 47;
	m_[2] = 75;
	m_[3] = 105;
	m_[4] = 135;
	m_[5] = 162; 
	m_[6] = 198;
	m_[7] = 228;
	m_[8] = 255;
	m_[9] = 288;
	m_[10] = 318;
	m_[11] = 344;

			 monthLabels[0] = "Gen ";
			 monthLabels[1] ="Feb ";
			 monthLabels[2] ="Mar ";
			 monthLabels[3] ="Apr ";
			 monthLabels[4] ="Mag ";
			 monthLabels[5] ="Giu ";
			 monthLabels[6] ="Lug ";
			 monthLabels[7] ="Ago ";
			 monthLabels[8] ="Sett";
			 monthLabels[9] ="Ott ";
			 monthLabels[10] ="Nov ";
			 monthLabels[11] ="Dec ";
	
	// Other settings
	bestInclHb = 0;	
        startIncl  = 10;
        endIncl    = 90;
        stepIncl   = 20;
        varInclGenerated = false;
	for (int i=0;i<=ceil((endIncl-startIncl)/stepIncl)+1;i++) { 
				plotOptiMarker[i] = new QwtPlotMarker();
				plotOptiMarker[i]->attach(this);
				plotOpti[i] = new QwtPlotCurve();
				
				plotOpti[i]->attach(this);
				}
	maxLegend = new QwtPlotMarker();

	// Set default settings
	// Set default settings
	set = new Settings();
	set->setTitle(tr("Radiazione solare ideale diretta"));
	set->setUnit(1);//MJ/m2
	currentUnit = 1;
	set->setAxisY(tr("Media mensile giornaliera"));
	set->setAxisX(tr("Mese"));
	set->setVisible(false);
	connect(set,SIGNAL(accepted()),SLOT(updateSet()));

	QwtText ulabel(u.at(set->getUnit()-1));
	ulabel.setFont(QFont("Times",12,QFont::Normal));
	QwtText xlabel(set->getAxisX());
	xlabel.setFont(QFont("Times",12,QFont::Normal));
	QwtText ylabel(set->getAxisY()+ " " + ulabel.text() );
	ylabel.setFont(QFont("Times",12,QFont::Normal));
	QwtText tlabel(set->getTitle());
	tlabel.setFont(QFont("Times",14,QFont::Normal));
	

	setTitle(tlabel);
	setAxisTitle(QwtPlot::xBottom,xlabel);
        setAxisTitle(QwtPlot::yLeft,ylabel );
	setAxisTitle(QwtPlot::yRight,set->getAxisYRight() + " " + u.at(set->getUnit()-1));
	setTitle(set->getTitle());
	setAxisTitle(QwtPlot::xBottom,set->getAxisX());
        setAxisTitle(QwtPlot::yLeft,set->getAxisY() + " " + u.at(set->getUnit()-1));
	setAxisScale(QwtPlot::xBottom,1,12);
	 

	 
	setCanvasBackground(QColor(Qt::white));
	setMargin(2);
   	picker = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft,       QwtPicker::PointSelection , QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn,this->canvas());
	picker->setRubberBandPen(QColor(Qt::black));
    	picker->setRubberBand(QwtPicker::CrossRubberBand);
	picker->setEnabled(true);
	picker->setTrackerPen(QColor(Qt::black));

	connect(picker, SIGNAL(moved(const QPoint &)),SLOT(moved(const QPoint &)));
	connect(picker, SIGNAL(selected(const QwtPolygon &)),SLOT(selected(const QwtPolygon &)));

	createActions();
	graphPresent = true;
	year = 2009;
resize(600,500);
}
bool OptimumPlot::unitChanged()
{
	int chosenUnit = set->getUnit();
	 if (currentUnit!=chosenUnit) 
		return true;
	else
		return false;
}
void OptimumPlot::swapUnit()
{
// 	qDebug()<<"RR swap unit";
	if (currentUnit==2)
		set->setUnit(1);
	if (currentUnit==1)
		set->setUnit(2);
	
	updateSet();
// 	convertRaw(currentUnit);
// 	convertFit(currentUnit);
// 	drawContents(1);
	
}
void OptimumPlot::updateSet()
{
	QString str;
	int chosenUnit = set->getUnit();
	str = u.at(chosenUnit-1);
	#ifdef DEBUG
	qDebug()<<"update Set"<<set->getTitle();	
	#endif
	setTitle(set->getTitle());
	setAxisTitle(QwtPlot::yLeft,set->getAxisY() + " " + str);
	setAxisTitle(QwtPlot::xBottom,set->getAxisX());
       if (unitChanged()) {
		convert(chosenUnit);
		drawContents(1);
		currentUnit = chosenUnit;
		emit unitChanged(currentUnit);
	}
	 
}
double OptimumPlot::convert(int unit,double value)
{
		double k;
	if (unit==1)
		// convert from kWh to MJ
		k = 3.6;
	if (unit==2)
		// convert from MJ to kWh
		k=1/3.6;
	return value * k;

}
void OptimumPlot::convert(int unit)
{

		for(int i=0;i<12;i++) {
                    Hb[i] = convert(unit,Hb[i]);
		   
                    Hbh[i]= convert(unit,Hbh[i]);
                        if (varInclGenerated){
                            for(int j=0;j<=ceil((endIncl - startIncl)/stepIncl )+1;j++)
                                varHb_[j][i] = convert(unit,varHb_[j][i]);
                        }

		}

}
// void OptimumPlot::computeOmegas()
// {
// }

void OptimumPlot::computeDailyRad(double localIncl,double azi,int year )
/*input in radiants!*/
{
// 	double localIncl=incl;
        //double Rb,Hb_;
        //double d_[366],T_[366],Th_[366],Uh_[366],U_[366],V_[366],Vh_[366],omegasH_,omegas_,app_,sco_ ;
	QVector<double> res;

	dailyRbBiAx.resize(0);
	dailyHho.resize(0);
	dailyRb.resize(0);
	dailyOmegas.resize(0);
	dailyOmegasH.resize(0);
	dailyOmegaApp.resize(0);
	dailyOmegaSco.resize(0);
	dailyVarTilt.resize(0);

	for(int i=0;i<MyMath::yearEnd(year);i++) {
	
		res = MyMath::rb(lat,localIncl,azi,i,year,1);/*use i as month value (actually,it is a day!) */		
		dailyOmegas<< QPointF(i,res.at(6));
	 	dailyOmegasH<< QPointF(i,res.at(7));	
		dailyOmegaApp<<QPointF(i,res.at(5)*180/pi);/*in degree */
	 	dailyOmegaSco<<QPointF(i,res.at(4)*180/pi);/*in degree */
		dailyHho<< QPointF(i,res.at(1));
		totalDayLen<<res.at(3);
		dailyRb<<QPointF(i,res.at(0));
		dailyRbBiAx<<QPointF(i,res.at(2));
		dailyVarTilt <<QPointF(i,res.at(8));

	
	}
        // qDebug()<<"OO Hho daily"<<dailyHho<<MyMath::yearEnd(year);
}

void OptimumPlot::compute(int mode,double tilt)
{
        double localIncl,omegas_,omegasH_,omega_app_,omega_sco_, tempArg,tempArg2;
	double a[2];
	//Tutti gli angoli in rad(i)ianti

 	// Giorno med(i)io mensile nell'anno
/* If we are using this routine for multiple titls, we use the passed value, otherwise we use
   the member variable */

        if (mode == 1){
                localIncl = incl;
                meanDayLen.resize(0);
		varTilt.resize(0);
                omega_sco.resize(0);
                omega_app.resize(0);
                omegas.resize(0);

            }
        if (mode == 0){
                localIncl = tilt;
//                 
            }
        //Check if the lat is negative
        localIncl = lat>=0 ? localIncl : -localIncl;

for(int i=0;i<12;i++) {
	double x;
	int n=m_[i];
	d[i] = 23.45*pi/180 * sin(2*pi*(284+n)/365);
  	#ifdef DEBUG 
        qDebug()<<"d="<<d[i]*180/pi<<"Lat="<<lat<<"Azi="<<azi<<"localIncl="<<localIncl;
  	#endif
        T[i] = sin(d[i])*( sin(lat)*cos(localIncl) -cos(lat)*sin(localIncl)*cos(azi) );
	Th[i] = sin(d[i])*(sin(lat));
        U[i] = cos(d[i])*( cos(lat)*cos(localIncl) + sin(lat)*sin(localIncl)*cos(azi));
	Uh[i] = cos(d[i])*(cos(lat));
        V[i] = cos(d[i])*(sin(localIncl)*sin(azi));
	#ifdef DEBUG
  	qDebug()<<"T="<<T[i]<<"U="<<U[i]<<"V="<<V[i]<<"Th="<<Th[i]<<"Uh[i]="<<Uh[i];
	#endif
	// Irraggiamento med(i)io mensile su piano orizzontale extraatm. (Ho)

 	
	

	
	
 	//Angolo della comparsa e scomparsa del sole

/****** UNI 84 77, too complicated *///


	 
		
		
	 
	 

// Irradiazione extra atmosferica sul piano orizzontale in MJ/m2giorno (media mensile)
//Serve per calcolare Kt = Hg/Hho;
	double r =(1+0.033*cos(2*pi*n/365));
	if (mode==1){
		
		//angolo d(i)el tramonto astronomico
		tempArg = tan(lat-localIncl)*tan(d[i]);
		if (fabs(tempArg)>1)
			/* The sun never rise/set*/
// 			omegas[i] = pi;
			omegas<<pi;/*10 Dec 2009*/
			
		else

//         		omegas[i] = acos(-tempArg);//rad	
			omegas<< acos(-tempArg);/*10 Dec 2009*/

		tiltedRiseSet(localIncl,d[i],azi,lat,omegas[i],a);
// 		omega_app[i]  = a[0];
// 		omega_sco[i] = a[1];
		omega_app<< a[0];/*10 Dec 2009*/
		omega_sco<< a[1];

		tempArg2 = tan(lat)*tan(d[i]);
		if (fabs(tempArg2)>1){
			/* The sun never rise/set*/
			 
			omegasH[i] = pi;
		}
		else
        		omegasH[i] = acos(-tempArg2);//rad


		Hho[i] = (fabs(omegasH[i])>pi) ? 0 :
		0.001*3.6*(24/pi)  *Go*r *(Th[i]*omegasH[i] + Uh[i]*sin(omegasH[i]));
		
		// Irradiazione diretta reale sulla superficie Inclinata (tiene conto degli ostacoli dovuti alla superficie) in MJ
		Hb[i]=  ((fabs(omega_sco[i])>pi) || (fabs(omega_app[i])>pi)) ? 0 :
		3.6*(24/(2*pi))*r* 0.001 * Go *( T[i]*(omega_sco[i] - omega_app[i]) + U[i]*(sin(omega_sco[i]) - sin(omega_app[i])) - V[i]*(cos(omega_sco[i])-cos(omega_app[i])) );
		
		// Irradiazione diretta sul piano orizzontale senza ostacoli in MJ
		Hbh[i] =  (fabs(omegasH[i])>pi) ? 0 :
		  3.6*(24/(2*pi))*0.001*2*r*Go*(Th[i]*omegasH[i]+Uh[i]*sin(omegasH[i]));
		Hbh[i] = Hbh[i]<0 ? 0 : Hb[i];	/* The sun never rise */

			if (localIncl<0.000000000002) {  Hb[i]=Hbh[i];}

		
		Rb[i]	    = (Hbh[i]<0.000000002) ? 0 : Hb[i]/Hbh[i];
		Rb[i] = Rb[i]< 0 ? 0 : Rb[i];
		RbBiAx[i] = (Hbh[i]<0.000000000002)? 0 : ((3.6*24/pi) * Go*0.001* r * omegasH[i])/ Hbh[i];
		if ((fabs(omega_app[i])>pi) || (fabs(omega_sco[i])>pi))
			meanDayLen.append(24);
                else
			meanDayLen.append( 12*(2*omegasH[i])/pi); /* omegas in rad */

                   #ifdef DEBUG
                qDebug()<<"Optimum (mode=1,tilt local), (tilt,mese)"<<localIncl*180/pi<<i<<"Hb="<<Hb[i]<<"Hho="<<Hho[i]<<"Hbh="<<Hbh[i]<<Rb[i]<<meanDayLen[i]<<omegas[i]<<omegasH[i]<<omega_app[i]<<omega_sco[i];
                   #endif
		x = acos((Th[i]*(omega_sco_-omega_app_)+Uh[i]*(sin(omega_sco_)-sin(omega_app_)))*(1/(2*pi)));
		varTilt<<QPointF(i,x);
	  	#ifdef DEBUG
		qDebug()<<"OO VarTilt ="<<varTilt;
	 	#endif
		
	}
			graphPresent = false;

	if (mode==0) {

		/* Here we do not modify class variable */
		//angolo d(i)el tramonto astronomico
		 tempArg = tan(lat-localIncl)*tan(d[i]);
		if (fabs(tempArg)>1)
			/* The sun never rise/set*/
			
			omegas_ = pi;
		else

        		omegas_ = acos(-tan(lat-localIncl)*tan(d[i]));//rad

		tempArg2 = tan(lat)*tan(d[i]);
		if (fabs(tempArg2)>1){
			/* The sun never rise/set*/
			
			omegasH_ = pi;
		}
		else
        		omegasH_ = acos(-tan(lat)*tan(d[i]));//rad	

		
		tiltedRiseSet(localIncl,d[i],azi,lat,omegas_,a);
		omega_app_  = a[0];
		omega_sco_ = a[1];

 		Hbh_[i] = (omegasH_>pi) ? 0 :
		3.6*(24/(2*pi))*0.001*2*r*Go*(Th[i]*omegasH_+Uh[i]*sin(omegasH_));
		
		Hb_[i]=  ((omega_sco_>pi) || (omega_app_)>pi) ? 0 :
		3.6*(24/(2*pi))*r* 0.001 * Go *( T[i]*(omega_sco_ - omega_app_) + U[i]*(sin(omega_sco_) - sin(omega_app_)) - V[i]*(cos(omega_sco_)-cos(omega_app_)) );
		
		if (localIncl<0.000000000002) {  Hb[i]=Hbh[i];}

		Hbh_[i] = Hbh_[i]<0 ? 0 : Hb_[i];/*The sun never rise*/
// 		if (Hbh_[i]<0.0000000000002) {
// 				qDebug()<<"OO SOMETHING STRANGE"<<omegasH_<<Hbh_[i]<<d[i]<<lat*180/pi<<Uh[i]<<Th[i]<<i;
// 				}
		if (Hbh_[i]<0.00000000000002)
			Rb_[i] = 0; /*The sun never rise */
		else
			Rb_[i] = Hb_[i]/Hbh_[i];
		
		Rb_[i] = Rb_[i]<0 ? 0 : Rb_[i];
          		 #ifdef DEBUG
		qDebug()<<"Optimum (mode=0,tilt local), (tilt,mese)"<<Rb_[i]<<localIncl*180/pi<<i<<"Hb="<<Hb_[i]<<"Hho="<<"Hbh="<<Hbh_[i]<<omegas_<<omegas_<<omega_app_<<omegasH_<<tempArg2;
         	 	#endif	
	}
	
	 
	 
 	
  }
}
void OptimumPlot::tiltedRiseSet(double tilt,double decl,double azimuth,double latitude,double os ,double *out)
{	
	/* altra via per calcolare il tramonto e l'alba vera E/ Anderson*/

	double A,B,app,sco;
	if (tilt>0 & azimuth >0)
	{
		A = cos(latitude)/(sin(-azimuth)*tan(tilt)) + sin(latitude)/tan(-azimuth);
		B = tan(decl)*(cos(latitude)/tan(-azimuth) - sin(lat)/(sin(-azimuth)*tan(tilt)));
		if (azimuth>0)
		{
		/* West  of South*/
			app = -acos((A*B + sqrt((pow(A,2) - pow(B,2) +1)))/(pow(A,2)+1));
			sco =acos((A*B - sqrt((pow(A,2) - pow(B,2) +1)))/(pow(A,2)+1));
		}
		else
		{
		/* East of South */
			 app  = -acos((A*B - sqrt((pow(A,2) - pow(B,2) +1)))/(pow(A,2)+1));
			 sco  =acos((A*B + sqrt((pow(A,2) - pow(B,2) +1)))/(pow(A,2)+1));
		}
	/* Compare with omegas */
	if (-os  >  app )   app   = -os ;	
	if (os  < sco)  sco  = os ;
// 	qDebug()<<"OptimimPlot TiltedSurface if";
	}
	else
	{
// 		qDebug()<<"OptimimPlot TiltedSurface else";
			app = -os;
			sco = os;
	}
	
	out[0] = app;
	out[1] = sco;
	
}
void OptimumPlot::compute()
{
        int k=0;
        double incl_;
        for (int i=startIncl;i<=endIncl;i+=stepIncl) {
                incl_ = i*pi/180;
                compute(0,incl_);
                /*Copy values */
                for(int j=0;j<12;j++)
			{
                    	varHb_[k][j] = Hb_[j];
// 			qDebug()<<"OptimumPlot compute varHb_"<<varHb_[k][j]<<k<<i;
			}
                k++;
            }

        varInclGenerated = true;
	
}
QPolygonF OptimumPlot::getOmegasDaily()
{
	return dailyOmegas;
}
QPolygonF OptimumPlot::getOmegasHDaily()
{
	return dailyOmegasH;
}
 
double* OptimumPlot::getOmegasH()
{
	double* start;
	start = omegasH;
	return start;
}
/*
double* OptimumPlot::getOmegaApp()
{
	// Output in degree
	double* start;
	start = omega_app;
// 	qDebug()<<"OmptimumPlot: sparo omegaApp[0]"<<start[0]*180/pi;
	return start;
}*/
QVector<double> OptimumPlot::getOmegaApp()
{
	// Output in degree
	
        //qDebug()<<"OmptimumPlot: sparo omegaApp[0]"<<start[0]*180/pi;
	return omega_app;
}
// double* OptimumPlot::getOmegaSco()
// {
// 	// Output in degree
// 	double* start;
// 	start = omega_sco;
// 	return start;
// }
QVector<double> OptimumPlot::getOmegaSco()
{
	// Output in degree


	return omega_sco;
}
void OptimumPlot::drawContents(int mode)
{
	 
	double m[12] = {1,2,3,4,5,6,7,8,9,10,11,12};

        //int k=0;
	int limit = ceil((endIncl-startIncl)/stepIncl)+1 ;
        for(int i=0;i<limit;i++){
		 

		if (mode==1){

                plotOptiMarker[i]->setValue(6,varHb_[i][limit ]);
                QwtText label(QString::number((i*stepIncl+startIncl))+" gradi");
		plotOptiMarker[i]->setLabel(label);
		
		
// 		plotOpti[i]= new QwtPlotCurve();
                plotOpti[i]->setData(m,varHb_[i],12);
		plotOpti[i]->setCurveAttribute(QwtPlotCurve::Fitted,true);
		}
		else
		{
		plotOpti[i]->setRawData(0,0,0);
		plotOptiMarker[i]->setLabel(QwtText(""));
		resetTitle();
		}
		
}
      if (mode == 1){
	#if QT_VERSION >= 0x040000
   	plotOpti[limit ]->setRenderHint(QwtPlotItem::RenderAntialiased);
	#endif
	plotOpti[limit ]->setPen(QPen(Qt::blue));
	plotOpti[limit  ]->setCurveAttribute(QwtPlotCurve::Fitted,true);
	plotOpti[limit ]->setData(m,Hbh,12);
	
	}
	else{
	plotOpti[limit]->setRawData(0,0,0);
	resetTitle();
	resetTitle();
	}
	

	replot();
}

void OptimumPlot::setIncl(double i)
{
	incl = i;
}
void OptimumPlot::setAzi(double i)
{
	/* Azimuth is positive westward */
	azi = i;
}

void OptimumPlot::setLat(double i)
{
	lat = i;
// 	qDebug()<<"Ho settato lat to ="<<lat;
}
void OptimumPlot::alignScales()
{
    // The code below shows how to align the scales to
    // the canvas frame, but is also a good example demonstrating
    // why the spreaded API needs polishing.

    canvas()->setFrameStyle(QFrame::Box | QFrame::Plain );
    canvas()->setLineWidth(1);

    for ( int i = 0; i < QwtPlot::axisCnt; i++ )
    {
        QwtScaleWidget *scaleWidget = (QwtScaleWidget *)axisWidget(i);
        if ( scaleWidget )
            scaleWidget->setMargin(0);

        QwtScaleDraw *scaleDraw = (QwtScaleDraw *)axisScaleDraw(i);
        if ( scaleDraw )
            scaleDraw->enableComponent(QwtAbstractScaleDraw::Backbone, false);
    }
}
void OptimumPlot::optimize()
{
	#ifdef DEBUG_S
	qDebug()<<"optimize tilt...lat="<<lat;
	#endif
	double i=10;
//	int k=0;
	double prec,actual;
	bool condition = true;
        double localIncl = i*pi/180;
	bestInclHb = i;
        compute(0,localIncl);
 	prec = MyMath::cumSumMonthly(Hb,12) ;
	i+=0.5;
  	while (condition) {
		
                localIncl = i*pi/180;
                compute(0,localIncl);
		actual = MyMath::cumSumMonthly(Hb,12) ;
//  	qDebug()<<actual<<i;
		if (actual < prec){
		// We found the max
		condition = false;
//   		qDebug()<<i;
	
		bestInclHb = i;
		maxIrr = prec;
		
		} else {
		        prec = actual;
			i+=0.5;
		
		}
}
	
// 	tempSum = cumSum(Hb[k],365);
}
double OptimumPlot::getMaxIrr()
{
	return maxIrr;
}

double OptimumPlot::getBestInclHb()
{
// 	qDebug()<<"Optimum,"<<lat*180.0/pi<<bestInclHb;
	return bestInclHb;
}

QPolygonF OptimumPlot::getRbBiAxDaily()
{
	return dailyRbBiAx;
}
QPolygonF OptimumPlot::getRbDaily()
{
	return dailyRb;
}
QPolygonF OptimumPlot::getHhoDaily()
{
	return dailyHho;
}

double *OptimumPlot::getRbBiAx()
{
	double *start = RbBiAx;
	return start;
}
double *OptimumPlot::getRb()
{
// for (int i=0;i<365; i++) {
// 	 a[i] = Hb[i]/Hbh[i];
// }
	double *start = Rb;
	return start;
}
double *OptimumPlot::getRelativeRb()
{

        double *start = Rb_;
	
        return start;
}
double *OptimumPlot::getHb( )
{
	double *start = Hb;
	return start;
}
double *OptimumPlot::getHbh( )
{
	double *start = Hbh;
	return start;
}
double *OptimumPlot::getHho( )
{
	double *start = Hho;
	return start;
}
QVector<double> OptimumPlot::getTotalDayLen()
{
	return totalDayLen;
}
QVector<double> OptimumPlot::getMeanDayLen()
{

        return meanDayLen;
}
void OptimumPlot::getAll(double Hb_[12]  ,double Hho_[12], double Hbh_[12], double Rb_[12])
{
  	for (int i=0;i<12; i++) {
 	Hb_  = Hb;
 	Hho_ = Hho;
 	Hbh_ = Hbh;
 	
  	}
}

 void OptimumPlot::createActions()
{
	a_print =  new QAction(tr("&Stampa"),this);
	a_export = new QAction(tr("&Esporta"),this);
	a_proprieta = new QAction(tr("Impostazioni"),this);

	connect(a_print,SIGNAL(triggered()),this,SLOT(printOut()));
	connect(a_export,SIGNAL(triggered()),this,SLOT(exportSVG()));
	connect(a_proprieta,SIGNAL(triggered()),this,SLOT(settings()));
}
void OptimumPlot::settings()
{
#ifdef DEBUG
	qDebug()<<"I am here";	
	#endif
  
	set->setVisible(true);
	set->raise();
}
void OptimumPlot::popUpMenu(const QPoint &pos)
{ 
	
	 
 	QMenu menu;
	menu.addAction(a_print);
	menu.addAction(a_export);
	menu.addAction(a_proprieta);
	#ifdef Q_X11
	menu.popup(pos);
	#endif
	menu.exec(QCursor::pos());
}

void OptimumPlot::printOut()
{
	QString path = QDir::currentPath()+tr("/radiazione.pdf");
	 QPrinter printer(QPrinter::HighResolution);
	#ifdef Q_WS_X11
	 printer.setOutputFileName(path);
	#endif
	 printer.setCreator("Solar Calc");
         printer.setOrientation(QPrinter::Landscape);
	 printer.setOrientation(QPrinter::Portrait);
	 QPrintDialog dialog(&printer);
    if ( dialog.exec() )
    {	
	QwtPlotPrintFilter filter;
//         if ( printer.colorMode() == QPrinter::GrayScale )
        {
            int options = QwtPlotPrintFilter::PrintAll;
            options &= ~QwtPlotPrintFilter::PrintBackground;
            options |= QwtPlotPrintFilter::PrintFrameWithScales;
            filter.setOptions(options);
        }

	print(printer, filter);



   }
}
void OptimumPlot::moved(const QPoint &pos)
{
	 
	picker->rubberBand();
}
void OptimumPlot::selected(const QwtPolygon &)
{
	 
}
void OptimumPlot::exportPDF()
{
	 QString fileName;
	 fileName = QFileDialog::getSaveFileName(this, tr("Nome file da esportare"),  QDir::homePath(),"Acrobat ( *pdf)");

	if ( !fileName.isEmpty() ) {
	 QPrinter printer(QPrinter::HighResolution);
	 printer.setOutputFormat(QPrinter::PdfFormat);
	 printer.setOutputFileName(fileName);
	 printer.setCreator("Solar Calc");
         printer.setOrientation(QPrinter::Landscape);
	 
	 
     
       
	QwtPlotPrintFilter filter;
//          if ( printer.colorMode() == QPrinter::GrayScale )
         
            int options = QwtPlotPrintFilter::PrintAll;
            options &= ~QwtPlotPrintFilter::PrintBackground;
            options |= QwtPlotPrintFilter::PrintFrameWithScales;
            filter.setOptions(options);
        

	print(printer,filter);



      }
}
 
void OptimumPlot::exportSVG()
{
	QString fileName;
 

    fileName = QFileDialog::getSaveFileName(this, tr("Nome file da esportare"), QString(),        "SVG files (*.svg)");

    if ( !fileName.isEmpty() )
    {
	QwtPlotPrintFilter filter;
//         if ( printer.colorMode() == QPrinter::GrayScale )
        {
            int options = QwtPlotPrintFilter::PrintAll;
            options &= ~QwtPlotPrintFilter::PrintBackground;
            options |= QwtPlotPrintFilter::PrintFrameWithScales;
            filter.setOptions(options);
        }
        QSvgGenerator generator;
        generator.setFileName(fileName);
        generator.setSize(QSize(1024, 800));

        print(generator,filter);
    }


}
void OptimumPlot::setLocName(const QString &s)
{	
	name = s;
	QString title = tr("Radiazione solare ideale diretta, ") + s;
        setTitle(title);
	
}
bool OptimumPlot::isEmpty()
{
	return graphPresent;
}

int OptimumPlot::getUnit()
{
	return currentUnit;
}
QPolygonF OptimumPlot::getVarTilt()
{
	return varTilt;
}
QPolygonF OptimumPlot::getDailyVarTilt()
{
return dailyVarTilt; 
}
QPolygonF OptimumPlot::getDailyOmegaApp()
{
	return dailyOmegaApp;
}

QPolygonF OptimumPlot::getDailyOmegaSco()
{
	return dailyOmegaSco;
}
  
 
void OptimumPlot::setYear(int i)
{
	year = i;
}
void OptimumPlot::resetTitle()
{
	QString str;
	QwtText tlabel(tr("Radiazione solare ideale diretta")+ " ");
	tlabel.setFont(QFont("Times",13,QFont::Normal));
	setTitle(tlabel);
	set->setTitle(tr("Radiazione solare ideale diretta")+ " ");
}