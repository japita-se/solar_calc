#ifndef DATISTRUCT_H
#define DATISTRUCT_H
#include <QtGui>

struct designer {
    QString name,name_r;
    QDate date;
    QString title;
    QString clientName,clientAddress;
    QString notes,albo,company;
    QString logoPath;


};

enum{
   meanCassa,
   bonusOnly,
   ribMolCs
};
struct rbData
{
    QDate date;
    double rotation;//degree
    double slope;   //degree
    int    hour;
    double mode;    // type of surface
    int    model;   // type of correlation model,e.g. Collaires
};

struct panel {
	QString fabric;
	QString model;
	double voc;
	double vmp;
	double isc;
	double vmax;
	double imp;
	double noct;
	double alfa;
	double beta;
	double gamma;
	double H;
	double L;
	double s;
	double pnom;
	double eff;
	double gar;
	int indexDB;
	bool isValid;
	 

	};
struct inverter {
	int isValid;
	QString fabric;
        QString model,type;
	
	double vmax;
	double vmin;
        double vout;
        double icc;
	double vmpmin,vmpmax,eff;
	double imax;
	
        double pnom,pin,cosphi;
	int indexDB;
        bool isvalid,trasformer;
	double gar;

};
struct googleMap 
	{
                double latGradi;
                double latMin;
                double latSec;
                double lonGradi;
                double lonMin;
                double lonSec;
		double lat;
		double lon;
		QString name;
	};
struct loc  {
		int albedoType;
		int reg;
		int prov;
                QString sigla;
		int comune;
		double lat;
		double lon;
                double latGradi;
                double latMin;
                double latSec;
                double lonGradi;
                double lonMin;
                double lonSec;
		int anno;
		int utc;
		double tempMin,tempMax;
		double wind;
		int mounting;
		double mountingHeight;
                double trackerArea;
		double area;
		QVector<double> additionalArea;
	        double alt;
		double ore;
		double albedo;
		double azi;
		double incl;
		QVector<double> additionalAzi;
		QVector<double> additionalIncl;
		double concRatio ;
                double radRealeAnnuaDF;
	  	double radRealeAnnuaTotale;
		double radRealeAnnuaMedia;
		double radRealeBiAxAnnuaTotale;
                double radRealeAnnuaOrizzontale;
		double radRealeOmbreAnnuaTotale;
		double radRealeBiAxOmbreAnnuaTotale;
		double radDirettaAnnuaTotale;
		double radDirettaAnnuaMedia;

		int radCorrModel;/* UNI=1, ENEA=2*, Erbs=3*/
		int ombreModel; /* sample and hold = 0, spline=1*/
		int hourlyCorrModel; /*Kaplanis = 0, Pereira =1; Kyushu =2*/
		QString name,coordinates,projectName;
		
		int tipo; /* 0= tilt fixed , 1= bi axis*/
		int source;/* 0=Enea, 1=Custom,2=PVGIS,3=NASA*/
		int radUnit;/*0 Mj, 1 kWh*/

		double starRatio ; //kWh/kWp
		
		 
	};
struct option {
	
	QString ombrePath,nearOmbrePath;
	QString tempPath ;
	QString windPath;
	double totalLossTemp;
	double meanShadowLossFactor;
	double totalShadowLossFactor;
	QVector<double> thermalLosses;
	QVector<double> shadows;
	QVector<double> temperatures;
	QVector<double> wind;	
	QVector<double> otherLoss;
	int thermalModel;
	bool scaling;
};

struct ecopara {
        bool useImmIntervals;
        double ammCostLimit;
        double power; //in kW
	double bonusPerkWp;
	double assicurazione;
	int assicurazioneAnni;
	double ammortamento;
        double ammortamentoAnni;
	int regime;
	QString fileBands;
	QList<QStringList> bands;
        QPolygonF intervals; //Intervalli di consumo per le Bande
        QPolygonF tIntervals; //Intervalli di consumo per le Tariffe
        QPolygonF pIntervals; //Intervalli di consumo per l'Immissione
        QString fileTariffe,fileTax;
        int intervalConsumo;
       // double tariffe[21][20];
        QList<QVector<double> > tariffe;
        static const int tariffe_size = 23;
        double taxes[15];
        static const int taxes_size   = 15;
        QVector<double> immissione;

        double pedaggiokWh;
        double pedaggiokW;
        double pedaggio;
        double VATonTotEnergy;
        double IMPonEnergy;
        double fasceInflazione;
        double tariffeInflazione;
        QVector<int> simoptions;

	QString loadsFile;
	QString filePrezziEnergia;
        static const int numBands = 12;
        double prezziEnergia[12][numBands];
	QString filePrezziMinimi;
	double prezziMinEnergia[12];
	int prezziEnergiaModel;
	QVector<double> prezziEnergiaGARCH;
	double prezziEnergiaInflazione;
	int prezziMinEnergiaModel;
	QVector<double> minPrezziEnergiaGARCH;
	double prezziMinEnergiaInflazione;
	double	maintenanceCost;
	double maintenanceS;
	int    maintenanceSFreq;
        bool   credit;
        double affitti;
	double taxesCost;
	double otherCost;
	double benefitInitialCost;
        double benefitTaxes;
	double benefitTotalInterest;
	double benefitVATCost;
        double vat;
	double initialCost;
	double loan;
	int loanYears;
	double loanInterestRate;
	double inflRate;
        double inflEnergyRate;
        double inflBandsRate;
	double discountRate;
	double bonuses;
        int bonusesYears;
	int life;
	QString loadPath;


};
struct nasaObject {
        QVector<double> rad ;
        QVector<double> temp;
        QVector<double> wind;
	bool status;
	};
struct sy {
	QVector<int> campiVector;
	QVector<int> panelVector;
	QVector<double> efficiencies;
	QStringList index;
 	QStringList models;
	bool systemValid;
        QList<inverter> inverters;
	
};

#endif
