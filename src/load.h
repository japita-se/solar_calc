#ifndef LOAD_H
#define LOAD_H
#include "mymath.h"
#include "ui_consumi.h"

class QwtPlotCurve;
class HistogramItem;
class Load : public QWidget, public Ui::widgetConsumi
{
	Q_OBJECT
public:
	Load(QWidget* parent=0);
	~Load();
        int getYearProfile();
        double getYearlyTotal();
        void resetAll();
        bool zeroLoad();
        void saveState();
        void reloadSavedState();
        void load(const QString &i);
	void setYear(int i);
	QPolygonF getHourlyLoads(int year,int day,int month);
	double getHourlyLoad(int year, int hour,int day,int month);
	double getMonthly(int year, int month,int day, int hour);
	bool isError();
	void   setYearly(double d);
	QString getFileCustom();
	void setFileCustom(const QString &g);
	int getLang();
        bool loadInserted();
signals:
	void updated();
public slots:
	void notify();
	void load();
	void save();
	void saveAs();
	void setMonthlyProfile(int i);
	void setHourlyProfile(int i);
	void setDefault();
private slots:
        void clearSelected();
        void clearSelectedHours();
        void uniformize();
        void uniformizeHours();
        void popMenu();
        void popMenuHours();
        void setSatNormOption(int m);
        void setSunNormOption(int m);
        void updateQuotas(int m,int y);
        void updateTitle();
        void updateHoursProfileDetails(int t);
        void updateHoursFromSelection();
	void setRestDay(int i);
	void setSunPercent(double c);
	void setSatPercent(double c);
	void settings();
	void updateWeeklyPlot(int month);
	void updateMonthlyPlot();
	void updateHourlyPlot(int month);
// 	void viewHours(QTableWidgetItem* current);
	void storeItem(QTableWidgetItem* c);
	void checkHourlyData(QTableWidgetItem* c);
	void checkData(QTableWidgetItem* current );
	void saveProfile();
	void montlhyChanged();
	 
	void hourlyChanged();
	void update();
	void updateMonths();
         void updateHours(QTableWidgetItem* a);
        void updateHours(QTableWidgetItem* a,int mode);
	void updateHourlyItems();
	 
	void updateMonthlyItems();
protected:

        double getYearlyLoadPercent(int y,int m);
        void createActions();
	int getClosingDay();
        QVector<double> getMonthlyLoad(int month,int y);
	void alignScales();
	void saveCustom(  QString &fileName);
	bool loadCustom(const QString &fileName);
private:
	QString w1,w2;
// 	QwtPlotCurve* plot;
	HistogramItem* plot,*plotM,*plotW;
        bool isDirty,valueDirty,doNotCheck,
        doNotCheckHours,someError,doNotUpdate,doNotAskAgain,onlyCurrentMonth
        ,doNotModifyWin;
        int monthlyProfile,year,numDecimals;
        double currentItemValue,saturdayPercent,sundayPercent,yearlyLoad;
	QStringList monthsList;
        QVector<double> loadValue,mLoadValue,gSunLoad,gSatLoad,gNormLoad,quotaSat,
        quotaSun,quotaSatB,quotaSunB,ML;
        QVector<double> monthlyLoad,typicalProfile,
        typicalCommercial,typicalIndustrial;
	QVector<double> monthlyLoadPrev,monthlySummerLoad,monthlySummerLoadPrev,monthlyWinterLoadPrev,monthlyWinterLoad,monthlyCustomLoadPrev, monthlyCustomLoad;
	QVector<int> hourlyProfile,restDay;
	QVector<double> hLoad,hLoadPercent;//entire vector
        QVector<bool> equalSat,equalSun;

        QAction *a_clear,*a_copy,*a_copy_hours,*a_clear_hours;
	
	enum
	{	
	Uniform,
	Summer,
	Winter,
	SeasonalWinter,
	SeasonalSummer,
	Custom,
        Commercial,
	Industrial
	};
	enum
	{
        hUniform,
	hTipico,
	hCustom,
	hCommercial,
	hIndustrial
	};
        enum{
            default_,
            user_

        };
        QString fileCustom,recentSave,recentDirCarichi,grayStyle,yellowStyle;
};
#endif
