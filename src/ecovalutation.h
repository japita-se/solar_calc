#ifndef ECOVAL_H
#define ECOVAL_H
#include "mymath.h"
#include "ui_ecoval.h"
#include <QtGui>
#include "data.h"


class HistogramItem;
class QwtPlotCurve;
class QStringListModel;
class IntervalEditor;
class EcoVal : public QWidget, public Ui::widgetEcoVal
{
	Q_OBJECT
public:
	EcoVal(QWidget* parent=0);
	~EcoVal();
// 	QwtPlot* rawDiagram();
// 	QwtPlot* vanDiagram();
        void resetAll();
        int getNumBands();
        double finWithVat();
        double findPedaggiokW(double energy);
        double findPedaggio(double energy);
        double weightedSumTariffekWh(double en,int year);
        double weightedSumTariffekW(double en,int year);
        double findPedaggiokWh(double energy);
        double getMonthlyTaxOnEn(int year, double mEnergy);
        double getInjectedPrice(int month,int band,int year);
        double getAltro(const QVector<double> &i);
        double getIva(const QVector<double> &i);
        double getIrpef(const QVector<double> &i);
        double getIrap(const QVector<double> &i);
        double getIres(const QVector<double> &i);
        double getAltro();
        double getIres();
        double getIrpef();
        double getIrap();
        double getBonuses(int year);
        double getTaxes(const QVector<double> &i);
	void setInstalledPower(double a);
        double getYearlyAssic(int y,bool inflated);
        double getYearlyAssicNPV(int year,int mode);
	double getDepreciationNPV(int year);
        double getDepreciationYears();
        double getDepreciation(int year);
	void setProjectFolder(const QString &f);
	void setEcoParameters(const ecopara a);
	ecopara getEcoParameters();
	double getTaxVatReduction();
        double getFreqCosts(int i,bool inflated);
        double getYearlyInterestNPV(int year,int mode);
	double getTaxReduction();
	double getYearlyTaxReductionOnInterest(int year);
	double getYearlyTaxReductionOnInterestNPV(int year);
	double getYearlyLoan(int i);
	double getYearlyLoanNPV(int year);
	double getYearlyInterest( int year);
        double getInitialCost( );
        double getNPVFactor(double C,int year,int mode);
// 	void drawNPV(const QPolygonF &npv);
//         void drawCS(const QPolygonF &cs);
// 	void drawFlowCash(const QPolygonF &data);
	int getRegime();
        double getYearlyCost(int i,bool inflated);
        int getImmBandsId(int hour,int month,int day,int year);
        int getBandsId(int hour,int month,int day,int year);
        double getYearlyEnergyCost(const QVector<double> &f, int nthYear );
        double getEnergyCost(int hour,int month,int day,int year,int nthYear);
        QVector<double> getContribute(QPolygonF &Eprod,QPolygonF &epr, QPolygonF &ei, QPolygonF &vei,double oe, double fc,double credit,int year);
// 	double getHourlyLoad(int hour,int month,int year);
	bool bandError();
	
public slots:
	void saveAll();
	void computeLoan();
        //void processEnergyPrices( );
	void processMinEnergyPrices( );
        //void reProcessEnergyPrices(bool i);
	void reProcessMinEnergyPrices(bool i);
	void checkBands();
 signals:
	void isDirty();
        void isDirtyBands();
private slots:
        void updatePrezziView();
        void enableMinPrices(int i);
        void updatePower();
        void updatePower(double d);
        void addImmissione();
        void addTariffeConsumo();
        void updateTariffeIntervals();
        void updateImmIntervals();
        void updateTIntervals();
        void updatePIntervals();
        void updateTableAndSpin();
        void updateImmissioneView();
        void updateTableBandsView( );
        void updateIntervals();
        void addBandsConsumo();
        void showTab();
        void updateTariffeView();
        void deleteTaxFile();
        void deleteBandsFile();
        void deleteOneriFile();
        void deletePrezziFile();
        void deleteMinPrezziFile();
        void setTaxOnEn();
        void setTax();
        void setDirtyBands();
        void setLife(int years);
        void setLife();
        void drawBandsPrices(int years);
        void updatePedaggiokW();
        void updatePedaggio();
        void undoDel();
        void clearAllBands();
	void popUpMenu(const QPoint& p);
        void popUpMenuMinPrezzi(const QPoint& a);
	void clearSelected();
        void clearSelectedMin();
	 
	void uniformize();
        void uniformizeMin();
        void setYearlyMinPrice();
        void setEco();
        void setEcoInvestment();
        void setTras();
        void setDist();
        void setDisp();
        void setMisura();
        void setAuc();
        void setLossFactor();
        void setProdFactors();

        void updateTaxView();
        void updateEcoParView();
	void updateInfoPrezzi();
	void updateInfoPrezziMinimi();
	void updateInfoBands();
	void updateInfo();
        void updateTaxInfo();
	void changeSelectedBand(const QModelIndex& i);
        void setPlots(int y);
	void toggleCoeff(int i);
        void loadTariffeFromList(QModelIndex a);
        void loadTaxFromList(QModelIndex a);
	void loadPricesFromList(QModelIndex y);
	void loadMinPricesFromList(QModelIndex y);
	void loadBandFromList(QModelIndex y);
	void loadP();
	void loadMinP();
	bool loadPrezzi(QString input);
	bool loadMinPrezzi(QString input);
	void loadTariffe();
        void loadTax();
	void loadB();
	void updatePrezzi(QTableWidgetItem* current );
	void updateMinPrezzi(QTableWidgetItem* current);
	bool loadBands(QString input);

	void updateBandsA(int i);
        void updateBandsDa(int i);
	void updateBandsVal(double d);
	void updateView(int i);
public slots:

        void savePrezziAs();
	void saveMinPrezziAs();
	void saveP();
	void saveMinP();
	
	void saveBandsAs();
	void saveBandsValues(QString s);
	void saveAs();
	bool getTariffeFromFile(QString s);
        bool getTaxFromFile(QString s);
	void save();
        void saveTariffe(QString s);
        void saveTax();
        void saveTax(QString s);
        void saveTaxAs();
	void saveBands();
	 
	
	
protected:
        double findImmPrice(double level,int year);
        double weightedSumBands(double en,int w,int year);
        double weightedSumCus(double en,double es,int year);
        double getTariffeValueFromId(int index);
        void updateIntervalsView();
        void updateTIntervalsView();
        void updatePIntervalsView();

        void setEcoBands();
        void updateBandsIntervals();
        QStringList fromIntervalsToString(const QPolygonF &a);
        bool eventFilter(QObject *obj, QEvent *e);
        void fireError(int num);
        double inflateBandPrice(double d,int year);
        void updatePedaggiokWh();
  	void createActions();

	void updateTableBandsView(int i,int x );
        void updateRowBandsView(int i,int x );

	void updateMinPrezziView();
	void savePrezzi(QString s);
	void saveMinPrezzi(QString s);
	void updatePrezziLabel(QString s);
	void updateMinPrezziLabel(QString s);
	void updateRecent(QString s);
        void updateRecentTax(QString s);
	
	void updateRecentBands(QString s);
        //void updatePrezziPlot();
	void updateMinPrezziPlot();
	void setDefault();

	void alignScales();

        int    findTariffeIntervalId(int i, double epr);
        int    findBandId(int a,int b,int hour);
        double findValue(int wchichBand,double en);
	double findValue(int a,int b,int hour);
	
private:

        ecopara ecoParameters,backupEco;
	double installedPower,assicurazione;
        QString recentDir,recentSave,recentDirTariffe,recentSaveTariffe,recentSaveTax,
                recentDirTax,recentDirPrezzi,recentSavePrezzi,
                recentDirMinPrezzi,recentSaveMinPrezzi,
                recentFile,w1,message1,message2,w2,w3,w4,fileTariffe,
                fileTax,fileBands;
        QString filePrezzi,fileMinPrezzi,titleBox,titleBandBox,
        titleTariffeBox,titleBox2,titleBox3,titleTaxBox;
        QString infoTariffe,infoPrezzi,infoBands,infoPrezziMinimi,infoTax;
        bool bandsError,doNotCheck,doNotLoad,bandsDirty;
	int numOfWBands,numOfTariffe;
        QStringList values,recent,recentFileName,recentTax,recentTaxFileName,
        recentBands,recentBandsFileName,recentPricesFileName,
        recentPrices,recentMinPricesFileName,recentMinPrices ;

        QList<QStringList> bands,bandsDefault,bandsPrevious;

        QVector< QVector<double> > mPrezziEnergia,mPrezziEnergiaSpan;
        QVector<double> minEnergyPrices;
        QString groupTariffeTitle,groupBandsTitle,groupPrezziTitle,
                groupMinPrezziTitle,groupTaxTitle;
        QStringListModel *model,*modelInj,*modelTariffe,*modelSell,*modelTax;
	int numBands;

        //QwtPlotCurve *prezziPlot
        QwtPlotCurve *csPlot,*minPrezziPlot,*bandPricesPlots[12];
// 	QwtPlotCurve *vanPlot,*rawPlot,*csPlot;
	
	HistogramItem *vanPlot,*rawPlot;
	enum{
	Vendita,
	SSPIT,
	SSP
	};
	enum{
	error,
	noError
	};
        int TARIFFESIZE,TASSESIZE,TARIFFESIZE_Y;
        double ammPeriodo,loan;
  	QString recentExportPath,projectFolder;
        QStringList f,g;
        QAction *a_clear,*a_copy,*a_clear_min,*a_copy_min;
	QPointF cursorPos;
        bool doNotChange,doNotUpdate,doNotUpdateIntervals,doNotUpdateTariffeIntervals,
         doNotUpdateImmissioneIntervals,doNotEmit;
        IntervalEditor *intervalEditor,*tIntervalEditor,*pIntervalEditor;
        QPolygonF intervals,intervalsPrevious,tIntervals,pIntervals;

};



#endif
