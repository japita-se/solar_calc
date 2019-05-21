 // #define DEBUG
#include "energyout.h"
 
#include "settings.h"
 
#include <qwt_plot.h>
#include <qwt_plot_canvas.h>
#include <qwt_scale_draw.h>
#include <qwt_scale_widget.h>
#include <qwt_painter.h>
#include <qwt_plot_grid.h>
#include "mymath.h"
#include <qwt_plot_curve.h>
#include <qwt_plot_marker.h>
#include "histogram_item.h"



#include <qwt_interval_data.h>
#include <qwt_legend.h>
// #include <qwt_data.h>
#include <qwt_text.h>
#include <QtGui>
#include <QSvgGenerator>
#include <qwt_picker.h>
#include <qwt_plot_picker.h>
#define sign MyMath::sign
#define pi 3.14159
#define Go 1367
#define correction 1367/1353

EnergyOut::EnergyOut(QWidget* parent): QwtPlot(parent)
{
	year=2009;	
	area2=0;
	this->setWindowIcon(QIcon(":/images/app.png"));
	setWindowTitle("SolarCalc - Energia annuale prodotta");
	
        u<<tr("[MJ]")<<tr("[kWh]");
	
	QwtPainter::setDeviceClipping(false);
	
//	plotEnergy = new QwtPlotCurve();
//	plotEnergy->attach(this);
//	plotEnergy->setPen(QPen(Qt::red));
//	plotEnergy->setBrush(QBrush(Qt::Dense7Pattern));

        plotEnergy = new HistogramItem();
        plotEnergy->attach(this);
        plotEnergy->setColor(Qt::darkYellow);

	 
	recentExportPath = QDir::homePath() ;
	recentDir= QDir::homePath() ;
        setMargin(40);
   	picker = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft,       QwtPicker::PointSelection , QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn,this->canvas());
	picker->setRubberBandPen(QColor(Qt::black));
    	picker->setRubberBand(QwtPicker::CrossRubberBand);
	picker->setEnabled(true);
	picker->setTrackerPen(QColor(Qt::black));
	connect(picker, SIGNAL(moved(const QPoint &)),SLOT(moved(const QPoint &)));
	 pan.isValid = false;
	 

// #ifdef Q_WS_X11
//     /*
//        Qt::WA_PaintOnScreen is only supported for X11, but leads
//        to substantial bugs with Qt 4.2.x/Windows
//      */
//     canvas()->setAttribute(Qt::WA_PaintOnScreen, true);
// 	#endif
	
	 
        enableAxis(QwtPlot::yLeft,true);
	
	
	setCanvasBackground(QColor(Qt::white));

	// Set default settings
	set = new Settings();
	set->setTitle(tr("Energia producibile"));
	set->setUnit(2);//kWh
	currentUnit = 2;//kWh
	set->radiokWh->setText("kWh");
	set->radioMJ->setText("MJ");
	set->setAxisY(tr("Media mensile"));
	set->setAxisX(tr("Mese"));
	set->setVisible(false);
	connect(set,SIGNAL(accepted()),SLOT(updateSet()));
	
	QwtText ulabel(u.at(set->getUnit()-1));
	ulabel.setFont(QFont("Times",12,QFont::Normal));
	QwtText xlabel(set->getAxisX());
	xlabel.setFont(QFont("Times",12,QFont::Normal));
	QwtText ylabel(set->getAxisY()+ " " + ulabel.text());
	ylabel.setFont(QFont("Times",12,QFont::Normal));
	QwtText tlabel(set->getTitle());
	tlabel.setFont(QFont("Times",14,QFont::Normal));
	 

	setTitle(tlabel);

	setAxisTitle(QwtPlot::xBottom,xlabel);
        setAxisTitle(QwtPlot::yLeft,ylabel);
        setAxisScale(QwtPlot::xBottom,0.5,12.5,1);
        replot();
	this->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this,SIGNAL(customContextMenuRequested(const QPoint &  )),this,SLOT(popUpMenu(const QPoint &)));

	plotEnergyMarker = new QwtPlotMarker;
	plotEnergyMarker->attach(this);
	plotEnergyMarker2 = new QwtPlotMarker;
	plotEnergyMarker2->attach(this);
	
	alignScales();
	createActions();
	
	totEnergy   = totEnergy1   = totEnergy2   = area = area2 = 0;
	otherLoss.fill(0,12);
	totLossTemp = 0;
	for(int i=0;i<12;i++)
	defaultTemp<<0;
	tempDaily.fill(0,12);
	windDaily.fill(0,12);
	effTemp.fill(0,12);
	effTemp2.fill(0,12);

	/* for Noct correction */
	 
	mounting       = rack;
	mountingHeight = 2.5;
	concRatio=1;
	status = tr("Pannello assente");
}

void EnergyOut::createActions()
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

        a_export_txt = new QAction(tr("File di testo"),this);
        a_export_txt->setIcon(QIcon(":/images/text.png"));

	connect(a_print,SIGNAL(triggered()),this,SLOT(printOut()));
	connect(a_export,SIGNAL(triggered()),this,SLOT(exportSVG()));
	connect(a_proprieta,SIGNAL(triggered()),this,SLOT(settings()));
	 
	connect(a_exportPNG,SIGNAL(triggered()),this,SLOT(exportPNG()));
	connect(a_exportPDF,SIGNAL(triggered()),this,SLOT(exportPDF()));
	connect(a_export_txt,SIGNAL(triggered()),this,SLOT(exportTXT()));
	 
	 
	 
}
void EnergyOut::setArea(double a)
{	
	area = a;
}
void EnergyOut::setAddArea(double a)
{	
	area2 = a;
}
void EnergyOut::setInverter(inverter i)
{
	inv = i;
}
void  EnergyOut::setPanel(panel p)
{
        pan = p;
        if (pan.isValid)
            status = tr("Pannello=") + pan.model+"  ";
        else
            status = tr("Pannello assente")+"  ";
//  	qDebug()<<"EnergyOut: ho settato panel"<<p.isValid<<pan.isValid;
}
void  EnergyOut::setTempMin(double a)
{
	
	tempMin = a;

}
void  EnergyOut::setTempMax(double a)
{
	tempMax = a;

}
void EnergyOut::setTemp(const QVector<double> & t)
{
	tempDaily.resize(0);
	if (t.size()>=12)
	{
	tempDaily = t;
	}
	else
	
		tempDaily.fill(0,12);
  	#ifdef DEBUG
 	qDebug()<<tempDaily<<"EnergyOut size of passed temp:"<<t;
  	#endif
}
double EnergyOut::getHourlyValue(double area_,double rad,int month,int doy)
/*rad MUST BE IN kWh */
/* month run from 1 to 12 */
{
// 	int numDays = MyMath::monthEnd(month,year);
        double inverterEff,effTemp,Energy_,at,Ta,upv,tc,bn,r ;
	if ((systemDetails.efficiencies.size()>0) && systemDetails.systemValid)
		inverterEff = MyMath::mean(systemDetails.efficiencies)/100;
		else{

			if (inv.isValid)
				inverterEff = inv.eff/100;
			else
				inverterEff = 1;
        }
	if (pan.isValid) {
		 
		/*TODO We should use also a daily temperature profile here! */
		switch (thermalModel) {
			case NOCT:
			effTemp = 1-(tempDaily.at(month-1) - 25 + ((9.5/(5.7+3.8*windDaily.at(month-1)))*rad)*(realNoct(pan.noct)-tempDaily.at(month-1))/0.8)*(-pan.gamma/100);
			break;
			case CEA:
			effTemp = 0.94 +(pan.gamma/100)*(tempDaily.at(month-1)  + (1/(22.4+8.7*windDaily.at(month-1)))*rad /meanDayLen.at(month-1)  );
			break;
			case other:
			r  = rad/meanDayLen.at(month-1);
			bn = -pan.gamma*pan.eff/10000;
			upv= 11.34+7.72*windDaily.at(month-1);
			at =0.9;
			tc = (upv*Ta + 1000*r*(at - pan.eff/100 -bn*25))/(upv-bn*r*1000);
			effTemp  = 1-(-pan.gamma/100)*(tc- 25);
			break;
                        default:
                        effTemp = 1;
		}
		if (effTemp>1) effTemp=1;

		if  (area_>0)   {
                        //int ddend = MyMath::monthEnd(month,year);
			
			/* This energy is in kWh !!!*/
			/* and it is for just one our*/

                        Energy_ = area_* (pan.eff/100)*rad*effTemp*(1-otherLoss[month-1])*inverterEff*concRatio;
			
	
	
          			#ifdef DEBUG
			if (month==11)
                        qDebug()<<"EnergyOut, computeRealEnergy hourly "<<rad<<Energy<<effTemp<<pan.eff<<pan.gamma<<pan.noct<<tempMax<<pan.isValid<<tempDaily.at(month-1)<<totEnergy<<doy<<totalDayLen.at(doy );
             			#endif
	
			}
			else
                        Energy_=0;
                return Energy_;
		}
	else
	return 0;

}
void EnergyOut::computeRealEnergy()
{
        double inverterEff,tempMed,at,Ta,upv,tc,tc2,bn,rad,rad2,ePure,ePure1,ePure2;
	#ifdef DEBUG
        qDebug()<<"EnergyOut, computeRealEnergy top"<<pan.isValid<<meanDayLen.at(0);
	#endif
	if (systemDetails.efficiencies.size()>0 && systemDetails.systemValid){
		inverterEff = MyMath::mean(systemDetails.efficiencies)/100;
//    		qDebug()<<"EO compureReal eff"<<systemDetails.efficiencies<<systemDetails.systemValid;
		}
		else {
			if (inv.isValid)
				inverterEff = inv.eff/100;
			else
				inverterEff = 1;
                }
        tempMed = (tempMax+tempMin)/2;
	if (pan.isValid) {
		totEnergy = totEnergy2 = totEnergy1 =0;
		totLossTemp=0;
                ePure1 = ePure2 = ePure = 0;
		effTemp.resize(0);
		effTemp2.resize(0);
	
		for(int i=1;i<=12;i++) {
 			#ifdef DEBUG
                       qDebug()<<"EnergyOut, computeRealEnergy FRO LOOP"<<pan.isValid<<meanDayLen.at(i-1)<<otherLoss;
 			#endif
			/* H in kW/m2*/
                        /* See E.Skoplaki,J.A. Payvos Solar Energy 83 (2009) pp.614-624*/
                 
                    /* From E.Lorenzo */
		    /* cfr.Evans, D.L., Florschuetz, L.W., 1978. Terrestrial concentrating photovoltaic
power system studies. Solar Energy 20, 37-43.*/
	Ta = tempDaily.at(i-1);
	
	switch (thermalModel) {	 
		case NOCT:
                    effTemp<<  1-(Ta - 25 + ((9.5/(5.7+3.8*windDaily.at(i-1)))*H[i-1]/meanDayLen.at(i-1))*(realNoct(pan.noct)-Ta)/0.8)*(-pan.gamma/100);
                    effTemp2<<  1-(Ta - 25 + ((9.5/(5.7+3.8*windDaily.at(i-1)))*H2[i-1]/meanDayLen.at(i-1))*(realNoct(pan.noct)-Ta)/0.8)*(-pan.gamma/100);
		break;
		/* alternative equation CLEFS CEA (2004), On the temperature dependence of photovoltaic module electrical performance: A review of efficiency/power correlations*/ 
		case CEA:
                    effTemp<<  0.94 +(pan.gamma/100)*(Ta  + (1/(22.4+8.7*windDaily.at(i-1)))*H[i-1]/meanDayLen.at(i-1) );
                    effTemp2<<  0.94 +(pan.gamma/100)*(Ta  + (1/(22.4+8.7*windDaily.at(i-1)))*H2[i-1]/meanDayLen.at(i-1) );
		break;
		case other:
                    rad = H[i-1]/meanDayLen.at(i-1);
                    rad2 = H[i-1]/meanDayLen.at(i-1);
                    bn = -pan.gamma*pan.eff/10000;
                    upv= 11.34+7.72*windDaily.at(i-1);
                    at =0.9;
                    tc = (upv*Ta + 1000*rad*(at - pan.eff/100 -bn*25))/(upv-bn*rad*1000);
                    tc2 = (upv*Ta + 1000*rad2*(at - pan.eff/100 -bn*25))/(upv-bn*rad2*1000);
                    effTemp<< 1-(-pan.gamma/100)*(tc- 25);
                    effTemp2<< 1-(-pan.gamma/100)*(tc- 25);
                break;
		/* To check*/
	}
        if (effTemp.at(i-1)>1) {effTemp.replace(i-1,1);}
        if (effTemp2.at(i-1)>1) {effTemp2.replace(i-1,1);}

			int ddend = MyMath::monthEnd(i,year);
			if  (area>00.000000002)   {
			
			
                                /* This energy is in kWh !!!*/
                                ePure1 += area*ddend*(pan.eff/100)*H[i-1]*(1-otherLoss.at(i-1))*inverterEff*concRatio;
                                Energy1[i-1] = area*ddend*(pan.eff/100)*H[i-1]*effTemp.at(i-1)*(1-otherLoss.at(i-1))*inverterEff*concRatio;


        // 			totLossTemp+=effTemp.at(i-1);
                                                 #ifdef DEBUG
                                qDebug()<<"EnergyOut1, computeRealEnergy "<<otherLoss.at(i-1)<<inverterEff<<area<<H[i-1]<<Energy1[i-1]<<ddend<<effTemp.at(i-1)<<pan.eff<<pan.gamma<<pan.noct<<tempMax<<pan.isValid<<tempDaily.at(i-1)<<totEnergy1<<ePure1<<installedPower<<meanDayLen.at(i-1);
                                qDebug()<<tc<<upv<<bn<<at<<area<<inverterEff<<concRatio<<otherLoss;
                                                 #endif

 	
			}
			else
                                Energy1[i-1]=0;

			/* SECOND FACADE*/
			if  (area2>0.000000002)   {
			
			
                                /* This energy is in kWh !!!*/
                                ePure2 += area2*ddend*(pan.eff/100)*H2[i-1]*(1-otherLoss.at(i-1))*inverterEff*concRatio;
                                Energy2[i-1] = area2*ddend*(pan.eff/100)*H2[i-1]*effTemp2.at(i-1)*(1-otherLoss.at(i-1))*inverterEff*concRatio;


        // 			totLossTemp+=effTemp.at(i-1);
                                                #ifdef DEBUG
                                qDebug()<<"EnergyOut2, computeRealEnergy "<<H2[i-1]<<Energy2[i-1]<<ddend<<effTemp2.at(i-1)<<pan.eff<<pan.gamma<<pan.noct<<tempMax<<pan.isValid<<tempDaily.at(i-1)<<installedPower<<meanDayLen.at(i-1);
        // 			qDebug()<<tc<<upv<<bn<<at<<area<<inverterEff<<concRatio<<otherLoss;
                                                #endif
 	
			}
			else

                                Energy2[i-1]=0;

			totEnergy2+=Energy2[i-1];
			totEnergy1+=Energy1[i-1];
		
			Energy[i-1] = Energy1[i-1] + Energy2[i-1];
                        EnergyView[i-1] = Energy[i-1];
			totEnergy = totEnergy1 + totEnergy2;
			ePure = ePure1 + ePure2;

           //qDebug()<<"EnergyOut,effTemp"<<thermalModel<<windDaily.at(i-1)<<effTemp<<ePure1<<ePure2<<totEnergy1<<totEnergy2;
		}
               //qDebug()<<"EnergyOut,effTemp"<<thermalModel<<totEnergy<<ePure<<effTemp<<ePure1<<ePure2<<totEnergy1<<totEnergy2;
	totLossTemp = (ePure>0.000000002) ? (1-totEnergy/ePure)*100 : 0;

// 	totLossTemp=(1-totLossTemp/12)*100;
        if (currentUnit == 1)
                /* Convert to MJ else nothing */
            convert(currentUnit);
	}

}

void EnergyOut::popUpMenu(const QPoint &pos)
{ 
	 QMenu menu;
	QMenu exMenu(tr("&Esporta"),&menu);
	QMenu ombreMenu(tr("&Ombre"),&menu);
	
	exMenu.addAction(a_export);
	exMenu.addAction(a_exportPNG);
	exMenu.addAction(a_exportPDF);
        exMenu.addAction(a_export_txt);
	
	 
	
	menu.addAction(a_print);
	menu.addMenu(&exMenu);
 
	
	menu.addAction(a_proprieta);
 
	 
	#ifdef Q_WS_X11
	menu.popup(pos);	
	#endif
	menu.exec(QCursor::pos());
 	 
}
void EnergyOut::settings()
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
// void EnergyOut::exportPDF()
// {
// 	 QString fileName;
// 	 fileName = QFileDialog::getSaveFileName(this, tr("Nome file da esportare"),  QDir::homePath(),"Acrobat ( *pdf)");
// 
// 	if ( !fileName.isEmpty() ) {
// 	 QPrinter printer(QPrinter::HighResolution);
// 	 printer.setOutputFormat(QPrinter::PdfFormat);
// 	 printer.setOutputFileName(fileName);
// 	 printer.setCreator("Solar Calc");
//          printer.setOrientation(QPrinter::Landscape);
// 	 
// 	 
//      
//        
// 	QwtPlotPrintFilter filter;
// //          if ( printer.colorMode() == QPrinter::GrayScale )
//          
//             int options = QwtPlotPrintFilter::PrintAll;
//             options &= ~QwtPlotPrintFilter::PrintBackground;
//             options |= QwtPlotPrintFilter::PrintFrameWithScales;
//             filter.setOptions(options);
//         
// 
// 	print(printer,filter);
// 
// 
// 
//       }
// }

void EnergyOut::printOut()
{
	QString path = QDir::currentPath()+tr("/energiaprodotta_reale.pdf");
         QPrinter printer ;
	#ifdef Q_WS_X11
	 printer.setOutputFileName(path);
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
void EnergyOut::exportTXT()
{
        QString fileName;


    fileName = QFileDialog::getSaveFileName(this, tr("Nome file da esportare"),  recentDir,"Text files ( *txt)");

    if ( !fileName.isEmpty() )
    {
        fileName = MyMath::checkFormat(fileName,"txt");
        if (!MyMath::exportToText(fileName,Energy,12))
        QMessageBox::warning(this,tr("Esportazione dati"),tr("Qualche errore di scrittura sul file/cartella selezionata. Prova a ripetere o a cambiare cartella/nome file"),QMessageBox::Ok);
        recentDir = QFileInfo(fileName).absoluteDir().absolutePath();
    }

}
// void EnergyOut::exportSVG()
// {
// 	QString fileName;
//  
// 
//     fileName = QFileDialog::getSaveFileName(this, tr("Nome file da esportare"),  QDir::homePath(),"Graphic files ( *svg)");
// 
//     if ( !fileName.isEmpty() )
//     {
//         QSvgGenerator generator;
//         generator.setFileName(fileName);
//         generator.setSize(QSize(1024, 800));
// 	QwtPlotPrintFilter filter;
//    	int options = QwtPlotPrintFilter::PrintAll;
//             options |= QwtPlotPrintFilter::PrintBackground;
//             options |= QwtPlotPrintFilter::PrintFrameWithScales|QwtPlotPrintFilter::PrintMargin;
// 	    filter.setOptions(options);
//            
// //     QPixmap pixmap =  QPixmap::grabWidget(this);
// //     QPainter painter(&generator);
//       print(generator,filter);
//     }
// 	
// 
// }
void EnergyOut::exportPNG()
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
 
void EnergyOut::moved(const QPoint &pos)
{
	
	
	picker->rubberBand();
}
void EnergyOut::updateSet()
{
	QString str;
	int chosenUnit = set->getUnit();
	str = u.at(chosenUnit-1);
 	#ifdef DEBUG
 	qDebug()<<"update Set"<<set->getTitle();	
 	#endif

	QwtText ulabel(str);
	ulabel.setFont(QFont("Times",11,QFont::Normal));

	QwtText xlabel(set->getAxisX());
	xlabel.setFont(QFont("Times",11,QFont::Normal));
	QwtText ylabel(set->getAxisY()+ " " + ulabel.text());
	ylabel.setFont(QFont("Times",11,QFont::Normal));
	QwtText tlabel(set->getTitle());
	tlabel.setFont(QFont("Times",13,QFont::Normal));
	
	setTitle(tlabel);
	setAxisTitle(QwtPlot::yLeft,ylabel);
	setAxisTitle(QwtPlot::xBottom,xlabel);
       if (currentUnit!=chosenUnit) {
		currentUnit = chosenUnit;
		convert(chosenUnit);
		drawContents(1);
		
	}
	 
}
void EnergyOut::convert(int unit)
{
        double k=3.6;
	if (unit==1)
		// convert from kWh to MJ
		k = 3.6;
	if (unit==2)
		// convert from MJ to kWh
                k=1/3.6;

		for(int i=0;i<12;i++) {
                EnergyView[i] = k * EnergyView[i];
		
		}
	totEnergy = k* totEnergy;
	emit unitChanged();
}
void EnergyOut::drawContents( int mode)
{
        QwtArray<QwtDoubleInterval> intervals(12);
        QwtArray<double> values(12);
        //double m[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
 	double maxCurve=MyMath::max(Energy,12);


        double pos=0;
	QwtText label;
	label.setFont(QFont("Helvetica [Cronyx]", 12));
	if (mode==1) {
	 
		if (pan.isValid) {
			#if QT_VERSION >= 0x040000
			setAxisScale(QwtPlot::yLeft,0,maxCurve*1.2);
                        for(int i=0;i<12;i++)
                        {

                                        intervals[i] = QwtDoubleInterval(0.5+pos,pos+1.5);

                                pos += 1;
                                values[i] = EnergyView[i];
                        }
                        plotEnergy->setData(QwtIntervalData(intervals, values));
   			plotEnergy->setRenderHint(QwtPlotItem::RenderAntialiased);
			
			#endif

//			plotEnergy->setData(m,Energy,12);
			
// 			plotEnergyMarker2->setValue(10,MyMath::max(Energy,12)-40);
// 			QwtText label2(tr("Perdite termiche ") + " " + QString::number(totLossTemp));
// 			plotEnergyMarker2->setLabel(label2);
		
			
                    }else{
                        //plotEnergy->setRawData(0,0,0);
                        plotEnergy->setData(QwtIntervalData());
                    }
		
	}
	else
	{
 
        //plotEnergy->setRawData(0,0,0);
        plotEnergy->setData(QwtIntervalData());
	label.setText("");
	plotEnergyMarker->setLabel(label);
	resetTitle();
	}
//qDebug()<<"Radiazione reale mode"<<mode;
replot();

//	if ((pan.isValid) && (mode==1))
//		{
//			max = axisScaleDiv(yLeft)->upperBound();
//			s   = max*0.20;
//			plotEnergyMarker->setValue(10,max-s);
//			label.setRenderFlags(Qt::AlignLeft);
//                        label.setText("<p>" + tr("Potenza installata = ") + QString("%L1").arg(installedPower) + "kWp</p><p>" + tr("Totale anno ")+" = " +QString("%L1").arg(totEnergy) + u.at(currentUnit-1) + "</p><p>" + tr("Perdite termiche ") + " = " + QString::number(totLossTemp,'f',1)+ " %</p><p> kWh/kWp " + " = " +QString("%L1").arg((starRatio())));
//			plotEnergyMarker->setLabel(label);
//		}
//
//			replot();
}
QVector<double> EnergyOut::getEffTemp()
{
// 	double *start = effTemp;
// 	return start;
// This is not in %!!!
	return effTemp;

}
 QVector<double> EnergyOut::getEffTemp2()
{
// 	double *start = effTemp;
// 	return start;
// This is not in %!!!
	return effTemp2;

}
double EnergyOut::getLossTemp()
{
        //qDebug()<<"ENERGYOUT0 temp"<<totLossTemp;
	return totLossTemp;

}
double* EnergyOut::getRealEnergy()
{
        double *start = Energy;//always in kWh
	return start;
	
}

void EnergyOut::setH(double*  a,double* b,int unit)
/* TWO FACADE */
{
	/* unit = 1, MJ/m2, unit=2 kW/m2*/
//  	qDebug()<<"EO current unit ="<<unit;
 	for(int i=0;i<12;i++){
 		if (unit==1){
 			H[i] = a[i]/3.6;
			H2[i] = b[i]/3.6;
		}
 		if (unit==2){
			H[i] = a[i];
			H2[i]= b[i];
		}
// 	qDebug()<<"EO H = "<<H[i];
  	}
}


void EnergyOut::exportPDF()
{
	 QString fileName;
	 fileName = QFileDialog::getSaveFileName(this, tr("Nome file da esportare"),  recentExportPath,"Acrobat ( *pdf)");
	QFileInfo fileInfo(fileName);
	recentExportPath = fileInfo.absoluteDir().absolutePath();
	if ( !fileName.isEmpty() ) {
         fileName = MyMath::checkFormat(fileName,"pdf");
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
 
void EnergyOut::exportSVG()
{
	QString fileName;
 

    fileName = QFileDialog::getSaveFileName(this, tr("Nome file da esportare"), recentExportPath,"SVG files (*.svg)");
    QFileInfo fileInfo(fileName);
    recentExportPath = fileInfo.absoluteDir().absolutePath();

    if ( !fileName.isEmpty() )
    {
 
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
void EnergyOut::alignScales()
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

void EnergyOut::setMeanDayLen(const QVector<double> &p)
{
        meanDayLen = p;
	#ifdef DEBUG
        qDebug()<<"EnergyOut ho settato la lunghezza delgiorno"<<p.at(0)<<meanDayLen.at(0)<<meanDayLen.at(1)<<meanDayLen.at(2);
	#endif
}
void EnergyOut::setTotalDayLen(const QVector<double> &p)
{
        totalDayLen = p;
	#ifdef DEBUG
        qDebug()<<"EnergyOut ho settato la lunghezza delgiorno per tutti i giorni"<<p.at(0)<<totalDayLen.at(0)<<totalDayLen.at(1)<<totalDayLen.at(2);
	#endif
}

void EnergyOut::setOtherLoss(const QVector<double> &a)
{
	otherLoss = a;
// 	qDebug()<<"EnergyOut other losses"<<otherLoss;
}
double EnergyOut::getTotEnergy()
{

	return totEnergy;
}
int EnergyOut::getUnit()
{
	return currentUnit;/*1 -> MJ, 2->kWh*/
}

QString EnergyOut::getStatus()
{
    return status;
}
bool EnergyOut::getStatus(int p)
{
//qDebug()<<"EnergyPlot getStatus"<<p;
	switch (p) {
		case 1:
			if (pan.isValid) {
                                qDebug()<<"EnergyPlot panel valid"<<pan.isValid;
				return true;
				}
			else
				return false;
		break;
	}
}

void EnergyOut::resetTitle()
{
	QString str;
	QwtText tlabel(tr("Energia producibile")+ " ");
	tlabel.setFont(QFont("Times",13,QFont::Normal));
	setTitle(tlabel);
	set->setTitle(tr("Energia producibile")+ " ");
}
void EnergyOut::setWind(const QVector<double> &t)

{
	windDaily.resize(0);
	if (t.size()>=12)
	{
		windDaily = t;
	}
	else
	
	windDaily.fill(0,12);
        #ifdef DEBUG
 	qDebug()<<windDaily<<"EnergyOut size of passed wind:"<<t;
       #endif
}
void EnergyOut::setWind( double w)
{
	wind = w;
}
double EnergyOut::realNoct(double t)
{
	switch (mounting) {
		case rack:
			return t-3;
			break;
		case direct:
                        return t+18;
			break;
		default:/*standoff or rack*/
			return t + MyMath::linear(2.5,11.0,7.5,2.0,mountingHeight); /* INOCT values, h=2.5;7.5, x=11;2 degree C */
		break;
 
	return t;
	}
}
void EnergyOut::setMounting(int i,double h)
{
	if (i>=0 && i<=3)
	mounting = i;
	if (i==2)
	mountingHeight = h;
	
// 	qDebug()<<"EO mounting"<<i<<h;
}

void EnergyOut::setConcRatio(double i)
{
	if (i>0)
		concRatio = i;
	else
		concRatio = 1;
}
void EnergyOut::setYear(int y)
{
year = y;
}
void EnergyOut::setThermalModel(int i)
{
	if (i<=3)
		thermalModel = i;
#ifdef DEBUG
qDebug()<<"EO thermal model = "<<i;
#endif
}
double EnergyOut::starRatio()
{
	if (pan.isValid)
    {
            if (installedPower>0.0000002)
                return totEnergy/installedPower;
            else
                return 0;
    }else
	return 0;
}
void EnergyOut::setInstalledPower(double i)
{
	// we suppose i in kWh/kWp!!
	if (i>0)	
		installedPower = i;
	else
		installedPower = 0;
}
void EnergyOut::setSystem(const sy i)
{
	systemDetails = i ;
// 	qDebug()<<"EO system"<<systemDetails.efficiencies;
}
