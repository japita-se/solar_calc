#ifndef _XMLENGINE_
#define _XMLENGINE_
#include "data.h"
#include <QDomDocument>
#include <QDomText>
#include <QPolygonF>
class QTreeWidget;
class QDomElemnt;
class QIODevice;
class QTreeWidgetItem;
class XmlEngine 

{
public:
	XmlEngine( );
        void setDetails(designer d);
	sy getSystem();
	void setSystem(QList<inverter> a, sy s);
	ecopara getEcoParameters();
	void setEcoParameters(ecopara o);
	void setPanelId(int i);
	void setInverterId(int i);
 	void setLoc(loc   l);
	void setOption(option o);
 	loc getLoc();
	option getOption();
        designer getDetails();
	int getPanelId();
	int getInverterId();
// 	void save();
// 	void read();
        void updateDetailsTree();
	void updateInvertersTree();
	void updateLocTree();
	void updateComponentsTree();
	void updateOptionTree();
	void updateEcoTree();
	void setFile(QFile *f);
	void newTree();
	void write();
	void read();
	

private:
        void parseDetailsEntry(const QDomElement &element);
	void parseSiteEntry(const QDomElement &element);
	void parseInvEntry(const QDomElement &element);
	void parsePvEntry(const QDomElement &element);
	void parseOptEntry(const QDomElement &element);
	void parseEcoEntry(const QDomElement &element);
	loc localita;
	option   opt;
	ecopara  econ;
	QDomDocument doc;
	
        QDomElement root,panelElement,panelIdElement,
        inverterElement,inverterIdElement,  localitaElement,
        detailsElement;
	 QDomElement domLocName,domLocLatGradi,domLocLatMin,domLocLonGradi, domLocLonMin,domLocAltitude,domLocLonSec,optElement,ecoElement,
        domLocAnno, domLocAlbedo,domLocAlbedoModel,domLocIncl , domLocAddIncl,domLocRadCorr
        ,domLocTipo,domLocSource,domOptLoss[12],domLocLatSec,domLocArea,domLocAddArea,
        domLocWind,domLocMounting,domLocMountingH,domLocUtc,domLocMinT,domLocMaxT,
        domLocAzi,domLocAddAzi,domLocOmbre, domOptOmbrePath,domOptTempPath,domLocConc,
        domLocTrackerDim;
	QDomElement domTemperature[12],domWind[12],domEcoMinPrezziGARCH[4],domEcoPrezziGARCH[4];



        QDomElement domDetailsName,domDetailsNameR,domDetailsDate,
                    domDetailsTitle,domDetailsClient,domDetailsClientAddress,
                    domDetailsNotes,domDetailsCompany,domDetailsAlbo,
                    domDetailsLogo,
                    domEcoPower,domEcoRegime,domEcoFilePrezziEnergia,
                    domEcoFilePrezziMinimi,
                    domEcoPrezziEnergiaModel,
                   domEcoMinPrezziEnergiaModel,domEcoMaintenanceCost,
                   domEcoTaxesCost,domEcoOtherCost,domEcoBenefitInitialCost,
                    domEcoBenefitTotalInterest,domEcoInitialCost,
                    domEcoLoan,domEcoLoanYears,
                    domEcoLoanInterestRate,domEcoCredit,
                    domEcoInflRate,domEcoDiscountRate,
                    domEcoLife,domEcoRents,domEcoImmissione,domEcoPI,domEcoUseImmIntervals,
                    domEcoMinPrezziEnergiaInflazione,
                    domEcoBandsInflRate,domEcoAmmLimit,
                    domEcoPrezziEnergiaInflazione,domEcoTariffe[22],
                    domEcoVatOnEn,domEcoIMPOnkWh,
                    domEcoPrezziEnergia[12],domEcoPrezziMinEnergia[12],
                    domEcoBenefitVAT,domEcoBenefitTaxes,
                    domEcoVat,domEcoMaintenanceSFreq,
                    domEcoMaintenanceS,domThermalModel, domEcoBands[12], domEcoFileLoad,
                    domEcoBonus,domEcoBonusYears,domEcoTaxes[15],
                    domEcoBonusW,domEcoAmm,domEcoAmmAnni,domEcoAssic,
                    domEcoAssicAnni,domEcoFileTariffe,domEcoFileBands,
                    domEcoSimOptions,domEcoFileTax,
                    domFields,domStrings,domInvertersId,
                    domOptNearOmbrePath,domOptScaling  ;
       QDomElement  domEcoLI,domEcoTI;

QFile  *d;
	int panelId,inverterId;
	QStringList bands;
	QPolygonF shadow;
	QList<inverter> inverters;
	sy systemDetails;
        designer details;
};
#endif
