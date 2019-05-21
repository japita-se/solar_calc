#ifndef OUTREPORT_H
#define OUTREPORT_H
#include "data.h"
#include <QTextCursor>
#include <QImage>
#include <QtGui>

class QTextDocument;
class QwtPlot;
class QPrinter;
class MyPlot;

 
class OutReport :public QWidget 
{

	 
public:
	OutReport(QWidget* parent =0);
	~OutReport();
	void addSystem(sy a);
	QString getDir();
        void addYearlyLoad(double a);
        void addMonthlyProfile(int a);
        void setNumPanels(int n1,int n2);
        void setTax(const QString& g);
	void setTable(const QString& g);
	void setDir(const QString& g);
	void setEcoParameters(ecopara o);

	void addVanDiagram(const QwtPlot* p);
	void addRawDiagram(const QwtPlot* p);
	void addSolarRadiation(const QwtPlot* p);
	void addSolarRadiation2(const QwtPlot* p);
	void addEEnergy(const QwtPlot* p);
        void setVersion(const QString &version);
  	void addLocation(loc localita);
 	void addPanel(panel p);
  	void addInverter(inverter inv);
	void addOption(option o);
  	void addRad(const double *H);
	void addEnergy(const double *E);
	void addUnitRad(const QString &s);
	void addUnitEnergy(const QString &s);
	void addTotEnergy(double a);
        void addSolarDiagram(MyPlot *p);
       
        void print(QPrinter *y,int mode,QPrinter::OutputFormat format);
        void printGeneral(QPrinter *y);
private:
        QRectF contentRect(QPaintDevice *device);
        QRectF paperRect(QPaintDevice *device);
        QString makeTable();
        QString makeEcoTable();
         QString cssTable();
	
private:

	QTextDocument * const m_document;
	QTextCursor   m_cursor;
        QPrinter* printer_;

	loc localita;
	panel    pan;
	inverter inv;
	option opt;
	ecopara eco;
        QStringList models,types,sources,mounting,regime,profile;
	bool Hset,Eset,ecoIsPresent;
        QString unit,unitEnergy,recentDir,version,summaryTable,summaryTax;
	double totEnergy ;
        double yearlyLoad;
        int    monthlyProfile;
        double leftmargin_,rightmargin_,topmargin_,bottommargin_;
        int numPanels,numPanels2;
        const QwtPlot
                *vanDiagram,*rawDiagram,*solarRadiation,*solarRadiation2,*eEnergy;
        MyPlot* solarDiagram;
	sy systemDetails;
	 
	const double* H,*E;
enum {
		rack,
		direct,
		standoff	
	};

	enum{
	con,
	variable_high_snow,
	variable_low_snow
	};
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
};
#endif
