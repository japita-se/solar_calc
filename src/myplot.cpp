  
 // #define DEBUG
 #define DEBUGINT

#include <myplot.h>
#include "mymath.h"
#include <cmath>
#include "linearinter.h"
 #include <qwt_plot_layout.h>
#include "settings.h"
#include "gridset.h"
#include <qwt_plot_panner.h>
#include <qwt_picker.h>
#include <qwt_plot_picker.h>
#include <qwt_curve_fitter.h>
#include <qwt_spline.h>
#include <qwt_plot_canvas.h>
#include <qwt_scale_draw.h>
#include <qwt_scale_widget.h>
#include <qwt_painter.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
 
#include <qwt_legend.h>
#include <qwt_legend_item.h>
// #include <qwt_data.h>
//#include <qwt_text.h>

 //#include "spa.h"

//  extern "C" {
// #include "spa.h"
//  }
#include <QtGui>
#include <QSvgGenerator>
#include <QPointF>
 
#define pi        3.1415926535897932384626433832795028841971
using namespace std;
void MyPlot::replotGraph()
{
	replot();
}
MyPlot::MyPlot( QWidget* par ) : QwtPlot(par )  
	
{
        // SOME INITIALIZATION
        temperatures.fill(0,12);
        currentSide = 0;
        addInclAzi.resize(0);
	image = new QImage(1024,800,QImage::Format_RGB32);
        p         = par;
	graphPresent = false;
        delta     = 1;
        offset    = -180;
        mode      =  default_;
        ombreMode =  sampleAndHoldMode;
        initializeGrid();
        recentDir = QDir::homePath();
	recentExportPath = QDir::homePath();
	spa.azm_rotation = 0;
	spa.slope = 0;

// 	 setHSteps();
        //legend
//        legend = new QwtLegend(this);
//        //legend->setDisplayPolicy(QwtLegend::NoIdentifier,QwtLegendItem::ShowLine);
//        insertLegend(legend,QwtPlot::LeftLegend);

	this->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this,SIGNAL(customContextMenuRequested(const QPoint &  )),this,SLOT(popUpMenu(const QPoint &)));

	

	 QwtPainter::setDeviceClipping(false);
       
// 	#ifdef Q_WS_X11
//     /*
//        Qt::WA_PaintOnScreen is only supported for X11, but leads
//        to substantial bugs with Qt 4.2.x/Windows
//      */
//          canvas()->setAttribute(Qt::WA_PaintOnScreen, true);
// 	#endif
	 
		
	
		
	givenDays[0] = 17;
	givenDays[1] = 16;
	givenDays[2] = 16;
	givenDays[3] = 15;
	givenDays[4] = 15;
	givenDays[5] = 21;
	givenDays[6] = 17;
	givenDays[7] = 15;
	givenDays[8] = 15;
	givenDays[9] = 15;
	givenDays[10] = 14;
	givenDays[11] = 10;
	
// 	{ 17, 16, 16, 15, 15, 21, 17, 15, 15, 15, 14, 11};
  
  	 		 monthLabels[0] = tr("Gen 17");
			 monthLabels[1] =tr("Feb 16");
			 monthLabels[2] =tr("Mar 16");
			 monthLabels[3] =tr("Apr 15");
			 monthLabels[4] =tr("Mag 15");
			 monthLabels[5] =tr("Giu 21");
			 monthLabels[6] =tr("Lug 17");
			 monthLabels[7] =tr("Ago 15");
			 monthLabels[8] =tr("Sett 15");
			 monthLabels[9] =tr("Ott 15");
			 monthLabels[10] =tr("Nov 14");
			 monthLabels[11] =tr("Dec 10");
//legendString="<p>";
//                          for(int i=0;i<12;i++)
//                              legendString += "<br/>" + QString::number(i+1) + " " +monthLabels[i] + "<br/>";
//                          legendString+="</p>";
//
//                            QwtText legendLabel(legendString);

 	
// Plot initialization
 
    gridSettings = new GridSet();
    gridSettings->setAsseX(Qt::Unchecked);
    gridSettings->setAsseY(Qt::Unchecked);
    connect(gridSettings,SIGNAL(accepted()),SLOT(updateGrid()));
	
//  grid
    grid = new QwtPlotGrid;
    grid->enableX(false);
    grid->enableXMin(false);
    grid->enableY(false);
    grid->enableYMin(false);
    grid->setMajPen(QPen(Qt::gray, 0, Qt::DotLine));
    grid->setMinPen(QPen(Qt::gray, 0 , Qt::DotLine));
    grid->attach(this);

	label = new QLabel(this);
	label->setGeometry(this->geometry().x()+10,this->geometry().y(),label->width()+10,label->height());

   picker = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft,QwtPicker::PointSelection , QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOff,canvas());
   picker->setRubberBandPen(QColor(Qt::black));
   picker->setRubberBand(QwtPicker::CrossRubberBand);
   picker->setEnabled(true);
  
   picker->setTrackerPen(QColor(Qt::black));

	connect(picker, SIGNAL(moved(const QwtDoublePoint &)),SLOT(moved(const QwtDoublePoint &)));
	connect(picker, SIGNAL(selected(const QwtDoublePoint &)),SLOT(selected(const QwtDoublePoint &)));
	
	// Set default settings
	set = new Settings();
	set->radioMJ->setEnabled(false);
	set->radiokWh->setEnabled(false);
	set->setUnit(1);//MJ/m2
	set->setTitle(tr("Diagramma solare")+ " ");
	
	set->setAxisY(tr("Elevazione"));
	set->setAxisX(tr("<---E  Azimuth(S)  O--->"));
	set->setVisible(false);
	connect(set,SIGNAL(accepted()),SLOT(updateSet()));
	
	QwtText xlabel(set->getAxisX());
        //xlabel.setFont(QFont("Times",12,QFont::Normal));
	QwtText xlabelTop("<---O  Azimuth(N) E--->");
	xlabelTop.setFont(QFont("Times",12,QFont::Normal));
	xlabelTop.setColor(Qt::red);
	QwtText ylabel(set->getAxisY());
	ylabel.setFont(QFont("Times",12,QFont::Normal));
        QwtText tlabel(set->getTitle());
        tlabel.setRenderFlags(tlabel.renderFlags() | Qt::TextWordWrap);
	tlabel.setFont(QFont("Times",14,QFont::Normal));

	setAxisTitle(QwtPlot::xBottom, xlabel);
        setAxisTitle(QwtPlot::yLeft, ylabel);
 	setAxisScale(QwtPlot::xBottom,-180*1.2,180*1.2);
	setAxisTitle(QwtPlot::xBottom, xlabel);
	setAxisScale(QwtPlot::xTop,-180*1.2,180*1.2);
   	setAxisScale(QwtPlot::yLeft,0,90);
        enableAxis(QwtPlot::yLeft,true);
	setAxisTitle(QwtPlot::xTop,xlabelTop);
	setMargin(40);
	enableAxis(QwtPlot::xTop);
// 	QString title = tr("Diagramma solare");
        setTitle(tlabel);
	setTitle(tlabel);
	setCanvasBackground(QColor(Qt::white));



	
//   	canvas()->setMouseTracking(true);
// 	canvas()->setTrackerMode(AlwaysOn);
   
  // plotLayout()->setAlignCanvasToScales(true);
  createActions();

   alignScales();
// replot();
//  Support *s =  new Support;
//   s->show();
 dailyValueDirty = true;

}  
void MyPlot::updateGrid()
{
// 	qDebug()<<"Sono in grid";
	if (gridSettings->getAsseX()==Qt::Checked) {
// 	qDebug()<<"Griglia vera";
	 	grid->enableXMin(true);
   	 	grid->enableX(true);
    	 	grid->enableXMin(true);
	} 
	else	
	{
		grid->enableXMin(false);
   	 	grid->enableX(false);
    	 	grid->enableXMin(false);
	}
	if (gridSettings->getAsseY()==Qt::Checked) {
	 	grid->enableYMin(true);
   	 	grid->enableY(true);
    	 	grid->enableYMin(true);
	}
	else	
	{
		grid->enableYMin(false);
   	 	grid->enableY(false);
    	 	grid->enableYMin(false);
	}
replot();
}
void MyPlot::updateSet()
{
	QString str;
	QwtText tlabel(set->getTitle());
	tlabel.setFont(QFont("Times",13,QFont::Normal));
	setTitle(tlabel);
	setAxisTitle(QwtPlot::yLeft,set->getAxisY());
	setAxisTitle(QwtPlot::xBottom,set->getAxisX());
   
	 
}

void MyPlot::setLong(double longi)
{
	spa.longitude = longi;
//  	qDebug()<<"MYPLOT lon"<<longi;
}

void MyPlot::setLat(double lat)
{
	QwtText xlabel(tr("<---E Azimuth(S) O--->"));
        xlabel.setFont(QFont("Times",12,QFont::Normal));
	xlabel.setColor(Qt::red);
	spa.latitude = lat;
// 	qDebug()<<"MP setLat"<<lat;
	if (tropic()==0)
	{
		if (spa.latitude<0)
		{
			
// 			set->setAxisX(tr("<---O Azimuth(N) E--->"));
			updateSet();
			//offset = 0;
			//initializeGrid();
		 
		}
	}
	else {
		setAxisTitle(QwtPlot::xTop, xlabel);
		set->setAxisX(tr("<---E Azimuth(S) O--->"));
		updateSet();
	     }
	
  	
}

void MyPlot::setAlt(double alt)
{
        spa.elevation = alt;

}

void MyPlot::setUTC(int utc)
{
	spa.timezone = utc;
}

void MyPlot::setYear(int i)
{
	spa.year = i;
}
void MyPlot::setMode(int m)
{
	if (m) meanVal = 1;
		else meanVal =0;

}
void MyPlot::setRes(int f)
{
	fast =f;
}
void MyPlot::computeDaily()
{
	int ddend,kk;
// 	int highestMonth;
		
	kk=0;
	reorder = 0;
	spa.second   = 0;
	//     spa.timezone      = -7.0;
	spa.delta_t       = 33.184;

//	spa.pressure      = 1010;
//	spa.temperature   = 10;
	//spa.slope         = 0;
        spa.azm_rotation  = -10;
//	spa.atmos_refract = 0.5667;
//	spa.function      = SPA_ALL;
	 
	
// 	 if (spa.latitude<0)
// 			highestMonth = 12;
// 		else
// 			highestMonth = 6;
 		 
        //int i;
        //bool found  ;
	

	int days=0;
        double   shiftedAzimuth,shiftedZenith, ea,az;
        //char str[20];
	
		
 		dailyOmbreFactor.resize(0);
		for (int mm=1; mm<=12;mm++) {
			spa.month=mm;
// 			qDebug()<<"computeDaily giorno"<<days<<ddend<<mm;
			ddend = MyMath::monthEnd(mm,spa.year);
// 			qDebug()<<"computeDaily giorno"<<days<<ddend<<mm;
			for (int dd=0;dd<ddend;dd++) {
				spa.day=dd;
				sunpos.resize(0); // it's another day!
				if (checkQuadrant(spa)) {
				/* We are in the I and II quadrant mostly*/
					reorder = 1;
					
					/*shiftedAzimuth = (spa.azimuth>180) ? spa.azimuth-360 : spa.azimuth*/;
							
				}
				else
				{
					/* We are in the III and IV quadrant mostly*/
					reorder = 0;
					
// 					shiftedAzimuth = spa.azimuth180;
				}	
				for (int i=0;i<numHours;i++) {
					spa.hour=(int)(floor(hl[i]));
					
					spa.minute = (int)(60*(hl[i]-floor(hl[i])));
					 int result = spa_calculate(&spa);
                                    

 						if (reorder==0)
							shiftedAzimuth = spa.azimuth180;
						if (reorder==1)
							shiftedAzimuth = (spa.azimuth>180) ? spa.azimuth-360 : spa.azimuth;

					 
 					 

					shiftedZenith = 90-spa.zenith;

					ea = shiftedZenith;

					az = shiftedAzimuth;
					if (reorder==1)

						sunpos.prepend(QPointF(az,ea));
					else
						sunpos.append(QPointF(az,ea));
				}
			

			if (shadowCombined.size()>0) {
                               
				/* Attenzione ai gradi/radianti*/
				/* IN this mode it is supposed that omegaApp and omegaSco take into account the tilt of the surface*/
			
			dailyOmbreFactor<< QPointF(days, eArea(sunpos ,shadowCombined,dailyOmegaApp.at(days).y(),dailyOmegaSco.at(days).y(),ombreMode));
			#ifdef DEBUG
                        //qDebug()<<"MYPLOT computeDaily app sco"<<dailyOmegaApp.at(days).y()<<dailyOmegaSco.at(days).y();
			#endif
				}
		 	else
			{
			dailyOmbreFactor << QPointF(days,1);
			}
		days++;
		}
		}
dailyValueDirty = false;
}
void MyPlot::compute() 
/* This funnction compute the solar diagram useful for plot. Only mean day of every month are considered */
{
        QVector<double> ssh,ssh2;
        double sunInc2;
	dailyValueDirty = true;
// 	int highestMonth;
        //myspa_data tempSpa;
	int ddend,kk,azimuthOffset;
	kk=0;
	if (tropic()!=0)
		azimuthOffset = 15;
	else
		azimuthOffset = 4;

	spa.second   = 0;
	//     spa.timezone      = -7.0;
	spa.delta_t       = 33.184;

	spa.pressure      = 1010;

	//spa.slope         = 0;
// 	spa.azm_rotation  = -10;
	spa.atmos_refract = 0.5667;
	spa.function      = SPA_ALL;
	 
	spa.year = 2005;
	// TO OPTIMIZE
 		 

	 
	
	spaMean s;
	int days=0;
        double hL,v,shiftedAzimuth,shiftedZenith;

		
	reorder = 0;
// 	if (spa.latitude<0)
// 		highestMonth = 12;
// 	else
// 		highestMonth = 6;
	hourPos.resize(0);
	sunIncWest.resize(0);
	sunIncEast.resize(0);
        sunIncWest2.resize(0);
        sunIncEast2.resize(0);

	thisMonthColor.resize(0);
	int hm = highestMonth(spa.latitude);
        //int lm = lowestMonth(spa.latitude);
// 	qDebug()<<"MP HIGHEST MONTH"<<hm<<lm; 
	for (int mm=1; mm<=12;mm++) 
	{
                        spa.temperature   = temperatures.at(mm-1);
			sunP[mm-1].resize(0);
// 			sunPathToPlot[mm-1].resize(0);
			ddend = MyMath::monthEnd(mm,spa.year);
			
			 
				
			intervalDays[2] = givenDays[mm-1];
			intervalDays[5] = ddend;
			
			for (int dd=0;dd<numDays;dd++) {

			 	spa.day=intervalDays[dd];
				spa.month=mm;
				 
				v=0;
			
				
				if (checkQuadrant(spa)) {
				/* We are in the I and II quadrant mostly*/
					reorder = 1;
					
					/*shiftedAzimuth = (spa.azimuth>180) ? spa.azimuth-360 : spa.azimuth*/;
							
				}
				else
				{
					/* We are in the III and IV quadrant mostly*/
					reorder = 0;
					
// 					shiftedAzimuth = spa.azimuth180;
				}	
				if (givenDays[mm-1] == intervalDays[dd]) {
					if (reorder==1) 
						thisMonthColor<<QPointF(mm,1);
					if (reorder==0)
						thisMonthColor<<QPointF(mm,0);
				}

				for (int i=0;i<numHours;i++)
				{
	
					spa.hour=(int)(floor(hl[i]));
					spa.minute = (int)(60*(hl[i]-floor(hl[i])));
					
					
                                        int result = spa_calculate(&spa);
                                        
						if (!meanVal) {
 	
						
 						if (reorder==0)
							shiftedAzimuth = spa.azimuth180;
						if (reorder==1)
							shiftedAzimuth = (spa.azimuth-180>0.0000002) ? spa.azimuth-360 : spa.azimuth;


 
 

							shiftedZenith = 90-spa.zenith;

							sunEA[days][i] = shiftedZenith;
							sunAZ[days][i] = shiftedAzimuth;

							sunInc[days][i] = incidence(spa.zenith, shiftedAzimuth,spa.slope,-spa.azm_rotation);
                                                        if (isTwoSide())
                                                            sunInc2 =  incidence(spa.zenith, shiftedAzimuth,addInclAzi.at(1),addInclAzi.at(0));
							#ifdef DEBUG
							qDebug()<<"MyPlot, spa result"<<result<<mm<<spa.day<<spa.hour;
							#endif		
		
							
						}
						else
						{
						// Compute also the mean values
							s = msun(spa.longitude,spa.latitude,spa.hour,mm,intervalDays[dd],spa.timezone);
							sunEA[days][i] = s.SEA;
							sunAZ[days][i]=  s.AZ;
						
						}
					
 
   					timeX[i][days] = sunAZ[days][i];
   					timeY[i][days] = sunEA[days][i];
				 
					if ((givenDays[mm-1] == intervalDays[dd]))
					/* We plot only some days */
					{
				
						 
						dataToPlotX[mm-1][i] = sunAZ[days][i];
						dataToPlotY[mm-1][i] = sunEA[days][i];

                                                 ssh = computeSelfShadow(days,sunInc[days][i],sunEA[days][i],sunAZ[days][i]);
                                                addSelfShadow(ssh.at(0),ssh.at(1));

                                                if (isTwoSide()){
                                                     ssh2 = computeSelfShadow(days,sunInc2,sunEA[days][i],sunAZ[days][i]);
                                                      addSelfShadow2(ssh2.at(0),ssh2.at(1));
                                                  }
						/* If the latitude is negative invert the vector */
						if (reorder==1) {
// 							qDebug()<<"MYPLOT INVERT VECTOR Prepend";
							sunP[mm-1].prepend(QPointF(sunAZ[days][i],sunEA[days][i]));
// 							sunPathToPlot[mm-1].prepend(QPointF(sunAZ[days][i],sunEA[days][i]));
							 
						}
						else
						{
							
							sunP[mm-1].append(QPointF(sunAZ[days][i],sunEA[days][i]));
// 							sunPathToPlot[mm-1].append(QPointF(sunAZ[days][i],sunEA[days][i]));
							 
							
						}
						//dSolar[mm-1]->setData(sunP[mm-1]);
						// Prepare data for plotting the hours
   						#ifdef DEBUG
						qDebug()<<result<<"MyPlot mm sunAZ["<<mm<<days<<"]["<<i<<"]="<<sunAZ[days][i]<<sunEA[days][i]<<sunInc[days][i];
   						#endif
						
	// 					qDebug()<<"HIGHEST MONTH =="<<hm<<lm;		
						QPointF ad;
						if (mm==hm) {
// 								ad = (hl[i]<12) ?	QPointF(sunAZ[days][i]-10,sunEA[days][i]+5):
// 								QPointF(sunAZ[days][i]+10,sunEA[days][i]+5);
								ad = QPointF(sunAZ[days][i]+MyMath::sign(sunAZ[days][i])*azimuthOffset,sunEA[days][i]+azimuthOffset);
								hourPos<<ad;
						
						}
						 	
					
						if (mm<=hm) 
							hL = 12;
						else
							hL = 13;
					
// 						qDebug()<<h[i]<<h[i]-hL<<(h[i]==12)<<(hL==(int)h[i]);
						if ((fabs(hl[i]-hL))<0.0000001)
						{
												
 						 	monthPosX[mm-1] = sunAZ[days][i];
							monthPosY[mm-1] = sunEA[days][i];
 
							 
						}
					}
				
 	
				}

				/* Calcola alba e tramonto , solo per i giorni medi del mese*/
				if ((givenDays[mm-1] == intervalDays[dd])){
					sunSet[mm-1]  = spa.ssha;
					sunRise[mm-1] = spa.srha;
// 	 				 qDebug()<<"alba e tramonto"<<mm<<spa.srha<<spa.ssha;
					//computeShadow();
// 				days++;
					
				}
			
  			days++;
			}
	
		
	}
	 
	 	
 	qStableSort(sunIncEast.begin(),sunIncEast.end(),lessThanPoint);
	qStableSort(sunIncWest.begin(),sunIncWest.end(),lessThanPoint);
        qStableSort(sunIncEast2.begin(),sunIncEast2.end(),lessThanPoint);
        qStableSort(sunIncWest2.begin(),sunIncWest2.end(),lessThanPoint);

}

QVector<double> MyPlot::computeSelfShadow(int days,double incAngle, double elev, double azimuth)
{
        /* This function can be called only after compute */
	/* incAngle is the incidence Angle */
    QVector<double> o;

// 	int days=0;
	bool found1,found2;
	double v1,v2,x1,x2;
 
			v1 = 0;
			v2 = 0;
			found1 = false;
			found2 = false;

 
				if (incAngle>90 && elev>0){
 
					switch (azimuth>0) {
						case true:
						/* We are at West*/
						if (elev>v1){
						v1 = elev;
						x1 = azimuth;
						found1 = true;
						}
						break;

						case false:
						/* We are at East */
						if (elev>v2){
						v2 = elev;
						x2 = azimuth;
						found2 = true;
						break;	
						}
					}
// 					qDebug()<<"Found (mese,giorno,ora)"<<mm<<days<<i<<x<<v;
				} else
				{
				
				}
					
				
#ifdef DEBUG
qDebug()<<"Self shadow"<<sunIncEast;
qDebug()<<"Self shadow"<<sunIncWest;
#endif

			if (found1) 
                                return o<<x1<<v1;
			if (found2)
                                return o<<x2<<v2 ;
                        return QVector<double>();


}
QVector<double> MyPlot::computeShadow(const QVector<double> &oApp, const QVector<double> &oSco)
{
	QVector<double> ombre;
	for(int mm=1;mm<=12;mm++) {
		if (shadowCombined.size()>0) {
                                
				if (mode == custom_)
				/* ALL  IN radiants*/
				/* IN this mode it is supposed that omegaApp and omegaSco take into account the tilt of the surface*/
// 				ombreFactor[mm-1] = eArea(sunP[mm-1],shadowCombined,omegaApp[mm-1],omegaSco[mm-1],ombreMode);
				ombre<< eArea(sunP[mm-1],shadowCombined,oApp[mm-1],oSco[mm-1],ombreMode);
				else
				{
// 				ombreFactor[mm-1] = eArea(sunP[mm-1],shadowCombined,sunRise[mm-1],sunSet[mm-1],ombreMode);
				/* TO MODIFY FOR MULTIPLE ARRAYS*/
				ombre << eArea(sunP[mm-1],shadowCombined,sunRise[mm-1],sunSet[mm-1],ombreMode);

				}
                        #ifdef DEBUG
                                qDebug()<<"Ho chiamato earea in QVector<double> computeShadow ............mode mese"<<mm<<mode<<oApp[mm-1]<<oSco[mm-1]<<ombre[mm-1];
                                #endif
			}
		 
		else
		{
// 			ombreFactor[mm-1] =1;
			ombre<< 1;
		}
		
		}
	return ombre;
  	#ifdef DEBUG
	qDebug()<<"MyPlot: ho chiamato QVector<double> computeShadow()"<<shadowCombined<<spa.latitude;
  	#endif
 }

 
void MyPlot::computeShadow()
{
// 	if (isSetOmegaApp && isSetmegaSco) {
	ombreFactor.resize(0);
	for(int mm=1;mm<=12;mm++) {
		if (shadowCombined.size()>0) {
                                
				if (mode == custom_){
				/* Attenzione ai gradi/radianti*/
				/* IN this mode it is supposed that omegaApp and omegaSco take into account the tilt of the surface*/

				ombreFactor<< eArea(sunP[mm-1],shadowCombined,omegaApp[mm-1],omegaSco[mm-1],ombreMode);

				}
				else
				{
// 				ombreFactor[mm-1] = eArea(sunP[mm-1],shadowCombined,sunRise[mm-1],sunSet[mm-1],ombreMode);
				ombreFactor << eArea(sunP[mm-1],shadowCombined,sunRise[mm-1],sunSet[mm-1],ombreMode);

				}
                        #ifdef DEBUG
                                qDebug()<<"Ho chiamato earea in computeShadow()............mode mese"<<mm<<mode<<omegaApp[mm-1]<<omegaSco[mm-1]<<ombreFactor[mm-1] ;
                                     #endif
			}
		 
		else
		{
// 			ombreFactor[mm-1] =1;
			ombreFactor<< 1;
                            // qDebug()<<"Non Ho chiamato earea computeShadow()............mode mese"<<mm<<mode<<omegaApp[mm-1]<<omegaSco[mm-1]<<ombreFactor[mm-1];
		}
		
		}
    	#ifdef DEBUG
	qDebug()<<"MyPlot: ho chiamato computeShadow()"<<shadowCombined<<spa.latitude;
   	#endif
 	}

 spaMean MyPlot::msun(float lon, float lati, int h, int m, int d,int UTC)
{
	int m_[12] = {0, 31, 60, 91, 121, 152,182,213,243,274,304,335};
	float g,t,D,EOT,LAT,TC,sinSEA,SEAg,SZA,cosAZ,AZ,sinAZ,SEA,AZg,SZAg;

// 	float pi=3.14;
	float longitude = lon * pi/180;
	float latitude  = lati * pi/180;
        int day = d + m_[m-1];
	 
	g  = (2*pi/365.25) * (day + h /24); 
	// solar day
	
	
	D = 0.4 * sin(g-1.4+0.0355*sin(g-0.0489)); 
	//mean declination
	
	EOT = -0.128*sin(g-2.8*pi/180) - 0.165*sin(2*g + 19.70);
	LAT = h  + (longitude-UTC)/15 + EOT;
	t = LAT;

	
	TC = (t-12) * 15 *pi/180;
	
	
	sinSEA = sin(latitude)*sin(D)+cos(latitude)*cos(D)*cos(TC);
	
	SEA  = asin(sinSEA);
	SZA  = pi/2 - SEA;
	 
	cosAZ = (sin(latitude) * sinSEA - sin(D)) / (cos(latitude)*cos(SEA));
	sinAZ = cos(D)*sin(TC)/cos(SEA);
	if (sinAZ > 0)
		
		AZ = acos(cosAZ);
	else
		AZ = -acos(cosAZ);
	 
	SEAg = SEA *180/pi;
	SZAg = SZA *180/pi;
	AZg  = AZ * 180/pi;
	spaMean out;
	out.SEA = SEAg;
	out.AZ = AZg;
	return out;
}
// void MyPlot::paintEvent(QPaintEvent *event)
// {
//     QFrame::paintEvent(event);
// 
//     QPainter painter(this);
//     painter.setClipRect(contentsRect());
//     drawContents(&painter);
// }

//
//  Set a plain canvas frame and align the scales to it
//
void MyPlot::alignScales()
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

double MyPlot::eArea(QPolygonF &dati,QPolygonF &ombre,double a, double b,int m)
{
    int n =20;
    double h,area,areaOmbre,solarPath,ombrePath;
    double estremoSinistroOmbra,estremoSinistroSolar,estremoDestroSolar,estremoDestroOmbra;
    int b1,b2;
    QPolygonF asseX;
    
    QwtSplineCurveFitter sp,spOmbre;
    QwtSpline spline,spline2;
    LinearInter sLinearOmbre;
      
    /* Diagramma Solare*/  
   //Is an ordered vector? TODO//
    if (!MyMath::isOrdered(dati))
    qStableSort(dati.begin(),dati.end(),lessThanPoint);

    sp.setSpline(spline);
    sp.spline().setPoints(dati);
    /* Ombre */
    sLinearOmbre.setPoints(ombre);
    spOmbre.setSpline(spline2);
    spOmbre.spline().setPoints(ombre);
                 #ifdef DEBUG
        qDebug()<<"MP eArea, estremi di integrazione"<<a<<b  ;
        qDebug()<<"MP eArea, ombre"<<ombre;
        #endif
     
    
	/* Estremi di integrazione: sunrise e sunset */
	/* Regola dei trapezi */
	/* 1) Calcolo il delta */
	
        
	/* Check of interval */
	a = (a<dati.at(0).x()) ? dati.at(0).x() : a;
	b = (b>dati.at(dati.size()-1).x()) ? dati.at(dati.size()-1).x() : b;
	
	h = (b-a)/n;
	
        if (m==sampleAndHoldMode){
	
        estremoSinistroOmbra = sLinearOmbre.value(a);
        estremoDestroOmbra   = sLinearOmbre.value(b);
        #ifdef DEBUG
        qDebug()<<"MP dati ombre------------------------------"<<ombre;
         qDebug()<<"-------------------------------------------";
	qDebug()<<"MP earea new extremes "<<a<<b<<h;
    	qDebug()<<"MP Fisso estremi"<<estremoSinistroOmbra<<estremoDestroOmbra;
        #endif
        }
        if (m==splineMode){
             estremoSinistroOmbra = spOmbre.spline().value(a);
             estremoDestroOmbra   = spOmbre.spline().value(b);
         }

		
	estremoSinistroSolar = sp.spline().value(a);
	estremoDestroSolar   = sp.spline().value(b);
	area = h/2*( fabs(estremoSinistroSolar) + fabs(estremoDestroSolar));
	
	/* Uso fabs perche' il tramonto e l'alba danno elevazioni negative 
	/* secondo la routine esatta della nasa */
	b1 = (int)(fabs(estremoSinistroSolar)-estremoSinistroOmbra<0.0000000002);
	b2 = (int)(fabs(estremoDestroSolar)-estremoDestroOmbra*2<0.0000000002);
	
	 switch (b1+b2) {
		case 0:
		areaOmbre =0;

		break;
		case 1:
		areaOmbre = h/2*(fabs(estremoSinistroSolar) + fabs(estremoDestroOmbra));
		break;
		case 2:
		areaOmbre = h/2*(fabs(estremoSinistroOmbra) + fabs(estremoDestroSolar));
		break;
		case 3:
		areaOmbre = h/2*(fabs(estremoSinistroSolar) + fabs(estremoDestroSolar));
		break;
	}
     	#ifdef DEBUG
   	qDebug()<<"Area iniziale di integrazione..."<<areaOmbre<<area<<b1+b2<<estremoSinistroOmbra<<estremoDestroOmbra<<estremoDestroSolar<<estremoSinistroSolar<<h;
    	#endif 
	
	for(int i=1;i<=n-1;i++) {
                solarPath = fabs((sp.spline().value(a+h*i)));
                //qDebug()<<"MYPLOT eArea solarpath"<<solarPath<<(a+h*i);
                if (m==splineMode)
                ombrePath = spOmbre.spline().value(a+h*i);
                else{
                ombrePath = sLinearOmbre.value(a+h*i);
               // qDebug()<<"Punto d'ombra...."<<ombrePath<<solarPath<<a<<h*i;
		}

		area += h*solarPath;
		
		if (ombrePath - solarPath>0.000000002)
			areaOmbre += h*solarPath;
		else
                        areaOmbre += 0;
		
		}
                           #ifdef DEBUG
              //  qDebug()<<"Compute area.........."<<area<<areaOmbre<<solarPath;
                         #endif
	return 1-areaOmbre/area;


}
void MyPlot::drawMyContents(int m)
{
// 	qDebug()<<"This color in draw"<<thisMonthColor;
        int  days;
	
	QwtSymbol sym;
	sym.setStyle(QwtSymbol::Ellipse);
	sym.setPen(QColor(Qt::blue));
	sym.setSize(5);
	QPen penRed,penBlack;
            penRed.setWidth(1);
            penRed.setColor(Qt::red);
            penBlack.setWidth(1);
            penBlack.setColor(Qt::black);
        QPen penMarker;
            penMarker.setWidth(1);
            penMarker.setColor(Qt::blue);
	days=0;
for (int mm=1; mm<=12;mm++) {
	if (tropic()!=0){
// 		qDebug()<<"SETTO IL COLORE A "<<thisMonthColor.at(mm).y();
		if (thisMonthColor.at(mm).y()==1)
			{
			
			dSolar[mm-1]->setPen(penRed);
			}
		else
			dSolar[mm-1]->setPen(penBlack);
	}
	else
			dSolar[mm-1]->setPen(penBlack);

 	if (m==1){
      		dSolar[mm-1]->setRawData(dataToPlotX[mm-1],dataToPlotY[mm-1],numHours);
//   		dSolar[mm-1]->setData(sunP[mm-1]);// questo non funziona bene...

                monthMarker[mm-1]->setSymbol(QwtSymbol(QwtSymbol::Ellipse,QBrush(QColor(0, 0, 255, 127),Qt::SolidPattern),penMarker,QSize(20,20)));
		monthMarker[mm-1]->setValue(monthPosX[mm-1],monthPosY[mm-1]);
                QwtText label(QString::number(mm));
                    label.setFont(QFont("Helvetica [Cronyx]", 10));
                    label.setColor(QColor("white"));
                monthMarker[mm-1]->setLabel(label);
		
                legendMarker[mm-1]->setSymbol(QwtSymbol(QwtSymbol::Ellipse,QBrush(QColor(0, 0, 255, 127),Qt::SolidPattern),penMarker,QSize(14,14)));
                legendMarker[mm-1]->setValue(-180,80-4*mm);
                QwtText labelM(QString::number(mm));
                    labelM.setFont(QFont("Helvetica [Cronyx]", 8));
                    labelM.setColor(QColor("white"));
                legendMarker[mm-1]->setLabel(labelM);

                legendMarkerText[mm-1]->setLabel(QwtText(monthLabels[mm-1]));
                legendMarkerText[mm-1]->setValue(-160,80-4*mm);

                //Giugno 2010
                //if ((!graphPresent) & shadowLoaded())
                //		emit ombreChanged();

		graphPresent = true;             
                

	} else {
		dSolar[mm-1]->setRawData(0,0,0);
		monthMarker[mm-1]->setLabel(QwtText(""));
                monthMarker[mm-1]->setSymbol(QwtSymbol());
                legendMarker[mm-1]->setSymbol(QwtSymbol());
                legendMarker[mm-1]->setLabel(QwtText(""));
                legendMarkerText[mm-1]->setSymbol(QwtSymbol());
                legendMarkerText[mm-1]->setLabel(QwtText(""));
		graphPresent = false;
		resetTitle();
		
	}
 
 	}
	// Plot the hours. We do not need new pointer. We copy the data with setData
	if (tropic()!=0)
		setAxisScale(QwtPlot::xTop,-180*1.2,180*1.2);
 
   int t = ceil(1/step);
   for (int i=0; i< numHours-1; i+=t) {
	/* Labels for hours */	
	QString label = QString::number(hl[i]);
	QString label2= "<font color=\"red\">(" + QString::number(hl[numHours-i ]) + ")</font>";
	QString label3= "<font color=\"red\">" + QString::number(hl[i]) + "</font>";
	QwtText text;

// 	QwtText label(QString::number(hl[i]));
// 	QwtText label2(QString::number(hl[numHours-i-2]));
// 	label2.setColor(Qt::red);
		if (m==1) {
			
			if (tropic()!=0)
			{	/* We are at tropics */
				dTime[i]->setStyle(QwtPlotCurve::Dots);
				dTime[i]->setSymbol(sym);
// 				hourMarker2[i]->setValue(hourPos2.at(i).x(),hourPos2.at(i).y());
// 				hourMarker2[i]->setLabel(label2);
				text.setText(label + label2,QwtText::RichText);
				
			}
			else
			{
				dTime[i]->setStyle(QwtPlotCurve::Lines);
				dTime[i]->setSymbol(QwtSymbol());
				if (reorder==1)
					/* Sourhern emisphere */
					text.setText(label3);
				if (reorder==0)
					/* Northern emisphere */
					text.setText(label);
			}
			

			hourMarker[i]->setValue(hourPos.at(i).x(),hourPos.at(i).y());
			hourMarker[i]->setLabel(text);
 
  			dTime[i]->setRawData(timeX[i],timeY[i],12*numDays);
			
 		} 
		else 
		{
	 		dTime[i]->setData(0,0,0);
			hourMarker[i]->setLabel(QwtText(""));
		}
         //legend->remove(dTime[i]);
   }
//         legend->remove(dTiltShadowWest);
//         legend->remove(dTiltShadowEast);
//         legend->remove(dShadowTemp);
//         legend->remove(dShadow);

//   if (m==1){
//   qDebug()<<"MP draw legend";
//                QwtText l;
//                l.setText(legendString);
//                legendMarker->setValue(-180,80);
//                legendMarker->setLabel(l);
//                }
//                else
//                {
//                 legendMarker->setLabel(QwtText(""));
//                }
   
   
	

    replot();
  
  
}
void MyPlot::setCurrentSide(int m)
{
/* For now only two sides */
if (m<2)
    currentSide=m;
    else
    currentSide=0;
    }
void MyPlot::toggleSelfShadow(int m )
{

	if (m==Qt::Checked) {
            if (currentSide==0){
   		 dTiltShadowEast->setData(sunIncEast);	
		 dTiltShadowWest->setData(sunIncWest);
                 }
            if (currentSide==1){
                 dTiltShadowEast->setData(sunIncEast2);
                 dTiltShadowWest->setData(sunIncWest2);
                 }
                //#ifdef DEBUG
		qDebug()<<"Myplot: Stampo le ombre dovute al tilt"<<m;
                //#endif
	}
	else {
		dTiltShadowEast->setRawData(0,0,0);
		dTiltShadowWest->setRawData(0,0,0);
	}
replot();
}

void MyPlot::drawShadow(int mode,const QPolygonF &data)
{
  #ifdef DEBUG
 qDebug()<<"shadow in drawShadow.."<<shadowCombined.size()<<ombreMode <<mode;
  #endif
if (ombreMode==1)
	dShadow->setCurveAttribute(QwtPlotCurve::Fitted,true);
    else
	dShadow->setCurveAttribute(QwtPlotCurve::Fitted,false);


if (mode == 1) {
	 //Add the shadows if exist
//    	#ifdef DEBUG
       
//        	#endif
 
	
   	dShadow->setData(shadowCombined);
	}

 if (mode==2)
	dShadowTemp->setData(data);
if (mode==3)
	//Delete preview shadow//
	dShadowTemp->setRawData(0,0,0);
if (mode==0)
	
	dShadow->setRawData(0,0,0);
    	replot();
}

void  MyPlot::setHSteps(int startH,int endH, double stepH)
{
// 	startH = 4;
// 	endH   = 22;
// 	stepH = 0.2;

//        legend->clear();
	numDays=6;
	step = stepH;
	
	intervalDays  = new int[numDays];
	intervalDays[0] = 1;
	intervalDays[1] = 8;
	intervalDays[3] = 22;
	intervalDays[4] = 25;



	numHours=ceil(((-startH + endH) +1)/stepH);
	numHoursFast = ceil(numHours*stepH);;
	 
	hl = new double[numHours];
 	hl[0]=startH;;
	dTime = 	new QwtPlotCurve*[numHours];
	hourMarker =    new QwtPlotMarker*[numHours];
	hourMarker2 =    new QwtPlotMarker*[numHours]; // For tropics
	dTime[0] =      new QwtPlotCurve();
	dTime[0]->attach(this);
	hourMarker[0] = new QwtPlotMarker();
	hourMarker[0]->attach(this);

	hourMarker2[0] = new QwtPlotMarker();
	hourMarker2[0]->attach(this);
	
	timeX    = new double*[numHours];
	timeY    = new double*[numHours];
	timeX[0] = new double[12*numDays];
	timeY[0] = new double[12*numDays];
	for(int i=1;i<numHours;i++) { hl[i] = hl[i-1]+stepH;
					dTime[i] = new QwtPlotCurve();
					dTime[i]->attach(this);
					hourMarker[i] = new QwtPlotMarker();
					hourMarker[i]->attach(this);
					hourMarker2[i] = new QwtPlotMarker();
					hourMarker2[i]->attach(this);
					#if QT_VERSION >= 0x040000
   					dTime[i]->setRenderHint(QwtPlotItem::RenderAntialiased);
// 					dTime[i]->setCurveAttribute(QwtPlotCurve::Fitted,true);
					dTime[i]->setPen(QPen(Qt::blue));
					dTime[i]->setPaintAttribute(QwtPlotCurve::ClipPolygons,true);
					#endif
					timeX[i] = new double[12*numDays];
					timeY[i] = new double[12*numDays];
                                        // Remove from legend
//                                        legend->remove(dTime[i]);
					} 
	
	 
	hf = new double[(int)(numHoursFast)];	
	hf[0] = startH;
	for(int i=1;i<(int)(ceil(stepH*numHours));i++) { hf[i] = hf[i-1]+1;}

	// 	Create multidimensional vectors
        sunEA= new double*[numDays*12];
        for(int i=0;i<numDays*12;i++) {sunEA[i]=new double[numHours];}

        sunAZ= new double*[numDays*12];
        for(int i=0;i<numDays*12;i++) {sunAZ[i]=new double[numHours];}

	sunInc = new double*[numDays*12];
	for(int i=0;i<numDays*12;i++) {sunInc[i]=new double[numHours];}

  	dataToPlotX = new double*[12];
        dataToPlotY = new double*[12];
        QPen pen;
        pen.setWidth(1);
        pen.setColor(Qt::black);



	for(int i=0;i<12;i++) {
  		dataToPlotX[i]=new double[numHours];
  		dataToPlotY[i] = new double[numHours];
                dSolar[i] = new QwtPlotCurve(monthLabels[i]);

		#if QT_VERSION >= 0x040000
   		dSolar[i]->setRenderHint(QwtPlotItem::RenderAntialiased);
     		dSolar[i]->setCurveAttribute(QwtPlotCurve::Fitted,true);
		dSolar[i]->setPaintAttribute(QwtPlotCurve::ClipPolygons,true);
		#endif	

		dSolar[i]->setPen(pen);
		dSolar[i]->setYAxis(QwtPlot::yLeft);
		dSolar[i]->attach(this);
		
		monthMarker[i] = new QwtPlotMarker();

		monthMarker[i]->attach(this);

                legendMarker[i] = new QwtPlotMarker();
                legendMarker[i]->attach(this);

                legendMarkerText[i] = new QwtPlotMarker();
                legendMarkerText[i]->attach(this);
	}

	
// 	hourPosX  = new double[numHours];
// 	hourPosY  = new double[numHours];
	
	monthPosX = new double[12];
	monthPosY = new double[12];
	
	 
// 	 timeDataX = new double[12*numDays];
//          timeDataY = new double[12*numDays];
	
        dShadow = new QwtPlotCurve();
	dShadowTemp = new QwtPlotCurve();
	#if QT_VERSION >= 0x040000
   		dShadow->setRenderHint(QwtPlotItem::RenderAntialiased);
		dShadowTemp->setRenderHint(QwtPlotItem::RenderAntialiased);
   //		dShadow->setCurveAttribute(QwtPlotCurve::Fitted,true);
		dShadow->setPaintAttribute(QwtPlotCurve::ClipPolygons,true);
		dShadowTemp->setPaintAttribute(QwtPlotCurve::ClipPolygons,true);
		#endif	
                QColor c;
                c.setHsv(121,3,99,220);
        QPen p;
        p.setColor(Qt::red);
        p.setStyle(Qt::SolidLine);
        p.setWidth(5);
        dShadow->setPen(p);
        dShadow->setBrush(QBrush(c,Qt::SolidPattern));
        dShadow->attach(this);

	dShadowTemp->setPen(QPen(Qt::red));
	dShadowTemp->setBrush(QBrush(Qt::Dense7Pattern));
	dShadowTemp->attach(this);


	p.setWidth(5);
	p.setColor(Qt::blue);
	dTiltShadowEast = new QwtPlotCurve();
	dTiltShadowEast->setStyle(QwtPlotCurve::Dots);
 
	dTiltShadowEast->setPen(p);
// 	dTiltShadowEast->setBrush(QBrush(Qt::Dense7Pattern));
	dTiltShadowEast->attach(this);
	
	dTiltShadowWest = new QwtPlotCurve();
	dTiltShadowWest->setStyle(QwtPlotCurve::Dots);
	dTiltShadowWest->setPen(p);
// 	dTiltShadowWest->setBrush(QBrush(Qt::Dense7Pattern));
	dTiltShadowWest->attach(this);


//         legend->remove(dTiltShadowWest);
//         legend->remove(dTiltShadowEast);
//         legend->remove(dShadowTemp);
//         legend->remove(dShadow);
//qDebug()<<"MP legend items setsteps"<<legend->itemCount();

 
}
// void MyPlot::setDamp()
// {
// 	compute();
// 	setAutoReplot(false);
// 	drawContents();
// }
void MyPlot::createActions()
{
	a_print       =  new QAction(tr("&Stampa"),this);
	a_print->setShortcut(tr("Ctrl+P"));
	a_export      = new QAction(tr("&SVG"),this);

	a_export->setShortcut(tr("Ctrl+S+V"));

	a_proprieta   = new QAction(tr("Impostazioni"),this);

	a_create_grid = new QAction(tr("Griglia"),this);

	a_exportPNG   = new QAction(tr("PNG"),this);
	
	a_exportPDF = new QAction(tr("PDF"),this);
	a_exportPDF->setIcon(QIcon(":/images/pdf.jpeg"));

	a_load_shadow = new QAction(tr("Carica"),this);
	a_load_shadow->setShortcut(tr("Ctrl+O"));
	a_delete_shadow = new QAction(tr("Rimuovi"),this);
	a_delete_shadow->setShortcut(tr("Ctrl+X"));

	a_undo_combine = new QAction(tr("Annulla"),this);
	a_undo_combine ->setShortcut(tr("Ctrl+Z"));
	
	connect(a_print,SIGNAL(triggered()),this,SLOT(printOut()));
	connect(a_export,SIGNAL(triggered()),this,SLOT(exportSVG()));
	connect(a_proprieta,SIGNAL(triggered()),this,SLOT(settings()));
	connect(a_create_grid,SIGNAL(triggered()),this,SLOT(gridset()));
	connect(a_exportPNG,SIGNAL(triggered()),this,SLOT(exportPNG()));
	connect(a_exportPDF,SIGNAL(triggered()),this,SLOT(exportPDF()));
	connect(a_load_shadow,SIGNAL(triggered()),this,SLOT(loadShadow()));
	connect(a_delete_shadow,SIGNAL(triggered()),this,SLOT(deleteShadow()));
	connect(a_undo_combine,SIGNAL(triggered()),SLOT(undoCombine()));
}

void MyPlot::gridset()
{
	if (!gridSettings-isVisible())
	gridSettings->show();
}

void MyPlot::popUpMenu(const QPoint &pos)
{ 
	 
 	QMenu menu;
	QMenu exMenu(tr("&Esporta"),&menu);
	QMenu ombreMenu(tr("&Ombre"),&menu);
	
	exMenu.addAction(a_export);
	exMenu.addAction(a_exportPNG);
	exMenu.addAction(a_exportPDF);
	
	ombreMenu.addAction(a_load_shadow);
	ombreMenu.addAction(a_delete_shadow);
	
// 	menu.addAction(a_undo_combine);
	menu.addAction(a_print);
	menu.addMenu(&exMenu);
	menu.addMenu(&ombreMenu);
	
	menu.addAction(a_proprieta);
	menu.addAction(a_create_grid);
	 
	#ifdef Q_WS_X11
	menu.popup(pos);	
	#endif
	menu.exec(QCursor::pos());
}
void MyPlot::settings()
{
	#ifdef DEBUG
	qDebug()<<"I am here";	
	#endif
// 	Settings s2;
// 	int a;
	if (!set->isVisible()) 	 
	set->show();
	
}
void MyPlot::exportPDF()
{
	 QString fileName;
	 fileName = QFileDialog::getSaveFileName(this, tr("Nome file da esportare"),   recentExportPath,"Acrobat ( *pdf)");
	QFileInfo fileInfo(fileName);
        recentExportPath = fileInfo.absoluteDir().absolutePath();
	if ( !fileName.isEmpty() ) {
	   fileName = MyMath::checkFormat(fileName,"pdf");
         QPrinter printer;
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

        //NOW try to open the exported file
        QDesktopServices::openUrl(fileName);

      }
}

void MyPlot::printOut()
{
	 QPrinter printer(QPrinter::HighResolution);
	#ifdef Q_WS_X11
	 printer.setOutputFileName(tr("diagrammasolare.pdf"));
	#endif
	 printer.setCreator("Solar Calc");
         printer.setOrientation(QPrinter::Landscape);
	 
	 QPrintDialog dialog(&printer);
    if ( dialog.exec() )
    {	
	QwtPlotPrintFilter filter;
//          if ( printer.colorMode() == QPrinter::GrayScale )
        {
            int options = QwtPlotPrintFilter::PrintAll;
            options &= ~QwtPlotPrintFilter::PrintBackground;
            options |= QwtPlotPrintFilter::PrintFrameWithScales;
            filter.setOptions(options);
        }

	print(printer,filter);



   }
}
void MyPlot::exportSVG()
{
	QString fileName;
 

    fileName = QFileDialog::getSaveFileName(this, tr("Nome file da esportare"),  recentExportPath,"Graphic files ( *svg)");
	
    QFileInfo fileInfo(fileName);
    recentExportPath = fileInfo.absoluteDir().absolutePath();
    
    if ( !fileName.isEmpty() )
    {
	fileName = MyMath::checkFormat(fileName,"svg");
        QSvgGenerator generator;
        generator.setFileName(fileName);
        generator.setSize(QSize(1024, 800));
	QwtPlotPrintFilter filter;
   	int options = QwtPlotPrintFilter::PrintAll;
            options |= ~QwtPlotPrintFilter::PrintBackground;
            options |= QwtPlotPrintFilter::PrintFrameWithScales|QwtPlotPrintFilter::PrintMargin;
	    filter.setOptions(options);
           
//     QPixmap pixmap =  QPixmap::grabWidget(this);
//     QPainter painter(&generator);
      print(generator,filter);
    }
	

}
QImage*  MyPlot::getImage()

{	
 

    
    QString filename = "temp_getImage.png";
    
    
    {
	
       
        QwtPlotPrintFilter filter;
   	int options = QwtPlotPrintFilter::PrintAll;
            options |=  QwtPlotPrintFilter::PrintBackground;
            options |= QwtPlotPrintFilter::PrintFrameWithScales;
	    filter.setOptions(options);
	 
// 	image->fill(Qt::white);
  	QPixmap pixmap(1024,800);
// 	pixmap.fill(Qt::white);
        print(*image,filter);
	 
// 	 if ( p.save(filename, "png" ))
// 		qDebug()<<"Ok";
//    else
// 		qDebug()<<"Error";
// 	 
         return image;
    }
	
	 
}
void MyPlot::exportPNG(QString& fileName)
{

    if ( !fileName.isEmpty() )
    {
        fileName = MyMath::checkFormat(fileName,"png");
        QwtPlotPrintFilter filter;
        int options = QwtPlotPrintFilter::PrintAll;
               options  = ~QwtPlotPrintFilter::PrintBackground;
               options |= QwtPlotPrintFilter::PrintFrameWithScales;

        filter.setOptions(options);
        //QImage pixmap(800,600,QImage::Format_RGB32);
// 	QPixmap pixmap= QPixmap::grabWidget(p);
        QPixmap pixmap(1024,800);
        pixmap.fill(Qt::white);

        print(pixmap,filter );

   if ( pixmap.save(fileName, "png" ))
                qDebug()<<"Ok";
   else
                qDebug()<<"Error"<<fileName;
        }
}

void MyPlot::exportPNG()
{	QString fileName;
 
        fileName = QFileDialog::getSaveFileName(this, tr("Nome file da esportare"),  recentExportPath,"Graphic files (*.png  )");
	QFileInfo fileInfo(fileName);
        recentExportPath = fileInfo.absoluteDir().absolutePath();

        exportPNG(fileName);
}
void MyPlot::moved(const QwtDoublePoint &pos)
{
//	qDebug()<<pos;
	picker->rubberBand();
	label->setText(QString::number(pos.x())+","+QString::number(pos.y()));
}
void MyPlot::selected(const QwtDoublePoint &pos)
{
// 	qDebug()<<"I am here"<<pos;
	label->setText(QString::number(pos.x())+","+QString::number(pos.y()));
}
void MyPlot::setLocName(const QString &s)
{
	name = s;
	QString title = tr("Diagramma solare, ") + " " + s;
        QwtText tlabel("<p>"+title+"</p>");
        tlabel.setRenderFlags(tlabel.renderFlags() | Qt::TextWordWrap);
	tlabel.setFont(QFont("Times",13,QFont::Normal));
	set->setTitle(title);
        setTitle(tlabel);
	 
}

bool MyPlot::shadowLoaded()
{
    return (shadow.size()>0? true:false);
}
bool MyPlot::nearShadowLoaded()
{
    return (nearShadow.size()>0? true:false);
}
void MyPlot::loadShadow()
{
	loadShadow("");
}
void MyPlot::loadShadow(const QString &f)
{
     
//         LinearInter sp;
        double  x,y;
        int condition;
	QVector<int> idxVector;

 	condition = 0;
	if (f.isEmpty())
        fileName = QFileDialog::getOpenFileName(this, tr("File ombre e orizzonti"), recentDir, "Text files (*.txt *.shadow )");
	else
	fileName = f;
	
	QFileInfo fileInfo(fileName);
// 	  qDebug()<<"Sono in loadShadow of myplot"<<fileInfo.exists() ;
    	if ( !fileName.isEmpty() && fileInfo.exists()  )
    	{ 
                QFile file(fileName);
                
                recentDir = fileInfo.absoluteDir().absolutePath();
		QTextStream in(&file);
		// Make a copy
                QPolygonF temp,temp2 ;
		
			
		if (file.open(QIODevice::ReadOnly)){

			while (!in.atEnd()) {
				QString lineRaw =in.readLine();
				lineRaw = lineRaw.simplified();
				QStringList l = lineRaw.split(" ");
				 
				if ( (l.size()<2) && (!lineRaw.isEmpty())) {
                                        QMessageBox::critical(this,tr("Importazione"),tr("Il file di dati deve avere almeno due colonne."),QMessageBox::Ok);

					return;
				}
				else 
				{
					if (!lineRaw.isEmpty()) {
						x = l.at(0).toDouble();
						y = l.at(1).toDouble();
                                                if (y<0) {
							condition++;
                                                        y = 0;
                                                         }
                                                temp<<QPointF(x,y);

					}
                                }
                            }
			if (condition>0)
				QMessageBox::warning(this,tr("Importazione ombre"),tr("Il file di ombre contiene ordinate negative. Le ho azzerate."),QMessageBox::Ok);

                temp2 = processShadow(temp,rawdata);/*for example, sample and hold */
		combineShadow(temp2); /*combine with existent horizon*/
		combineRawAndPoly();
                //qDebug()<<"Sono in loadShadow of myplot,shadowpresent"<<shadowLoaded()<<shadow.size()<<temp2;
		}

    		
    	
		drawShadow(1,QPolygonF());

		if (graphPresent){
			compute();
			//computeShadow();
			emit ombreChanged();
			}
	}
    	}
void MyPlot::combineRawAndPoly()
{
	if (nearShadowLoaded())
		if (shadowLoaded())
			shadowCombined = combineMax(shadow,nearShadow);
		else
			shadowCombined = nearShadow;
	
			
       // qDebug()<<"MYPLOT combineRawAndPoly"<<shadowLoaded()<<shadowCombined;
}
void MyPlot::combineShadow(QPolygonF &data)
{
	/* This function combine horizon data */

	if (shadowLoaded()) {
		previousShadow = shadow;
		if (shadow!=data)
		{
		shadowCombined = combineMax(shadow,data);
		shadow = shadowCombined;
		}
// 	qDebug()<<"MYPLOT combineShadow"<<shadowCombined;
	}
	else {
		shadow = data;
		shadowCombined = data;
	}
}
QPolygonF MyPlot::processShadow(QPolygonF &data,int type)
{
    QPolygonF out;
// 	qDebug()<<"process ombre..."<<ombreMode;
                switch (ombreMode) {
                        case sampleAndHoldMode:
				if (type==rawdata)
				out = sampleAndHold(data);
				if (type==polygon)
				out = sampleAndHoldPoly(data);

// 				combineShadow(data);
                        break;

                        case splineMode:
				if (type==rawdata) 
				{
				 
				out = combineSpline(shadow,data);
				}
				 
				
                        break;
			 
				
                    }
        return out;
}
int MyPlot::digitize(double x,double Lo,double delta)
{
	/* Ritorna l'indice dell'intervallo che contiene il punto*/
	if (delta>0)
                return ceil((x-Lo)/delta);
	else
		return -1;
	
}
QPolygonF MyPlot::sampleAndHoldPoly(const QPolygonF &data)
{
	  QPolygonF temp(baseShadow);
	  QVector<int> idx ;
	  int index;
	  double x,y;
	 /* Prima digitalizzo */
        for(int i=0;i<data.size();i++){
            x = data.at(i).x();
            y = data.at(i).y();
            index = digitize(x,offset,delta);
            idx.append(index);
            if (index<temp.size() && index>=0){
                 temp.replace(index,QPointF(temp.at(index).x(),y));
		 #ifdef DEBUG
                qDebug()<<"MYPLOT sampleAndHold..."<<index<<temp<<x<<y;
                #endif
		}
            else
                {
                #ifdef DEBUG
                qDebug()<<"Errore in sampleAndHold..."<<index<<temp<<x<<y;
                #endif
                }
        }
	/* Qui campiono e linearizzo */
	/* Scannerizzo il vettore temp che gia' contiene i punti del poligono (da sopra) */
        double x1,x2,y1,y2;
//   	 qDebug()<<"MYPLOT s&Hpoly"<<idx.size()<<idx<<data;
// 	  qDebug()<<"MYPLOT s&Hpoly before loop"<<temp.size()<<temp;
        for(int i=0;i<idx.size()-1;i++) {
		x1 = temp.at(idx.at(i)).x();
		x2 = temp.at(idx.at(i+1)).x();
		y1 = temp.at(idx.at(i)).y();
		y2 = temp.at(idx.at(i+1)).y();
		for(int k=0;k<idx.at(i+1)-idx.at(i);k++){
			
   			x  = temp.at(idx.at(i)+k).x();
//   			qDebug()<<"MYPLOT s&H"<<x1<<x2<<y1<<y2<<x<<k<<i<<temp.at(idx.at(i)+k).x();
  			temp.replace((idx.at(i)+k),QPointF(temp.at(idx.at(i)+k).x(),MyMath::linear(x1,y1,x2,y2,x)));
		}
	}
	return temp;
}
QPolygonF MyPlot::sampleAndHold(const QPolygonF &data)
{
	
	/* Fa quello che dice */
	/* idx e' il vettore degli indici dei valori da campionare */
        QPointF sample;
        QPolygonF temp(baseShadow);
        QPolygonF hold;
        QVector<int> idxVector;
        int idx;
        bool sampleFound = false;
        double x,y;

        /* Prima digitalizzo */
        for(int i=0;i<data.size();i++){
            x = data.at(i).x();
            y = data.at(i).y();
            idx = digitize(x,offset,delta);
            idxVector.append(idx);
            if (idx<temp.size() && idx>=0)
                 temp.replace(idx,QPointF(temp.at(idx).x(),y));
            else
                {
                #ifdef DEBUG
                qDebug()<<"Errore....";
                #endif
                }
        }
        /* Qui campiono e mantengo */
        for(int i=0;i<temp.size();i++) {
                sample.setX( temp.at(i).x());
                if (idxVector.contains(i))
		{
                  sample.setY( temp.at(i).y());
		  sampleFound = true;
		  
		}
 		else
 		{
		  if (!sampleFound)
 		  sample.setY(0);
 		  
 		}
	hold.append(sample);
	}
//          qDebug()<<"Sample data..."<<data.size();
//          qDebug()<<"Hold data..."<<hold.size();
//          qDebug()<<"Idx vector..."<<idx;
	return hold;
}
bool MyPlot::lessThanPoint(const QPointF &p1, const QPointF &p2)
{
//   	if (fabs((p1.x()-p2.x()))<0.000001)
  		/* Punti con la stessa ascissa */
//   		return ( p1.y()<p2.y() );
	return ( p1.x() < p2.x() );
			
}
bool MyPlot::lessThanPointLast(const QPointF &p1, const QPointF &p2)
{
  	if (fabs((p1.x()-p2.x()))<0.000001)
  		/* Punti con la stessa ascissa */
  		return ( p1.y()>p2.y() );
	return ( p1.x() < p2.x() );
			
}
QPolygonF MyPlot::combineSpline(const QPolygonF &p1, const QPolygonF &p2)
{
         /* Compute interpolated values based on a grid */
        double x,y1,y2;
        QPolygonF temp;
        QwtSplineCurveFitter sp1,sp2;
        QwtSpline s1,s2;
        sp1.setSpline(s1);
        sp2.setSpline(s2);
        sp1.spline().setPoints(p1);
        sp2.spline().setPoints(p2);

        for(int i=0;i<baseShadow.size();i++){
            x = baseShadow.at(i).x();/* reference to the grid */
            y1 = sp1.spline().value(x);
            y2 = sp2.spline().value(x);
            if (y1>y2)
                    temp.append(QPointF(x,y1));
                else
                    temp.append(QPointF(x,y2));
            }

return temp;
}
QPolygonF MyPlot::combineMax(const QPolygonF &p1,const QPolygonF &p2)
{
	/* we must have polygon referenced to the grid */
	QPolygonF temp;
         qDebug()<<"MYPLOT combineMax, size different?"<<p1.size()<<p2.size();

        if (p1.size()==0 && p2.size()>0)
        {
                return p2;
        }
        if (p1.size()>0 && p2.size() == 0)
        {
            return p1;
        }

	if (p1.size()!=p2.size())
		{
                 qDebug()<<"MYPLOT combineMax, size different"<<p1.size()<<p2.size();
		return QPolygonF();
		}
	for(int i=0;i<p1.size();i++)
            if (p1.at(i).y()>p2.at(i).y()){
                    //qDebug()<<"MP combineMax found"<<p1.at(i).y();
			temp.append(p1.at(i));
                    }
        else{
                       // qDebug()<<"MP combineMax found"<<p2.at(i).y();
			temp.append(p2.at(i));
                    }
	return temp;
}
 
QPolygonF  MyPlot::combine( QPolygonF &serie1,   QPolygonF &serie2)
{
 
	 QPolygonF p1(serie1);
	 QPolygonF p2(serie2);
	 if (!p1.contains(QPointF(serie1.first().x(),0)))
	 	p1.prepend(QPointF(serie1.first().x(),0));
	 if (!p1.contains(QPointF(serie1.last().x(),0)))
	 	p1.append(QPointF(serie1.last().x(),0));
	 if (!p2.contains(QPointF(serie2.first().x(),0)))
	 	p2.prepend(QPointF(serie2.first().x(),0));
	 if (!p2.contains(QPointF(serie2.last().x(),0)))
	 	p2.append(QPointF(serie2.last().x(),0));

 	 QPolygonF temp(p1.united(p2));
	double first,last;
	first = MyMath::leftValue(temp);
	last =  MyMath::rightValue(temp); 
	
//  	qDebug()<<"Combined...."<<temp;
// 	qDebug()<<"first Last..."<<first<<last;

	 
	
// 	 qDebug()<<"serie 1 ...."<<p1;
// 	 qDebug()<<"serie 2....."<<p2;

 	temp.resize(temp.size()-1);
	 /* elimino asseX */
	QPolygonF a;
	 for(int i=0;i<temp.size();i++)
	 {
// 	qDebug()<<"Elimino asseX..."<<(temp.at(i).x()<=last)<<(temp.at(i).x()>=first)<<temp.at(i).x()<<temp.at(i).y()<<(temp.at(i).y()==0);
		if (temp.at(i).y()!=0)
// 		   if ((temp.at(i).x())<=last && (temp.at(i).x())>=first )
// 			a.remove(i);
		a.append(temp.at(i));
	 }
	
// 	 qDebug()<<"Afte removing asseX...."<<a;
	 if (!MyMath::isOrdered(a))
	 qStableSort(a.begin(),a.end(),lessThanPoint);

	 
	 return a;
}
bool MyPlot::ombrePresent()
{
// 	/*Controlliamo se ci sonoombre */
 	if (shadow.size()>0)
	return true;
	else
	return false;
}
void MyPlot::deleteShadow()
{
	shadow.resize(0);
	shadowCombined.resize(0);
	nearShadow.resize(0);
	drawShadow(0,QPolygonF());
	drawShadow(3,QPolygonF());
	ombreFactor.resize(0);
	ombreFactor.fill(1,12);
	 
	emit ombreChanged();
	
}
void MyPlot::resetOmbre()
/* As deleteShadow, but do not emit ombreChanged*/
{
shadow.resize(0);
	shadowCombined.resize(0);
	nearShadow.resize(0);
	drawShadow(0,QPolygonF());
	drawShadow(3,QPolygonF());
	ombreFactor.resize(0);
	ombreFactor.fill(1,12);
	 
// 	qDebug()<<"MYPLOT resetOmbre"<<nearShadow.size()<<shadowCombined.size();
}
QPolygonF MyPlot::getDailyShadowFactor()
{
	return dailyOmbreFactor;
}
// double MyPlot::getHourlyOmbreFactor(int day,int hour)
// /* This function compute the ombre factor for a particulat hour. Daily value must be available */
// {

// }
// double* MyPlot::getShadowFactor()
// {
// 	double* start = ombreFactor;
// 	return start;
// }
QVector<double>& MyPlot::getShadowFactor()
{
	
	return ombreFactor;
}
void MyPlot::setShadowCombineMode(int m)
{
    if (m>=0 && m<2)
    ombreMode = m;
   	#ifdef DEBUG
	qDebug()<<"MyPlot spline mode:"<<m;
	#endif
}

void MyPlot::setPolyShadow(QPolygonF a,bool fire)
{
        /* We use this method only for setting polygon shadows*/

    if (a.size()>0){
      //  qDebug()<<"MP setPolyShadow top"<<a.size();
        nearShadow.resize(0);   /*delete previous polygon*/
        nearShadowToSave = a;   /* make a copy if the vector to save on disk */

	for(int i=0;i<a.size();i++){
		nearShadow.append(a.at(i));
	}
//qDebug()<<"MP setPolyShadow mid"<<nearShadow.size();
        nearShadow = processShadow(nearShadow,polygon); /* reference to the grid */
        //qDebug()<<"MP setPolyShadow nearShadow"<<nearShadow.size();
        //  qDebug()<<"MYPLOT nearShadow processed"<<nearShadow;
    }
	combineRawAndPoly();
	/* shadow changed, recompute */
	if (graphPresent){
			compute();
			//computeShadow();
                        if (fire)
                            emit ombreChanged();
			}

	
}

void MyPlot::initializeGrid()
{
	/* Resolution is 5 degree */
	int n = (int)ceil(360/delta);
	baseShadow.resize(0);
	for(int i=0;i<=n;i++)
		baseShadow.append(QPointF(offset+i*delta,0));
//   	qDebug()<<baseShadow;
}
void MyPlot::setIntegration(int m)
{
	if (m == 0)
		mode = default_;
	if (m == 1)
		mode = custom_;
		
}
void MyPlot::setDailyOmegaApp(const QPolygonF &input)
{
// Input in degree
	dailyOmegaApp = input;
}
void MyPlot::setDailyOmegaSco(const QPolygonF &input)
{
	dailyOmegaSco = input;
}

// void MyPlot::setOmegaApp(double *a)
// {
// // Input in degree
// 	omegaApp = a;
// 	#ifdef DEBUG
//         qDebug()<<"Ho settato omega app in myplot"<<omegaApp[1];
// 	#endif 
// 	
// }
void MyPlot::setOmegaSco(const QVector<double> &a)
{
// Input in degree
	omegaSco = a;
	#ifdef DEBUG
	qDebug()<<"Ho settato omega sco in myplot"<<omegaSco[1];
	#endif 
	
}
void MyPlot::setOmegaApp(const QVector<double> &a)
{
// Input in degree
	omegaApp = a;
        // #ifdef DEBUG
       // qDebug()<<"MP Ho settato omega app in myplot"<<omegaApp[1];
     //   #endif
	
}
// void MyPlot::setOmegaSco(double* a)
// {
// // Input in degree
// 	omegaSco = a;
// 	#ifdef DEBUG
// 	qDebug()<<"Ho settato omega sco in myplot"<<omegaSco[1];
// 	#endif 
// 	
// }

void MyPlot::setIncl(double i)
{
        spa.slope = i;
}

void MyPlot::setAzi(double a)
{
	/* Westward */
	if (fabs(a)<=360)
	 spa.azm_rotation = -a;
	else
	spa.azm_rotation = 0;
}
QString MyPlot::getFileName()
{
	return fileName;
}
double MyPlot::incidence( double sunZenith,double sunAzimuth,double slope,double rotation)
/*  Return the incidence angle for a given zenith,azimuth,slope */
{
	double i;
	i = acos(cos(sunZenith*pi/180) * cos(slope*pi/180) + 			sin(slope*pi/180)*sin(sunZenith*pi/180)*cos((sunAzimuth-rotation)*pi/180));
				
    	i = 180/pi * i;
	return i;
}
void MyPlot::addSelfShadow2(double x, double v )
{

        if (x<0)
        {
        /* We are at east*/
        sunIncEast2.append(QPointF(x,v));
// 	qDebug()<<"East"<<x<<v;
        }
        else{
// 	qDebug()<<"West"<<x<<v;
        sunIncWest2.append(QPointF(x,v));
        }
}

void MyPlot::addSelfShadow(double x, double v )
{
	
	if (x<0)
	{
	/* We are at east*/
	sunIncEast.append(QPointF(x,v));
// 	qDebug()<<"East"<<x<<v;
	}
	else{
// 	qDebug()<<"West"<<x<<v;
	sunIncWest.append(QPointF(x,v));
	}
}
void MyPlot::resetTitle()
{
	QString str;
	QwtText tlabel(tr("Diagramma solare")+ " ");
        tlabel.setRenderFlags(tlabel.renderFlags() | Qt::TextWordWrap);
	tlabel.setFont(QFont("Times",13,QFont::Normal));
	setTitle(tlabel);
	set->setTitle(tr("Diagramma solare")+ " ");
}
void MyPlot::undoCombine()
{
	shadow = previousShadow;
	drawShadow(1,QPolygonF());
}
void MyPlot::delPoly()
{
	shadowCombined = shadow; /* shadow is always the horizon data */
        nearShadow.resize(0);
        nearShadowToSave.resize(0);
	drawShadow(1,QPolygonF());
}
QPolygonF MyPlot::getShadowCombined()
{
	return shadowCombined;
}
QPolygonF MyPlot::getShadow()
{
        return shadow;
}
QPolygonF MyPlot::getShadowNear()
{
        //return nearShadow;
        return nearShadowToSave;
}
void MyPlot::setShadow(const QPolygonF &f,bool fire)
/* This function set the shadow only if it is a 360 point vector*/
/* It should be called only if the raw data have been processed*/
/* To load user defined data USE load instead.*/
{
        qDebug()<<"MYPLOT set Shadow"<<graphPresent;
        if (f.size()==361){
//		shadowCombined = f;
 /* If we set from outside the shadow it means that they are already combined */
        shadow = f;
        shadowCombined = shadow;
    }
	if (graphPresent){
			compute();
			//computeShadow();
                        if (fire)
                            emit ombreChanged();
			}
	drawShadow(1,QPolygonF());
}
bool MyPlot::checkQuadrant(myspa_data locSpa)
/* Return true if we are in the I and II quadrant */
{
	
	double aziNow,aziAfter;
	int result;
	 
	locSpa.hour = 11;
	result = spa_calculate(&locSpa);
	aziNow = locSpa.azimuth; 

  	locSpa.hour = 13;
	result = spa_calculate(&locSpa);
	aziAfter = locSpa.azimuth;

// 	qDebug()<<"CHECKPOINT "<<tempSpa.month<<tempSpa.day<<tempSpa.hour;
	 
	 
	if (result>0){
 		#ifdef DEBUG
		qDebug()<<"MYPLOT checkQuadrant result"<<result;
  		#endif
 	}
	else
	{
		
		 
			if (!MyMath::clockWise(aziAfter*pi/180,aziNow*pi/180))
			{
//           				qDebug()<<"MYPLOT check quadrant II and III"<<locSpa.month<<locSpa.day<<locSpa.hour<<aziNow<<aziAfter;
  				return false;
  			}
 			else
 			{
//           				qDebug()<<"MYPLOT check quadrant I and IV"<<locSpa.month<<locSpa.day<<locSpa.hour<<aziNow<<aziAfter;
 					return true;
  			}
	}  
}
int MyPlot::tropic()
/* This function tells if we are at tropics */
{
	if (spa.latitude>=0 && spa.latitude<=23.5)
	// North tropic
		return 1;
	if (spa.latitude<0 && spa.latitude>=-23.5)
	//Southern tropic
		return 2;
	if (fabs(spa.latitude)>23.5)
	// Not at tropics
		return 0;
}
int MyPlot::highestMonth(double latitude)
/* This function tells which the month with the highest sun elevation */
{ 
	int t = tropic();
	switch (t) {
		case 1:
			return 9;
		break;
		case 2:
			return 3;
		break;
		default:
		
		if (latitude<0)
				return 12;
			else
				return 6;
		}

	
	
}
int MyPlot::lowestMonth(double latitude)
/* This function tells which the month with the highest sun elevation */
{ 
	int t = tropic();
	switch (t) {
		case 1:
			return 12;
		break;
		case 2:
			return 1;
		break;
		default:
		
		if (latitude<0)
				return 6;
			else
				return 12;
		}
	 
	
	
}
void MyPlot::toggleSpline(int a)
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
		for(int i=0; i<12;i++){
			if (a==Qt::Checked)
				dSolar[i]->setCurveAttribute(QwtPlotCurve::Fitted,true);
			else
				dSolar[i]->setCurveAttribute(QwtPlotCurve::Fitted,false);
		}
		replot();
 QApplication::restoreOverrideCursor();	
}

double MyPlot::hourlyOmbreFactor(int year,int month, int day, int hour)
/* This function return the ombreFactor from the day n and hour hour. Can be 0 or 1 */
 
/* day is the day in the month */
{
    
    double elev,ombrePath,azimuth;
    LinearInter sLinearOmbre;
    myspa_data localSpa;
    localSpa = spa;
	
	/* Ombre */
	sLinearOmbre.setPoints(shadowCombined);
	
	
	
	localSpa.hour  = hour;
	localSpa.month = month;
	localSpa.day   = day;
	localSpa.year  = year;
	
		int result = spa_calculate(&localSpa);
		azimuth = getCorrectAzimuth(localSpa);
		
		if (result==0) {
			if (shadowCombined.size()>0)
			/* We have a shadow profile */
			{
				
				elev      = 90 - localSpa.zenith;
				ombrePath = sLinearOmbre.value(azimuth);
  				#ifdef DEBUG
				qDebug()<<"Myplot getHourly radiation...shadowCombined"<<ombrePath<<elev;
  				#endif
				if (ombrePath>elev)	
					return 0; /* Total shadowing */
				else
					return 1; /* No shadowing at all */
			}
			else
			/* No shadow */
				return 1;
		}
		else
		{	
  			#ifdef DEBUG
			qDebug()<<"Myplot error in getHourly radiation...spa"<<result;
  			#endif
			return -1;
		}
}
double MyPlot::getDeclinationPrime(int month, int day, int hour)
/* day is the day in the month */
{ 	
        myspa_data localSpa;
    	localSpa = spa;
	localSpa.hour  = hour;
	localSpa.month = month;
	localSpa.day   = day;
	int result = spa_calculate(&localSpa);
	if (result==0) {
			return localSpa.delta_prime;
			#ifdef DEBUG
			qDebug()<<"Myplot getHourly declination...spa"<<localSpa.delta_prime;
			#endif
		}
		else {
			#ifdef DEBUG
			qDebug()<<"Myplot error in getHourly radiation...spa"<<result<<month<<day<<hour;
			return -1;
			#endif
		     }
	
}

double MyPlot::getCorrectAzimuth(myspa_data s)
{
	double shiftedAzimuth;
	int r;
	if (checkQuadrant(s )) {
				/* We are in the I and II quadrant mostly*/
					r = 1;
					
					/*shiftedAzimuth = (spa.azimuth>180) ? spa.azimuth-360 : spa.azimuth*/;
							
				}
				else
				{
					/* We are in the III and IV quadrant mostly*/
					r = 0;
					
// 					shiftedAzimuth = spa.azimuth180;
				}	
		if (reorder==0)
			shiftedAzimuth = s.azimuth180;
		if (reorder==1)
			shiftedAzimuth = (s.azimuth>180) ? spa.azimuth-360 : s.azimuth;
return shiftedAzimuth;

}
QPointF MyPlot::computeSingleValue(int time, int month, int day, int year)
/* return the azimuth and elevation of the sun in degree for a given hour*/
/* other parameters are set in spa */
{
        int result;

        myspa_data local;
	local = spa;
	local.hour = time;
	local.minute= 0;
	local.month= month;
	local.day=day;
	local.year = year;
	

        result = spa_calculate(&local);


 	#ifdef DEBUG
	qDebug()<<"MP single value result"<<local.zenith<<time<<result<<day<<year;
   	#endif
	
	return QPointF( getCorrectAzimuth(local),90-local.zenith);
}
QPointF MyPlot::computeSingleValue(int time, int month, int year)
/* return the azimuth and elevation of the sun in degree for a given hour*/
/* other parameters are set in spa */
{
        int result;
        double z = -1;
        myspa_data local;
        local = spa;
        local.hour = time;
        local.minute= 0;
        local.month= month;
        local.second = 0;
        local.year = year;
        local.temperature = temperatures.at(month-1);

        /* Find the day with lowest elevation*/

        local.day = 1;
        result    = spa_calculate(&local);
        z         = local.zenith;
        for(int i=2;i<=MyMath::monthEnd(month,year);i++){
        local.day=i;
        result = spa_calculate(&local);

        if ( local.zenith < z )
            break;
        else
            z = local.zenith;

        if (result>0){
            qDebug()<<"SOME ERROR IN SINGLEVALUE OF MYPLOT"<<result<<time;
            return QPointF(0,0);
        }
        }
        #ifdef DEBUG
        qDebug()<<"MP single value result"<<local.zenith<<time<<result<<day<<year;
        #endif

        return QPointF( getCorrectAzimuth(local),90-local.zenith);
}
double MyPlot::getHGlobalRatio(rbData p, double rd)
/* See Collareis Pereira or Edward Anderson "Fundamentals of Solar Energy Conversion */
{
        double a,b,omegas,v,ha,tempArg;

        myspa_data local;
        local             = spa;
        local.hour        = p.hour;
        local.minute      = 0;
        local.month       = p.date.month();
        local.day         = p.date.day();
        local.year        = p.date.year();
        local.slope       = p.slope;
        local.temperature = temperatures.at(p.date.month()-1);
	int result = spa_calculate(&local);
//    	omegas =  (acos(-tan((pi/180)*(local.latitude) )*tan(local.delta_prime*pi/180)));//in rad
//     	omegas = fabs(local.srha*pi/180);

	tempArg = tan(local.latitude*pi/180)*tan(local.delta_prime*pi/180);
	if (fabs(tempArg)>1)
		/* The sun never rise/set*/
		omegas = pi;
	else
        	omegas = acos(-tempArg);
	
	a = 0.4090 + 0.5016*sin(omegas-pi/3);
	b = 0.6609 - 0.4767*sin(omegas-pi/3);
         ha     = 15*(p.hour+0.30-12);//in degrees
// 	ha     = local.h_prime - 360;
// 	if ((hour<local.sunrise) || (hour>local.sunset))
// 				return 0;
        switch (p.model) {
		case 1:
		
			//Collares-Pereira
// 			omegas = acos(arg)*(180/pi);//in rad
			v =(a + b*cos(ha*pi/180))*rd;
     #ifdef DEBUG
			qDebug()<<"MP HGlobalRatio "<<v<<local.h_prime<<local.delta_prime<<rd<<a<<b<<omegas<<ha<<rd<<result;
     #endif 
			
			return v;
			break;
		case 2:
		/*Gueymard*/
		break;
                default:
                return 0;
                break;
	}
}
double MyPlot::getHDiffuseRatio(rbData p)
        //int hour, int month, int day, int year,double slope, int model)
/* See Liu and Jordan or Edward Anderson "Fundamentals of Solar Energy Conversion */
{
	double omegas,v,arg,ha,t,tempArg;
        myspa_data local;
        local            = spa;
        local.azm_rotation = -p.rotation;
        local.hour      = p.hour;
        local.minute    = 0;
        local.month     = p.date.month();
        local.day       =p.date.day();
        local.year       = p.date.year();
        local.slope      = p.slope;
        local.temperature = temperatures.at(p.date.month()-1);
        int result      = spa_calculate(&local);
  	arg = -tan((pi/180)*(local.latitude))*tan(local.delta_prime*pi/180);	
//       	omegas = fabs(local.srha*pi/180);
//   	omegas =  acos(arg);
        ha     = 15*(p.hour+0.30-12);//in degrees

//  	if ((hour<local.sunrise) || (hour>local.sunset))
//  	{
// 				qDebug()<<"MP HOUR OUT OF SUNRISE?SET"<<hour<<local.sunrise<<local.sunset;
//  				return 0;
// 	}
	tempArg = tan(local.latitude*pi/180)*tan(local.delta_prime*pi/180);
		if (fabs(tempArg)>1)
		/* The sun never rise/set*/
		omegas = pi;
		else
        	omegas = acos(-tempArg);	

        switch (p.model) {
		case 1:
		//Collares-Pereira

// 		if (ha>local.ssha || ha<local.srha)
// 		{
// 			return 0;
// 		}
// 		else
		 
// 			omegas = acos(arg)*(180/pi);//in rad
			
			t =(pi/24) * (( cos(ha*pi/180) - cos(omegas))/(sin(omegas) -omegas*cos(omegas) ) );
 			v = t >0 ? t : 0;
       #ifdef DEBUG
                        qDebug()<<"MP HdiffuseRatio "<<v<<t<<local.srha<<omegas<<p.slope<<arg<<local.latitude<<ha<<local.delta_prime<<result;
       #endif
			
			return v;
		 
		break;
	}
        return 1; //default
}
//double MyPlot::getSingleRb(int hour,int month,int day,int year,double slope_,double rotation)
double MyPlot::getSingleRb(rbData p)
/* trigonometric values in degrees */
{
    double slope;


        if (p.slope<0.000000000000002)
		return 1;/* surface horizontal*/

	double a,e,d,in,Rb,s;
        myspa_data local;
	local = spa;
        local.azm_rotation = -p.rotation;
        local.hour         = p.hour;
        local.minute       = 0;
        local.month        = p.date.month();
        local.day          = p.date.day();
        local.year         = p.date.year();
        local.temperature = temperatures.at(p.date.month()-1);
        int result         = spa_calculate(&local);
        a                  = getCorrectAzimuth(local);
        e                  = local.zenith;
        //For northern emisphere
        slope              = local.latitude>=0 ? p.slope : -p.slope;


        d = getDeclinationPrime(p.date.month(), p.date.day(), p.hour);
        in=(cos(e*pi/180) * cos(slope*pi/180) + sin(slope*pi/180)*sin(e*pi/180)*cos((a-p.rotation)*pi/180));//is a cosine
	s = cos(e*pi/180);/*cos of elevation*/
	Rb = in/s;
// 	qDebug()<<"MP single Rb first"<<Rb;
	if (s<=0.1)
		Rb = 0;//values behind the surface or behind the horizon.
	Rb = MyMath::max(0,Rb);
       #ifdef DEBUG
        qDebug()<<"MP single Rb"<<p.hour<<p.date.month()<<p.date.day()<<in<<s<<slope<<e<<a<<p.rotation<<Rb;
         #endif
	return Rb;
	 
}
double MyPlot::getSingleInc(int hour,int month,int day,int year,double slope,double rotation)
/* trigonometric values in degrees */
{
	double a,e,d,in;
        myspa_data local;
	local = spa;
	local.hour = hour;
	local.minute= 0;
	local.month= month;
	local.day=day;
	local.year = year;
        local.temperature = temperatures.at(month-1);
        int result = spa_calculate(&local);
	a = getCorrectAzimuth(local);
	e =  local.zenith;
	d = getDeclinationPrime(month, day, hour);
	in=(cos(e*pi/180) * cos(slope*pi/180) + sin(slope*pi/180)*sin(e*pi/180)*cos((a-rotation)*pi/180));//is a cosine
	if (e-90>0.0000002) 
		in =0;
	
 #ifdef DEBUG
	qDebug()<<"MP single inc"<<in<<slope<<e<<a<<rotation;
 #endif
	return in;
	 
}
void MyPlot::setProjectDir(const QString &a)
{
        projectDir = a;
}
bool MyPlot::isTwoSide()
{
    if (addInclAzi.size()>0)
            return true;
    else
        return false;

}
void MyPlot::setAziIncl2(double x_azi,double y_incl)
{
        addInclAzi.resize(0);

        addInclAzi<<x_azi<<y_incl;
}
void MyPlot::setMonthlyTemp(const QVector<double> &a)
{
    temperatures = a;
}
