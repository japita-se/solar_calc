#include "secant.h"
#include "mymath.h"
#include "cashflow.h"
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
 #include "settings.h"
#include "gridset.h"
#include "histogram_item.h"
#include <qwt_legend.h>
#include <qwt_legend_item.h>
// #include <qwt_data.h>
#include <qwt_text.h>
#include <qwt_interval_data.h>
#include <QSvgGenerator>

CashFlowPlot::CashFlowPlot(QWidget* parent)  
{
	setupUi(this);
        /*SOME GLOBAL STRING */

        loan = 0;
        simOptions << 1 << 0; //MOL medio e WACC
	QwtPainter::setDeviceClipping(false);
        gridSettings = new GridSet();
        gridSettings->setAsseX(Qt::Unchecked);
    	gridSettings->setAsseY(Qt::Unchecked);
    	connect(gridSettings,SIGNAL(accepted()),SLOT(updateGrid()));
	
        numOfDec = 1;
        MOLx = 0;
        recentDir = QDir::homePath();
 
 // Set default settings
	set = new Settings();
	set->radioMJ->setEnabled(false);
	set->radiokWh->setEnabled(false);
        set->setAxisY(tr("valore unitario"));
        set->setAxisX(tr("Anno"));
//        set->setTitle(tr("MOL"));
        set->setTitle(tr("MOL")+" - " + tr("Tasse&Sgravi"));
	connect(set,SIGNAL(accepted()),SLOT(updateSet()));

	setVan = new Settings();
	setVan->radioMJ->setEnabled(false);
        setVan->setAxisY(tr("valore unitario"));
        setVan->setTitle(tr("VAN"));
        setVan->setAxisX(tr("Anno"));
	setVan->radiokWh->setEnabled(false);
	connect(setVan,SIGNAL(accepted()),SLOT(updateSetVan()));

  

        pickerVAN = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft,QwtPicker::PointSelection , QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn,qwtVan->canvas());
        pickerVAN->setRubberBandPen(QColor(Qt::black));
        pickerVAN->setRubberBand(QwtPicker::CrossRubberBand);
        pickerVAN->setEnabled(true);

        pickerVAN->setTrackerPen(QColor(Qt::black));

   pickerMOL = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft,QwtPicker::PointSelection , QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn,qwtPlot->canvas());
   pickerMOL->setRubberBandPen(QColor(Qt::black));
   pickerMOL->setRubberBand(QwtPicker::CrossRubberBand);
   pickerMOL->setEnabled(true);
  
   pickerMOL->setTrackerPen(QColor(Qt::black));

        connect(pickerVAN, SIGNAL(moved(const QPoint &)),SLOT(movedVAN(const QPoint &)));
        connect(pickerMOL, SIGNAL(moved(const QPoint &)),SLOT(movedMOL(const QPoint &)));
// 	connect(picker, SIGNAL(selected(const QwtPolygon &)),SLOT(selected(const QwtPolygon &)));
	
	qwtVan->enableAxis(QwtPlot::yLeft,true);
	
	qwtVan->setCanvasBackground(QColor(Qt::white));
	 
// 	grid->attach(qwtVan);

// 	vanPlot 	= new QwtPlotCurve();

        legend = new QwtLegend;



        rataPlot = new HistogramItem(tr("<font color=\"red\">Rata</font>"));
	rataPlot->attach(qwtPlot);
        rataPlot->setColor(Qt::red);

        rataNPVPlot = new HistogramItem();
	rataNPVPlot->attach(qwtVan);
	rataNPVPlot->setColor(Qt::darkYellow);

	interestPlot = new HistogramItem();
	interestPlot->attach(qwtPlot);
	interestPlot->setColor(Qt::darkYellow);

	interestNPVPlot = new HistogramItem();
	interestNPVPlot->attach(qwtVan);
	interestNPVPlot->setColor(Qt::darkYellow);
	
        vanPlot		= new HistogramItem(tr("VAN"));
	vanPlot->attach(qwtVan);
	vanPlot->setColor(Qt::darkGray);
	 
// 	rawPlot = new QwtPlotCurve();
//      rawPlot = new HistogramItem(tr("MOL"));
        rawPlot = new HistogramItem(tr("MOL")+" - " + tr("Tasse&Sgravi"));
	rawPlot->attach(qwtPlot);
	rawPlot->setColor(Qt::darkGray);

// 	csPlot = new QwtPlotCurve();
// 	csPlot->setPen(QPen(Qt::blue));
// 	csPlot->attach(qwtPlot);

	qwtPlot->setCanvasBackground(QColor(Qt::white));
//   	canvas()->setMouseTracking(true);
// 	canvas()->setTrackerMode(AlwaysOn);
   
  // plotLayout()->setAlignCanvasToScales(true);

        qwtPlot->insertLegend(legend,QwtPlot::BottomLegend);
  createActions();
  setPlots(20);

  qwtPlot->setContextMenuPolicy(Qt::CustomContextMenu);
  qwtVan->setContextMenuPolicy(Qt::CustomContextMenu);
  //tabWidget->widget(0)->setContextMenuPolicy(Qt::CustomContextMenu);
  //connect(tabWidget->widget(0),SIGNAL(customContextMenuRequested(const QPoint &  )),this,SLOT(popUpMenu(const QPoint &)));
  connect(qwtPlot,SIGNAL(customContextMenuRequested(const QPoint &  )),this,SLOT(popUpMenu(const QPoint &)));
  connect(qwtVan,SIGNAL(customContextMenuRequested(const QPoint &  )),this,SLOT(popUpMenuVAN(const QPoint &)));

  connect(checkCumulative,SIGNAL(stateChanged(int)),SLOT(changeDraw(int)));
  connect(checkRata,SIGNAL(stateChanged(int)),SLOT(toggleInterestPlot(int)));
   alignScales();
   drawInterestFlag = false;
   s="";
   sOther ="";

    grid = new QwtPlotGrid;
    grid->enableX(false);
    grid->enableXMin(false);
    grid->enableY(false);
    grid->enableYMin(false);
    grid->setMajPen(QPen(Qt::gray, 0, Qt::DotLine));
    grid->setMinPen(QPen(Qt::gray, 0 , Qt::DotLine));
    grid->attach(qwtPlot);
	
    grid2 = new QwtPlotGrid;
    grid2->enableX(false);
    grid2->enableXMin(false);
    grid2->enableY(false);
    grid2->enableYMin(false);
    grid2->setMajPen(QPen(Qt::gray, 0, Qt::DotLine));
    grid2->setMinPen(QPen(Qt::gray, 0 , Qt::DotLine));
    grid2->attach(qwtVan);
}
void CashFlowPlot::toggleInterestPlot(int state)
{	

	if (state==Qt::Checked)
		drawInterestFlag = true;
	else
		drawInterestFlag = false;
        //drawInterest(1);
        //drawInterestNPV(1);
        drawRata(1);
        drawFlowCash(1);
        drawNPV(1);
		
}
void CashFlowPlot::setPlots(int years)
{
	
  	
	QwtText xlabel(tr("Mese"));
	QwtText ylabel(tr("c/[kWh]"));
	ylabel.setFont(QFont("Times",12,QFont::Normal));
	xlabel.setFont(QFont("Times",12,QFont::Normal));

	

	
  	
	 

        QwtText tlabel2(tr("VAN"));
	tlabel2.setFont(QFont("Times",12,QFont::Normal));
	QwtText xlabel2(tr("Anno"));
        QwtText ylabel2(tr("valore unitario"));
        ylabel2.setFont(QFont("Times",10,QFont::Normal));
        xlabel2.setFont(QFont("Times",10,QFont::Normal));
	setVan->setTitle(ylabel2.text());
	
	qwtVan->setAxisTitle(QwtPlot::xBottom,xlabel2);
        qwtVan->setAxisTitle(QwtPlot::yLeft,ylabel2);
	qwtVan->setTitle(tlabel2);
//         qwtVan->setAxisScale(QwtPlot::xBottom,0,years);
  	 
        //QwtText tlabel3(tr("MOL"));
        QwtText tlabel3(tr("MOL")+" - " + tr("Tasse&Sgravi"));
        tlabel3.setFont(QFont("Times",12,QFont::Normal));
	QwtText xlabel3(tr("Anno"));
        QwtText ylabel3(tr("valore  unitario"));
        ylabel3.setFont(QFont("Times",10,QFont::Normal));
        xlabel3.setFont(QFont("Times",10,QFont::Normal));
	set->setTitle(ylabel3.text());
	qwtPlot->setAxisTitle(QwtPlot::xBottom,xlabel3);
        qwtPlot->setAxisTitle(QwtPlot::yLeft,ylabel3);
	qwtPlot->setTitle(tlabel3);
//         qwtPlot->setAxisScale(QwtPlot::xBottom,0,years);

        qwtPlot->setMargin(30);
        qwtVan->setMargin(30);
        qwtPlot->replot();
        qwtVan->replot();
//         qDebug()<<"ECO setPlots scale";
}
void CashFlowPlot::exportMOLTXT()
{
    exportTXT(0);
}
void CashFlowPlot::exportVANTXT()
{
    exportTXT(1);
}
void CashFlowPlot::exportTXT(int which)
{

        QString fileName;
        QPolygonF toPrint;

    fileName = QFileDialog::getSaveFileName(this, tr("Nome file da esportare"),  recentDir,"Text files ( *txt)");

    if ( !fileName.isEmpty() )
    {
        fileName = MyMath::checkFormat(fileName,"txt");

        if (which == 1)
                toPrint = npvToUse ;
        if (which == 0)
                toPrint = rawcashToUse ;



        if (!MyMath::exportToText(fileName,toPrint))
        QMessageBox::warning(this,tr("Esportazione dati"),tr("Qualche errore di scrittura sul file/cartella selezionata. Prova a ripetere o a cambiare cartella/nome file"),QMessageBox::Ok);
        recentDir = QFileInfo(fileName).absoluteDir().absolutePath();
    }

}
void CashFlowPlot::createActions()
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

        a_print_van       =  new QAction(tr("&Stampa"),this);
        a_print_van->setShortcut(tr("Ctrl+P"));
        a_export_van      = new QAction(tr("&SVG"),this);

        a_export_van->setShortcut(tr("Ctrl+S+V"));

        //a_proprieta   = new QAction(tr("Impostazioni"),this);

        //a_create_grid = new QAction(tr("Griglia"),this);

        a_exportPNG_van   = new QAction(tr("PNG"),this);

        a_exportPDF_van = new QAction(tr("PDF"),this);
        a_exportPDF_van->setIcon(QIcon(":/images/pdf.jpeg"));

        a_export_txt_van = new QAction(tr("File di testo"),this);
        a_export_txt_van->setIcon(QIcon(":/images/text.png"));



        connect(a_print,SIGNAL(triggered()),this,SLOT(printOutMOL()));
        connect(a_export,SIGNAL(triggered()),this,SLOT(exportMOLSVG()));
	 connect(a_proprieta,SIGNAL(triggered()),this,SLOT(settings()));
 	connect(a_create_grid,SIGNAL(triggered()),this,SLOT(gridset()));
        connect(a_exportPNG,SIGNAL(triggered()),this,SLOT(exportMOLPNG()));
        connect(a_exportPDF,SIGNAL(triggered()),this,SLOT(exportMOLPDF()));
        connect(a_export_txt,SIGNAL(triggered()),this,SLOT(exportMOLTXT()));

        connect(a_print_van,SIGNAL(triggered()),this,SLOT(printOutVAN()));
        connect(a_export_van,SIGNAL(triggered()),this,SLOT(exportVANSVG()));

        connect(a_exportPNG_van,SIGNAL(triggered()),this,SLOT(exportVANPNG()));
        connect(a_exportPDF_van,SIGNAL(triggered()),this,SLOT(exportVANPDF()));
        connect(a_export_txt_van,SIGNAL(triggered()),this,SLOT(exportVANTXT()));
	 
}
void CashFlowPlot::gridset()
{
	if (!gridSettings-isVisible())
	gridSettings->show();
}
void CashFlowPlot::exportMOLSVG()
{
    exportSVG(0);
}
void CashFlowPlot::exportVANSVG()
{
    exportSVG(1);
}

void CashFlowPlot::exportSVG(int which)
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
  if (which == 0)
      qwtPlot->print(generator,filter);
  if (which == 1)
      qwtVan->print(generator,filter);
}
}
void CashFlowPlot::printOutMOL()
{
    printOut(0);
}void CashFlowPlot::printOutVAN()
{
    printOut(1);
}
 void CashFlowPlot::printOut(int which)
{
         QPrinter printer ;
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
        
            int options = QwtPlotPrintFilter::PrintAll;
            options &= ~QwtPlotPrintFilter::PrintBackground;
            options |= QwtPlotPrintFilter::PrintFrameWithScales;
            filter.setOptions(options);
        
        if (which == 1)
        	qwtVan->print(printer,filter );
        if (which == 0)
		qwtPlot->print(printer,filter );
	
	}
}
 void CashFlowPlot::exportMOLPDF()
 {
     exportPDF(0);
 }
 void CashFlowPlot::exportVANPDF()
 {
     qDebug()<<"CASH EXPORT VAN";
     exportPDF(1);
 }
void CashFlowPlot::exportPDF(int which)
{
	 QString fileName;
	 fileName = QFileDialog::getSaveFileName(this, tr("Nome file da esportare"),   recentExportPath,"Acrobat ( *pdf)");
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
        

// 	qwtVan->print(printer,filter);
// 	printer.newPage();
// 	qwtPlot->print(printer,filter);

            QPainter painter;
            painter.begin(&printer);


            if (which == 0)
               qwtPlot->print(&painter,printer.pageRect(),filter);
            if (which == 1)
                qwtVan->print(&painter,printer.pageRect(),filter);
            painter.end();
            //NOW try to open the exported file
            QDesktopServices::openUrl(fileName);
      }
}
void CashFlowPlot::popUpMenuVAN(const QPoint &pos)
{
    QMenu menu;
    QMenu exMenu(tr("&Esporta"),&menu);


    exMenu.addAction(a_export_van);
    exMenu.addAction(a_exportPNG_van);
    exMenu.addAction(a_exportPDF_van);
    exMenu.addAction(a_export_txt_van);


// 	menu.addAction(a_undo_combine);
    menu.addAction(a_print_van);
    menu.addMenu(&exMenu);


    menu.addAction(a_create_grid);
    menu.addAction(a_proprieta);
    cursorPos = this->mapFromGlobal(QCursor::pos());
    #ifdef Q_WS_X11
    menu.popup(pos);
    #endif
    menu.exec(QCursor::pos());
}

void CashFlowPlot::popUpMenu(const QPoint &pos)
{ 
// 	cursorPos = this->mapFromGlobal(QCursor::pos());
 	QMenu menu;
	QMenu exMenu(tr("&Esporta"),&menu);
	
	
	exMenu.addAction(a_export);
	exMenu.addAction(a_exportPNG);
	exMenu.addAction(a_exportPDF);
        exMenu.addAction(a_export_txt);
	
		
// 	menu.addAction(a_undo_combine);
	menu.addAction(a_print);
	menu.addMenu(&exMenu);
		
	
 	menu.addAction(a_create_grid);
	menu.addAction(a_proprieta);
	cursorPos = this->mapFromGlobal(QCursor::pos());
	#ifdef Q_WS_X11
	menu.popup(pos);	
	#endif
	menu.exec(QCursor::pos());

}
void CashFlowPlot::exportMOLPNG()
{
    exportPNG(0);
}
void CashFlowPlot::exportVANPNG()
{
    exportPNG(1);
}

void CashFlowPlot::exportPNG(int which)
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
	QPixmap pixmap(1024,800);
	pixmap.fill(Qt::white);
      	
        //if (cursorPos.y()<=qwtVan->geometry().y()+qwtVan->geometry().height())
                //qwtVan->print(pixmap,filter );
        //if (cursorPos.y()>qwtVan->geometry().y()+qwtVan->geometry().height())

        if (which==0)
            qwtPlot->print(pixmap,filter );
        if (which==1)
            qwtVan->print(pixmap,filter );

	 if ( pixmap.save(fileName, "png" ))
                qDebug()<<"Ok"<<cursorPos.y()<<qwtVan->geometry().y()+qwtVan->geometry().height();
  	 else
		qDebug()<<"Error";
	 
    
}
}
void CashFlowPlot::movedMOL(const QPoint &pos)
{
//	qDebug()<<pos;
        pickerMOL->rubberBand();
}
void CashFlowPlot::movedVAN(const QPoint &pos)
{
//	qDebug()<<pos;
        pickerVAN->rubberBand();
}
 QwtPlot* CashFlowPlot::vanDiagram()
{
	return qwtVan;
}
QwtPlot* CashFlowPlot::rawDiagram()
{
	return qwtPlot;
}
void CashFlowPlot::alignScales()
{
    // The code below shows how to align the scales to
    // the canvas frame, but is also a good example demonstrating
    // why the spreaded API needs polishing.

    
    
    qwtVan->canvas()->setFrameStyle(QFrame::Box | QFrame::Plain );
    qwtVan->canvas()->setLineWidth(1);
    qwtPlot->canvas()->setFrameStyle(QFrame::Box | QFrame::Plain );
    qwtPlot->canvas()->setLineWidth(1);

    
for ( int i = 0; i < qwtVan->QwtPlot::axisCnt; i++ )
    {
         QwtScaleWidget *scaleWidget = (QwtScaleWidget *)(qwtVan->axisWidget(i));
        if ( scaleWidget )
            scaleWidget->setMargin(0);

         QwtScaleDraw *scaleDraw = (QwtScaleDraw *)qwtVan->axisScaleDraw(i);
        if ( scaleDraw )
           scaleDraw->enableComponent(QwtAbstractScaleDraw::Backbone, false);
    }
for ( int i = 0; i < qwtPlot->QwtPlot::axisCnt; i++ )
    {
         QwtScaleWidget *scaleWidget = (QwtScaleWidget *)(qwtPlot->axisWidget(i));
        if ( scaleWidget )
            scaleWidget->setMargin(0);

         QwtScaleDraw *scaleDraw = (QwtScaleDraw *)qwtPlot->axisScaleDraw(i);
        if ( scaleDraw )
           scaleDraw->enableComponent(QwtAbstractScaleDraw::Backbone, false);
    }
}

CashFlowPlot::~CashFlowPlot()
{
}
void CashFlowPlot::drawRataNPV(int mode)
{
     if (mode==1){
	QwtArray<QwtDoubleInterval> intervals(rataNPV.size());
	QwtArray<double> values(rataNPV.size());
        double pos=0.5;
	if (drawInterestFlag){
		for(int i=0;i<(int)rataNPV.size();i++)
		{
			
				intervals[i] = QwtDoubleInterval(0.5+pos,pos+1);
			
			pos += 1;
			values[i] = rataNPV.at(i).y();
		}
		rataNPVPlot->setData(QwtIntervalData(intervals, values));
	}else
		rataNPVPlot->setData(QwtIntervalData());

//     rawPlot->setData(x,y,size);
//       vanPlot->setData(npv);
    }else
     {
        rataNPVPlot->setData(QwtIntervalData());
    }
      qwtVan->replot();
}
void CashFlowPlot::drawRata(int mode)
{
    QPolygonF a;
    if (checkCumulative->isChecked())
        a = rataCum;
    else
        a = rata;
     if (mode==1){
        QwtArray<QwtDoubleInterval> intervals(a.size());
        QwtArray<double> values(a.size());
        double pos=0.5;
	if (drawInterestFlag){
                for(int i=0;i<(int)a.size() ;i++)
		{
			
				intervals[i] = QwtDoubleInterval(0.5+pos,pos+1);
			
			pos += 1;
                        values[i] = a.at(i).y();
		}
		rataPlot->setData(QwtIntervalData(intervals, values));

	}else
        {
		rataPlot->setData(QwtIntervalData());

            }

//     rawPlot->setData(x,y,size);
//       vanPlot->setData(npv);
    }else
     {
        rataPlot->setData(QwtIntervalData());
        }
      qwtPlot->replot();
}
void CashFlowPlot::drawInterestNPV(int mode)
{
    if (mode==1){
        QwtArray<QwtDoubleInterval> intervals(interestNPV.size()+1);
	QwtArray<double> values(interestNPV.size());
	double pos=0;
	if (drawInterestFlag){
		for(int i=0;i<(int)interestNPV.size();i++)
		{
			
				intervals[i] = QwtDoubleInterval(0.5+pos,pos+1);
			
			pos += 1;
			values[i] = interestNPV.at(i).y();
		}
		interestNPVPlot->setData(QwtIntervalData(intervals, values));
	}else
		interestNPVPlot->setData(QwtIntervalData());

//     rawPlot->setData(x,y,size);
//       vanPlot->setData(npv);
    }else
    {
                interestNPVPlot->setData(QwtIntervalData());
     }
      qwtVan->replot();
}
void CashFlowPlot::drawNPV(int mode)
{
    if (mode==1){
          qwtVan->setAxisScale(QwtPlot::xBottom,0,npvToUse.size()+1);
        changeDrawData();
        QwtArray<QwtDoubleInterval> intervals(npvToUse.size());
        QwtArray<double> values(npvToUse.size());
        double pos=0.5;
        for(int i=0;i<(int)npvToUse.size();i++)
	{
//		if (drawInterestFlag)
//			intervals[i] = QwtDoubleInterval(pos, pos + 0.5);
//		else
			intervals[i] = QwtDoubleInterval(pos, pos + 1);
		pos += 1;
                values[i] = npvToUse.at(i).y();
	}
	vanPlot->setData(QwtIntervalData(intervals, values));

// 	vanData = npv;
//     rawPlot->setData(x,y,size);
//       vanPlot->setData(npv);


// updateTable();
}
    else
    {
        vanPlot->setData(QwtIntervalData());
    }
    qwtVan->replot();
}
void CashFlowPlot::drawFlowCash(int mode)
{
    if (mode==1){
        qwtPlot->setAxisScale(QwtPlot::xBottom,0,flowToUse.size()+1);
        changeDrawData();
        QwtArray<QwtDoubleInterval> intervals(flowToUse.size());
        QwtArray<double> values(flowToUse.size());
        double pos=0.5;
        for(int i=0;i<(int)flowToUse.size() ;i++)
	{
	
		if (drawInterestFlag)
			intervals[i] = QwtDoubleInterval(pos, pos + 0.5);
		else
			intervals[i] = QwtDoubleInterval(pos, pos + 1);
		pos += 1;
              //  values[i] = rawcashToUse.at(i).y();
              values[i] = flowToUse.at(i).y();
	}
	rawPlot->setData(QwtIntervalData(intervals, values));


    }
    else
    {
        rawPlot->setData(QwtIntervalData());
    }
    qwtPlot->replot();
	
}
void CashFlowPlot::drawInterest(int mode)
{
    if (mode==1){
	QwtArray<QwtDoubleInterval> intervals(interest.size());
	QwtArray<double> values(interest.size());
	double pos=0;
	if (drawInterestFlag){
		for(int i=0;i<(int)interest.size();i++)
		{
			
				intervals[i] = QwtDoubleInterval(0.5+pos, pos + 1);
			
			pos += 1;
			values[i] = interest.at(i).y();
		}
		interestPlot->setData(QwtIntervalData(intervals, values));
	}
	else
		interestPlot->setData(QwtIntervalData());
// 	interestData = data;
		
//  	rawPlot->setData(data);

}
    else
    {
                interestPlot->setData(QwtIntervalData());
    }
    qwtPlot->replot();
}
void CashFlowPlot::updateGrid()
{
// 	qDebug()<<"Sono in grid";
	if (gridSettings->getAsseX()==Qt::Checked) {
// 	qDebug()<<"Griglia vera";
	 	grid->enableXMin(true);
   	 	grid->enableX(true);
    	 	grid->enableXMin(true);

		grid2->enableXMin(true);
   	 	grid2->enableX(true);
    	 	grid2->enableXMin(true);
	} 
	else	
	{
		grid->enableXMin(false);
   	 	grid->enableX(false);
    	 	grid->enableXMin(false);
		
		grid2->enableXMin(false);
   	 	grid2->enableX(false);
    	 	grid2->enableXMin(false);
	}
	if (gridSettings->getAsseY()==Qt::Checked) {
	 	grid->enableYMin(true);
   	 	grid->enableY(true);
    	 	grid->enableYMin(true);

		grid2->enableYMin(true);
   	 	grid2->enableY(true);
    	 	grid2->enableYMin(true);
	}
	else	
	{
		grid->enableYMin(false);
   	 	grid->enableY(false);
    	 	grid->enableYMin(false);

		grid2->enableYMin(false);
   	 	grid2->enableY(false);
    	 	grid2->enableYMin(false);
	}
qwtPlot->replot();
qwtVan->replot();
}
void CashFlowPlot::updateTable()
{

// 	QString s;
    QString sCs,sTop,headerCS,cusColumn,syString,suggY;
        s=sCs=sOther=sTop=cusColumn="";
        QString preamble = "<table border=1   cellspacing=\"0\" cellpadding=\"3\" bordercolor=\"#980000\" >";
        QString preambleTop = "<table border=0 width=\"40%\" cellspacing=\"0\" cellpadding=\"3\" bordercolor=\"#980000\" >";
        QString header   = "<tr  bgcolor=\"#C89800\"><td >" + tr("Anno") +  "</td><td>" + tr("Incentivo")    + "</td><td >"  ;

        QString preambleCS = warnings + "<br/>" +
                             "<table border=1   cellspacing=\"0\" cellpadding=\"3\" bordercolor=\"#980000\" >";

        /*********** SUGGESTED FIN YEARS ****************/
int  sy = suggestFinYears();
//int na = MyMath::npvCross(npvToUse);
if (sy >0){
        syString = tr("Anni di finanziamento suggeriti");
        suggY       = QString::number(sy);
    }
    else {
        if (sy == 0 )
            // Il sistema si autofinanzia //
            syString = tr("Possibile sistema autofinanziabile (fin. sconsigliato)");
        if (sy < 0 )
            // Il sistema non e' finanziabile//
            syString = tr("Possibile sistema non finanziabile");

        suggY       = "";
    }



        if (eco.regime == SSPIT) {
            cusColumn = tr("Cus(UM)");

        if (!eco.credit )
        headerCS   = "<tr  bgcolor=\"#C89800\"><td >"              +
                             tr("Anno") + "</td><td >"             +
                             tr("En. prodotta (kWh)") +"</td><td>" +
                             tr("En. immessa (kWh)")+ "</td><td>"   +
                             tr("En. prelevata (kWh)")+ "</td><td>"   +
                             tr("Autoconsumo (kWh)") +"</td><td>"  +
                             tr("Cei(UM)")      + "</td><td>"          +
                             tr("Oe(UM)")       + "</td><td>"          +
                             cusColumn      + "</td></tr/>";
        else
            headerCS   = "<tr  bgcolor=\"#C89800\"><td >"  +
                                 tr("Anno") + "</td><td >" +
                                 tr("En. prodotta (kWh)")  +"</td><td>" +
                                 tr("En. immessa (kWh)")+ "</td><td>"   +
                                 tr("En. prelevata (kWh)")+ "</td><td>"   +
                                 tr("Autoconsumo (kWh)") +"</td><td>"  +
                                 tr("Cei(UM)")    + "</td><td>"            +
                                 tr("Oe(UM)")     + "</td><td>"                +
                                 cusColumn    + "</td></tr>" ;

      }
        if (eco.regime == Vendita){
            cusColumn    = tr("Corrispettivi(UM)");
            headerCS   = "<tr  bgcolor=\"#C89800\"><td >"              +
                                 tr("Anno") + "</td><td >"             +
                                 tr("En. prodotta (kWh)") +"</td><td>" +
                                 tr("En. immessa (kWh)")+ "</td><td>"   +
                                 tr("En. prelevata (kWh)")+ "</td><td>"   +
                                 tr("Autoconsumo (kWh)") +"</td><td>"  +

                                 cusColumn      + "</td></tr>";

        }

        QString headerTop  = "<tr><td width=80%>" + tr("Finanziamento") + "</td><td>" + QString("%L1").arg(loan,0,'f',2) + "</td><</tr>";
        if (eco.loan > 0.0)
                headerTop += "<tr><td width=80%>" + tr("Tasso") + "</td> <td>"         + QString("%L1").arg(eco.loanInterestRate,0,'f',2) + "%</td</tr>";
                headerTop += "<tr style = \"font-weight:bold; \"><td width=80%> "+
                             tr("Anni finanziamento")      + "</td><td>"     +
                             QString::number(eco.loan!=0 ? eco.loanYears : 0)+ "</td></tr>";
                if (eco.loan > 0.00)
                      headerTop += "<tr style = \"font-weight:bold \"><td width=80%>" +   syString + "</td><td width=80%>"         +
                             suggY + "</td></tr>";

         sTop = preambleTop + headerTop;

        QString headerOther = "<tr  bgcolor=\"#C89800\"><td >" +
                              tr("Anno") + "</td><td >"        +
                              tr("Ammortamento") + "</td><td>" +
                              tr("MON")  + "</td><td >"        +
                              tr("IVA")  + "</td><td >"        +
                              tr("IRPEF")  + "</td><td >"      +
                              tr("IRAP")  + "</td><td >"       +
                              tr("IRES")  + "</td><td >"       +
                              tr(" Tasse&Sgravi")  + "</td><td >"       +
                              tr("Flusso di Cassa")  + "</td><td>"      +
                              tr("VAN") + "</td></tr>";
	if (eco.regime==SSPIT)
          header+= tr("CS") +"</td><td>";
	if (eco.regime==Vendita)
            header+= tr("Vendita En.") +"</td><td>";

        //Liquidazione credito?
        if (eco.credit && eco.regime==SSPIT)
           header +=    tr("RIB lordo") + "</td><td>" +
                        tr("Crediti liq.") + "</td><td>" +
                        tr("Costi di sistema(*)") + "</td><td>" +
                        tr("Rata") + "</td><td>" +
                        tr("Interessi") + "</td><td>" +
                        tr("MOL") + "</td><td>" +
                        tr("MOL Cumulato") + "</td></tr>";

        else

            header +=    tr("Risparmio in bolletta lordo") + "</td><td>" +
                         tr("Costi di sistema(*)") + "</td><td>" +
                         tr("Rata") + "</td><td>" +
                         tr("Interessi") + "</td><td>" +
                         tr("MOL") + "</td><td>" +
                         tr("MOL Cumulato") + "</td></tr>";


        s    += preamble + header;
        sCs  += preambleCS + headerCS;
        sOther+= preamble + headerOther;
       // qDebug()<<"Cash decimal" <<numOfDec;
 	sanityCheck();
	bool foundRoi = false;
        /* Every point in raw size represent data for one year */
	for(int i=0;i< rawcash.size();i++) {
                if ((npvToUse.at(i).y()>0) && (!foundRoi))
		{
                        s+="<tr bgcolor=\"#52d26b\"><td>" + QString("%1").arg(i+1) + "</td>";//ROI
                        sOther+="<tr bgcolor=\"#52d26b\"><td ALIGN=\"right\">" + QString("%1").arg(i+1) + "</td>";
			foundRoi = true;
		}
                else{
                        s+="<tr><td ALIGN=\"right\">" + QString("%1").arg(i+1) + "</td>";
                        sOther+="<tr><td ALIGN=\"right\">" + QString("%1").arg(i+1) + "</td>";
                    }

                sCs+="<tr>   <td ALIGN=\"right\">" + QString("%1").arg(i+1) + "</td>";


// 		s+="<td>" + QString("%L1").arg(produced.at(i).y(),0,'f',3) + "</td>";
// 		s+="<td>" + QString("%L1").arg(consumed.at(i).y(),0,'f',3) + "</td>";
                s+="<td ALIGN=\"right\">" + QString("%L1").arg(bonus.at(i).y(),0,'f',numOfDec) + "</td>";

 /**************************TABELLA DETTAGLI***********************/
                if ((eco.regime==SSPIT) ){
                        s+="<td ALIGN=\"right\">" + QString("%L1").arg(cs.at(i).y(),0,'f',numOfDec) + "</td>";
                        sCs+="<td ALIGN=\"right\">" + QString("%L1").arg(produced.at(i).y(),0,'f',numOfDec) + "</td>";
                        sCs+="<td ALIGN=\"right\">" + QString("%L1").arg(injected.at(i).y(),0,'f',numOfDec) + "</td>";
                        sCs+="<td ALIGN=\"right\">" + QString("%L1").arg(fetched.at(i).y(),0,'f',numOfDec) + "</td>";
                        sCs+="<td ALIGN=\"right\">" + QString("%L1").arg(consumed.at(i).y(),0,'f',numOfDec) + "</td>";
                        sCs+="<td ALIGN=\"right\">" + QString("%L1").arg(cei.at(i).y(),0,'f',numOfDec) + "</td>";
                        sCs+="<td ALIGN=\"right\">" + QString("%L1").arg(oe.at(i).y(),0,'f',numOfDec) + "</td>";

                        if (cusOrCor.at(i).y()<0)
                        sCs+="<td ALIGN=\"right\">" + tr("Non applicabile") + "</td>";
                        else
                        sCs+="<td ALIGN=\"right\">" + QString("%L1").arg(cusOrCor.at(i).y(),0,'f',numOfDec) + "</td>";

//                        if (!eco.credit )
//                        sCs+="<td ALIGN=\"right\">" + QString("%L1").arg(credit.at(i).y(),0,'f',numOfDec) + "</td></tr>";
                    }
 /*****************TABELLA DETTAGLI VENDITA***************************/
                if ((eco.regime==Vendita) ){
                        s+="<td ALIGN=\"right\">" + QString("%L1").arg(cs.at(i).y(),0,'f',numOfDec) + "</td>";
                        sCs+="<td ALIGN=\"right\">" + QString("%L1").arg(produced.at(i).y(),0,'f',numOfDec) + "</td>";
                        sCs+="<td ALIGN=\"right\">" + QString("%L1").arg(injected.at(i).y(),0,'f',numOfDec) + "</td>";
                         sCs+="<td ALIGN=\"right\">" + QString("%L1").arg(fetched.at(i).y(),0,'f',numOfDec) + "</td>";
                        sCs+="<td ALIGN=\"right\">" + QString("%L1").arg(consumed.at(i).y(),0,'f',numOfDec) + "</td>";
                        sCs+="<td ALIGN=\"right\">" + QString("%L1").arg(cusOrCor.at(i).y(),0,'f',numOfDec) + "</td></tr>";


                    }

/***********************SECONDA TABELLA********************************/

                sOther+="<td ALIGN=\"right\">" + QString("%L1").arg(amm.at(i).y(),0,'f',numOfDec) + "</td>";
                sOther+="<td ALIGN=\"right\">" + QString("%L1").arg(rawcash.at(i).y()-amm.at(i).y(),0,'f',numOfDec) + "</td>";
                sOther+="<td ALIGN=\"right\">" + QString("%L1").arg(iva.at(i).y(),0,'f',numOfDec) + "</td>";
                sOther+="<td ALIGN=\"right\">" + QString("%L1").arg(irpef.at(i).y(),0,'f',numOfDec) + "</td>";
                sOther+="<td ALIGN=\"right\">" + QString("%L1").arg(irap.at(i).y(),0,'f',numOfDec) + "</td>";
               sOther+="<td ALIGN=\"right\">" + QString("%L1").arg(ires.at(i).y(),0,'f',numOfDec) + "</td>";
               sOther+="<td ALIGN=\"right\">" + QString("%L1").arg(tasse.at(i).y(),0,'f',numOfDec) + "</td>";
               sOther+="<td ALIGN=\"right\">" + QString("%L1").arg(tassato.at(i).y(),0,'f',numOfDec) + "</td>";
               sOther+="<td ALIGN=\"right\">" + QString("%L1").arg(npvToUse.at(i).y(),0,'f',numOfDec) + "</td></tr>";

/**********************PRIMA TABELLA **********************************/

               s+="<td ALIGN=\"right\">" + QString("%L1").arg(savingsEn.at(i).y(),0,'f',numOfDec) + "</td>";
               if (eco.credit && eco.regime==SSPIT)
                   s+="<td ALIGN=\"right\">" + QString("%L1").arg(credit.at(i).y(),0,'f',numOfDec) + "</td>";

               s+="<td ALIGN=\"right\">" + QString("%L1").arg(yearlyCost.at(i).y(),0,'f',numOfDec) + "</td>";

               s+="<td ALIGN=\"right\">" + QString("%L1").arg(rata.at(i).y(),0,'f',numOfDec) + "</td>";
                s+="<td ALIGN=\"right\">" + QString("%L1").arg(interest.at(i).y(),0,'f',numOfDec) + "</td>";

                s+="<td ALIGN=\"right\">" + QString("%L1").arg(rawcash.at(i).y(),0,'f',numOfDec) + "</td>";
                s+="<td ALIGN=\"right\">" + QString("%L1").arg(rawcashCum.at(i).y(),0,'f',numOfDec) + "</td></tr>";

	}
        s      += "</table>";
        sTop   += "</table>";
        if (eco.regime==SSPIT)
        s+=tr("<p>(*) Costi Annuali Attualizzati = Costi di manutenzione + Affitti + Assicurazione + Altri costi") + "<br/>" + tr("Margine Operativo Lordo (MOL) = Incentivi + CS + RIB + Crediti")+ "</p>" ;
        if (eco.regime==Vendita)
        s+=tr("<p>(*) Costi Annuali Attualizzati = Costi di manutenzione + Affitti + Assicurazione + Altri costi") + "<br/>" + tr("Margine Operativo Lordo (MOL) = Incentivi + Vendita + RIB + Crediti")+ "</p>" ;
      //  s+= tr("(**) Il sistema aggiunge l'IVA effettivamente versata") + "</p>";
        sCs    += "</table><br/><br/>" +
                  tr("<p>UM = Unit&agrave; monetaria corrente</p>");
        sOther += "</table><br/><p>" +
                  tr("MON = MOL - Ammortamenti") + "<br/>" +
                  tr("Flusso di cassa =  MOL - Quota non finanziata - Tasse&Sgravi - Rata") + "<br/>" +
                  tr("VAN = Valore netto attualizzato comprensivo di beneficio fiscale a seguito del finanziamento") +
                  "</p>";




        textEdit->setHtml(sTop + s+"<br/><br/><br/>" + sOther);
  //       textEdit->setHtml(s +"<br/><br/>" + tr("Ammortamento = ") + QString("%L1").arg(amm,0,'f',numOfDec));

        textEditCS->setHtml(sCs);

}
void CashFlowPlot::sanityCheck()
{
	if (consumed.size()<rawcash.size())
		consumed.insert(consumed.size(),rawcash.size()-consumed.size(),QPointF(0,0));

	if (produced.size()<rawcash.size())
		produced.insert(produced.size(),rawcash.size()-produced.size(),QPointF(0,0));

	if (bonus.size()<rawcash.size())
		bonus.insert(bonus.size(),rawcash.size()-bonus.size(),QPointF(0,0));
	
	if (cs.size()<rawcash.size())
		cs.insert(cs.size(),rawcash.size()-cs.size(),QPointF(0,0));
}
void CashFlowPlot::setSelfConsumed(const QPolygonF &a)
        /* Self Consumed */
{
	consumed = a;

}
void CashFlowPlot::setProduced(const QPolygonF &a)
{
	produced = a;
        //qDebug()<<"CASHFLOW produced"<<a;
}
void CashFlowPlot::setBonus(const QPolygonF &a)
{
	bonus = a;
        //qDebug()<<"CASHFLOW bonus"<<a;
}
void CashFlowPlot::setCredit(const QPolygonF &a)
{
        credit = a;

}
void CashFlowPlot::setInjected(const QPolygonF &a)
{
        injected = a;

}
void CashFlowPlot::setCUSorCor(const QPolygonF &a)
{
    // CUS or Cor according to the recime
    // Cor = Corrispettivi passivi/attivi
        cusOrCor = a;


}
void CashFlowPlot::setOE(const QPolygonF &a)
{
        oe = a;

}
void CashFlowPlot::setCei(const QPolygonF &a)
{
        cei = a;
        if (a.size()==0){
            cei.fill(QPointF(0,0),rawcash.size());
        qDebug()<<"WARNING IN CASH cei size"<<cei.size();
    }
}
void CashFlowPlot::setCS(const QPolygonF &a)
{
	cs = a;

         if (a.size()==0){
        qDebug()<<"WARNING IN CASH cs size"<<cs.size();
    }
}
void CashFlowPlot::setRawCash(const QPolygonF &a)
{
        rawcash      = a;

        rawPlusTax   = MyMath::subtract(rawcash,tasse);
        rawPlusTaxCum   = MyMath::cumulative(rawPlusTax);
        flowToUse        = rawPlusTax;

        rawcashToUse = rawcash;
        rawcashCum = MyMath::cumulative(rawcash);
}
void CashFlowPlot::setInterest(const QPolygonF &a)
{
	interest = a;
}
void CashFlowPlot::setInterestNPV(const QPolygonF &a)
{
	interestNPV = a;
}
void CashFlowPlot::setNPV(const QPolygonF &a)
{
	npv = a;
        npvCum = MyMath::cumulative(npv);
        npvToUse = npvCum;
}
void CashFlowPlot::setRataNPV(const QPolygonF &a)
{
	rataNPV = a;
}
void CashFlowPlot::setRata(const QPolygonF &a)
{
        rata    = a;
        rataCum = MyMath::cumulative(rata);
}
void CashFlowPlot::setEcoParameters(const ecopara e)
{
	eco = e;
        if (eco.regime == Vendita)
            tabWidget->setTabText(2,tr("Dettagli vendita"));
        else
            tabWidget->setTabText(2,tr("Dettagli CS"));


}
QString CashFlowPlot::getTable()
{
	return s;
}
QString CashFlowPlot::getTaxTable()
{
        return sOther;
}
void CashFlowPlot::setAmmNPV(const QPolygonF& a)
{
	ammNPV = a;
}
void CashFlowPlot::setAmm(const QPolygonF& a)
{	
	amm = a;
}
void CashFlowPlot::setYearlyCost(const QPolygonF& a)
{	
	yearlyCost = a;
}
void CashFlowPlot::setYearlyCostNPV(const QPolygonF& a)
{	
	yearlyCostNPV = a;
}
void CashFlowPlot::settings()
{
	#ifdef DEBUG
	qDebug()<<"I am here";	
	#endif
// 	Settings s2;
// 	int a;
	if (cursorPos.y()<=qwtPlot->geometry().y()+qwtPlot->geometry().height()){
        //qDebug()<<"updateset";
            if (!set->isVisible()){
                        set->setTitle(rawPlot->title().text());
			set->show();
                    }
	}
	 if (cursorPos.y()>qwtPlot->geometry().y()+qwtPlot->geometry().height()){
         qDebug()<<"updatesetVAN"<<vanPlot->title().text();
             if (!setVan->isVisible()){
                        setVan->setTitle(vanPlot->title().text());
			setVan->show();
                    }
	}
}
void CashFlowPlot::updateSet()
{
        //qDebug()<<"UPDATESET";
	QString str;
	QwtText tlabel;
        tlabel.setFont(QFont("Times",12,QFont::Normal));
	 
  	tlabel.setText(set->getTitle());
	qwtPlot->setTitle(tlabel);
	qwtPlot->setAxisTitle(QwtPlot::yLeft,set->getAxisY());
	qwtPlot->setAxisTitle(QwtPlot::xBottom,set->getAxisX());
	 
		

	 
}
void CashFlowPlot::updateSetVan()
{
        //qDebug()<<"UPDATESETVAN";
	QString str;
	QwtText tlabel;
        tlabel.setFont(QFont("Times",12,QFont::Normal));
		
  	tlabel.setText(setVan->getTitle());
	qwtVan->setTitle(setVan->getTitle());
	qwtVan->setAxisTitle(QwtPlot::yLeft,setVan->getAxisY());
	qwtVan->setAxisTitle(QwtPlot::xBottom,setVan->getAxisX());
}
void CashFlowPlot::reset()
{
    textEdit->setHtml("");
    textEditCS->setHtml("");
     drawRata(0);
     drawRataNPV(0);
     drawInterest(0 );
     drawInterestNPV(0 );
     drawFlowCash( 0);
     drawNPV(0 );
}
void CashFlowPlot::setSavingsEn(const QPolygonF& a)
{
    savingsEn = a;
    if (a.size()!=rawcash.size()){
        qDebug()<<"CASH FLOW: strange vector size......";
        savingsEn.fill(QPoint(0,0),rawcash.size());
    }
}
void CashFlowPlot::changeDraw(int state)
{
    QwtText tlabel3;
    if (state==Qt::Checked){
      //  rawcashToUse = rawcashCum; //MOL
      //  tassatoToUse = tassatoCum;  // Flusso di cassa
        flowToUse = rawPlusTaxCum; // MOL+Tasse


//                tlabel3.setText(tr("MOL cumulato"));
           tlabel3.setText(tr("MOL")+" - " + tr("Tasse&Sgravi") + tr("(cumulati)"));
                tlabel3.setFont(QFont("Times",12,QFont::Normal));
                set->setTitle(tlabel3.text());
                qwtPlot->setTitle(tlabel3);
        //npvToUse     = npvCum;
        }
        else{
     //   rawcashToUse = rawcash;
      //  tassatoToUse = tassato;
        flowToUse = rawPlusTax;
//      tlabel3.setText(tr("MOL"));
        tlabel3.setText(tr("MOL")+" - " + tr("Tasse&Sgravi"));
        tlabel3.setFont(QFont("Times",12,QFont::Normal));
        qwtPlot->setTitle(tlabel3);
        set->setTitle(tlabel3.text());
        //npvToUse      = npv;
    }
        drawRata(1);
       // drawRataNPV(1);

    drawFlowCash(1);
    drawNPV(1);

    updateTable();

}
void CashFlowPlot::changeDrawData()
{
    /*Change data but not plot*/
    if (checkCumulative->isChecked()){
        rawcashToUse = rawcashCum;
        //npvToUse     = npvCum;
    }
        else{
        rawcashToUse = rawcash;
        //npvToUse       = npv;
    }
}
void CashFlowPlot::setNumOfDec(int i)
{
    if (i>=0 && i<=8)
        numOfDec = i;

}
double CashFlowPlot::functionFin(double n,double A,double Fin, double rate)
{
    double res ;
    if (n==0)
        return 0;
    res = ((Fin * rate) /( 1 - pow((1+rate),-n)) - A) ;

    return res;
}
double CashFlowPlot::functionFin2(double n,QPolygonF A,double Fin, double rate)
{
    double res ;
    if (n==0)
        return 0;
    res = ((Fin * rate) /( 1 - pow((1+rate),-n)) - MyMath::cumSum(A.mid(0,n))/n) ;

    return res;
}
double CashFlowPlot::suggestFinYears()
{

    double m;
    QPolygonF baseData;
    callback2 c;
 //   c.user_func = functionFin;
    c.user_func = functionFin2;

    if (rawcash.size()==0)
        return 0;
    if (rawcash.size()==1)
        return 1;

    
    switch (simOptions.at(0)){
//    case minMOL:
//        baseData = rawcash;
//        m = MyMath::min(baseData);
//        break;
//    case meanMOL:
//        baseData = rawcash;
//        m = MyMath::mean(baseData);
//
//        break;
//    case ribMeanCassa:
//        baseData = MyMath::subtract(tassato,savingsEn);
//        baseData = MyMath::subtract(baseData,cs);
//
//        m = MyMath::mean(baseData);
//        break;
//    case meanCumMOL:
//        baseData = rawcashCum;
//        m = MyMath::mean(baseData);
//        break;
     case ribMolCs:
         baseData = MyMath::subtract(rawcash,tasse);
         baseData = MyMath::subtract(baseData,savingsEn);
         baseData = MyMath::subtract(baseData,cs);

         m = MyMath::mean(baseData);

         break;

    case bonusOnly:
        baseData = MyMath::subtract(bonus,tasse);

        baseData = MyMath::subtract(baseData,yearlyCost);
        m        = MyMath::mean(baseData);
        break;
//    case minCassa:
//        baseData = MyMath::subtract(rawcash,tasse);
//        m        = MyMath::min(baseData);
//        break;

    default:
        /* Ricavi (CS+Incentivi+RIB+credit) - tasse + sgravi */
        baseData = MyMath::subtract(rawcash,tasse);

        m        = MyMath::mean(baseData);

    }

//qDebug()<<"CASHPLOT baseData"<<baseData;
    c.A = baseData;
    c.Fin =  loan;
    c.rate= eco.loanInterestRate/100;
    // qDebug()<<"CASH CAMBIO INTERVALLO?"<<MyMath::countCross(baseData);
     QPolygonF cT;
     for(int n=1;n<=eco.life;n++)
         cT << QPointF(n,functionFin2(n,baseData,c.Fin,c.rate));


    if (MyMath::countCross(cT)>1){
        /* Forse incentivi o consumi nulli *?
        /*Cambia intervallo*/
     //  qDebug()<<"CASH CAMBIO INTERVALLO?"<<MyMath::countCross(cT);
       return floor(bisection( &c,1,eco.bonusesYears,1E-10,1000));
       }

    return floor(bisection( &c,1,eco.life,1E-10,1000));
}

void CashFlowPlot::setIVA(const QPolygonF &a)
{
    iva = a;
}
void CashFlowPlot::setIrap(const QPolygonF &a)
{
    irap = a;
}
void CashFlowPlot::setIrpef(const QPolygonF &a)
{
    irpef = a;

}
void CashFlowPlot::setIres(const QPolygonF &a)
{
    ires = a;
}
void CashFlowPlot::setNetto(const QPolygonF &a)
{
    /* Flusso di Cassa o netto */
    tassato     = a;
    tassatoCum  = MyMath::cumulative(a);
    tassatoToUse= tassato;


}
void CashFlowPlot::setTasse(const QPolygonF &a)
{
    tasse = a;
    rawPlusTax   = MyMath::subtract(rawcash,tasse);
    rawPlusTaxCum   = MyMath::cumulative(rawPlusTax);
    flowToUse = rawPlusTax;
}

void CashFlowPlot::setOptions(const QVector<int> &o)
{
    simOptions = o;
}
void CashFlowPlot::setFetched(const QPolygonF &a)
{
    fetched = a;
}
void CashFlowPlot::setWarnings(const QString &q)
{
    warnings = q;
}
void CashFlowPlot::setFinVat(double l)
{
    loan = l;
}
