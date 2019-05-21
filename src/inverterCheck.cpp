#include "datiinverter.h"
#include "inverterCheck.h"
#include <math.h>
#include "mymath.h"
#include <QtGui>
#include <QtSvg>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlQuery>
// #define DEBUG
void InverterCheck::resetAll()
{
 
	inverters.clear();
	numCampi  = 0;
	numStringField = 0;
        //numPanels = 0;
	doNotChange = true;
	 
	comboInverter->clear();
	 
	comboCampi->clear();
	 
	lineCampi->setText("");
       // lineCampi->setValidator(new QRegExpValidator(QRegExp("([0-9]{1,1}|\\s+)"),lineCampi));
	linePannelli->setText("");
	textEdit->clear();
        warn.resize(0);
        warn.fill(false,7);
	
	for(int i=0;i<5;i++)
	{
	QTreeWidgetItem* item = treeWidget->topLevelItem(i);
 	item->setIcon(3,QIcon(":/images/ledspento.png"));
	}	
	emit componentStatus();
	//qDebug()<<"IC reset 6";
}
InverterCheck::InverterCheck(QWidget* parent) : QWidget(parent)
{
	inverters.clear();
	warningString<<tr("Nessun dato di radiazione disponibile. Prova a selezionare un sito");
	warningString<<tr("Numero di pannelli inseriti maggiore di quelli disponibili");
	warningString<<tr("I parametri dei campi, es.: Potenza, Tensioni, Correnti, non sono compatibili con l'inverter scelto. Prova a cambiare il campo e/o il tipo di inverter");
	warningString<<tr("Componenti assenti e/o incompleti.Setta i componenti");
	warningString<<tr("Controlla il numero di panneli per stringa.");
	warningString<<tr("Potenza nulla e/o pannelli non configurati");
	warningString<<tr("Alcuni inverter non configurati");
	for(int i=0;i<warningString.size();i++)
		warn<<0;
	setupUi(this);
	system<<tr("Pmax")<<tr("Voc(Tmin)")<<tr("Vmp(Tmin)")<<tr("Vmp(Tmax)")<<tr("Isc");
	in<<tr("Pin")<<tr("Vmax")<<tr("Vmppt")+"(min)"<<tr("Vmmpt(max)")<<tr("Iin(max)");
	QRegExpValidator *validator = new QRegExpValidator(QRegExp("[0-9]{1,1}|"),this);
// 	lineCampi->setValidator(validator);

 	 svg = new QSvgWidget(":/images/inverter3.svg",widget);
  	 svg->adjustSize();
// 	svg->setMinimumSize(widget->sizeHint());
	widget->adjustSize();
//   	 imageLabel->setPixmap(QPixmap::fromImage(p) );
// 	 imageLabel->setFrameShape(QFrame::Box);

// //      imageLabel->setBackgroundRole(QPalette::Base);
//       imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
//        imageLabel->setScaledContents(true);

    

      
    
//        imageLabel->adjustSize();

	treeWidget->setColumnCount(4);
	QStringList h;
	h<<tr("Campo FV")<<""<<tr("Inverter")<<tr("Stato");
	treeWidget->setHeaderLabels(h);
	QList<QTreeWidgetItem *> items;
	 
 
	 for (int i = 0; i < system.size(); i++){
	QTreeWidgetItem *it = new QTreeWidgetItem(treeWidget);
  	it->setIcon(3,QIcon(":/images/ledspento.png"));
	 
	it->setText(0,system.at(i));
	it->setText(1," ");
	it->setText(2,in.at(i));
	
	it->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	items.append(it);
	treeWidget->resizeColumnToContents(1);
	}
	treeWidget->insertTopLevelItems(0, items);
	thisProjectInverter.isValid=false;
	thisProjectPanel.isValid=true;
	 
 	numCampi  = 0;
	numStringField = 0;
	numPanels = 0;
	doNotChange = false;
	temp<<0<<0;
	connect(pushSuggerisci,SIGNAL(clicked()),SLOT(suggest()));
	connect(treeWidget,SIGNAL(itemClicked(QTreeWidgetItem*, int)),SLOT(test(QTreeWidgetItem*, int)));
	connect(pushCheck,SIGNAL(clicked()),SLOT(checkAll()));
	connect(comboCampi,SIGNAL(currentIndexChanged(int)),SLOT(updateView(int)));
//   	connect(lineCampi,SIGNAL(editingFinished()),SLOT(enableCheck()));
	connect(lineCampi,SIGNAL(textEdited(const QString &)),SLOT(enableSuggest(const QString &)));
  	connect(linePannelli,SIGNAL(editingFinished()),SLOT(checkAll()));
// 	connect(linePannelli,SIGNAL(textChanged(QString)),SLOT(enableCheck()));
// 	connect(linePannelli,SIGNAL(textEdited(QString)),SLOT(enableCheck()));
	connect(pushScegli,SIGNAL(clicked()),SLOT(chooseInverter()));
	connect(pushElimina,SIGNAL(clicked()),SLOT(resetAll()));
	pushCheck->setAutoDefault(true);
	textEdit->setReadOnly(true);
	pushScegli->setEnabled(false);

	label_2->setToolTip(tr("<p> Inserisci una lista di numeri separati da spazio.</p><p> Ogni numero rappresenta il numero di stringhe per campo</p><p> Ex.: 1 2 rappresenta due campi, il primo da 1 stringa e il secondo con due stringhe</p>"));
	label_11->setToolTip(tr("<p>Clicca sul menu a tendina per cambiare il modello di inverter per il campo corrente</p>"));
}

void InverterCheck::setDatabase(const QString &s)
{
	databasePanelsId = s;
	pushScegli->setEnabled(true);
// 	qDebug()<<"IC database set"<<databasePanelsId;
}
void InverterCheck::chooseInverter()
{
	DatiInverter dati ;

	 
	QSqlDatabase db = QSqlDatabase::database(databasePanelsId);
	
	dati.setDatabase(db,"inverter");
		if (dati.exec()) {
			inverter t = dati.getSelectedInverter(); 
			if (t.isValid && comboInverter->currentIndex()<inverters.size()){
				//qDebug()<<"IC chooseInerter"<<inverters.size()<<comboInverter->currentIndex();
				
				 if (!inverters.isEmpty())
					inverters.replace(comboInverter->currentIndex(), t);
				 else
					inverters.append(t);
			}
		}
	updateComboModel();
	inverterListCheck();
	emit componentStatus();
	 
}

bool InverterCheck::inverterListCheck()
{
        bool o = true;
  //qDebug()<<"IC lsit check "<<inverters.size()<<comboInverter->count();
	if (comboInverter->count()==0)
		o=false;
	for(int i=0;i<comboInverter->count();i++)
        {
		if (i<inverters.size()){
                       //  qDebug()<<"IC list check "<<inverters.size()<<comboInverter->count()<<inverters.at(i).isValid;
                         o &= inverters.at(i).isValid;

		}
		else
			o = false;
         }

        // qDebug()<<"IC warn 6"<<o;
                warn.replace(6,o);
	
	return o;
}
void InverterCheck::enableSuggest(const QString &s)
{
	if (s.isEmpty())
		pushSuggerisci->setEnabled(true);
	else	
		pushSuggerisci->setEnabled(false);
enableCheck();
}
void InverterCheck::enableCheck()
{
	pushCheck->setEnabled(true);
}
void InverterCheck::parsePannelli()
{
	QStringList panels;	
	int a,ps;
	a=0;	
	ps=0;
	
	panels = linePannelli->text().trimmed().split(" ");
	ps = panels.size();
// 	numCampi =lineCampi->text().trimmed().split(" ").size();
	pString.resize(0);
	if (panels.size()<numCampi){
		for(int s=0;s<(numCampi - ps);s++) panels.append("0");
		warn.replace(4,true);
		#ifdef DEBUG
		 qDebug()<<"IC check parsepannelli panelsiez"<<panels.size();
		#endif
	}
	else
	{
		if (panels.size()>numCampi){
			panels = panels.mid(0,numCampi);
			warn.replace(4,true);
		}
		else
			warn.replace(4,false);
	}

        //if (panels.size()>numCampi)
        //	panels = panels.mid(0,numCampi);

	for(int i=0;i<numCampi;i++){
		a+= panels.at(i).toInt() * campiVector.at(i);//sp
		pString<<panels.at(i).toInt();
		}

	if (a>numPanels)
		warn.replace(1,true);
	else
		warn.replace(1,false);
        #ifdef DEBUG
	 qDebug()<<"IC check pannelli"<<a<<numCampi<<pString<<campiVector;
        #endif
	warnLabel();
	
}	
// void InverterCheck::checkCampi()
// {
// 	parseCampi();
// 	checkAll();
// }
void InverterCheck::updateView(int i)
{
// 	spinStringhe->setValue(stringField.at(i));
	if (!doNotChange){
		checkVoltage(campiVector.at(i),pString.at(i),i);
		comboInverter->setCurrentIndex(i);
	}
	
}
void InverterCheck::checkAll()
{
	//TODO CHEKC THE VALIDATOR
	
	parseCampi();
	parsePannelli();
	//  	//qDebug()<<"IC check parsecampi checkAll dopo checkVoltage prima di clear"<<MyMath::listOfNumber(1,numCampi)<<numCampi;
	doNotChange = true;
	comboCampi->clear();
//  	//qDebug()<<"IC check parsecampi checkAll dopo checkVoltage dopo di clear"<<MyMath::listOfNumber(1,numCampi)<<numCampi;
	
 	comboCampi->addItems(MyMath::listOfNumber(1,numCampi));
//  	//qDebug()<<"IC check parsecampi checkAll dopo checkVoltage dopo add"<<MyMath::listOfNumber(1,numCampi)<<numCampi;
	
// 	comboCampi->setCurrentIndex(0);
	fillInverters();
	int r = checkVoltage();
  	//qDebug()<<"IC ritorni in checkAll"<<r;
	if (r>0) {
//                 QPoint ss(checkVoltage(),0);
		comboCampi->setCurrentIndex(r);//Change the combo to the first field in error and redo check
		comboInverter->setCurrentIndex(r);
	}
	

	warnLabel();
	doNotChange = false;
// 	pushCheck->setEnabled(false);
	emit componentStatus();
}
void InverterCheck::test(QTreeWidgetItem* a, int c)
{
	//qDebug()<<"IC "<<a<<c;
}
 void InverterCheck::setInverter(inverter i)
         /* Set the inverter type from outside*/
         /* If the inverters data has been filled then update with i*/
         /* Otherwise, perhaps it is the first time we set a component here*/
{
     int s = inverters.size()==0 ? 1 : inverters.size();

  	thisProjectInverter = i;//Template
	//Set all the inverters to i
	
        // qDebug()<<"IC set inverter size"<<inverters.size();
	if (i.isValid) {
		inverters.clear();
		for(int t=0;t<s;t++)
			inverters.append(i);
                #ifdef DEBUG
                 qDebug()<<"IC set inverter"<<i.indexDB<<i.isValid<<inverters.size();
                #endif
	}
 	 
}
 void InverterCheck::setPanel(panel i)
{
	thisProjectPanel = i;
	 
	
}
 void InverterCheck::setNumPanels(int i)
{
	
	numPanels = i;
     //   qDebug()<<"IC setNumPanels"<<numPanels;
	
}
QString InverterCheck::getStatusInverter()
{
        //qDebug()<<"IC"<< thisProjectInverter.isValid;
	if ( thisProjectInverter.isValid)
		return tr("Inverter=")+thisProjectInverter.model+"  ";
	   else
		if (inverterListCheck())
			return tr("Inverters configurati");
		
		
//	if ( !thisProjectInverter.isValid )
		return tr("Inverter non valido o assente");

}
void InverterCheck::minTempChanged(double i)
{

	temp.replace(0,i);
	checkVoltage();
}
void InverterCheck::maxTempChanged(double i)
{
	temp.replace(1,i);
	checkVoltage();
}
void InverterCheck::setTemp(QVector<double> a)
{
	/* We suppose that temp is a vector with Tmin at the first place, Tmax at the second */
	temp.resize(0);
	temp = a;
        qDebug()<<"IC temperatures"<<temp;
}
double InverterCheck::installedPower()
{
	if (thisProjectPanel.isValid)
	return numPanels*thisProjectPanel.pnom;
	else
	return 0;
}
void InverterCheck::parseCampi()
{
	if (( (!thisProjectPanel.isValid) || (!thisProjectInverter.isValid) ) && !inverterListCheck()){
		warn.replace(3,true);
// 		//qDebug()<<"parse campi head"<<thisProjectPanel.isValid<<thisProjectInverter.isValid<<inverterListCheck();
	}
	else{
// 		//qDebug()<<"parse campi head step"<<thisProjectPanel.isValid<<thisProjectInverter.isValid<<inverterListCheck();
		warn.replace(3,false);
	}
	
	#ifdef DEBUG
	 qDebug()<<"IC PARSE CAMPI"<<numCampi;
	#endif
	QStringList in,panels;
	campiVector.resize(0);
	
// 	pString.resize(0);

	in =lineCampi->text().trimmed().split(" ");
// 	panels = linePannelli->text().trimmed().split(" ");
//	int ps = panels.size();
	
	numCampi = lineCampi->text().isEmpty() ? 0 : in.size();
	#ifdef DEBUG
	 qDebug()<<"IC check parsecampi panelsiez"<<in<<numCampi;
	#endif
// 	if (panels.size()<numCampi){
// 		for(int s=0;s<(numCampi - ps);s++) panels.append("0");
// 		warn.replace(4,true);
// 		//qDebug()<<"IC check parsecampi panelsiez"<<panels.size();
// 	}
// 	else
// 		warn.replace(4,false);
	
	for(int i=0;i<numCampi;i++)
		
	{	
		#ifdef DEBUG
		 qDebug()<<"IC check parsecampi campo,stringa"<<in.at(i).toInt()<<numCampi<<in<<i;
		#endif
		campiVector<<in.at(i).toInt();
		
// 		pString<<panels.at(i).toInt();
				
	}
	
	if (numCampi==0)
		warn.replace(5,true);
	else
		warn.replace(5,false);
 
	

}

void InverterCheck::suggest()
{
	if (((!thisProjectPanel.isValid) || (!thisProjectInverter.isValid)) && !inverterListCheck()) {
		warn.replace(3,true);
// 		//qDebug()<<"Suggest not possible"<<thisProjectPanel.isValid<<thisProjectInverter.isValid<<inverterListCheck();
		
	}
	else
	{
// 		//qDebug()<<"Suggest   possible"<<thisProjectPanel.isValid<<thisProjectInverter.isValid<<inverterListCheck();
		warn.replace(3,false);
		
		QStringList s,p;

		
//                 numCampi       = ceil(installedPower() / thisProjectInverter.pin);
		  double minPower = 999999999;
		  double minIsc   = 999999999;


                  if (inverters.size()==0 ){

                            inverters.append(thisProjectInverter);
                            minPower = MyMath::min(minPower,inverters.at(0).pin);
                            minIsc   = MyMath::min(minIsc,inverters.at(0).imax);


                       // qDebug()<<"IC sugget top"<<inverters.size()<<inverters.at(0).pin;
                    }
                  else {
                      for(int o=0;o<inverters.size();o++) {
                                    minPower = MyMath::min(minPower,inverters.at(o).pin);
                                    minIsc   = MyMath::min(minIsc,inverters.at(o).imax);

                      }
                 }
                  if (minPower>0.00000000002)
                      numCampi       = ceil(installedPower() / minPower);
                  else
                      numCampi = 0;
		campiVector.resize(0);
		

		doNotChange = true;
		comboCampi->clear();
		comboCampi->addItems(MyMath::listOfNumber(1,numCampi));
		
		doNotChange = false;
	// 	numCampi       = (installedPower() % thisProjectInverter.pin) + numCampi;
// 		numStringField = (numCampi==0) ? 0 : floor(thisProjectInverter.imax / thisProjectPanel.isc);
		numStringField = (numCampi==0) ? 0 : floor(minIsc / thisProjectPanel.isc);
		

		campiVector.fill(numStringField,numCampi);
		
		numPanelString = (numStringField==0) ? 0 : floor((numPanels / numCampi)/numStringField);
		pString.resize(0);
		fillInverters();
// 	//qDebug()<<"IC suggest 2"<<numPanels;
		for(int i=0;i<numCampi;i++) {
			
			
			pString<<(numPanelString);//all string equal
			s<<QString::number(numStringField);
			p<<QString::number(numPanelString);
		}
                #ifdef DEBUG
 qDebug()<<"IC Suggest"<<thisProjectInverter.imax <<thisProjectPanel.isc<<comboCampi->currentIndex()<<campiVector<<numStringField<<numCampi<<installedPower()<<thisProjectPanel.pnom<<thisProjectPanel.isc<<minIsc<<inverters.size()<<thisProjectPanel.isc<<minIsc;
                #endif
		
	// 	spinStringhe->setValue(stringField.at(comboCampi->currentIndex()));
		
		linePannelli->setText(p.join(" "));
		lineCampi->setText(s.join(" "));
	
		parsePannelli();
		checkVoltage();
		updateComboModel();
		comboCampi->setCurrentIndex(0);
		
	}
	warnLabel();
}
void InverterCheck::fillInverters()
{
	#ifdef DEBUG
	 qDebug()<<"IC fillInverter inverters.size()"<<inverters.size()<<numCampi;
	#endif 
	if ((inverters.size() <= numCampi) && numCampi>0 ){
			QList<inverter> addI;
			for(int k=0;k<numCampi-inverters.size();k++) {
					
					addI.append(thisProjectInverter);
	
						
						
			}
			inverters.append(addI);
		}
	updateComboModel();
}
void InverterCheck::updateComboModel()
{
	//qDebug()<<"IC updateComboModel"<<comboCampi->currentIndex()<<inverters.size();
	comboInverter->clear();
	if (!inverters.isEmpty()){
		for(int s=0;s<inverters.size();s++){
			if (inverters.at(s).isValid)
			comboInverter->addItem(inverters.at(s).fabric + " - " + inverters.at(s).model);
			else
			comboInverter->addItem(" - ");
		}
	
		if (comboCampi->currentIndex()>0)
			comboInverter->setCurrentIndex(comboCampi->currentIndex());
	}
}
int InverterCheck::checkVoltage()
{
        QPoint o;
	QVector<int> temp;
        o.setX(true);
        o.setY(false);
	resumeCheck.clear();
	 
	for(int i=0;i<numCampi;i++)
	{
		#ifdef DEBUG
		 qDebug()<<"IC checkVoltage"<<pString.at(i)<<campiVector.at(i)<<numCampi;
		#endif
  		o = checkVoltage(campiVector.at(i),pString.at(i),i);
            //     qDebug()<<"IC checkVoltage ritorno"<<pString.at(i)<<campiVector.at(i)<<numCampi;
                if (!o.x()){
 			resumeCheck << tr("Campo...") + QString::number(i+1) + "<font color=\"red\">" + tr(" errore") + "</font>";
			
 			
 			temp<<i;
			 
// 			
 		}
		else
		{
                        if (o.y())
                        resumeCheck << tr("<h5>Campo... ") + QString::number(i+1) + "</h5><font color=\"orange\">"+tr(" OK")+"..." + tr("Forse sovradimensionato") + "</font>";
			else
                        resumeCheck << tr("Campo... ") + QString::number(i+1) + "</h5><font>"+tr(" OK") + "</font>";
			
		}
	if (campiVector.at(i)>1)
        resumeCheck<<QString::number(campiVector.at(i))+ ".... " + tr("Stringhe da ") + QString::number(pString.at(i)) ;
	else
        resumeCheck<<QString::number(campiVector.at(i))+ "... " + tr("Stringa da ") + QString::number(pString.at(i));

        resumeCheck<<"MAX(Vmp) = " + QString::number(vmpMax) + "V"<<"Imax = "
                + QString::number(imax) + "A"<<"--------------------<br/>";

	}
	
// 	//qDebug()<<"IC checkVoltage furoi loop";
	
	if (temp.size()>0 )
		return temp.at(0);
	else 
		return -1;
	
		
}
QPoint InverterCheck::checkVoltage(int s,int p,int numinverter)
{
        QPoint output(false,false);

	/* We suppose that temp is a vector with Tmin at the first place, Tmax at the second */
// if (thisProjectPanel.isValid && thisProjectInverter.isValid){

	
if (thisProjectPanel.isValid && inverters.at(numinverter).isValid){
	double cellTempMin = getCellTemp(temp.at(0));
	double cellTempMax = getCellTemp(temp.at(1));

        vocMax = p * (thisProjectPanel.voc *
                      (1 + thisProjectPanel.beta*(cellTempMin-25)/100));
	if ((vocMax-inverters.at(numinverter).vmax) <= 0.000002)
	{
		statusV[1] = true;
		//statusVoc = true;
	}
	else
		statusV[1] = true;
		//statusVoc = false;
        vmpMin = p*(thisProjectPanel.vmp  *
                 (1 - thisProjectPanel.beta*(cellTempMax-25)/100));
	if ((inverters.at(numinverter).vmpmin-vmpMin)<=0.000002)
		statusV[2] = true;
		//statusVmpMin =true;
	else
		statusV[2] = true;
		//statusVmpMin =false;
        vmpMax =    p*(thisProjectPanel.vmp   *
                   (1+ thisProjectPanel.beta*(cellTempMin-25)/100));
	if ((vmpMax-inverters.at(numinverter).vmpmax)<=0.0000002)
		statusV[3] = true;
		//statusVmpMax = true;
	else
		statusV[3] = false;
	imax = thisProjectPanel.isc*s;

	if ((imax-inverters.at(numinverter).imax)<=0.00000002)
		statusV[4] = true;
	else
		statusV[4] = false;
		//statusVmpMax = false;
	pmax = thisProjectPanel.pnom*s*p;
// qDebug()<<"IC check power "<<pmax<<s<<p<<numinverter;
	if ((pmax-inverters.at(numinverter).pin)<0.000000002)
		statusV[0] = true;
	else	
		statusV[0] = false;
	
         #ifdef DEBUG

        #endif
        output.setX( updateLed());

	if (pmax-2*inverters.at(numinverter).pin>0.000002)
                output.setY(  true);
	else
                output.setY(false);

	

	}
	else
	{
	       output.setX(  false);
	       output.setY(  false);
	       
	}


    return output;

}
bool InverterCheck::updateLed()
{
	/*system<<tr("Pmax")<<tr("Voc(Tmin)")<<tr("Vmp(Tmin)")<<tr("Vmp(Tmax)");*/
	
	bool s;
	s= true;
	for(int i=0;i<5;i++)
	{
	QTreeWidgetItem* item = treeWidget->topLevelItem(i);
// 	//qDebug()<<"IC updateLed()"<<item->text(0);
// 	//qDebug()<<"IC updateLed()"<<item->text(1);
	
	if (numPanels == 0){
		item->setIcon(3,QIcon(":/images/ledspento.png"));
		warn.replace(5,true);
	}
	else
	{
		if (statusV[i]){
			item->setIcon(3,QIcon(":/images/ledverde.png"));
			switch (i){
					
					break;
					case 3:
					item->setText(1,">");
					break;
					default:
					item->setText(1,"<");
					
				}
				warn.replace(2,false);
		}
		else
			{
			item->setIcon(3,QIcon(":/images/ledrosso.png"));
				switch (i){
					
					break;
					case 3:
					item->setText(1,"<");
					
					break;
					default:
					item->setText(1,">");
					
					
				}
				warn.replace(2,true);
			}
		s &= statusV[i];
		}
		warn.replace(5,false);
	}
	return s;
}
void InverterCheck::setRad(double*  a,int unit)
{
	/* unit = 1, MJ/m2, unit=2 kW/m2*/
//  	//qDebug()<<"EO curen unit ="<<unit;
 	for(int i=0;i<12;i++){
 		if (unit==1)
 		H[i] = a[i]/3.6;
 		if (unit==2)
		H[i] = a[i];
// 	//qDebug()<<"EO H = "<<H[i];
  	}
}
void InverterCheck::setAddRad(double*  a,int unit)
{
	/* unit = 1, MJ/m2, unit=2 kW/m2*/
//  	//qDebug()<<"EO curen unit ="<<unit;
 	for(int i=0;i<12;i++){
 		if (unit==1)
 		H2[i] = a[i]/3.6;
 		if (unit==2)
		H2[i] = a[i];
// 	//qDebug()<<"EO H = "<<H[i];
  	}
}
void InverterCheck::setMounting(int a,double m)
{
	mounting = a;
	mountingHeight = m;
}
 
double InverterCheck::getCellTemp(double Ta)
{
        double t[12],maxH[12],rad,bn,upv,at;
	double rn  = MyMath::realNoct(thisProjectPanel.noct,mounting,mountingHeight);
	
	for(int k=0;k<12;k++) maxH[k] = MyMath::max(H[k],H2[k]);

	if (meanDayLen.isEmpty()){
		warn.replace(0, true);
		warnLabel();
		return 0;
	}
	else
	{
	for(int i=0;i<12;i++){
		switch (thermalModel) {	 
			case NOCT:
                        t[i-1] = (Ta + ((9.5/(5.7+3.8*windDaily.at(i-1)))*H[i-1]/meanDayLen.at(i-1))*(rn-Ta)/0.8);
			break;
			/* alternative equation CLEFS CEA (2004), On the temperature dependence of photovoltaic module electrical performance: A review of efficiency/power correlations*/ 
			case CEA:
			t[i-1] = (Ta  + (1/(22.4+8.7*windDaily.at(i-1)))*H[i-1]/meanDayLen.at(i-1) );
			break;
			case other:
			rad = H[i-1]/meanDayLen.at(i-1);
			bn = -thisProjectPanel.gamma*thisProjectPanel.eff/10000;
			upv= 11.34+7.72*windDaily.at(i-1);
			at =0.9;
			t[i-1] = (upv*Ta + 1000*rad*(at - thisProjectPanel.eff/100 -bn*25))/(upv-bn*rad*1000);
			
		
		}
	}
	return MyMath::min(t,12);
	}
	
}
void InverterCheck::setThermalModel(int f)
{
	thermalModel = f;
}
void InverterCheck::setMeanDayLen(const QVector<double> &p)
{
        meanDayLen = p;
	#ifdef DEBUG
         qDebug()<<"EnergyOut ho settato la lunghezza delgiorno"<<p.at(0)<<meanDayLen.at(0)<<meanDayLen.at(1)<<meanDayLen.at(2);
	#endif
}
int InverterCheck::configuredPanels()
{
	int a=0;
	
	if (campiVector.size()!=pString.size()){
// 		//qDebug()<<"IC configured"<<campiVector.size()<<pString.size();
		return 0;
	}
	else
	{
	for(int i=0;i<campiVector.size();i++)
		a+=campiVector.at(i)*pString.at(i);
	return a;
	}
}
void InverterCheck::warnLabel( )
{
	QString t;
	bool ad;
        //double numInserted = MyMath::cumSum(pString);
        double numInserted  = configuredPanels();
        t =  "<p>###########################</p>";
        t += "   #<h2>  SYSTEM CHECK </h2> #";
        t += "<p>###########################</p> ";
	t += "<p>" + tr("Potenza installata = ") + QString::number(installedPower()) + "Wp</p>";
	t+= "<p>" + tr("Numero pannelli inseriti   = ") + QString::number(numPanels) + "</p>";
        if (numPanels-numInserted>0.0000000000002)
		t+= "<p><font color=\"orange\">" + tr("Numero pannelli configurati   = ") + QString::number(numInserted) + "</font></p>";
	else
		t+= "<p>" + tr("Numero pannelli configurati   = ") + QString::number(configuredPanels()) + "</p>";
        for(int i=0;i<warn.size();i++){
		if (warn.at(i))
			{
			ad =true;
			t = t + "<p><font color=\"red\">" + warningString.at(i) + "</font></p>";
			}
		else 
			ad = false;
	}
	t+=  resumeCheck.join("<br>");
	if (ad)
		t+= tr("Clicca su Check per scoprire gli errori");
// 	labelWarn->setText(t);
	textEdit->clear();
	textEdit->setHtml(t);
	#ifdef DEBUG
	 qDebug()<<"IC warn"<<warn<<t;
	#endif
}
void InverterCheck::setWind( const QVector<double> &t)
{
	windDaily  = t;
}
// QList<QStringList> InverterCheck::getMainPar()
// {
// 	QStringList value,p;
// 	for(int i=0;i<campiVector.size();i++)
// 			p << QString::number(pString.at(i));
// 	p.join("-");
// 	value<<QString::number(numCampi)<<p<<
// 	
// }
sy InverterCheck::getSystem()
{

	
	sy temp ;
	QStringList s;
	temp.campiVector    = campiVector;
	temp.panelVector    = pString;
	temp.efficiencies.resize(0);
	 
	
	for(int i=0;i<comboInverter->count();i++) {
	  
			if (inverters.at(i).isValid){
				s<<inverters.at(i).fabric + inverters.at(i).model;
				temp.efficiencies.append(inverters.at(i).eff);	
				temp.index.append(QString::number(inverters.at(i).indexDB)); 
				temp.systemValid=true;
			}
			else
			{
			s<<"-";
			temp.systemValid=false;
			}
			
			
	
	}
	temp.models = s;
        temp.inverters.clear();
        temp.inverters.append(inverters);
// 	if (warn.at(3))
// 		temp.systemValid=false;
// 	else
// 		temp.systemValid=true;
// 	//qDebug()<<"IC get sytem end";
	return temp;
}
QList<inverter> InverterCheck::getInverters()
{
	return inverters;
}
void InverterCheck::setSystem( sy a)
{
	int row=0;
	inverter inv;
	
	
	/*Get inverters from the database. If not present, warn */
	QSqlDatabase db = QSqlDatabase::database(databasePanelsId);
	QSqlQueryModel* model = new QSqlQueryModel;
	QSqlRecord r;
	
	
	inverters.clear();
//   	qDebug()<<"IC SET SYSTEM"<<a.index.size()<<a.index.isEmpty()<<a.index.at(0);
	if (!a.index.isEmpty() && a.index.at(0)!="" && a.index.at(0)!="-1"){
		for(int i=0;i<a.index.size();i++){
			row = a.index.at(i).toInt();
			model->setQuery("SELECT * from inverter WHERE id = " + QString::number(row),db);	
			r = model->record(0);
			if (!r.isEmpty() && model->query().isValid() && model->query().size())
			{
				inv.fabric = r.value("costruttore").toString();
				inv.model  = r.value("modello").toString();
				inv.vmax = r.value("vmax").toDouble();
				inv.vmin  = r.value("vmin").toDouble();
				inv.vmpmin    = r.value("vmpmin").toDouble();
				inv.imax   = r.value("imax").toDouble();
				inv.vmpmax   = r.value("vmpmax").toDouble();
				inv.eff    = r.value("efficienza").toDouble();
				inv.gar    = r.value("usura").toDouble();
				inv.pnom = r.value("pnom").toDouble();
				inv.pin  = r.value("pin").toDouble();
				inv.indexDB = r.value("id").toInt();
				inv.isValid = true;
 			#ifdef DEBUG
			qDebug()<<"IC setSystem true"<<inv.fabric<<inv.eff<<model->lastError()<<model->query().executedQuery()<<row<<r<<model->query().isValid()<<model->query().size();
  			#endif
			}
			else{
				inv.isValid = false;
				inv.fabric = "";
				inv.model  ="";
				#ifdef DEBUG
				qDebug()<<"IC setSystem false"<<row<<a.index.at(i)<<model->lastError()<<databasePanelsId;
				#endif
			}
			inverters.append(inv);
		}
	}
	updateComboModel();
	#ifdef DEBUG
	qDebug()<<"IC chiamo setText "<<a.campiVector<<MyMath::toStringList(a.campiVector).join(" ")<<MyMath::toStringList(a.panelVector).join(" ");
	#endif
	lineCampi->setText(MyMath::toStringList(a.campiVector).join(" "));
	linePannelli->setText(MyMath::toStringList(a.panelVector).join(" "));

	
}
 
void InverterCheck::paintEvent(QPaintEvent* event) 
{
	 
	svg->resize(widget->size());
	widget->adjustSize();
}
