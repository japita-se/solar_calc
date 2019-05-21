#ifndef _HOURLYEN_PLOT_
#define _HOURLYEN_PLOT_
#include <QtGui>

 #include <qwt_plot_curve.h>
#include <qwt_plot_marker.h>
#include <qwt_plot.h>
#include "data.h"
#include <QPolygonF>
class Settings;
class QwtPlotCurve;
class QwtPlotMarker;
 
class QwtPlotPicker;
 
class QwtPlotCurve;
class QwtPlotMarker;
class HourlyEnergyPlot: public QwtPlot
{
	Q_OBJECT
public:
	HourlyEnergyPlot(QWidget* parent=0 );
	~HourlyEnergyPlot();
	void setLoad(QPolygonF &a);
	void setMode(bool i, double a);
        void setTime(int month,int day);
	void setHourlyData(const QPolygonF &d);
	void draw(int mode);
signals:
	void unitChanged(int i);
protected:
	void drawLoad();
	void convert(int i);
	void createActions();
	void alignScales();
public slots:
	void enableDrawingLoads(bool i);
protected slots:
	void exportTXT();
	void updateSet();
	void settings();
	void printOut();
	void exportSVG();
	void exportPNG();
	void exportPDF();
	void popUpMenu(const QPoint &pos);
private:
	  QwtPlotCurve *plotHourly,*plotLoad;
	  QwtPlotMarker *totalMarker;
	  QString name,currentTitle,recentDir;
	  QStringList u;
	  QwtPlotPicker  *picker;
	QAction *a_print,*a_export,*a_proprieta,*a_create_grid,*a_exportPNG,*a_exportPDF,*a_export_txt;
	bool plotPresent,scaling,enableLoads;
	QPolygonF hourlyData,hourlyLoads;
	Settings *set;
	int currentUnit;
	QString recentExportPath,dateLabel;
	double integral,totalThisDay;
};
#endif