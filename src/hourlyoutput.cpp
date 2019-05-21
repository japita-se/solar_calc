#include "hourlyoutput.h"
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
HourlyOutput::HourlyOutput(QWidget* parent): QwtPlot(parent)
{
	createActions();
	recentExportPath = QDir::homePath();
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
	

	setCanvasBackground(QColor(Qt::white));
	// Set default settings
	set = new Settings();
	set->setTitle(tr("Energia producibile oraria"));
	set->setUnit(1);//MJ/m2
	currentUnit = 1;
	set->setAxisY(tr("Media oraria"));
	 
	set->setAxisX(tr("Ora"));
	set->setVisible(false);
	connect(set,SIGNAL(accepted()),SLOT(updateSet()));

	QwtText xlabel(set->getAxisX());
	xlabel.setFont(QFont("Times",11,QFont::Normal));
	QwtText ylabel(set->getAxisY());
	ylabel.setFont(QFont("Times",11,QFont::Normal));
	QwtText tlabel(set->getTitle());
	tlabel.setFont(QFont("Times",14,QFont::Normal));
	QwtText ulabel(u.at(set->getUnit()-1));
	ulabel.setFont(QFont("Times",11,QFont::Normal));

	setTitle(tlabel);
	setAxisTitle(QwtPlot::xBottom,xlabel);
        setAxisTitle(QwtPlot::yLeft,ylabel.text() + " " + ulabel.text());
	setAxisTitle(QwtPlot::yRight,set->getAxisYRight() + " " + u.at(set->getUnit()-1));
	this->setContextMenuPolicy(Qt::CustomContextMenu);

	connect(this,SIGNAL(customContextMenuRequested(const QPoint &  )),this,SLOT(popUpMenu(const QPoint &)));

	alignScales();
	plotPresent = false;
}
void HourlyOutput::setHourlyData(const QPolygonF &data)
{
	hourlyData = data;
// 	qDebug()<<"HEP data"<<hourlyData;
}
void HourlyOutput::draw(int mode)
{
	if (mode==1)
	{

		plotHourly->setData(hourlyData);
	}
	if (mode==0)
		plotHourly->setRawData(0,0,0);
		
replot();
}
void HourlyOutput::alignScales()
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
HourlyOutput::~HourlyOutput()
{}
void HourlyOutput::updateSet()
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
void HourlyOutput::convert(int unit)
{
	QPolygonF temp;
	double k;
	if (unit==1)
		// convert from kWh to MJ
		k = 3.6;
	if (unit==2)
		// convert from MJ to kWh
                k=1/3.6;

		for(int i=0;i<hourlyData.size();i++) {
		temp<< QPointF(i,k * hourlyData.at(i).y());
		
		}
	hourlyData.resize(0);
	hourlyData = temp;
// 	totRad = k* totRad;
	emit unitChanged(unit);
}
void HourlyOutput::popUpMenu( const QPoint &pos)
{ 
	 QMenu menu;
	QMenu exMenu(tr("&Esporta"),&menu);
 
	
	exMenu.addAction(a_export);
	exMenu.addAction(a_exportPNG);
	exMenu.addAction(a_exportPDF);
	
	 
	
	menu.addAction(a_print);
	menu.addMenu(&exMenu);
 
	
	menu.addAction(a_proprieta);
 
	 
	#ifdef Q_WS_X11
	menu.popup(pos);	
	#endif
	menu.exec(QCursor::pos());
 	 
}
void HourlyOutput::createActions()
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

	 
	connect(a_print,SIGNAL(triggered()),this,SLOT(printOut()));
	connect(a_export,SIGNAL(triggered()),this,SLOT(exportSVG()));
	connect(a_proprieta,SIGNAL(triggered()),this,SLOT(settings()));
	 
	connect(a_exportPNG,SIGNAL(triggered()),this,SLOT(exportPNG()));
	connect(a_exportPDF,SIGNAL(triggered()),this,SLOT(exportPDF()));
	 
	 
	 
}
void HourlyOutput::settings()
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
void HourlyOutput::printOut()
{
	QString path = QDir::currentPath()+tr("/energiaoraria_reale.pdf");
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
void HourlyOutput::exportPNG()
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
 void HourlyOutput::exportPDF()
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
