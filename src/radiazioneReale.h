
#ifndef _RREALE_PLOT_
#define _RREALE_PLOT_
#include <QtGui>

 #include <qwt_plot_curve.h>
#include <qwt_plot_marker.h>
#include <qwt_plot.h>
#include "data.h"
class Settings;
class QwtPlotCurve;
class QwtPlotMarker;
class QPoint;
class QwtPlotPicker;
 
class QwtPlotCurve;
class QwtPlotMarker;
class RadiazioneReale: public QwtPlot
{
	Q_OBJECT
public:
	void resetOmbre();
	void resetAdditionalOmbre();
	void addOmbre(const QVector<double> &a);
	
	void addInclAzi(const QVector<double> &a,const QVector<double> &b);
	void setSource(int source);
	void viewRefCurve(bool i);
	void computeRefCurve(int mode,double tilt);
	double* getHref();
  	double getTotalShadowLossFactor();
	QVector<double> getLossFactors();
	double getLossFactor();
	void convertFit( );
	void setYear(int i);
	void setTotalDayLen(const QVector<double> &a);
	void setMeanDayLen(const QVector<double> &a);
	double getHourlyH(int h,int year,int month,int day, double shadow, double lat,double tilt,double d,double Rb, double rrd, double r,int mode,int model);
	RadiazioneReale(QWidget* parent=0 );
	bool mainPlotPresent();
	void compute();
// 	void computeDaily();
	void fit();
	double* getFittingPar();
	const double* getFittedValues();
	QPolygonF getDailyHincl();
	QPolygonF getDailyHinclOmbre();
	void compute(double Rb[12]);
	void drawContents(int mode,int whichone);
	void drawDailyContents(int mode);
	void setOmegasDaily(const QPolygonF &in);
	void setOmbreFactorDaily(const QPolygonF &input);
	void setHhoDaily(const QPolygonF &input);
	void setRbDaily(const QPolygonF &input);
	 
// 	void drawDailyValue(int i);
	void setIncl(QPolygonF a);
	void setDailyIncl(QPolygonF a);
	void setAzi(double a);
	void setLat(double a);
	void setRb(double a[12]);
	void setR(const QVector<double>  &a);
	void setOmegas(double a[12]);
// 	void setAll(double a[12], double c[12]);//set Rb and Hho
	void setHg(double a[12]);//set the Hg;
	void setOmbre(const QVector<double> &a);
	double getBestIncl();
        int getUnit();
	bool dailyIsDirty();
        double *getHincl(int whicone);
        double *getHinclOmbre(int whichone);
	void setModel(int i);
	void setLocName(const QString &s);
	bool hgIsPresent();
        void  optimize(int select );
	 
	double getMaxIrr();
// 	void setArea(double area);
// 	void setPanel(panel pan);
// 	void setTempMin(double tempMin);
// 	void setTempMax(double tempMax);
// 	double* getRealEnergy();
// 	double* getEffTemp();
// 	void computeRealEnergy();
 signals:
        void unitChanged(int i);
	void computeDone();
public slots:
	void swapUnit();
	void exportPDF();
	void drawRefCurve(int mode);
private slots:
	void redraw();
	void popUpMenu(const QPoint &);
	void printOut();
	void exportSVG();
	void exportTXT();
	void exportPNG();
	 
	
	void moved(const QPoint &pos);
	 
	void settings();
	void updateSet();
private:
        void checkMarkers();
	void drawMarkers(bool doit);
	void resetTitle();
	void  createActions();
	void convertFit(int i);
	void convertRaw(int i);
	void convertDailyFit(int i);
	double convert(int i,double value);
	void alignScales();
	
	static double fittingFunction(double t,   double* p);
	static double fittingFunction2(double t,   double* p);
//         double* compute_(double rb[12],double tilt,int select);
	double compute_(double rb,double hho,double hg,int month,double tilt,int select);
	double diffuseIndex(int m,double omegas,double kt);
	
private:
	double azi,lat;
	double bestIncl;
	double maxIrr;
	 
	double Energy[12] ;
	QVector<double> R ;
	double Kt[12];
	double K[12];
	double Hd[12],Rb[12],Hg[12],dailyHg[366],fittedHg[366],Hho[12],Hb[12],omegas[12];
        double Hincl[12],HinclOmbre[12],Hincl2[12],HinclOmbre2[12],
               HinclView[12],HinclOmbreView[12],Hincl2View[12],HinclOmbre2View[12];
        double Hincl_[12],HinclOmbre_[12],Href[12];
 	double days[366];
// 	double ombreFactor[12];
	QVector<double> ombreFactor;
	double meanLossFactor,totalLossFactor;
	int model,currentUnit;
        QwtPlotCurve *plotReale,*plotRealeNoShadow,*plotEnergy,*fittedDailyValue,*dDailyValues,*plotRealeRef;
	QwtPlotMarker *plotRealeMarker,*realeLegend,*monthMarker[12],*lossMarker;
	QString name;
	QStringList u;
	QwtPlotPicker  *picker;
	QAction *a_print,*a_export,*a_proprieta,*a_exportPNG,*a_exportPDF,*a_export_txt;
	QAction* aw_toggle_marker;
	Settings *set;
	bool HgIsPresent,fittingDone,dailyValueDirty,mainPlot,inclOptiPresent,showRefCurve;
	double p[3];/*parameter of the fitting function*/
	QPolygonF incl,dailyIncl,dailyHincl,dailyHinclOmbre,dailyHho,dailyRb ,dailyOmbreFactor,dailyOmegas;
	QString  recentExportPath,recentDir;
	QVector<double> totalDayLen,meanDayLen,mLF;//365 values
	int year;
	 int source,whichGraph;
	QList<QVector<double> > additionalOmbreFactor;
	QVector<double> additionalIncl,additionalAzi;


        enum{
            north,
            south
        };
	enum{
	kaplanis,
	pereira,
	kyushu
	};
        enum {
        radEnea,
        radUNI,
        radNasa,
        radCustom
        };

}; 
#endif
