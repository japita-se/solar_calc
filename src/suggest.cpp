#include "suggest.h"
#include <QDebug>

Suggest::Suggest(QWidget *parent ) : QDialog(parent)
{
	setupUi(this);
	localPanel.isValid = false;
        localPanel2.isValid = false;
	localLoss = 0;
	radiation = 0;
        areaPanel = 0;
        areaPanel2 = 0;
	
        //pushSuggerisci->setEnabled(false);
        connect(pushOK,SIGNAL(clicked()),SLOT(accept()));
        connect(pushCancel,SIGNAL(clicked()),SLOT(reject()));
        connect(dSpinBoxPotenza,SIGNAL(valueChanged(double)),SLOT(compute()));
        connect(dSpinBoxConsumi,SIGNAL(valueChanged(double)),SLOT(compute()));
        connect(radiokWh,SIGNAL(toggled(bool)),SLOT(updateSpin()));
        connect(radiokW,SIGNAL(toggled(bool)),SLOT(updateSpin()));
        radiokWh->setEnabled(true);
        dSpinBoxConsumi->setEnabled(true);

        dSpinBoxPotenza->setEnabled(false);
}
void Suggest::updateSpin()
{
    if (radiokWh->isChecked()){
        dSpinBoxPotenza->setEnabled(false);
        dSpinBoxConsumi->setEnabled(true);
    }

        if (radiokW->isChecked()){
            dSpinBoxPotenza->setEnabled(true);
            dSpinBoxConsumi->setEnabled(false);
        }
}
void Suggest::setPanel2(panel p)
{
        localPanel2 = p;
        powerPanel2 = p.pnom;
        areaPanel2 = p.H * p.L/1000000;//we suppose that dimension are in mm
        if (areaPanel2==0)

                QMessageBox::warning(this,tr("Errore"),tr("<p>Area del pannello della seconda falda nulla. Hai selezionato il pannello? Se s&igrave;, ricontrolla il database dei pannelli</p>"),QMessageBox::Ok);
}
void Suggest::setPanel(panel p)
{
	localPanel = p;
	powerPanel = p.pnom;
	areaPanel = p.H * p.L/1000000;//we suppose that dimension are in mm
	if (areaPanel==0)
		
		QMessageBox::warning(this,tr("Errore"),tr("Area del pannello nulla. Hai selezionato il pannello? Se si', ricontrolla il database dei pannelli"),QMessageBox::Ok);
}
void Suggest::setRad(double r)
{
	radiation = r;
	if (radiation>0)
        pushOK->setEnabled(true);
	else
        pushOK->setEnabled(false);
}
void Suggest::setInverter(inverter i)
{
	localInverter = i;
	if (i.isValid)
		inverterEff = i.eff/100;
	else
		inverterEff = 1;
}
void Suggest::setLoss(double o)
{
		localLoss = o;
        //qDebug()<<"SUGGEST loss"<<localLoss;
}

void Suggest::compute()
{
	 
        if (pushOK->isEnabled() && localPanel.isValid && (areaPanel!=0) && (powerPanel!=0) && (radiation>0)) {

                switch (radiokW->isChecked()) {

		   case true:
                    if (localPanel2.isValid && areaPanel2!=0){
                            /* Pannelli identici su due falde */
                            area  = dSpinBoxPotenza->value()*
                                   (areaPanel+areaPanel2)/(2*powerPanel);
                            numPanels =  ceil(2*area/(areaPanel+areaPanel2));
                        }
                    else{
                            /* Singola Falda */
                            area  = dSpinBoxPotenza->value()*areaPanel/powerPanel;
                            numPanels =  ceil(area/(areaPanel));
                        }


			
		   break;
		   case false:

			if (dSpinBoxConsumi->value()>0) {

                        if (localPanel2.isValid && areaPanel2!=0){
                            area = (2*dSpinBoxConsumi->value()*1000*areaPanel)/
                                    (radiation * (1-localLoss/100) * (inverterEff) * powerPanel );
                        }
                        else


			area = (dSpinBoxConsumi->value()*1000*areaPanel)/
				(radiation * (1-localLoss/100) * (inverterEff) * powerPanel );
				numPanels = ceil(area/areaPanel);
			
			}

		   break;
	}
			labelArea->setText(QString::number(area));	
			labelNum->setText(QString::number(numPanels));
       }

}


double Suggest::getArea()
{
	return area;
}
double Suggest::getNum()
{
	return numPanels;
}
Suggest::~Suggest()
{};
	
