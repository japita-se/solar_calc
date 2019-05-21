#ifndef _HOURLY_PLOT_
#define _HOURLY_PLOT_
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
class HourlyPlot: public QwtPlot
{
	Q_OBJECT
public:
	HourlyPlot(QWidget* parent=0 );
	~HourlyPlot();
	
	void setMode(bool i, double a);
	void setHourlyData(const QPolygonF &d);
	void setTime(int month,int day);
	void draw(int mode);
signals:
	void unitChanged(int i);
protected:
	void convert(int i);
	void createActions();
	void alignScales();
protected slots:
	void updateSet();
	void settings();
	void printOut();
	void exportSVG();
	void exportPNG();
	void exportPDF();
	void exportTXT();
	void popUpMenu(const QPoint &pos);
private:
	  QwtPlotCurve *plotHourly;
	  QwtPlotMarker *totalMarker;
	  QString name;
	  QStringList u;
	  QwtPlotPicker  *picker;
	QAction *a_print,*a_export,*a_proprieta,*a_create_grid,*a_exportPNG,*a_exportPDF,*a_export_txt;
	bool plotPresent,scaling;
	QPolygonF hourlyData;
	Settings *set;
	int currentUnit;
	QString recentExportPath,recentDir,dateLabel;
	double integral,totalThisDay;
};
#endif