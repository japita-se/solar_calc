
#ifndef INVERTERCHECK_H
#define INVERTERCHECK_H

#include <QWidget>
#include <QPushButton>
#include "ui_inverterCheck.h" 
#include "data.h"
class QSvgWidget;
class InverterCheck : public QWidget, public Ui::inverterCheck
{
    Q_OBJECT
    
public:

    InverterCheck(QWidget *parent);
//    QMap getMainPar();
   void setSystem( sy a);
    
   QList<inverter> getInverters();
   
   sy getSystem();
   void setDatabase(const QString &s);
   void setInverter(inverter i);
   void setPanel(panel p);
   QString getStatusInverter();
   void setNumPanels(int i);
   void setTemp(QVector<double> a);
   void setThermalModel(int i);
   void setRad(double*  a,int unit);
   void setAddRad(double*  a,int unit);
   void setMeanDayLen(const QVector<double> &p);
   void setMounting(int a,double b); 
   void setWind(const QVector<double> &p);
signals:
	void componentStatus();
	 
public slots:
	void minTempChanged(double t);
	void maxTempChanged(double t);
	void resetAll();
	void checkAll();
        QPoint checkVoltage(int s,int p,int numinverter);
	int checkVoltage();
	void suggest();
private slots:
	void chooseInverter();
	void fillInverters();
	void enableSuggest(const QString &s);
	void updateComboModel();
	void enableCheck();
	void parseCampi();
	void parsePannelli();
	void updateView(int i);
	
	void test(QTreeWidgetItem* a, int c);
	void warnLabel( );
	bool updateLed();
   	double installedPower();

private:
	bool inverterListCheck();
	int configuredPanels();
	double getCellTemp(double a);
protected:
 	void paintEvent(QPaintEvent* event) ;
private:
	QString databasePanelsId;
	QStringList resumeCheck;
	QStringList warningString;
	double H[12],H2[12];
	bool statusV[4];
	double vocMax,vmpMin,vmpMax,imax,pmax,mountingHeight;
	int thermalModel,mounting;
        QVector<double> meanDayLen;
        QVector<int> campiVector,pString,stringField;
	QVector<double> temp;	
	QVector<bool> warn;
	QVector<double> windDaily;
	int numPanels,numCampi,numStringField,numPanelString;
	 
	 
	 bool statusVoc,statusVmpMin,statusVmpMax,doNotChange;
	 
	 panel thisProjectPanel;
	 inverter thisProjectInverter;
	 QList<inverter> inverters;
	 QStringList in,system;
	QSvgWidget* svg;
	enum {
	NOCT,
	CEA,
	other
	};	 

	
};
#endif
 
