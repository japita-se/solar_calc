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
         //SOME INITIALIZATION //
         for(int i=0;i<econ.taxes_size;i++) econ.taxes[i] = 0;
         for(int i=0;i<econ.tariffe_size;i++)
               econ.tariffe << QVector<double>(1,0);


	 bands<<"F1"<<"F2"<<"F3"<<"F4"<<"F5"<<"F6"<<"F1S"<<"F2S"<<"F3S"<<"F1D"<<"F2D"<<"F3D";	
	econ.assicurazione = 0;
	econ.assicurazioneAnni = 0;
        //resetEco();
	
}
void XmlEngine::updateDetailsTree()
{
     QDomElement d = doc.documentElement().firstChildElement("designer");
     d.firstChildElement("name").firstChild().setNodeValue(details.name);
     d.firstChildElement("revisor").firstChild().setNodeValue(details.name_r);
     d.firstChildElement("client").firstChild().setNodeValue(details.clientName);
     d.firstChildElement("client-address").firstChild().setNodeValue(details.clientAddress);
     d.firstChildElement("date").firstChild().setNodeValue(details.date.toString("dd.MM.yyyy"));
     d.firstChildElement("notes").firstChild().setNodeValue(details.notes);
     d.firstChildElement("title").firstChild().setNodeValue(details.title);
     d.firstChildElement("albo").firstChild().setNodeValue(details.albo);
     d.firstChildElement("logopath").firstChild().setNodeValue(details.logoPath);
     d.firstChildElement("company").firstChild().setNodeValue(details.company);
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
            site.firstChildElement("latsec").firstChild().setNodeValue(QString::number(localita.latSec,'f',8));
	    site.firstChildElement("longradi").firstChild().setNodeValue(QString::number(localita.lonGradi));
	    site.firstChildElement("lonmin").firstChild().setNodeValue(QString::number(localita.lonMin));
            site.firstChildElement("lonsec").firstChild().setNodeValue(QString::number(localita.lonSec,'f',8));
	    site.firstChildElement("altitude").firstChild().setNodeValue(QString::number(localita.alt));

	    site.firstChildElement("anno").firstChild().setNodeValue(QString::number(localita.anno));
	    site.firstChildElement("area").firstChild().setNodeValue(QString::number(localita.area));
	
	    if (localita.additionalArea.size()==1)
	    	site.firstChildElement("add-area").firstChild().setNodeValue(QString::number(localita.additionalArea.at(0)));
		else
		site.firstChildElement("add-area").firstChild().setNodeValue("");

	    site.firstChildElement("wind").firstChild().setNodeValue(QString::number(localita.wind));
site.firstChildElement("min-t").firstChild().setNodeValue(QString::number(localita.tempMin));
site.firstChildElement("max-t").firstChild().setNodeValue(QString::number(localita.tempMax));
	    site.firstChildElement("mounting").firstChild().setNodeValue(QString::number(localita.mounting));
	    site.firstChildElement("mounting-height").firstChild().setNodeValue(QString::number(localita.mountingHeight));
            site.firstChildElement("tracker-dim").firstChild().setNodeValue(QString::number(localita.trackerArea));
	 
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
            site.firstChildElement("add-azimuth").firstChild().setNodeValue(QString::number(localita.additionalAzi.at(0)));
	else
            site.firstChildElement("add-azimuth").firstChild().setNodeValue("");



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
                 option.firstChildElement(MyMath::monthsIta(i)+"-losses").firstChild().setNodeValue(QString::number(opt.otherLoss.at(i-1)));
                option.firstChildElement(MyMath::monthsIta(i)+"-t").firstChild().setNodeValue(
										QString::number(opt.temperatures.at(i-1)));
                option.firstChildElement(MyMath::monthsIta(i)+"-w").firstChild().setNodeValue(
										QString::number(opt.wind.at(i-1)));
		
	}
}
void XmlEngine::updateEcoTree()
{
QString ba,pe,mpe,ta,tax,sep;
QStringList u;
u << "A1" << "B1" << "O1" << "MU";
sep="-";
/*TO FINISH*/
	QDomElement eco = doc.documentElement().firstChildElement("economy-par");
//  		qDebug()<<"XMLEngine debug  ECO updateTree"<< econ.regime<<econ.maintenanceCost;

eco.firstChildElement("power").firstChild().setNodeValue(QString::number(econ.power));	eco.firstChildElement("regime").firstChild().setNodeValue(QString::number(econ.regime));
		eco.firstChildElement("bonus").firstChild().setNodeValue(QString::number(econ.bonuses));
eco.firstChildElement("bonus-years").firstChild().setNodeValue(QString::number(econ.bonusesYears));
		eco.firstChildElement("bonusxWp").firstChild().setNodeValue(QString::number(econ.bonusPerkWp));
eco.firstChildElement("file-bands").firstChild().setNodeValue(econ.fileBands);
eco.firstChildElement("file-tariffe").firstChild().setNodeValue(econ.fileTariffe);
eco.firstChildElement("file-taxes").firstChild().setNodeValue(econ.fileTax);
 //TASSE in BOLLETTA//

eco.firstChildElement("vat-payedEn").firstChild().setNodeValue(QString::number(econ.VATonTotEnergy));
eco.firstChildElement("imp-kwh").firstChild().setNodeValue(QString::number(econ.IMPonEnergy));

/* BANDE DI CONSUMO */

eco.firstChildElement("LI").firstChild().setNodeValue(MyMath::toString(econ.intervals,sep));
/* BANDE DI ORARIE */
	for(int i=0;i<bands.size();i++){	

        ba = bands.at(i);
                eco.firstChildElement(ba).firstChild().setNodeValue(econ.bands[i].join("-"));

		
		
	}


        //TASSE SU REDDITI//
        for (int i=0;i<econ.taxes_size;i++){

                tax = "tax-income"+QString::number(i);
                eco.firstChildElement(tax).firstChild().setNodeValue(QString::number(econ.taxes[i]));
        }
        //IMMISSIONE//
        eco.firstChildElement("use-imm-int").firstChild().setNodeValue(QString::number(econ.useImmIntervals ? 1 : 0));
        eco.firstChildElement("PI").firstChild().setNodeValue(MyMath::toString(econ.pIntervals,sep));

        eco.firstChildElement("rid-prices").firstChild().setNodeValue(MyMath::toString(econ.immissione,sep));

        //TARIFFE//
        eco.firstChildElement("TI").firstChild().setNodeValue(MyMath::toString(econ.tIntervals,sep));
        for (int i=0;i<econ.tariffe_size;i++){
                ta = "ta"+QString::number(i);
                eco.firstChildElement(ta).firstChild().setNodeValue(
                        MyMath::toString(econ.tariffe[i],sep));

        }
        //PREZZI//
	for (int i=0;i<12;i++)
	{

		pe = "pe"+QString::number(i);
	       mpe = "mpe"+QString::number(i);

               eco.firstChildElement(pe).firstChild().
                       setNodeValue(MyMath::toStringList(econ.prezziEnergia[i],12).join(" "));
		eco.firstChildElement(mpe).firstChild().setNodeValue(QString::number(econ.prezziMinEnergia[i]));
// 		qDebug()<<"XML prezzi"<<econ.prezziEnergia[i]<<econ.prezziMinEnergia[i];
	}

		eco.firstChildElement("load-file").firstChild().setNodeValue((econ.loadPath));
		eco.firstChildElement("file-prezzi").firstChild().setNodeValue(econ.filePrezziEnergia);
		eco.firstChildElement("file-min-prezzi").firstChild().setNodeValue(econ.filePrezziMinimi);
		eco.firstChildElement("prezzi-model").firstChild().setNodeValue(QString::number(econ.prezziEnergiaModel));
                eco.firstChildElement("prezzi-energia-inflazione").firstChild().setNodeValue(QString::number(econ.prezziEnergiaInflazione));
                eco.firstChildElement("bands-inflation").firstChild().setNodeValue(QString::number(econ.fasceInflazione));
		
	for (int i=0;i<4;i++)
	{
		eco.firstChildElement(u.at(i)).firstChild().setNodeValue(QString::number(econ.prezziEnergiaGARCH.at(i)));
		
		
	}

        eco.firstChildElement("min-prezzi-inflazione").firstChild().setNodeValue(QString::number(econ.prezziMinEnergiaInflazione));
	eco.firstChildElement("min-prezzi-model").firstChild().setNodeValue(QString::number(econ.prezziMinEnergiaModel));
		
	for (int i=0;i<4;i++)
	{
		eco.firstChildElement("m"+u.at(i)).firstChild().setNodeValue(QString::number(econ.minPrezziEnergiaGARCH.at(i)));
	}

	
        eco.firstChildElement("rents").firstChild().setNodeValue(QString::number(econ.affitti));
eco.firstChildElement("credit").firstChild().setNodeValue(QString::number(econ.credit));	eco.firstChildElement("maintenance").firstChild().setNodeValue(QString::number(econ.maintenanceCost));
		eco.firstChildElement("maintenance-s").firstChild().setNodeValue(QString::number(econ.maintenanceS));
		eco.firstChildElement("maintenance-s-freq").firstChild().setNodeValue(QString::number(econ.maintenanceSFreq));
		eco.firstChildElement("taxes").firstChild().setNodeValue(QString::number(econ.taxesCost));
		eco.firstChildElement("other-cost").firstChild().setNodeValue(QString::number(econ.otherCost));
			
                eco.firstChildElement("benefit-taxes").firstChild().setNodeValue(QString::number(econ.benefitTaxes));
                eco.firstChildElement("benefit-start").firstChild().setNodeValue(QString::number(econ.benefitInitialCost));
		eco.firstChildElement("benefit-interest").firstChild().setNodeValue(QString::number(econ.benefitTotalInterest));
		eco.firstChildElement("benefit-VAT").firstChild().setNodeValue(QString::number(econ.benefitVATCost));
		eco.firstChildElement("initial-cost").firstChild().setNodeValue(QString::number(econ.initialCost));
                eco.firstChildElement("vat").firstChild().setNodeValue(QString::number(econ.vat));
		eco.firstChildElement("loan").firstChild().setNodeValue(QString::number(econ.loan));
		eco.firstChildElement("loan-years").firstChild().setNodeValue(QString::number(econ.loanYears));
		eco.firstChildElement("loan-interest-rate").firstChild().setNodeValue(QString::number(econ.loanInterestRate));
		eco.firstChildElement("inflation").firstChild().setNodeValue(QString::number(econ.inflRate));
               // eco.firstChildElement("energy-inflation").firstChild().setNodeValue(QString::number(econ.inflEnergyRate));
		eco.firstChildElement("discount").firstChild().setNodeValue(QString::number(econ.discountRate));
		eco.firstChildElement("life").firstChild().setNodeValue(QString::number(econ.life));
		eco.firstChildElement("depreciation").firstChild().setNodeValue(QString::number(econ.ammortamento));
		eco.firstChildElement("depreciation-years").firstChild().setNodeValue(QString::number(econ.ammortamentoAnni));
		eco.firstChildElement("assic").firstChild().setNodeValue(QString::number(econ.assicurazione));
		eco.firstChildElement("assic-years").firstChild().setNodeValue(QString::number(econ.assicurazioneAnni));


                eco.firstChildElement("cost-limit").firstChild().setNodeValue(QString::number(econ.ammCostLimit));
                eco.firstChildElement("sim-options").firstChild().setNodeValue(MyMath::toStringList(econ.simoptions).join("-"));
		
}

void XmlEngine::newTree()
{
// 	qDebug()<<"XML newTree";
	QStringList u;
        QString ta,pe,mpe,ba,tax;
	u << "A1" << "B1" << "O1" << "MU";

	root  	     	= doc.createElement("solarcalc-proj");
        detailsElement  = doc.createElement("designer");
	localitaElement	= doc.createElement("site");
	panelElement 	= doc.createElement("pv-type");
	panelIdElement	= doc.createElement("id-pv");
	inverterIdElement= doc.createElement("id-inv");
	inverterElement =  doc.createElement("inverter-type");
	optElement	=  doc.createElement("option");	
	ecoElement      =  doc.createElement("economy-par");


        domDetailsName = doc.createElement("name");
        domDetailsName.appendChild(doc.createTextNode(""));
        detailsElement.appendChild(domDetailsName);

        domDetailsNameR = doc.createElement("revisor");
        domDetailsNameR.appendChild(doc.createTextNode(""));
        detailsElement.appendChild(domDetailsNameR);

        domDetailsClient = doc.createElement("client");
        domDetailsClient.appendChild(doc.createTextNode(""));
        detailsElement.appendChild(domDetailsClient);

        domDetailsClientAddress = doc.createElement("client-address");
        domDetailsClientAddress.appendChild(doc.createTextNode(""));
        detailsElement.appendChild(domDetailsClientAddress);

        domDetailsNotes = doc.createElement("notes");
        domDetailsNotes.appendChild(doc.createTextNode(""));
        detailsElement.appendChild(domDetailsNotes);

        domDetailsDate = doc.createElement("date");
        domDetailsDate.appendChild(doc.createTextNode(""));
        detailsElement.appendChild(domDetailsDate);

        domDetailsCompany = doc.createElement("company");
        domDetailsCompany.appendChild(doc.createTextNode(""));
        detailsElement.appendChild(domDetailsCompany);

        domDetailsAlbo = doc.createElement("albo");
        domDetailsAlbo.appendChild(doc.createTextNode(""));
        detailsElement.appendChild(domDetailsAlbo);

        domDetailsTitle = doc.createElement("title");
        domDetailsTitle.appendChild(doc.createTextNode(""));
        detailsElement.appendChild(domDetailsTitle);

        domDetailsLogo = doc.createElement("logopath");
        domDetailsLogo.appendChild(doc.createTextNode(""));
        detailsElement.appendChild(domDetailsLogo);

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
		domLocLatGradi.appendChild(doc.createTextNode(QString::number(-999)));

	domLocLatMin  = doc.createElement("latmin");
		localitaElement.appendChild(domLocLatMin);
		domLocLatMin.appendChild(doc.createTextNode(QString::number(-999)));

	domLocLatSec  = doc.createElement("latsec");
		localitaElement.appendChild(domLocLatSec);
		domLocLatSec.appendChild(doc.createTextNode(QString::number(-999)));

	domLocLonGradi	= doc.createElement("longradi");
		localitaElement.appendChild(domLocLonGradi);
		domLocLonGradi.appendChild(doc.createTextNode(QString::number(-999)));

	domLocLonMin  = doc.createElement("lonmin");
		localitaElement.appendChild(domLocLonMin);
		domLocLonMin.appendChild(doc.createTextNode(QString::number(-999)));

	domLocLonSec  = doc.createElement("lonsec");
		localitaElement.appendChild(domLocLonSec);
		domLocLonSec.appendChild(doc.createTextNode(QString::number(-999)));

	domLocAltitude  = doc.createElement("altitude");
		localitaElement.appendChild(domLocAltitude);
		domLocAltitude.appendChild(doc.createTextNode(QString::number(0)));

	domLocAnno    = doc.createElement("anno");
		localitaElement.appendChild(domLocAnno);
		domLocAnno.appendChild(doc.createTextNode(QString::number(0)));

	domLocArea    = doc.createElement("area");
		localitaElement.appendChild(domLocArea);
		domLocArea.appendChild(doc.createTextNode(QString::number(0)));

	domLocAddArea    = doc.createElement("add-area");
		localitaElement.appendChild(domLocAddArea);
		domLocAddArea.appendChild(doc.createTextNode(""));

        domLocMinT    = doc.createElement("min-t");
                        localitaElement.appendChild(domLocMinT);
                        domLocMinT.appendChild(doc.createTextNode(QString::number(0)));
        domLocMaxT    = doc.createElement("max-t");
                        localitaElement.appendChild(domLocMaxT);
                        domLocMaxT.appendChild(doc.createTextNode(QString::number(0)));

	domLocWind    = doc.createElement("wind");
		localitaElement.appendChild(domLocWind);
		domLocWind.appendChild(doc.createTextNode(QString::number(0)));

	domLocMounting    = doc.createElement("mounting");
		localitaElement.appendChild(domLocMounting);
		domLocMounting.appendChild(doc.createTextNode(QString::number(0)));

	domLocMountingH    = doc.createElement("mounting-height");
		localitaElement.appendChild(domLocMountingH);
		domLocMountingH.appendChild(doc.createTextNode(QString::number(0)));
        domLocTrackerDim    = doc.createElement("tracker-dim");
                localitaElement.appendChild(domLocTrackerDim);
                domLocTrackerDim.appendChild(doc.createTextNode(QString::number(0)));

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
                domOptLoss[i-1]	= doc.createElement(MyMath::monthsIta(i) + "-losses");
		optElement.appendChild(domOptLoss[i-1]);
		domOptLoss[i-1].appendChild(doc.createTextNode(QString::number(0)));
		
                domTemperature[i-1] = doc.createElement(MyMath::monthsIta(i)+"-t");
		optElement.appendChild(domTemperature[i-1]);
		domTemperature[i-1].appendChild(doc.createTextNode(QString::number(0)));
	}
	for(int i=1;i<13;i++)	
	{
                domWind[i-1] = doc.createElement(MyMath::monthsIta(i)+"-w");
		optElement.appendChild(domWind[i-1]);
		domWind[i-1].appendChild(doc.createTextNode(QString::number(0)));
	}

        domEcoPower = doc.createElement("power");
                ecoElement.appendChild(domEcoPower);
                domEcoPower.appendChild(doc.createTextNode(QString::number(0)));
	domEcoRegime = doc.createElement("regime");
		ecoElement.appendChild(domEcoRegime);
		domEcoRegime.appendChild(doc.createTextNode(""));

	domEcoBonus = doc.createElement("bonus");
		ecoElement.appendChild(domEcoBonus);
		domEcoBonus.appendChild(doc.createTextNode(""));
        domEcoBonusYears = doc.createElement("bonus-years");
                ecoElement.appendChild(domEcoBonusYears);
                domEcoBonusYears.appendChild(doc.createTextNode(QString::number(0)));

	domEcoBonusW = doc.createElement("bonusxWp");
		ecoElement.appendChild(domEcoBonusW);
		domEcoBonusW.appendChild(doc.createTextNode(QString::number(0)));


        domEcoFileBands = doc.createElement("file-bands");
                ecoElement.appendChild(domEcoFileBands);
                domEcoFileBands.appendChild(doc.createTextNode(""));


        /* BANDE ORARIE */


                domEcoLI = doc.createElement("LI");
                domEcoLI.appendChild(doc.createTextNode(""));
                ecoElement.appendChild(domEcoLI);

	for(int i=0;i<12;i++){	
		
		ba = bands.at(i);
		domEcoBands[i] = doc.createElement(ba);
		ecoElement.appendChild(domEcoBands[i]);
		domEcoBands[i].appendChild(doc.createTextNode("0-0-0"));
	}
        //TASSE in BOLLETTA//
        domEcoVatOnEn = doc.createElement("vat-payedEn");
            ecoElement.appendChild(domEcoVatOnEn);
            domEcoVatOnEn.appendChild(doc.createTextNode(QString::number(0)));
        domEcoIMPOnkWh = doc.createElement("imp-kwh");
            ecoElement.appendChild(domEcoIMPOnkWh);
            domEcoIMPOnkWh.appendChild(doc.createTextNode(QString::number(0)));

        domEcoFileTariffe = doc.createElement("file-tariffe");
                ecoElement.appendChild(domEcoFileTariffe);
                domEcoFileTariffe.appendChild(doc.createTextNode(""));
	
	domEcoFileLoad = doc.createElement("load-file");
		ecoElement.appendChild(domEcoFileLoad);
		domEcoFileLoad.appendChild(doc.createTextNode(""));

        domEcoFileTax = doc.createElement("file-taxes");
                ecoElement.appendChild(domEcoFileTax);
                domEcoFileTax.appendChild(doc.createTextNode(""));

        //Tasse sui redditi//
        for(int i=0;i<econ.taxes_size;i++)	{

                tax = "tax-income"+QString::number(i);
                domEcoTaxes[i] = doc.createElement(tax);
                ecoElement.appendChild(domEcoTaxes[i]);
                domEcoTaxes[i].appendChild(doc.createTextNode(QString::number(0)));
         }
        //IMMISSIONE //
        domEcoPI = doc.createElement("PI");
        domEcoPI.appendChild(doc.createTextNode(""));
        ecoElement.appendChild(domEcoPI);

        domEcoUseImmIntervals = doc.createElement("use-imm-int");
        domEcoUseImmIntervals.appendChild(doc.createTextNode(QString::number(0)));
        ecoElement.appendChild(domEcoUseImmIntervals);

        domEcoImmissione = doc.createElement("rid-prices");
        domEcoImmissione.appendChild(doc.createTextNode(""));
        ecoElement.appendChild(domEcoImmissione);


        //TARIFFE//

        domEcoTI = doc.createElement("TI");
        domEcoTI.appendChild(doc.createTextNode(""));
        ecoElement.appendChild(domEcoTI);

        for(int i=0;i<econ.tariffe_size;i++)	{
                ta = "ta"+QString::number(i);
                domEcoTariffe[i] = doc.createElement(ta);
                ecoElement.appendChild(domEcoTariffe[i]);
                domEcoTariffe[i].appendChild(doc.createTextNode(QString::number(0)));
                }
	for(int i=0;i<12;i++)	
	{

		pe = "pe"+QString::number(i);
	       mpe = "mpe"+QString::number(i);



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

        domEcoCredit = doc.createElement("credit");
                ecoElement.appendChild(domEcoCredit);
                domEcoCredit.appendChild(doc.createTextNode(QString::number(0)));

        domEcoRents = doc.createElement("rents");
                ecoElement.appendChild(domEcoRents);
                domEcoRents.appendChild(doc.createTextNode(""));
	
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
		
        domEcoBenefitTaxes = doc.createElement("benefit-taxes");
                ecoElement.appendChild(domEcoBenefitTaxes);
                domEcoBenefitTaxes.appendChild(doc.createTextNode(""));
	
	domEcoBenefitInitialCost = doc.createElement("benefit-start");
		ecoElement.appendChild(domEcoBenefitInitialCost);
		domEcoBenefitInitialCost.appendChild(doc.createTextNode(""));

	domEcoBenefitTotalInterest	   = doc.createElement("benefit-interest");
		ecoElement.appendChild(domEcoBenefitTotalInterest);
                domEcoBenefitTotalInterest.appendChild(doc.createTextNode(""));

	domEcoBenefitVAT	   = doc.createElement("benefit-VAT");
		ecoElement.appendChild(domEcoBenefitVAT);
		domEcoBenefitVAT.appendChild(doc.createTextNode(""));
	domEcoBenefitInitialCost = doc.createElement("initial-cost");
		ecoElement.appendChild(domEcoBenefitInitialCost);
		domEcoBenefitInitialCost.appendChild(doc.createTextNode(""));
                domEcoVat = doc.createElement("vat");
                        ecoElement.appendChild(domEcoVat);
                        domEcoVat.appendChild(doc.createTextNode(""));
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
		
//	domEcoInflEnergyRate	   = doc.createElement("energy-inflation");
//		ecoElement.appendChild(domEcoInflEnergyRate);
//		domEcoInflEnergyRate.appendChild(doc.createTextNode(""));

        domEcoBandsInflRate	   = doc.createElement("bands-inflation");
                ecoElement.appendChild(domEcoBandsInflRate);
                domEcoBandsInflRate.appendChild(doc.createTextNode(""));

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

        domEcoAmmLimit = doc.createElement("cost-limit");
                ecoElement.appendChild(domEcoAmmLimit);
                domEcoAmmLimit.appendChild(doc.createTextNode(""));


        domEcoSimOptions = doc.createElement("sim-options");
                ecoElement.appendChild(domEcoSimOptions);
                domEcoSimOptions.appendChild(doc.createTextNode("0-0"));

	doc.appendChild(root);
        root.appendChild(detailsElement);
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
        updateDetailsTree();
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
            if (node.toElement().tagName() == "designer")
                    parseDetailsEntry(node.toElement());

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

void XmlEngine::parseDetailsEntry(const QDomElement &element)
{
    QDomNode node = element.firstChild();
    while (!node.isNull()){
        qDebug()<<"XML parse details";
        if (node.toElement().tagName() == "name")
           details.name = node.firstChild().toText().data();
        if (node.toElement().tagName() == "title")
           details.title = node.firstChild().toText().data();
        if (node.toElement().tagName() == "revisor")
           details.name_r = node.firstChild().toText().data();
        if (node.toElement().tagName() == "client")
           details.clientName = node.firstChild().toText().data();
        if (node.toElement().tagName() == "client-address")
           details.clientAddress = node.firstChild().toText().data();
        if (node.toElement().tagName() == "notes")
           details.notes = node.firstChild().toText().data();
        if (node.toElement().tagName() == "company")
               details.company = node.firstChild().toText().data();
        if (node.toElement().tagName() == "albo")
           details.albo = node.firstChild().toText().data();
        if (node.toElement().tagName() == "logopath")
           details.logoPath = node.firstChild().toText().data();
        if (node.toElement().tagName() == "date")
            details.date =
                    QDate::fromString(node.firstChild().toText().data(),"dd.MM.YYY");
        node = node.nextSibling();
    }
}

void XmlEngine::parseEcoEntry(const QDomElement &element)
{
	QStringList u;
        QStringList j,jt,jp;
        QPolygonF   jh,jht,jhp;
	 u << "A1" << "B1" << "O1" << "MU";
	econ.bands.clear();

	QDomNode node = element.firstChild();
	while (!node.isNull()){
            if (node.toElement().tagName() == "power"){
                    econ.power = node.firstChild().toText().data().toDouble();
                }
		if (node.toElement().tagName() == "regime"){
			econ.regime = node.firstChild().toText().data().toInt();
			
		}
		if (node.toElement().tagName() == "bonus"){
			econ.bonuses = node.firstChild().toText().data().toDouble();
		
			
		}
                if (node.toElement().tagName() == "bonus-years"){
                        econ.bonusesYears = node.firstChild().toText().data().toInt();


                }
		if (node.toElement().tagName() == "bonusxWp"){
			econ.bonusPerkWp = node.firstChild().toText().data().toDouble();
		}
                if (node.toElement().tagName() == "file-bands")
                        econ.fileBands = node.firstChild().toText().data();
		if (node.toElement().tagName() == "load-file")
			econ.loadPath = node.firstChild().toText().data();
	

                /*BANDE*/



                if (node.toElement().tagName() == "LI"){

                  j = node.firstChild().toText().data().split("-");
   qDebug()<<"XML LI"<<j.size()%2<<j.size()<<j<<node.toText().data()<<node.toElement().tagName();
                  if (j.size()%2!=0){
                    qDebug()<<"XML read: ERROR IN LI";
                    }
                    else{
                        for(int k=0;k<j.size()/2;k++){
                        jh << QPointF(j.at(2*k).toDouble(),j.at(2*k+1).toDouble());
                    //    qDebug()<<"XML LI";
                        }
                        econ.intervals << jh;
                    }

                }

		for(int k=0;k<12;k++)
		{
			if (node.toElement().tagName() == bands.at(k)){
				econ.bands.append(node.firstChild().toText().data().split("-"));

                         }

		}

                if (node.toElement().tagName() == "file-tariffe")
                        econ.fileTariffe = node.firstChild().toText().data();
                if (node.toElement().tagName() == "file-taxes")
                        econ.fileTax = node.firstChild().toText().data();
                //TASSE in BOLLETTA//
                if (node.toElement().tagName() == "vat-payedEn")
                        econ.VATonTotEnergy = node.firstChild().toText().data().toDouble();
                if (node.toElement().tagName() == "imp-kwh")
                        econ.IMPonEnergy = node.firstChild().toText().data().toDouble();
                //TASSE SUI REDDITI//
                for (int i=0;i<econ.taxes_size;i++){

                        if (node.toElement().tagName() == ("tax-income"+ QString::number(i))){
                            econ.taxes[i] = node.firstChild().toText().data().toDouble();
                        }
                    }
                //IMMISSIONE//
                if (node.toElement().tagName() == "use-imm-int"){
                    if (node.firstChild().toText().data().toInt()==0)
                    econ.useImmIntervals = false;
                    else
                    econ.useImmIntervals = true;
                }

                if (node.toElement().tagName() == "rid-prices"){
                    econ.immissione =
                            MyMath::toVectorDouble(node.firstChild().toText().data().split("-"));
                }


                if (node.toElement().tagName() == "PI"){
                     jp = node.firstChild().toText().data().split("-");
                     if (jp.size()%2!=0)
                         qDebug()<<"XML read: ERROR IN PI";
                     else{
                         for(int k=0;k<jp.size()/2;k++){
                         jhp << QPointF(jp.at(2*k).toDouble(),jp.at(2*k+1).toDouble());
                          //qDebug()<<"XML PI"<<jhp;
                         }
                         econ.pIntervals << jhp;
                     }

                 }


                //TARIFFE//
                if (node.toElement().tagName() == "TI"){

                  jt = node.firstChild().toText().data().split("-");
  // qDebug()<<"XML TI"<<jt.size()%2<<jt.size()<<t<<node.toText().data()<<node.toElement().tagName();
                    if (jt.size()%2!=0)
                        qDebug()<<"XML read: ERROR IN TI";
                    else{
                        for(int k=0;k<jt.size()/2;k++){
                        jht << QPointF(jt.at(2*k).toDouble(),jt.at(2*k+1).toDouble());
                    //    qDebug()<<"XML TI";
                        }
                        econ.tIntervals << jht;
                    }

                }

                for (int i=0;i<econ.tariffe_size;i++){
                    if (node.toElement().tagName() == ("ta"+ QString::number(i))){
                        econ.tariffe[i] =
                                QVector<double>(MyMath::toVectorDouble(
                                        node.firstChild().toText().data().split("-")));
                     //   qDebug()<<"XMLTARIFFE"<< node.firstChild().toText().data()<<econ.tariffe[21];
                    }
                }


                // PREZZI ENERGIA//
                QVector<double> tpe;
                for (int i=0;i<12;i++){

			if (node.toElement().tagName() == ("pe"+ QString::number(i))){

                            tpe = MyMath::toVectorDouble(node.firstChild().toText().data().split(" "));
                            for (int j=0; j<econ.numBands;j++)
                            {
                                if (j<tpe.size())
                                    econ.prezziEnergia[i][j] = tpe.at(j);
                                else
                                {
                                   // qDebug()<<"XML WARNING AT PREZZI ENERGIA";
                                    econ.prezziEnergia[i][j] = 0;
                                }
                            }
			
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
                if (node.toElement().tagName() == "credit")
                    econ.credit = (bool)(node.firstChild().toText().data().toInt());
                if (node.toElement().tagName() == "rents")
                        econ.affitti = node.firstChild().toText().data().toDouble();
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
                if (node.toElement().tagName() == "benefit-taxes")
                        econ.benefitTaxes = node.firstChild().toText().data().toDouble();
		if (node.toElement().tagName() == "benefit-start")
			econ.benefitInitialCost = node.firstChild().toText().data().toDouble();
		if (node.toElement().tagName() == "benefit-interest")
			econ.benefitTotalInterest = node.firstChild().toText().data().toDouble();
		if (node.toElement().tagName() == "benefit-VAT")
			econ.benefitVATCost = node.firstChild().toText().data().toDouble();
                if (node.toElement().tagName() == "vat")
                        econ.vat = node.firstChild().toText().data().toDouble();
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
                //if (node.toElement().tagName() == "energy-inflation")
                  //      econ.inflEnergyRate = node.firstChild().toText().data().toDouble();
                if (node.toElement().tagName() == "prezzi-energia-inflazione")
                      econ.prezziEnergiaInflazione = node.firstChild().toText().data().toDouble();
                if (node.toElement().tagName() == "min-prezzi-inflazione")
                      econ.prezziMinEnergiaInflazione = node.firstChild().toText().data().toDouble();
                if (node.toElement().tagName() == "bands-inflation")
                        econ.fasceInflazione = node.firstChild().toText().data().toDouble();
		if (node.toElement().tagName() == "discount")
			econ.discountRate = node.firstChild().toText().data().toDouble();
		if (node.toElement().tagName() == "life")
			econ.life = node.firstChild().toText().data().toInt();
		if (node.toElement().tagName() == "depreciation")
			econ.ammortamento = node.firstChild().toText().data().toDouble();
		if (node.toElement().tagName() == "depreciation-years")
                        econ.ammortamentoAnni = node.firstChild().toText().data().toDouble();
		if (node.toElement().tagName() == "assic-years")
			econ.assicurazioneAnni = node.firstChild().toText().data().toInt();
		if (node.toElement().tagName() == "assic")
			econ.assicurazione = node.firstChild().toText().data().toDouble();
                if (node.toElement().tagName() == "cost-limit")
                    econ.ammCostLimit =         node.firstChild().toText().data().toDouble();
                if (node.toElement().tagName() == "sim-options"){
                    econ.simoptions = MyMath::toVector(node.firstChild().toText().data().split("-"));
                //qDebug()<<"XML SIMOPTIONS"<<econ.simoptions<<node.firstChild().toText().data().split("-");
            }
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
                        localita.latMin = MyMath::convertToDouble(node.firstChild().toText().data());
		if (node.toElement().tagName() == "latsec")
                    localita.latSec = MyMath::convertToDouble(node.firstChild().toText().data());
		if (node.toElement().tagName()  == "longradi")
			localita.lonGradi = node.firstChild().toText().data().toInt();
		if (node.toElement().tagName()  == "lonmin")
                        localita.lonMin = MyMath::convertToDouble(node.firstChild().toText().data());
		if (node.toElement().tagName()  == "lonsec")
                        localita.lonSec = MyMath::convertToDouble(node.firstChild().toText().data());

		if (node.toElement().tagName()  == "altitude")
			localita.alt = node.firstChild().toText().data().toDouble();
		if (node.toElement().tagName()  == "anno")
			localita.anno = node.firstChild().toText().data().toInt();
		if (node.toElement().tagName()  == "utc")
			localita.utc = node.firstChild().toText().data().toInt();
		if (node.toElement().tagName()  == "albedo")
			localita.albedo = node.firstChild().toText().data().toDouble();
		if (node.toElement().tagName()  == "albedo-model")
                        localita.albedoType = node.firstChild().toText().data().toInt();
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
                if (node.toElement().tagName()  == "min-t")
                        localita.tempMin = node.firstChild().toText().data().toDouble();
                if (node.toElement().tagName()  == "max-t")
                        localita.tempMax = node.firstChild().toText().data().toDouble();
		if (node.toElement().tagName()  == "wind")
			localita.wind = node.firstChild().toText().data().toDouble();
		if (node.toElement().tagName()  == "mounting")
			localita.mounting = node.firstChild().toText().data().toInt();
                     //   qDebug()<<"XmlEngine mountinh"<<localita.mounting;
		if (node.toElement().tagName()  == "concratio")
			localita.concRatio = node.firstChild().toText().data().toDouble();
		if (node.toElement().tagName()  == "mounting-height")
			localita.mountingHeight = node.firstChild().toText().data().toDouble();
                if (node.toElement().tagName()  == "tracker-dim"){

                        localita.trackerArea = node.firstChild().toText().data().toDouble();
                    }



	
		if (node.toElement().tagName()  == "source")
                        localita.source = node.firstChild().toText().data().toInt();
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
                                if (node.toElement().tagName() == MyMath::monthsIta(i)+"-losses")	{
					opt.otherLoss.append(node.firstChild().toText().data().toDouble());
                                      //  qDebug()<<"XML engine found losses"<<MyMath::monthsIta(i)<<node.firstChild().toText().data().toDouble();
				}
                                if (node.toElement().tagName() == MyMath::monthsIta(i)+"-w")	{
// 					qDebug()<<"XML engine found w"<<MyMath::months(i)<<node.firstChild().toText().data().toDouble();
					opt.wind.append(node.firstChild().toText().data().toDouble());
				}
// 		}
// 		for (int i=1;i<13;i++){
                                if (node.toElement().tagName() == MyMath::monthsIta(i)+"-t")	{
                                    //    qDebug()<<"XML engine found t"<<MyMath::monthsIta(i)<<node.firstChild().toText().data().toDouble();
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
 
void XmlEngine::setDetails(designer de)
{
    details = de;
    updateDetailsTree();
    qDebug()<<"XML setDetails"<<details.name;
}

void XmlEngine::setLoc(loc l)
{
	localita = l;
	updateLocTree();

}
void XmlEngine::setEcoParameters(ecopara o)
{
	econ = o;

     for(int i=0; i<12;i++)
         for(int j=0; j<econ.numBands;j++)
   //  qDebug()<<"XmlEngine ho chiamato setEcoParameters BANDE"<<econ.prezziEnergia[i][j];



	updateEcoTree();
     	
}

void XmlEngine::setPanelId(int i)
{
        qDebug()<<"XmlEngine setpanelid"<<i;
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
designer XmlEngine::getDetails()
{
    qDebug()<<"XML getDetails"<<details.name;
    return details;
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
 
