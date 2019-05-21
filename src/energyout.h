#ifndef _ENERGYOUT_PLOT_
#define _ENERGYOUT_PLOT_
#include <QtGui>
#include <QPolygonF>
 #include <qwt_plot_curve.h>
#include <qwt_plot_marker.h>
#include <qwt_plot.h>
#include "data.h"
class Settings;
class QwtPlotCurve;
class QwtPlotMarker;
class QPoint;
class QwtPlotPicker;
class QPos;
class QwtPlotCurve;
class QwtPlotMarker;
class HistogramItem;
class EnergyOut: public QwtPlot

{
	Q_OBJECT
public:
	EnergyOut(QWidget* parent=0 );
	void setSystem(const sy i);
	void setInstalledPower(double i);
	double starRatio();
	void setThermalModel(int i);
	void setTotalDayLen(const QVector<double> &p);
	double getHourlyValue(double a,double rad,int month,int doy);
	void setYear(int i);
	 
	double getLossTemp();
	void setConcRatio(double d);
	void setMounting(int i,double d);
	void setWind(double w);
	void setWind(const QVector<double> &q);
        void setMeanDayLen(const QVector<double> &p);
	void computeEnergy();
	void drawContents(int mode);
	void setArea(double area);
	void setAddArea(double area);
	void setPanel(panel pan);
	void setInverter(inverter i);
	 
	void setH(double  a[12],double b[12],int unit);
	
	void setTempMin(double tempMin);
	void setTempMax(double tempMax);
	void setTemp(const QVector<double> &t);
	double* getRealEnergy();
	QVector<double> getEffTemp();
	QVector<double> getEffTemp2();
	void computeRealEnergy();
	double getTotEnergy();
	void setOtherLoss(const QVector<double> &a);
        int getUnit();
        QString getStatus();
	bool getStatus(int p);
signals:
	void unitChanged();
public slots:
	void exportPDF();

private slots:
	void popUpMenu(const QPoint &);
	void printOut();
	void exportSVG();
	 
	void exportPNG();
	void exportTXT();
	 
	void settings();
	void updateSet();
	void  moved(const QPoint &pos);
private:
	double realNoct(double i);
	void convert(int i);
	void alignScales();
	void  createActions();
	void resetTitle();
	 
private:
	 
	double area,area2,tempMin,tempMax;
	panel pan;
	inverter inv;
        double Energy[12],EnergyView[12],Energy1[12],Energy2[12];
        QVector<double> tempDaily,windDaily,otherLoss;
        QVector<double> meanDayLen,totalDayLen,effTemp,effTemp2,defaultTemp;
	double  H[12],H2[12],totEnergy,totEnergy1,totEnergy2,totLossTemp ;
	 
//	QwtPlotCurve  *plotEnergy;
        HistogramItem *plotEnergy;
	QwtPlotMarker *plotEnergyMarker,*plotEnergyMarker2 ;
	 int  currentUnit;
	QwtPlotPicker  *picker;
	QAction *a_print,*a_export,*a_proprieta,*a_create_grid,*a_exportPNG,*a_exportPDF,*a_export_txt;
	QAction *a_load_shadow,*a_delete_shadow; 
	Settings *set;
        QStringList u;
        QString status;
	QString recentExportPath,recentDir;
	double wind,mountingHeight,concRatio,installedPower;
	int mounting,year,thermalModel ;
	

	enum {
		rack,
		direct,
		array,	
		standoff
		
	};
	enum {
	NOCT,
	CEA,
	other
	};
	sy systemDetails;
		
}; 

#endif
