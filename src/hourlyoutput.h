#ifndef HOURLYOUTPUT_H
#define HOURLYOUTPUT_H
#include <qwt_plot.h>
#include "data.h"
#include <QPolygonF>
class Settings;
class QwtPlotCurve;
class QwtPlotMarker;
 
class QwtPlotPicker;
 
class QwtPlotCurve;
class QwtPlotMarker;
class HourlyOutput: public QwtPlot
{
	Q_OBJECT
public:
	HourlyOutput(QWidget* parent=0 );
	~HourlyOutput();
	 
	void setHourlyData(const QPolygonF &d);
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
	void exportPNG();
	void exportPDF();
	void popUpMenu(const QPoint &pos);
private:
	  QwtPlotCurve *plotHourly;
	  QwtPlotMarker *plotHourlyMarker;
	  QString name;
	  QStringList u;
	  QwtPlotPicker  *picker;
	QAction *a_print,*a_export,*a_proprieta,*a_create_grid,*a_exportPNG,*a_exportPDF;
	bool plotPresent;
	QPolygonF hourlyData;
	Settings *set;
	int currentUnit;
	QString recentExportPath;
};
#endif