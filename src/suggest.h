#ifndef _SUGGESTGUI_
#define _SUGGESTGUI_
#include "data.h"
#include "ui_suggest.h"

class Suggest : public QDialog, public Ui::Suggest
{
	Q_OBJECT
public:
	Suggest(QWidget *parent =0 );
	~Suggest();
	
	void setPanel(panel p);
        void setPanel2(panel p);
	void setRad(double rad);
	void setInverter(inverter i);
	void setLoss(double o);
	double getArea();
	double getNum();
	
private slots:
	void compute();
        void updateSpin();
	
private:
        double radiation,panelEff,inverterEff,otherEff,
        consumption,areaPanel,powerPanel,numPanels,areaPanel2,powerPanel2,numPanelsarea2,area;
        panel 	 localPanel,localPanel2;
	inverter localInverter;
	double  localLoss;
private:
	
	
	
};
#endif
