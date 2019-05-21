#include "hourlyenergyplot.h"
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
HourlyEnergyPlot::HourlyEnergyPlot(QWidget* parent): QwtPlot(parent)
{
	enableLoads = false;
	recentDir = QDir::homePath();
	dateLabel="";
	integral=0;
	createActions();
	recentExportPath = QDir::homePath();
	  u<<tr("[MJ]")<<tr("[kWh]");
	QwtSymbol sym2,sym1;
	sym2.setStyle(QwtSymbol::Ellipse);
	sym2.setPen(QColor(Qt::blue));
	sym2.setSize(10);
	
	sym1.setStyle(QwtSymbol::Diamond);
	sym1.setPen(QColor(Qt::red));
	sym1.setSize(10);


	plotHourly = new QwtPlotCurve(tr("Energia elettrica prodotta"));
	plotHourly->attach(this);
        plotHourly->setSymbol(sym2);
// 	plotHourly->setStyle(QwtPlotCurve::Sticks);
	
	plotLoad = new QwtPlotCurve(tr("Energia elettrica assorbita"));
	plotLoad->attach(this);
        plotLoad->setSymbol(sym1);
	plotLoad->setPen(QPen(Qt::red));

	plotHourly->setPen(QPen(Qt::black));

	setAxisScale(QwtPlot::xBottom,0,23);
	setMargin(2);

	QwtLegend* legend = new QwtLegend(this);
       	insertLegend(legend,QwtPlot::BottomLegend);

   	picker = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft,       QwtPicker::PointSelection , QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn,this->canvas());
	picker->setRubberBandPen(QColor(Qt::black));
    	picker->setRubberBand(QwtPicker::CrossRubberBand);
	picker->setEnabled(true);
	picker->setTrackerPen(QColor(Qt::black));
	 enableAxis(QwtPlot::yLeft,true);
//   	enableAxis(QwtPlot::yRight,true);
	
	totalMarker = new QwtPlotMarker();
	totalMarker->attach(this);

	setCanvasBackground(QColor(Qt::white));
	// Set default settings
	set = new Settings();
	set->setTitle(tr("Energia elettrica oraria"));
	set->setUnit(2);//MJ/m2
	currentUnit = 2;
	set->setAxisY(tr("Media oraria"));
	currentTitle = set->getTitle();
	 
	set->setAxisX(tr("Ora"));
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
        setAxisTitle(QwtPlot::yLeft,ylabel );
	setAxisTitle(QwtPlot::yRight,set->getAxisYRight() + " " + u.at(set->getUnit()-1));
	this->setContextMenuPolicy(Qt::CustomContextMenu);

	connect(this,SIGNAL(customContextMenuRequested(const QPoint &  )),this,SLOT(popUpMenu(const QPoint &)));

	alignScales();
	plotPresent = false;
}
void HourlyEnergyPlot::setHourlyData(const QPolygonF &data)
{
	/* supposed in kWh */
	
	double i;
	hourlyData = data;
	if (currentUnit==1)
		convert(currentUnit);
	if (scaling && totalThisDay>0.0000000002){
		i = MyMath::cumSum(hourlyData);
              //  qDebug()<<"HD enerhy orig data scale"<<hourlyData;
		MyMath::scale(hourlyData,totalThisDay/i);
               // qDebug()<<"HD energy scaled data scale"<<hourlyData<<totalThisDay<<i;
		}
	integral = MyMath::cumSum(hourlyData);
     //  qDebug()<<"HEP data"<<integral<<totalThisDay;
}
void HourlyEnergyPlot::draw(int mode)
{
	
	if (mode==1)
	{
// 		qDebug()<<"HEP replot"<<hourlyData;
		plotHourly->setData(hourlyData);
//  		double max = axisScaleDiv(yLeft)->upperBound();	
		double max = MyMath::max(hourlyData);
	
                QwtText label(tr("<p> Totale giornaliero = </p><p>") + QString("%L1").arg(integral) + u.at(set->getUnit()-1) +"</p>");
		label.setRenderFlags(Qt::AlignLeft);
		label.setLayoutAttribute(QwtText::MinimumLayout,true);
		label.setFont(QFont("Helvetica [Cronyx]", 10));
                totalMarker->setValue(3,max*9/10);
		totalMarker->setLabel(label);
		
		
		 
	}
	if (mode==0){
 		plotHourly->setRawData(0,0,0);
		
 		dateLabel="";
 		totalMarker->setLabel(QwtText(""));
	}
// monthMarker->setValue(2,8*max/10);
replot();		
	
}
void HourlyEnergyPlot::alignScales()
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
HourlyEnergyPlot::~HourlyEnergyPlot()
{}
void HourlyEnergyPlot::setTime(int month,int day)
{
	if (month>=1 && month<=12)
	dateLabel = MyMath::months(month);
	set->setTitle(tr("Energia elettrica oraria") +" - " +dateLabel);
	currentTitle = set->getTitle();
	updateSet();
	

}
void HourlyEnergyPlot::updateSet()
{
// 	QString str;
	int chosenUnit = set->getUnit();
// 	str = u.at(chosenUnit-1);
 	#ifdef DEBUG
 	qDebug()<<"update Set"<<set->getTitle();	
 	#endif


	QwtText ulabel(u.at(set->getUnit()-1));
	QwtText xlabel(set->getAxisX());
	xlabel.setFont(QFont("Times",12,QFont::Normal));
	QwtText ylabel(set->getAxisY()+ " " + ulabel.text());
	ylabel.setFont(QFont("Times",12,QFont::Normal));
	
	QwtText tlabel(set->getTitle());
		tlabel.setFont(QFont("Times",14,QFont::Normal));
		setTitle(tlabel);
	
	setAxisTitle(QwtPlot::yLeft,ylabel);
	setAxisTitle(QwtPlot::xBottom,xlabel);
       if (currentUnit!=chosenUnit) {
		convert(chosenUnit);
		draw(1);
		currentUnit = chosenUnit;
	}

	 
		
	 
	 
}
void HourlyEnergyPlot::convert(int unit)
{
	QPolygonF temp;
	double k;
        if (unit<=2){
            integral = 0;
            if (unit==1)
                    // convert from kWh to MJ
                    k = 3.6;
            if (unit==2)
                    // convert from MJ to kWh
                    k=1/3.6;

                    for(int i=0;i<hourlyData.size();i++) {
                    temp<< QPointF(i,k * hourlyData.at(i).y());
                    integral+=temp.at(i).y();

                    }
    // 	integral = k * integral;
            hourlyData.resize(0);
            hourlyData = temp;
    // 	totRad = k* totRad;
            emit unitChanged(unit);
       }
}
void HourlyEnergyPlot::popUpMenu( const QPoint &pos)
{ 
	 QMenu menu;
	QMenu exMenu(tr("&Esporta"),&menu);
 
	
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
void HourlyEnergyPlot::createActions()
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

void HourlyEnergyPlot::settings()
{
 	#ifdef DEBUG
 	qDebug()<<"I am here";	
 	#endif
// 	Settings s2;
// 	int a;
	currentTitle = set->getTitle();
	set->setVisible(true);
	set->raise();
	
}
void HourlyEnergyPlot::exportTXT()
{
	QString fileName;
 

    fileName = QFileDialog::getSaveFileName(this, tr("Nome file da esportare"),  recentDir,"Text files ( *txt)");

    if ( !fileName.isEmpty() )
    {
	fileName = MyMath::checkFormat(fileName,"txt");
	if (!MyMath::exportToText(fileName,hourlyData))
	QMessageBox::warning(this,tr("Esportazione dati"),tr("Qualche errore di scrittura sul file/cartella selezionata. Prova a ripetere o a cambiare cartella/nome file"),QMessageBox::Ok);
	recentDir = QFileInfo(fileName).absoluteDir().absolutePath();
    }
	
}

void HourlyEnergyPlot::exportSVG()
{
	QString fileName;
 

    fileName = QFileDialog::getSaveFileName(this, tr("Nome file da esportare"),  recentDir,"Graphic files ( *svg)");

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
           
//     QPixmap pixmap =  QPixmap::grabWidget(this);
//     QPainter painter(&generator);
      print(generator,filter);
	recentDir = QFileInfo(fileName).absoluteDir().absolutePath();
    }
	

}
void HourlyEnergyPlot::printOut()
{
	QString path = QDir::currentPath()+tr("/energiaoraria.pdf");
	 QPrinter printer(QPrinter::HighResolution);
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
void HourlyEnergyPlot::exportPNG()
{	QString fileName;
 	 
        fileName = QFileDialog::getSaveFileName(this, tr("Nome file da esportare"),  recentExportPath,"Graphic files (*.png  )");
	QFileInfo fileInfo(fileName);
	recentExportPath = fileInfo.absoluteDir().absolutePath();

    if ( !fileName.isEmpty() )
    {
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
 void HourlyEnergyPlot::exportPDF()
{
	 QString fileName;
	 fileName = QFileDialog::getSaveFileName(this, tr("Nome file da esportare"),  recentExportPath,"Acrobat ( *pdf)");
	QFileInfo fileInfo(fileName);
	recentExportPath = fileInfo.absoluteDir().absolutePath();
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

        //NOW try to open the exported file
        QDesktopServices::openUrl(fileName);

      }
}void HourlyEnergyPlot::setMode(bool i,double t)
{
	
		scaling = i;
		totalThisDay = t;
                //qDebug()<<"HE set mode"<<i<<t;
}

void HourlyEnergyPlot::setLoad(QPolygonF &a)
{
hourlyLoads = a;
}

void HourlyEnergyPlot::drawLoad()
{
	if (enableLoads)
	plotLoad->setData(hourlyLoads);
	else
	plotLoad->setRawData(0,0,0);

	replot();
	
}
void HourlyEnergyPlot::enableDrawingLoads(bool i)
{
	enableLoads = i;
	drawLoad();
}
