
//  #define DEBUG
#include "assert.h"
#include "radiazioneReale.h"
#include "settings.h"
#include "generalValues.h";
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
#include <qwt_symbol.h>
#include <qwt_legend.h>
// #include <qwt_data.h>
#include <qwt_text.h>
#include <QtGui>
#include <QSvgGenerator>
#include <qwt_picker.h>
#include <qwt_plot_picker.h>
#define sign MyMath::sign
#include "lmmin.h"
#include "lm_eval.h"

#define Go 1367
#define correction 1367/1353
#define pi        3.1415926535897932384626433832795028841971

// class MonthScaleDraw: public QwtScaleDraw
// {
// public:
//       MonthScaleDraw(int month);
// 	{
// 	}
//       virtual QwtText label(double v) const
// 	{
// 	 
// 	}
// };

RadiazioneReale::RadiazioneReale(QWidget*parent ): QwtPlot(parent)
{
	meanLossFactor =0;
	whichGraph = 1;
	additionalOmbreFactor.clear();
	additionalIncl.resize(0);
	additionalAzi.resize(0);;
	inclOptiPresent  = false;
	year = 2009;
	this->setWindowIcon(QIcon(":/images/app.png"));
	setWindowTitle("SolarCalc - Radiazione reale");
	model =1;
	R<<0.25;
	resetOmbre();
	
	
        u<<tr("[MJ/m2]")<<tr("[kWh/m2]");
	QwtPainter::setDeviceClipping(false);
	
 

	QPen p;
	p.setWidth(10);
	p.setColor(Qt::blue);

 


        QwtSymbol sym;
        sym.setStyle(QwtSymbol::XCross);
        sym.setPen(QColor(Qt::blue));
        sym.setSize(10);

	QwtSymbol sym2;
	sym2.setStyle(QwtSymbol::Ellipse);
	sym2.setPen(QColor(Qt::blue));
	sym2.setSize(10);

	QwtSymbol sym3;
	sym3.setStyle(QwtSymbol::Triangle);
	sym3.setPen(QColor(Qt::blue));
	sym3.setSize(10);
	
	for(int i=0;i<12;i++){
		monthMarker[i]= new QwtPlotMarker();
		monthMarker[i]->attach(this);

		/*Init Hincl, HinclOmbre */
		Hincl[i] = 0;
		HinclOmbre[i] = 0;
		Hincl2[i] = 0;
		HinclOmbre2[i] = 0;
	}
	lossMarker = new QwtPlotMarker();
	lossMarker->attach(this);


	QPen pen;
	pen.setColor(Qt::black);
	pen.setWidth(1);

	fittedDailyValue = new QwtPlotCurve(tr("Rad. su superficie orizzontale"));
	fittedDailyValue->setCurveAttribute(QwtPlotCurve::Fitted,true);
	fittedDailyValue->attach(this);
	QPen redPen;
	redPen.setWidth(1);
	redPen.setColor(Qt::red);
        fittedDailyValue->setPen(redPen);
	fittedDailyValue->setYAxis(QwtPlot::yLeft);

	plotReale = new QwtPlotCurve(tr("Radiazione incidente mensile"));
	plotReale->attach(this);
        plotReale->setSymbol(sym);
	plotReale->setStyle(QwtPlotCurve::Sticks);
	plotReale->setBaseline(0);
	plotReale->setPen(pen);
// 	plotReale->setBrush(QBrush(Qt::Dense7Pattern));
  	setAxisScale(QwtPlot::xBottom,1,365);

	plotRealeNoShadow = new QwtPlotCurve(tr("Radiazione incidente senza ombre"));
	plotRealeNoShadow->attach(this);
        plotRealeNoShadow->setSymbol(sym2);
	plotRealeNoShadow->setStyle(QwtPlotCurve::Sticks);
	plotRealeNoShadow->setBaseline(0);
	plotRealeNoShadow->setPen(pen);

	plotRealeRef = new QwtPlotCurve(tr("Radiazione incidente, tilt ottimo,  SUD"));
	plotRealeRef->attach(this);
        plotRealeRef->setSymbol(sym3);
	plotRealeRef->setStyle(QwtPlotCurve::Sticks);
	plotRealeRef->setBaseline(0);
	plotRealeRef->setPen(pen);

	

	

// 	realeMarker = new QwtPlotMarker();

        

	
	 

	dDailyValues = new QwtPlotCurve("");
// 	dDailyValues->setCurveAttribute(QwtPlotCurve::Fitted,true);
	dDailyValues->attach(this);
        dDailyValues->setPen(pen);
  	dDailyValues->setStyle(QwtPlotCurve::Dots);
	dDailyValues->setYAxis(QwtPlot::yLeft);
// 	dDailyValues->setSymbol(sym2);
	dDailyValues->setItemAttribute(QwtPlotItem::Legend, false);

	QwtLegend* legend = new QwtLegend(this);
        legend->remove(dDailyValues);
	insertLegend(legend,QwtPlot::BottomLegend);

	setMargin(2);
   	picker = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft,       QwtPicker::PointSelection , QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn,this->canvas());
	picker->setRubberBandPen(QColor(Qt::black));
    	picker->setRubberBand(QwtPicker::CrossRubberBand);
	picker->setEnabled(true);
	picker->setTrackerPen(QColor(Qt::black));

	
	 

// #ifdef Q_WS_X11
//     /*
//        Qt::WA_PaintOnScreen is only supported for X11, but leads
//        to substantial bugs with Qt 4.2.x/Windows
//      */
//     canvas()->setAttribute(Qt::WA_PaintOnScreen, true);
// 	#endif
	
	 
        enableAxis(QwtPlot::yLeft,true);
//   	enableAxis(QwtPlot::yRight,true);
	

	setCanvasBackground(QColor(Qt::white));

	// Set default settings
	set = new Settings();
	set->setTitle(tr("Radiazione solare reale"));
	set->setUnit(1);//MJ/m2
	currentUnit = 1;
	set->setAxisY(tr("Media mensile giornaliera"));
	set->setAxisYRight(tr("Media giornaliera"));
	set->setAxisX(tr("Giorno"));
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
	 setTitle(tlabel);
	setAxisTitle(QwtPlot::xBottom,xlabel);
        setAxisTitle(QwtPlot::yLeft,ylabel );
	setAxisTitle(QwtPlot::yRight,set->getAxisYRight() + " " + u.at(set->getUnit()-1));
// 	setAxisScale(QwtPlot::xBottom,1,12);
	
	this->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this,SIGNAL(customContextMenuRequested(const QPoint &  )),this,SLOT(popUpMenu(const QPoint &)));

	alignScales();
	createActions();

	 HgIsPresent = false;
	 fittingDone = false;
	for(int i=0;i<366;i++) 
		days[i] =i;

	dailyValueDirty = true;

	//Other ini
	 recentExportPath =  QDir::homePath();
	recentDir = QDir::homePath();
	mainPlot = false;
	lat=0;
	azi=0;
replot();
}
void RadiazioneReale::checkMarkers()
{
    qDebug()<<"CHECK MARKERS"<<aw_toggle_marker->isChecked();
    if (aw_toggle_marker!=0){
            if (!aw_toggle_marker->isChecked())
                    drawMarkers(true);
            else
                    drawMarkers(false);
}
    replot();
}
void RadiazioneReale::updateSet()
{
	QString str;
	int chosenUnit = set->getUnit();
	str = u.at(chosenUnit-1);
 	#ifdef DEBUG
 	qDebug()<<"update Set"<<set->getTitle();	
 	#endif
	setTitle(set->getTitle());
	 setAxisTitle(QwtPlot::yLeft,set->getAxisY() + " " + str);
	 setAxisTitle(QwtPlot::yRight,set->getAxisYRight() + " " + str);
	setAxisTitle(QwtPlot::xBottom,set->getAxisX());
       if (currentUnit!=chosenUnit) {
		currentUnit = chosenUnit;
// 		qDebug()<<"RR start conversion"<<currentUnit;
		
		convertRaw(chosenUnit);
		convertFit(chosenUnit);
// 		covnertRefCurve(choseUnit);
// 		convertDailyFit(chosenUnit);
		
// 		drawDailyContents(1);
		drawContents(1,whichGraph);
		if (showRefCurve)
			drawRefCurve(1);
		else
			drawRefCurve(0);

                checkMarkers();


//   		drawDailyValue(1);
		
                emit unitChanged(currentUnit);
}
	 
   }
double RadiazioneReale::convert(int unit,double value)
{double k;
	if (unit==1)
		// convert from kWh to MJ 
		k = 3.6;
	if (unit==2)
		// convert from MJ to kWh
		k=1/3.6;
//  	 qDebug()<<"convert"<<value<<value*k;
	return value*k;
}

void RadiazioneReale::convertRaw(int unit)
{
	

 
		for(int i=0;i<12;i++) 
			{
                          HinclView[i] = convert(unit,HinclView[i]);
                          HinclOmbreView[i]= convert(unit,HinclOmbreView[i]);
				
				if ( (additionalIncl.size()>0) && (incl.size()!=0) ){
                                          Hincl2View[i] = convert(unit,Hincl2View[i]);
                                         HinclOmbre2View[i]= convert(unit,HinclOmbre2View[i]);
				}
			  Href[i] = convert(unit,Href[i]);
// 			  Hg[i]    = convert(unit,Hg[i]);
// 			  Hho[i]   = convert(unit,Hho[i]);
			  
			}
// 	qDebug()<<"RR Raw converterd"<<unit;
}

int RadiazioneReale::getUnit()
{
// 	qDebug()<<"RR current Unit"<<currentUnit;
        return currentUnit;
}
void RadiazioneReale::setDailyIncl(QPolygonF a)
{
	/* We suppose that values of a are QPoint(month,Inclination value in rad.) */
	

	switch (a.size()) {
		case 1:
			dailyIncl = a;
		break;
		case 366:
			dailyIncl = a;
		break;
		case 365:
			dailyIncl = a;
		break;
		default:
			dailyIncl = QPolygonF()<<QPointF(0,0);
		break;
	}
//  qDebug()<<"RadiazioneReale setIncl daily"<<dailyIncl<<a.size();
}
void RadiazioneReale::setIncl(QPolygonF a)
{
	/* We suppose that values of a are QPoint(month,Inclination value in rad.) */
	

	switch (a.size()) {
		case 1:
			incl = a;
		break;
		case 12:
			incl = a;
		break;
		default:
			incl = QPolygonF()<<QPointF(0,0);
		break;
	}
//     	qDebug()<<"RadiazioneReale setIncl"<<incl<<a.size();
}
void RadiazioneReale::setR( const QVector<double> &a)
{
	R.resize(0);
	
       	#ifdef DEBUG
 	qDebug()<<"R="<<R<<a;
       	#endif
   	R = a;
        //qDebug()<<"R="<<R;
}
void RadiazioneReale::setRb(double a[12])
{
	 for (int i=0;i<12; i++){
			Rb[i] = a[i];
	}
}

void RadiazioneReale::setOmegas(double o[12])
{
	 for (int i=0;i<12; i++)
		omegas[i] = o[i]; 
}
void RadiazioneReale::setHg(double Hg_[12])
//In MJ
{
	 for (int i=0;i<12; i++)
		Hg[i] = Hg_[i];
HgIsPresent = true;
}

// void RadiazioneReale::setAll(double Rb_[12], double Hho_[12])
// /* Default unit is Mj */
// {
// 	 for (int i=0;i<12; i++){
// 	 Rb[i] = Rb_[i];
// // 	 Hg[i] = Hg_[i];
// 	 Hho[i] = Hho_[i];
//  	 
// 	}
//  
// 	 
// }
//  double* RadiazioneReale::compute_(double rb[12],double tilt, int select)
// {
// 	/* WARNING omegas MUST BE SET */
// 	/* Output here is in MJ */
//         double Hd_[12],Kt_[12],K_[12],Hb_[12],omegasLimit;
// 	for (int i=0;i<12;i++) {
// 	
//                 Kt_[i] = correction*Hg[i]/hho[i];
// 		K_[i] = diffuseIndex(model,omegas[i],Kt_[i]);
// 		
// 
//                 Hd_[i] = K_[i] * Hg[i];
//                 Hb_[i] = Hg[i] - Hd_[i];
//                 Hincl_[i] = rb[i]*Hb_[i] + Hd_[i]*(1+cos(tilt))/2 + Hg[i]*R*(1-cos(tilt))/2;
//                 HinclOmbre_[i] = rb[i]*Hb_[i]*ombreFactor[i]  + Hd_[i]*(1+cos(tilt))/2 + Hg[i]*R*(1-cos(tilt))/2;
//       #ifdef DEBUG
//   	qDebug()<<"RadiazioneReale: compute_ reale.."<<rb[i]<<Hho[i]<<Hg[i]<<Hb[i]<<"local var."<<Kt_[i]<<K_[i]<<Hd_[i]<<Hb_[i]<<Hincl_[i]<<tilt;
//  	
//      #endif
// }
// 	switch (select) {
// 		case 0:
// 		return Hincl_;
// 		break;
// 		case 1:
// 		return HinclOmbre_;
// 		break;
// 	}
// 
// }

double RadiazioneReale::compute_(double rb,double hho,double hg,int month,double tilt,int select)
{

 	/* WARNING omegas MUST BE SET */
	/* Output here is in MJ */
        double Hd_,Kt_,K_,Hb_, Hincl_,HinclOmbre_,R_;
	if  (month<0 || (month>11) ) 
			return 0;
	
	if ((R.size() == 1) || R.size()<11 ){
			if (R.isEmpty())
				R_ = 0;
			else
				R_ = R.at(0);
		}
		else
			R_ = R.at(month);

                if (source==radEnea)
                Kt_ = hho<0.0000002 ? 0 :correction*hg/hho;//ENEA
		else
                Kt_ = hho<0.0000002 ? 0 :correction*hg/hho;

		K_ = diffuseIndex(model,omegas[month],Kt_);
                Hd_ = K_ * hg;
                Hb_ = hg - Hd_;
                Hincl_ = rb*Hb_ + Hd_*(1+cos(tilt))/2 + hg*R_*(1-cos(tilt))/2;
                HinclOmbre_ = rb*Hb_*ombreFactor[month]  + Hd_*(1+cos(tilt))/2 + hg*R_*(1-cos(tilt))/2;
             //    qDebug()<<"compute_ single value"<<model<<Hho[month]<<hg<<Kt_<<K_<<Hd_<<Hb_<<Hincl_<<HinclOmbre_<<R<<rb<<ombreFactor[month]<<tilt;
	
	switch (select) {
		case 0:
		return Hincl_;
		break;
		case 1:
		return HinclOmbre_;
		break;
	}

 }
double RadiazioneReale::diffuseIndex(int m,double omegas,double kt)
{
/* WARNIGN omegas MUST BE SET */
/*omegs is considered to be in rad */

        double omegasLimit = 81.4*pi/180;//rad
        double k;
		if (m==1) 
		/* UNI 8477 */
			k = 0.881 - 0.972*kt;
		if  (m==2)
		/*ENEA*/
				k  = 1- 1.165*(0.0695 + 0.8114*kt);
		if (m==3) {
		/*Erbs*/
			if (omegas<omegasLimit){
				if (kt<0.715)
				 k = 1 -0.2727*kt + 2.4495*kt*kt -11.9514*pow(kt,3)+9.3879*pow(kt,4);
				else
				k=0.143;
			}
			else
				if (kt<0.715)
				k = 1 +0.2832*kt - 2.5557*kt*kt+0.8448*pow(kt,3);
				else
				k=0.175;
		}

	return k;	
}
// void RadiazioneReale::computeDaily()
// {
// 	double tempIncl,hd,hb,kt,k,unit,g,R_;
// 	const double* hg;
// 	int yearDays = MyMath::yearEnd(year);
// 	/* WARNING omegas MUST BE SET */
// 	if (dailyOmegas.size()==0) {
// 	qDebug()<<"RR Error in computeDaily, no omegas set";
// 	return;
// 	}
// 	if ((R.size() == 1) || R.size()<11 ){
// 			if (R.isEmpty())
// 				R_ = 0;
// 			else
// 				R_ = R.at(0);
// 		}
// 		else
// 			R_ = R.at(month);
// 
// 	if ( (fittingDone) && (dailyHho.size()== yearDays) && (dailyRb.size() ==yearDays)  &&     dailyOmbreFactor.size()>0) 
// 	{	
// 		dailyHincl.resize(0);
//  		dailyHinclOmbre.resize(0);
// /* Default MJ*/
// 		hg  = getFittedValues();
// // 		if (currentUnit == 2)
// // 		unit = 3.6;
// // 		else
// // 		unit =1;
// 
// 		for (int i=0;i<yearDays;i++) {
// 
// 			g = hg[i];
// 			if (dailyIncl.size()==1)
// 			/* Tilt fixed */
// 			tempIncl = dailyIncl.at(0).y();
// 
// 			if ((dailyIncl.size()==365) || (dailyIncl.size()==366))
// 			/* Tilt variable */
// 			tempIncl = dailyIncl.at(i).y();
// 
// 			
// 			
// 			 kt = g/dailyHho.at(i).y();
// 			 
// 			 k = diffuseIndex(model,dailyOmegas.at(i).y() ,kt);
// 
// 			hd = k * g;
// 			hb = g - hd;
// 	
// 			dailyHincl << QPointF(i, (dailyRb.at(i).y() *hb  + hd*(1+cos(tempIncl))/2 + g*R_*(1-cos(tempIncl))/2));
// 
// 			dailyHinclOmbre << QPointF(i, (dailyRb.at(i).y() *hb*dailyOmbreFactor.at(i).y() + hd*(1+cos(tempIncl))/2 + g*R_*(1-cos(tempIncl))/2));
// 			#ifdef DEBUG
//   			qDebug()<<"RR computeDaily "<<i<< tempIncl<<dailyHincl.at(i).y()<<dailyRb.at(i).y()<<dailyHho.at(i).y()<<dailyOmbreFactor.at(i).y();
// 			#endif
// 		}
// 	dailyValueDirty = false;
// // 	if (currentUnit ==2)
// // 	convertDailyFit(2);
// 	}
// 
// //   qDebug()<<"RR computeDaily out"<<dailyHincl.at(150).y()<<dailyHinclOmbre.at(150).y();
// 
// }
 
void RadiazioneReale::setOmbreFactorDaily(const QPolygonF &input)
{
	dailyOmbreFactor.resize(0);
	dailyOmbreFactor = input;
// 	qDebug()<<"RR setOmbreFactorDaily"<<input.size()<<input.at(150).y();
}
void RadiazioneReale::setHhoDaily(const QPolygonF &input)
{
	dailyHho.resize(0);
	dailyHho = input;
       //qDebug()<<"RR setHhoDaily"<<dailyHho.size();
	
}
void RadiazioneReale::setRbDaily(const QPolygonF &input)
{
	dailyRb.resize(0);
	dailyRb = input;
     //   qDebug()<<"RR dailyRbsize"<<dailyRb.size();
}
 
void RadiazioneReale::setOmegasDaily(const QPolygonF &input)
{
	
	dailyOmegas.resize(0);
	dailyOmegas = input;
}

void RadiazioneReale::compute()
{
	inclOptiPresent  = false;//We have to call optimize() to set a new Optimum tilt
	/* DEFAULT unit is MJ */
	double tempIncl,s,delta,Htot,R_;
	double Hd2,Hb2,K2,omegas_;
	QVector<double> res;
        meanLossFactor=0;
	Htot=0;
	delta=0;
	s=0;
	totalLossFactor=0;
	mLF.resize(0);
	for (int i=0;i<12;i++) {
	
		if ((R.size() == 1) || R.size()<11 ){
			if (R.isEmpty())
				R_ = 0;
			else
				R_ = R.at(0);
// 			qDebug()<<"RR single albedo"<<R;
		}
		else
			{
// 			qDebug()<<"RR multi albedo"<<R;
			R_ = R.at(i);
			}
		

		if (incl.size()==1)
			/* Tilt fixed */
			tempIncl = incl.at(0).y();
		if (incl.size()==12)
			tempIncl = incl.at(i).y();

		res   = MyMath::rb(lat*pi/180,tempIncl,azi*pi/180,i,2009,0);//use ref days

//                 if (incl.size()==12)
//                		 qDebug()<<"RR COMPUTE REALE RES"<<res;

		if (incl.size()==12)
			Rb[i] =  res.at(2);
		else
			Rb[i] =  res.at(0);

		omegas_ = res.at(6);
		omegas[i]=omegas_;
		Hho[i] = res.at(1);
                if (source==radEnea)
		Kt[i] = Hho[i]<0.0000000000002 ? 0 : correction*Hg[i]/Hho[i];//ENEA
		else
		Kt[i] = Hho[i]<0.0000000000002 ? 0 : Hg[i]/Hho[i];

		K[i]  = diffuseIndex(model,omegas_,Kt[i]);

		Hd[i] = K[i] * Hg[i];
		Hb[i] = Hg[i] - Hd[i];

		Hincl[i] = Rb[i]*Hb[i]  + Hd[i]*(1+cos(tempIncl))/2 + Hg[i]*R_*(1-cos(tempIncl))/2;
		HinclOmbre[i] = Rb[i]*Hb[i]*ombreFactor[i] + Hd[i]*(1+cos(tempIncl))/2 + Hg[i]*R_*(1-cos(tempIncl))/2;
	
                HinclOmbreView[i] = HinclOmbre[i];
                HinclView[i] = Hincl[i];

		/*Double field*/
		if ( (additionalIncl.size()>0) && (incl.size()!=0) )	{
			QVector<double> res2;
			for(int k=0;k<additionalIncl.size();k++){
				res2   = MyMath::rb(lat*pi/180,additionalIncl.at(k)*pi/180,additionalAzi.at(k)*pi/180,i,2009,0);//use ref days
				omegas_ = res2.at(6);
				K2  = diffuseIndex(model,omegas_,Kt[i]);
				Hd2 = K2 * Hg[i];
				Hb2 = Hg[i] - Hd2;
				Hincl2[i]      = res2.at(0)*Hb2  + Hd2*(1+cos(additionalIncl.at(k)*pi/180))/2 + Hg[i]*R_*(1-cos(additionalIncl.at(k)))/2;
		
				HinclOmbre2[i] = res2.at(0)*Hb2*additionalOmbreFactor.at(k)[i] + Hd2*(1+cos(additionalIncl.at(k)*pi/180))/2 + Hg[i]*R_*(1-cos(additionalIncl.at(k)*pi/180))/2;

                                Hincl2View[i] = Hincl2[i];
                                HinclOmbre2View[i] = HinclOmbre2[i];
				  #ifdef DEBUG
				qDebug()<<"RR additional facade"<<HinclOmbre2[i]<<additionalAzi.at(k)<<additionalIncl.at(k)<<additionalOmbreFactor.at(k)[i]<<Hd2<<Hb2<<K2<<omegas_;
				#endif
			}
		}

// 		meanLossFactor += (Hincl[i]-HinclOmbre[i])/12;
		Htot+=Hincl[i];
		delta = (Hincl[i]-HinclOmbre[i])<=0.0000000002 ? 0 : (Hincl[i]-HinclOmbre[i]);
		s     = Hincl[i]<0.000000000002 ? 1 : 1 - delta/Hincl[i];
 		meanLossFactor +=  s/12;
		mLF<< s;
 		totalLossFactor += delta;
                   if (meanLossFactor<0.000002)
                    meanLossFactor=0;	
                if (totalLossFactor<0.00002)
                    totalLossFactor=0;
                     #ifdef DEBUG
         qDebug()<<"RR compute reale..mode:"<<ombreFactor[i]<<model<<Hho[i]<<Hg[i]<<Kt[i]<<K[i]<<Hd[i]<<Hb[i]<<Hincl[i]<<HinclOmbre[i]<<R<<Rb[i]<<ombreFactor[i]<<tempIncl<<omegas[i];
 	
  	qDebug()<<meanLossFactor<<totalLossFactor<<mLF<<s;

                 #endif
// 	qDebug()<<incl.size()<<incl<<tempIncl<<Hincl[i]<<HinclOmbre[i]<<R<<Rb[i];
	}
// 	qDebug()<<"RR Totale Hinck"<<MyMath::cumSumMonthly(Hincl,12);
// 	qDebug()<<"RR Totale Hinck"<<MyMath::cumSumMonthly(HinclOmbre,12)<<Rb[0];
// 	meanLossFactor  = meanLossFactor; //This is the monthly mean of losses factordue to shadows
	totalLossFactor = (Htot<=0.00000002) ? 0 :totalLossFactor/Htot; //This is the yearly mean of losses due to shadows 
	if (currentUnit==2) {
// 		qDebug()<<" convertRaw from compute";
		convertRaw(2);
		
		
	}
emit computeDone();
// 	computeRealEnergy();
dailyValueDirty = true;
}
// void RadiazioneReale::addIncl(const QVector<double> &a)
// {
// 	/*In degree*/
// 	additionalIncl = a;
// }
// void RadiazioneReale::addAzi(const QVector<double> &a)
// {
// 	/*In degree*/
// 	additionalAzi = a;
// }
void RadiazioneReale::drawDailyContents( int mode)
{
	if ((HgIsPresent) && (dailyHincl.size()>0))  {
	#if QT_VERSION >= 0x040000
	dDailyValues->setRenderHint(QwtPlotItem::RenderAntialiased);
	#endif
	switch (mode) {
	case 0:
		dDailyValues->setRawData(0,0,0);
		resetTitle();
	break;	
	case 1:
		dDailyValues->setData(dailyHincl);
//   		qDebug()<<"RR dailyContents senza Ombre"<<dailyHincl.at(150).y();
	break;;
	
	case 2:
		 dDailyValues->setData(dailyHinclOmbre);
//   		 qDebug()<<"RR dailyContents Ombre"<<dailyHinclOmbre.at(150).y()<<dailyHincl.at(150).y();
	break;
			
			
		
                //plotDot->setRawData(0,0,0);
		}
	}
// for(int i=0;i<365;i++)
//  qDebug()<<"Radiazione reale giornaliera "<<dailyHincl.at(i).y();
replot();
}
// void RadiazioneReale::drawDailyValue(int i)
// // Plot the fitted values for the horizontal plane
// {
// if (i == 1) {
// 
// 	if (fittingDone)
// 	{	 
// 		
//  		
// 		
// 		fittedDailyValue->setRawData(days,dailyHg,MyMath::yearEnd(year));
// 		#if QT_VERSION >= 0x040000
// 		fittedDailyValue->setRenderHint(QwtPlotItem::RenderAntialiased);
// 		#endif
// 	#ifdef DEBUG
// 	 
// 	#endif
// 		
// 	}
// }
//  
// else{
// 	fittedDailyValue->setRawData(0,0,0);
// 	resetTitle();
// 	}
// replot();
// }
void RadiazioneReale::drawMarkers(bool doit)
{
// 	double max= MyMath::max(dailyHg,366) ;
	double max = axisScaleDiv(yLeft)->upperBound();
	double s   = max/20;
	QwtText label;
	for(int i=0;i<12;i++) {
		if (doit){
			monthMarker[i]->setValue(normDays[i],max-s);
			label.setText(QString::number(MyMath::refMonthDay(i)) +" "+ MyMath::months(i+1));
			label.setFont(QFont("Helvetica [Cronyx]", 10));
			monthMarker[i]->setLabel(label);
//    		qDebug()<<"RR: drawMarkers-----"<<max-s<<normDays[i]<<doit;
		}
		else{
			label.setText("");
			monthMarker[i]->setLabel(label);
			monthMarker[i]->setValue(0,0);
		 }
		
		
	}
		lossMarker->setValue(normDays[1],8*max/10);
		
		if (doit){
		
                label.setText("<p>" + tr("Perdita ombregg. </p><p>media mensile = ")
                              + "" +QString::number((1-meanLossFactor)*100,'f',2)
                              + "%" +"</p>",QwtText::RichText);
                label.setFont(QFont("Helvetica [Cronyx]", 10));


		}
		else
			label.setText("");

		lossMarker->setLabel(label);
	

	 
}
void RadiazioneReale::drawRefCurve(int mode)
{
  qDebug()<<"DRAW REF CURVE";
	
	if (mode==1)
	{
		if (!inclOptiPresent)

                        optimize(1 );

// 		computeRefCurve(1);//Href ready
		plotRealeRef->setData(normDays,Href,12);
	}
	if (mode==0)
		plotRealeRef->setRawData(0,0,0);
	
        checkMarkers();
	
replot();

}
void RadiazioneReale::drawContents( int mode,int whichone)
{
	//We must convert unit of fit because it is not automatic for horizontal fit!
	// This step is necessary here because otherwise the plot change 2 times!
//   	qDebug()<<"Radiazione reale mode"<<mode<<whichone<<dm;
	whichGraph = whichone;
//  	double m[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
	setTitle(set->getTitle());
	if (HgIsPresent) {
		#if QT_VERSION >= 0x040000
		plotReale->setRenderHint(QwtPlotItem::RenderAntialiased);
		#endif
		switch (mode) {
		
		case 1:
			if (whichone==2)
                        plotReale->setData(normDays,HinclOmbre2View,12);
			else
                        plotReale->setData(normDays,HinclOmbreView,12);

			plotRealeNoShadow->setRawData(0,0,0);
			mainPlot = true;
// 			qDebug()<<"Radiazione reale mode"<<mode<<whichone;
		break;
		case 2:
			if (whichone==2){
                        plotReale->setData(normDays,HinclOmbre2View,12);
                        plotRealeNoShadow->setData(normDays,Hincl2View,12);
		}
		else{
                        plotReale->setData(normDays,HinclOmbreView,12);
                        plotRealeNoShadow->setData(normDays,HinclView,12);
		}
// 		qDebug()<<"Radiazione reale mode"<<mode<<whichone;
		mainPlot = true;
		break;
		
		case 0:
		plotReale->setRawData(0,0,0);	
		plotRealeNoShadow->setRawData(0,0,0);
		mainPlot = false;
		
		resetTitle();	
		break;
		}
		
	}
replot();
if (mode ==1 || mode == 2) {
 // qDebug()<<"RR drawContents fittingDone"<<fittingDone<<aw_toggle_marker->isChecked();
			if (fittingDone)
			{	 
				fittedDailyValue->setRawData(days,fittedHg,MyMath::yearEnd(year));
				#if QT_VERSION >= 0x040000
				fittedDailyValue->setRenderHint(QwtPlotItem::RenderAntialiased);
				#endif
			}
			if (!aw_toggle_marker->isChecked()) {
				drawMarkers(true);
				 }
 			else{
				drawMarkers(false);
				 }
 		}
	 
	else{
		fittedDailyValue->setRawData(0,0,0);
		drawMarkers(false);
	}
replot();





}

void RadiazioneReale::setModel(int i)
{
	if (model>0 & model<=3)
	model = i;
	else
	model = 1; //defaul = UNI

}
double *RadiazioneReale::getHincl(int whichone)
{
    /* for simplicity return always in mj */
// 	 for (int i=0;i<12; i++)
        double *start;
	switch (whichone){
	case 2:
		if ( (additionalIncl.size()>0) && (incl.size()!=0) )	
		start = Hincl2;
		else
		start = Hincl;
	break;
	default:
		start = Hincl;
	break;
	}

	return start;
}
double *RadiazioneReale::getHref()
{
    /* for simplicity return always in mj */
// 	 for (int i=0;i<12; i++)
        
	double *start = Href;
	return start;
}
double *RadiazioneReale::getHinclOmbre(int whichone)
{
	double *start;
	switch (whichone){
	case 2:
		if ( (additionalIncl.size()>0) && (incl.size()!=0) )	
		start = HinclOmbre2;
		else
		start = HinclOmbre;
	break;
	default:
		start = HinclOmbre;
	break;
	}
	return start;
}
void RadiazioneReale::exportTXT()
{
	QString fileName;
 

    fileName = QFileDialog::getSaveFileName(this, tr("Nome file da esportare"),  recentDir,"Text files ( *txt)");

    if ( !fileName.isEmpty() )
    {
	fileName = MyMath::checkFormat(fileName,"txt");
	if (!MyMath::exportToText(fileName,Energy,12));
		QMessageBox::warning(this,tr("Esportazione data"),tr("Qualche errore di scrittura sul file/cartella selezionata. Prova a ripetere o a cambiare cartella/nome file"),QMessageBox::Ok);
	recentDir = QFileInfo(fileName).absoluteDir().absolutePath();
    }
	
}

void RadiazioneReale::exportPNG()
{	QString fileName;
 	 
        fileName = QFileDialog::getSaveFileName(this, tr("Nome file da esportare"),  recentExportPath,"Graphic files (*.png  )");
	QFileInfo fileInfo(fileName);
	recentExportPath = fileInfo.absoluteDir().absolutePath();

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
	QPixmap pixmap(800,600);
	pixmap.fill(Qt::white);
      	
        print(pixmap,filter );
    
    if ( pixmap.save(fileName, "png" ))
 		qDebug()<<"Ok";
    else
 		qDebug()<<"Error";
 	}
}
 void RadiazioneReale::createActions()
{
	a_print =  new QAction(tr("&Stampa"),this);
	a_export = new QAction(tr("&Esporta"),this);
	 
	a_proprieta = new QAction(tr("Impostazioni"),this);
	a_exportPNG   = new QAction(tr("PNG"),this);
	
	a_exportPDF = new QAction(tr("PDF"),this);
	a_exportPDF->setIcon(QIcon(":/images/pdf.jpeg"));

	a_export_txt = new QAction(tr("File di testo"),this);	

	aw_toggle_marker = new QAction(tr("Rimuovi etichette"),this);
	aw_toggle_marker->setCheckable(true);
 
	connect(a_print,SIGNAL(triggered()),this,SLOT(printOut()));
	connect(a_export,SIGNAL(triggered()),this,SLOT(exportSVG()));
	connect(a_proprieta,SIGNAL(triggered()),this,SLOT(settings()));
	connect(a_exportPNG,SIGNAL(triggered()),this,SLOT(exportPNG()));
	connect(a_exportPDF,SIGNAL(triggered()),this,SLOT(exportPDF()));
	connect(a_export_txt,SIGNAL(triggered()),this,SLOT(exportTXT()));
	connect(aw_toggle_marker,SIGNAL(triggered()),SLOT(redraw()));
}
void RadiazioneReale::redraw()
{
// 	qDebug()<<"RR redraw marker"<<aw_toggle_marker->isChecked();
	if (aw_toggle_marker->isChecked())
			drawMarkers(false);
	else
			drawMarkers(true);
replot();
	
}

void RadiazioneReale::popUpMenu(const QPoint &pos)
{ 
	 
 	QMenu menu;
	QMenu exMenu(tr("&Esporta"),&menu);
	menu.addAction(a_print);
	menu.addAction(aw_toggle_marker);
	menu.addAction(a_proprieta);


	exMenu.addAction(a_exportPNG);
	exMenu.addAction(a_exportPDF);
	exMenu.addAction(a_export_txt);

	menu.addMenu(&exMenu);
	 #ifdef Q_X11
	menu.popup(pos);
	#endif
	menu.exec(QCursor::pos());
}
void RadiazioneReale::settings()
{
 	#ifdef DEBUG
 	qDebug()<<"I am here";	
 	#endif
// 	Settings s2;
// 	int a;
// 	 
	set->setVisible(true);
	set->raise();
	
}
void RadiazioneReale::printOut()
{
	QString path = QDir::currentPath()+tr("/radiazione_reale.pdf");
         QPrinter printer ;
	#ifdef Q_WS_X11
	 printer.setOutputFileName(path);
	#endif
	 printer.setCreator("Solar Calc");
          
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
void RadiazioneReale::moved(const QPoint &pos)
{
	
	
	picker->rubberBand();
}
 
void RadiazioneReale::exportPDF()
{
	 QString fileName;
	 fileName = QFileDialog::getSaveFileName(this, tr("Nome file da esportare"),   recentExportPath,"Acrobat ( *pdf)");
	QFileInfo fileInfo(fileName);
    	recentExportPath = fileInfo.absoluteDir().absolutePath();

	if ( !fileName.isEmpty() ) {
         QPrinter printer ;
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
 
void RadiazioneReale::exportSVG()
{
	QString fileName;
 

    fileName = QFileDialog::getSaveFileName(this, tr("Nome file da esportare"), recentExportPath ,        "SVG files (*.svg)");
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
            options |= QwtPlotPrintFilter::PrintBackground;
            options |= QwtPlotPrintFilter::PrintFrameWithScales|QwtPlotPrintFilter::PrintMargin;
	    filter.setOptions(options);
         print(generator,filter);
    }


}
void RadiazioneReale::setSource(int l)
{
	source = l;
}
void RadiazioneReale::setLocName(const QString &s)
{
	name = s;
	QString title = tr("Radiazione solare reale,") + name;
	QwtText ulabel(u.at(set->getUnit()-1));
	 
	QwtText tLabel(set->getTitle());
	tLabel.setFont(QFont("Times",14,QFont::Normal));
        setTitle(tLabel);
	 setTitle(tLabel);
}
void RadiazioneReale::computeRefCurve(int ombre, double t)
{
	QVector<double> res;
	
// 	RbLocal = o.getRelativeRb();
	for(int i=i<0;i<12;i++){
		res = MyMath::rb(lat*pi/180,t*pi/180,azi*pi/180,i,2009,0);//use ref daysc
		Href[i] = compute_(res.at(0),res.at(1),Hg[i],i,bestIncl*pi/180,ombre);
//    		qDebug()<<"RR COMPUTE REF CURVE"<<bestIncl*pi/180<<azi<<res<<Href[i];
// 	l = (double*)compute_(RbLocal,bestIncl*pi/180,ombre);//This is in MegaJoule!
// 	for(int i=0;i<12;i++) Href[i] = l[i];
	if (currentUnit==2) {
// 		qDebug()<<"RR: convertRaw from refCurve";
// 		for(int i=0;i<12;i++)
			Href[i] = convert(currentUnit,Href[i]);
		}
	}
	
}
void RadiazioneReale::optimize(int ombre )
{
// 	
	QVector<double> res;
        double hincl_[12] ;
	double i=0.0;
	bestIncl = i;

	double prec,actual;
        double inclLocal;

	


  //  	#ifdef DEBUG
	qDebug()<<"optimize tilt in rad.reale...lat="<<lat<<azi;
  //  	#endif
	
	bool condition = true;
	
	
//         Hincl_ = compute_(RbLocal,inclLocal,ombre);
//  	prec = MyMath::cumSumMonthly(hincl_,12);
	prec = 0;
  	while (condition && i<90) {

            inclLocal = i*pi/180;

		for(int t=0;t<12;t++){
			res = MyMath::rb(lat*pi/180,inclLocal,azi*pi/180,t,2009,0);//use ref days

                        hincl_[t] =
                                compute_(res.at(0),res.at(1),Hg[t],t,inclLocal,ombre);
 #ifdef DEBUG
qDebug()<<"optimize tilt in rad.reale...loop="<<i<<prec<<azi<<lat<<inclLocal<<res.at(0)<<
        res.at(1)<<res.at(3)<<res.at(4)<<res.at(5)<<condition;
 #endif
		}

		actual = MyMath::cumSumMonthly(hincl_,12);


		 
                if ((actual -prec)< 0.0000002) {
			// We found the max
			condition = false;
 
			
			bestIncl = i;
			maxIrr = prec;
		
		} else {
		        prec = actual;
                        i+=0.1;
		
		}
	if (i>=90) bestIncl=90;
	inclOptiPresent  = true;
	/*condition = false*/;/* for debug purpose */
	}
	
 
}
double RadiazioneReale::getMaxIrr()
{
	return maxIrr;
}

double RadiazioneReale::getBestIncl()
{
//   	qDebug()<<"Optimum,"<<lat*180.0/pi<<bestIncl;
	return bestIncl;
}

void RadiazioneReale::setLat(double a)
{
	lat=a;
}
void RadiazioneReale::setAzi(double a)
{
	azi=a;
}



void RadiazioneReale::alignScales()
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

// void RadiazioneReale::setOmbre(double *a)
// {
// 	for(int i=0;i<12;i++){
// 	ombreFactor[i] = a[i];
// 	#ifdef DEBUG
// 	qDebug()<<"setto le ombre in radiazione reale"<<a[i];
// 	#endif DEBUG
// 	}
// }
void RadiazioneReale::setOmbre(const QVector<double> &a)
{
	
	ombreFactor = a;
// 	qDebug()<<"RR setOMbre"<<a;
	
}
void RadiazioneReale::resetOmbre()
{
// 	for(int i=0;i<12;i++) ombreFactor[i] =1;
	ombreFactor.resize(0);
	ombreFactor.fill(1,12);
	
}
 double RadiazioneReale::fittingFunction(double t, double* p )
{
return (p[0] + p[1]*sin(2*pi*t/365 + p[2]));

}
 double RadiazioneReale::fittingFunction2(double t, double* p )
{
return (p[0] + p[1]*sin(2*pi*t/366 + p[2]));

}
void RadiazioneReale::fit()
{
 /* This function compute the parameter of the fitting function for daily radiation */
 // data and parameter arrays:

if (HgIsPresent)
	{
	
	int m_dat = 12;
	int n_p = 3;
	double* y;
	y = Hg;
	// auxiliary settings:
	
	lm_control_type control;
	lm_data_type data;
	
	lm_initialize_control(&control);
	
	if (MyMath::leapYear(year))
	data.user_func = fittingFunction2;
	else
	data.user_func = fittingFunction;
	data.user_t = normDays;
	//     qDebug()<<normDays[0]<<normDays[1];
	data.user_y = y;
	
	// perform the fit:
	p[2] = .5;
	p[1] = .5;
	p[0] = .5;
	
	lm_minimize(m_dat, n_p, p, lm_evaluate_default, lm_print_default,
			&data, &control);
	fittingDone = true;
	
	/* Update the values */
	 
	 
	for(int i=0;i<MyMath::yearEnd(year);i++){
		dailyHg[i]  = fittingFunction(i,p);//in MJ
		fittedHg[i] = dailyHg[i];
		
		 
 	}
	if ( currentUnit == 2)	
			convertFit(currentUnit);
//DO NOT CONVERT BECAUSE THESE VALUES ARE USED ALSO OUTSIDE
// THE CONVERSION CONCERNS THE PLOT!
  	
  	//{		
// 		for(int i=0;i<MyMath::yearEnd(year);i++)	{
// 			qDebug()<<"fit convert before convert"<<dailyHg[i];

//   			qDebug()<<"fit convert after convert"<<dailyHg[i];
 		//}
// 	drawDailyContents(1);
// 	}	
 
	
}
}
void RadiazioneReale::convertFit()
{
	if (currentUnit==2){
// 	qDebug()<<"RR convertFit with unit"<<currentUnit;
		convertFit(2);
}
}
void RadiazioneReale::convertFit(int unit)
{
	
	for(int i=0;i<MyMath::yearEnd(year);i++){
		 
	  	  fittedHg[i] = convert(unit,fittedHg[i]);
		
		
		}
	
	 
}
void RadiazioneReale::convertDailyFit(int unit)
{
QPolygonF tempIncl,tempInclOmbre;
// 	qDebug()<<"ConvertFit";
	for(int i=0;i<MyMath::yearEnd(year);i++)
	{
  	  
	  if (dailyHincl.size()>0 && dailyHinclOmbre.size()>0){
			tempIncl << QPointF(i,  convert(unit,dailyHincl.at(i).y())) ;
			tempInclOmbre << QPointF(i,  convert(unit,dailyHinclOmbre.at(i).y())); 
// 	qDebug()<<"ConvertFit n"<<i;
		}
	}

	 
		dailyHincl.resize(0);
		
		dailyHincl = tempIncl;
		dailyHinclOmbre = tempInclOmbre;
// 		qDebug()<<"copied Hinlc"<<dailyHincl.at(0).y();
}
 


double* RadiazioneReale::getFittingPar()
{
if (fittingDone)

	return p;
else
	return 0;
}
const double* RadiazioneReale::getFittedValues()
{
	
	return dailyHg;
}
QPolygonF RadiazioneReale::getDailyHincl()
{
	return dailyHincl;
}
QPolygonF RadiazioneReale::getDailyHinclOmbre()
{
	return dailyHinclOmbre;
}
bool RadiazioneReale::dailyIsDirty()
{
	return dailyValueDirty;
}
bool RadiazioneReale::hgIsPresent()
{
	return HgIsPresent;
}
void RadiazioneReale::resetTitle()
{
	QString str;
	QwtText tlabel(tr("Radiazione solare reale")+ " ");
	tlabel.setFont(QFont("Times",13,QFont::Normal));
	setTitle(tlabel);
	 setTitle(tlabel);
	set->setTitle(tr("Radiazione solare reale")+ " ");
}
bool RadiazioneReale::mainPlotPresent()
{
	return mainPlot;
}
double RadiazioneReale::getHourlyH(int h,int year,int month, int day, double shadow, double lat,double tilt, double d,double cosinc,double rrd,double r, int mode,int model)
/* This function return a vector of values of hourly radiation (in MJ) for a specific day of the year*/
/* lat,tilt in rad */
/* We suppose that only the direct beam is affected by the shadowing */
/* if mode==1 we have a sun-tracker*/
{
	double Ih,ratio,x,So,sigma,hd,hb,Hdirect,k,kt, hTot, hBeam,hDiffuse,G,R_;
	const double* hg;

	  d  = 23.45*pi/180 * sin(2*pi*(284+day)/365);
	/* Gaussian model */
// 	 So = (2.0/0.2618) * acos(-tan(lat)*tan(d));// HERE WE NEED THE APPARENT DAY LENGHT
 	So = totalDayLen.at(day);
	sigma = So*0.246;
	//   x = -pow(h-12,2)/(2*pow(sigma,2)) + cos(2*pi*(h-12)/(So-1));
	x = - pow(h-12,2)/(2*pow(sigma,2)) ;
	
	ratio = (exp(x)) * (1/(2*sigma*sqrt(2*pi)));

	if ((R.size() == 1) || R.size()<11 ){
			if (R.isEmpty())
				R_ = 0;
			else
				R_ = R.at(0);
		}
		else
			R_ = R.at(month);

	if (day>dailyHho.size()){
		qDebug()<<"RR getHourly not valid day"<<day<<dailyHho.size();	
		return -1;
		}
	if (h>23 || h<0){
		qDebug()<<"RR getHourly not valid hour";	
		return -1;
		}
		
		fit();//here we recompute the fit;Therefore the values hg are in MJ
		 
	if (  (dailyHho.size()==MyMath::yearEnd(year))  ) {
			hg  = getFittedValues();// daily values in MJ/m2
				
                        G = hg[day]>0 ? hg[day] : 0  ;/* Maybe the interpolation gave negative results*/
			// 
			
			 
			//We must divide the hourly hg because shadow impacts only on beam radiation
				kt = dailyHho.at(day).y()<0.00000000000002 ? 0 : G/dailyHho.at(day).y();/* the sun never rise */
				
				k = dailyHho.at(day).y()<0.00000000000002 ?  0 : diffuseIndex(model,dailyOmegas.at(day).y() ,kt);
	
			if (model==kaplanis){
				// Kaplanis
 				G = G  * ratio;   // houlry gloabl horizontal
     				hDiffuse = k * G;       // hourly diffuse
      				hBeam = G - hDiffuse; 	 //daily beam
				hTot = G;
			}
			
			if (model==pereira){ 
				//Pereira
				hd = k * G;		  // Daily diffuse
				hb = G - hd;		  // Daily beam

  				hDiffuse = rrd * hd; 	  // Hourly diffuse radiation at considered hour on horizontal plane
   				hTot    = r * G;  	  // Hourly total
 				hBeam   = hTot - hDiffuse;// Hourly Beam
				 ;
				
			}
				//KANAYAMA Kimio, Kyushu University JSME 1986
			if (model==kyushu)
			{
// 				G = G;//G is the horizontal daily
				hTot = r*G;// Hourly total
				hd = k * G; // Daily diffuse
				hb = G - hd; // Daily beam
				hBeam    = (hb)*MyMath::W_1(15*(h-12+0.5)*pi/180,dailyOmegas.at(day).y())/totalDayLen.at(day);// Hourly Beam
				hDiffuse = hd * MyMath::W_1(15*(h-12+0.5)*pi/180,dailyOmegas.at(day).y())/totalDayLen.at(day);
  				
				
			}
   #ifdef DEBUG
			qDebug()<<"RR model"<<model<<G<<hd<<hb<<hBeam<<hDiffuse<<h<<dailyOmegas.at(day).y()<<totalDayLen.at(day)<<dailyHho.at(day).y()<<cosinc<<k<<kt<<r<<rrd;
   #endif
				
// 				switch (mode) {
// 					case 0:
					Hdirect = cosinc * hBeam * shadow;
				
					Ih = Hdirect + hDiffuse*(1+cos(tilt))/2 + (hTot)*R_*(1-cos(tilt))/2;
					 
// 					break;
// 					case 1:
// 					Hdirect =  cosinc * hBeam * shadow;
// 					Ih =  (Hdirect + hDiffuse*(1+cos(tilt))/2 + (hTot)*R_*(1-cos(tilt))/2);
// // 					break;
// 				}
					
         	    		#ifdef DEBUG			
			qDebug()<<"RR getHourly..."<<hTot<<hBeam<<tilt<<Ih<<hBeam<<hDiffuse<<shadow<<tilt<<G<<hg[day]<<day<<h<<r<<rrd<<kt<<k<<hd<<cosinc<<Hdirect <<So;
         	   		#endif
			return Ih;
	}
	else{
		qDebug()<<"RR exit with 0"<<dailyHho.size()<< dailyRb.size();
		return 0;
	}
}
void RadiazioneReale::setTotalDayLen(const QVector<double> &a)
{
	totalDayLen = a;

}
void RadiazioneReale::setMeanDayLen(const QVector<double> &a)
{
	meanDayLen = a;
}
void RadiazioneReale::setYear(int i)
{
	year = i; 
}
QVector<double> RadiazioneReale::getLossFactors()
{
	
return mLF;//monthly loss factors due to shadows
}
double RadiazioneReale::getLossFactor()
{
	
return meanLossFactor;
}
 double RadiazioneReale::getTotalShadowLossFactor()
 {
 	
 return totalLossFactor;
 }
void RadiazioneReale::swapUnit()
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
void RadiazioneReale::viewRefCurve(bool i)
{
	showRefCurve = i;
}
void RadiazioneReale::addInclAzi(const QVector<double> &i,const QVector<double> &az)
{
	additionalIncl = i;
	additionalAzi  = az;
}
void RadiazioneReale::addOmbre(const QVector<double> &o)
{
	additionalOmbreFactor<<o;
}
void RadiazioneReale::resetAdditionalOmbre()
{
	additionalOmbreFactor.clear();
}
