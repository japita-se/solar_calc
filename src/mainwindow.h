
#ifndef _QMAINWINDOW_H
#define _QMAINWINDOW_H
#include <QNetworkProxy>
#include <QUrl>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QDoubleSpinBox>
#include <QPolygonF>
#include <QModelIndex>
#include <QMessageBox>
#include "data.h"
#include "suggest.h"
#include "outreport.h"
class DesignerData;
class DocumentEdit;
class SimEcoOptions;
class CheckUpdate;
class MagicTable;
class QTextEdit;
class QStackedWidget;
class InverterCheck;
class FaderWidget;
class CashFlowPlot;
class EcoVal;
class Load;
class HourlyEnergyPlot;
class HourlyPlot;
class Support;
class QShadowEditor;
class SurfaceWidget ;
class QTabWidget;
class MyPlot;
class OptimumPlot;
class EnergyOut;
class QWidget;
class QLineEdit;
class QLabel;
class QPushButton;
class QMenu;
class QAction;
class DatiPannello;
class DatiInverter;
class QRegExpValidator;
class QSqlDatabase;
class QSqlQueryModel;
class QGridLayout;
class QWidget;
class QListView;
class QSqlTableModel;
class QTreeView;
class QSortFilterProxyModel;
 class QTableWidget;
class RadiazioneReale;
class QComboBox;
class QCheckBox;
 class QTextStream;
class QToolBox;
class ModelSettings;
class DatiRadiazione;
class XmlEngine;
class QPainter;
class QTabWidget;
/* La seguente struttura tiene conto di tutti i dati di simulazione */
/* To be changed in a class in future versions */


class MainWindow: public QMainWindow
{
	Q_OBJECT
public:
	MainWindow();
        ~MainWindow();
        void loadDelayed(int i, const QString &a);
	void setLang(int i);
	void setVersion(const QString &v,const QString &wi,const QUrl& a);
	void prepareNasaGlob(QProgressBar &p,int v);
	bool prepareNasaTemp(QProgressBar &p,int v);
	bool prepareNasaRad(QProgressBar &p,int v);
	bool prepareNasaWind(QProgressBar &p,int v);
        void load(const QString &fileName);
protected:
void closeEvent(QCloseEvent *event);

private:
        void updateDbPanels(const QString &id);
        void suggestMinMax();
        QString getWhereEnea(int num);
        QString getWhereUNI(int num);
        void updateEnergyLabels(int mode);
        bool findNasaDataFast(double lat,double lon,double latG, double latM, double latS, double lonG, double lonM,double lonS, int mode);
       // QVector<double> seekInFile(const QString file,qint64 pos,int length);
        void decorateTab(QTabWidget *w, QTabWidget *hWidget,int num,int numH,int mode);
        int compareEnergies(double e);
        void fillEnString(const QString &a);
        bool sanityCheck(ecopara p);
        void updateShadow();
        void updateLatFromLoc();
        void updateRecentFileActions();

	bool additionalParChanged();
	double installedPower();
	QVector<double> computeAlbedo();
	void paintEvent(QPaintEvent * /* event */);
	void resetStatusBar();
	
        int numPanels();
        int numPanels2();
	int numPanels(double a);
	void insertNasaDatabase(int slat,int slon,const QStringList &data,int mode);
	void drawHourlyValues();
	void formatCoordinates();
	void resetFlags();
	QPolygonF readShadow(const QString& s);
	void saveShadow(const QString &g,int mode);
	
	void updateStatusBar(const QString &s,const QString& color);
	void convertToDegree(double l,double lon);
	QString normalize(const QString &g);
	void noRad(int i);
	void adjustVector(QVector<double> &g);
	void adjustVector(QPolygonF &g);
	void drawSurface(QWidget &i,double a);
	void resetWidgets();
	void createMenu();
        void createActions();
        void createTab();
	void printPreamble(QTextStream &s);
	void initializeModel();
	void initializeModelPanels(const QString &s);
	void readSettings();
	void writeSettings();
	bool confirmErase(const QString &c);
	bool extractRadiazione(loc localita);
        bool findNearUNI();
	bool findNear();
	void createTable();
	void createTablePanel(const QString &t);
//	int  goodCo(int g, int m, int s);
	void convertLat(loc l);
	int  checkLat(int i, const QStringList &y);
	void updateComuneLabel(int reset);
	void updateFromModel(int i);
	 
	bool radSourceLoaded();
	void createInterface();
	void setupConnection();
	void setupConnectionToPanel(const QString &s);
	void changeColor(QLabel &s,const QString  &c);
        //double wattUnit();
	void setIntegrationInterval();
	void createSettings();
	void updateSourceRadSettings();
	void resetHg();
	void resetCustomHg();
	void setupGuiPanels();
	bool somethingChanged();
	void updateSitePar();
	void resetWindDaily(int mode);
	void updateWindWidget();
	void resizeCustomWind(int s);
	
	void resetTempDaily(int mode);
	void updateTempWidget();
	void resizeCustomTemp(int s);
// 	QString checkFormat(const QString &source, const QString &format);
	QString getMonthString(int i);
	QString toS(int i);
	QString toS(double i);
signals:
	void gNameAvailable(const QString& a);
private slots:
        void updateDetails();
        void showDetails();
        void showMiniWord();
        void ldDelayed();
        void updateMinTemp(double a);
        void updateMaxTemp(double a);
        void updateTrackValue(double a);
        void yearChanged(int i);
        void showSimOptions();
        void setSimOptions();
        void viewSite();
        void viewSup();
        void viewMeteo();
        void loadHourlyEnergy();
        void exportHourlyEnergy();
        void setUpdateAtStart();
        void swapLimitDistance();
        void checkUpdatesSilent(bool a);
        void showEcoVal();
	 void openRecentFile();

        void redrawSelfShadow(int m);
	void redrawReale(int whichone);
	void checkUpdates();
	void enableDrawingLoads();
	void enableScaling(int state);
	void setNameDiagramPlot(const QString& a);
	void updateComponentStatus();
	void viewMonthlyLoss();
	void resetEnString();
	void updateHourlyTable();

	void toFade();
 	void fadeInWidget(int s)	;
// 	void update();
// 	void showSuggestion(int i);
	void drawRefCurve();
	void makeDirty();
	void simulateNew();
	void simulateNewEco();
	void simulate(int mode);
	void openLoad();
	void getLoad();
	void updateLimitDistance(double i,double incl);
	void updateLimitDistance(double incl);
	void updateLimitDistance();
	void changeNumPanels(double a);
	void changeNumPanels2(double a);
	void changeDays( );
	void dayChanged(int index);
	void computeHourlyValues(int month,int day);
        double computeHourlyValue(int month,int day,int hour,int year);
	void updateLatFromGoogle(double,double,QString& a);
	
	void updateFromGoogle();
	void reloadCoordinates();
	void drawShadowFromEditor();
	void tableResetted();
	void updateShadowFromEditor();
	void newShadowEditor();
	void about();
	void enableHeight(int i);
        void tempChangedPower();
	void windChangedPower();
	void updateSurface(double d);
	void updateTiltSurface(double d);
	 
	void printPreview();
	void printPreview(QPrinter* p);
        void printReport(QPrinter* p,int m,QPrinter::OutputFormat format);
	void print();
        void printPS();
        void printGeneral( );
	void wizard();
	void updateTitle(const QString &t);
	void exportData();
	void exportDaily();
	void exportPDF();
	void setDamp();
  	void setDampOthers( );
	void addPV();
// 	void closeEvent(QCloseEvent *event);
	bool createConnection();
	bool createConnection(const QString &t);
	bool checkIfDatabase();
	bool checkIfDatabase(const QString &a, const QString &name);
	void loadEneaData();
	void loadComuniData();
	void updateLat();	
	void set();
        void set(int a);
        int ask(const QString &t,const QString &what);
        int askYESNO(const QString &t,const QString &what);
        int ask();
	void getCity();
	void getCityFromCo(int c);
	void updateCity(const QModelIndex &m);
	void viewOpti( );
        void viewEnergy();
	void viewReale( );
	void viewAlbedo();
// 	void viewSolar();
  	void setNewCity(const QString &g );
        void updateRadLabel(int i );
	void updateOptiLabels(int i);
	void updateOptiLabel(int i);
	void createSolarPlot();
	void createOptimumPlot();
	void createRealePlot();
	void createEnergyOutPlot();
	void createCheckInverter();
        //void viewDailyRealePlot(int a);
//	void createDailyRealePlot(int state);
        //void createDailyRealePlot();
// 	void getOptiIncl();
// 	void stateChanged(int i);
        void updateRadLabels(int i);
	void ombreChanged();
	void updateModelSettings();
// 	void loadCustomRad();
	void setRadData();
	void selectPV();
	void selectInv();
	void updatePower();
        void updatePower(int mode);
	void updateEnergyUnit();
	void loadTemp(bool i);
	void loadWind(bool i);
	void loadTempFile();
	void loadWindFile();
	void save();
	void clearProject();
	void newProject();
	void saveAs();
	void load();
	void loadShadow();
	void updateProject();
        void updateTempDaily( );
        void updateWindDaily();
	void clearTemp();
	void clearWind();
	void reloadWind();
 	void changeRealePlots(int state);
	void updateOptions();
        nasaObject findNasaDataSQL(double lat,double lon,double latG, double latM, double latS, double lonG, double lonM,double lonS);
        bool findNasaData(double lat,double lon,double latG, double latM, double latS, double lonG, double lonM,double lonS, int mode);
//         nasaObject findNasaData2(double lat,double lon,int latG, int latM, int latS, int lonG, int lonM,int lonS, int mode);
// 	QPolygonF extractNasaTemp(int lat, int lon);
	void reloadTemp();
	QPolygonF convertListToPol(const QStringList &s);
	
	
// 	void changeUnit(int i);
// 	 void setFiltro();
private:
        QString specialFolder(int i);

private:
	
	QGroupBox *italiaData;
	QColor co;
	QDate currentDate;
        QAction *a_load_data,*a_load_comuni,*a_view_opti,*a_view_energy,
        *a_view_reale,
        *a_view_solar,*a_about,*a_eleload_editor,*a_simulate,*a_simulate_redo,
        *a_view_site,*a_view_sup,*a_view_meteo,*a_sim_options;
	QAction *a_get_albedo,*a_suggest,*a_check_update;
	QAction *a_quit,*a_export,*a_exportPDF;
	QAction *a_load_shadow,*a_delete_shadow;
	QAction *a_impostazioni,*a_property;
	QAction *a_load_rad,*a_check_custom;
	QAction *a_refresh,*a_save_project,*a_saveas_project,*a_load_project;
	QAction *a_new_project,*a_create_daily;
	QAction *a_add_component,*a_select_component,*a_select_inv;
	QAction *a_export_daily;
        QAction *a_print_report,*a_print_report_ps,*a_print,*a_shadow_editor,
                *a_ecoval,*a_export_esim_text,*a_export_allsim,
                *a_load_esim,*a_mini_word,*a_details;
        QMenu *viewMenu,*toolMenu,*eneaMenu,*strumentiMenu,
              *strumentiExportMenu,*fileMenu,*aboutMenu;
	QMenu *ombreMenu,*impostazioni,*radMenu,*dataMenu;
// 	,*exportMenu;

	QStatusBar *status;
        QToolBar *toolBar,*toolBar2,*toolBar3,*toolBar4,*toolBar5,*toolBar6,*toolBar7,*toolBarView;
        QWidget *mainSettings,*optiWidget,*realeWidget,*myPlotWidget,*energyWidget, *realeToolWidget;
        QTabWidget *tabWidget,*innerTabEO;
	QListView *comuniView;
 	QSortFilterProxyModel *proxyModel;
// 	QLineEdit *latGradi,*latMin,*latSec,*lonGradi,*lonMin,*lonSec,
	QLineEdit *locValue,*comuneValue;
	QDoubleSpinBox *altitudeValue;
	 
	QLabel *comuniViewLabel,*tempNote,*concRatioLabel;
	QLabel *latLabel,*lonLabel,*comuneLat,*comuneLatS,*comuneLon,*comuneLonS;
	QLabel *areaLabel,*numOfPanels,*numOfPanelsValue,*numOfPanelsValue2;
        QLabel *tempMinLabel,*tempMaxLabel,*statusLabelWarning,*statusLabelEnergy,
        *statusLabelInverter,*tempExplainLabel,*statusLabelPower,
        *pValue,*totEnValue,*tlossValue,*srValue;
	
	QLabel *locLabel,*locLabelEx,*otherLoss;
	QDoubleSpinBox *aziValue,*aziValue2,*oreTickValue,*trackDimValue;	
	QDoubleSpinBox *inclValue,*inclValue2,*windValue,*mountingHeightValue;
	QDoubleSpinBox *albedoValue,*areaValue,*areaValue2,*tempMinValue,*tempMaxValue,*concRatioValue;
	
	QSpinBox *annoValue,*utcValue;
	QLabel *optiIncl;
        QLabel *optiInclValue;
	QLabel *incl,*azi,*comuneLabel;
	QLabel *utcLabel,*altitudeLabel,*gainLabel,*gainValue;
	QLabel *annoLabel,*maxIrrHinclOmbre,*maxIrrHinclOmbreValue, *maxIrrHb,*maxIrrHbValue,*maxIrrHincl,*maxIrrHinclValue,*statusLabel,*inclOptiValue,*albedoLabel,*inclOptiLabel;
// 	QPixmap warningPixmap;
	QComboBox *mountingValue,*selectMonth,*selectDay,*comboCurrentField;
	QLabel *windLabel,*mountingLabel,*mountingHeightLabel;
	QLabel *meanIrrHinclValue,*meanIrrHincl,*inclOptiOmbreLabel,*inclOptiValueOmbre;
        QPushButton* wattLabel,*wattLabel2,*wattOptiLabel,*pushMonthly;
	
	QLabel* surfaceLabel,*limitDistanceLabel,*limitDistanceValue,*trackDim;
        QCheckBox *toggleSplineBox,*toggleSelfShadowBox,*checkScaling,*checkDrawLoads;
        QCheckBox *checkOmbre,*inclOptiCheck;
	 QToolBox *toolBox;
	
        QPushButton *okButton,*tempLoadButton,*tempClearButton,*tempResetButton,*suggestButton,*tempUpdatePower,*tiltButton;
	QPushButton *windLoadButton,*windClearButton,*windResetButton,*windUpdatePower,*wattLabel3;

	
	/*Basic Plot Widgets*/
	MyPlot *w;
	OptimumPlot *o;
	RadiazioneReale *reale;
	EnergyOut *energyOut;
	QStackedWidget *pagesWidget;
	QRegExpValidator *validator,*validator2,*validator3,*validator4;
	QGridLayout *leftLayout,*topLayout;
	QVBoxLayout *ves,*lv;
        bool isDirty,convertionDone,
        wrongCoordinates,noNameAvailable,googleNameAvailable,newCity,onlyLat,bothCoord;
	bool panelsLoaded,dailyValuesPresent,showItalia,firstRun;
	bool energyPlotPresent;
        bool doNotLoadTemp,doNotLoadWind,doNotUpdateField,doNotUpdatePower;
        bool refCurveShown,ecoTablePresent ;
	 bool googleError,useLoc,useLoadedLoc;
	QSqlDatabase db;
	QSqlQueryModel *modelExtract,*modelRadiazione,*modelRadiazione2;
	QSqlTableModel *modelPanels;
	QTableWidget *tempDailyTable,*windDailyTable;
	QString databaseEntry,projectName;
	QString databasePanels,databasePanelsId;
	QStringList unit,source,unitE,recentFiles;
	QString tempFile,ombreFile;
	QStringList nasaTempRecord;
	QString energString;
	QHash<QString,double> nasaTemp;
	QHash<QString,double> nasaRad;
	QHash<QString,double> nasaWind;
		 
        enum { MaxRecentFiles = 8 };
    	QAction *recentFileActions[MaxRecentFiles];
	QAction *separatorAction;


	QVector<double> effTemp,effTemp2;
// 	double lat,lon,latGradi,latMin,latSec,lonGradi,lonMin,lonSec;
	double Hg[12],*Hb,*Hho,*Hbh,*Rb,*RbBiAx,*Hincl,*Hincl2,*HinclOmbre,*HinclOmbre2,*Energy,*omegasH;
	loc localita;
	googleMap google;
     //   QVector<double> meanDay;
	double totEnergy,limitDistance;
// 	double *omegaApp,*omegaSco;
	QVector<double> omegaApp,omegaSco,addOmbre,addOmegaRb;/*10 Dec 2009*/
	QList<QVector<double> > ombreMultiple;/*15 Dec */

        QPolygonF Epr,Ei,CS,Eprod,RawCash,NPV,Interest,InterestNPV,
        yearlyEprod,consumedEn,BN,CREDIT,CEI,Rata,RataNPV,AmmNPV,Amm,
        yearlyCost,yearlyCostNPV,selfConsumed,SavingsEn;
	QPolygonF omegasHDaily,omegasHDaily2,HhoDaily,HhoDaily2;
	panel thisProjectPanel;
	inverter thisProjectInverter;
	option otherLosses;

	QVector<double> tempDaily,windDaily,nasaData;
	QPolygonF customHg,hourlyRR,hourlyEO;
	ModelSettings *modelSettings;
	DatiRadiazione *sourceRadSettings;
        QString recentDir,recentDirReport,recentDirExport,
                recentExportDaily,saveProjectFile,recentDirProject,
                recentDirHE,recentSaveProject ;
        QString radNASAFile,tempNASAFile,windNASAFile,version,
                versionId,globalNASAFile,fileEnergyData;
	DatiPannello *datiPanels;
	DatiInverter *datiInverter;

        int energyOutUnit,language,numOfDec;

	XmlEngine *xmlBag;
	QShadowEditor* editor;
// 	QPainter  painter;
// 	QPixmap   pixmapSurface;
	SurfaceWidget * canvas;
	Support *support;
	HourlyPlot* hourlyPlot;
	HourlyEnergyPlot *hourlyEOPlot;
	Load *loadInterface;
	EcoVal* ecoVal;
	CashFlowPlot* cash;
	QPointer<FaderWidget> bF;	
	InverterCheck *inverterCheck;
	OutReport t;
	QTextEdit* energySummary;
	MagicTable* monthlyLoss;
	QUrl urlOwner;
	CheckUpdate* ch;
        SimEcoOptions * simEcoOpt;
protected:
        bool validForExport,ombrePresent,projectIsDirty,estimatedCoordinates,
        noRadiation,tempDataIsEdited,windDataIsEdited,firstPassDone,
        userYearChanged,minTempIsEdited,maxTempIsEdited,loadedProject,doNotSetCity;
        bool myplotpresent,checkAtStart;
        int integrationType,radSource,simYear;
        //QVector<double> temp,eprod,ei,eprv,opr,ec;
        QVector<double> eprod;
        QStringList monthMem;

        QString hostProxy;
        QString userProxy;
        QString passwordProxy;
        int portaProxy;
        QString typeProxy,fileFromMain;
        QNetworkProxy proxy;
        bool proxyEnabled;

        enum{
            north,
            south
        };
	enum{
	horizon,
	near
	};

	enum{
	myplot_,
	custom_
	
	};
	
	
	enum {
	default_,
	UNI,
	Enea,
	Erbs
	/* Erbs =3,Enea=2,UNI =1, default_ = 0 */
	};
	enum {
	radEnea,
        radUNI,
        radNasa,
        radCustom
	};

	enum {
	none,
	megajoule,
	kwh
	};

        enum {
            fixed,
            tracker,
            multiple
        };
	enum {
		rack,
		direct,
		array,
		standoff 
			
	};
	enum {
		all,
		onlyRad
	};
	enum{
	Vendita,
	SSPIT,
	SSP
	};

	enum{
	NOCT,
	CEA,
	other
	};
  	enum{
	site,
	captureSurface,
	meteo
	};
	enum{
	energetics,
	economics
	};
	enum{
	kaplanis,
	pereira,
	kyushu
	};

	enum{
	con,
	variable_high_snow,
	variable_low_snow
	};
	enum{
	tilt,
	biax
	};
        enum{
            normal,
            fromGoogle
        };

        QProgressBar* progressCompute;
        DocumentEdit* miniWord;
        DesignerData* projectDetails;
 
		
};
#endif
