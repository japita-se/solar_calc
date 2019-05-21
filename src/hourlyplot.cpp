#include "hourlyplot.h"
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
HourlyPlot::HourlyPlot(QWidget* parent): QwtPlot(parent)
{
	integral = 0;
	totalThisDay =0;
	scaling = false;
	createActions();
	recentExportPath = QDir::homePath();
	recentDir = QDir::homePath();
	  u<<tr("[MJ/m2]")<<tr("[kWh/m2]");
	QwtSymbol sym2;
	sym2.setStyle(QwtSymbol::Ellipse);
	sym2.setPen(QColor(Qt::blue));
	sym2.setSize(10);
	plotHourly = new QwtPlotCurve();
	plotHourly->attach(this);
        plotHourly->setSymbol(sym2);
// 	plotHourly->setStyle(QwtPlotCurve::Sticks);
	
	plotHourly->setPen(QPen(Qt::black));

	setAxisScale(QwtPlot::xBottom,0,23);
	setMargin(2);

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
	set->setTitle(tr("Radiazione solare oraria"));
	set->setUnit(1);//MJ/m2
	currentUnit = 1;
	set->setAxisY(tr("Media oraria"));
	 
	set->setAxisX(tr("Ora"));
	set->setVisible(false);
	connect(set,SIGNAL(accepted()),SLOT(updateSet()));

	QwtText ulabel(u.at(set->getUnit()-1));
	ulabel.setFont(QFont("Times",11,QFont::Normal));
	QwtText xlabel(set->getAxisX());
	xlabel.setFont(QFont("Times",11,QFont::Normal));
	QwtText ylabel(set->getAxisY()+ " " + ulabel.text());
	ylabel.setFont(QFont("Times",11,QFont::Normal));
	QwtText tlabel(set->getTitle());
	tlabel.setFont(QFont("Times",14,QFont::Normal));
	;

	setTitle(tlabel);
	setAxisTitle(QwtPlot::xBottom,xlabel);
        setAxisTitle(QwtPlot::yLeft,ylabel );
	setAxisTitle(QwtPlot::yRight,set->getAxisYRight() + " " + u.at(set->getUnit()-1));
	this->setContextMenuPolicy(Qt::CustomContextMenu);

	connect(this,SIGNAL(customContextMenuRequested(const QPoint &  )),this,SLOT(popUpMenu(const QPoint &)));

	alignScales();
	plotPresent = false;
}
void HourlyPlot::setTime(int month,int day)
{
	if (month>=1 && month<=12)
	dateLabel = MyMath::months(month);
	if (scaling)
	set->setTitle(tr("Radiazione solare oraria scalata") + " - "  + dateLabel);
	else
	set->setTitle(tr("Radiazione solare oraria") + " - "  + dateLabel);
	updateSet();

}
void HourlyPlot::exportTXT()
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
void HourlyPlot::exportSVG()
{
	QString fileName;
 

    fileName = QFileDialog::getSaveFileName(this, tr("Nome file da esportare"),  QDir::homePath(),"Graphic files ( *svg)");

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
           
//     QPixmap pixmap =  QPixmap::grabWidget(this);
//     QPainter painter(&generator);
      print(generator,filter);
    }
	

}

void HourlyPlot::setHourlyData(const QPolygonF &data)
/* INput data are supposed to be in MJ*/
{
	double i;
	hourlyData = data;
	if (currentUnit==2)
		{
// 		qDebug()<<"HD data unit"<<currentUnit;
		convert(currentUnit);
		}
	if (scaling && totalThisDay>0.0000000002){
		i = MyMath::cumSum(hourlyData);
// 		qDebug()<<"HD data scale"<<hourlyData<<currentUnit;
		MyMath::scale(hourlyData,totalThisDay/i);
// 		qDebug()<<"HD data scale"<<hourlyData<<totalThisDay<<i;
		}
	
		integral = MyMath::cumSum(hourlyData);
              //  qDebug()<<"HP data scale total"<<integral<<totalThisDay<<i;
}
void HourlyPlot::draw(int mode)
{
	if (mode==1)
	{
		double max = MyMath::max(hourlyData);
		plotHourly->setData(hourlyData);
		QwtText label(tr("<p>Totale giornaliero = </p>") + QString("%L1").arg(integral) + u.at(set->getUnit()-1));
		label.setFont(QFont("Helvetica [Cronyx]", 10));
                totalMarker->setValue(2,max*8/10);
		totalMarker->setLabel(label);
	}
	if (mode==0){
		dateLabel="";
		plotHourly->setRawData(0,0,0);
		totalMarker->setLabel(QwtText(""));
		}
replot();
}
void HourlyPlot::alignScales()
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
HourlyPlot::~HourlyPlot()
{}
void HourlyPlot::updateSet()
{
	QString str;
	int chosenUnit = set->getUnit();
	str = u.at(chosenUnit-1);
 	#ifdef DEBUG
 	qDebug()<<"update Set"<<set->getTitle();	
 	#endif


	QwtText ulabel(u.at(set->getUnit()-1));
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
		convert(chosenUnit);
		draw(1);
		currentUnit = chosenUnit;
	}
	 
}
void HourlyPlot::convert(int unit)
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
            totalThisDay = k* totalThisDay;
    // 	integral = k * integral;
            hourlyData.resize(0);
            hourlyData = temp;
    // 	totRad = k* totRad;
            emit unitChanged(unit);
        }
}
void HourlyPlot::popUpMenu( const QPoint &pos)
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
void HourlyPlot::createActions()
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
	

	 
	connect(a_print,SIGNAL(triggered()),this,SLOT(printOut()));
	connect(a_export,SIGNAL(triggered()),this,SLOT(exportSVG()));
	connect(a_proprieta,SIGNAL(triggered()),this,SLOT(settings()));
	 
	connect(a_exportPNG,SIGNAL(triggered()),this,SLOT(exportPNG()));
	connect(a_exportPDF,SIGNAL(triggered()),this,SLOT(exportPDF()));
	connect(a_export_txt,SIGNAL(triggered()),this,SLOT(exportTXT()));
	 
	 
	 
}
void HourlyPlot::settings()
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
void HourlyPlot::printOut()
{
	QString path = QDir::currentPath()+tr("/radiazioneoraria_reale.pdf");
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
void HourlyPlot::exportPNG()
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
 void HourlyPlot::exportPDF()
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
}
void HourlyPlot::setMode(bool i,double t)
{
	
		scaling = i;
                totalThisDay = t;/*in MJ*/
               // qDebug()<<"HP set mode"<<i<<totalThisDay;
}
