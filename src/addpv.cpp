
#define DEBUG
#include "math.h"
#include "addpv.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
AddPv::AddPv(QWidget *parent): QDialog(parent)
{
	setupUi(this);
	groupParElettriciPannello->setEnabled(false);
	groupParElettriciInverter->setEnabled(false);
	dSpinBoxBeta->setMaximum(0);
	dSpinBoxBeta->setMinimum(-100);
        dSpinBoxPnom->setRange(0,1000000000);
        dSpinBoxVoc->setRange(0,1000000000);
        dSpinBoxVmax->setRange(0,1000000000);
        dSpinBoxVmp->setRange(0,1000000000);
        dSpinBoxImp->setRange(0,100000000);
        dSpinBoxIsc->setRange(0,100000000);
        dSpinBoxImp->setRange(0,10000000);
	dSpinBoxNoct->setRange(0,100);
	dSpinBoxH->setRange(0,200000);
	dSpinBoxL->setRange(0,200000);
	dSpinBoxS->setRange(0,900);
	 
	dSpinBoxBeta->setRange(-100,100);
	dSpinBoxAlfa->setRange(-100,100);
	dSpinBoxGamma->setRange(-100,100);
	dSpinBoxEff->setRange(0,100);
	dSpinBoxEff->setDecimals(3);
        dSpinBoxInvPnom->setRange(0,10000000);
        dSpinBoxInvVmin->setRange(0,10000000);
        dSpinBoxInvVmax->setRange(0,10000000);
        dSpinBoxInvPin->setRange(0,10000000);
        dSpinBoxInvVmpmin->setRange(0,10000000);
        dSpinBoxInvVmpmax->setRange(0,10000000);
	dSpinBoxInvEff->setRange(0,100);
	dSpinBoxInvEff->setDecimals(3);
	dSpinBoxEff->setEnabled(false);
	
// 	connect(this,SIGNAL(accepted()),SLOT(accept()));
	connect(pushOk,SIGNAL(clicked()),SLOT(checkAndExit()));
	connect(pushCancel,SIGNAL(clicked()),SLOT(reject()));
	connect(lineCostruttore,SIGNAL(textChanged(const QString &)),SLOT(updatePanelWidget()));
	connect(lineModello,SIGNAL(textChanged(const QString &)),SLOT(updatePanelWidget()));
	tabWidget->setCurrentIndex(0);
	connect(lineInverterCostruttore,SIGNAL(textChanged(const QString &)),SLOT(updatePanelWidget()));
	connect(lineInverterModello,SIGNAL(textChanged(const QString &)),SLOT(updatePanelWidget()));
	connect(checkDimensioni,SIGNAL(stateChanged(int)),SLOT(updateEffWidget(int)));
	connect(dSpinBoxH,SIGNAL(editingFinished()),SLOT(updateEff()));
	connect(dSpinBoxL,SIGNAL(editingFinished()),SLOT(updateEff()));
}
void AddPv::checkAndExit()
{
	int resP,resI;
	if( groupParElettriciPannello->isEnabled())
		resP = checkData() ? 1 :0;
	else 
		resP = 1;
	if (groupParElettriciInverter->isEnabled())
		resI = checkDataInverter() ? 1 :0;
	else 
		resI =1;

	
	switch (resP + 2*resI) {
		case 0:
		QMessageBox::warning(this,tr("Dati errati"),tr("I dati obbligatori sono le dimensioni, il gamma, Pnom e le efficienze. Ricontrolla."),QMessageBox::Ok);
		break;
		
		case 1:
		QMessageBox::warning(this,tr("Dati errati Inverter"),tr("Efficienza deve essere non nulla. Ricontrolla."),QMessageBox::Ok);
		break;
	
		case 2:
		QMessageBox::warning(this,tr("Dati errati"),tr("I dati obbligatori sono le dimensioni, il gamma, e la Pnom. Ricontrolla."),QMessageBox::Ok);
		break;
		
		case 3:
		updateModel();
		emit accepted();
		accept();
		break;
	}
	
		
		
 
			
}
void AddPv::updateEff()
{
	double p = dSpinBoxPnom->value();
	double H = dSpinBoxH->value();
	double l = dSpinBoxL->value();
	double eff  = dSpinBoxEff->value();
        double area = (H*l)/1000;/* area in mq*/
	if (area>0)
        panelEff = ceil(100*p/(area));
	else
	panelEff =0;
}

void AddPv::updateEffWidget(int state)
{
    if (state==Qt::Checked){
                groupBox->setEnabled(true);
		dSpinBoxEff->setEnabled(false);
            }
    else{
        groupBox->setEnabled(false);
		dSpinBoxEff->setEnabled(true);
            }
	
}
void AddPv::updatePanelWidget()
{ 
	if (!lineCostruttore->text().isEmpty() && (!lineModello->text().isEmpty()))
		{
		  groupParElettriciPannello->setEnabled(true);
	          
		  }
        else
              groupParElettriciPannello->setEnabled(false);
	if (!lineInverterCostruttore->text().isEmpty() && (!lineInverterModello->text().isEmpty()))
		{
		  groupParElettriciInverter->setEnabled(true);
	          
		  }
        else
              groupParElettriciInverter->setEnabled(false);

}
bool AddPv::checkDataInverter()
{
	if (dSpinBoxInvEff->value()>0)
		return true;
	else
		return false;
}
bool AddPv::checkData()
{
	double pnom = dSpinBoxPnom->value();
	double H = dSpinBoxH->value();
	double l = dSpinBoxL->value();
        //double gamma = dSpinBoxGamma->value();
	double area = (H*l)/1000000;/* area in mq*/
	
	 
	if ((area>0) && (pnom>0) )
		return true;
	else	
		return false;
	
 
	
}
void AddPv::updateModel()
{
	QSqlDatabase db = QSqlDatabase::database(connId);
	QSqlQuery query(db);
	if (groupParElettriciPannello->isEnabled()) {	

		
            query.prepare("INSERT INTO pannelli (costruttore,modello,pnom,voc,isc,imp,noct,peso,vmp,vmax,beta,alfa,gamma,H,L,s,tolleranza,efficienza,usura) VALUES (:costruttore,:modello,:pnom,:voc,:isc,:imp,:noct,:peso,:vmp,:vmax,:beta,:alfa,:gamma,:H,:L,:S,:tolleranza,:efficienza,:usura)");
			query.bindValue(":costruttore",lineCostruttore->text().trimmed());
			query.bindValue(":modello",lineModello->text().trimmed());
			query.bindValue(":pnom",dSpinBoxPnom->value());
			query.bindValue(":voc",dSpinBoxVoc->value());
			query.bindValue(":isc",dSpinBoxIsc->value());
			query.bindValue(":imp",dSpinBoxImp->value());
			query.bindValue(":noct",dSpinBoxNoct->value());
			query.bindValue(":peso",linePeso->text().toDouble());
			query.bindValue(":vmp",dSpinBoxVmp->value());
			query.bindValue(":vmax",dSpinBoxVmax->value());
			query.bindValue(":beta",dSpinBoxBeta->value());
		
			 /*TO DO */	
	
			query.bindValue(":alfa",dSpinBoxAlfa->value());
			query.bindValue(":gamma",dSpinBoxGamma->value());

			query.bindValue(":H",dSpinBoxH->value());
			query.bindValue(":L",dSpinBoxL->value());
			query.bindValue(":S",dSpinBoxS->value());
			query.bindValue(":tolleranza",spinBoxTolleranza->value());
			query.bindValue(":efficienza",panelEff);
                        query.bindValue(":usura",dSpinBoxUsura->value());
			query.exec();
			#ifdef DEBUG
			qDebug()<<"inserimento in pannelli..."<<query.lastError()<<query.lastError().text()<<db<<connId;
			/* no usa direttamente query!*/
			#endif
		
	}
	if (groupParElettriciInverter->isEnabled())
	{
		if (checkDataInverter()) {
                    query.prepare("INSERT INTO inverter (costruttore,modello,pnom,pin,vmax,vmin,vmpmin,vmpmax,imax,efficienza,usura,tipo,vout,icc,tra,cosfi) VALUES (:costruttore,:modello,:pnom,:pin,:vmax,:vmin,:vmpmin,:vmpmax,:imax,:efficienza,:usura,:tipo,:vout,:icc,:tra,:cosfi)");
			query.bindValue(":costruttore",lineInverterCostruttore->text().trimmed());
			query.bindValue(":modello",lineInverterModello->text().trimmed());
			query.bindValue(":pnom",dSpinBoxInvPnom->value());
			query.bindValue(":pin",dSpinBoxInvPin->value());
			query.bindValue(":vmax",dSpinBoxInvVmax->value());
			query.bindValue(":vmin",dSpinBoxInvVmin->value());
			query.bindValue(":vmpmin",dSpinBoxInvVmpmin->value());
			query.bindValue(":vmpmax",dSpinBoxInvVmpmax->value());
			query.bindValue(":imax",dSpinBoxInvImax->value());
			query.bindValue(":efficienza",dSpinBoxInvEff->value());
                        query.bindValue(":usura",dSpinBoxInvUsura->value());
                        if (radioTT->isChecked())
                            query.bindValue(":tipo","Trifase");
                        else
                            query.bindValue(":tipo","Monofase");

                        query.bindValue(":vout",dSpinVout->value());
                         query.bindValue(":icc",dSpinIcc->value());
                        if (checkTra->isChecked())
                            query.bindValue(":tra",true);
                        else
                            query.bindValue(":tra",false);

                        query.bindValue(":cosfi",dSpinCosPhi->value());
			query.exec();
			#ifdef DEBUG
			qDebug()<<"inserimento in inverter..."<<query.lastError();
			/* no usa direttamente query!*/
			#endif
		}		
	
	}
}
void AddPv::setConnId(const QString &m)
{
	connId = m;
}
  AddPv::~AddPv()
{
}
