#include "xmlengine.h"
#include <QMessageBox>
#include "mymath.h"
XmlEngine::XmlEngine( )
{
	panelId    = -1;
	inverterId = -1;
	QStringList dummy;
	dummy<<"0"<<"0"<<"0";
	 for(int i=0;i<12;i++){
		opt.temperatures<<0;
		opt.wind<<0;
		econ.bands<<dummy;
	}
	 bands<<"F1"<<"F2"<<"F3"<<"F4"<<"F5"<<"F6"<<"F1S"<<"F2S"<<"F3S"<<"F1D"<<"F2D"<<"F3D";	
	econ.assicurazione = 0;
	econ.assicurazioneAnni = 0;
	
}
void XmlEngine::updateLocTree()
{
// 	QStringList u;
	QString ta,pe,mpe,ba;
// 	u << "A1" << "B1" << "O1" << "MU";
	
	
	 QDomElement site = doc.documentElement().firstChildElement("site");
	    site.firstChildElement("name").firstChild().setNodeValue(localita.name);
	    site.firstChildElement("latgradi").firstChild().setNodeValue(QString::number(localita.latGradi));
	    site.firstChildElement("latmin").firstChild().setNodeValue(QString::number(localita.latMin));
	    site.firstChildElement("latsec").firstChild().setNodeValue(QString::number(localita.latSec));
	    site.firstChildElement("longradi").firstChild().setNodeValue(QString::number(localita.lonGradi));
	    site.firstChildElement("lonmin").firstChild().setNodeValue(QString::number(localita.lonMin));
	    site.firstChildElement("lonsec").firstChild().setNodeValue(QString::number(localita.lonSec));
	    site.firstChildElement("anno").firstChild().setNodeValue(QString::number(localita.anno));
	    site.firstChildElement("area").firstChild().setNodeValue(QString::number(localita.area));
	
	    if (localita.additionalArea.size()==1)
	    	site.firstChildElement("add-area").firstChild().setNodeValue(QString::number(localita.additionalArea.at(0)));
		else
		site.firstChildElement("add-area").firstChild().setNodeValue("");

	    site.firstChildElement("wind").firstChild().setNodeValue(QString::number(localita.wind));
	    site.firstChildElement("mounting").firstChild().setNodeValue(QString::number(localita.mounting));
	    site.firstChildElement("mounting-height").firstChild().setNodeValue(QString::number(localita.mountingHeight));
	 
	    site.firstChildElement("concratio").firstChild().setNodeValue(QString::number(localita.concRatio));
	    site.firstChildElement("utc").firstChild().setNodeValue(QString::number(localita.utc));
	    site.firstChildElement("albedo").firstChild().setNodeValue(QString::number(localita.albedo));
	    site.firstChildElement("albedo-model").firstChild().setNodeValue(QString::number(localita.albedoType));
	    site.firstChildElement("tilt").firstChild().setNodeValue(QString::number(localita.incl));
	    site.firstChildElement("azimuth").firstChild().setNodeValue(QString::number(localita.azi));	

	/*TO MODIFY FOR MULTIPLE FACADE */
	if (localita.additionalIncl.size()==1)
	    site.firstChildElement("add-tilt").firstChild().setNodeValue(QString::number(localita.additionalIncl.at(0)));
	else
	    site.firstChildElement("add-tilt").firstChild().setNodeValue("");

	if (localita.additionalAzi.size()==1)
	    site.firstChildElement("add-azi").firstChild().setNodeValue(QString::number(localita.additionalAzi.at(0)));
	else
	    site.firstChildElement("add-azi").firstChild().setNodeValue("");



	        site.firstChildElement("corrmodel").firstChild().setNodeValue(QString::number(localita.radCorrModel));
	    site.firstChildElement("ombre").firstChild().setNodeValue(QString::number(localita.ombreModel));
	    site.firstChildElement("type").firstChild().setNodeValue(QString::number(localita.tipo));

	    site.firstChildElement("source").firstChild().setNodeValue(QString::number(localita.source));
}
void XmlEngine::updateComponentsTree()
{
	    QDomElement pv = doc.documentElement().firstChildElement("pv-type");
	    pv.firstChildElement("id-pv").firstChild().setNodeValue(QString::number(panelId));

	    QDomElement inv = doc.documentElement().firstChildElement("inverter-type");
	    inv.firstChildElement("id-inv").firstChild().setNodeValue(QString::number(inverterId));

}
void XmlEngine::updateInvertersTree()
{
		QDomElement inv = doc.documentElement().firstChildElement("inverter-type");
		inv.firstChildElement("inverters-id").firstChild().setNodeValue(systemDetails.index.join("-"));

		 
		inv.firstChildElement("fields").firstChild().setNodeValue(MyMath::toStringList(systemDetails.campiVector).join("-"));

		 
		inv.firstChildElement("strings-panels").firstChild().setNodeValue(MyMath::toStringList(systemDetails.panelVector).join("-"));
}
void XmlEngine::updateOptionTree()
{

	    QDomElement option = doc.documentElement().firstChildElement("option");
	   
	    
	   option.firstChildElement("ombrepath").firstChild().setNodeValue( opt.ombrePath);
	   option.firstChildElement("near-ombrepath").firstChild().setNodeValue( opt.nearOmbrePath);
// 	   qDebug()<<"XML ombrepath"<<opt.ombrePath;
// 	   option.firstChildElement("temppath").firstChild().setNodeValue(opt.tempPath);
	   option.firstChildElement("thermal-model").firstChild().setNodeValue(QString::number(opt.thermalModel));
	   option.firstChildElement("energy-scaling").firstChild().setNodeValue(QString::number(opt.scaling));
	
	for(int i=1;i<13;i++)	
	{
		 option.firstChildElement(MyMath::months(i)+"-losses").firstChild().setNodeValue(QString::number(opt.otherLoss.at(i-1)));
		option.firstChildElement(MyMath::months(i)+"-t").firstChild().setNodeValue(
										QString::number(opt.temperatures.at(i-1)));
		option.firstChildElement(MyMath::months(i)+"-w").firstChild().setNodeValue(
										QString::number(opt.wind.at(i-1)));
		
	}
}
void XmlEngine::updateEcoTree()
{
QString ba,pe,mpe,ta;
QStringList u;
u << "A1" << "B1" << "O1" << "MU";
/*TO FINISH*/
	QDomElement eco = doc.documentElement().firstChildElement("economy-par");
//  		qDebug()<<"XMLEngine debug  ECO updateTree"<< econ.regime<<econ.maintenanceCost;
		eco.firstChildElement("regime").firstChild().setNodeValue(QString::number(econ.regime));
		eco.firstChildElement("bonus").firstChild().setNodeValue(QString::number(econ.bonuses));
		eco.firstChildElement("bonusxWp").firstChild().setNodeValue(QString::number(econ.bonusPerkWp));
		eco.firstChildElement("file-bands").firstChild().setNodeValue(econ.fileBands);
		eco.firstChildElement("file-tariffe").firstChild().setNodeValue(econ.fileTariffe);

	
	for(int i=0;i<12;i++){	
		
		ba = bands.at(i);
 		eco.firstChildElement(ba).firstChild().setNodeValue(econ.bands[i].join("-"));
// 		qDebug()<<"XML bands ecotree"<<ba<<econ.bands[i].join("-");
		
		
	}


	for (int i=0;i<12;i++)
	{
		ta = "ta"+QString::number(i);
		pe = "pe"+QString::number(i);
	       mpe = "mpe"+QString::number(i);
		eco.firstChildElement(ta).firstChild().setNodeValue(QString::number(econ.tariffe[i]));
		eco.firstChildElement(pe).firstChild().setNodeValue(QString::number(econ.prezziEnergia[i]));
		eco.firstChildElement(mpe).firstChild().setNodeValue(QString::number(econ.prezziMinEnergia[i]));
// 		qDebug()<<"XML prezzi"<<econ.prezziEnergia[i]<<econ.prezziMinEnergia[i];
	}

		eco.firstChildElement("load-file").firstChild().setNodeValue((econ.loadPath));
		eco.firstChildElement("file-prezzi").firstChild().setNodeValue(econ.filePrezziEnergia);
		eco.firstChildElement("file-min-prezzi").firstChild().setNodeValue(econ.filePrezziMinimi);
		eco.firstChildElement("prezzi-model").firstChild().setNodeValue(QString::number(econ.prezziEnergiaModel));
		eco.firstChildElement("prezzi-inflation").firstChild().setNodeValue(QString::number(econ.prezziEnergiaInflazione));
		
	for (int i=0;i<4;i++)
	{
		eco.firstChildElement(u.at(i)).firstChild().setNodeValue(QString::number(econ.prezziEnergiaGARCH.at(i)));
		
		
	}

	eco.firstChildElement("min-prezzi-inflation").firstChild().setNodeValue(QString::number(econ.prezziMinEnergiaInflazione));
	eco.firstChildElement("min-prezzi-model").firstChild().setNodeValue(QString::number(econ.prezziMinEnergiaModel));
		
	for (int i=0;i<4;i++)
	{
		eco.firstChildElement("m"+u.at(i)).firstChild().setNodeValue(QString::number(econ.minPrezziEnergiaGARCH.at(i)));
	}

	
		eco.firstChildElement("maintenance").firstChild().setNodeValue(QString::number(econ.maintenanceCost));
		eco.firstChildElement("maintenance-s").firstChild().setNodeValue(QString::number(econ.maintenanceS));
		eco.firstChildElement("maintenance-s-freq").firstChild().setNodeValue(QString::number(econ.maintenanceSFreq));
		eco.firstChildElement("taxes").firstChild().setNodeValue(QString::number(econ.taxesCost));
		eco.firstChildElement("other-cost").firstChild().setNodeValue(QString::number(econ.otherCost));
			
		eco.firstChildElement("benefit-start").firstChild().setNodeValue(QString::number(econ.benefitInitialCost));;
		eco.firstChildElement("benefit-interest").firstChild().setNodeValue(QString::number(econ.benefitTotalInterest));
		eco.firstChildElement("benefit-VAT").firstChild().setNodeValue(QString::number(econ.benefitVATCost));
		eco.firstChildElement("initial-cost").firstChild().setNodeValue(QString::number(econ.initialCost));
		eco.firstChildElement("loan").firstChild().setNodeValue(QString::number(econ.loan));
		eco.firstChildElement("loan-years").firstChild().setNodeValue(QString::number(econ.loanYears));
		eco.firstChildElement("loan-interest-rate").firstChild().setNodeValue(QString::number(econ.loanInterestRate));
		eco.firstChildElement("inflation").firstChild().setNodeValue(QString::number(econ.inflRate));
// 		eco.firstChildElement("energy-inflation").firstChild().setNodeValue(QString::number(econ.inflEnergyRate));
		eco.firstChildElement("discount").firstChild().setNodeValue(QString::number(econ.discountRate));
		eco.firstChildElement("life").firstChild().setNodeValue(QString::number(econ.life));
		eco.firstChildElement("depreciation").firstChild().setNodeValue(QString::number(econ.ammortamento));
		eco.firstChildElement("depreciation-years").firstChild().setNodeValue(QString::number(econ.ammortamentoAnni));
		eco.firstChildElement("assic").firstChild().setNodeValue(QString::number(econ.assicurazione));
		eco.firstChildElement("assic-years").firstChild().setNodeValue(QString::number(econ.assicurazioneAnni));
// 		qDebug()<<"XML Update assi"<<econ.assicurazione;
		
}

void XmlEngine::newTree()
{
// 	qDebug()<<"XML newTree";
	QStringList u;
	QString ta,pe,mpe,ba;
	u << "A1" << "B1" << "O1" << "MU";
	QDomText domLocText[16];
	root  	     	= doc.createElement("solarcalc-proj");
	localitaElement	= doc.createElement("site");
	panelElement 	= doc.createElement("pv-type");
	panelIdElement	= doc.createElement("id-pv");
	inverterIdElement= doc.createElement("id-inv");
	inverterElement =  doc.createElement("inverter-type");
	optElement	=  doc.createElement("option");	
	ecoElement      =  doc.createElement("economy-par");

	domFields = doc.createElement("fields");
		inverterElement.appendChild(domFields);
	domFields.appendChild(doc.createTextNode(""));

	domStrings = doc.createElement("strings-panels");
		inverterElement.appendChild(domStrings);
	domStrings.appendChild(doc.createTextNode(""));

	domInvertersId = doc.createElement("inverters-id");
		inverterElement.appendChild(domInvertersId);
	domInvertersId.appendChild(doc.createTextNode(""));


	domLocName = doc.createElement("name");
		localitaElement.appendChild(domLocName);
		
		domLocName.appendChild(doc.createTextNode( localita.name));

	domLocLatGradi  = doc.createElement("latgradi");
		localitaElement.appendChild(domLocLatGradi);
		domLocLatGradi.appendChild(doc.createTextNode(QString::number(0)));

	domLocLatMin  = doc.createElement("latmin");
		localitaElement.appendChild(domLocLatMin);
		domLocLatMin.appendChild(doc.createTextNode(QString::number(0)));

	domLocLatSec  = doc.createElement("latsec");
		localitaElement.appendChild(domLocLatSec);
		domLocLatSec.appendChild(doc.createTextNode(QString::number(0)));

	domLocLonGradi	= doc.createElement("longradi");
		localitaElement.appendChild(domLocLonGradi);
		domLocLonGradi.appendChild(doc.createTextNode(QString::number(0)));

	domLocLonMin  = doc.createElement("lonmin");
		localitaElement.appendChild(domLocLonMin);
		domLocLonMin.appendChild(doc.createTextNode(QString::number(0)));

	domLocLonSec  = doc.createElement("lonsec");
		localitaElement.appendChild(domLocLonSec);
		domLocLonSec.appendChild(doc.createTextNode(QString::number(0)));

	domLocAnno    = doc.createElement("anno");
		localitaElement.appendChild(domLocAnno);
		domLocAnno.appendChild(doc.createTextNode(QString::number(0)));

	domLocArea    = doc.createElement("area");
		localitaElement.appendChild(domLocArea);
		domLocArea.appendChild(doc.createTextNode(QString::number(0)));

	domLocAddArea    = doc.createElement("add-area");
		localitaElement.appendChild(domLocAddArea);
		domLocAddArea.appendChild(doc.createTextNode(""));

	domLocWind    = doc.createElement("wind");
		localitaElement.appendChild(domLocWind);
		domLocWind.appendChild(doc.createTextNode(QString::number(0)));

	domLocMounting    = doc.createElement("mounting");
		localitaElement.appendChild(domLocMounting);
		domLocMounting.appendChild(doc.createTextNode(QString::number(0)));

	domLocMountingH    = doc.createElement("mounting-height");
		localitaElement.appendChild(domLocMountingH);
		domLocMountingH.appendChild(doc.createTextNode(QString::number(0)));
	domLocConc    = doc.createElement("concratio");
		localitaElement.appendChild(domLocConc);
		domLocConc.appendChild(doc.createTextNode(QString::number(0)));

	domLocUtc     = doc.createElement("utc");
		localitaElement.appendChild(domLocUtc);
		domLocUtc.appendChild(doc.createTextNode(QString::number(0)));

	domLocAlbedo  = doc.createElement("albedo");
		localitaElement.appendChild(domLocAlbedo);
		domLocAlbedo.appendChild(doc.createTextNode(QString::number(0)));

	domLocAlbedoModel  = doc.createElement("albedo-model");
		localitaElement.appendChild(domLocAlbedoModel);
		domLocAlbedoModel.appendChild(doc.createTextNode(QString::number(0)));

	domLocIncl    = doc.createElement("tilt");
		localitaElement.appendChild(domLocIncl);
		domLocIncl.appendChild(doc.createTextNode(QString::number(0)));

	domLocAzi     = doc.createElement("azimuth");	
		localitaElement.appendChild(domLocAzi);
		domLocAzi.appendChild(doc.createTextNode(QString::number(0)));

	domLocAddIncl    = doc.createElement("add-tilt");
		localitaElement.appendChild(domLocAddIncl);
		domLocAddIncl.appendChild(doc.createTextNode(""));

	domLocAddAzi     = doc.createElement("add-azimuth");	
		localitaElement.appendChild(domLocAddAzi);
		domLocAddAzi.appendChild(doc.createTextNode(""));

	domLocRadCorr = doc.createElement("corrmodel");
		localitaElement.appendChild(domLocRadCorr);
		domLocRadCorr.appendChild(doc.createTextNode(QString::number(0)));

	domLocOmbre    = doc.createElement("ombre");
		localitaElement.appendChild(domLocOmbre);
		domLocOmbre.appendChild(doc.createTextNode(QString::number(0)));

	domLocTipo	= doc.createElement("type");
		localitaElement.appendChild(domLocTipo);
		domLocTipo.appendChild(doc.createTextNode(QString::number(0)));

	 domLocSource	= doc.createElement("source");
		localitaElement.appendChild(domLocSource);
		domLocSource.appendChild(doc.createTextNode(QString::number(0)));
	
	

	domOptNearOmbrePath	= doc.createElement("near-ombrepath"); 
 	
		optElement.appendChild(domOptNearOmbrePath);
		domOptNearOmbrePath.appendChild(doc.createTextNode(" "));

	

	domOptOmbrePath	= doc.createElement("ombrepath"); 
//  	qDebug()<<"XmlEngine Newtree..."<<opt.ombrePath;
		optElement.appendChild(domOptOmbrePath);
		domOptOmbrePath.appendChild(doc.createTextNode(" "));

	
	domThermalModel	= doc.createElement("thermal-model"); 
		optElement.appendChild(domThermalModel);
		domThermalModel.appendChild(doc.createTextNode(QString::number(0) ));


	domOptScaling	= doc.createElement("energy-scaling"); 
		optElement.appendChild(domOptScaling);
		domOptScaling.appendChild(doc.createTextNode(QString::number(0)));

// 	domOptTempPath	= doc.createElement("temppath"); 
// 		optElement.appendChild(domOptTempPath);
// 		domOptTempPath.appendChild(doc.createTextNode(" ") );
	/* Save the temperatures data inside the xml bag */
	for(int i=1;i<13;i++)	
	{
		domOptLoss[i-1]	= doc.createElement(MyMath::months(i) + "-losses"); 
		optElement.appendChild(domOptLoss[i-1]);
		domOptLoss[i-1].appendChild(doc.createTextNode(QString::number(0)));
		
		domTemperature[i-1] = doc.createElement(MyMath::months(i)+"-t");
		optElement.appendChild(domTemperature[i-1]);
		domTemperature[i-1].appendChild(doc.createTextNode(QString::number(0)));
	}
	for(int i=1;i<13;i++)	
	{
		domWind[i-1] = doc.createElement(MyMath::months(i)+"-w");
		optElement.appendChild(domWind[i-1]);
		domWind[i-1].appendChild(doc.createTextNode(QString::number(0)));
	}

	domEcoRegime = doc.createElement("regime");
		ecoElement.appendChild(domEcoRegime);
		domEcoRegime.appendChild(doc.createTextNode(""));

	domEcoBonus = doc.createElement("bonus");
		ecoElement.appendChild(domEcoBonus);
		domEcoBonus.appendChild(doc.createTextNode(""));

	domEcoBonusW = doc.createElement("bonusxWp");
		ecoElement.appendChild(domEcoBonusW);
		domEcoBonusW.appendChild(doc.createTextNode(QString::number(0)));


	domEcoFileBands = doc.createElement("file-bands");
		ecoElement.appendChild(domEcoFileBands);
		domEcoFileBands.appendChild(doc.createTextNode(""));

	for(int i=0;i<12;i++){	
		
		ba = bands.at(i);
		domEcoBands[i] = doc.createElement(ba);
		ecoElement.appendChild(domEcoBands[i]);
		domEcoBands[i].appendChild(doc.createTextNode("0-0-0"));
	}
	domEcoFileTariffe = doc.createElement("file-tariffe");
		ecoElement.appendChild(domEcoFileTariffe);
		domEcoFileTariffe.appendChild(doc.createTextNode(""));
	
	domEcoFileLoad = doc.createElement("load-file");
		ecoElement.appendChild(domEcoFileLoad);
		domEcoFileLoad.appendChild(doc.createTextNode(""));

	for(int i=0;i<12;i++)	
	{
		ta = "ta"+QString::number(i);
		pe = "pe"+QString::number(i);
	       mpe = "mpe"+QString::number(i);
		domEcoTariffe[i] = doc.createElement(ta);
		ecoElement.appendChild(domEcoTariffe[i]);
		domEcoTariffe[i].appendChild(doc.createTextNode(QString::number(0)));

		domEcoPrezziEnergia[i] = doc.createElement(pe);
		ecoElement.appendChild(domEcoPrezziEnergia[i]);
		domEcoPrezziEnergia[i].appendChild(doc.createTextNode(QString::number(0)));
	
		domEcoPrezziMinEnergia[i] = doc.createElement(mpe);
		ecoElement.appendChild(domEcoPrezziMinEnergia[i]);
		domEcoPrezziMinEnergia[i].appendChild(doc.createTextNode(QString::number(0)));


	}
	
	domEcoFilePrezziEnergia = doc.createElement("file-prezzi");
		ecoElement.appendChild(domEcoFilePrezziEnergia);
		domEcoFilePrezziEnergia.appendChild(doc.createTextNode(""));
	
	domEcoFilePrezziMinimi = doc.createElement("file-min-prezzi");
		ecoElement.appendChild(domEcoFilePrezziMinimi);
		domEcoFilePrezziMinimi.appendChild(doc.createTextNode(""));

	domEcoPrezziEnergiaModel = doc.createElement("prezzi-model");
		ecoElement.appendChild(domEcoPrezziEnergiaModel);
		domEcoPrezziEnergiaModel.appendChild(doc.createTextNode(""));

	domEcoPrezziEnergiaInflazione = doc.createElement("prezzi-energia-inflazione");
		ecoElement.appendChild(domEcoPrezziEnergiaInflazione);
		domEcoPrezziEnergiaInflazione.appendChild(doc.createTextNode(""));

	
	for (int i=0;i<4;i++)
	{
		domEcoPrezziGARCH[i] = doc.createElement(u.at(i));
		ecoElement.appendChild(domEcoPrezziGARCH[i]);
		domEcoPrezziGARCH[i].appendChild(doc.createTextNode(""));
	}

	domEcoMinPrezziEnergiaModel = doc.createElement("min-prezzi-model");
		ecoElement.appendChild(domEcoMinPrezziEnergiaModel);
		domEcoMinPrezziEnergiaModel.appendChild(doc.createTextNode(""));

	domEcoMinPrezziEnergiaInflazione = doc.createElement("min-prezzi-inflazione");
		ecoElement.appendChild(domEcoMinPrezziEnergiaInflazione);
		domEcoMinPrezziEnergiaInflazione.appendChild(doc.createTextNode(""));
	for (int i=0;i<4;i++)
	{
		domEcoMinPrezziGARCH[i] = doc.createElement("m" + u.at(i) );
		ecoElement.appendChild(domEcoMinPrezziGARCH[i]);
		domEcoMinPrezziGARCH[i].appendChild(doc.createTextNode(""));
	}

	
	domEcoMaintenanceCost = doc.createElement("maintenance");
		ecoElement.appendChild(domEcoMaintenanceCost);
		domEcoMaintenanceCost.appendChild(doc.createTextNode(""));

	domEcoMaintenanceS = doc.createElement("maintenance-s");
		ecoElement.appendChild(domEcoMaintenanceS);
		domEcoMaintenanceS.appendChild(doc.createTextNode(""));

	domEcoMaintenanceSFreq = doc.createElement("maintenance-s-freq");
		ecoElement.appendChild(domEcoMaintenanceSFreq);
		domEcoMaintenanceSFreq.appendChild(doc.createTextNode(""));

	domEcoTaxesCost = doc.createElement("taxes");
		ecoElement.appendChild(domEcoTaxesCost);
		domEcoTaxesCost.appendChild(doc.createTextNode(""));
	domEcoOtherCost = doc.createElement("other-cost");
		ecoElement.appendChild(domEcoOtherCost);
		domEcoOtherCost.appendChild(doc.createTextNode(""));
		
	
	domEcoBenefitInitialCost = doc.createElement("benefit-start");
		ecoElement.appendChild(domEcoBenefitInitialCost);
		domEcoBenefitInitialCost.appendChild(doc.createTextNode(""));
	domEcoBenefitTotalInterest	   = doc.createElement("benefit-interest");
		ecoElement.appendChild(domEcoBenefitTotalInterest);
	domEcoBenefitVAT	   = doc.createElement("benefit-VAT");
		ecoElement.appendChild(domEcoBenefitVAT);
		domEcoBenefitVAT.appendChild(doc.createTextNode(""));
	domEcoBenefitInitialCost = doc.createElement("initial-cost");
		ecoElement.appendChild(domEcoBenefitInitialCost);
		domEcoBenefitInitialCost.appendChild(doc.createTextNode(""));
	domEcoLoan	           = doc.createElement("loan");
		ecoElement.appendChild(domEcoLoan);
		domEcoLoan.appendChild(doc.createTextNode(""));
	domEcoLoanYears		   = doc.createElement("loan-years");
		ecoElement.appendChild(domEcoLoanYears);
		domEcoLoanYears.appendChild(doc.createTextNode(""));
		
	domEcoLoanInterestRate	   = doc.createElement("loan-interest-rate");
		ecoElement.appendChild(domEcoLoanInterestRate);
		domEcoLoanInterestRate.appendChild(doc.createTextNode(""));
	
	domEcoInflRate		   = doc.createElement("inflation");
		ecoElement.appendChild(domEcoInflRate);
		domEcoInflRate.appendChild(doc.createTextNode(""));
		
	domEcoInflEnergyRate	   = doc.createElement("energy-inflation");
		ecoElement.appendChild(domEcoInflEnergyRate);
		domEcoInflEnergyRate.appendChild(doc.createTextNode(""));

	domEcoDiscountRate	   = doc.createElement("discount");
		ecoElement.appendChild(domEcoDiscountRate);
		domEcoDiscountRate.appendChild(doc.createTextNode(""));

	domEcoLife		   = doc.createElement("life");
		ecoElement.appendChild(domEcoLife);
		domEcoLife.appendChild(doc.createTextNode(""));

	domEcoAmm		   = doc.createElement("depreciation");
		ecoElement.appendChild(domEcoAmm);
		domEcoAmm.appendChild(doc.createTextNode(QString::number(0)));

	domEcoAmmAnni		   = doc.createElement("depreciation-years");
		ecoElement.appendChild(domEcoAmmAnni);
		domEcoAmmAnni.appendChild(doc.createTextNode(QString::number(0)));

	domEcoAssic		   = doc.createElement("assic");
		ecoElement.appendChild(domEcoAssic);
		domEcoAssic.appendChild(doc.createTextNode(QString::number(0)));

	domEcoAssicAnni		   = doc.createElement("assic-years");
		ecoElement.appendChild(domEcoAssicAnni);
		domEcoAssicAnni.appendChild(doc.createTextNode(QString::number(0)));

	doc.appendChild(root);
	root.appendChild(localitaElement);
	root.appendChild(panelElement);
	root.appendChild(inverterElement);
	root.appendChild(optElement);
	root.appendChild(ecoElement);

	 
	panelElement.appendChild(panelIdElement);
	panelIdElement.appendChild(doc.createTextNode(QString::number(panelId)));
	inverterElement.appendChild(inverterIdElement);
	inverterIdElement.appendChild(doc.createTextNode(QString::number(inverterId)));
	
	
}
void XmlEngine::write()
{
	 
	if (!d->open(QIODevice::WriteOnly)) {
		
  		qDebug()<<"Errore scrittura Xml";
		return;
	}
	 
	updateLocTree();
	updateOptionTree();
	updateComponentsTree();
	updateEcoTree();
	QTextStream out(d) ;
	doc.save(out,4);
 	
	 
	 
}

void XmlEngine::read()
{
	QString errorStr;
	int errorLine,errorColumn;
	 if (d->open(QIODevice::ReadOnly))
		if (!doc.setContent(d,true,&errorStr,&errorLine,&errorColumn)) 
			{
			QMessageBox::warning(0,QObject::tr("Apertura progetto"),QObject::tr("Errore alla line %1 colonna %2:\n%3").arg(errorLine).arg(errorColumn).arg(errorStr));
			return;
		}

	root = doc.documentElement();
	if (root.tagName()!="solarcalc-proj")
		return;

	QDomNode node = root.firstChild();
	while (!node.isNull()) {
		if (node.toElement().tagName() == "site")
			parseSiteEntry(node.toElement());
		if (node.toElement().tagName() == "pv-type")
			parsePvEntry(node.toElement());
		if (node.toElement().tagName() == "inverter-type")
			parseInvEntry(node.toElement());
		if (node.toElement().tagName() == "option")
			parseOptEntry(node.toElement());
		if (node.toElement().tagName() == "economy-par")
			parseEcoEntry(node.toElement());
		node = node.nextSibling();
	}
}

void XmlEngine::parseEcoEntry(const QDomElement &element)
{
	QStringList u;
	 u << "A1" << "B1" << "O1" << "MU";
	econ.bands.clear();

	QDomNode node = element.firstChild();
	while (!node.isNull()){
		if (node.toElement().tagName() == "regime"){
			econ.regime = node.firstChild().toText().data().toInt();
			
		}
		if (node.toElement().tagName() == "bonus"){
			econ.bonuses = node.firstChild().toText().data().toDouble();
		
			
		}
		if (node.toElement().tagName() == "bonusxWp"){
			econ.bonusPerkWp = node.firstChild().toText().data().toDouble();
		}
		if (node.toElement().tagName() == "file-bands")
			econ.fileBands = node.firstChild().toText().data();
		if (node.toElement().tagName() == "load-file")
			econ.loadPath = node.firstChild().toText().data();
	
		for(int k=0;k<12;k++)
		{
			if (node.toElement().tagName() == bands.at(k)){
				econ.bands.append(node.firstChild().toText().data().split("-"));
}

		}
		if (node.toElement().tagName() == "file-tariffe")
			econ.fileTariffe = node.firstChild().toText().data();
		for (int i=0;i<12;i++){
			if (node.toElement().tagName() == ("ta"+ QString::number(i))){
				econ.tariffe[i] = node.firstChild().toText().data().toDouble();
			
			}
			if (node.toElement().tagName() == ("pe"+ QString::number(i))){
				econ.prezziEnergia[i] = node.firstChild().toText().data().toDouble();
			
			}
			if (node.toElement().tagName() == ("mpe"+ QString::number(i))){
				econ.prezziMinEnergia[i] = node.firstChild().toText().data().toDouble();
			
			}
	
		}
		if (node.toElement().tagName() == "file-prezzi")
			econ.filePrezziEnergia = node.firstChild().toText().data();
		if (node.toElement().tagName() == "file-min-prezzi")
			econ.filePrezziMinimi = node.firstChild().toText().data();
		if (node.toElement().tagName() == "prezzi-model")
			econ.prezziEnergiaModel = node.firstChild().toText().data().toInt();
		econ.prezziEnergiaGARCH.resize(0);
		for (int i=0;i<4;i++){
		if (node.toElement().tagName() == u.at(i))
			econ.prezziEnergiaGARCH << node.firstChild().toText().data().toDouble();
		}
		if (node.toElement().tagName() == "min-prezzi-model")
			econ.prezziMinEnergiaModel = node.firstChild().toText().data().toInt();
		for (int i=0;i<4;i++){
		if (node.toElement().tagName() == ("m"+ u.at(i)))
			econ.minPrezziEnergiaGARCH << node.firstChild().toText().data().toDouble();
		}
		if (node.toElement().tagName() == "maintenance")
			econ.maintenanceCost = node.firstChild().toText().data().toDouble();
		if (node.toElement().tagName() == "maintenance-s")
			econ.maintenanceS = node.firstChild().toText().data().toDouble();
		if (node.toElement().tagName() == "maintenance-s-freq")
			econ.maintenanceSFreq = node.firstChild().toText().data().toInt();
		if (node.toElement().tagName() == "taxes")
			econ.taxesCost = node.firstChild().toText().data().toDouble();
		if (node.toElement().tagName() == "other-cost")
			econ.otherCost = node.firstChild().toText().data().toInt();
		if (node.toElement().tagName() == "benefit-start")
			econ.benefitInitialCost = node.firstChild().toText().data().toDouble();
		if (node.toElement().tagName() == "benefit-interest")
			econ.benefitTotalInterest = node.firstChild().toText().data().toDouble();
		if (node.toElement().tagName() == "benefit-VAT")
			econ.benefitVATCost = node.firstChild().toText().data().toDouble();
		if (node.toElement().tagName() == "initial-cost")
			econ.initialCost = node.firstChild().toText().data().toDouble();
		if (node.toElement().tagName() == "loan")
			econ.loan = node.firstChild().toText().data().toDouble();
		if (node.toElement().tagName() == "loan-interest-rate")
			econ.loanInterestRate = node.firstChild().toText().data().toDouble();
		if (node.toElement().tagName() == "loan-years")
			econ.loanYears = node.firstChild().toText().data().toInt();
		if (node.toElement().tagName() == "inflation")
			econ.inflRate = node.firstChild().toText().data().toDouble();
// 		if (node.toElement().tagName() == "energy-inflation")
// 			econ.inflEnergyRate = node.firstChild().toText().data().toDouble();
		if (node.toElement().tagName() == "discount")
			econ.discountRate = node.firstChild().toText().data().toDouble();
		if (node.toElement().tagName() == "life")
			econ.life = node.firstChild().toText().data().toInt();
		if (node.toElement().tagName() == "depreciation")
			econ.ammortamento = node.firstChild().toText().data().toDouble();
		if (node.toElement().tagName() == "depreciation-years")
			econ.ammortamentoAnni = node.firstChild().toText().data().toInt();
		if (node.toElement().tagName() == "assic-years")
			econ.assicurazioneAnni = node.firstChild().toText().data().toInt();
		if (node.toElement().tagName() == "assic")
			econ.assicurazione = node.firstChild().toText().data().toDouble();
		
	node = node.nextSibling();
	}
}
void XmlEngine::parseSiteEntry(const QDomElement &element)
{	 	
	QDomNode node = element.firstChild();
	while (!node.isNull()){
		if (node.toElement().tagName() == "name")
			localita.name = node.firstChild().toText().data();
			 
		if (node.toElement().tagName() == "latgradi"){
			localita.latGradi = node.firstChild().toText().data().toInt();
			}
		if (node.toElement().tagName() == "latmin")
			localita.latMin = node.firstChild().toText().data().toInt();
		if (node.toElement().tagName() == "latsec")
			localita.latSec = node.firstChild().toText().data().toInt();
		if (node.toElement().tagName()  == "longradi")
			localita.lonGradi = node.firstChild().toText().data().toInt();
		if (node.toElement().tagName()  == "lonmin")
			localita.lonMin = node.firstChild().toText().data().toInt();
		if (node.toElement().tagName()  == "lonsec")
			localita.lonSec = node.firstChild().toText().data().toInt();
		if (node.toElement().tagName()  == "anno")
			localita.anno = node.firstChild().toText().data().toInt();
		if (node.toElement().tagName()  == "utc")
			localita.utc = node.firstChild().toText().data().toInt();
		if (node.toElement().tagName()  == "albedo")
			localita.albedo = node.firstChild().toText().data().toDouble();
		if (node.toElement().tagName()  == "albedo-model")
			localita.albedoType = node.firstChild().toText().data().toDouble();
		if (node.toElement().tagName()  == "tilt")
			localita.incl = node.firstChild().toText().data().toDouble();
		if (node.toElement().tagName()  == "add-tilt"){
			if (!node.firstChild().toText().data().isEmpty())
				localita.additionalIncl << node.firstChild().toText().data().toDouble();
		}

		if (node.toElement().tagName()  == "add-azimuth"){
			if (!node.firstChild().toText().data().isEmpty())
					localita.additionalAzi  << node.firstChild().toText().data().toDouble();			
		}
		if (node.toElement().tagName()  == "azimuth")
			localita.azi  = node.firstChild().toText().data().toDouble();

		if (node.toElement().tagName()  == "corrmodel")
			localita.radCorrModel = node.firstChild().toText().data().toInt();
		if (node.toElement().tagName()  == "ombre")
			localita.ombreModel = node.firstChild().toText().data().toInt();
		if (node.toElement().tagName()  == "type")
			localita.tipo = node.firstChild().toText().data().toInt();
		if (node.toElement().tagName()  == "area")
			localita.area = node.firstChild().toText().data().toDouble();
		if (node.toElement().tagName()  == "add-area"){
			if (!node.firstChild().toText().data().isEmpty())
				localita.additionalArea << node.firstChild().toText().data().toDouble();
		}
		if (node.toElement().tagName()  == "wind")
			localita.wind = node.firstChild().toText().data().toDouble();
		if (node.toElement().tagName()  == "mounting")
			localita.mounting = node.firstChild().toText().data().toInt();
// 			qDebug()<<"XmlEngine mountinh"<<localita.mounting;
		if (node.toElement().tagName()  == "concratio")
			localita.concRatio = node.firstChild().toText().data().toDouble();
		if (node.toElement().tagName()  == "mounting-height")
			localita.mountingHeight = node.firstChild().toText().data().toDouble();



	
		if (node.toElement().tagName()  == "source")
			localita.source = node.firstChild().toText().data().toDouble();
	node = node.nextSibling();
	}
}
void XmlEngine::parsePvEntry(const QDomElement &element)
{	 
	QDomNode node = element.firstChild();
	while (!node.isNull()){
		if (node.toElement().tagName() == "id-pv")
			panelId = node.firstChild().toText().data().toInt();
	node = node.nextSibling();
}
}
void XmlEngine::parseOptEntry(const QDomElement &element)
{	
opt.wind.resize(0);
opt.temperatures.resize(0);
opt.otherLoss.resize(0);
/* I know, it can be done better...I have no time now!*/
	 	QDomNode node = element.firstChild();
		while (!node.isNull()){
// 		if (node.toElement().tagName() == "losses")
// 			opt.otherLoss = node.firstChild().toText().data().toDouble();
		if (node.toElement().tagName() == "ombrepath")
			opt.ombrePath = node.firstChild().toText().data();
		if (node.toElement().tagName() == "near-ombrepath")
			opt.nearOmbrePath = node.firstChild().toText().data();
// 		if (node.toElement().tagName() == "temppath")
// 			opt.tempPath = node.firstChild().toText().data();
		if (node.toElement().tagName() == "thermal-model")
			opt.thermalModel = node.firstChild().toText().data().toInt();
		if (node.toElement().tagName() == "energy-scaling")
			opt.scaling = QVariant(node.firstChild().toText().data()).toBool();
		for (int i=1;i<13;i++){
				if (node.toElement().tagName() == MyMath::months(i)+"-losses")	{
					opt.otherLoss.append(node.firstChild().toText().data().toDouble());
				}
				if (node.toElement().tagName() == MyMath::months(i)+"-w")	{
// 					qDebug()<<"XML engine found w"<<MyMath::months(i)<<node.firstChild().toText().data().toDouble();
					opt.wind.append(node.firstChild().toText().data().toDouble());
				}
// 		}
// 		for (int i=1;i<13;i++){
				if (node.toElement().tagName() == MyMath::months(i)+"-t")	{
// 					qDebug()<<"XML engine found t"<<MyMath::months(i)<<node.firstChild().toText().data().toDouble();
					opt.temperatures.append(node.firstChild().toText().data().toDouble());
				}
		}

//  
	node = node.nextSibling();
}
}
void XmlEngine::parseInvEntry(const QDomElement &element)
{	 	QDomNode node = element.firstChild();
	while (!node.isNull()){
		if (node.toElement().tagName() == "id-inv")
			inverterId = node.firstChild().toText().data().toInt();
// 			qDebug()<<"XML read parseInv"<<inverterId;

		if (node.toElement().tagName() == "fields")
			systemDetails.campiVector = MyMath::toVector(node.firstChild().toText().data().split("-"));

		if (node.toElement().tagName() == "inverters-id")
			systemDetails.index = node.firstChild().toText().data().split("-");
		if (node.toElement().tagName() == "strings-panels")
			systemDetails.panelVector = MyMath::toVector(node.firstChild().toText().data().split("-"));
	node = node.nextSibling();
}
}
	 
void XmlEngine::setOption(option o)
{
	opt = o;
	updateOptionTree();
//     	qDebug()<<"XmlEngine ho chiamato setOption"<<opt.ombrePath<<opt.tempPath<<opt.temperatures;
}	 
 
void XmlEngine::setLoc(loc l)
{
	localita = l;
	updateLocTree();
//    	qDebug()<<"XmlEngine ho chiamato setLoc"<<localita.mountingHeight;
}
void XmlEngine::setEcoParameters(ecopara o)
{
	econ = o;
	updateEcoTree();
//     	qDebug()<<"XmlEngine ho chiamato setEcoParameters"<<econ.assicurazione;
}

void XmlEngine::setPanelId(int i)
{
// 	qDebug()<<"XmlEngine setpanelid"<<i;
	panelId =i;
	updateComponentsTree();
}

void XmlEngine::setInverterId(int i)
{
	inverterId = i;
	updateComponentsTree();
}
int XmlEngine::getPanelId()
{
// 	QString s = doc.documentElement().firstChildElement("pv-type").firstChildElement("id-pv").firstChild().toText().data();;
// 	
// 	return s.toInt();
	return panelId;
}
int XmlEngine::getInverterId()
{
	 
// 	QString s = doc.documentElement().firstChildElement("inv-type").firstChildElement("id-inv").firstChild().toText().data();;
// 	qDebug()<<"XML getInverterID"<<s;
// 	return s.toInt();
	return inverterId;
}
void XmlEngine::setFile(QFile *f)
{
	d  = f;
}

loc XmlEngine::getLoc()
{
// 	qDebug()<<"XmlEngine getLoc"<<localita.latGradi;
	return localita;
}
 
option XmlEngine::getOption()
{
	return opt;
}
 

ecopara XmlEngine::getEcoParameters()
{
	return econ;
}
void XmlEngine::setSystem(QList<inverter> a,sy s)
{
	inverters = a;
	systemDetails = s;
	updateInvertersTree();
// 	qDebug()<<"XML ho chiamato updateInverters()";
}
sy XmlEngine::getSystem()
{
	return systemDetails;
}
 