#include <QtGui>
#include "data.h"
#include "back_spa.h"
#include <qwt_plot_marker.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <QPixmap>
#include <qwt_text.h>
class Settings;
class QwtPlotPicker;
class QPos;
class GridSet;
class QPoint;
class QActions;
class QwtPlotGrid;
class QPolygonF;
class QwtLegend;

struct spaMean {
 	float SEA;
 	float AZ;
 	};
class MyPlot  : public QwtPlot
{
	Q_OBJECT 
public:
  MyPlot( QWidget *par =NULL);
  void setCurrentSide(int m);
  void setAziIncl2(double a, double in);
  void setProjectDir(const QString &a);
  void replotGraph();
  double getSingleInc(int hour,int month,int day,int year,double slope,double rotation);
  double getHGlobalRatio(rbData p,double rd);
 // double getHGlobalsRatio(int hout, int month, int day, int year,double omegas,int model);
  double getHDiffuseRatio(rbData r);
  double getSingleRb(rbData r);
  double incidence( double sunZenith,double sunAzimuth,double slope,double rotation);
  QPointF computeSingleValue(int time, int month, int year);
  QPointF computeSingleValue(int time,int month,int day,int year);
  int lowestMonth(double lat);
  double hourlyOmbreFactor(int year,int month, int day, int hour);	
  QImage* getImage();
  double getDeclinationPrime(int month, int day, int hour);
  void setShadow(const QPolygonF &s,bool fire);
  QPolygonF getShadow();
  QPolygonF getShadowCombined();
  QPolygonF getShadowNear();
  void delPoly();
  void setX(float x);
  void setY(float y);
  
  void compute();
  void computeDaily();
  QVector<double> computeShadow(const QVector<double> &oApp, const QVector<double> &oSco);
  void computeShadow();
  void setMonthlyTemp(const QVector<double> &a);
  void setLong(double l);
  void setLat(double l);
  void setAlt(double l);
  void setAzi(double a);
  void setUTC(int i);
  void setYear(int i);
  void setIncl(double i);
  void setMode(int m);
  void setRes(int m);
  	
  void drawMyContents( int mode);	
  void setHSteps(int a, int b, double c);
  void  setLocName(const QString &s);
  double* getSunrise();
  double* getSunset();
//   void setOmegaApp(double *a);
//   void setOmegaSco(double *a);
  void setOmegaApp(const QVector<double> &a);
  void setOmegaSco(const QVector<double> &a);
  void setDailyOmegaApp(const QPolygonF &in);
  void setDailyOmegaSco(const QPolygonF &in);
  void setPolyShadow(  QPolygonF  a,bool fire);
//   double* getShadowFactor();
  QVector<double>& getShadowFactor();
  QPolygonF getDailyShadowFactor();
  void setIntegration(int mode);
  void setShadowCombineMode(int mode);
  bool ombrePresent();
	QString getFileName();
protected:
        bool isTwoSide();
        double getCorrectAzimuth(myspa_data s);
	int highestMonth(double lat);
	
	int tropic();
        bool checkQuadrant(myspa_data l);
	void resetTitle();
	void alignScales();
        void createActions();
        double eArea(QPolygonF &a,QPolygonF &ombre,double start,double end,int mode);
        
        void addSelfShadow2(double a,double v);
	void addSelfShadow(double a,double v);
        QVector<double> computeSelfShadow(int days,double inc,double elev,double azi);
       
        bool shadowLoaded();
	bool nearShadowLoaded();
	int digitize(double x,double o, double delta);
	void initializeGrid();
	void combineShadow(QPolygonF &data);
	void combineRawAndPoly();
        QPolygonF combine( QPolygonF &p1,  QPolygonF &p2);
        QPolygonF combineSpline(const QPolygonF &p1,const QPolygonF &p2);
	QPolygonF combineMax( const QPolygonF &p1,  const QPolygonF &p2);
        QPolygonF sampleAndHold(const QPolygonF &p1);
	QPolygonF sampleAndHoldPoly(const QPolygonF &p1);
        QPolygonF processShadow(QPolygonF &data,int i);
	void change( const QPolygonF &source,QPolygonF &destination, int id);
  	static bool lessThanPoint(const QPointF &p1, const QPointF &p2);
	static bool lessThanPointLast(const QPointF &p1, const QPointF &p2);
	
//  	virtual void paintEvent(QPaintEvent *);
public slots:
// 	void setDamp();
 	void resetOmbre();
	void toggleSelfShadow( int mode);	
	void toggleSpline(int a);
	void undoCombine();
	void popUpMenu(const QPoint &);
	void printOut();
	void settings();
	void exportSVG();
	void exportPNG();
        void exportPNG(  QString& a);
	void exportPDF();
	void moved(const QwtDoublePoint &pos);
	void selected(const QwtDoublePoint &);
	void updateSet();
	void updateGrid();
	void gridset();
	void loadShadow(const QString &s);
	void loadShadow();
	void deleteShadow();
	 void drawShadow(int i,const QPolygonF &d);
 signals:
	void ombreChanged();
private:
	spaMean msun(float lon, float lati, int h, int m, int d,int UTC);
	
private:
        myspa_data spa;
	QwtScaleMap xMap; 
	QwtScaleMap yMap;
	
	QAction *a_print,*a_export,*a_proprieta,*a_create_grid,*a_exportPNG,*a_exportPDF;
	QAction *a_load_shadow,*a_delete_shadow,*a_undo_combine;
	
// 	double h[40];
	double *hl;
	double *hf;
// 	double *gnuDataX;
// 	double *gnuDataY;
  	double **dataToPlotX;
  	double **dataToPlotY;
// 	double *timeDataX;
//    	double *timeDataY;
	double **sunEA;
        double **sunAZ;
	double **sunInc;
	QPolygonF thisMonthColor;
        QPolygonF sunP[12];
	QPolygonF sunPathToPlot[12];
        QPolygonF sunIncEast,sunIncWest,sunIncEast2,sunIncWest2;
	QPolygonF  dailyOmegaApp;
	QPolygonF  dailyOmegaSco;
	QPolygonF  dailyOmbreFactor;
//         double  ombreFactor[12];
	QVector<double> ombreFactor;
	double **timeX,**timeY;
        QString name;
        QString recentDir,recentExportPath;
	bool graphPresent,dailyValueDirty;

	double step;
	int *intervalDays;
	 int numHours,numHoursFast,fast,meanVal,numDays,startH,endH,stepH;
        int givenDays[12],currentSide;
	
        QString monthLabels[13],projectDir;
      	QStringList hourLabels;
//     	double  *hourPosX;
//    	double  *hourPosY;
	QPolygonF hourPos;
	 
	double  *monthPosX;
	double  *monthPosY;
	
	 
 	 QwtPlotCurve *dSolar[12];
	 QwtPlotCurve **dTime;
	 QwtPlotCurve *dShadow,*dShadowTemp,*dTiltShadowEast,*dTiltShadowWest;
         QPolygonF  shadow,baseShadow,previousShadow,nearShadow,nearShadowToSave,shadowCombined, sunpos;
         double sunSet[12];
         double sunRise[12];

// 	double *omegaApp,*omegaSco;
        QVector<double> omegaApp,omegaSco,addInclAzi;
	
         QwtPlotMarker *monthMarker[12],*legendMarker[12],*legendMarkerText[12],**hourMarker,**hourMarker2;
	 QwtPlotPicker  *picker;
	 QwtPlotGrid *grid;

         QwtText legendLabel;
	 Settings *set;
	 GridSet  *gridSettings;
	 QWidget *p;
        QString fileName,legendString;

	QLabel* label;	 
 	QImage*  image;
// 	QPixmap  pixmap;
        double delta,offset;
         int ombreMode;
         int mode,reorder ;
         QVector<double> temperatures;

        enum {
        default_,
        custom_
        };
        enum {
             sampleAndHoldMode,
             splineMode
         };
	 
	enum {
	rawdata,
	polygon
	}; 

};
