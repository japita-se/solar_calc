#include "energyout.h"

EnergyOut::EnergyOut(QWidget* parent): QwtPlot(parent)
{
	this->setWindowIcon(QIcon(":/images/app.png"));
	setWindowTitle("SolarCalc - Energia annau prodotta");
	
	u<<tr("[MJ/m2 giorno]")<<tr("[kWh/m2 giorno]");
	
	QwtPainter::setDeviceClipping(false);
	
	plotEnergy = new QwtPlotCurve();
	plotEnergy->attach(this);
	plotEnergy->setPen(QPen(Qt::red));
	plotEnergy->setBrush(QBrush(Qt::Dense7Pattern));
	
	realeLegend = new QwtPlotMarker();
	

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
	
	
	setCanvasBackground(QColor(Qt::white));

	// Set default settings
	set = new Settings();
	set->setTitle(tr("Energia producibile"));
	set->setUnit(1);//MJ/m2
	currentUnit = 1;
	set->setAxisY(tr("Media mensile"));
	set->setAxisX(tr("Mese"));
	set->setVisible(false);
	connect(set,SIGNAL(accepted()),SLOT(updateSet()));
	
	setTitle(set->getTitle());
	setAxisTitle(QwtPlot::xBottom,set->getAxisX());
        setAxisTitle(QwtPlot::yLeft,set->getAxisY() + " " + u.at(set->getUnit()-1));
	setAxisScale(QwtPlot::xBottom,1,12);
	
	this->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this,SIGNAL(customContextMenuRequested(const QPoint &  )),this,SLOT(popUpMenu(const QPoint &)));

	alignScales();
	createActions();
}
