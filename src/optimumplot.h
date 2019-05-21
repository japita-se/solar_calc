#ifndef _OPTIMUM_PLOT_
#define _OPTIMUM_PLOT_
#include <QtGui>

#include "back_spa.h"
#include <qwt_plot_marker.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>

class QPoint;
class QwtPlotPicker;
class QPos;
class QwtPlotCurve;
class QwtPlotMarker;
class Settings;
class OptimumPlot: public QwtPlot
{
	Q_OBJECT
public:
	OptimumPlot(QWidget* parent=0);
	QVector<double> getTotalDayLen();
	void setYear(int i);
        void compute(int mode,double tilt);
        void compute(); /* This function generates different graphs for some incl values*/
	void computeHourlyRad();
	void computeDailyRad( double localIncl,double azi,int year );
	void drawContents(int mode);
	void setIncl(double d);
	void setLat(double l);
	void setAzi(double a);
	void getAll(double a[12] , double b[12], double c[12],double d[12]);
	QPolygonF getHhoDaily();
	QPolygonF getRbBiAxDaily();
	QPolygonF getRbDaily();
	QPolygonF getOmegasDaily();
	QPolygonF getOmegasHDaily();
	QPolygonF getDailyVarTilt();
	QPolygonF getDailyOmegaApp();
	QPolygonF getDailyOmegaSco();
	double *getRb();
        double *getRelativeRb();
	double *getRbBiAx();
	double *getHb( );
	double *getHbh( );
	double *getHho( );
	double getMaxIrr();
// 	double* getOmegaApp();
// 	double* getOmegaSco();
 	QVector<double> getOmegaApp();
 	QVector<double> getOmegaSco();

	double* getOmegasH();
        QVector<double> getMeanDayLen();
	QPolygonF getVarTilt();
	int getUnit();
	double getBestInclHb();
	void optimize();
	void setLocName(const QString &s);
	bool isEmpty();
signals:
	
	 void unitChanged(int i);
private:
	QString monthLabels[12];
	QString name;
	QPolygonF dailyRb,dailyHho,dailyRbBiAx,dailyOmegas,dailyOmegasH;
        QPolygonF dailyOmegaApp,dailyOmegaSco, varTilt,dailyVarTilt;
        QVector<double> meanDayLen,totalDayLen;
        int m_[12];
	double bestInclHb,maxIrr;
	double incl,lat,azi;
        double d[12],T[12],Th[12],U[12],Uh[12],V[12],Vh[12],omegasH[12],Hho[12],Hbh[12],Hb_[12],Hbh_[12];
        double omega_app1[12],omega_sco1[12],omega_app2[12],omega_sco2[12];
        double Hb[12],Rb[12],Rb_[12],RbBiAx[12];
        double varHb_[10][12];/* max 10 graphs */

// 	double omega_sco[12],omega_app[12],omegas[12];
	QVector<double> omega_app,omega_sco,omegas;

	double cumIrr;
	int optimumIncl;
	QwtPlotCurve *plotOpti[6];
	QwtPlotMarker *plotOptiMarker[6];
	QwtPlotMarker *maxLegend ;
	QAction *a_print,*a_export,*a_proprieta;
	
public slots:
	void exportPDF();
	void swapUnit();

private slots:
	void popUpMenu(const QPoint &);
	void printOut();
	void exportSVG();
	
	void moved(const QPoint &pos);
	void selected(const QwtPolygon &);
	void updateSet();
	void settings();
	
	
protected:
	 void resetTitle();
	 void alignScales();
	 void createActions();
	 void convert(int i);
	 double convert(int unit,double value);
	 bool unitChanged();
	 void tiltedRiseSet(double tilt,double decl,double azimuth,double latitude,double omegas ,double *out);
	 QwtPlotPicker  *picker;
	Settings *set;
	QStringList u;
	 
	int currentUnit,year;
        bool graphPresent,varInclGenerated;
        double startIncl,endIncl,stepIncl;
};
#endif
