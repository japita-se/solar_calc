     #define DEBUG
// #include "about.h"
 
//#define PLUSVERSION2
#define PLUSVERSION
#define WITHTOOLS
#include "designerdata.h"
#include "documentedit.h"
#include "newlabel.h"
#include "styles.h"
#include "simecooptions.h"
#include "checkUpdate.h"
#include "magictable.h"
#include "doubledelegate.h"
#include "inverterCheck.h"
#include "buttonFade.h"

#include "cashflow.h"
#include "ecovalutation.h"
#include "load.h"
#include "hourlyenergyplot.h"
#include "hourlyplot.h"
#include "support.h"
#include "qshadoweditor.h"
#include "surfacewidget.h"
// #include "outreport.h"
#include "proprieta.h"
#include "xmlengine.h"
#include "datipannello.h"
#include "datiinverter.h"
#include "modelsettings.h"
#include "mainwindow.h"
#include "myplot.h"
#include "energyout.h"
#include "mymath.h"
#include "addpv.h"
#include "radiazioneReale.h"
#include "optimumplot.h"
#include "albedo.h"
#include "datiradiazione.h"
#include <QtGui>
#include <cmath>
 #include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlError>
#include <QComboBox>
#include <QSqlRecord>
#include <QProgressDialog>
#include <QTreeView>
#include <QModelIndex>
#include <QDesktopWidget>
#include <QRect>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QToolBox>
#include <QIcon>
#include <QTableWidget>
#include <QSvgRenderer>
 
 #define pi        3.1415926535897932384626433832795028841971
#define EPS 0.00000000002;

#ifdef Q_WS_WIN
//#include "qt_windows.h"
//#include "qlibrary.h"
//#ifndef CSIDL_COMMON_APPDATA
//#define CSIDL_COMMON_APPDATA 0x0023 // All Users\Application Data
//#endif
//#ifndef CSIDL_APPDATA
//#define CSIDL_APPDATA 0x001a // <username>\Application Data
#endif
//
//
//QString MainWindow::specialFolder(int type)
//{
//        QString result;
//
//        QLibrary library(QLatin1String("shell32"));
//        QT_WA( {
//                typedef BOOL (WINAPI*GetSpecialFolderPath)(HWND, LPTSTR, int, BOOL);
//                GetSpecialFolderPath SHGetSpecialFolderPath = (GetSpecialFolderPath)library.resolve("SHGetSpecialFolderPathW");
//                if (SHGetSpecialFolderPath) {
//                        TCHAR path[MAX_PATH];
//                        SHGetSpecialFolderPath(0, path, type, FALSE);
//                        result = QString::fromUtf16((ushort*)path);
//                }
//        } , {
//                typedef BOOL (WINAPI*GetSpecialFolderPath)(HWND, char*, int, BOOL);
//                GetSpecialFolderPath SHGetSpecialFolderPath = (GetSpecialFolderPath)library.resolve("SHGetSpecialFolderPathA");
//                if (SHGetSpecialFolderPath) {
//                        char path[MAX_PATH];
//                        SHGetSpecialFolderPath(0, path, type, FALSE);
//                        result = QString::fromLocal8Bit(path);
//                }
//        } );
//
//        // Fallback on error
//        if (result.isEmpty()) {
//                switch (type) {
//                case CSIDL_COMMON_APPDATA:
//                        result = QLatin1String("C:\\temp\\qt-common");
//                        break;
//                case CSIDL_APPDATA:
//                        result = QLatin1String("C:\\temp\\qt-user");
//                        break;
//                default:
//                        ;
//                }
//        }
//
//        return result;
//}
MainWindow::MainWindow( ) 
{

   // QMessageBox::information(this,"APPDATA",QDesktopServices::storageLocation(QDesktopServices::DataLocation));
        setWindowModified(false);
#ifdef PLUSVERSION2
        miniWord        = new DocumentEdit;
        projectDetails  = new DesignerData;
        connect(projectDetails,SIGNAL(isDirty()),SLOT(updateDetails()));
#endif
        progressCompute = new QProgressBar;
        progressCompute->hide();
        progressCompute->setMaximum(5);
        proxy.setHostName("");
        proxy.setPassword("");
        proxy.setUser("");
        proxy.setPort(1080);
        proxy.setType(QNetworkProxy::DefaultProxy);
        proxyEnabled = false;
        checkAtStart = true;
        numOfDec =2;
	urlOwner="";



        ch = new CheckUpdate(this);
         monthMem  << "gen" << "feb" << "mar" << "apr" << "mag" << "giu" << "lug" << "ago"<< "set" << "ott" << "nov" << "dic";

        connect(ch,SIGNAL(done(bool)),SLOT(checkUpdatesSilent(bool)));
        connect(ch,SIGNAL(accepted()),SLOT(setUpdateAtStart()));

	showItalia = false;
	firstRun = true;
        currentDate = QDate::currentDate()  ;
 
        noRadiation = true;
	createInterface();
	createTab();

	modelExtract 	    = new QSqlQueryModel(this); //per caricare punti vicini
	modelRadiazione     = new QSqlQueryModel(this);
	modelRadiazione2    = new QSqlQueryModel(this);

	readSettings();

        simYear = annoValue->value();
	#ifdef DEBUG
	qDebug()<<"Conversion="<<convertionDone;
	#endif
	// Connect to database
	
	setupConnection(); /* Crea connessione a dati Enea*/
	
        setupConnectionToPanel("panels"); /* Crea Connessione a dati sui pannelli*/
        // Nov 2010
        // Check if the database is old and update it
        updateDbPanels("panels");

	#ifdef PLUSVERSION
        if(inverterCheck!=0)
	inverterCheck->setDatabase(databasePanelsId);
        if(cash!=0)
            cash->setNumOfDec(numOfDec);
	#endif

// 	setWindowIcon(QIcon(":/images/app.png"));
	setWindowIcon(QIcon(":/images/logo3.png"));
        setWindowTitle("SolarCalc ");
	
	setAttribute(Qt::WA_QuitOnClose);
       // setAttribute(Qt::WA_DeleteOnClose);
        source<<"ENEA"<<"UNI10349"<<"NASA"<<"CUSTOM";
	

	validator = new QRegExpValidator(QRegExp("^[0-8]{1,1}[0-9]{1,1}.[0-9]{1,}|^[9]{1,1}0"),this);
	validator2 = new QRegExpValidator(QRegExp("^[+-0-8]{1,1}[0-9]{1,1}|[0-8]{1,2}|^[9]{1,1}0|^[+-9]{1,1}0"),this);
	validator3 = new QRegExpValidator(QRegExp("[0-5][0-9]|60|[0-9]{1,1}"),this);
	validator4 = new QRegExpValidator(QRegExp("[0-8][0-9]|90|[0-9]{1,1}"),this);
	
	// Valori di riferimento//
	// To be changed for multiple projects //
	 effTemp.fill(0,12);
	 localita.radDirettaAnnuaTotale=0;
	 localita.additionalAzi.resize(0);
	 localita.additionalIncl.resize(0);
	 localita.additionalArea.resize(0);
	 localita.albedoType = con;
	 localita.wind = 0;
	 localita.mounting = rack;
	 localita.mountingHeight = 2.5;
	 localita.utc =0;
	 localita.anno=2009;
	 localita.lat = 0;
	 localita.latGradi =0;
	 localita.latMin =0;
	 localita.latSec =0;
	 localita.lon = 0;
	 localita.lonGradi = 0;
	 localita.lonMin =0;
	 localita.lonSec =0;
         userYearChanged = 0;
	 otherLosses.temperatures.fill(0,12);
	 otherLosses.wind.fill(0,12);
         otherLosses.thermalModel = 0;//NOCT model
	 otherLosses.otherLoss.fill(0,12);
	 localita.alt = 0;
         localita.area = 0;
         localita.incl = 0;
         localita.azi = 0;
         localita.albedo = 0;
	 thisProjectPanel.isValid = false; /*no panel selected at the start*/
	 thisProjectInverter.isValid =false;
	 
	 otherLosses.meanShadowLossFactor=0;
	 otherLosses.totalShadowLossFactor=0;
	 otherLosses.tempPath ="";
	 otherLosses.ombrePath="";
	 localita.tempMin = 0;
	 localita.tempMax = 40;
	 localita.ombreModel   = 0; /*sample and hold*/
         localita.radCorrModel = 2; /* ENEA */
	 localita.tipo         = 0; /* Tilt fixed */
	 localita.concRatio     = 1;
	 localita.source       = radEnea;
	 localita.radUnit      = megajoule;
	 tempDataIsEdited = false;
         minTempIsEdited = false;
         maxTempIsEdited = false;
	 windDataIsEdited = false;
	 doNotLoadTemp	  = false;
	 doNotLoadWind    = false;
         doNotUpdateField = false;
         doNotUpdatePower = false;
         loadedProject    = false;
         doNotSetCity     = false;
	refCurveShown = false;
        firstPassDone = false;
        ecoTablePresent = false;
         radNASAFile           = QCoreApplication::applicationDirPath() + "/raw2005.txt";
         qDebug()<<"MW start" << radNASAFile;
	 tempNASAFile	       = QCoreApplication::applicationDirPath() + "/22yr_T10M";
	 windNASAFile	       = QCoreApplication::applicationDirPath() + "/10yr_wspd50m";
 	 globalNASAFile	       = QCoreApplication::applicationDirPath() + "/nasaGlobal.txt";
	 estimatedCoordinates = false;

         ecoTablePresent = false;
	 resetFlags();
	 projectName = "(Untitled)";
	 projectIsDirty = false;
	/* Altri settaggi*/
	 validForExport = false;
         recentDirHE   = QDir::homePath();
	 recentDirReport   = QDir::homePath();
         recentDir 	   = QDir::homePath();
	 recentDirExport   = QDir::homePath();
	 recentExportDaily = QDir::homePath();
	 recentDirProject  = QDir::homePath();
	 recentSaveProject = QDir::homePath();
         fileEnergyData    = "";
         integrationType=custom_;
    	 CS.resize(0);
	RawCash.resize(0);
	NPV.resize(0);
	Interest.resize(0);
	InterestNPV.resize(0);
// 	prepareNasaTemp();

	if (canvas)
				canvas->setType(localita.tipo);
	
	editor = new QShadowEditor(this);		
	connect(editor, SIGNAL(accepted()),SLOT(updateShadowFromEditor()));
	connect(editor, SIGNAL(tableResetted()),SLOT(tableResetted()));
	connect(editor, SIGNAL(shadowChanged()),SLOT(drawShadowFromEditor()));
	sourceRadSettings = new DatiRadiazione;
	updateSourceRadSettings();


 	modelSettings = new ModelSettings(this);

        
	createSettings();
	createActions(); 
	createMenu();


	
	
	QFile f(saveProjectFile);
	xmlBag = new XmlEngine();
	xmlBag->newTree();
	 
	

	setupGuiPanels();
		
// 	#ifdef WITHTOOLS
// 	QProgressBar p(statusBar());
// 	p.show();
// 	p.setMaximum(65000*3);
// 	p.setMinimum(0);
// 	qDebug()<<"Start Inserting NasaRad...";
//  	prepareNasaRad(p,1);
// 	qDebug()<<"Start Inserting NasaTemp...";
// 	prepareNasaTemp(p,2);
// 	qDebug()<<"Start Inserting NasaWind...";
// 	prepareNasaWind(p,3);
// 	#endif

 	statusLabel = new QLabel;
	
	
        statusLabel->setAlignment(Qt::AlignCenter);
        statusLabel->setMinimumSize(statusLabel->sizeHint());
	
        statusLabelWarning = new QLabel(tr("Rad.: Database"));
	statusLabelWarning->setAutoFillBackground(true);
	statusLabelWarning->setFrameShape(QFrame::Box);
	
  	/*statusLabelWarning->setPixmap( warningPixmap)*/;
	 
        statusLabelInverter = new newLabel;
        statusLabelInverter->setToolTip(tr("Clicca per cambiare componente"));
        connect(statusLabelInverter,SIGNAL(clicked()),SLOT(selectInv()));
	statusLabelInverter->setFrameShape(QFrame::Box);
        statusLabelInverter->setIndent(3);
        statusLabelInverter->setAlignment(Qt::AlignCenter);
        statusLabelInverter->setMinimumSize(statusLabelInverter->sizeHint());

        statusLabelPower = new QLabel;
        statusLabelPower->setFrameShape(QFrame::Box);
        statusLabelPower->setIndent(3);
        statusLabelPower->setAlignment(Qt::AlignCenter);
        statusLabelPower->setMinimumSize(statusLabelInverter->sizeHint());

        if (energyOut!=0)
        statusLabelEnergy = new newLabel(energyOut->getStatus());
	else
        statusLabelEnergy = new newLabel;


        connect(statusLabelEnergy,SIGNAL(clicked()),SLOT(selectPV()));
        statusLabelEnergy->setToolTip(tr("Clicca per cambiare componente"));
	statusLabelEnergy->setFrameShape(QFrame::Box);
        statusLabelEnergy->setIndent(3);
        statusLabelEnergy->setAlignment(Qt::AlignCenter);
        statusLabelEnergy->setMinimumSize(statusLabelEnergy->sizeHint());
	statusLabel->setIndent(3);
	statusLabelWarning->setIndent(3);
	statusLabelWarning->setAlignment(Qt::AlignCenter);
	statusLabelWarning->setMinimumSize(statusLabelWarning->sizeHint());
	statusLabel->setAlignment(Qt::AlignHCenter);
        statusLabel->setMinimumSize(statusLabel->sizeHint());
        statusBar()->insertPermanentWidget(0,progressCompute,0);
        statusBar()->insertPermanentWidget(1,statusLabelPower,0);
        statusBar()->insertPermanentWidget(2,statusLabelInverter,0);
        statusBar()->insertPermanentWidget(3,statusLabelEnergy,0);
        statusBar()->insertPermanentWidget(4,statusLabelWarning,0);
        statusBar()->insertPermanentWidget(5,statusLabel,0);
	statusBar()->showMessage(tr("Pronto"),4000);


	updateTitle(projectName);
	updateStatusBar("Database","darkkhaki");
	updateComponentStatus();


// 	pSplash.finish(this);
// 	 qDebug()<<"MW italiaData"<<italiaData->frameSize().width()<<italiaData->frameSize().height();
//  	bF  = new FaderWidget(italiaData);
	
	resetEnString();
	connect(this,SIGNAL(gNameAvailable(const QString&)),SLOT(setNameDiagramPlot(const QString&)));
}

void MainWindow::setupConnectionToPanel(const QString &id)

{
databasePanelsId = id;
if (!panelsLoaded) {

		// no DB of panels in the settings. Maybe the file exsists....
		 

		if ( createConnection(id)) {		
			if (!checkIfDatabase(id,"pannelli")) {
						 
						#ifdef DEBUG
						
						#endif
						// Il database non esiste e non e' stato caricato, ergo creane uno
 					        createTablePanel(id);
						
 			} else {
			// Il db esiste ed e' sano.

			panelsLoaded = true;
			initializeModelPanels(id); 
			}
		} else  
					
			  QMessageBox::critical(this,tr("Database assente"),tr("Problema di connessione con il database ")+id+".",QMessageBox::Ok);
	} else {
		if ( createConnection(id)) 	
			initializeModelPanels(id);
		else
			QMessageBox::critical(this,tr("Connessione Database"),tr("Problema di connessione con il database ")+id+".",QMessageBox::Ok);
	}



}
void MainWindow::setupConnection()
{
if (!convertionDone) {

		// no DB name in the settings. Maybe the file exsists....
                databaseEntry = QCoreApplication::applicationDirPath()+"/datiUNIEnea.db";
		qDebug()<<"ApplicationDir path"<<databaseEntry;
		if ( createConnection()) {		
			if (!checkIfDatabase()) {
						QMessageBox::warning(this,tr("Database Enea assente"),"Database dei dati di radiazione Enea mancante. Caricalo o generalo dopo dal menu Strumenti",QMessageBox::Ok);
						#ifdef DEBUG
						qDebug()<<"Create connetion,convertion"<<convertionDone;
						#endif
						// Il database non esiste e non e' stato caricato, ergo creane uno
 					        createTable();
						
 			}
			// Il db esiste ed e' sano.
			convertionDone = true;
			initializeModel(); 
		} else  
					
			  QMessageBox::critical(this,tr("Database assente"),tr("Problema di connessione con il database Enea. Ricerca comuni non attiva."),QMessageBox::Ok);
	} else {
		if ( createConnection()) 	
			initializeModel();
		else
			QMessageBox::critical(this,tr("Connessione Database"),tr("Problema di connessione con il database Enea. Ricerca comuni non attiva."),QMessageBox::Ok);
	}
}
void MainWindow::createTable()
{
	QSqlQuery q;
	q.prepare("CREATE TABLE radiazione (id INTEGER NOT NULL PRIMARY KEY,	reg INTEGER, prov INTEGER,	comune INTEGER,	targa VARCHAR(3),	nome  VARCHAR(50),	gennaio REAL,	febbraio REAL,	marzo REAL,	aprile REAL,	maggio REAL,	giugno REAL,	luglio REAL,	agosto REAL,	settembre REAL,	ottobre REAL,	novembre REAL,	dicembre REAL,	media REAL, latitudine_g INTEGER,latitudine_m INTEGER,latitudine_s INTEGER,longitudine_g INTEGER,longitudine_m INTEGER,longitudine_s INTEGER)");
	q.exec();
	#ifdef DEBUG
	qDebug()<<"createTable.."<<q.lastError();
	#endif
 
}
void MainWindow::createTablePanel(const QString &type)
{
	QSqlDatabase db=QSqlDatabase::database(type);
	db.setDatabaseName(databasePanels);
	QSqlQuery q(db);
	q.prepare(" CREATE TABLE pannelli ( id INTEGER NOT NULL PRIMARY KEY,costruttore VARCHAR(50),modello VARCHAR(50),pnom REAL,voc REAL,isc REAL,imp REAL,noct REAL,peso REAL,vmp REAL,vmax REAL,beta REAL,alfa REAL,gamma REAL,tolleranza REAL,h REAL,l REAL,s REAL,efficienza REAL, usura REAL)");
	q.exec();
        q.prepare("create table inverter (id INTEGER NOT NULL PRIMARY KEY,costruttore VARCHAR(50),modello VARCHAR(50),pin REAL,pnom REAL,vmax REAL,vmin REAL,vmpmin REAL,vmpmax REAL,imax REAL, efficienza REAL, usura REAL,tipo VARCHAR(50),vout REAL, icc REAL, tra BOOLEAN DEFAULT 0,cosphi REAL )");
	q.exec();

// 	#ifdef DEBUG
	qDebug()<<"createTable in panels."<<q.lastError()<<q.executedQuery()<<q.lastError().text()<<databasePanels;
	qDebug()<<q.lastError().driverText();
// 	#endif
}
void MainWindow::initializeModelPanels(const QString &id)
{
	QSqlDatabase db= QSqlDatabase::database(id);
	modelPanels = new QSqlTableModel(0,db); /* This will be used to list the panels*/
	
}
void MainWindow::initializeModel()
{
	

    if (localita.source == radEnea || localita.source == radNasa)
    {
	modelRadiazione->setQuery("SELECT * from radiazione");
	modelRadiazione2->setQuery("SELECT * from radiazione");
    }
     if (localita.source == radUNI){
         modelRadiazione->setQuery("SELECT * from uni");
         modelRadiazione2->setQuery("SELECT * from uni");
     }
  	proxyModel = new QSortFilterProxyModel(this);
  	proxyModel->setSourceModel(modelRadiazione);
	proxyModel->setDynamicSortFilter(true);
//  	proxyModel->setFilterKeyColumn(-1);

// 	comuniView->setModel(modelRadiazione);
	comuniView->setModel(proxyModel);

        if (localita.source == radEnea || localita.source == radNasa)
        {
            comuniView->setModelColumn(5);
            proxyModel->sort(5, Qt::AscendingOrder);
        }
        if (localita.source == radUNI){
            comuniView->setModelColumn(1);
            proxyModel->sort(1, Qt::AscendingOrder);
        }
	
	 
	
	 
	
	
// 	qDebug()<<"Problems in initializeModel="<<model->lastError();
}
bool MainWindow::createConnection(const QString &id)
{
	databasePanels = QCoreApplication::applicationDirPath()+"/panels.db";
         #ifdef DEBUG
	qDebug()<<"database pannelli="<<databasePanels;
         #endif
	 
	QSqlDatabase db =  QSqlDatabase::addDatabase("QSQLITE",id);
	
	db.setDatabaseName(databasePanels);
	db.open();
                 #ifdef DEBUG
		qDebug()<<"Problems with database panels="<<db.lastError()<<db.isOpen()<<id;
                #endif
	 
	if (db.isOpen())
		return true;
	else
	
		return false;
}
bool MainWindow::createConnection()
{	
       // #ifdef DEBUG
	qDebug()<<"database="<<databaseEntry;
      //  #endif
	QSqlDatabase db =  QSqlDatabase::addDatabase("QSQLITE");
	
	db.setDatabaseName(databaseEntry);
	db.open();
               #ifdef DEBUG
                qDebug()<<"Problems with Enea="<<db.lastError()<<db.isOpen();
        #endif
	if (db.isOpen())
		return true;
	else
	
		return false;


}
 
bool MainWindow::checkIfDatabase(const QString &id,const QString &table)
{
	/*Controlla se il file di database con conn. identificata da id esiste*/
	QFileInfo file(QCoreApplication::applicationDirPath()+"/panels.db");	
	QSqlDatabase temp = QSqlDatabase::database(id);
	if (file.exists()) {
		

		QSqlQuery m(temp);
		m.prepare("SELECT * from "+ table);
		m.exec();

  	if (!m.isActive()) {	
 
			return false;


		} else {
			return true;
		} 
		
} else {

	return false;
	}
}
bool MainWindow::checkIfDatabase()
{
	// Check if the database is present in the current dir
        QFileInfo file(QCoreApplication::applicationDirPath()+"/datiUNIEnea.db");
 	QSqlQueryModel m;
	if (file.exists()) {
		QSqlDatabase temp = QSqlDatabase::database();
		temp.setDatabaseName(databaseEntry);
		
		m.setQuery("SELECT * from radiazione");
		
	#ifdef DEBUG
	qDebug()<<m.lastError()<<m.query().executedQuery()<<temp<<m.rowCount();
	#endif 
		if ( (m.rowCount())<10) {
                        int r= QMessageBox::question(this,tr("Database corrotto"),"Il database e' presente ma sembra non valido. Ci sono solo" + QString::number(m.rowCount()) + " chiavi.",QMessageBox::Ok);
			if (r)
				 return true;
			else 
				return false;
		}
		if (!m.query().isActive()) {	
			QMessageBox::critical(this,tr("Database corrotto"),"Il database e' presente ma sembra non valido",QMessageBox::Ok);
			return false;

		} else {
			return true;
		} 
	} else {
			return false;
	}
	
}
void MainWindow::setDamp()
{	
	localita.azi    = aziValue->value();
	localita.incl   = inclValue->value();
	localita.albedo = albedoValue->value();
	localita.anno   = annoValue->value();
        initializeModel();

	if (!locValue->text().isEmpty())
	{ 
            doNotSetCity=false;
            #ifdef DEBUG
            qDebug()<<"MW Son in setDamp"<<localita.azi<<localita.incl<<locValue->text()<<localita.name;
             #endif
            localita.name = locValue->text();
            updateLat();

            set(normal);

}


// 		

		 
		 
}
bool MainWindow::additionalParChanged()
{
	bool o = false;
	
	for(int i=0;i<localita.additionalIncl.size();i++){
		if (localita.additionalIncl.at(i) !=inclValue2->value() ||
		    localita.additionalAzi.at(i)  !=aziValue2->value()||
		    localita.additionalArea.at(i) !=areaValue2->value()){
		o =true;
  		qDebug()<<"MW addPar cahnged=TRUE"<<localita.additionalIncl.at(i);
		}
	}
	return o;
}
bool MainWindow::somethingChanged()
{
	/* This function check if the lat lon incl albedo area have changed */
	if (aziValue->value()!=localita.azi   || 
		inclValue->value()  !=localita.incl     ||
		albedoValue->value()!=localita.albedo  ||
		areaValue->value()!=localita.area      ||
		additionalParChanged() ){
                  qDebug()<<"MainWindow SomethingChanged...";
                  firstPassDone = false;//for simulation
		return true;
               
	}
	else 
	return false;

}
void MainWindow::updateSitePar()
{
			
			if (localita.tipo==2){
			localita.additionalAzi.resize(0);
			localita.additionalIncl.resize(0);
			localita.additionalArea.resize(0);
			localita.additionalAzi<< aziValue2->value();
			localita.additionalIncl<< inclValue2->value();	
			localita.additionalArea<< areaValue2->value();
			}
// 			qDebug()<<"MainWindow updateSitePar..."<<localita.additionalAzi<<localita.additionalIncl;

			localita.azi  = aziValue->value();
			localita.incl = inclValue->value();
                        localita.albedo = albedoValue->value();
			localita.area =areaValue->value() ;
			localita.wind=windValue->value();
			localita.mounting=mountingValue->currentIndex();
			localita.mountingHeight=mountingHeightValue->value();
			localita.concRatio = concRatioValue->value();
			localita.tempMin = tempMinValue->value();
			localita.tempMax = tempMaxValue->value();
// 			otherLosses.otherLoss = otherLoss->value();
}
void MainWindow::setDampOthers( )
{

	
        if (!comuneValue->text().isEmpty() ||
            (!(wrongCoordinates) || (onlyLat) ) ||
            googleNameAvailable || bothCoord) {
		  if (somethingChanged()) {
                        qDebug()<<"I am in damp others some changed";
			updateSitePar();
                        set(normal);
		 }

            } else {
                qDebug()<<"I am in damp others no change";
                    /* update only the shadows */
                   // qDebug()<<"Ombre present in Mainwindow"<<ombrePresent;
                    if (ombrePresent)
                                    w->drawMyContents(0);
            // 	qDebug()<<"setDampOther..nonameAv?"<<noNameAvailable;
       // updatePower(0);
        }
// 	updateTempDaily();

	 
        }
void MainWindow::set()
{
    set(normal);
}

void MainWindow::set(int mode)
{
//QProgressDialog pr( tr("Calcolo diagrammi..."),tr("Annulla"),0,4,this);
//pr.setValue(0);

    progressCompute->show();

 #ifdef DEBUG
qDebug()<<"set()..wrongCoordinate"<<wrongCoordinates;
qDebug()<<"set()..onlyLat"<<onlyLat;
qDebug()<<"set()..noNameAvailable"<<noNameAvailable;
qDebug()<<"set()..bothCoord"<<bothCoord;
qDebug()<<"set()..googleName"<<googleNameAvailable;
qDebug()<<"set()..googleError"<<googleError;
qDebug()<<"set()..useLoadedLoc"<<useLoadedLoc;
qDebug()<<"set() localita before computation"<<localita.latGradi<<localita.latMin<<localita.latSec<<localita.lonGradi<<localita.lonMin<<localita.lonSec;
   #endif
	
    if (loadedProject)
    {
        setWindowModified(false);
        loadedProject=false;
    }
    else
        if (mode!=fromGoogle)
            setWindowModified(true);




// 	double Rb[12],Hincl[12];

        /*We must tell to recompute the dailyValues*/
        /*every time we make a new computation */
        dailyValuesPresent = false;
        statusLabelPower->setText(tr("Pot.= ") + QString( "%L1").arg(installedPower()) + " kWp");
	
	if (!(wrongCoordinates) || (onlyLat) || bothCoord || !noNameAvailable || (googleNameAvailable && !googleError ) ||
	      useLoadedLoc||useLoc)
	{
//            qDebug()<<"SET()........................................noNameAvailable"<<noNameAvailable;
		QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
// 			utcValue->setValue(floor((localita.lonGradi+7.5)/15));
//                 qDebug()<<"MW time START SIM before optimumplot"<<QTime::currentTime().toString();
                        progressCompute->setValue(1);
                        createOptimumPlot();
                        progressCompute->setValue(2);
                        setIntegrationInterval();
//                        qDebug()<<"MW time START SIM after optimumplot"<<QTime::currentTime().toString();
			createSolarPlot();
                        progressCompute->setValue(3);
//qDebug()<<"MW time START SIM after MyPlot"<<QTime::currentTime().toString();
			/* There is a strange bug in th QWT's refresh. The following seems to be necessary */
			if (firstRun){
				createSolarPlot();
				firstRun=false;
			}


                        //w->computeShadow();
                     //   qDebug()<<"MW time START SIM after MyPlot compute shadow"<<QTime::currentTime().toString();

			updateLimitDistance(0,localita.incl);
                progressCompute->setValue(4);
		if (extractRadiazione(localita)) {
 
				noRadiation    = false;
				isDirty = true;
                        	projectIsDirty = true;        

                		createRealePlot();
//                                qDebug()<<"MW time START SIM after reale Plot"<<QTime::currentTime().toString();
				createEnergyOutPlot();
                                progressCompute->setValue(5);
//                                qDebug()<<"MW time START SIM after eneryout"<<QTime::currentTime().toString();
				createCheckInverter();
				validForExport = true;
				drawHourlyValues();

                                firstPassDone = false;//for simulation

                                updateTempWidget( );
                                updateWindWidget();
                                tempUpdatePower->setEnabled(false);
                                windUpdatePower->setEnabled(false);
                                suggestMinMax();
                                #ifdef PLUSVERSION2
                                updateDetails();
                                #endif

				
			} else
			{
					noRadiation     = true;
					validForExport = false;
					statusBar()->showMessage(tr("Estrazione radiazione fallita"),2000);
					noRad(onlyRad);
                                        progressCompute->setValue(5);
			}	
	#ifdef DEBUG
	qDebug()<<"MW set after"<<validForExport<<noRadiation;
	#endif
	} else	
		{
		validForExport = false;			
		noRad(all);
		
		}
	QApplication::restoreOverrideCursor();		
	//Last check

	


//DEBUG
// QPolygonF f = findNasaData(localita.latGradi,localita.lonGradi);
        progressCompute->reset();
        progressCompute->hide();
	}
		
		
 void MainWindow::toFade()
{
	if ((!noNameAvailable)||showItalia)
		pagesWidget->setCurrentIndex(1);
	else
		pagesWidget->setCurrentIndex(0);
}

		

 
void MainWindow::loadEneaData()

{
	confirmErase("radiazione");
	QStringList campi;
	campi<<"reg"<<"prov"<<"comune"<<"targa"<<"nome"<<"gennaio"<<"febbraio"<<"marzo"<<"aprile"<<"maggio"<<"giugno"<<"luglio"<<"agosto"<<"settembre"<<"ottobre"<<"novembre"<<"dicembre"<<"media";
	
	QString fileName= QFileDialog::getOpenFileName(this, tr("Apri"),
                                                     "/home",
                                                     tr("Text File (*.txt *.rtf )"));
	
	if (!fileName.isNull()) {
		
// 	        int count;
		QFile file(fileName);
		QFileInfo fileInfo(fileName);
		QTextStream in(&file);

	// Suppose 10*8byte = 80 byte per line
        int lines = (int)ceil(fileInfo.size()/20);
	QProgressDialog progress(tr("Caricamento dei dati di radiazione..."), tr("Cancella "), 0, lines, this);
  	progress.setWindowModality(Qt::WindowModal);
		if (file.open(QIODevice::ReadOnly)){
			
			int i=0;
			
			while (!in.atEnd()) {
				
				progress.setValue(i);
				 if (progress.wasCanceled()) {
           					  
// 						  model->setQuery("DELETE FROM radiazione");
						  break;
				} else {
					QString lineRaw = in.readLine();	
					QStringList l = lineRaw.split(",");
					QString name = l.at(4);
					name.replace(QString("'"),QString("''")); //escaping single quote
					QString sigla = l.at(3);
					l[4] = "\'" + name + "\'";
					l[3] = "\'" + sigla + "\'";
					QString line;
					line = l.join(",");
					
					
					//QStringLins = line.split(','); //Enea uses comma as separators
	modelRadiazione->setQuery("INSERT INTO radiazione (" + campi.join(",") + ") VALUES ("+line + ")");
	 
	if (modelRadiazione->lastError().isValid()) {
				#ifdef DEBUG
				 qDebug()<<modelRadiazione->lastError()<<("INSERT INTO radiazione (" + campi.join(",") + ") VALUES ("+line + ")");
				#endif
				QMessageBox::critical(this,tr("Errore"),tr("Il database sembra non corretto. Prova a riscaricarlo."),QMessageBox::Ok);
				convertionDone = false;
				return;
					}
					i++;
			
				}	
		 
			convertionDone = true;
			}
		progress.setValue(lines);
		
		}
	}
	int a = QMessageBox::question(this,tr("Dati sui Comuni"),tr("I dati ENEA non contengono le coordinate dei comuni. Per completare l'operazione devi caricare i dati dei Comuni. Carico adesso?"),QMessageBox::Ok,QMessageBox::Cancel);
	
	if (a==QMessageBox::Ok) loadComuniData();
}

void MainWindow::loadComuniData()
{

//   	confirmErase("comuni");
	QString line,lineRaw,reg,prov,com,qS;
	QStringList l;
	QString name,latGradi,latMin,latSec,lonGradi,lonMin,lonSec;
	QStringList campi,campiRad,lineRad;
	QString sigla;
	QSqlQuery query;
	int lines;

	campi<<"reg"<<"prov"<<"comune"<<"latitudine_g"<<"latitudine_m"<<"latitudine_s"<<"longitudine_g"<<"longitudine_m"<<"longitudine_s"<<"altitudine_c"<<"altitudine_m"<<"altitudine_ma"<<"superficie"<<"pop"<<"nome"<<"sigla";  
	
	campiRad<<"latitudine_g"<<"latitudine_m"<<"latitudine_s"<<"longitudine_g"<<"longitudine_m"<<"longitudine_s";

	QString fileName= QFileDialog::getOpenFileName(this, tr("Apri"),
                                                     "/home",
                                                     tr("Text File (*.txt *.rtf )"));
	
	if (!fileName.isNull()) {
		
// 	        int count;
		QFile file(fileName);
		QFile temp(fileName);
		QFileInfo fileInfo(fileName);
		QFileInfo tempInfo(fileName);
		QTextStream inTemp(&temp);
		QTextStream in(&file);
	

	if (temp.open(QIODevice::ReadOnly)) {
		QString t = inTemp.readLine();


                lines = (int)ceil(fileInfo.size()/t.size()*4);
	} else  
		lines=0;
	 
	QProgressDialog progress(tr("Caricamento dei dati sui comuni..."), tr("Cancella "), 0, lines, this);
  	progress.setWindowModality(Qt::WindowModal);
	if (file.open(QIODevice::ReadOnly)){
			
			int i=0;
			
			while (!in.atEnd()) {
				
				progress.setValue(i);
 				 if (progress.wasCanceled()) {
           					  
// 						  model->setQuery("DELETE FROM radiazione");
 						  break;
 				} else {
  					  lineRaw = in.readLine();
// 					qDebug()<<lineRaw;	
  					 l = lineRaw.split(",");
  					  name = l.at(14);
  					name.replace(QString("'"),QString("''")); //escaping single quote
  					sigla = l.at(15);
					l[14] = "\'" + name + "\'";
					l[15] = "\'" + sigla + "\'";

					reg   = l.at(0);
					prov  = l.at(1);
					com   = l.at(2);
					latGradi = l.at(3);
					latMin   = l.at(4);
					latSec   = l.at(5);
					lonGradi = l.at(6);
					lonMin   = l.at(7);
					lonSec	 = l.at(8);

  					line = l.join(","); 
// 					
					lineRad.clear();
					lineRad << l.at(3)<<l.at(4)<<l.at(5)<<l.at(6)<<l.at(7)<<l.at(8);		
// 					
 					//QStringLins = line.split(','); //Enea uses comma as separators
//  					model->setQuery("INSERT INTO comuni (" + campi.join(",") + ") VALUES ("+line + ")");
	qS = "UPDATE radiazione SET latitudine_g="+latGradi+",latitudine_m="+latMin+",latitudine_s="+latSec+",longitudine_g="+lonGradi+",longitudine_m="+lonMin+",longitudine_s="+lonSec+"  WHERE reg="+reg+" AND prov="+prov+" AND comune="+com;


  			modelRadiazione->setQuery(qS);
					 #ifdef DEBUG
 					 qDebug()<<modelRadiazione->lastError()<<qS;
 					 #endif
					i++;
// 				 
				}	
		 
			convertionDone = true;
			initializeModel();
			}
// 		progress.setValue(lines);
		
		}
	
	}

 }
 
void MainWindow::exportPDF()
{
// 	switch (tabWidget->currentIndex()) {
// 		case 0:
// 		w->exportPDF();
// 		break;
// 		case 1:
// 		o->exportPDF();
// 		break;
// 		case 2:
// 		reale->exportPDF();
// 		break;
// 		case 3:
// 		energyOut->exportPDF();
// 	}
	
}
void MainWindow::createActions()
{
	 for (int i = 0; i < MaxRecentFiles; ++i) {
       		 recentFileActions[i] = new QAction(this);
        	 recentFileActions[i]->setVisible(false);
      		  connect(recentFileActions[i], SIGNAL(triggered()),this, SLOT(openRecentFile()));
    }


        a_export = new QAction(tr("Esporta dati (*.txt)"),this);
	a_export->setShortcut(tr("Ctrl+E"));
	a_export->setIcon(QIcon(":/images/export.png"));
        a_export->setStatusTip(tr("Esporta estratto dati di progetto in formato testo"));
        connect(a_export,SIGNAL(triggered()),this,SLOT(exportData()));

	a_export_daily = new QAction(tr("Esporta dati giornalieri interpolati"),this);
	a_export_daily->setShortcut(Qt::CTRL +Qt::SHIFT + Qt::Key_D);
	connect(a_export_daily,SIGNAL(triggered()),SLOT(exportDaily()));

	a_exportPDF = new QAction(tr("Esporta PDF"),this);
	a_exportPDF->setIcon(QIcon(":/images/adobe.ico"));
	a_exportPDF->setStatusTip(tr("Esporta in PDF il minireport"));
	connect(a_exportPDF,SIGNAL(triggered()),SLOT(exportPDF()));

	a_impostazioni = new QAction(tr("Impostazioni"),this);	
	a_impostazioni->setShortcut(tr("Ctrl+I"));
	a_impostazioni->setIcon(QIcon(":/images/settings.png"));
        a_impostazioni->setStatusTip(tr("Impostazioni del modello e del sistema"));
	connect(a_impostazioni,SIGNAL(triggered()),SLOT(updateModelSettings()));

	a_quit   = new QAction(tr("Esci"),this);
	a_quit->setShortcut(tr("Ctrl+Q"));
	a_quit->setStatusTip(tr("Esci"));
        //connect(a_quit,SIGNAL(triggered()),SLOT(close()));
        connect(a_quit,SIGNAL(triggered()),qApp,SLOT(closeAllWindows()));

	a_refresh = new QAction(tr("Aggiorna"),this);
	a_refresh->setShortcut(tr("Ctrl+R"));
	a_refresh->setIcon(QIcon(":/images/arrow.png"));
	connect(a_refresh,SIGNAL(triggered()),SLOT(set()));

	
	a_load_data = new QAction(tr("Carica dati"),this);
	a_load_comuni = new QAction(tr("Carica comuni"),this);
	a_load_comuni->setStatusTip(tr("Carica il database Enea-Istat dei Comuni italiani"));
	connect(a_load_data,SIGNAL(triggered()),this,SLOT(loadEneaData()));	
	connect(a_load_comuni,SIGNAL(triggered()),this,SLOT(loadComuniData()));	 
	
// 	a_view_solar = new QAction(tr("&Diagramma solare"),this);	
	
	a_view_opti = new QAction(tr("&Variazione Tilt"),this);
	a_view_opti->setShortcut(tr("Ctrl+T"));
	a_view_opti->setIcon(QIcon(":/images/opti2.png"));
	a_view_opti->setStatusTip(tr("Mostra il diagramm del tilt ottimo rispetto al piano orizzontale"));
// 	a_view_opti->setCheckable(true);
	connect(a_view_opti,SIGNAL(triggered(bool)),this,SLOT(viewOpti()));	

	a_view_reale = new QAction(tr("Radiazione reale"),this);
        a_view_reale->setShortcut(tr("Ctrl+W"));
        a_view_reale->setIcon(QIcon(":/images/rr.png"));
	a_view_reale->setStatusTip(tr("Mostra il diagramma della radiazione reale compresa di ombreggiamenti"));
// 	a_view_reale->setCheckable(true);
		connect(a_view_reale, SIGNAL(triggered()),this,SLOT(viewReale()));

        a_view_energy = new QAction(tr("Energia producibile"),this);
        a_view_energy->setShortcut(tr("Ctrl+J"));
        a_view_energy->setIcon(QIcon(":/images/ep.png"));
        a_view_energy->setStatusTip(tr("Mostra il diagramma dell'energia producibile dal sistema corrente"));
        // 	a_view_reale->setCheckable(true);
        connect(a_view_energy, SIGNAL(triggered()),this,SLOT(viewEnergy()));

        a_view_site = new QAction(tr("Sito"),this);
        a_view_site->setShortcut(tr("Ctrl+P"));
        a_view_site->setIcon(QIcon(":/images/mp.png"));
        a_view_site->setStatusTip(tr("Localizza il sito"));
        connect(a_view_site,SIGNAL(triggered()),SLOT(viewSite()));


        a_view_sup = new QAction(tr("Superficie"),this);
        a_view_sup->setShortcut(tr("Ctrl+F"));
        a_view_sup->setIcon(QIcon(":/images/supcap.png"));
        a_view_sup->setStatusTip(tr("Dati sulla superficie captante"));
        connect(a_view_sup,SIGNAL(triggered()),SLOT(viewSup()));

        a_view_meteo = new QAction(tr("Dati meteo"),this);
        a_view_meteo->setShortcut(tr("Ctrl+M"));
        a_view_meteo->setIcon(QIcon(":/images/meteo.png"));
        a_view_meteo->setStatusTip(tr("Visualizza temperature medie e vento"));
        connect(a_view_meteo,SIGNAL(triggered()),SLOT(viewMeteo()));

	a_get_albedo = new QAction(tr("&Albedo"),this);
	a_get_albedo->setIcon(QIcon(":/images/albedo.ico"));
	a_get_albedo->setShortcut(tr("Ctrl+B"));
	a_get_albedo->setStatusTip(tr("Imposta il valore di albedo"));
	connect(a_get_albedo,SIGNAL(triggered()),SLOT(viewAlbedo()));

	
 
	 
	a_load_shadow = new QAction(tr("Carica ombre"),this);
	a_load_shadow->setShortcut(Qt::CTRL + Qt::Key_O);
        a_load_shadow->setIcon(QIcon(":/images/ombreadd.png"));
	a_load_shadow->setStatusTip(tr("Carica i dati d'ombra"));

	a_delete_shadow = new QAction(tr("Rimuovi ombre"),this);
	a_delete_shadow->setShortcut(tr("Ctrl+X"));
        a_delete_shadow->setIcon(QIcon(":/images/scissors.png"));
	a_delete_shadow->setStatusTip(tr("Elimina le ombre"));
	connect(a_load_shadow,SIGNAL(triggered()),SLOT(loadShadow()));
	connect(a_delete_shadow,SIGNAL(triggered()),w,SLOT(deleteShadow()));
	
  	a_check_custom = new QAction(tr("Sorgente"),this);
	a_check_custom->setStatusTip(tr("Seleziona la sorgente dati di radiazione"));
  	connect(a_check_custom,SIGNAL(triggered()),SLOT(setRadData()));

	a_add_component = new QAction(tr("Aggiungi componenti"),this);
	a_add_component->setStatusTip(tr("Aggiungi moduli FV o inverter al database componenti"));
        a_add_component->setShortcut(tr("Ctrl+D"));
	a_add_component->setIcon(QIcon(":/images/addcomponent.png"));
	connect(a_add_component,SIGNAL(triggered()),SLOT(addPV()));

	a_select_component = new QAction(tr("Selezione pannello"),this);
	a_select_component->setStatusTip(tr("Seleziona un pannello fv dal database"));
        a_select_component->setShortcut(tr("Ctrl+Shift+W"));
 	a_select_component->setIcon(QIcon(":/images/selectcomponent.png"));
	connect(a_select_component,SIGNAL(triggered()),SLOT(selectPV()));

	a_select_inv = new QAction(tr("Selezione Inverter"),this);
	a_select_inv->setStatusTip(tr("Seleziona un inverter dal database"));
	a_select_inv->setShortcut(tr("Ctrl+Shift+I"));
 	a_select_inv->setIcon(QIcon(":/images/selectinv.png"));
	connect(a_select_inv,SIGNAL(triggered()),SLOT(selectInv()));

	a_save_project = new QAction(tr("Salva progetto"),this);
	a_save_project->setStatusTip(tr("Salva il progetto corrente"));
	a_save_project->setShortcut(tr("Ctrl+S"));
	a_save_project->setIcon(QIcon(":/images/save.png"));
	connect(a_save_project,SIGNAL(triggered()),SLOT(save()));

	a_saveas_project = new QAction(tr("Salva progetto con nome"),this);
	a_saveas_project->setStatusTip(tr("Salva il progetto corrente con un nuovo nome"));
	a_saveas_project->setShortcut(tr("Ctrl+S+A"));
	a_saveas_project->setIcon(QIcon(":/images/filesaveas.png"));
	connect(a_saveas_project,SIGNAL(triggered()),SLOT(saveAs()));

	a_load_project = new QAction(tr("Apri progetto"),this);
	a_load_project->setStatusTip(tr("Apre un progetto "));
	a_load_project->setShortcut(tr("Ctrl+O"));
	a_load_project->setIcon(QIcon(":/images/open.png"));
	connect(a_load_project,SIGNAL(triggered()),SLOT(load()));

	a_new_project = new QAction(tr("Nuovo progetto"),this);
	a_new_project->setStatusTip(tr("Crea un nuovo progetto "));
	a_new_project->setShortcut(tr("Ctrl+N"));
	a_new_project->setIcon(QIcon(":/images/new.png"));
	connect(a_new_project,SIGNAL(triggered()),SLOT(newProject()));
	
//	a_create_daily = new QAction(tr("Genera dati giornalieri"),this);
//	a_create_daily->setStatusTip(tr("Genera dati di radiazione giornalieri interpolati sulla base di dati medi mensili di radiazione "));
//	a_create_daily->setShortcut(tr("Ctrl+F"));
//	a_create_daily->setIcon(QIcon(":/images/fit.png"));
//	connect(a_create_daily,SIGNAL(triggered()),SLOT(createDailyRealePlot()));

        a_property = new QAction(tr("Lingua/Opzioni"),this);
        a_property->setStatusTip(tr("Cambia Lingua e altre opzioni"));
	a_property->setShortcut(tr("Ctrl+Shift+O"));
	connect(a_property,SIGNAL(triggered()),SLOT(updateOptions()));

	
	a_suggest = new QAction(tr("Wizard"),this);
	a_suggest->setStatusTip(tr("Calcola area captante in base ai consumi"));
	a_suggest->setShortcut(tr("Ctrl+Shift+S"));
	a_suggest->setIcon(QIcon(":/images/wizard.png"));
	connect(a_suggest,SIGNAL(triggered()),SLOT(wizard()));

        a_print_report_ps = new QAction(tr("Stampa report PostScript"),this);
        a_print_report_ps->setIcon(QIcon(":/images/postscript.png"));
        a_print_report_ps->setShortcut(tr("Ctrl+Shift+T"));
        a_print_report_ps->setStatusTip(tr("Stampa rapporto in PostScrip"));
        connect(a_print_report_ps,SIGNAL(triggered()),SLOT(printPS()));

	a_print_report = new QAction(tr("Stampa report PDF"),this);
        a_print_report->setIcon(QIcon(":/images/adobe.ico"));
	a_print_report->setShortcut(tr("Ctrl+Shift+P"));
        a_print_report->setStatusTip(tr("Stampa rapporto in PDF"));
	connect(a_print_report,SIGNAL(triggered()),SLOT(print()));

        a_print  = new QAction(tr("Stampa report"),this);
        a_print->setIcon(QIcon(":/images/print.png"));

        a_print->setStatusTip(tr("Stampa rapporto sintetico"));
        connect(a_print,SIGNAL(triggered()),SLOT(printGeneral()));

	
	a_about = new QAction(tr("Info"),this);
 	connect(a_about,SIGNAL(triggered()),SLOT(about()));

	a_shadow_editor = new QAction(tr("Editor di ombre"),this);
	a_shadow_editor->setIcon(QIcon(":/images/editorshadow.png"));
	a_shadow_editor->setStatusTip(tr("Apre l'editor di ombre vicine"));
	connect(a_shadow_editor,SIGNAL(triggered()),SLOT(newShadowEditor()));

#ifdef PLUSVERSION
	a_eleload_editor = new QAction(tr("Consumi e carichi elettrici"),this);
	a_eleload_editor->setIcon(QIcon(":/images/editorconsumi.png"));
        a_eleload_editor->setShortcut(tr("Ctrl+G"));
	a_eleload_editor->setStatusTip(tr("Apre l'editor dei consumi elettrici"));
	connect(a_eleload_editor,SIGNAL(triggered()),SLOT(openLoad()));

	a_simulate = new QAction(tr("Simulazione energetica"),this);
	a_simulate->setIcon(QIcon(":/images/play.png"));
	a_simulate->setStatusTip(tr("Lancia la simulazione oraria per la valutazione dei contributi energetici associati al sistema"));
	connect(a_simulate,SIGNAL(triggered()),SLOT(simulateNew()));

        a_simulate_redo = new QAction(tr("Simulazione economica"),this);
	a_simulate_redo->setIcon(QIcon(":/images/play2.png"));
        a_simulate_redo->setShortcut(tr("Ctrl+L"));
        a_simulate_redo->setStatusTip(tr("Lancia la simulazione economica. Si assume che solo i parametri economici sono cambiati"));
	connect(a_simulate_redo,SIGNAL(triggered()),SLOT(simulateNewEco()));

	a_ecoval = new QAction(tr("Configura parametri economici"),this);
	a_ecoval->setIcon(QIcon(":/images/ecopara.png"));
	a_ecoval->setStatusTip(tr("Configura i parametri economici associati all'allacciamento del sistema alla rete elettrica"));
        a_ecoval->setShortcut(tr("Ctrl+H"));
        connect(a_ecoval,SIGNAL(triggered()),SLOT(showEcoVal()));
#endif
	a_check_update = new QAction(tr("Controlla aggiornamenti"),this);
        a_check_update->setStatusTip(tr("Controlla se vi sono aggiornamenti per la versione corrente di SolarCalc"));
	connect(a_check_update,SIGNAL(triggered()),SLOT(checkUpdates()));


        a_export_esim_text = new QAction(tr("Esporta dati orari energia prodotta"),this);
        a_export_esim_text->setStatusTip(tr("Esporta i risultati energetici orari di produzione su file di testo"));
        a_export_esim_text->setToolTip(tr("<p>Per esportare i dati energetici orari simulati, occorre effettuare almeno una simulazione energetica</p>"));
        a_export_esim_text->setIcon(QIcon(":/images/textgreen.png"));
        connect(a_export_esim_text,SIGNAL(triggered()),SLOT(exportHourlyEnergy()));

        a_export_allsim = new QAction(tr("Esporta simulazione"),this);
        a_export_allsim->setStatusTip(tr("Esporta i dati energetici orari e i risultati di simulazione di produzione su file"));
        a_export_allsim->setToolTip(tr("<p>Per esportare i risultati di simulazione, occorre effettuare almeno una volta la simulazione</p>"));
        a_export_allsim->setIcon(QIcon(":/images/textorange.png"));
       // connect(a_export_esim_text,SIGNAL(triggered()),SLOT(exportHourlyEnergy()));

        a_load_esim = new QAction(tr("Carica energia oraria annuale"),this);
        a_load_esim->setIcon(QIcon(":/images/loadsimdata.png"));
        a_load_esim->setToolTip(tr("<p>Carica i dati orari di produzione elettrica annuale per la simulazione"));
        a_load_esim->setStatusTip(tr("Carica da file dati energetici orari per la simulazione"));
        connect(a_load_esim,SIGNAL(triggered()),SLOT(loadHourlyEnergy()));

        a_sim_options = new QAction(tr("Imposta simulazione economica"),this);
        a_sim_options->setToolTip(tr("Imposta alcuni parametri usati nella simulazione economica"));
        connect(a_sim_options,SIGNAL(triggered()),SLOT(setSimOptions()));

        a_mini_word = new QAction(tr("Getione documentazione"),this);
        a_mini_word->setIcon(QIcon(":/images/textIcon.png"));
        a_mini_word->setToolTip(tr("Crea e stampa relazioni di progetto per documentazione al cliente"));
        connect(a_mini_word,SIGNAL(triggered()),SLOT(showMiniWord()));

        a_details = new QAction(tr("Dati di progetto"),this);
        a_details->setToolTip(tr("Imposta i dati del cliente e del progettista"));
        a_details->setIcon(QIcon(":/images/users.png"));
        connect(a_details,SIGNAL(triggered()),SLOT(showDetails()));


}
void MainWindow::createMenu()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(a_new_project);
	fileMenu->addAction(a_load_project);
	fileMenu->addAction(a_save_project);
	fileMenu->addAction(a_saveas_project);
        fileMenu->addSeparator();
	fileMenu->addAction(a_impostazioni);
#ifdef PLUSVERSION2
        fileMenu->addAction(a_details);
#endif
        fileMenu->addAction(a_property);
        fileMenu->addSeparator();
        fileMenu->addAction(a_export);
        QMenu* stampaMenu = fileMenu->addMenu(tr("Stampa"));
        stampaMenu->addAction(a_print_report);
      //  stampaMenu->addAction(a_print_report_ps);
        stampaMenu->addAction(a_print);
//	fileMenu->addAction(a_print_report);
//        fileMenu->addAction(a_print);
// 	exportMenu = fileMenu->addMenu(tr("Esporta"));
	
// 	exportMenu->addAction(a_export_daily);
	 separatorAction = fileMenu->addSeparator();
	for (int i = 0; i < MaxRecentFiles; ++i)
        fileMenu->addAction(recentFileActions[i]);

	fileMenu->addSeparator();
	fileMenu->addAction(a_quit);

	viewMenu = menuBar()->addMenu(tr("&Visualizza"));
// 	viewMenu->addAction(dockParametri->toggleViewAction());
  //	viewMenu->addAction(dockMyPlot->toggleViewAction());
// 	viewMenu->addAction(dockOpti->toggleViewAction());
// 	viewMenu->addAction(a_view_solar);
        viewMenu->addAction(a_view_site);
        viewMenu->addAction(a_view_sup);
        viewMenu->addAction(a_view_meteo);
        viewMenu->addSeparator();
  	viewMenu->addAction(a_view_opti);
  	viewMenu->addAction(a_view_reale);
        viewMenu->addAction(a_view_energy);
// 	viewMenu->addAction(a_impostazioni);
	viewMenu->addAction(a_refresh);
	 

// 	toolMenu = strummenti->addMenu(tr("Carica &dati"));
        dataMenu = menuBar()->addMenu(tr("&Radiazione"));
	dataMenu->addAction(a_check_custom);
	  

	strumentiMenu = menuBar()->addMenu(tr("&Strumenti"));
#ifdef PLUSVERSION2
        strumentiMenu->addAction(a_mini_word);
#endif
        strumentiMenu->addSeparator();
	strumentiMenu->addAction(a_suggest);
	strumentiMenu->addAction(a_get_albedo);
	
        //eneaMenu = strumentiMenu->addMenu(tr("Carica dati Enea"));
        //eneaMenu->addAction(a_load_data);
        //eneaMenu->addAction(a_load_comuni);
	
// 	radMenu = strumentiMenu->addMenu(tr("Carica radiazione custom"));
// 	radMenu->addAction(a_load_rad);
	
        ombreMenu =strumentiMenu->addMenu(tr("&Ombre"));
	ombreMenu->addAction(a_load_shadow);
	ombreMenu->addAction(a_delete_shadow);
	ombreMenu->addAction(a_shadow_editor);

	strumentiMenu->addSeparator();
	strumentiMenu->addAction(a_add_component);
	strumentiMenu->addAction(a_select_component);
	strumentiMenu->addAction(a_select_inv);
	
	strumentiMenu->addSeparator();
#ifdef PLUSVERSION
	strumentiMenu->addAction(a_ecoval);
	strumentiMenu->addAction(a_eleload_editor);
        strumentiMenu->addSeparator();
	strumentiMenu->addAction(a_simulate);
	strumentiMenu->addAction(a_simulate_redo);
        strumentiMenu->addAction(a_sim_options);


#endif

      //  strumentiExportMenu->addAction(a_load_esim);
#ifdef PLUSVERSION
      //  TODO
      //  strumentiExportMenu->addAction(a_export_allsim);
        strumentiExportMenu = strumentiMenu->addMenu((tr("Esporta dati simulazione")));
        strumentiExportMenu->addAction(a_export_esim_text);
        strumentiMenu->addAction(a_load_esim);
#endif


        aboutMenu = menuBar()->addMenu(tr("&Aiuto"));
	aboutMenu->addAction(a_about);

	aboutMenu->addAction(a_check_update);
	
	/*create toolbar*/
	toolBar = new QToolBar(this);
	addToolBar(Qt::TopToolBarArea,toolBar);
	toolBar->addAction(a_new_project);
	toolBar->addAction(a_load_project);
	toolBar->addAction(a_save_project);
	toolBar->addAction(a_saveas_project);
	toolBar->addAction(a_impostazioni);
	toolBar->addAction(a_export);
// 	toolBar->addAction(a_exportPDF);
	toolBar->addAction(a_print_report);

        
	toolBarView = new QToolBar(this);
	addToolBar(Qt::TopToolBarArea,toolBarView);
	toolBarView->addAction(a_view_opti);
	toolBarView->addAction(a_view_reale);
	toolBarView->addAction(a_refresh);

	toolBar2 = new QToolBar(this);
        addToolBar(Qt::TopToolBarArea,toolBar2);
        
        
        toolBar2->addAction(a_suggest);
	toolBar2->addAction(a_get_albedo);
      

        toolBar3 = new QToolBar(this);
        addToolBar(Qt::TopToolBarArea,toolBar3);
        toolBar3->addAction(a_load_shadow);
        toolBar3->addAction(a_delete_shadow);
        toolBar3->addAction(a_shadow_editor);


        toolBar4 = new QToolBar(this);
        addToolBar(Qt::TopToolBarArea,toolBar4);
        toolBar4->addAction(a_add_component);
        toolBar4->addAction(a_select_component);
        toolBar4->addAction(a_select_inv);



	/*To be divided*/
        toolBar5 = new QToolBar(this);
        addToolBar(Qt::TopToolBarArea,toolBar5);
//         addToolBar(Qt::TopToolBarArea,toolBar3);
        #ifdef PLUSVERSION
	toolBar5->addAction(a_ecoval);
        toolBar5->addAction(a_eleload_editor);
        toolBar5->addAction(a_simulate);
        toolBar5->addAction(a_simulate_redo);
       // toolBar5->addAction(a_export_allsim);
        toolBar5->addAction(a_export_esim_text);
        toolBar5->addAction(a_load_esim);
	#endif

	toolBar6 = new QToolBar(this);
	addToolBar(Qt::TopToolBarArea,toolBar6);
	toolBar6->addWidget(new QLabel(tr("Anno")));
	toolBar6->addWidget(annoValue);
	toolBar6->addWidget(new QLabel(tr("Mese")));
	toolBar6->addWidget(selectMonth);
	toolBar6->addWidget(new QLabel(tr("Giorno")));
	toolBar6->addWidget(selectDay);

        toolBar7 = new QToolBar(this);
        addToolBar(Qt::TopToolBarArea,toolBar7);

        toolBar7->addWidget(new QLabel(tr("Falda corrente"))) ;
        toolBar7->addWidget(comboCurrentField );



}
void MainWindow::updateOptions()
{
#ifdef PLUSVERSION
    Proprieta prop(this,1);//MONOLANG
#else
    Proprieta prop(this,0);//MULTILANG COMMUNITY
#endif
	switch (language){
		case 0:
		break;/* default is italian */
		case 1:
		prop.setLanguage(1);	
		break;/*english*/
		default:
		prop.setLanguage(0);
	}

        if (proxyEnabled){
            prop.enableProxy(true);
            prop.setProxy(proxy);
        }

        prop.setNumOfDecimals(numOfDec);
        prop.updateNumOfDecimals();
	
	
	if (prop.exec()){
		language = prop.getLang();
                numOfDec = prop.getNumberOfDecimals();

                proxy = prop.getProxy();
                proxyEnabled= prop.proxyEn();
            }

         if (support!=0)
             support->setProxy(proxy);

#ifdef PLUSVERSION
                if (cash!=0){
                    cash->setNumOfDec(numOfDec);
                    if (ecoTablePresent)
                        cash->updateTable();
                }
#endif
                qDebug()<<"Language="<<language<<numOfDec;

}
void MainWindow::openLoad()
{
#ifdef PLUSVERSION
        if (loadInterface!=0)
		loadInterface->show();
        if (loadInterface->isMinimized())
            loadInterface->showNormal();
        loadInterface->activateWindow();
#endif
}
void MainWindow::getLoad()
{
	int m = selectMonth->currentIndex();
	int day = selectDay->currentIndex();
	QPolygonF l;
	 
	 
                if (hourlyEOPlot!=0){
		l = loadInterface->getHourlyLoads(localita.anno,day+1,m+1);
		hourlyEOPlot->setLoad(l);
		hourlyEOPlot->enableDrawingLoads(checkDrawLoads->isChecked());
		}
	 
}
void MainWindow::updateSourceRadSettings()
{
	if (localita.source == radEnea)
	sourceRadSettings->radioEnea->setChecked(true);
	if (localita.source == radCustom)
	sourceRadSettings->radioCustom->setChecked(true);
	if (localita.source == radNasa)
	sourceRadSettings->radioNasa->setChecked(true);
         if (localita.source == radUNI)
        sourceRadSettings->radioUNI->setChecked(true);
//	if (localita.radUnit == radPvgis)
//            sourceRadSettings->radioPvgis->setChecked(true);
	if (localita.radUnit == megajoule)
	sourceRadSettings->radioMJ->setChecked(true);
	else
	sourceRadSettings->radioKWh->setChecked(true);

}
void MainWindow::setRadData( )
{	
	 
// 	 if (radSource == radEnea)
// 	 r->radioEnea->setChecked(true);
// 	 if (radSource == radCustom)
// 	 r->radioCustom->setChecked(true);
	if (sourceRadSettings->exec()) {
		if (sourceRadSettings->radioEnea->isChecked()){
// 			qDebug()<<"radioEnea is Checked"<<sourceRadSettings->radioEnea->isChecked();
			localita.source = radEnea;
                        italiaData->setTitle(tr("Database Coordinate - ENEA"));
		}
		if (sourceRadSettings->radioCustom->isChecked()){
			
			localita.source = radCustom;
                        italiaData->setTitle(tr("Database Coordinate - ENEA"));
// 			qDebug()<<"radioCustom is Checked"<<sourceRadSettings->radioCustom->isChecked()<<"localita.source"<<localita.source;
			QPolygonF temp(sourceRadSettings->getCustomHg());
			if (temp.size()>0)
				customHg = temp;
			else
			    resetCustomHg();
		}

                if (sourceRadSettings->radioNasa->isChecked()) {
			localita.source = radNasa;
                        italiaData->setTitle(tr("Database Coordinate - ENEA"));
                    }
                if (sourceRadSettings->radioUNI->isChecked()){
                        localita.source = radUNI;
                        italiaData->setTitle(tr("Database Coordinate - UNI"));
                    }
		if (sourceRadSettings->radioKWh->isChecked() ) 
			localita.radUnit = kwh;
		else
			localita.radUnit = megajoule;

	if (sourceRadSettings->isDirty()) {
                initializeModel();
		statusLabel->setText(tr("Sorgente: ") + source.at(localita.source));

                if (!locValue->text().isEmpty()){
                    qDebug()<<"SETRAD GO................."<<googleNameAvailable;
                    //GIUGNO 2010
                    updateLat();

                    set();
            }
		sourceRadSettings->setDirty( false);	
		}
	}
	
}

void MainWindow::addPV()
{
	AddPv form(this);
	form.setConnId(databasePanelsId);
	if (form.exec()) {
		if (datiPanels)
			datiPanels->refreshView();
		if (datiInverter)
			datiInverter->refreshView();
	 
	}
}
void MainWindow::selectInv()
{
if (datiInverter)
	datiInverter->refreshView();
		if (datiInverter->exec()) {
		thisProjectInverter = datiInverter->getSelectedInverter();
   qDebug()<<"selecInv:"<<thisProjectInverter.isValid<<thisProjectInverter.eff<<thisProjectInverter.pnom<<thisProjectInverter.indexDB;
		if (thisProjectInverter.isValid){
			#ifdef PLUSVERSION
                         if (inverterCheck!=0)
				inverterCheck->setInverter(thisProjectInverter);
			#endif
                         updatePower(0);
			 }
		}
	updateComponentStatus();

}
void MainWindow::selectPV()
{
        if (datiPanels!=0)
		datiPanels->refreshView();
		if (datiPanels->exec()) {
		

  #ifdef DEBUG
	qDebug()<<"selecPV:"<<thisProjectPanel.isValid<<thisProjectPanel.eff<<thisProjectPanel.pnom<<thisProjectPanel.indexDB;
  #endif
                if (datiPanels->getSelectedPanel().isValid){
                        thisProjectPanel = datiPanels->getSelectedPanel();
                        qDebug()<<"MW select panel"<<thisProjectPanel.indexDB<<thisProjectPanel.fabric<<thisProjectPanel.isValid;
                        if (energyOut!=0)
				energyOut->setPanel(thisProjectPanel);
			
                        if (areaValue!=0)
                                changeNumPanels(areaValue->value());
                        if (areaValue2!=0)
                                changeNumPanels2(areaValue2->value());
                        updatePower(0);
		}
		
		initializeModel();	 
		}
	updateLimitDistance();
	updateComponentStatus();
	
}
//double MainWindow::wattUnit()
//{
//	double factor;
//
//	if (wattCombo->currentIndex()>0)
//            factor = 3.6;
//        else
//            factor =1;
//
//	return factor;
//}
void MainWindow::exportDaily()
{
	QString m;
	if (validForExport){
		QString fileName = QFileDialog::getSaveFileName(this, tr("Esporta dati"),
                                 recentExportDaily,
                                tr("Text (*.txt *.dat *.rtf)"));
	QFileInfo fileInfo(fileName);
	QFile file(fileName);
	qDebug()<<fileInfo.path();
		if (!fileName.isEmpty() && file.open(QFile::WriteOnly)) {
		recentExportDaily = fileInfo.absoluteDir().absolutePath();
		 
		QTextStream out(&file);
		out.setFieldWidth(8);
		out.setFieldAlignment(QTextStream::AlignLeft);
		 
			if (reale->getDailyHinclOmbre().size()>0)
				out<<'\n';
				for(int i=0;i<MyMath::yearEnd(localita.anno);i++) {
				m = getMonthString(i);
				out<<m<<" "<<reale->getDailyHinclOmbre().at(i).x()<<reale->getDailyHinclOmbre().at(i).y()<<'\n';
				}
		
		}
	}
}

void MainWindow::exportData()
{
// 	double* ombre;
	QVector<double> ombre;
	double e,eTemp,eTemp2;
	ombre = w->getShadowFactor();
	



	if (validForExport) {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Esporta dati di energia"),
                                recentDirExport,
                                tr("Text (*.txt *.dat *.rtf)"));
	// Check the forma....TO DO
	QFile file(fileName);
	QFileInfo fileInfo(file);
	if (!fileName.isEmpty() && file.open(QFile::WriteOnly)) {
		recentDirExport = fileInfo.absoluteDir().absolutePath();
		QTextStream out(&file);
		out.setFieldWidth(15);
		out.setFieldAlignment(QTextStream::AlignLeft);
		/*Start preamble*/
		printPreamble(out);
		
		/*QString a(tr("Mese") + "\t" +tr("Rad.Reale") +"\t"+ tr("Rb")+"\t"+tr("Ombre")+ "\t"+tr("Energia-mensile")+"\n");
	out<<tr("Mese")<<'\t'<<tr("Rad.Reale")<<'\t'<<tr("Rb")<<'\t'<<tr("Ombre")<<'\n'*/
;
		out <<'\n'<<tr("Mese")
			<<tr("Rad.Reale");
			
		if (localita.tipo==2){
			out<<tr("Rb falda1 ")
			<<tr("Rb falda2 ")
			<< tr("Fattore-Ombra 1 ")
			<< tr("Fattore-Ombra 2 ")
			<<tr("Fattore-temp. 1 ")
			<<tr("Fattore-temp. 2 ");
		}
		else
		{
			out<<tr("Rb falda ")
			<< tr("Fattore-Ombra");
		}
			
			out<<tr("Energia-mensile")<<'\n';		

		for(int i=0;i<12;i++) {
// 		QString str;
// 		str = QString("%1 \t %2 \t %3 \t %4 \n").arg(i+1).arg(HinclOmbre[i]).arg(Rb[i]).arg(ombre[i]);
// 		out<<str;
		#ifdef DEBUG
		qDebug()<<"MainWindow: energyPlotPresent"<<energyPlotPresent<<energyOut->getStatus(1);
		#endif
 		if (energyPlotPresent)  {
			e = Energy[i];
			eTemp = effTemp.at(i);
			if (localita.tipo ==2)
				eTemp2 = effTemp.at(i);
		}
			
		else
		{
			e = 0;
			eTemp =0;
		}
		
			out <<i+1
			   <<HinclOmbre[i];
		if (localita.tipo==1){
			   out<<RbBiAx[i];
			   out<<ombre[i];
			   out<<eTemp;
		}
		if  (localita.tipo==0){
			   out<<Rb[i];
			   out<<ombre[i];
		           out<<eTemp;
		}
		if (localita.tipo==2){
			   out<<Rb[i]<<addOmegaRb.at(i);
			   out<<ombre[i]<<addOmbre.at(i);/*It is only one more facade!*/
			   out<<eTemp<<eTemp2;
		}
			   
			   out<<e<<'\n';
// 		qDebug()<<"MW RB"<<Rb[i];
		}
	}
}	
}
void MainWindow::viewOpti( )
{/*
	if (isDirty) {*/
// 			o->compute();
// 			o->drawContents(1);
// 			isDirty = false;
// // 	 	 }

// 	tabWidget->setCurrentIndex(1);
 	if (!optiWidget->isVisible()) {
// 		 
 	optiWidget->show();
 	}
}
void MainWindow::viewMonthlyLoss()
{
	
	if (monthlyLoss) {
		if (monthlyLoss->exec())
		{

			if (monthlyLoss->isDirty())
			{
				double a;
                                otherLosses.otherLoss = monthlyLoss->getLosses();
                                updatePower(0);
				monthlyLoss->makeDirty(false);
				a = MyMath::mean(otherLosses.otherLoss);
				otherLoss->setText(QString::number(a));
				qDebug()<<"MW losses"<<a;
			}
		}
			
	}
}
void MainWindow::viewAlbedo()
{
	Albedo albedoTable;
	
	if (localita.albedoType==con){
		albedoTable.setAlbedo(localita.albedo);	
		}
	
		albedoTable.setAlbedoType(localita.albedoType);
	if (albedoTable.exec()) {
		
		localita.albedo = albedoTable.getAlbedo();
		localita.albedoType = albedoTable.getAlbedoModel();
                if (localita.albedoType !=con)
                    albedoValue->setEnabled(false);
                else{
                    albedoValue->setEnabled(true);
                    albedoValue->setValue(localita.albedo);
                }
		
		qDebug()<<"MW get ALbedo"<<localita.albedoType<<localita.albedo;
                updatePower(0);
}	}

void MainWindow::viewReale( )
{
	
// 	if (isDirty) {
// 			reale->compute();
//   			reale->drawContents(1);
//   			Hincl = reale->getHincl(Hincl);
// 			isDirty=false;
// // 	qDebug()<<"is dirty"<<isDirty;
//   		}
	tabWidget->setCurrentIndex(1);
// 	if (!realeWidget->isVisible()) {
//  		
// 	realeWidget->show();
// 	}
}
void MainWindow::viewEnergy()
{
    tabWidget->setCurrentIndex(2);
}

void MainWindow::readSettings()

{QSettings settings;
	 if (settings.contains("lang"))
            language = settings.value("lang").toInt();
         if (settings.contains("decimals"))
            numOfDec = settings.value("decimals").toInt();
         if (settings.contains("check"))
             checkAtStart = settings.value("check").toBool();
	qDebug()<<"Language readSettings="<<language;	

	qDebug()<<settings.value("pos").toString();
	QRect r;
	QDesktopWidget screen;
	r = screen.screenGeometry();	

	
        settings.beginGroup("mainWindow");

        resize(settings.value("size",QSize((int)ceil(r.width()/2),(int)ceil(r.height()/2))).toSize());
        move(settings.value("pos",QPoint(200,200)).toPoint());
	restoreGeometry(settings.value("geometry").toByteArray());
// 	toolBox->setMinimumWidth(settings.value("toolbox").toInt());
	recentFiles = settings.value("recentFiles").toStringList();
	settings.endGroup();
	
        settings.beginGroup("Proxy");
            if (settings.contains("proxy"))
                    proxyEnabled = settings.value("proxy").toBool();
            if (settings.contains("host"))
                    proxy.setHostName(settings.value("host").toString());
            if (settings.contains("user"))
                    proxy.setUser(settings.value("user").toString());
            if (settings.contains("password"))
                    proxy.setPassword(settings.value("password").toString());
            if (settings.contains("porta"))
                    proxy.setPort(settings.value("porta").toInt());
            if (settings.contains("type"))
                proxy.setType((QNetworkProxy::ProxyType)(settings.value("type").toInt()));



        settings.endGroup();

        settings.beginGroup("Dirs");
            if (settings.contains("energy"))
                recentDirHE = settings.value("energy").toString();
            qDebug()<<"MW energyread"<< recentDirHE;
        settings.endGroup();

        settings.beginGroup("database");

	if (settings.contains("databaseName")) {
            qDebug()<<"MW readingSettings contain database"<<settings.contains("databaseName");
		if (!settings.value("databaseName").toString().isEmpty()){
			convertionDone = true;

			databaseEntry = settings.value("databaseName").toString();
			
		} else  
			convertionDone = false;
			

			
	} else 	 
			convertionDone = false;
			
	if (settings.contains("databasePanels")) {
           qDebug()<<"MW readingSettings contain databasePanels"<<settings.contains("databasePanels");
		if (!settings.value("databasePanels").toString().isEmpty()) {
			panelsLoaded = true;
			databasePanels = settings.value("databasePanels").toString();
		} else
			panelsLoaded = false;
	} else
			panelsLoaded = false;
	 
	
	settings.endGroup();

        if (support!=0)
            support->setProxy(proxy);
        ch->setUpdateAtStart(checkAtStart);
		
	 
}

void MainWindow::writeSettings()
{
	
        QSettings settings;
        settings.beginGroup("Proxy");
            settings.setValue("proxy",proxyEnabled);
            settings.setValue("host",proxy.hostName());
            settings.setValue("user",proxy.user());
            settings.setValue("password",proxy.password());
            settings.setValue("porta",proxy.port());
            settings.setValue("type",proxy.type());
        settings.endGroup();

        settings.beginGroup("Dirs");
            settings.setValue("energy",recentDirHE);
qDebug()<<"MW RECENTDIRHE"<<recentDirHE;
        settings.endGroup();

	settings.setValue("lang",language);
        settings.setValue("decimals",numOfDec);
        settings.setValue("check",checkAtStart);
	settings.beginGroup("mainWindow");
        settings.setValue("pos",pos());
        settings.setValue("size",size());
        settings.setValue("geometry",  saveGeometry());
	settings.setValue("recentFiles",recentFiles);
// 	settings.setValue("toolBox",toolBox->width());
	

  	
    	 
	if (convertionDone) {
		settings.beginGroup("database");
		settings.setValue("databaseName",databaseEntry);
		settings.endGroup();
	}

	 
	
 

	
}
void MainWindow::setLang(int i)
{
	if (i>=0)
		language = i;
	else
		language = 0;	

}

void MainWindow::updateLatFromGoogle(double a,double b,QString& address)
        /* Called when the user changes the point on the map */
{
    qDebug()<<"I am going to call formatCoodinates"<<address<<QString::number(a,'f',15);
	/* We assume that google returns valid coordinates */
	localita.latGradi = MyMath::degree(a);
	localita.latMin   = MyMath::minute(a);
	localita.latSec   = MyMath::seconds(a);
	localita.lonGradi = MyMath::degree(b);
	localita.lonMin   = MyMath::minute(b);
	localita.lonSec   = MyMath::seconds(b);
	localita.name     = address;
	localita.lat      = a;
	localita.lon      = b;

        qDebug()<<"MW updateLtaFrom Google localita"<<localita.latGradi<<localita.latMin<<localita.latSec<<localita.lonGradi<<localita.lonMin<<localita.lonSec;
	formatCoordinates();
	updateComuneLabel(1);
	wrongCoordinates= false;
	googleNameAvailable = true;
	noNameAvailable = true;
	bothCoord = true;
        locValue->setText(address);
	comuneValue->setText(""); /* in general we suppose that there is no name in italian db */
// 	getCityFromCo(3); /* Here we try to find a city in the italian dataBase  */
        set(normal);
}
void MainWindow::updateLatFromLoc()
{
    if (support){
        localita.lat= localita.latGradi + localita.latMin/60.0 + localita.latSec/3600.0;
        localita.lon= localita.lonGradi + localita.lonMin/60.0 + localita.lonSec/3600.0;
        support->setCo(localita.lat,localita.lon);
//       qDebug()<<"MW update lat from loc"<<
//              localita.latGradi<<
//               localita.latMin<<
//             localita.latSec<<localita.lonSec<<
//              QString::number(localita.lat,'f',8)<<QString::number(localita.lon,'f',8);
    }
}

void MainWindow::updateLat()
{
// 	resetFlags();
	wrongCoordinates = true;
	noNameAvailable  = true;
	googleNameAvailable = false;
	googleError = true;
	onlyLat = false;
	bothCoord = false;
	QStringList s,co,coDecimal,coDecimal1,coDecimal2;
	QString sNum,sNum2,sNum1;
	bool  ok, ok1, ok2;
	int numCo;
	 


	if (!locValue->text().isEmpty() & (!locValue->text().isNull())) {
		// CONTROLLO SE HO INSERITO DEI NUMERI
		 	
                s = locValue->text().simplified().split(" ");
				
				#ifdef DEBUG
				qDebug()<<"size della stringa ="<<s.size();
				#endif
				if (s.size()==1) {
					
					coDecimal = s.at(0).split('/');
					sNum = s.at(0);
					sNum.remove(QChar('/'),Qt::CaseInsensitive);
					double  r = sNum.toDouble(&ok);
					#ifdef DEBUG
					qDebug()<<"Nome ? ="<< ok<<r<<sNum;
					#endif
					//PRIMO CASO: solo coordinate
					if (ok) {
						onlyLat = true;
						bothCoord = false;
						/*Decimal coord. inserted?*/
						if (coDecimal.size()==1)
						{
							convertToDegree(r,0);
							localita.lat = r;
							localita.lon = 0;
							
							getCityFromCo(1);
//							toFade();
                                                        if (support)
                                                        {

		 						 support->setCo(r,0);
                                                             }
                                                    }
						else
						{
						/* GG MM SS coord.*/
						// Estraggo latitudine
						#ifdef DEBUG
						qDebug()<<"SOLO LATITUDINE";
						#endif
						numCo =checkLat(0,s);
						getCityFromCo(numCo);//solo lat
//						toFade();
						
                                                if (support && !doNotSetCity){

                                                support->setCity(locValue->text());
                                                }
						
						}
						
					} else {
						// HO inserito un nome
						
						getCity();
//						toFade();
						onlyLat = false;
						bothCoord = false;
                                                if (support && !doNotSetCity)
                                                {

                                                support->setCity(locValue->text());
                                                }
						}
				}
				// LAT LON - suppose that there are numbers
				if (s.size()==2) {

					coDecimal1 = s.at(0).split("/");
					coDecimal2 = s.at(1).split("/");

					sNum1 = s.at(0);
					sNum2 = s.at(1);
					sNum1.remove(QChar('/'),Qt::CaseInsensitive);
					sNum2.remove(QChar('/'),Qt::CaseInsensitive);
					double r1 = sNum1.toDouble(&ok1);
					double r2 = sNum2.toDouble(&ok2);
					#ifdef DEBUG
					qDebug()<<"Check lat lon:are numbers?"<<r1<<r2<<(ok1)<<(ok2)<<coDecimal1.size()<<coDecimal2.size();
					#endif
					if (ok1 && ok2) {
						onlyLat   = false;
						bothCoord = true;
						// inputs are numbers		
							if (coDecimal1.size()==1 && coDecimal2.size()==1)
							/* Decimal coordinates */		
							{
								convertToDegree(r1,r2);
								localita.lat = r1;
								localita.lon = r2;
								getCityFromCo(3);						
//								toFade();
		
								if (support)
                                                                {

		 						 support->setCo(r1,r2);
                                                             }
							}
							else
							{
								
								numCo = checkLat(0,s);
								numCo +=checkLat(1,s);
								#ifdef DEBUG
								qDebug()<<"NumCo"<<numCo;
								#endif
								getCityFromCo(numCo);
//								toFade();
								if (support)
                                                                {

		 						 support->setCo(localita.lat,localita.lon);
                                                             }
								
							}
					} 
					else
						{
						/* Text inserted */
						getCity();
//
						onlyLat = false;
						bothCoord = false;
						wrongCoordinates=true;
                                                if (support && !doNotSetCity)
                                                {

                                                support->setCity(locValue->text());
                                                }
						}
				}
			
                                // In all other case try google
                                if (s.size()>2)
                                    if (support!=0 && !doNotSetCity)
                                    {

                                    support->setCity(locValue->text());

                                    }
	 
		 #ifdef DEBUG
		qDebug()<<"UpdateLat"<<localita.lat<<wrongCoordinates<<"latGradi="<<localita.latGradi<<"latMin="<<localita.latMin<<"latSec="<<localita.latSec;
		#endif
	} else {
		 
		comuneValue->setText("");
		updateComuneLabel(0);
		getCity();
//		toFade();
		wrongCoordinates = true;
		#ifdef DEBUG
		qDebug()<<"I am here, testo vuoto"<<locValue->text();
		#endif
	}
        toFade();

formatCoordinates();	
}

int MainWindow::checkLat(int mode,const QStringList &s)
{
	/* Check coordinates in GG MM SS*/
	QStringList co; 	
	 
	 
		
	if (mode==0) {
	// UPDATE LAT
	co = s.at(0).split("/");
	#ifdef DEBUG
	qDebug()<<"cerca split.size()="<<co.size();
	#endif
						// SOLO GRADI 
						if (co.size()==1) {
                                                        localita.latGradi = co.at(0).toDouble();
							
							localita.latMin = 0;
							localita.latSec = 0;
							convertLat(localita);
							wrongCoordinates = true;
							#ifdef DEBUG
							qDebug()<<"check lat, solo gradi"<<localita.latGradi<<co.at(0);
							#endif
						}
						// SOLO GRADI-MIN
						if (co.size()==2) {
                                                        localita.latGradi = co.at(0).toDouble();
                                                        localita.latMin   = co.at(1).toDouble();
							localita.latSec = 0;
							convertLat(localita);
							wrongCoordinates = true;
							#ifdef DEBUG
							qDebug()<<"check lat, solo gradi e min"<<localita.latGradi<<localita.latMin<<localita.latSec<<localita.lat;
							#endif
						}
						// GRADI-MIN-SEC
						if (co.size()==3) {
                                                        localita.latGradi = co.at(0).toDouble();
                                                        localita.latMin   = co.at(1).toDouble();
                                                        localita.latSec   = co.at(2).toDouble();
							convertLat(localita);
							wrongCoordinates = false;
							#ifdef DEBUG
							qDebug()<<"check lat, gradi e min,sec"<<localita.latGradi<<localita.latMin<<localita.latSec<<localita.lat; 
							#endif
						}
						if (co.size()>3)
							wrongCoordinates = true;
	}
	if (mode==1) {
	// UPDATE LON
	co = s.at(1).split("/");
						// SOLO GRADI 
						if (co.size()==1) {
                                                        localita.lonGradi = co.at(0).toDouble();
							localita.lon = localita.lonGradi;
							wrongCoordinates = true;
						}
						// SOLO GRADI-MIN
						if (co.size()==2) {
                                                        localita.lonGradi = co.at(0).toDouble();
                                                        localita.lonMin   = co.at(1).toDouble();
							localita.lon      = localita.lonGradi + localita.lonMin/60.0;
							wrongCoordinates = true;
						}
						// GRADI-MIN-SEC
						if (co.size()==3) {
                                                        localita.lonGradi = co.at(0).toDouble();
                                                        localita.lonMin   = co.at(1).toDouble();
                                                        localita.lonSec   = co.at(2).toDouble();
							localita.lon      = localita.lonGradi + localita.lonMin/60.0 + localita.lonSec/3600;
							wrongCoordinates = false;
						}
						if (co.size()>3)
							wrongCoordinates = true;	
	}

formatCoordinates();
return co.size();
}
QString MainWindow::getWhereUNI(int num)
{
    QString where;
    switch (num ){
    case 0:
        where = QString("WHERE ") + "latitug=" +
                QString::number(localita.latGradi) +" AND " +
                       "latitup=" + QString::number(localita.latMin)+ " AND " +
                       "longitug=" + QString::number(localita.lonGradi) + " AND " +
                       "longitup=" + QString::number(localita.lonMin);
        break;
    case 1:
        where = QString("WHERE ") + "latitug=" +
                QString::number(localita.latGradi);
    case 2:
        where = QString("WHERE") + "latitug=" +
                QString::number(localita.latGradi) +" AND " +
              QString("latitup=") + QString::number(localita.latMin);
        break;
    case 3:
        where = QString("WHERE ") + "latitug=" +
                QString::number(localita.latGradi) +" AND " +
              "latitup=" + QString::number(localita.latMin);

        break;

    }
    return where;
}

QString MainWindow::getWhereEnea(int num)
{
    QString where;
    switch (num ){
    case 0:
        where = QString("WHERE ") + "latitudine_g=" +
                QString::number(localita.latGradi) +" AND " +
                       "latitudine_m=" + QString::number(localita.latMin) +" AND " +
                       "latitudine_s=" + QString::number((int)(localita.latSec))   +" AND " +
                       "longitudine_g=" + QString::number(localita.lonGradi) + " AND " +
                       "longitudine_m=" + QString::number(localita.lonMin)+   " AND " +
                       "longitudine_s=" + QString::number((int)(localita.lonSec))  ;
        break;
    case 1:
        where = QString("WHERE ") + "latitudine_g=" +
                QString::number(localita.latGradi);
    case 2:
        where = QString("WHERE") + "latitudine_g=" +
                QString::number(localita.latGradi) +" AND " +
              QString("latitudine_m=") + QString::number(localita.latMin);
        break;
    case 3:
        where = QString("WHERE ") + "latitudine_g=" +
                QString::number(localita.latGradi) +" AND " +
              "latitudine_m=" + QString::number(localita.latMin) +" AND " +
              "latitudine_s=" + QString::number((int)(localita.latSec));

        break;

    }
    return where;
}

void MainWindow::getCityFromCo(int numCo)
{
	QSqlDatabase d = QSqlDatabase::database();
	QString where;

	if (convertionDone) 
	{
		 
		if ((!wrongCoordinates) && (bothCoord) ){
                          if (localita.source == radEnea)
                          where = getWhereEnea(0);
                          if (localita.source == radUNI)
                          where = getWhereUNI(0);

		} else {
		// Forse ci sono solo coordinate incomplete. Provo a elencare le citta che si avvicinano
                        if (localita.source == radEnea)
                        where = getWhereEnea(numCo);
                        if (localita.source == radUNI)
                        where = getWhereUNI(numCo);

		}
                        if (localita.source == radEnea)
			modelRadiazione->setQuery("SELECT * FROM radiazione  " + where);
                        if (localita.source == radUNI)
                        modelRadiazione->setQuery("SELECT * FROM uni  " + where);

                        #ifdef DEBUG
			qDebug()<<"GetCityFRomCo wronCo="<<wrongCoordinates<<onlyLat<<modelRadiazione->lastError()<<modelRadiazione->query().executedQuery()<<where;
                       #endif

			if (modelRadiazione->rowCount()==1) {
					noNameAvailable = false;
					updateFromModel(0);  
					updateComuneLabel(1);
					comuneValue->setText(modelRadiazione->record(0).value("nome").toString());
					
					
			} else {
							noNameAvailable = true;
							comuneValue->setText("");
							//IL diagramma solare si puo' fare comunque
							//set();
                                                        showItalia = false;
							updateComuneLabel(1);
							
			}	

		
	}
}
 

void MainWindow::getCity()
{
       #ifdef DEBUG
    	qDebug()<<"Sto cercando...";
        #endif
	int count;


	QSqlDatabase d = QSqlDatabase::database();
        QString n = locValue->text().simplified();
	QStringList list = n.split(",");
        QString name,temp;
        name = list.at(0).simplified();
	name.replace("'","''");

	// Get the coordinates from the name of the city, if possible
	if (convertionDone) 
	{
		//Find the city; TO DO check on the values
		

                if (localita.source == radUNI)
                modelRadiazione->setQuery("SELECT * FROM uni WHERE comune LIKE '%" + name + "%'");
                else
                    modelRadiazione->setQuery("SELECT * FROM radiazione WHERE nome LIKE '%" + name + "%'");


                count = modelRadiazione->rowCount();
              //  qDebug()<<"Results in getCity"<<modelRadiazione->lastError()<<modelRadiazione->query().executedQuery()<<count;
		// Se ci sono comuni omonimi ? TO DO

 		if (count>1) {
				
			 
                         #ifdef DEBUG
			qDebug()<<"Some results in getCity"<<modelRadiazione->lastError()<<modelRadiazione->query().executedQuery()<<(modelRadiazione->record(0).value("latitudine_g").toInt())<<count;	
                         #endif

			//updateFromModel(0);
  		 	//updateComuneLabel(1);
			// We must choose one city, therefore a null city is a wrong city
			showItalia = true;
			noNameAvailable = true;
			wrongCoordinates = true;
			onlyLat = false;
  			comuneValue->setText("");
			/* If there is a match in the italian database, there is also in google maybe*/
                        if (support && !doNotSetCity){

                                support->setCity(locValue->text()  );
                            }
		
		} else {
				if (count==0) {
				// Non ho trovato la ocalita
					showItalia = false;
					noNameAvailable = true;	
					wrongCoordinates = true;
					onlyLat = false;
					updateComuneLabel(0);				
                                         #ifdef DEBUG
					qDebug()<<"MW GETCITY No results in getCity"<<modelRadiazione->lastError()<<modelRadiazione->query().executedQuery()<<count;
                                         #endif
					comuneValue->setText("");
                                        if (support && !doNotSetCity)
                                        {

                                         support->setCity(locValue->text());

                                        }
				}
			
                        if (count==1) {
				// HO trovato la localita posso disegnare
				/* Check if there is an exact match*/
				
                        if (localita.source == radEnea)
                        temp = modelRadiazione->record(0).value("nome").toString().simplified();
                        if (localita.source == radUNI)
                        temp = modelRadiazione->record(0).value("comune").toString().simplified();

                        if (temp.compare(name, Qt::CaseInsensitive)==0)
					{
					noNameAvailable = false;
					updateFromModel(0);
					updateComuneLabel(1);
                                          #ifdef DEBUG
					qDebug()<<"Un risultato in getCity"<<modelRadiazione->record(0).value("latitudine_g").toString()<<temp<<name<<normalize(name);
                                         #endif
					comuneValue->setText(modelRadiazione->record(0).value("nome").toString());
					 
					}
					else
					{
					/* We must select the result found to confirm */
                                        showItalia      = true;
					noNameAvailable = true;
					wrongCoordinates = true;
					onlyLat = false;
					comuneValue->setText("");
                                         #ifdef DEBUG
					qDebug()<<"No exact matching in getCity"<<temp<<name<<normalize(name);
                                         #endif
					 
					}
                                        if (support && !doNotSetCity)
		 				 support->setCity(locValue->text() + ", It");
				}
		 
	 
			} 
	 } else  {
		 noNameAvailable = true;
		 }

 
}
bool MainWindow::confirmErase(const QString &c)
{
	QSqlDatabase d = QSqlDatabase::database();
	int r = QMessageBox::question(this,tr("Nuovo database"),tr("Cancello il database precedente?"),QMessageBox::Ok,QMessageBox::Cancel);
		if (r==QMessageBox::Ok) {
				QSqlQuery q(d);
				q.prepare("DELETE FROM " + c);
				
				q.exec();
				#ifdef DEBUG
				qDebug()<<"Erase="<<q.lastError();
				#endif
				return true;
		} else {
				return false;
		}
}
		
//  void MainWindow::setFiltro()
// {   
// 	QString filtro = comuneValue->text();
// 	QRegExp regExp(filtro, Qt::CaseInsensitive,QRegExp::PatternSyntax(QRegExp::FixedString));
//         proxyModel->setFilterRegExp(regExp);
// 
// }
void MainWindow::updateCity(const QModelIndex & m)
{
	QModelIndex source;
	if (m.isValid())
	{
		source =proxyModel->mapToSource(m);
		
		int i = (source.row());//id of the selected city
		// Aggiorno la localita
 		updateFromModel(i);
		
		noNameAvailable = false;
		
		
		updateComuneLabel(1);
                //#ifdef DEBUG
		qDebug()<<"UpdateCity"<<localita.lat<<wrongCoordinates<<"latGradi="<<localita.latGradi<<"latMin="<<localita.latMin<<"latSec="<<localita.latSec<<localita.name<<i;
                //#endif
		wrongCoordinates = false;	
		comuneValue->setText(localita.name);
		/* Since I select from the italian database, tell Google to search in Italy*/
                if (support && !doNotSetCity){
                           qDebug()<<"MW updateCity---,support->setCity"<<localita.name;
			support->setCity(localita.name + ", It"); 
                    }

                set(normal);
		
	}
	else {
		
		noNameAvailable = true;
		wrongCoordinates = false;
	     }
	
}
void MainWindow::suggestMinMax()
{

//Suggest min max temp values //
if (!minTempIsEdited){
    tempMinValue->setValue(MyMath::min(tempDaily));
    localita.tempMin = tempMinValue->value();
     minTempIsEdited = false;
}
if (!maxTempIsEdited){
    tempMaxValue->setValue(MyMath::max(tempDaily));

    localita.tempMax = tempMaxValue->value();
    maxTempIsEdited = false;
}
}
bool MainWindow::extractRadiazione(loc localita)
{
//bool n;
QString where;
nasaObject res;
       // qDebug()<<"Extract radiazione ..mode"<<localita.source;
/* We can also extract temperature and wind files if the user did not edit the temp. table*/

switch (localita.source) {
    // Se il nome non e' disponibile, la localita' non e' presente nell'archivio
    // e bisogna prendere due punti "vicini"
        case radUNI:
    // I dati UNI contengono solo le province
    // qDebug()<<"MW EXTRACT UNI "<<noNameAvailable<<localita.name;
             if (!noNameAvailable) {
                 where = "comune='" + localita.name+"'";
                 modelRadiazione->setQuery("SELECT * from uni WHERE " + where);
//                   qDebug()<<"Extract Num affected"
//                          <<modelRadiazione->rowCount()
//                         <<modelRadiazione->query().executedQuery()
//                          <<modelRadiazione->lastError();

                 if (modelRadiazione->rowCount()==1) {
                     QString     mg,vg;
                     QStringList mgl;
                     if (!doNotLoadTemp)
                        otherLosses.temperatures.resize(0);
                         for (int i=0;i<12;i++) {
                         mg  = modelRadiazione->record(0).value("irrad"+monthMem.at(i)).toString().simplified().trimmed();
                         mgl = mg.split(" ");
                         Hg[i] = mgl.last().toDouble();
                         mg  = modelRadiazione->record(0).value("tempmed"+monthMem.at(i)).toString();
                         vg  = modelRadiazione->record(0).value("velocvento").toString();


                         if (!doNotLoadTemp){
                            otherLosses.temperatures << mg.toDouble();
                       //  qDebug()<<"EXTRAC TEMP"<<otherLosses.temperatures<<modelRadiazione->record(0).value("tempmed"+monthMem.at(i)).toString();

                             }
                       }
                         if (!doNotLoadTemp)
                            tempDaily = otherLosses.temperatures;
                         /* UNI has only one value for the wind */
                         if (!doNotLoadWind)
                         {
                             otherLosses.wind.fill(vg.toDouble(),12);
                             windDaily.fill(vg.toDouble(),12);
                         }
                 updateStatusBar("Database","darkkhaki");
                 return true;
             }
             }
                 else {
                     /* In findNearUNI there is also the computation of temp*/
                     if (findNearUNI()) {
                         updateStatusBar(tr("Stimata"),"red");

                         estimatedCoordinates = true;
                         return true;
                     }
                     else
                         estimatedCoordinates = false;
                     updateStatusBar(tr("Dato mancante"),"red");
                     // 				 qDebug()<<"MW Extract returned "<<false;
                     return false;
                 }
             break;

	case radEnea:
	

              #ifdef DEBUG
		qDebug()<<"Extract Radiazione...noname?"<<noNameAvailable;
                 #endif
		if (!noNameAvailable) {
                         where = "reg=" + QString::number(localita.reg) +
					" AND prov=" + QString::number(localita.prov) +
					" AND comune=" + QString::number(localita.comune);
			modelRadiazione->setQuery("SELECT * from radiazione WHERE " + where);
			//12 mesi
                       //  #ifdef DEBUG
			qDebug()<<"Num affected"<<modelRadiazione->rowCount()<<modelRadiazione->query().executedQuery();
                       //  #endif
			
			if (modelRadiazione->rowCount()==1) {
				for (int i=0;i<12;i++) {
					Hg[i]=modelRadiazione->record(0).value(i+6).toDouble();
					
  					#ifdef DEBUG
					qDebug()<<"Hg="<< Hg[i];
  					#endif
				}
// 			changeColor(*maxIrrHinclValue,"darkkhaki");
			updateStatusBar("Database","darkkhaki"); 
			return true; 
			
			} else 
				{ 	
					
				}
		} else {
			if (findNear()) {
				
				updateStatusBar(tr("Stimata"),"red"); 
				
				estimatedCoordinates = true;
				return true;
			}
			else
				estimatedCoordinates = false;
				updateStatusBar(tr("Dato mancante"),"red");
// 				 qDebug()<<"MW Extract returned "<<false;
				return false;
			}
		

	break;
	
	case radCustom:
		/* Controllo se e' stato caricato il databse custom */
		if (!radSourceLoaded()) {	
			QMessageBox::critical(this,tr("Errore Radiazione"),tr("Vuoi usare un database custom ma non lo hai caricato, oppure hai un file corrotto (dati non in 12 mesi). Prova prima a caricarlo"),QMessageBox::Ok);
			resetHg();
			return false;
			}
		/* Carico il database */
		qDebug()<<"Carico il database custom";
		for (int i=0;i<12;i++) 
			/* Convert all in Megajoule because routines use mj as base unit */
			if (localita.radUnit == kwh )
				Hg[i]=customHg.at(i).y()*3.6;
			else
				Hg[i]=customHg.at(i).y()*3.6;
		
		statusLabel->setText(tr("Sorgente") +"("+ QString::number(localita.radUnit)+"):"+sourceRadSettings->getSourceName());
		return true;
	break;

	case radNasa:
        /********EXTRAC METEO DATA**************************/


        /*
                       findNasaData(localita.lat,localita.lon,localita.latGradi,localita.latMin,localita.latSec,
                       localita.lonGradi,localita.lonMin,localita.lonSec,1);*/
             res  =
                    findNasaDataSQL(localita.lat,localita.lon,localita.latGradi,
                                    localita.latMin,localita.latSec,
                                    localita.lonGradi,localita.lonMin,
                                    localita.lonSec);
                       //Find Temp Data
            if (!tempDataIsEdited && !doNotLoadTemp)
            {
                        tempDaily = res.temp;
                        adjustVector(tempDaily);
            }


            if (!windDataIsEdited && !doNotLoadWind )
            {
                    windDaily = res.wind;
                    adjustVector(windDaily);
            qDebug()<<"MW NASA"<<minTempIsEdited<<maxTempIsEdited;
            }


//        if (!windDataIsEdited
//            && !doNotLoadWind
//             ){
//                       findNasaData(localita.lat,localita.lon,localita.latGradi,localita.latMin,localita.latSec,
//                       localita.lonGradi,localita.lonMin,localita.lonSec,2);
//                       //Find Temp Data
//
//                        adjustVector(windDaily);
//
//        }
        /************************************************/

        /************EXTRACT RAD******************/

		statusLabel->setText(tr("Sorgente: ") + source.at(localita.source));


                if (res.rad.size()>=12)
                {
                    /* Dati nasa in kwh/m2/day*/
                    for(int i=0;i<12;i++){
                        Hg[i] = 3.6 * res.rad.at(i);
                      qDebug()<<"MW extract:"<<i<<res.rad.at(i)<<Hg[i];
                    }
                    if (!res.status)
                        updateStatusBar("Stimata","red");
                    else
                        updateStatusBar("Database","darkkhaki");

                changeColor(*statusLabel,"darkkhaki");
// 		statusLabelWarning->setText(tr("Rad.: Database"));
// 		changeColor(*statusLabelWarning,"darkkhaki");

                return true;
		
		} 
		 else {
                        //qDebug()<<"MW extract NASA:"<<nasaData.size();
			statusLabelWarning->setText(tr("Rad.: Errore"));
			 
			changeColor(*statusLabel,"red"); 
			return false;
		}
	break;
		default:
			return false;
	}	
}

void MainWindow::resetHg()
{
	for (int i=0;i<12;i++)
		Hg[i] = 0;
}
void MainWindow::resetCustomHg()
{
	customHg.resize(0);
	for (int i=0;i<customHg.size();i++){
		customHg.append(QPointF(i,0));
		
	}
}
bool MainWindow::radSourceLoaded()
{
	/* ci servono dodici mesi*/
	if (customHg.size()==12)
		return true;
	else
		return false;
}
bool MainWindow::findNearUNI()
{
    double Hg1[12],Hg2[12];
    double    lat1,lat2,lat,lon;
    int condition = 1;
    QPolygonF region;
    QVector<int> index;
    QVector<double> t1,t2,v1,v2;
    QString es;


     modelExtract->setQuery("SELECT id,latitug,latitup,longitug,longitup FROM uni WHERE	abs(latitug-"+QString::number((int)(localita.latGradi)) + ")<2 AND abs(latitup-" + QString::number((int)(localita.latMin)) + ")<5 ");
     int rSize = modelExtract->rowCount();
     if (rSize==0)
             condition = -1;
if (condition>0){
    int k=0;
   // #ifdef DEBUG
    qDebug()<<"FINDNEAR"<<modelExtract->query().executedQuery()<<modelExtract->lastError();
   //  #endif
    // Get and convert coordinates of the point in the region
    while (k<rSize)
    {

            index<<modelExtract->record(k).value("id").toInt();

            lat = MyMath::convertCoFromDegree(modelExtract->record(k).value("latitug").toDouble(),
                    modelExtract->record(k).value("latitup").toDouble(),0.0);
            lon = MyMath::convertCoFromDegree(modelExtract->record(k).value("longitug").toDouble(),
                    modelExtract->record(k).value("longitup").toDouble(),0.0);
            region<<QPointF(lat*pi/180,lon*pi/180);
    k++;
    }
//    qDebug()<<"FINDNEAR UNI"<<modelExtract->query().executedQuery()<<modelExtract->lastError()<<index;
    /*Compute distance with arc circle for short distances*/
    /*http://en.wikipedia.org/wiki/Great-circle_distance*/
    /*http://en.wikipedia.org/wiki/Geographical_distance*/

    //First Point
    int firstId = MyMath::findPoint(localita,index,region,index.size());

    int indexOfFirstId = index.indexOf(firstId);
    index.remove(index.indexOf(firstId));

    if (firstId<0)
        condition = -1;

    int secondId = MyMath::findPoint(localita,index,region,index.size());

    if (secondId<0)
        condition = -1;

    modelRadiazione2->setQuery("SELECT * from uni WHERE id=" +
                               QString::number(firstId));
             //  qDebug()<<"MW FindNear()..."<<localita.lat<<localita.lon<<modelRadiazione2->query().executedQuery()<<modelRadiazione2->lastError();
              // qDebug()<<"First near city UNI"<<modelRadiazione2->record(0).value("comune").toString();
    lat1 = region.at(indexOfFirstId).x();
    /**********PRIMO PUNTO*****************/

    //Copio la radiazione
    for (int i=0;i<12;i++){
        es    = modelRadiazione2->record(0).
         value("irrad"+monthMem.at(i)).toString().simplified().trimmed();
        Hg1[i]= es.split(" ").last().toDouble();
    //Copio la temperatura
        es    = modelRadiazione2->record(0).
         value("tempmed"+monthMem.at(i)).toString().simplified().trimmed();
        t1 << es.toDouble();

    }
    //Copio il vento
        es    = modelRadiazione2->record(0).
         value("velocvento").toString().simplified().trimmed();
        v1.fill(es.toDouble(),12);
  /**********SECONDO PUNTO e RISULTATO INTERP.*****************/
    modelRadiazione2->setQuery("SELECT * from uni WHERE id=" + QString::number(secondId));


     //Copio la radiazione
    lat2 = region.at(index.indexOf(secondId)).x();
    if (!doNotLoadTemp)
     otherLosses.temperatures.resize(0);
    if (!doNotLoadWind)
     otherLosses.wind.resize(0);


    es    = modelRadiazione2->record(0).
         value("velocvento").toString().simplified().trimmed();
    v2.fill(es.toDouble(),12);
    for (int i=0;i<12;i++) {
            es    = modelRadiazione2->record(0).
                 value("irrad"+monthMem.at(i)).toString().simplified().trimmed();
            Hg2[i]= es.split(" ").last().toDouble();
            es    = modelRadiazione2->record(0).
             value("tempmed"+monthMem.at(i)).toString().simplified().trimmed();
            t2 << es.toDouble();
            Hg[i] = Hg1[i] + (pi/180*localita.lat-lat1)*(Hg2[i]-Hg1[i])*180/pi*(lat1-lat2);
            if (!doNotLoadTemp)
                otherLosses.temperatures << t1.at(i) + (pi/180*localita.lat-lat1)*(t2.at(i)-t1.at(i))*180/pi*(lat1-lat2);

            if (!doNotLoadWind)
                otherLosses.wind << v1.at(i) + (pi/180*localita.lat-lat1)*(v2.at(i)-v1.at(i))*180/pi*(lat1-lat2);
           ;

          #ifdef DEBUG
            qDebug()<<"Radiazione stimata ..."<<Hg[i]<<Hg1[i]<<Hg2[i]<<localita.lat<<lat1<<lat2<<firstId<<secondId;
           #endif
    }
//    qDebug()<<"MW findNearUNI temp"<<doNotLoadWind<<otherLosses.wind;
    tempDaily = otherLosses.temperatures;
    windDaily = otherLosses.wind;

}
if (condition>0)
        return true;
else
        return false;
}

bool MainWindow::findNear()
{
	double Hg1[12],Hg2[12];
        double    lat1,lat2,lat,lon;
	int condition = 1;
	QPolygonF region;
	QVector<int> index;
	 
	// Cerco due punti vicini alle coordinate date
	// Find a region

        modelExtract->setQuery("SELECT id,latitudine_g,latitudine_m,latitudine_s,longitudine_g,longitudine_m,longitudine_s FROM radiazione WHERE	abs(latitudine_g-"+QString::number(localita.latGradi) + ")<2 AND abs(latitudine_m-" + QString::number(localita.latMin) + ")<5 AND abs (latitudine_s-" + QString::number((int)(localita.latSec)) + ")<20");
	
	int rSize = modelExtract->rowCount();

	if (rSize==0)	
		condition = -1;
if (condition>0){
	int k=0;
	#ifdef DEBUG
  	qDebug()<<"FINDNEAR"<<modelExtract->query().executedQuery()<<modelExtract->lastError();	
	#endif
	// Get and convert coordinates of the point in the region
	while (k<rSize)
	{
		
		index<<modelExtract->record(k).value("id").toInt();
		 
                lat = MyMath::convertCoFromDegree(modelExtract->record(k).value("latitudine_g").toInt(),
			modelExtract->record(k).value("latitudine_m").toInt(),
			modelExtract->record(k).value("latitudine_s").toInt());
                lon = MyMath::convertCoFromDegree(modelExtract->record(k).value("longitudine_g").toInt(),
			modelExtract->record(k).value("longitudine_m").toInt(),			modelExtract->record(k).value("longitudine_s").toInt());
		region<<QPointF(lat*pi/180,lon*pi/180);
	k++;
	}
	/*Compute distance with arc circle for short distances*/
	/*http://en.wikipedia.org/wiki/Great-circle_distance*/
	/*http://en.wikipedia.org/wiki/Geographical_distance*/

	//First Point
        int firstId = MyMath::findPoint(localita,index,region,rSize);
        int indexOfFirstId = index.indexOf(firstId);
//	double minDistance=9999999;
//	int firstId = index.at(0);
//	for (int i=0; i<rSize;i++) {
//		latMed = (pi/180*localita.lat+ region.at(i).x())/2;
//		distance = sqrt( pow( (pi/180*localita.lat-region.at(i).x()),2)
//		+ pow( cos(latMed)*(pi/180*localita.lon-region.at(i).y()) ,2));
//// 		qDebug()<<"DISTANCES "<<i<<distance<<index.at(i);
//		if (distance < minDistance) {
//			minDistance = distance;
//			firstId = index.at(i);
//			}
//	}
	#ifdef DEBUG
        qDebug()<<"First point "<<firstId<<index.indexOf(firstId)<<localita.lat<<localita.lon<<region.at(index.indexOf(firstId))<<
	MyMath::degree(region.at(firstId).x());
	qDebug()<<"First point "<<
	MyMath::minute(region.at(firstId).x());
	qDebug()<<"First point "<<
	MyMath::seconds(region.at(firstId).x());
	#endif

        if (firstId < 0)
		condition = -1;

	//Second point
        index.remove(index.indexOf(firstId));
        int secondId = MyMath::findPoint(localita,index,region,rSize);
//	minDistance = 9999999;
//	int secondId = index.at(0);
//	for (int i=0; i<rSize;i++) {
//
//		latMed = (pi/180*localita.lat+region.at(i).x())/2;
//		distance = sqrt(pow((pi/180*localita.lat-region.at(i).x()),2) + pow( cos(latMed)*(pi/180*localita.lon-region.at(i).y()) ,2));
//
//		if (distance < minDistance && i!=index.indexOf(firstId)) {
//			minDistance = distance;
//			secondId = index.at(i);
//			}
//	}
	#ifdef DEBUG
        qDebug()<<"Second point "<<secondId<<localita.lat<<localita.lon<<region.at(index.indexOf(secondId))<<modelExtract->record(index.indexOf(secondId)).value("nome").toString();
	#endif
        if (secondId < 0)
		condition = -1;

 
	
		modelRadiazione2->setQuery("SELECT * from radiazione WHERE id=" + QString::number(firstId));
               // qDebug()<<"MW FindNear()..."<<localita.lat<<localita.lon;
               // qDebug()<<"First near city "<<modelRadiazione2->record(0).value("nome").toString();
                lat1 = region.at(indexOfFirstId).x();
		//Copio la radiazione
                for (int i=0;i<12;i++){ Hg1[i]=modelRadiazione2->record(0).value(i+6).toDouble();

                }
 
	
		modelRadiazione2->setQuery("SELECT * from radiazione WHERE id=" + QString::number(secondId));
                //qDebug()<<"Second near city "<<modelRadiazione2->record(0).value("nome").toString();
		 //Copio la radiazione
		lat2 = region.at(index.indexOf(secondId)).x();
		for (int i=0;i<12;i++) {
			Hg2[i]=modelRadiazione2->record(0).value(i+6).toDouble();
			Hg[i] = Hg1[i] + (pi/180*localita.lat-lat1)*(Hg2[i]-Hg1[i])*180/pi*(lat1-lat2);
                        #ifdef DEBUG
			qDebug()<<"Radiazione stimata ..."<<Hg[i]<<Hg1[i]<<Hg2[i]<<localita.lat<<lat1<<lat2<<firstId<<secondId;
                        #endif
		}
}		
	if (condition>0)	
		return true;
	else
		return false;
 

}

//int MainWindow::goodCo(int g,int m,int s)
//{
//	if ((g>=-90 && g<=90)){
//
//		if ( (m>=0 && m<=60) && (s>=0 && s<=60) )
//			{
//// 			qDebug()<<"Good g m s"<<g<<m<<s;
//			return 3;}
//		else
//			if  ((m>=0 && m<=60))
//			{qDebug()<<"Good g m "<<g<<m<<s;
//			return 2;
//			}
//	}
//	else
//		{
//		qDebug()<<"Good g "<<g<<m<<s;
//		return 1;
//		}
//}
void MainWindow::convertLat(loc loca)
{
	
	localita.lat = loca.latGradi + (loca.latMin)/60.0 + (loca.latSec)/3600.0;
	localita.lon = loca.lonGradi + (loca.lonMin)/60.0 + (loca.lonSec)/3600.0;
        // #ifdef DEBUG
	qDebug()<<"lat convertita="<<localita.lat;
        // #endif
}

void MainWindow::updateComuneLabel(int reset)
{
	// Inserisco le coordinate
	if (reset==1) {
           //qDebug()<<"MW updateComunelabel"<<localita.latGradi<<localita.latMin<<localita.lonSec;
	comuneLat->setText(QString::number(localita.latGradi) +
                          "<sup>o</sup>" +
                          QString::number(localita.latMin)+  "'" +
                          QString::number(localita.latSec)+"''" + " (" +QString::number(localita.lat)+")"+ "<sup>o</sup>");

	comuneLatS->setText(QString::number(localita.lat)+"<sup>o</sup>");
        comuneLon->setText(QString::number(localita.lonGradi) +
                           "<sup>o</sup>" +
                           QString::number(localita.lonMin)+ "'" +
                           QString::number(localita.lonSec)+"''" + " (" + QString::number(localita.lon) +")"+ "<sup>o</sup>");

	comuneLonS->setText(QString::number(localita.lon) + "<sup>o</sup>");

	}
	else
	{
	comuneLat->setText("");
	comuneLatS->setText("");
	comuneLon->setText("");
	comuneLonS->setText("");
	}
}
void MainWindow::updateFromModel(int i)
{
//GET ONLY COORDINATES FROM dataUNIEneab database
    if (localita.source == radEnea || localita.source == radNasa){
	if (!modelRadiazione->record(i).isEmpty()){
			localita.latGradi =  (modelRadiazione->record(i).value("latitudine_g").toInt());
                        localita.latMin =  (modelRadiazione->record(i).value("latitudine_m").toDouble());
                        localita.latSec =  (modelRadiazione->record(i).value("latitudine_s").toDouble());
			localita.lonGradi =  (modelRadiazione->record(i).value("longitudine_g").toInt());
                        localita.lonMin = (modelRadiazione->record(i).value("longitudine_m").toDouble());
                        localita.lonSec = (modelRadiazione->record(i).value("longitudine_s").toDouble());
			localita.lat= localita.latGradi + localita.latMin/60.0 + localita.latSec/3600.0;
			localita.lon= localita.lonGradi + localita.lonMin/60.0 + localita.lonSec/3600.0;
	
			localita.reg = modelRadiazione->record(i).value("reg").toInt();
			localita.prov = modelRadiazione->record(i).value("prov").toInt();
 			localita.comune = modelRadiazione->record(i).value("comune").toInt();
	 
			localita.name =modelRadiazione->record(i).value("nome").toString();
//                          qDebug()<<"From model..."<<localita.lat<<localita.latMin<<localita.lonMin;
			formatCoordinates();

        localita.utc = (int)floor((localita.lonGradi+7.5)/15);
	}
    }
    else
    {
        if (!modelRadiazione->record(i).isEmpty()){

            localita.latGradi =  (modelRadiazione->record(i).value("latitug").toDouble());
            localita.latMin =  (modelRadiazione->record(i).value("latitup").toDouble());
            //qDebug()<<"MW UPDATE FROM UNI DATA............"<<localita.latGradi
                    //<<localita.latMin<<modelRadiazione->record(i).value("latitug").toString();
            localita.latSec =  0;
            localita.lonGradi =  (modelRadiazione->record(i).value("longitug").toDouble());
            localita.lonMin = (modelRadiazione->record(i).value("longitup").toDouble());
            localita.lonSec = 0;
            localita.lat= localita.latGradi + localita.latMin/60.0 + localita.latSec/3600.0;
            localita.lon= localita.lonGradi + localita.lonMin/60.0 + localita.lonSec/3600.0;

            localita.reg = 0;
            localita.sigla   = modelRadiazione->record(i).value("provsigla").toString();
            localita.comune  =0;

            localita.name =modelRadiazione->record(i).value("comune").toString().simplified();

            formatCoordinates();
        }
    }
}
void MainWindow::setNewCity(const QString &s )
{
	
	 
	localita.azi  = aziValue->value();
	localita.incl = inclValue->value();
	localita.anno = annoValue->value();
	localita.albedo = albedoValue->value();
	 if (!s.isEmpty())
		{
// 		qDebug()<<"MW setNewCity set()";
                set(normal);
		}
	 
}

void MainWindow::createSolarPlot()
{
int index;
                localita.utc = (int)floor((localita.lonGradi+7.5)/15);
		localita.alt = altitudeValue->value();
		w->toggleSpline(toggleSplineBox->checkState());

		
                w->setMonthlyTemp(tempDaily);
                w->setIncl(localita.incl);
		w->setUTC(localita.utc);
		w->setAlt(localita.alt);
		w->setAzi(localita.azi);
                /* Double facade?*/
                index = comboCurrentField->currentIndex() < 0 ? 0 :
                        comboCurrentField->currentIndex();
                 w->setCurrentSide(index);
                if (localita.tipo==2)
                    w->setAziIncl2(localita.additionalIncl.at(0),localita.additionalAzi.at(0));


		w->setLong(localita.lon);
		w->setLat(localita.lat);
		w->setYear(localita.anno);
	 	w->setIntegration(1);/* custom integration interval */
                w->setShadowCombineMode(localita.ombreModel);
                #ifdef DEBUG
                qDebug()<<"ombreMode in createsolar"<<localita.ombreModel;
                #endif
qDebug()<<"MW create solar PLOT "<<googleNameAvailable<<noNameAvailable<<googleError<<onlyLat<<localita.name;
	if ((!noNameAvailable) || googleNameAvailable && !googleError && !(onlyLat||bothCoord) ){

                if (localita.name.isEmpty())
                    w->setLocName(google.name);
                else
		w->setLocName(localita.name);
	}
	else
	   	w->setLocName(localita.coordinates);

  		w->compute();

		w->computeShadow();
                w->toggleSelfShadow(toggleSelfShadowBox->checkState());
  		w->drawMyContents(1);
	myplotpresent=true;
	
 }
void MainWindow::updateOptiLabels(int i)
{
		Hb       = o->getHb( );
		Hho      = o->getHho( );
		Hbh      = o->getHbh( );
		Rb       = o->getRb();
		RbBiAx   = o->getRbBiAx();
		omegaApp = o->getOmegaApp();
		omegaSco = o->getOmegaSco();
		omegasH  = o->getOmegasH();

		if (myplotpresent)
			localita.radDirettaAnnuaTotale= MyMath::cumSumMonthly(Hb,12);
		else
			localita.radDirettaAnnuaTotale= 0;

		if (!noRadiation){
		
		localita.radDirettaAnnuaMedia = MyMath::cumSum(Hb,12)/12;
		maxIrrHbValue->setText(QString("%L1").arg(localita.radDirettaAnnuaTotale));
		
		updateOptiLabel(i);
		}
      		#ifdef DEBUG		
		qDebug()<<"MW updateOptiLabels, lat ="<<localita.lat;
		qDebug()<<"Hb[gennaio]="<<Hb[0]<<"Ho[gennaio]="<<Hho[0]<<"Hbh[gennaio]="<<Hbh[0]<<"Rb[gennaio]="<<Rb[0];
      		#endif
// 		qDebug()<<"MainWindow:: updateOptiLabel"<<o->getUnit()<<Hb[0]<<localita.radDirettaAnnuaTotale;
}
void MainWindow::updateOptiLabel(int i )
{
	if (i<=2)
	{
//   	wattOptiLabel->setText((unit.at(i-1)));
	wattLabel2->setText((unit.at(i-1)));
	}
}	
void MainWindow::createOptimumPlot()
{
	
		o->setLat((localita.lat*pi/180));
		o->setAzi(localita.azi*pi/180);
		if (!noNameAvailable)
			o->setLocName(localita.name);
		else
 			o->setLocName(localita.coordinates);
                o->setIncl(localita.incl*pi/180);/* in radiants */
                o->compute(1,0); // 12 months available here, and also varTilt, i.e. the tilt values of trakers


                o->compute();  // 5 graphs here with different incl
		// Copy the results
		 
//  		o->getAll(*Hb,Hho,Hbh,Rb);
		

// 		qDebug()<<"CreateOptimumPlot...omegaApp[0]"<<omegaApp[0];		
		


	 	o->drawContents(1);
		updateOptiLabels(o->getUnit());

//		updateRadLabel(wattCombo->currentIndex(),maxIrrHbValue,localita.radDirettaAnnuaTotale);

		
}
// void MainWindow::stateChanged(int i)
// {
//     if (i){
//                 inclOptiValue->setEnabled(true);
//                 inclOptiValueOmbre->setEnabled(true);
// 		getOptiIncl();
//             }
//     else{
//         inclOptiValue->setEnabled(false);
//                 inclOptiValueOmbre->setEnabled(false);
//             }
// 
// }
// void MainWindow::getOptiIncl()
// {				
// 	 if (reale->hgIsPresent()) {
// // 				reale->setAll(Rb,Hg,Hho);
// 				reale->setLat(localita.lat);
// // 				reale->setYear(localita.year);
// // 				reale->setIncl(localita.incl);
// 				reale->setAzi(localita.azi);
// 				reale->setR(localita.albedo);
// 				reale->setOmbre(w->getShadowFactor());
// 				reale->setModel(localita.radCorrModel);//UNI
// // 				reale->setAll(Rb,Hg,Hho);
// 				reale->optimize(0);/*optimize without shadow*/
// 				inclOptiValue->setText(QString::number(reale->getBestIncl()));
// 				reale->optimize(1);/* optimize with shdawo*/
// 				inclOptiValueOmbre->setText(QString::number(reale->getBestIncl()));
// 
// 				gain = (noRadiation==false) ? MyMath::cumSumMonthly(reale->getHref(),12) : 0;
// 				gain = 100*(gain - localita.radRealeOmbreAnnuaTotale)/localita.radRealeOmbreAnnuaTotale;
// 				gainValue->setText(QString::number(gain)+" %");
// 	}
// }
double MainWindow::installedPower()
/* In kWp */
{
	int n2;
	int n = numPanels(localita.area);
	if (localita.additionalArea.size()>0)
	   n2 = numPanels(localita.additionalArea.at(0));
	else
		n2 = 0;
	return ((n+n2)* thisProjectPanel.pnom/1000);//in kWp
}
void MainWindow::createEnergyOutPlot()
	/*This function needs the vector HinclOmbre to work */
{
        double ip = installedPower();
	int n = numPanels(localita.area);
	int n2;
	if (localita.additionalArea.size()>0)
		n2 = numPanels(localita.additionalArea.at(0));
	else
		n2 = 0;
        qDebug()<<"MW ENERGYOUT---------AREA"<<localita.additionalArea;
        if (reale!=0 && o!=0){
            statusLabelPower->setText(tr("Pot.= ")+QString("%L1 kWp").arg(ip));
                energyOut->setInstalledPower(ip);
		energyOut->setThermalModel(otherLosses.thermalModel);
		energyOut->setYear(localita.anno);
// 		energyOut->setArea(localita.area);
		energyOut->setArea(n *thisProjectPanel.H * thisProjectPanel.L/1000000);
		energyOut->setAddArea(n2 *thisProjectPanel.H * thisProjectPanel.L/1000000);
		
                qDebug()<<"MW createEnergyOUt panel"<<thisProjectPanel.indexDB;
 		energyOut->setPanel(thisProjectPanel);

		energyOut->setInverter(thisProjectInverter);
		#ifdef PLUSVERSION
		if (inverterCheck)
			energyOut->setSystem(inverterCheck->getSystem());
		#endif
		energyOut->setOtherLoss(otherLosses.otherLoss);
 		energyOut->setTempMin(localita.tempMin);
 		energyOut->setTempMax(localita.tempMax);
  		energyOut->setTemp(tempDaily);
                energyOut->setMeanDayLen(o->getMeanDayLen());
		energyOut->setWind(windValue->value());
		energyOut->setWind(windDaily);
		energyOut->setMounting(mountingValue->currentIndex(),mountingHeightValue->value());
		energyOut->setConcRatio(localita.concRatio);
                energyOut->setH(HinclOmbre,HinclOmbre2,megajoule);//always rad is in MJ
		
		
                statusLabelEnergy->setText(energyOut->getStatus());/*this return a string*/
		
		energyOut->computeRealEnergy();
		energyOut->drawContents(1);
	
		energyOutUnit = energyOut->getUnit();
		effTemp   = energyOut->getEffTemp();
		effTemp2   = energyOut->getEffTemp2();

		otherLosses.thermalLosses = effTemp;
		Energy    = energyOut->getRealEnergy();
		totEnergy = energyOut->getTotEnergy();
		otherLosses.totalLossTemp = energyOut->getLossTemp();
		energyPlotPresent = energyOut->getStatus(1); /* this return a bool*/
		localita.starRatio = energyOut->starRatio();
                updateEnergyLabels(1);
         }
        else
            updateEnergyLabels(0);
	  
}
void MainWindow::updateEnergyLabels(int i)
{
    if(i==1)
    {
        pValue->setText(QString("%L1").arg(installedPower()));
        totEnValue->setText(QString("%L1").arg(totEnergy));
        tlossValue->setText(QString("%L1").arg(otherLosses.totalLossTemp));
        srValue->setText(QString("%L1").arg(localita.starRatio));
    }
    if (i==0)
    {
        pValue->setText("0");
        totEnValue->setText("0");
        tlossValue->setText("0");
        srValue->setText("0");
    }

}

QVector<double> MainWindow::computeAlbedo()
{
	QVector<double> a;
	double v,a1,a2;
        a1 = a2 = 0;
	/* Model from Jan Remund 2003*/
	if (localita.albedoType > con ){
	
		if (localita.albedoType==variable_low_snow)
			a1 = 0.423; a2 = 0.042;
		if (localita.albedoType==variable_high_snow)
			a1 = 0.618; a2 = 0.044;

			for(int i=0;i<tempDaily.size();i++){
				 v = a1 - a2*tempDaily.at(i);
				 v = (v-0.8)>=0.000000002 ?  0.8 : v;
				 v = (v-0.2)<=0.000000002 ?  0.2 : v;
				 a.append(v);
			}
	return a;
			
	}
	else
		return QVector<double>(1,0);
}
void MainWindow::createRealePlot()
{
	double gain;
 // Radiazione reale
		
			
// 		reale->setIncl(localita.incl);//in degree
		reale->resetOmbre();
		reale->setSource(localita.source);
		reale->setLat(localita.lat);
		reale->setAzi(localita.azi);
		if (localita.albedoType==con )
			reale->setR(QVector<double>(1,localita.albedo));
		if (localita.albedoType > con )
			reale->setR(computeAlbedo());
		 
		
		reale->setYear(localita.anno);
	if (!noNameAvailable)
		reale->setLocName(localita.name);
	else
		reale->setLocName(localita.coordinates);
		reale->setOmegas(omegasH);
		 
		/*Type of system, 1 is biaxial*/
		QPolygonF p;
		switch (localita.tipo){
		default:
		
// 			reale->setAll(Rb,Hho);
			
			p<<QPointF(0,localita.incl*pi/180);
			reale->setIncl(p);

		break;
		case 1:

			reale->setIncl(o->getVarTilt());// varTilt in radiants!/
		break;
		 
		}
		reale->setHg(Hg);
// 		double *tw = w->getShadowFactor();

// 		reale->setOmbre(tw);
		reale->setOmbre(w->getShadowFactor());
		otherLosses.shadows.resize(0);
		 
		/*Double facade?*/
		if (localita.additionalIncl.size()>0 && localita.additionalAzi.size()>0 && localita.tipo==2)
		{
			addOmbre.resize(0);
			addOmegaRb.resize(0);
			 
			reale->resetAdditionalOmbre();
			reale->addInclAzi(localita.additionalIncl,localita.additionalAzi);

			QVector<double> addOmega,addOmegaApp,addOmegaSco,addOmbre;
			for(int s=0;s<localita.additionalIncl.size();s++){
				for(int month=0;month<12;month++){
				addOmega = MyMath::rb(localita.lat*pi/180,localita.additionalIncl.at(s)*pi/180,localita.additionalAzi.at(s),month,localita.anno,0);
// 				addOmega  = MyMath::tiltedRiseSet(localita.additionalIncl.at(s)*pi/180,localita.additionalAzi.at(s)*pi/180,localita.lat *pi/180,month);
// 				
				addOmegaRb<< addOmega.at(0);
				addOmegaApp<< addOmega.at(5);
				addOmegaSco<< addOmega.at(4);
				}
			addOmbre = w->computeShadow(addOmegaApp,addOmegaSco);
 			#ifdef DEBUG
				qDebug()<<"MW double facade..............."<<addOmega<<localita.additionalIncl<<localita.additionalAzi<<addOmbre;
 				#endif 
			reale->addOmbre(addOmbre);
			}
		}

		reale->setModel(localita.radCorrModel);//UNI
	 
 		reale->compute();
		reale->fit();
// 		reale->convertFit();
		otherLosses.shadows = reale->getLossFactors();//In percent		

		/* Plot Ombre*/
		if (checkOmbre->isChecked()){
			reale->drawContents(2,comboCurrentField->currentIndex()+1);/*because Reale wants index from 1 to 2*/
// 			reale->drawDailyContents(2);
		}
		else{
			reale->drawContents(1,comboCurrentField->currentIndex()+1);
// 			reale->drawDailyContents(1);
		}
		
	       
	
		/* Plot daily fitted values */
// 		reale->drawDailyValue(1);
		

               
	
	
		updateRadLabels(reale->getUnit());
 
                                qDebug()<<"Ottimizzo...";

                                reale->optimize(0 );


                                    inclOptiValue->setText(QString::number(reale->getBestIncl()));


                                    reale->optimize(1 );/* optimize with shadow*/


				inclOptiValueOmbre->setText(QString::number(reale->getBestIncl()));
  				reale->computeRefCurve(1,reale->getBestIncl());
				gain = (noRadiation==false) ? MyMath::cumSumMonthly(reale->getHref(),12) : 0;
// 				qDebug()<<"Ottimizzo...end"<<gain;
				gain = 100*(gain - localita.radRealeOmbreAnnuaTotale)/localita.radRealeOmbreAnnuaTotale;
				if (fabs(gain)<0.0000002)
				gainValue->setText("0 %");
				else
				gainValue->setText(QString::number(gain)+" %");
	
//                                 }



		/* Calcolo anche su inseguitore BiAsse */
		
		
                
	 

// if (checkDaily->isChecked())
//	viewDailyRealePlot(Qt::Checked);
//else
//	reale->drawDailyContents(0);

otherLosses.totalShadowLossFactor= reale->getTotalShadowLossFactor();//This is a total yearly loss
otherLosses.meanShadowLossFactor= reale->getLossFactor();// this is the monthly mean of loss factor
		 
}
void MainWindow::drawHourlyValues(){
	//TEST: dati orari
	QPolygonF a,l;
	int m = selectMonth->currentIndex();
	int day = selectDay->currentIndex();
 
	computeHourlyValues(m+1,selectDay->currentIndex()+1);
        //otherLosses.scaling = checkScaling->isChecked();
        if ((selectMonth->currentIndex()<12)&&(!noRadiation)){
		hourlyPlot->setMode(otherLosses.scaling,HinclOmbre[m]);
		hourlyEOPlot->setMode(otherLosses.scaling,Energy[selectMonth->currentIndex()]/MyMath::monthEnd(m+1,localita.anno) );
               // qDebug()<<"MW drawHourly current index"<<selectDay->currentIndex()<<selectMonth->currentIndex()<<hourlyEO<<HinclOmbre[m]<<localita.tipo;
	}
		
	else
        {
                //qDebug()<<"MW problem setting the month in HOURLYPLOT"<<selectMonth->currentIndex()<<hourlyRR;
            }
	
	
	hourlyPlot->setHourlyData(hourlyRR);
	hourlyPlot->setTime(m+1,selectDay->currentIndex()+1);

	hourlyEOPlot->setHourlyData(hourlyEO);
	hourlyEOPlot->setTime(m+1,selectDay->currentIndex()+1);
	#ifdef PLUSVERSION
                if (loadInterface!=0){
			l = loadInterface->getHourlyLoads(localita.anno,day+1,m+1);
			hourlyEOPlot->setLoad(l);
			hourlyEOPlot->enableDrawingLoads(checkDrawLoads->isChecked());

		}
	#endif
	
	hourlyPlot->draw(1);
	hourlyEOPlot->draw(1);
}
void MainWindow::changeRealePlots(int state)
{
	/* change the plot between shaded or unshaded data */
// 	qDebug()<<"MW changeRealePlot"<<state;
// 	dailyValuesPresent = false;
	if (state==Qt::Checked) {
	 	reale->drawContents(2,comboCurrentField->currentIndex());
// 		if (checkDaily->isChecked())
// 			reale->drawDailyContents(2);
// 		else
			reale->drawDailyContents(0);
	}
	if (state==Qt::Unchecked){
		
		reale->drawContents(1,comboCurrentField->currentIndex());
// 		if (checkDaily->isChecked())
// 			reale->drawDailyContents(1);
// 		else
			reale->drawDailyContents(0);

	}
}
//void MainWindow::viewDailyRealePlot(int state)
//{
//	if (state==Qt::Checked) {
//		if (!reale->dailyIsDirty())
//			/* We have called compute() and computeDaily() in RR */
//			if (checkOmbre->isChecked())
//				reale->drawDailyContents(1);
//			else
//				reale->drawDailyContents(2);
//		else
//			/* Never generated */
//
//			createDailyRealePlot(Qt::Checked);
//	}
//	else
//		reale->drawDailyContents(0);
//
//}
//void MainWindow::createDailyRealePlot()
//{
//	createDailyRealePlot(checkDaily->checkState());
//}
//void MainWindow::createDailyRealePlot(int state)
//{
//if (checkDaily->isEnabled()) {
//	if (state==Qt::Checked) {
//		if (validForExport){
//			QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
//			/* WARNING this function must be called after createRealePlot() */
//			o->setYear(localita.anno);
//			o->computeDailyRad();
//			dailyValuesPresent = true;
//			/*Type of system, 1 is biaxial*/
//				if (localita.tipo==0){
//					QPolygonF p;
//					p<<QPointF(0,localita.incl*pi/180);
//					reale->setDailyIncl(p);
//					reale->setRbDaily(o->getRbDaily());
//				}
//				else{
//					reale->setDailyIncl(o->getVarTilt());
//					reale->setRbDaily(o->getRbBiAxDaily());
//				}
//				w->setDailyOmegaApp(o->getDailyOmegaApp());// o gives degree here*/
//					w->setDailyOmegaSco(o->getDailyOmegaSco());
//					w->setYear(localita.anno);
//					w->computeDaily();
//					reale->setOmbreFactorDaily(w->getDailyShadowFactor());
//					reale->setOmegasDaily(o->getOmegasHDaily());
//					reale->setHhoDaily(o->getHhoDaily());
//					reale->setYear(localita.anno);
//					reale->computeDaily();
//				if (checkOmbre->isChecked())
//					reale->drawDailyContents(2);	
//				else
//					reale->drawDailyContents(1);	
//				
//			QApplication::restoreOverrideCursor();		
//				
//				
//			}		
//	}
//	else
//		reale->drawDailyContents(0);
//}
//	else 
//		checkDaily->setEnabled(true);
//}
void MainWindow::updateRadLabels(int i )
{
	/* i is the unit */
	/* if mode==0 no rad is available */
	double* hToShow,*hOmbreToShow;
        double k = 1;

        Hincl              = reale->getHincl(1);
        HinclOmbre         = reale->getHinclOmbre(1);
        Hincl2             = reale->getHincl(2);
	HinclOmbre2	   = reale->getHinclOmbre(2);

	if (comboCurrentField->currentIndex()==1){
		hToShow = Hincl2;
		hOmbreToShow = HinclOmbre2;
	}
	else{
		hToShow = Hincl;
		hOmbreToShow = HinclOmbre;
	}

        if (i==kwh)
            k  = 1.0/3.6;

        
//        if (localita.additionalArea.size()>0)
//            localita.radRealeAnnuaDF = (noRadiation==false) ?
//                  k * (MyMath::cumSumMonthly(Hincl,12) +
//                  MyMath::cumSumMonthly(HinclOmbre2,12)) :0;

        localita.radRealeAnnuaTotale = (noRadiation==false) ? MyMath::cumSumMonthly(hToShow,12)*k : 0;
        localita.radRealeAnnuaMedia  = (noRadiation==false) ? MyMath::cumSum(hToShow,12)*k/12 : 0;
        localita.radRealeOmbreAnnuaTotale = (noRadiation==false) ? MyMath::cumSumMonthly(hOmbreToShow,12)*k : 0;
        localita.radRealeAnnuaOrizzontale = (noRadiation==false) ? MyMath::cumSumMonthly(Hg,12)/3.6 : 0; // This is always in kWh
      //  qDebug()<<"MW updateRadLabels"<< i<<k;

        /* Check for double facades */
        if (localita.additionalArea.size()>0)
            localita.radRealeAnnuaDF = (noRadiation==false) ?
                  k * (MyMath::cumSumMonthly(HinclOmbre,12) +
                  MyMath::cumSumMonthly(HinclOmbre2,12)) :0;
        else
            localita.radRealeAnnuaDF = localita.radDirettaAnnuaTotale;

        maxIrrHbValue->setText(QString("%L1").arg(localita.radDirettaAnnuaTotale*k));
        maxIrrHinclValue->setText(QString("%L1").arg(localita.radRealeAnnuaTotale));
        maxIrrHinclOmbreValue->setText(QString("%L1").arg(localita.radRealeOmbreAnnuaTotale ));
	meanIrrHinclValue->setText(QString("%L1").arg(localita.radRealeAnnuaMedia));
	

// 	if (checkDaily->isChecked())
// 			reale->drawDailyContents(1);
// 		else
// 			reale->drawDailyContents(0);
	
        updateRadLabel(i);

}
void MainWindow::updateRadLabel(int i)
{

        if (i<=2) {

//         wattLabel->setText(unit.at(i-1));
 	wattLabel2->setText(unit.at(i-1) );
// 	wattLabel3->setText(unit.at(i-1)+"/"+tr("giorno"));
        }


}
void MainWindow::changeColor( QLabel &s, const QString &color)
{	
	QPalette palette;
	palette.setColor(QPalette::Active,QPalette::Window,QColor(color));
		s.setPalette(palette);	
        //qDebug()<<"Colore.."<<s.palette()<<color;
}

void MainWindow::createTab()
{
    	/* ATTENTION :This function must be called after createInterface!!! */
	/* because we need tabWidget */
	
        myPlotWidget = new QWidget;
        QVBoxLayout *solarLayout = new QVBoxLayout;
        w = new MyPlot(myPlotWidget);

        w->setHSteps(1,23,0.2);
        w->setLong(13);
        w->setLat(42 + 10.0/60 + 0.0);
        w->setAlt(1);
        w->setUTC(1);
        w->setMode(0);//exact values
        w->setIntegration(integrationType);
        w->setRes(0);
        w->setYear(2009);
        connect(w,SIGNAL(ombreChanged()),this,SLOT(ombreChanged()));

	toggleSplineBox = new QCheckBox(tr("Interpolazione (grafica fine)"));
	toggleSelfShadowBox = new QCheckBox(tr("Visualizza variazione dell'alba-tramonto dovuta al tilt"));
	connect(toggleSplineBox,SIGNAL(stateChanged(int)),w,SLOT(toggleSpline(int)));
	connect(toggleSelfShadowBox,SIGNAL(stateChanged(int)),w,SLOT(toggleSelfShadow(int)));
	
        solarLayout->addWidget(w);
	solarLayout->addWidget(toggleSplineBox);
	solarLayout->addWidget(toggleSelfShadowBox);

//         updateButton = new QPushButton(tr("Aggiorna"));
//         connect(updateButton,SIGNAL(clicked()),SLOT(setDampOthers()));
//         solarLayout->addWidget(updateButton);
        myPlotWidget->setLayout(solarLayout);
        tabWidget->addTab(myPlotWidget,tr("Diagramma Solare"));

        optiWidget = new QWidget;
	optiWidget->setWindowIcon(QIcon(":/images/opti2.png"));
        QVBoxLayout *v = new QVBoxLayout;

        o = new OptimumPlot(optiWidget);
        o->setLat(localita.lat);
        o->setIncl(inclValue->text().toDouble());
        o->setAzi(aziValue->text().toDouble()*pi/180);
        aziValue->setValue(0);
	connect(o,SIGNAL(unitChanged(int)),SLOT(updateOptiLabels(int)));

        v->addWidget(o);
        optiWidget->setLayout(v);
//         tabWidget->addTab(optiWidget,tr("Radiazione e tilt"));

	QTabWidget* innerTab   = new QTabWidget;
	hourlyPlot 	       = new HourlyPlot(this);
	
	checkScaling           = new QCheckBox(tr("Abilita lo scaling automatico"));
	checkScaling->setToolTip(tr("<p>Lo scaling moltiplica tutti i valori orari per un fattore tale che la somma oraria coincide con la media mensile giornaliera. Questo opzione va usata con cautela.</p>"));
	connect(checkScaling,SIGNAL(stateChanged(int)),SLOT(enableScaling(int)));
        checkScaling->setChecked(true);

        realeWidget = new QWidget;
        realeToolWidget = new QWidget;
        QGridLayout *vr = new QGridLayout;
	QVBoxLayout *vr2 = new QVBoxLayout;
// 	QHBoxLayout *hr2 = new QHBoxLayout;
        QGridLayout *gr  = new QGridLayout;
        reale = new RadiazioneReale(realeWidget);
	connect(wattLabel2,SIGNAL(clicked()),reale,SLOT(swapUnit()));
	connect(wattLabel2,SIGNAL(clicked()),o,SLOT(swapUnit()));
// 	connect(wattLabel3,SIGNAL(clicked()),reale,SLOT(swapUnit()));
// 	connect(wattLabel,SIGNAL(clicked()),reale,SLOT(swapUnit()));




// 	checkDaily = new QCheckBox(tr("Genera dati giornalieri"));
// 	checkDaily->setVisible(false); // Not very useful. Kept for future versions.
// 	checkDaily->setCheckState(Qt::Unchecked);
// 	checkDaily->setEnabled(false);

//	currentFieldLabel = new QLabel(tr("Falda corrente"));
        comboCurrentField = new QComboBox;
	comboCurrentField->addItem("1");
        connect(comboCurrentField,SIGNAL(currentIndexChanged(int)),SLOT(redrawSelfShadow(int)));
	connect(comboCurrentField,SIGNAL(currentIndexChanged(int)),SLOT(redrawReale(int)));
	

        checkOmbre = new QCheckBox(tr("Visualizza radiazione incidente senza ombre"));
	checkOmbre->setCheckState(Qt::Unchecked);
  	connect(checkOmbre,SIGNAL(stateChanged(int)),SLOT(changeRealePlots(int)));
//	connect(checkDaily,SIGNAL(stateChanged(int)),SLOT(viewDailyRealePlot(int)));
//	connect(reale,SIGNAL(computeDone()),SLOT(createDailyRealePlot()));
// 	connect(hourlyPlot,SIGNAL(unitChanged(int)),SLOT(),updateHourlyPlot
 
        vr->addWidget(reale,0,0,1,4);
 
 	vr->addWidget(checkOmbre,1,0,1,1);
// 	vr->addItem(QSpacerItem(20,10),1,1,1,1);
//	vr->addWidget(currentFieldLabel,1,2,1,1);
//	vr->addWidget(comboCurrentField,1,3,1,1);

        QGroupBox *group = new QGroupBox(tr("Tilt ottimo sistema fisso"));
	group->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"     background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                       stop: 0 #E0E0E0, stop: 1 #FFFFFF);\n"
"     border: 2px solid gray;\n"
"     border-radius: 5px;\n"
"     margin-top: 1ex;  \n"
" }\n"
"QGroupBox::title {\n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top left; /* position at the top center */\n"
"     padding: 0 1px;\n"
 
" }"));
	QGridLayout *gridGroup = new QGridLayout;
	
	tiltButton = new QPushButton(tr("Visualizza"));
	tiltButton->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed));
	tiltButton->setMinimumSize(QSize(100,tiltButton->minimumSizeHint().height()));
	
	connect(tiltButton,SIGNAL(clicked()),SLOT(drawRefCurve()));
	
//         gr->addWidget(inclOptiCheck,0,0,1,1);	
// 	QLabel *iol = new QLabel(tr("Tilt ottimo"));	
	gainLabel = new QLabel(tr("Guadagno"));
	gainLabel->setToolTip(tr("Guadagno del sistema fisso con tilt ottimo rispetto al sistema impostato"));
	gainValue = new QLabel("");
        
	gridGroup->addWidget(inclOptiLabel,0,0,1,1);
        gridGroup->addWidget(inclOptiValue,0,1,1,2);
	gridGroup->addWidget(tiltButton,0,3,1,1);
        gridGroup->addWidget(inclOptiOmbreLabel,1,0,1,1);
        gridGroup->addWidget(inclOptiValueOmbre,1,1,1,2);
	gridGroup->addWidget(gainLabel,1,3,1,1);
	gridGroup->addWidget(gainValue,1,4,1,1);
	gridGroup->setColumnStretch(5,3);
	group->setLayout(gridGroup);

        gr->addWidget(maxIrrHb,0,0,1,1);
        gr->addWidget(maxIrrHbValue,0,1,1,1);
// 	gr->addWidget(wattOptiLabel,0,2,1,1);
	gr->addWidget(maxIrrHincl,0,2,1,1);
        gr->addWidget(maxIrrHinclValue,0,3,1,1);
//         gr->addWidget(wattLabel,0,5,1,1);

        gr->addWidget(meanIrrHincl,1,0,1,1);
        gr->addWidget(meanIrrHinclValue,1,1,1,1);
//         gr->addWidget(wattLabel3,1,2,1,1);
        gr->addWidget(maxIrrHinclOmbre,1,2,1,1);
        gr->addWidget(maxIrrHinclOmbreValue,1,3,1,1);
        gr->addWidget(wattLabel2,1,4,1,1);
        realeToolWidget->setLayout(gr);
  	vr->addWidget(group,2,0,1,4);
         vr->addWidget(realeToolWidget,3,0,1,4);
        realeWidget->setLayout(vr);

// 	selectMonth = new QComboBox;
// 	QLabel *monthLabel  = new QLabel(tr("Mese"));
// 	QLabel *dayLabel    = new QLabel(tr("Giorno"));
// 	selectDay   = new QComboBox;
// 	
// 	selectMonth->addItems(MyMath::stringSerie(1,12));
// 	selectDay->addItems(MyMath::stringSerie(1,MyMath::monthEnd(1,localita.anno)));
// 	connect(selectMonth,SIGNAL(currentIndexChanged(int)),SLOT(changeDays(int)));
// 	connect(selectDay,SIGNAL(currentIndexChanged(int)),SLOT(dayChanged(int)));

   	vr2->addWidget(hourlyPlot);
	vr2->addWidget(checkScaling);
// 	hr2->addWidget(monthLabel);
// 	hr2->addWidget(selectMonth);
// 	hr2->addWidget(dayLabel);
// 	hr2->addWidget(selectDay);
// 	vr2->addLayout(hr2);
	
	QWidget* innerWidget = new QWidget;
	innerWidget->setLayout(vr2);
	
	innerTab->addTab(realeWidget,tr("Radiazione mensile"));
	innerTab->addTab(innerWidget,tr("Radiazione oraria"));

	
        tabWidget->addTab(innerTab,tr("Radiazione reale"));
        tabWidget->setTabIcon(1,QIcon(":/images/rr.png"));

        connect(reale,SIGNAL(unitChanged(int)),SLOT(updateRadLabels(int)));

        innerTabEO   = new QTabWidget;
	hourlyEOPlot 	         = new HourlyEnergyPlot(this);


	#ifdef PLUSVERSION
	
	 lv = new QVBoxLayout;
	QWidget* lvw    = new QWidget;
	checkDrawLoads =  new QCheckBox(tr("Visualizza carichi elettrici del mese corrente"));
	checkDrawLoads->setToolTip(tr("<p>Puoi cambiare i carichi elettrici dal menu Strumenti</p>"));
	connect(checkDrawLoads,SIGNAL(stateChanged(int)),SLOT(enableDrawingLoads()));

 	QWidget* energySummaryWidget = new QWidget;
	QScrollArea* stext = new QScrollArea;
	stext->setWidgetResizable(true);
	
 	energySummary		 = new QTextEdit;
	energySummary->setReadOnly(true);
	stext->setWidget(energySummary);
  	ves = new QVBoxLayout;
 	ves->addWidget(stext);
	energySummaryWidget->setLayout(ves);
	
	#endif
	energyWidget = new QWidget;
	QWidget *belowWidget = new QWidget;

	QGridLayout *ve = new QGridLayout;
	energyOut = new EnergyOut(energyWidget);
	connect(energyOut,SIGNAL(unitChanged()),SLOT(updateEnergyUnit()));
	
        //QHBoxLayout *he = new QHBoxLayout;

	
// 	QWidget* nn = new QWidget;


	
// 	connect(otherLoss,SIGNAL(editingFinished()),SLOT(updatePower()));
// 	he->addWidget(otherLossLabel);
// 	he->addWidget(otherLoss);
//	he->addWidget(pushMonthly);
//	belowWidget->setLayout(he);
	
        pushMonthly = new QPushButton(tr("Altre perdite mensili "));
        pushMonthly->setIcon(QIcon(":/images/edit.png"));
        monthlyLoss = new MagicTable;
        connect(pushMonthly,SIGNAL(clicked()),SLOT(viewMonthlyLoss()));
        QLabel *otherLossLabel = new QLabel;
        otherLossLabel->setStyleSheet(labelStyle);
        otherLossLabel->setText(tr("Perdite mensili (media)"));
        otherLoss = new QLabel;
        otherLoss->setText("0");
        otherLoss->setStyleSheet(labelStyle);
        QLabel* pLabel = new QLabel;
        pLabel->setText(tr("Potenza installata [kWp]"));
        pLabel->setStyleSheet(labelStyle);
        QLabel* eLabel = new QLabel;
        eLabel->setStyleSheet(labelStyle);
        eLabel->setText(tr("Totale annuo [kWh]"));
        QLabel* tlLabel= new QLabel;
        tlLabel->setStyleSheet(labelStyle);
        tlLabel->setText(tr("Perdite termiche [%]"));
        QLabel* srLabel= new QLabel;
        srLabel->setStyleSheet(labelStyle);
        srLabel->setText(tr("Rendimento kWh/kWp"));

        pValue     = new QLabel;
        pValue->setStyleSheet(labelStyle);
        pValue->setText("0");
        totEnValue = new QLabel;
        totEnValue->setStyleSheet(labelStyle);
        totEnValue->setText("0");
        tlossValue = new QLabel;
        tlossValue->setStyleSheet(labelStyle);
        tlossValue->setText("0");
        srValue    = new QLabel;
        srValue->setStyleSheet(labelStyle);
        srValue->setText("0");

        QGridLayout* vel = new QGridLayout;
        vel->addWidget(otherLossLabel,0,0,1,1);
        vel->addWidget(otherLoss,0,1,1,1);
        vel->addWidget(pushMonthly,0,2,1,1);
        vel->addWidget(pLabel,1,0,1,1);
        vel->addWidget(pValue,1,1,1,1);
        vel->addWidget(eLabel,2,0,1,1);
        vel->addWidget(totEnValue,2,1,1,1);
        vel->addWidget(tlLabel,3,0,1,1);
        vel->addWidget(tlossValue,3,1,1,1);
        vel->addWidget(srLabel,4,0,1,1);
        vel->addWidget(srValue,4,1,1,1);
        vel->setColumnStretch(3,10);

	ve->addWidget(energyOut,0,0,1,1);
	ve->addWidget(belowWidget,1,0,1,1);
        ve->addLayout(vel,2,0,1,1);
	energyWidget->setLayout(ve);

	innerTabEO->addTab(energyWidget,tr("Energia mensile"));

	#ifdef PLUSVERSION
		lv->addWidget(hourlyEOPlot);
		lv->addWidget(checkDrawLoads);
		
		lvw->setLayout(lv);
		innerTabEO->addTab(lvw,tr("Energia oraria"));
		innerTabEO->addTab(energySummaryWidget,tr("Esploso En. oraria"));
				innerTabEO->addTab(energySummaryWidget,tr("Esploso En. oraria"));
	#else
		innerTabEO->addTab(hourlyEOPlot,tr("Energia oraria"));

	#endif
		
          tabWidget->addTab(innerTabEO,tr("Energia elettrica"));
          tabWidget->setTabIcon(2,QIcon(":/images/ep.png"));


	
#ifdef PLUSVERSION
          /* Add economical valution widget*/
          QWidget* cashWidget = new QWidget;

          cash   = new CashFlowPlot();
          //cash->setNumOfDec(numOfDec);

          QVBoxLayout* vc = new QVBoxLayout;
          vc->addWidget(cash);

          cashWidget->setLayout(vc);
  	tabWidget->addTab(cashWidget,tr("Valutazioni economiche"));
        tabWidget->setTabIcon(3,QIcon(":/images/euro.png"));
	
	tabWidget->addTab(inverterCheck,tr("Check sistema"));
        tabWidget->setTabIcon(4,QIcon(":/images/check.png"));
#endif
	
    }
void MainWindow::makeDirty()
{
      //  qDebug()<<"MW project is Dirty";
	projectIsDirty = true;
        setWindowModified(true);
	
}
void MainWindow::createInterface()
{
#ifdef PLUSVERSION

        simEcoOpt = new SimEcoOptions(this);
        //connect(simEcoOpt,SIGNAL(accepted()),SLOT(setSimOptions()));

	inverterCheck = new InverterCheck(this);
	
	
        ecoVal = new EcoVal(this);
        ecoVal->setProjectFolder(projectName);
	 
	 connect(ecoVal,SIGNAL(isDirty()),this,SLOT(makeDirty()));
	 connect(inverterCheck,SIGNAL(componentStatus( )),SLOT(updateComponentStatus()));
	 
         loadInterface = new Load;
	 connect(loadInterface,SIGNAL(updated()),SLOT(getLoad()));
#endif
	 
//   	 loadInterface->setDefault();
//  	 loadInterface->show();

	 QGridLayout *mainH = new QGridLayout;

         tabWidget = new QTabWidget;
         tabWidget->setTabPosition(QTabWidget::West);
    	
	 
	mainSettings = new QWidget;
  	mainSettings->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
 	mainSettings->setGeometry(QRect(0,0,241,281));

 	leftLayout = new QGridLayout;
//  	leftLayout->setSizeConstraint(QLayout::SetMinimumSize);

	annoLabel = new QLabel;
        annoLabel->setText(tr("Anno"));

	annoValue = new QSpinBox;	
	annoValue->setMinimum(2008);
	annoValue->setMaximum(3000);
	annoValue->setValue(currentDate.year());
// 	utcLabel = new QLabel;
// 	utcLabel->setText(tr("UTC"));
// 	utcValue = new QSpinBox;
// 	utcValue->setMinimum(-12);
// 	utcValue->setMaximum(12);	
// 	utcValue->setValue(1);
 	connect(annoValue,SIGNAL(valueChanged(int)),SLOT(changeDays()));
        connect(annoValue,SIGNAL(valueChanged(int)),SLOT(yearChanged(int)));

	altitudeLabel = new QLabel;
	altitudeLabel->setText(tr("Altitudine"));
	altitudeValue = new QDoubleSpinBox;
	altitudeValue->setMinimum(-100);
	altitudeValue->setMaximum(10000);
// 	altitudeValue->setText(QString::number(localita.alt));
         connect(altitudeValue,SIGNAL(editingFinished()),SLOT(createSolarPlot()));

	selectMonth = new QComboBox;

	
	
	selectDay   = new QComboBox;
	
// 	qDebug()<<"MW currentdate"<<currentDate.day()<<currentDate.month();
	selectMonth->addItems(MyMath::stringSerie(1,12));
        selectDay->addItems(MyMath::stringSerie(1,MyMath::monthEnd(currentDate.month(),localita.anno)));
	selectDay->setCurrentIndex((currentDate.day())-1);
	selectMonth->setCurrentIndex((currentDate.month()-1));
	connect(selectMonth,SIGNAL(currentIndexChanged(int)),SLOT(changeDays()));
 	connect(selectDay,SIGNAL(currentIndexChanged(int)),SLOT(dayChanged(int)));
		
	locLabel = new QLabel;
	locLabel->setText(tr("Cerca"));
	
	QFont font;
	font.setItalic(true);
	locLabelEx = new QLabel;	
	locLabelEx->setFont(font);
        locLabelEx->setText(tr("es.: 40/20/11 14/10/1 oppure 41.14 14.20 oppure Roma, It"));
// 	locLabelEx->setWordWrap(true);
	locValue = new QLineEdit;
		
	 connect(locValue,SIGNAL(returnPressed()),this,SLOT(setDamp()));
 
        italiaData = new QGroupBox(tr("Database Coordinate - ENEA"),this);
//  	italiaData->setVisible(false);
	pagesWidget = new QStackedWidget;
	pagesWidget->addWidget(new QWidget);
	connect(pagesWidget,SIGNAL(currentChanged(int)),SLOT(fadeInWidget(int)));

	italiaData->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"     background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                       stop: 0 #E0E0E0, stop: 1 #FFFFFF);\n"
"     border: 2px solid gray;\n"
"     border-radius: 5px;\n"
"     margin-top: 2ex;  \n"
" }\n"
"QGroupBox::title {\n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top left; /* position at the top center */\n"
"     padding: 0 3px;\n"
 
" }"));
	comuneLabel = new QLabel;
	comuneLabel->setText(tr("Comune"));
	comuneValue = new QLineEdit;
	comuneValue->setReadOnly(true);

	latLabel     = new QLabel;
	latLabel->setText(tr("Lat."));
	lonLabel     = new QLabel;
	lonLabel->setText(tr("Lon."));

	comuneLat    = new QLabel;
	comuneLat->setTextInteractionFlags(Qt::TextSelectableByMouse);
	comuneLon    = new QLabel;
	comuneLon->setTextInteractionFlags(Qt::TextSelectableByMouse);
	comuneLatS   = new QLabel;
	comuneLatS->setTextInteractionFlags(Qt::TextSelectableByMouse);
	comuneLonS   = new QLabel;
	comuneLonS->setTextInteractionFlags(Qt::TextSelectableByMouse);
	 
	comuniViewLabel = new QLabel;
	comuniViewLabel->setText(tr("Database"));
	comuniView = new QListView;
	comuniView->setLayoutMode(QListView::Batched);
	comuniView->setGeometry(0,0,italiaData->frameGeometry().width(),10);
	comuniView->setBatchSize(10);	
//  	connect(comuneValue,SIGNAL(textChanged(const QString &)),this,SLOT(setNewCity(const QString)));
	connect(comuniView,SIGNAL(doubleClicked(const QModelIndex &)),this,SLOT(updateCity(const QModelIndex &)));

	topLayout = new QGridLayout;
	topLayout->addWidget(comuneLabel,0,0,1,1);
	topLayout->addWidget(comuneValue,0,1,1,1);
	topLayout->addWidget(comuniViewLabel,2,0,1,1);
	topLayout->addWidget(comuniView,2,1,1,2);
	italiaData->setLayout(topLayout);
	pagesWidget->addWidget(italiaData);
	pagesWidget->setCurrentIndex(0);

	 support= new Support(this);
        connect(support,SIGNAL(coordinatesValid()),SLOT(reloadCoordinates()));
        connect(support,SIGNAL(pointChanged(double,double,QString&)),SLOT(updateLatFromGoogle(double,double,QString&)));

// 	QWidget *dateWidget = new QWidget;
// 	QHBoxLayout *hh = new QHBoxLayout;
// 	hh->addWidget(annoLabel);
// 	hh->addWidget(annoValue);
// 	hh->addWidget(monthLabel);
// 	hh->addWidget(selectMonth);
// 	hh->addWidget(dayLabel);
// 	hh->addWidget(selectDay);
// 	dateWidget->setLayout(hh);
	
	leftLayout->addWidget(locLabel,0,0,1,1);
	leftLayout->addWidget(locValue,0,1,1,1);
	leftLayout->addWidget(locLabelEx,1,0,1,2);
//  	leftLayout->addWidget(comuneLabel,2,0,1,1);
// 	leftLayout->addWidget(comuneValue,2,1,1,1);
	leftLayout->addWidget(latLabel,2,0,1,1);
	leftLayout->addWidget(comuneLat,2,1,1,1);
// 	leftLayout->addWidget(comuneLatS,2,2,1,1);
	leftLayout->addWidget(lonLabel,3,0,1,1);
	leftLayout->addWidget(comuneLon,3,1,1,2);
//   	leftLayout->addWidget(comuneLonS,3,2,1,2);
// 	leftLayout->addWidget(annoLabel,4,0,1,1);
//   	leftLayout->addWidget(annoValue,4,1,1,1);
// 	leftLayout->addWidget(dateWidget,4,2,1,1);
 	leftLayout->addWidget(altitudeLabel,4,0,1,1);
  	leftLayout->addWidget(altitudeValue,4,1,1,2);
   	leftLayout->addWidget(pagesWidget,5,0,1,2);
// 	leftLayout->addWidget(comuniViewLabel,5,0,1,1);
// 	leftLayout->addWidget(comuniView,5,1,1,2);

  	 leftLayout->addWidget(support,6,0,1,3);
	
	
	
	
// 	leftLayout->addWidget(monthLabel,6,2,1,1);
// 	leftLayout->addWidget(selectMonth,6,3,1,1);
// 	leftLayout->addWidget(dayLabel,6,4,1,1);
// 	leftLayout->addWidget(selectDay,6,5,1,1);
	
// 	leftLayout->addWidget(utcLabel,8,0,1,1);
// 	leftLayout->addWidget(utcValue,8,1,1,1);
//    	leftLayout->setColumnStretch(2, 10 );
 	mainSettings->setLayout(leftLayout);
	
 	 

 
	
	QGridLayout *surfaceLayout = new QGridLayout;

	aziValue = new QDoubleSpinBox(mainSettings);
	aziValue2 = new QDoubleSpinBox(mainSettings);
	
	aziValue->setMinimum(-180);
	aziValue->setMaximum(180);
	aziValue->setReadOnly(false);
	aziValue2->setMinimum(-180);
	aziValue2->setMaximum(180);
	aziValue2->setReadOnly(false);
	aziValue2->setVisible(false);
// 	azi->setMinimumWidth(2);
	azi = new QLabel;
	azi->setText(tr("Azimuth(SO)"));
        azi->setToolTip(tr("<p>Azimuth misurato rispetto a SUD <br> positivo verso OVEST</p>"));
	connect(aziValue,SIGNAL(editingFinished()),this,SLOT(setDampOthers()));
	connect(aziValue,SIGNAL(valueChanged(double)),this,SLOT(updateSurface(double)));
	
	connect(aziValue2,SIGNAL(editingFinished()),this,SLOT(setDampOthers()));
	connect(aziValue2,SIGNAL(valueChanged(double)),this,SLOT(updateSurface(double)));

	incl = new QLabel;
	incl->setText(tr("Tilt (gradi)"));
	inclValue = new QDoubleSpinBox ;
        inclValue->setMinimum(-89);
        inclValue->setMaximum(89);
	inclValue->setReadOnly(false);

	inclValue2 = new QDoubleSpinBox ;
	inclValue2->setMinimum(0);
	inclValue2->setMaximum(180);
	inclValue2->setReadOnly(false);
	inclValue2->setVisible(false);

	albedoLabel = new QLabel(mainSettings);	
	albedoLabel->setText(tr("Coeff. di albedo"));
	albedoValue = new QDoubleSpinBox(mainSettings);
	albedoValue->setMinimum(0);
	albedoValue->setMaximum(1);
	albedoValue->setSingleStep(0.01);
	albedoValue->setReadOnly(false);
 
	connect(albedoValue,SIGNAL(editingFinished()),this,SLOT(setDampOthers()));
	connect(inclValue,SIGNAL(editingFinished()),this,SLOT(setDampOthers()));
	connect(inclValue,SIGNAL(valueChanged(double)),this,SLOT(updateTiltSurface(double)));
	connect(inclValue,SIGNAL(valueChanged(double)),SLOT(updateLimitDistance(double)));

	connect(inclValue2,SIGNAL(editingFinished()),this,SLOT(setDampOthers()));
	connect(inclValue2,SIGNAL(valueChanged(double)),this,SLOT(updateTiltSurface(double)));
	

	areaLabel = new QLabel;
	areaLabel->setText(tr("Area(mq)"));
	areaValue = new QDoubleSpinBox;
        areaValue->setRange(0,1000000);
        areaValue->setDecimals(5);

	areaValue2 = new QDoubleSpinBox;
        areaValue2->setRange(0,1000000);
        areaValue2->setDecimals(5);
	areaValue2->setVisible(false);
        connect(areaValue,SIGNAL(valueChanged(double)),SLOT(updateTrackValue(double)));
	connect(areaValue,SIGNAL(editingFinished()),SLOT(updatePower()));
	connect(areaValue,SIGNAL(valueChanged(double)),SLOT(changeNumPanels(double)));
	
	connect(areaValue2,SIGNAL(editingFinished()),SLOT(updatePower()));
	connect(areaValue2,SIGNAL(valueChanged(double)),SLOT(changeNumPanels2(double)));

	numOfPanels 	= new QLabel(tr("Numero di pannelli"));
	numOfPanelsValue= new QLabel;
	numOfPanelsValue->setTextInteractionFlags(Qt::TextSelectableByMouse);

	numOfPanelsValue2= new QLabel;
	numOfPanelsValue2->setTextInteractionFlags(Qt::TextSelectableByMouse);
	numOfPanelsValue2->setVisible(false);

	limitDistanceLabel    = new QLabel(tr("<p>Distanza limite <i>a</i> (mm)<p>"));
	limitDistanceLabel->setWordWrap(true);

	trackDim    = new QLabel(tr("<p>Larghezza tracker (m)<p>"));
	trackDim->setWordWrap(true);
	trackDimValue = new QDoubleSpinBox;
	trackDimValue->setMinimum(0);
	trackDimValue->setVisible(false);
	trackDim->setVisible(false);
	connect(trackDimValue,SIGNAL(valueChanged(double)),SLOT(updateLimitDistance(double)));
	limitDistanceLabel->setToolTip(tr("<p>In caso di disposizione in file, questo valore rappresenta la distanza fra file di pannelli che evita l'autombreggiamento. Il calcolo considera un angolo di elevazione del sole alle ore 10:00 del mese pi&ugrave; basso. <u>Con tilt nullo, tale distanza &egrave; nulla.</u><p>"));
	limitDistanceValue    = new QLabel;
	limitDistanceValue->setTextInteractionFlags(Qt::TextSelectableByMouse);
	

	 mountingLabel = new QLabel(tr("Tipo installazione"));
	 mountingValue = new QComboBox;
	 mountingValue->addItems(QStringList()<<tr("Su guida")<<tr("BIPV")<<tr("Schiera"));
	 mountingValue->setCurrentIndex(rack);
	 mountingHeightLabel = new QLabel(tr("<p>Altezza palo <i>h</i> (m)<p>"));
	 mountingHeightValue = new QDoubleSpinBox;
	 mountingHeightValue->setMinimum(0);
	 mountingHeightValue->setMaximum(50);
	 mountingHeightValue->setValue(2.5);
	 mountingHeightValue->setEnabled(false);

         limitDistanceLabel->setVisible(false);
         limitDistanceValue->setVisible(false);
	 
        concRatioLabel = new QLabel(tr("Fattore di concentrazione"));
  	concRatioValue = new QDoubleSpinBox;
	concRatioValue->setMinimum(1);
	concRatioValue->setMaximum(1000);
	concRatioValue->setValue(1.0);

// 	QLabel *l=new QLabel(tr("Premi CTRL+I per altre opzioni o clicca qui"));
// 	QLabel *l2=new QLabel(tr("Premi CTRL+I per altre opzioni o clicca qui"));
// 	QWidget *t=new QWidget(this);
// 	QHBoxLayout *htl = new QHBoxLayout;
// 	htl->addWidget(l);
// 	htl->addWidget(l2);
// 	t->setLayout(htl);
// 
//   	bF = new FaderWidget(t);
// 	
// 	bF->show();
// 	QPushButton *bF = new QPushButton(this);
	
	
	connect(mountingValue,SIGNAL(currentIndexChanged(int)),SLOT(enableHeight(int)));
	connect(mountingHeightValue,SIGNAL(editingFinished()),SLOT(updatePower()));
	connect(mountingHeightValue,SIGNAL(valueChanged(double)),SLOT(updateLimitDistance()));
	connect(concRatioValue,SIGNAL(editingFinished()),SLOT(updatePower()));
// 	drawSurface(canvas,0); // Initially the surface is at 0 degree SW*?
	 canvas = new SurfaceWidget ;
        connect(canvas,SIGNAL(swapped( )),SLOT(swapLimitDistance()));
	connect(mountingValue,SIGNAL(currentIndexChanged(int)),canvas,SLOT(setType(int)));
	surfaceLayout->addWidget(azi,0,0,1,1);
	surfaceLayout->addWidget(aziValue,0,1,1,1);
	surfaceLayout->addWidget(aziValue2,0,2,1,1);
	surfaceLayout->addWidget(incl,1,0,1,1);
	surfaceLayout->addWidget(inclValue,1,1,1,1);
	surfaceLayout->addWidget(inclValue2,1,2,1,1);
	surfaceLayout->addWidget(albedoLabel,2,0);
	surfaceLayout->addWidget(albedoValue,2,1);
	surfaceLayout->addWidget(areaLabel,3,0,1,1);
	surfaceLayout->addWidget(areaValue,3,1,1,1);
	surfaceLayout->addWidget(areaValue2,3,2,1,1);
	surfaceLayout->addWidget(numOfPanels,4,0,1,1);
	surfaceLayout->addWidget(numOfPanelsValue,4,1,1,1);
	surfaceLayout->addWidget(numOfPanelsValue2,4,2,1,1);
  	surfaceLayout->addWidget(canvas,5,0,3,3);
	surfaceLayout->addWidget(limitDistanceLabel,8,0,1,1);
	surfaceLayout->addWidget(limitDistanceValue,8,1,1,2);
	surfaceLayout->addWidget(trackDim,9,0,1,1);
	surfaceLayout->addWidget(trackDimValue,9,1,1,2);
	surfaceLayout->addWidget(mountingLabel,10,0,1,1);
	surfaceLayout->addWidget(mountingValue,10,1,1,2);
	surfaceLayout->addWidget(mountingHeightLabel,11,0,1,1);
	surfaceLayout->addWidget(mountingHeightValue,11,1,1,2);
	surfaceLayout->addWidget(concRatioLabel,12,0,1,1);
	surfaceLayout->addWidget(concRatioValue,12,1,1,2);
//    	surfaceLayout->addWidget(bF,12,0);
//  bF->show();
	surfaceLayout->setRowStretch(13,10);
 
	QWidget *surface      = new QWidget;
 
	surface->setLayout(surfaceLayout);
		
	


//	QGridLayout *radLayout = new QGridLayout;

	optiIncl = new QLabel;
	optiInclValue = new QLabel;
	maxIrrHb = new QLabel ;
	maxIrrHb->setWordWrap(true);
	maxIrrHbValue = new QLabel ;
	maxIrrHb->setText(tr("Hb extraatmosferica"));
	maxIrrHb->setToolTip(tr("<p>Radiazione diretta all'esterno dell'atmosfera</p>"));
	maxIrrHb->setWordWrap(true);
	
	maxIrrHincl = new QLabel ;
	maxIrrHinclValue = new QLabel ;//wattLabel2
	
	maxIrrHinclValue->setTextInteractionFlags(Qt::TextSelectableByMouse);
	maxIrrHinclValue->setAutoFillBackground(true);
        maxIrrHincl->setText(tr("H annua"));
	maxIrrHincl->setToolTip(tr("<p>Radiazione incidente annua</p>"));
	QString c = "darkkhaki";
	changeColor(*maxIrrHinclValue,c);
	
	maxIrrHinclOmbre      = new QLabel ;
	maxIrrHinclOmbreValue = new QLabel  ;//wattLabel2
	maxIrrHinclOmbreValue->setTextInteractionFlags(Qt::TextSelectableByMouse);
	maxIrrHinclOmbreValue->setAutoFillBackground(true);
        maxIrrHinclOmbre->setText(tr("H annua con ombre"));
	maxIrrHinclOmbre->setToolTip(tr("<p>Radiazione incidente annua con ombre</p>"));
	maxIrrHinclOmbre->setWordWrap(true);
	 
	changeColor(*maxIrrHinclOmbreValue,c);
	

	meanIrrHincl	      = new QLabel;
	
	meanIrrHincl->setText(tr("H media giornaliera"));
	meanIrrHincl->setToolTip(tr("<p>Radiazione incidente media in un giorno</p>"));
	meanIrrHincl->setWordWrap(true);
	meanIrrHinclValue     = new QLabel;
	meanIrrHinclValue->setTextInteractionFlags(Qt::TextSelectableByMouse);//wattLabel3
	
	changeColor(*maxIrrHinclOmbreValue,c);
// 	maxIrrHinclOmbre->setText(tr("Radiazione incidente annua con ombre"));
 
		
	
	unit<<"MJ/m2"<<"kWh/m2";
	unitE<<"MJ"<<"kWh";
//         wattLabel = new QPushButton(tr("MJ/m2"));
// 	wattLabel->setToolTip(tr("<p> Clicca per cambiare unit&agrave;<p>"));
 	wattLabel2 = new QPushButton(tr("MJ/m2"));
        wattLabel2->setToolTip(tr("<p> Clicca per cambiare unit&agrave;</p>"));
//         wattLabel3 = new QPushButton(tr("MJ/m2/giorno"));
// 	wattLabel3->setToolTip(tr("<p> Clicca per cambiare unit&agrave;<p>"));
// 	wattOptiLabel = new QPushButton(tr("MJ/m2"));
//         wattLabel3->setFlat(true);
 	wattLabel2->setFlat(true);
// 	wattLabel->setFlat(true);
// 	wattOptiLabel->setFlat(true);
	
	
	/*
	wattLabel3->setStyleSheet(QString::fromUtf8("QPushButton:flat {"
     		"border: none; /* no border for a flat push button "
//  		"}"));*/
// 	wattLabel2->setStyleSheet(QString::fromUtf8("QPushButton:flat {"
//      		"border: none; /* no border for a flat push button "
//   		"}"));
// 	wattLabel->setStyleSheet(QString::fromUtf8("QPushButton:flat {"
//      		"border: none; /* no border for a flat push button */"
//  		"}"));
// 	wattOptiLabel->setStyleSheet(QString::fromUtf8("QPushButton:flat {"
//      		"border: none; /* no border for a flat push button */"
//  		"}"));

	
	inclOptiLabel = new QLabel;
	inclOptiLabel->setText(tr("Senza Ombre"));
	inclOptiOmbreLabel = new QLabel;
	inclOptiOmbreLabel->setText(tr("Con Ombre"));

	inclOptiValue = new QLabel ;
	inclOptiValue->setFrameStyle(QFrame::Plain|QFrame::Box);
	inclOptiValue->setTextInteractionFlags(Qt::TextSelectableByMouse);
	inclOptiValue->setText("      ");
        inclOptiCheck = new QCheckBox(tr("Calcolo tilt ottimo") );
	
	inclOptiValueOmbre = new QLabel;
	inclOptiValueOmbre->setFrameStyle(QFrame::Plain|QFrame::Box);
	inclOptiValueOmbre->setFrameStyle(QFrame::Plain|QFrame::Box);
	inclOptiValueOmbre->setText("      ");

        okButton = new QPushButton(tr("Tilt ottimo"));
	okButton->setEnabled(false);


	
//	radLayout->addWidget(maxIrrHb,0,0);
//	radLayout->addWidget(maxIrrHbValue,0,1);
//	radLayout->addWidget(wattOptiLabel,0,2);
//	radLayout->addWidget(maxIrrHincl,1,0);
//	radLayout->addWidget(maxIrrHinclValue,1,1);
//
//        radLayout->addWidget(wattLabel,1,2);
//	radLayout->addWidget(meanIrrHincl,2,0);
//	radLayout->addWidget(meanIrrHinclValue,2,1);
//	radLayout->addWidget(wattLabel3,2,2);
//	radLayout->addWidget(maxIrrHinclOmbre,3,0);
//	radLayout->addWidget(maxIrrHinclOmbreValue,3,1);
//        radLayout->addWidget(wattLabel2,3,2);
        //radLayout->addWidget(wattCombo,3,0);
//        radLayout->addWidget(inclOptiCheck,4,0);
//	radLayout->addWidget(inclOptiLabel,5,0);
//	radLayout->addWidget(inclOptiValue,5,1);
//	radLayout->addWidget(inclOptiOmbreLabel,6,0);
//	radLayout->addWidget(inclOptiValueOmbre,6,1);
//         radLayout->addWidget(inclOptiValue,4,1);
//        radLayout->addWidget(okButton,7,1);
//        radLayout->setRowStretch(4,10);
//	QWidget *radiation = new QWidget;
//	radiation->setLayout(radLayout);
	
// 	connect(okButton,SIGNAL(clicked()),this,SLOT(getOptiIncl()));
//         connect(inclOptiCheck,SIGNAL(stateChanged(int)),SLOT(stateChanged(int)));
	QVector<int> d;
	d<<0;

	QWidget *meteo = new QWidget;
	windLabel    = new QLabel(tr("Vel. vento(m/s) "));
	windLabel->setWordWrap(true);
	windValue    = new QDoubleSpinBox;
	windValue->setMinimum(0);
	windValue->setMaximum(500);
	windValue->setValue(localita.wind);

	windDailyTable = new QTableWidget(0,1,meteo);
	windDailyTable->setItemDelegate(new DoubleDelegate(d,200,0,2));
	windDailyTable->horizontalHeader()->setStretchLastSection(true);
        windDailyTable->setHorizontalHeaderLabels(QStringList()<<tr("Vel. vento media giornaliera(m/s)"));

	windLoadButton = new QPushButton(tr("Carica"));
	windLoadButton->setToolTip(tr("Carica valori medi mensili da file di testo"));
        windClearButton = new QPushButton(tr("Azzera"));
	windClearButton->setToolTip(tr("Imposta a 0 i valori medi mensili"));
        windResetButton = new QPushButton(tr("Reset"));
	windResetButton->setToolTip(tr("Ricarica i valori medi mensili dal database, se presente"));
        windUpdatePower = new QPushButton(tr("Applica"));
	windUpdatePower->setToolTip(tr("Applica i valori editati al sistema corrente"));
        windUpdatePower->setEnabled(false);
	tempMinLabel = new QLabel(tr("Temp. minima annuale(gradi)"));
	tempMinLabel->setWordWrap(true);
	tempMaxLabel = new QLabel(tr("Temp. max annnuale(gradi)"));
	
	tempMaxLabel->setWordWrap(true);
	tempMinValue = new QDoubleSpinBox;
	tempMinValue->setMinimum(-100);
	tempMinValue->setMaximum(100);
	tempMaxValue = new QDoubleSpinBox;
	tempMaxValue->setMinimum(-100);
	tempMaxValue->setMaximum(100);
	#ifndef PLUSVERSION
	tempMinLabel->setVisible(false);
	tempMinValue->setVisible(false);
	tempMaxLabel->setVisible(false);
	tempMaxValue->setVisible(false);
	#endif

#ifdef PLUSVERSION
        connect(tempMaxValue,SIGNAL(valueChanged(double)),SLOT(updateMaxTemp(double)));
        connect(tempMinValue,SIGNAL(valueChanged(double)),SLOT(updateMinTemp(double)));
//	connect(tempMaxValue,SIGNAL(valueChanged(double)),inverterCheck,SLOT(maxTempChanged(double)));
#endif
	tempExplainLabel = new QLabel(tr("Premi Reset per ricaricare i dati dal database"));
	tempDailyTable = new QTableWidget(0,1,meteo);
	
	tempDailyTable->setItemDelegate(new DoubleDelegate(d,70,-50,2));
	

	tempDailyTable->horizontalHeader()->setStretchLastSection(true);
	tempDailyTable->setHorizontalHeaderLabels(QStringList()<<tr("Temp. media giornaliera(gradi)"));
	
        tempLoadButton = new QPushButton(tr("Carica"));
	tempLoadButton->setToolTip(tr("Carica valori medi mensili da file di testo"));
        tempClearButton = new QPushButton(tr("Azzera"));
	tempClearButton->setToolTip(tr("Imposta a 0 i valori medi mensili"));
        tempResetButton = new QPushButton(tr("Reset"));
	tempResetButton->setToolTip(tr("Ricarica i valori medi mensili dal database, se presente"));
        tempUpdatePower = new QPushButton(tr("Applica"));
	tempUpdatePower->setToolTip(tr("Applica i valori editati al sistema corrente"));
        tempUpdatePower->setEnabled(false);
	resetTempDaily(1);
	resetWindDaily(1);

	tempNote  = new QLabel(tr("NOTA"));
	tempNote->setWordWrap(true);
	tempNote->setText(tr("NOTA: Perdite termiche negative vengono assunte pari a zero."));

        connect(windDailyTable,SIGNAL(itemChanged( QTableWidgetItem *  )),SLOT(windChangedPower()));
        connect(windLoadButton,SIGNAL(clicked()),SLOT(loadWindFile()));
	//connect(tempMinValue,SIGNAL(editingFinished()),SLOT(updatePower()));
	//connect(tempMaxValue,SIGNAL(editingFinished()),SLOT(updatePower()));
	connect(windClearButton,SIGNAL(clicked()),SLOT(clearWind()));	
	connect(windResetButton,SIGNAL(clicked()),SLOT(reloadWind()));	
        connect(windUpdatePower,SIGNAL(clicked()),SLOT(updateWindDaily()));


// 	connect(windValue,SIGNAL(editingFinished()),SLOT(updatePower()));

        connect(tempDailyTable,SIGNAL(itemChanged( QTableWidgetItem *  )),SLOT(tempChangedPower()));
        connect(tempLoadButton,SIGNAL(clicked()),SLOT(loadTempFile()));
	//connect(tempMinValue,SIGNAL(editingFinished()),SLOT(updatePower()));
	//connect(tempMaxValue,SIGNAL(editingFinished()),SLOT(updatePower()));
	connect(tempClearButton,SIGNAL(clicked()),SLOT(clearTemp()));	
	connect(tempResetButton,SIGNAL(clicked()),SLOT(reloadTemp()));	
        connect(tempUpdatePower,SIGNAL(clicked()),SLOT(updateTempDaily()));

	QFrame *line = new QFrame(this);
	QFrame *line2 = new QFrame(this);
        line->setObjectName(QString::fromUtf8("line"));

        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

	line2->setObjectName(QString::fromUtf8("line"));
        line2->setFrameShape(QFrame::HLine);
        line2->setFrameShadow(QFrame::Sunken);



	QGridLayout *meteoLayout = new QGridLayout;
// 	meteoLayout->addWidget(windLabel,0,0);
// 	meteoLayout->addWidget(windValue,0,1);
	meteoLayout->addWidget(windDailyTable,0,0,1,2);
 
	meteoLayout->addWidget(windLoadButton,1,0);
	meteoLayout->addWidget(windClearButton,1,1);
	meteoLayout->addWidget(windResetButton,2,0);
        meteoLayout->addWidget(windUpdatePower,2,1);
	meteoLayout->addWidget(line,3,0,1,2);
	meteoLayout->addWidget(tempMinLabel,4,0);
	meteoLayout->addWidget(tempMinValue,4,1);
	meteoLayout->addWidget(tempMaxLabel,5,0);
	meteoLayout->addWidget(tempMaxValue,5,1);
	meteoLayout->addWidget(line2,6,0,1,2);
        meteoLayout->addWidget(tempDailyTable,7,0,1,2);
	meteoLayout->addWidget(tempLoadButton,8,0);
	meteoLayout->addWidget(tempClearButton,8,1);
	meteoLayout->addWidget(tempResetButton,9,0);
        meteoLayout->addWidget(tempUpdatePower,9,1);
  	meteoLayout->addWidget(tempExplainLabel,10,0,1,2);
 	 meteoLayout->addWidget(tempNote,11,0);
//         meteoLayout->setColumnStretch(4,10);
	meteoLayout->setRowStretch(11,10);
	meteo->setLayout(meteoLayout);


// 	monthToolButton = new QToolButton

	
	
	toolBox = new QToolBox;
	toolBox->setStyleSheet("QToolBox::tab {"
   	 "background: qlineargradient(spread:reflect, x1:1, y1:0.647273, x2:1, y2:0.028, stop:0 rgba(255, 213, 128, 255), stop:1 rgba(255, 255, 255, 255)) ; "
     "border-radius: 2px;"
     "color: black;"
      "}"
	"QToolBox::tab:selected { /* italicize selected tabs */"
     "font: italic;"
     "color: black;"
 	"}");
 	toolBox->setItemIcon(0,QIcon(":/images/save.png"));
        toolBox->setFrameShape(QFrame::Box);
   	toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding));
 	toolBox->setMinimumWidth(mainSettings->sizeHint().width()+10);
        toolBox->addItem(mainSettings,QIcon(":/images/mp.png"),tr("Sito"));
	toolBox->addItem(surface,QIcon(":/images/supcap.png"),tr("Superficie captante"));
	
	toolBox->addItem(meteo,QIcon(":/images/meteo.png"),tr("Dati Meteo"));
//	toolBox->addItem(radiation,tr("Risultati radiazione"));
// 	connect(toolBox,SIGNAL(currentChanged(int)),SLOT(showSuggestion(int)));

//	QWidget *delWidget = new QWidget;
//	dockMyPlot = new QDockWidget(tr("Diagramma solare"), delWidget);
//  	dockMyPlot->setAllowedAreas( Qt::RightDockWidgetArea);
//        dockMyPlot->setMinimumWidth(delWidget->width()/2);
	mainH->addWidget(toolBox,0,0);
        mainH->addWidget(tabWidget,0,1);
	QWidget *central=new QWidget;
	central->setLayout(mainH);
	setCentralWidget(central);
	
	locValue->setFocus( );
}

// void MainWindow::showSuggestion(int i)
// {
// //   if (i==captureSurface)
// // {
// // 	
// // 	
// //       		bF->start();
// // 	qDebug()<<"SHOWSUGGESTION";
// // }
// }
void MainWindow::ombreChanged()
{
        //qDebug()<<"Ombre changed in mainwindow...";
// 	reale->setOmbre(w->getShadowFactor());
 	createOptimumPlot();
 	setIntegrationInterval();
        qDebug()<<"Ombre changed in mainwindow...computeShadow";
	w->computeShadow();
	
 	createRealePlot();
        updatePower(0);
	ombrePresent = w->ombrePresent();
//	set();
}

void MainWindow::printPreamble(QTextStream &out)
{
/*TODO*/	
	QString sistema;
	if (localita.tipo == 1)
		sistema = tr("Inseguitore biassiale");
	if (localita.tipo == 0)
		sistema = tr("Tilt fisso");
	if (localita.tipo == 2)
		sistema = tr("Doppia falda");

	   out <<'\n'<<tr("Loc.: ")<<'\t'<<localita.name<<'\n'
	   <<tr("Tilt: ")<<'\t'<<localita.incl<<'\n'
	   <<tr("Tipo: ")<<'\t'<<sistema<<'\n'
	   <<tr("Azimuth: ")<<'\t'<<localita.azi<<'\n'
	   <<tr("Latitudine: ")<<'\t'<<localita.lat<<'\n'
		<<tr("Gradi-Min-Sec")<<QString::number(localita.latGradi)<<QString::number(localita.latMin)<<QString::number(localita.latSec)<<'\n'
	   <<tr("Longitudine:")<<'\t'<<localita.lon<<'\n'
		<<tr("Gradi-Min-Sec")<<QString::number(localita.lonGradi)<<QString::number(localita.lonMin)<<QString::number(localita.lonSec)<<'\n';
	 out<<tr("PANNELLO FOTOVOLTAICO-------------------")<<'\n';
	  if (thisProjectPanel.isValid)
	   
	   out<<tr("Marca:")<<'\t'<<thisProjectPanel.fabric<<'\n'
	   <<tr("Tipo:")<<'\t'<<thisProjectPanel.model <<'\n'
	   <<tr("Pnom:")<<'\t'<<thisProjectPanel.pnom<<'\n'
	   <<tr("Efficienza:")<<'\t'<<thisProjectPanel.eff<<'\n';
	   else
	   out<<tr("Marca:")<<'\n'
	   <<tr("Tipo:")<<'\n'
	   <<tr("Pnom:")<<'\n'
	   <<tr("Efficienza:")<<'\n';
	out<<tr("INVERTER (For complex system see the minireport)-------------------")<<'\n';
	if (thisProjectInverter.isValid)
	   out<<tr("Marca:")<<'\t'<<thisProjectInverter.fabric<<'\n'
	   <<tr("Tipo:")<<'\t'<<thisProjectInverter.model <<'\n'
	   <<tr("Pnom:")<<'\t'<<thisProjectInverter.pnom<<'\n'
	   <<tr("Efficienza:")<<'\t'<<thisProjectInverter.eff<<'\n';
	   else
	   out<<tr("Marca:")<<'\n'
	   <<tr("Tipo:")<<'\n'
	   <<tr("Pnom:")<<'\n'
	   <<tr("Efficienza:")<<'\n'<<'\n';
	out<<tr("Media Altre perdite:")<<'\t'<<QString::number(MyMath::mean(otherLosses.otherLoss))<<'\n';

           out<<tr("Radiazione in:")<<'\t'<<unit.at(reale->getUnit()-1)<<'\n'
	   <<tr("Energia annuale:")<<'\t'<<totEnergy<<unit.at(energyOutUnit-1)<<'\n'
	   <<"-------------------------------------------\n";
	   
}
void MainWindow::setIntegrationInterval()
{
	/* Fisso gli estremi di integrazione */
	/* per il calcolo delle ombre        */
	/* L'intervallo si puo' calcolare o in base a UNI 8477*/
	/* oppure in base agli angoli orari del sorgere e tramontare del sole*/
	/* Questi angoli sono disponibili in MyPlot */

	if (o!=0 && w!=0) {
		if (integrationType == custom_) {
		/* Se l'integrazione non e' fra gli estremi dettati */
		/* dalla norma UNI, usiamo il metodo di default di MyPlot */
// 		MyMath::convertToDegree(omegaApp,12);
// 		MyMath::convertToDegree(omegaSco,12);
               // qDebug()<<"MW omegaApp before"<<integrationType<<omegaApp.at(0)<<omegaApp.size()<<omegaSco.size();
                omegaApp = MyMath::convertToDegree(omegaApp);
                omegaSco = MyMath::convertToDegree(omegaSco);
		w->setOmegaApp(omegaApp);
		w->setOmegaSco(omegaSco);
		
             //qDebug()<<"MW omegaApp after"<<integrationType<<omegaApp.at(0);
		}
	}
}
void MainWindow::createSettings()
{
/*Correlazione*/
	switch (localita.radCorrModel) {
		case 1:
		modelSettings->radioUNI->setChecked(true);
		break;
		case 2:
		modelSettings->radioEnea->setChecked(true);
		break;
		case 3:
		modelSettings->radioErbs->setChecked(true);
		break;
	}
/*Perdite termiche*/
	switch (otherLosses.thermalModel) {
		case NOCT:
		modelSettings->radioNOCT1->setChecked(true);
		break;
		case CEA:
		modelSettings->radioCEA->setChecked(true);
		break;
		case other:
		modelSettings->radioOther->setChecked(true);
		 
	}
        /*Ombre*/
	if (localita.ombreModel==0)
  		modelSettings->radioOmbreLineari->setChecked(true);
	
	
	if (localita.ombreModel==1)
  	modelSettings->radioOmbreSpline->setChecked(true);

/******************************Tipo sistema*******************/
        modelSettings->comboType->setCurrentIndex(localita.tipo);
	if (localita.tipo==0){

// 		modelSettings->radioTilt->setChecked(true);

                        inclValue->setEnabled(true);

                        aziValue->setEnabled(true);

                        aziValue2->setVisible(false);

                        areaValue2->setVisible(false);

                        inclValue2->setVisible(false);

                        numOfPanelsValue2->setVisible(false);

                        doNotUpdatePower = true;
                        mountingValue->clear();

                        mountingValue->addItems(QStringList()<<tr("Su guida")<<tr("BIPV")<<tr("Schiera"));
                        mountingValue->setCurrentIndex(localita.mounting);
                       // qDebug()<<"MW MOUNTING CREATE"<<localita.mounting;
                        doNotUpdatePower = false;

                        trackDimValue->setEnabled(false);

                        trackDimValue->setVisible(false);

                        trackDim->setVisible(false);
                        mountingValue->setEnabled(true);
                        mountingHeightValue->setEnabled(false);
                        if (comboCurrentField->count()>1)
                                comboCurrentField->removeItem(1);



	}

	if (localita.tipo==1){
// 		modelSettings->radioBiAx->setChecked(true);
                        mountingHeightValue->setEnabled(true);
                        mountingValue->setEnabled(false);
                        limitDistanceLabel->setVisible(true);
                        limitDistanceValue->setVisible(true);
                        inclValue->setEnabled(false);
                        aziValue->setEnabled(false);
                        inclValue2->setVisible(false);
                        aziValue2->setVisible(false);
                        areaValue2->setVisible(false);
                        numOfPanelsValue2->setVisible(false);
                        trackDimValue->setEnabled(true);
                        trackDimValue->setVisible(true);
                        trackDim->setVisible(true);
                        if (comboCurrentField->count()>1)
                                comboCurrentField->removeItem(1);
	}
	if (localita.tipo==2){

                        mountingHeightValue->setEnabled(true);
                        inclValue->setEnabled(true);
                        aziValue->setEnabled(true);
                        mountingValue->setEnabled(true);
                        inclValue2->setVisible(true);
                        aziValue2->setVisible(true);
                        areaValue2->setVisible(true);
                        numOfPanelsValue2->setVisible(true);
                        doNotUpdatePower = true;
                        mountingValue->clear();

                        mountingValue->addItems(QStringList()<<tr("Su guida")<<tr("BIPV"));
                        mountingValue->setCurrentIndex(localita.mounting);

                        trackDimValue->setEnabled(false);
                        trackDimValue->setVisible(false);
                        trackDim->setVisible(false);
                        doNotUpdatePower = false;
                        if (comboCurrentField->count()<2)
                                                comboCurrentField->addItem("2");
                //
	}
	
if (canvas){
				canvas->setType(localita.mounting);
				canvas->setTiltType(localita.tipo);
				if (localita.tipo==2){
				canvas->setTilt(QVector<double>()<<inclValue->value()<<inclValue2->value());
				canvas->setAzimuth(QVector<double>()<<aziValue->value()<<aziValue2->value());
				canvas->update();
				}
				else
				{
					canvas->setTilt(QVector<double>()<<inclValue->value());
					canvas->setAzimuth(QVector<double>()<<aziValue->value());
					canvas->update();
				}
}

  //qDebug()<<"MW CREATE SETTIGNS"<<localita.tipo<<localita.mounting<<mountingValue->currentIndex();
}
void MainWindow::updateModelSettings()
{
	int corr,ombre,tm,type,sim;
	sim = 0;
        corr = 1;
	if (modelSettings->exec()) {

		
                doNotUpdatePower = true;

		if (modelSettings->radioUNI->isChecked())
			corr = 1;
		if (modelSettings->radioEnea->isChecked())
			corr = 2;
		if (modelSettings->radioErbs->isChecked())
			corr = 3;
		
		if (localita.radCorrModel!=corr){
			localita.radCorrModel=corr;
			sim++;
		}

		if (modelSettings->radioOmbreLineari->isChecked())
			ombre = 0;
		if (modelSettings->radioOmbreSpline->isChecked())
			ombre  = 1;

		if (ombre!=localita.ombreModel){
			localita.ombreModel = ombre;
			sim++;
		}
		
		if (modelSettings->radioCEA->isChecked())
			tm = CEA;
		if (modelSettings->radioNOCT1->isChecked())
			tm = NOCT;
		if (modelSettings->radioOther->isChecked())
			tm = other;

		if (otherLosses.thermalModel!=tm){
			otherLosses.thermalModel = tm;
			sim++;
		}
		

		if (modelSettings->comboType->currentIndex()==0)  {
			type = 0;
			inclValue->setEnabled(true);
			aziValue->setEnabled(true);
			aziValue2->setVisible(false);
			areaValue2->setVisible(false);
			inclValue2->setVisible(false);
			numOfPanelsValue2->setVisible(false);
			
			mountingValue->clear();
			mountingValue->addItems(QStringList()<<tr("Su guida")<<tr("BIPV")<<tr("Schiera"));
                        trackDimValue->setEnabled(false);
                        trackDimValue->setVisible(false);
                        trackDim->setVisible(false);
			localita.additionalIncl.resize(0);
			localita.additionalAzi.resize(0);
			localita.additionalArea.resize(0);
			if (comboCurrentField->count()>1)
				comboCurrentField->removeItem(1);
			
		}

		if (modelSettings->comboType->currentIndex()==1){
			type= 1;
			
			mountingHeightValue->setEnabled(true);
                        limitDistanceLabel->setVisible(true);
                        limitDistanceValue->setVisible(true);
			inclValue->setEnabled(false);
			aziValue->setEnabled(false);
			inclValue2->setVisible(false);
			aziValue2->setVisible(false);
			areaValue2->setVisible(false);
			numOfPanelsValue2->setVisible(false);
                        trackDimValue->setEnabled(true);
                        trackDimValue->setVisible(true);
                        trackDim->setVisible(true);
			
			localita.additionalIncl.resize(0);
			localita.additionalAzi.resize(0);
			localita.additionalArea.resize(0);
			if (comboCurrentField->count()>1)
                                comboCurrentField->removeItem(1);
		}
		
		if (modelSettings->comboType->currentIndex()==2){
			type= 2;
			
			mountingHeightValue->setEnabled(true);
			inclValue->setEnabled(true);
			aziValue->setEnabled(true);

			inclValue2->setVisible(true);
			aziValue2->setVisible(true);
			areaValue2->setVisible(true);
			numOfPanelsValue2->setVisible(true);
			
			mountingValue->clear();
			mountingValue->addItems(QStringList()<<tr("Su guida")<<tr("BIPV"));
                        trackDimValue->setEnabled(false);
                        trackDimValue->setVisible(false);
                        trackDim->setVisible(false);
			localita.additionalArea<<areaValue2->value();
			localita.additionalAzi<<aziValue2->value();
			localita.additionalIncl<<inclValue2->value();
                        if (comboCurrentField->count()<2)
                            comboCurrentField->addItem("2");
			

			
		}

		if (type!=localita.tipo){
			localita.tipo = type;
			sim++;
		}

		 w->setShadowCombineMode(localita.ombreModel);

		reale->setModel(localita.radCorrModel);

		if (localita.tipo==1)
		{
                        if ((mountingValue!=0) && (trackDimValue!=0)){
  			mountingValue->setEnabled(false);
			mountingHeightValue->setEnabled(true);
                        //trackDimValue->setValue(sqrt(areaValue->value()));

// 			qDebug()<<"MW mounting value enabled";
			}
		}
		else
			{	

			mountingValue->setEnabled(true);
			mountingHeightValue->setEnabled(false);
		 }
		
        doNotUpdatePower = false;
	}
        else
            createSettings();
	
	if (canvas)
	{
				canvas->setType(localita.mounting);
				
				if (localita.tipo==2){
				canvas->setTilt(QVector<double>()<<inclValue->value()<<inclValue2->value());
				canvas->setAzimuth(QVector<double>()<<aziValue->value()<<aziValue2->value());
				
				}
				else
				{
					canvas->setTilt(QVector<double>()<<inclValue->value());
					canvas->setAzimuth(QVector<double>()<<aziValue->value());
				
				}
					updateLimitDistance();
				canvas->setTiltType(localita.tipo);
	}

        if (sim>0){

                        set(normal);
                        qDebug()<<"MW first pass false";
                        firstPassDone = false; //for simulation
                    }
		
	 
// 	qDebug()<<"Modello ombre...."<<localita.ombreModel;
// 	qDebug()<<"Model correlazione..."<<localita.radCorrModel;
// 
}

void MainWindow::setupGuiPanels()
{	
	/* This function must be called if a database is open*/
	datiPanels   = new DatiPannello(this);
	datiInverter = new DatiInverter(this);
	QSqlDatabase db = QSqlDatabase::database(databasePanelsId);
	datiPanels->setDatabase(db,"pannelli");
	datiInverter->setDatabase(db,"inverter");
}

void MainWindow::updatePower()
{

    if (somethingChanged()){

        updateSitePar();

        updatePower(0);
    }

}

void MainWindow::updatePower(int mode)
{
    if (!doNotUpdatePower) {

        setWindowModified(true);
        //updateSitePar();
        /* Check if area, incl or azimuth changed */

        /* For re-computation and invalidate data */
        if (mode==1)

        {

            set(normal);
        }


        if (mode==0)
        {


                /* Only temp or wind or area have been changed */
                if ((!wrongCoordinates) || !noNameAvailable ||
                    googleNameAvailable || estimatedCoordinates)
                {
                    if (thisProjectPanel.isValid)
                    {


                                createRealePlot();
                                createEnergyOutPlot();
                                drawHourlyValues();
                                createCheckInverter();
                                qDebug()<<"MW first pass false in updatepower";
                                firstPassDone = false; //Invalidate hourly data
                                statusLabelPower->setText(tr("Pot.= ") + QString("%L1 kWp").arg(installedPower()));
                    }

    }

        }
//	if (somethingChanged())
//	{
//
//		updateSitePar();
//                set(normal);
//	}
//	else
//		if ((!wrongCoordinates) || !noNameAvailable ||
//                    googleNameAvailable || estimatedCoordinates)
//                    if (thisProjectPanel.isValid)
//                    {
//
//
//  				createRealePlot();
//                                createEnergyOutPlot();
//				drawHourlyValues();
//				createCheckInverter();
//                                qDebug()<<"MW first pass false in updatepower";
//                                firstPassDone = false; //Invalidate hourly data
//                    }
//        statusLabelPower->setText(tr("Pot.= ") + QString("%L1 kWp").arg(installedPower()));
     }
}
void MainWindow::updateEnergyUnit()
{
        if (energyOut!=0) {
		energyOutUnit = energyOut->getUnit();
		effTemp   = energyOut->getEffTemp();
		Energy    = energyOut->getRealEnergy();
		totEnergy = energyOut->getTotEnergy();
	}
}
void MainWindow::resetWindDaily(int mode)
{
	/* mode =1, create new rows, mode=0, reset only value */
	QStringList s;
	
	if (windDailyTable) {
                windDaily.resize(0);
		for(int i=0;i<12;i++) {
			if (mode==1)
                        {   /* We do not have a table item at all, create it*/
				windDailyTable->insertRow(i);
				QTableWidgetItem *item = new QTableWidgetItem;
				item->setText(QString::number(0));
				item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
				windDailyTable->setItem(i,0,item);
                                
			}
			if ( (mode==0) && (tempDailyTable->item(i,0)) ) {
				windDailyTable->item(i,0)->setText(QString::number(0));

				/*reset also the vecotr */
				
			}
			windDaily<<0;
			otherLosses.wind<<0;
		}
	if (mode == 1)
	windDailyTable->setVerticalHeaderLabels(MyMath::monthFull());
	}
	if (mode == 0){
	/* We cleared all the values, we must rerun updatePoswer() */
        updatePower(0);
	}
	
}
void MainWindow::resetTempDaily(int mode )
{
	/* mode =1, create new rows, mode=0, reset only value */
	QStringList s;
	
	if (tempDailyTable) {
                tempDaily.resize(0);
		for(int i=0;i<12;i++) {
			if (mode==1)
                        {   /* We do not have a table item at all, create it*/
				tempDailyTable->insertRow(i);
				QTableWidgetItem *item = new QTableWidgetItem;
				item->setText(QString::number(0));
				item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
				tempDailyTable->setItem(i,0,item);
                                
			}
			if ( (mode==0) && (tempDailyTable->item(i,0)) ) {
				tempDailyTable->item(i,0)->setText(QString::number(0));

				/*reset also the vecotr */
				
			}
			tempDaily<<0;
			otherLosses.temperatures<<0;
		}
	if (mode == 1)
	tempDailyTable->setVerticalHeaderLabels(QStringList()<<tr("Gennaio")<<tr("Febbraio")<<tr("Marzo")<<tr("Aprile")<<tr("Maggio")<<tr("Giugno")<<tr("Luglio")<<tr("Agosto")<<tr("Settembre")<<tr("Ottobre")<<tr("Novembre")<<tr("Dicembre"));
	}
	if (mode == 0){

            tempMinValue->setValue(0);
            localita.tempMin = tempMinValue->value();
            minTempIsEdited = true;
            tempMaxValue->setValue(0);
            localita.tempMax= tempMaxValue->value();
            maxTempIsEdited = true;
            /* We cleared all the values, we must rerun updatePoswer() */
            updatePower(0);
	}
	
}
void MainWindow::updateWindDaily()
{
        double t;
//	/* We could use a model here, but the result is not much different */
//         qDebug()<<"MW updateWindDaily inizio..........";
         if (windDailyTable) {
             windDaily.resize(0);
  	     otherLosses.wind.resize(0);
             for(int i=0;i<12;i++) {

                                t=windDailyTable->item(i,0)->text().toDouble();
                                windDaily<<t;
  				otherLosses.wind << t;
#ifdef DEBUG
                                qDebug()<<"MW updateTempDaily"<<i<<t<<windDailyTable->item(i,0)->text();
#endif
                        }
                }
	
	
         qDebug()<<"MW windDaily updated..."<<otherLosses.wind;
        windUpdatePower->setEnabled(false);
        updatePower(0);
	windDataIsEdited = true;
		
}
void MainWindow::updateTempDaily()
{
        double t;
//	/* We could use a model here, but the result is not much different */
//         qDebug()<<"MW updateTempDaily inizio..........";
         if (tempDailyTable) {
             tempDaily.resize(0);
  	     otherLosses.temperatures.resize(0);
             for(int i=0;i<12;i++) {

                                t=tempDailyTable->item(i,0)->text().toDouble();
                                tempDaily<< t;
  				otherLosses.temperatures << t;
#ifdef DEBUG
                               qDebug()<<"MW updateTempDaily"<<i<<t<<tempDailyTable->item(i,0)->text();
#endif
                        }
                }
	
	
          qDebug()<<"MW tempDaily updated..."<<otherLosses.temperatures;
        tempUpdatePower->setEnabled(false);
        updatePower(0);
	tempDataIsEdited = true;
		
}
void MainWindow::updateWindWidget()
{
  if (windDailyTable) {
	for (int i=0;i<12;i++) {
		if (i<windDaily.size()) {
			windDailyTable->item(i,0)->setText(QString::number(windDaily.at(i),'f',2));
			
		}
	}

  }
  
}
void MainWindow::updateTempWidget()
{
  if (tempDailyTable) {
	for (int i=0;i<12;i++) {
		if (i<tempDaily.size()) {
			tempDailyTable->item(i,0)->setText(QString::number(tempDaily.at(i),'f',2));
			
		}
	}

  }
// qDebug()<<"MainWinodw updateWidget"<< tempDaily;
}
void MainWindow::clearTemp()
{
	resetTempDaily(0);
	
}
void MainWindow::clearWind()
{
	resetWindDaily(0);
	
}
void MainWindow::reloadWind()
{
    nasaObject res;
// 	switch (localita.source) {
// 		case radEnea:
// 			loadWind(false);
// 		break;
// 		case radNasa:
                        windDaily.resize(0);
			
                       // findNasaData(localita.lat,localita.lon,localita.latGradi,localita.latMin,localita.latSec,
                               //                  localita.lonGradi,localita.lonMin,localita.lonSec,2);
// 			windDaily = n.data;
                        res  =
                               findNasaDataSQL(localita.lat,localita.lon,localita.latGradi,
                                               localita.latMin,localita.latSec,
                                               localita.lonGradi,localita.lonMin,
                                               localita.lonSec);
                        windDaily = res.wind;
			otherLosses.wind = windDaily;
			adjustVector(windDaily);
			updateWindWidget( );
                        updatePower(0);
// 		break;
// 		case radPvgis:
// 		break;
// 		case radCustom:
// 			loadWind(false);
// 		break;
// 	}
	windDataIsEdited = false;
}

void MainWindow::reloadTemp()
{
    nasaObject res;
        switch (localita.source) {
                case radUNI:
                        extractRadiazione(localita);
                break;
        default:

                        tempDaily.resize(0);
			
                       // findNasaData(localita.lat,localita.lon,localita.latGradi,localita.latMin,localita.latSec,
                                       //          localita.lonGradi,localita.lonMin,localita.lonSec,1);
                        res  =
                               findNasaDataSQL(localita.lat,localita.lon,localita.latGradi,
                                               localita.latMin,localita.latSec,
                                               localita.lonGradi,localita.lonMin,
                                               localita.lonSec);
                        tempDaily = res.temp;


              }
			otherLosses.temperatures = tempDaily;
			adjustVector(tempDaily);

                            tempMinValue->setValue(MyMath::min(tempDaily));
                            localita.tempMin = tempMinValue->value();



                            tempMaxValue->setValue(MyMath::max(tempDaily));
                            qDebug()<<"MAX TEMP"<<MyMath::max(tempDaily);
                            localita.tempMax = tempMaxValue->value();


			updateTempWidget( );

	tempDataIsEdited = false;
        minTempIsEdited  = false;
        maxTempIsEdited = false;
}
void MainWindow::loadWindFile()
{
	/* convenience function */	
	loadWind(true);
}
void MainWindow::loadTempFile()
{
	/* convenience function */	
	loadTemp(true);
}
void MainWindow::loadWind(bool newWind)

{
	 
	if (otherLosses.windPath.isEmpty() || newWind)
			otherLosses.tempPath = QFileDialog::getOpenFileName(this, tr("File venti"), recentDir, "Text files (*.txt  )");
	
	 QFileInfo fileInfo(otherLosses.windPath);
    	 
		
	
	QVector<double> temp;
	int condition;
	double x,y;
	condition = 0;
    	if ( !otherLosses.windPath.isEmpty() && fileInfo.exists())
    	{ 
                QFile file(otherLosses.windPath);
                
                recentDir = fileInfo.absoluteDir().absolutePath();
		QTextStream in(&file);
		if (file.open(QIODevice::ReadOnly)){
			while (!in.atEnd()) {
				QString lineRaw =in.readLine();
				lineRaw = lineRaw.simplified();
				QStringList l = lineRaw.split(" ");
//                                 qDebug()<<"MW load wind"<<l.size()<<lineRaw;
				if ( (l.size()<2) && (!lineRaw.isEmpty())) {
                                        QMessageBox::critical(this,tr("Importazione"),tr("Il file di dati deve avere almeno due colonne."),QMessageBox::Ok);

					return;
				}
				else 
				{
					if (!lineRaw.isEmpty()) {
						x = l.at(0).toDouble();
						y = l.at(1).toDouble();
                                                temp<<y;

					}
                                }
			}
				
					if ( temp.size()!=12 ) {
						int r2 = QMessageBox::question(this,tr("Errore"),tr("Il file contiene un numero di mesi diverso da 12. Se si continua, i mesi mancanti avranno valore nullo."),QMessageBox::Ok,QMessageBox::Cancel);
						if (r2==QMessageBox::Ok){
							  
							 resizeCustomWind(temp.size());
							 
						}
						else
							return;
					}
					else {
						windDaily.resize(0);
						windDaily = temp;
						
					}
				}
			 				
		}
	updateWindWidget();
        updatePower(0);
}
void MainWindow::loadTemp(bool newTemp)

{
	 
	if (otherLosses.tempPath.isEmpty() || newTemp)
			otherLosses.tempPath = QFileDialog::getOpenFileName(this, tr("File temperature"), recentDir, "Text files (*.txt  )");
	
	 QFileInfo fileInfo(otherLosses.tempPath);
    	 
		
	
	QVector<double> temp;
	int condition;
	double x,y;
	condition = 0;
    	if ( !otherLosses.tempPath.isEmpty() && fileInfo.exists())
    	{ 
                QFile file(otherLosses.tempPath);
                
                recentDir = fileInfo.absoluteDir().absolutePath();
		QTextStream in(&file);
		if (file.open(QIODevice::ReadOnly)){
			while (!in.atEnd()) {
				QString lineRaw =in.readLine();
				lineRaw = lineRaw.simplified();
				QStringList l = lineRaw.split(" ");
//                                 qDebug()<<"MW load temperature"<<l.size()<<lineRaw;
				if ( (l.size()<2) && (!lineRaw.isEmpty())) {
                                        QMessageBox::critical(this,tr("Importazione"),tr("Il file di dati deve avere almeno due colonne."),QMessageBox::Ok);

					return;
				}
				else 
				{
					if (!lineRaw.isEmpty()) {
						x = l.at(0).toDouble();
						y = l.at(1).toDouble();
                                                temp<<y;

					}
                                }
			}
				
					if (temp.size()!=12) {
						int r2 = QMessageBox::question(this,tr("Errore"),tr("Il file contiene un numero di mesi diverso da 12. Se si continua, i mesi mancanti avranno tempertura nulla."),QMessageBox::Ok,QMessageBox::Cancel);
						if (r2==QMessageBox::Ok) {
							  
							 resizeCustomTemp(temp.size());
							 
						}
						else
							return;
					}
					else {
						tempDaily.resize(0);
						tempDaily = temp;
						
					}
				}
			 				
		}
	updateTempWidget();
        updatePower(0);
}

void MainWindow::resizeCustomWind(int s)
{
	if (s>12)
			windDaily.resize(12);
			
		if (s<12) {
			for (int i=s;i<12-windDaily.size();i++)
				windDaily.append(0);
		}	
// 	qDebug()<<"MaiWindow Dati temperatura resize..."<<tempDaily;
}
void MainWindow::resizeCustomTemp(int s)
{
	if (s>12)
			tempDaily.resize(12);
			
		if (s<12) {
			for (int i=s;i<12-tempDaily.size();i++)
				tempDaily.append(0);
		}	
// 	qDebug()<<"MaiWindow Dati temperatura resize..."<<tempDaily;
}		

void MainWindow::saveAs()
{
	QString fileName;
	fileName = QFileDialog::getSaveFileName(this, tr("Salva progetto"),
                                recentSaveProject,
                                tr("SolarCalc (*.sc)"));
	if (!fileName.isEmpty())
	{
	saveProjectFile = fileName;
	save();
	}
	
}
void MainWindow::clearProject()
{
        updateEnergyLabels(0);
        decorateTab(innerTabEO,tabWidget,2,2,2); //reset//

        if (pagesWidget)
            pagesWidget->setCurrentIndex(0);
        simYear = annoValue->value();
	myplotpresent = false;
        refCurveShown = false;
        tempDataIsEdited = false;
        minTempIsEdited = false;
        maxTempIsEdited = false;
        windDataIsEdited = false;
        doNotLoadTemp	  = false;
        doNotLoadWind    = false;

	thisProjectPanel.isValid = false;
	thisProjectInverter.isValid = false;



        localita.name                 = "";
        localita.radDirettaAnnuaTotale=0;
        localita.additionalAzi.resize(0);
        localita.additionalIncl.resize(0);
        localita.additionalArea.resize(0);
        localita.albedoType = con;
        localita.wind = 0;
        localita.mounting = rack;
        localita.mountingHeight = 2.5;
        localita.utc =0;
        localita.anno=2009;
        localita.lat = 0;
        localita.latGradi =-999;
        localita.latMin =-999;
        localita.latSec =-999;
        localita.lon = -999;
        localita.lonGradi = -999;
        localita.lonMin =-999;
        localita.lonSec =-999;

        localita.alt = 0;
        localita.area = 0;
        localita.incl = 0;
        localita.azi = 0;
        localita.albedo = 0;
        thisProjectPanel.isValid = false; /*no panel selected at the start*/
        thisProjectInverter.isValid =false;
        otherLosses.otherLoss.fill(0,12);
	 
	 otherLosses.tempPath ="";
	 otherLosses.ombrePath="";
	 otherLosses.nearOmbrePath="";
         otherLosses.thermalModel = 0; //NOCT//
	 localita.tempMin = 0;
	 localita.tempMax = 40;
	 localita.ombreModel   = 0; /*sample and hold*/
         localita.radCorrModel = 2; /* ENEA */
	 localita.concRatio    = 1;
	 localita.tipo         = 0; /* Tilt fixed */
	 localita.source       = radEnea;
	 localita.radUnit      = megajoule;
	 
	 radNASAFile           = QCoreApplication::applicationDirPath() + "/nasa2005.txt";
	 tempNASAFile	       = QCoreApplication::applicationDirPath() + "/22yr_T10M";
	 estimatedCoordinates = false;

	 resetFlags();
         fileEnergyData = "";
	 saveProjectFile = "";
	 projectName = "(Untitled)";
	 projectIsDirty = false;
	/* Altri settaggi*/
	 validForExport = false;
	w->resetOmbre();
	w->drawMyContents(0);
	w->drawShadow(0,QPolygonF());
	o->drawContents(0);
	reale->resetOmbre();
	reale->drawContents(0,1);
	reale->drawRefCurve(0);
// 	reale->drawDailyValue(0);
	energyOut->drawContents(0);

	resetWidgets();
	setNewCity(" ");	
	initializeModel();
	delete xmlBag;
	xmlBag = new XmlEngine;
	xmlBag->newTree();
		CS.resize(0);
		RawCash.resize(0);
		NPV.resize(0);
		Interest.resize(0);
		InterestNPV.resize(0);

        resetStatusBar();
	resetEnString();
        createSettings();
        updateSourceRadSettings();
	#ifdef PLUSVERSION
                if (inverterCheck!=0)
			inverterCheck->resetAll();
                if (cash!=0)
                        cash->reset();
                if (ecoVal!=0)
                        ecoVal->resetAll();
                if (loadInterface!=0)
                        loadInterface->resetAll();

	#endif
       support->reset();
}
void MainWindow::resetWidgets()
{
		locValue->setText("");
		comuneValue->setText("");
		areaValue->setValue(0);
		inclValue->setValue(0);
		aziValue->setValue(0);
		otherLoss->setText(QString::number(0));	
		albedoValue->setValue(0);
		if (thisProjectPanel.isValid)
			numOfPanelsValue->setText(QString::number(0));
		else
			numOfPanelsValue->setText(QString(tr("<font color=\"red\"> pannello assente </font>")));
		windValue->setValue(0);
		inclOptiValue->setText("");
		gainValue->setText("");
		inclOptiValueOmbre->setText("");
		altitudeValue->setValue(0);
		
		
}
void MainWindow::newProject()
{
    /* 2 = NO
       3 = CANCEL
       1 = YES
    */
    int a;
	if (projectIsDirty)
	{
                a = ask();
                if (a==QMessageBox::Yes)
                    save();
                if (a==QMessageBox::Cancel)
                    return;
		 
	}
//	else
//	{
//
//	projectIsDirty = true;
//	}
	clearProject();
	projectName = "(Untitled)";
#ifdef PLUSVERSION
        if (ecoVal!=0)
		ecoVal->setProjectFolder(projectName);
#endif
	updateTitle(projectName);
}
int MainWindow::ask(const QString &t,const QString &what)
{
    /* 2 = NO
       3 = CANCEL
       1 = YES
    */
    int o = 2;
    QMessageBox msgBox(QMessageBox::Warning,t,what,QMessageBox::No);


     QPushButton *yesButton = msgBox.addButton(tr("Si"), QMessageBox::ActionRole);
     QPushButton *cancelButton = msgBox.addButton(tr("Annulla"), QMessageBox::ActionRole);
    msgBox.exec();
    if (msgBox.clickedButton() == yesButton)
        {
        o = 1;

        }


   if (msgBox.clickedButton() == cancelButton)
       o = 3;

    delete yesButton;
    delete cancelButton;

    return o; //default is "NO"


}
int MainWindow::askYESNO(const QString &t,const QString &what)
{
    int o = 2;
    QMessageBox msgBox(QMessageBox::Warning,t,what,QMessageBox::No);


     QPushButton *yesButton = msgBox.addButton(tr("Si"), QMessageBox::ActionRole);

    msgBox.exec();
    if (msgBox.clickedButton() == yesButton)
        {
        o = 1;

        }


    delete yesButton;


    return o; //default is "NO"


}
int MainWindow::ask()
{
	
	int a =QMessageBox::question(this, tr("Progetto non salvato"),tr("Vuoi salvare le modifiche?"),QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
//         if (a ==QMessageBox::Yes)
//                 return true;
//         else
//                 return false;

	return a;
}
QPolygonF MainWindow::readShadow(const QString &g)
/* This function read back the 360 point shadow file */

{
	QPolygonF temp;
	QFile file(g);
        QFileInfo fileInfo(g);
        QFileInfo projectDir(projectName);
 //qDebug()<<"MW READSW"<<g<<file.fileName()<<qPrintable(file.errorString())<<endl;
 //qDebug()<<"MW READSW file exist"<<file.exists();
 if (!file.exists()){
            /* The file does not exist: try to find it in the current project dir */
            file.setFileName(projectDir.absolutePath() + "/" +fileInfo.fileName());
//qDebug()<<"MW READSW file not exist, change dir"<<file.fileName();
}
	if (!file.open(QIODevice::ReadOnly)) {
                qDebug()<<"Cannot open shadow file"<<g<<file.fileName()<<qPrintable(file.errorString())<<endl;
		return QPolygonF();
	}
	QTextStream in(&file);
	
	while (!in.atEnd()) {
		QString line = in.readLine();
		QStringList fields = line.split(' ');
		if (fields.size()==2) 
			temp<<QPointF(fields.at(0).toDouble(),fields.at(1).toDouble());
		else{
			QMessageBox::warning(this,tr("Attenzione!"),tr("File di ombre danneggiato. Controlla"),QMessageBox::Ok);
			return QPolygonF();
		}
	}

	return temp;
}
void MainWindow::saveShadow(const QString &g,int mode)
{

	QFile file(g);	
	QPolygonF s;
	if (mode==horizon)
//		s = w->getShadowCombined();
                s = w->getShadow();
	if (mode==near)
        //        s = editor->getShadow();
                s = w->getShadowNear();
	if(!file.open(QIODevice::WriteOnly)) {
	qDebug()<<"Cannot open file shadow for writing"<<g<<qPrintable(file.errorString());
	return;
	}
        //if (s.size()>0){
			if (mode==horizon)
				otherLosses.ombrePath = g;
			if (mode==near)
				otherLosses.nearOmbrePath = g;
			QTextStream out(&file);
				for(int i=0;i < s.size();i++)
				{
                                        out<<s.at(i).x()<<" "<<s.at(i).y()<<"\n";
				}
        //}
	
}
void MainWindow::save()
{
	QString shadowFile,shadowFileNear;
#ifdef DEBUG
qDebug()<<"Mainwindow salvo progetto"<<saveProjectFile;
#endif 
qDebug()<<"MW save loc.name"<<localita.name;
	QString fileName;
	if (saveProjectFile.isEmpty())
		   saveProjectFile  = QFileDialog::getSaveFileName(this, tr("Salva progetto"),recentSaveProject,tr("SolarCalc (*.sc)"));

	if (!saveProjectFile.isEmpty()){
		saveProjectFile = MyMath::checkFormat(saveProjectFile,"sc");
		
                QFileInfo fileInfo(saveProjectFile);
                recentSaveProject = fileInfo.absoluteDir().absolutePath();

		shadowFile     = saveProjectFile + ".shadow.txt" ;
		shadowFileNear = saveProjectFile + ".Nearshadow.txt" ;
		saveShadow(shadowFile,horizon);
		saveShadow(shadowFileNear,near);
                qDebug()<<"MW save ombre"<<otherLosses.ombrePath<<otherLosses.nearOmbrePath;

		if (xmlBag){
  			delete xmlBag;
  			xmlBag = new XmlEngine();

                        //xmlBag->newTree();

		updateSitePar();
                QFile f(saveProjectFile);
#ifdef PLUSVERSION2
                xmlBag->setDetails(projectDetails->getAll());
                qDebug()<<"MW end get All PD"<<projectDetails->getAll().name;
#endif

                qDebug()<<"MW SAVE PANEL ID"<<thisProjectPanel.indexDB<<thisProjectPanel.isValid;
		xmlBag->setFile(&f);
		xmlBag->setLoc(localita);
		xmlBag->setPanelId(thisProjectPanel.isValid ? thisProjectPanel.indexDB:-1);
		xmlBag->setInverterId(thisProjectInverter.isValid ?thisProjectInverter.indexDB: -1);
		xmlBag->setOption(otherLosses);	

		ecopara tempEco;
		#ifdef PLUSVERSION
                if (ecoVal!=0)
			tempEco = ecoVal->getEcoParameters();
                if (simEcoOpt!=0)
                        tempEco.simoptions = simEcoOpt->getOptions();
		 
                #endif

                xmlBag->newTree();

                #ifdef PLUSVERSION
                if (loadInterface!=0){
                    if (loadInterface->isWindowModified())
                        {
                        QString consPath;
                        consPath =  consPath.isEmpty() ? tr("<font color=\"red\">Non specificato</font>") : loadInterface->getFileCustom();
                        int r =askYESNO(tr("Consumi elettrici"),tr("<p>La finestra consumi contiene consumi modificati ma non salvati. Si desidera salvarli?</p>") + tr("<p>Percorso File: ") + consPath);
                            if (r==1)
                                loadInterface->save();
                        }
                        tempEco.loadPath = loadInterface->getFileCustom();
                    }

			
                 if (ecoVal!=0){
                        xmlBag->setEcoParameters(tempEco);
                        ecoVal->saveAll();
                    }

		if (inverterCheck)
			xmlBag->setSystem(inverterCheck->getInverters(),inverterCheck->getSystem());



		#endif

		 
                 xmlBag->write();
		projectIsDirty = false; /*beacause we saved the file */
		projectName = saveProjectFile;
		
		updateTitle(projectName);
		}		
	 
// 	qDebug()<<"Mainwindo salvo progetto"<<saveProjectFile;
	}
	//SAVE ECOVAL PARAMETERS //
#ifdef PLUSVERSION
// 	if (ecoVal)
// 	{
// // 		ecoVal->save();
// // 		ecoVal->saveBands();
// // 		ecoVal->saveP();
// // 		ecoVal->saveMinP();
// 	}
#endif

}
void MainWindow::updateTitle(const QString &title)
{
	setWindowModified(false);
	
	localita.projectName = title;
	if (!title.isEmpty())
	{
		recentFiles.removeAll(title);
		recentFiles.prepend(title);
		updateRecentFileActions();	
	}
	setWindowTitle(QCoreApplication::applicationName()  + " - " + title + tr("[*]"));
	
}
void MainWindow::updateRecentFileActions()
{
	QMutableStringListIterator i(recentFiles);
	while (i.hasNext()) {
		if (!QFile::exists(i.next()))
		i.remove();
	}
	for (int j =0;j< MaxRecentFiles; ++j) {
		if (j < recentFiles.count()) {
		QString text = tr("&%1 %2").arg(j+1).arg(recentFiles[j]);
		recentFileActions[j]->setText(text);
		recentFileActions[j]->setData(recentFiles[j]);
		recentFileActions[j]->setVisible(true);
		}
		else
		{ 
		recentFileActions[j]->setVisible(false);
		}
	}
	separatorAction->setVisible(!recentFiles.isEmpty());
}
void MainWindow::openRecentFile()
{
    
        QAction *action = qobject_cast<QAction *>(sender());
        if (action)
            load(action->data().toString());
     
}
void MainWindow::ldDelayed()
{
    load(fileFromMain);
}

void MainWindow::loadDelayed(int delay, const QString &f)
{
    fileFromMain = f;
    QTimer::singleShot(delay, this, SLOT(ldDelayed()));
}

void MainWindow::load()
{
	load("");
}
void MainWindow::load(const QString& f )
/* Apre un nuovo progetto */
        /* 2 = NO
           3 = CANCEL
           1 = YES
        */

{
	if (projectIsDirty )
	{
                int answer = ask(tr("Attenzione"),tr("Vuoi salvare le modifiche?"));
                if (answer==1){
			qDebug()<<"MW projectisDirty"<<projectIsDirty;
			save();
		}
                if (answer == 3)
                    return;
	}
 		QString fileName;
		if (f.isEmpty())
			fileName = QFileDialog::getOpenFileName(this, tr("File progetto"), recentDirProject, tr("Solar Calc files (*.sc)"));
		else
			fileName = f;
	    	

	int condition;
// 	double x,y;
	condition = 0;
    	if ( !fileName.isEmpty() )
    	{ 
		QFile file(fileName);
                QFileInfo fileInfo(fileName);
                recentDirProject = fileInfo.absoluteDir().absolutePath();
		if (xmlBag){
			
			delete xmlBag;
			xmlBag = new XmlEngine();
			xmlBag->newTree();

			xmlBag->setFile(&file);
			xmlBag->read();
			localita = xmlBag->getLoc();
#ifdef PLUSVERSION2
                        if (projectDetails)
                            projectDetails->setAll(xmlBag->getDetails());
#endif


//
			thisProjectPanel.indexDB = xmlBag->getPanelId();
			thisProjectInverter.indexDB = xmlBag->getInverterId();
// 			otherLosses.tempPath  = xmlBag->getOption().tempPath;
 			otherLosses.ombrePath = xmlBag->getOption().ombrePath;
			otherLosses.nearOmbrePath = xmlBag->getOption().nearOmbrePath;
// 			otherLosses.otherLoss = xmlBag->getOption().otherLoss;
			otherLosses = xmlBag->getOption();

                        if (monthlyLoss!=0)
                            monthlyLoss->setLosses(otherLosses.otherLoss);
		#ifdef PLUSVERSION
                        ecopara tempEco = xmlBag->getEcoParameters();

                        if (ecoVal!=0){

                                ecoVal->setEcoParameters(tempEco);
				ecoVal->setProjectFolder(fileName);
			}
                        if (loadInterface!=0)
                       {
                           if (!tempEco.loadPath.isEmpty())
                            loadInterface->setFileCustom(tempEco.loadPath);
                       }

                        if (inverterCheck!=0)
				inverterCheck->setSystem(xmlBag->getSystem());

                        if (cash!=0){
                            cash->setOptions(tempEco.simoptions);
                            cash->reset();
                        }
                        if (simEcoOpt!=0)
                            simEcoOpt->setOptions(tempEco.simoptions);
                            CS.resize(0);
                            RawCash.resize(0);
                            NPV.resize(0);
                            Interest.resize(0);
                            InterestNPV.resize(0);
                            resetEnString();
                        innerTabEO->setTabIcon(2,QIcon(""));

		#endif

			
                       // qDebug()<<"Mainwindo apro progetto"<<localita.name<<localita.latGradi<<localita.latMin<<localita.latSec<<localita.lonGradi<<localita.lonMin<<localita.lonSec<<localita.area<<thisProjectInverter.indexDB<<thisProjectPanel.indexDB<<otherLosses.ombrePath<<localita.tipo;
// 			qDebug()<<"MW apro progetto..temperature"<<otherLosses.temperatures;
			projectName = fileName;

			updateTitle(projectName);
                        loadedProject = true;
			updateProject();
			saveProjectFile = projectName;
			
		 } 
}
}
void MainWindow::updateProject()
{

        initializeModel();
        doNotUpdatePower = true;
        mountingValue->setCurrentIndex(localita.mounting);
        doNotUpdatePower = false;
        decorateTab(innerTabEO,tabWidget,2,2,2);
	
// 	mountingValue->clear();
// 	mountingValue->addItems(QStringList()<<tr("Su guida")<<tr("BIPV")<<tr("Schiera"));

	if (!localita.name.isEmpty())
	locValue->setText(localita.name);
        else
	{
		if  (localita.latGradi!=-999){
                        locValue->setText(toS(localita.latGradi)+"/"+toS(localita.latMin)+"/"+toS(localita.latSec)+" "+toS(localita.lonGradi)+"/"+toS(localita.lonMin)+"/"+toS(localita.lonSec));
			useLoc = true;
// 			qDebug()<<"UPDATEPROJECT "<<useLoc<<useLoadedLoc;
			}
		else
		{
		useLoc = false;
// 		qDebug()<<"UPDATEPROJECT "<<useLoc<<useLoadedLoc;
		}
		 
	}
        //This function update the site by using the coordinates in the loaded project

        updateLatFromLoc();
        //set the shadow in the plot but not emit signals
        updateShadow();
        //do not find the city in google map if we are loading a project
        doNotSetCity=true;

qDebug()<<"MW localita"<<localita.name;

	thisProjectPanel = datiPanels->getSelectedPanel(thisProjectPanel.indexDB);

        if (localita.tipo==2){
                areaValue2->setValue(localita.additionalArea.at(0));
                inclValue2->setValue(localita.additionalIncl.at(0));
                aziValue2->setValue(localita.additionalAzi.at(0));
        }
        if (localita.tipo==1)
        {

                trackDimValue->setValue(localita.trackerArea);
                mountingHeightValue->setValue(localita.mountingHeight);
        }
	concRatioValue->setValue(localita.concRatio);
	albedoValue->setValue(localita.albedo);
	
// 	utcValue->setValue(localita.utc);
	annoValue->setValue(localita.anno);
	areaValue->setValue(localita.area);
	inclValue->setValue(localita.incl);
	aziValue->setValue(localita.azi);
	altitudeValue->setValue((localita.alt));

	otherLoss->setText(QString::number(MyMath::mean(otherLosses.otherLoss)));

	enableHeight(mountingValue->currentIndex());

	windValue->setValue(localita.wind);
	 

	createSettings();

        //qDebug()<<"MainWindow updateproject mounting"<<localita.mounting<< mountingValue->currentIndex();
	
//   	qDebug()<<"MainWindow updateproject panel valid"<<thisProjectPanel.isValid<<localita.area<<thisProjectPanel.H;

	thisProjectInverter = datiInverter->getSelectedInverter( thisProjectInverter.indexDB);
// 	qDebug()<<"MW inverter"<<thisProjectInverter.isValid<<thisProjectInverter.indexDB;
	updateSourceRadSettings();
	

	 
	tempDaily = otherLosses.temperatures;
	windDaily = otherLosses.wind;
	doNotLoadTemp = true;
	doNotLoadWind = true;
	updateTempWidget();
	updateWindWidget();
        tempMinValue->setValue(localita.tempMin);
        tempMaxValue->setValue(localita.tempMax);


updateLat();
qDebug()<<"MW localita"<<localita.name;
set(normal);


/* Other settings */

  checkScaling->setChecked(  otherLosses.scaling  );

    }
QString MainWindow::toS(int value)
{
	return QString::number(value);
}
QString MainWindow::toS(double value)
{
	return QString::number(value);
}

void MainWindow::loadShadow()
{
	w->loadShadow();
// 	otherLosses.ombrePath = w->getFileName();
}
QString MainWindow::getMonthString(int i)
{
	
	if (i<=31) return tr("Gennaio");
	if (i>31 && i<=60) return tr("Febbraio");
	if (i>60 && i<=91) return tr("Marzo");
	if (i>91 && i<=121) return tr("Aprile");
	if (i>121 && i<=152) return tr("Maggio"); 
	if (i>152 && i<=182) return tr("Giugno");
	if (i>182 && i<=213) return (tr("Luglio"));
	if (i>213 && i<=244) return tr("Agosto");
	if (i>244 && i<=274) return tr("Settembre");
	if (i>274 && i<=305) return tr("Ottobre");
	if (i>305 && i<=335) return tr("Novembre");
	if (i>335  && i<=366) return tr("Dicembre");
return QString();//Default
}
bool MainWindow::findNasaDataFast(double lat, double lon,double latG, double latM, double latS, double lonG, double lonM,double lonS, int mode)
{
    // Interpolate ?
    double A,B,C,D;
    QVector<double> a;
    if (mode==0)
    nasaData.resize(0);
    if (mode==1)
    tempDaily.resize(0);
    if (mode==2)
    windDaily.resize(0);



    A = (lat - latG ) * (lon-lonG);
    B = (lat - latG ) * (lonG+1-lon);
    C = (latG+1-lat)*(lon-lonG);
    D = (latG+1-lat)*(lonG+1-lon);
    qDebug()<<"MW start seekinFile"<<latG<<lonG;
    nasaData = MyMath::seekInFile(radNASAFile,((int)(latG+90)%360)*360 + lonG+180.0 ,75);
    return true;

}
//QVector<double> MainWindow::seekInFile(const QString file,qint64 pos,int length)
//{
//    QVector<double> o;
//    QFile f(file);
//    QString s;
//    bool a;
//     if (f.open(QIODevice::ReadOnly)){
//    QTextStream in(&f);
//
//    a = in.seek(pos * length);
//    s = in.readLine().split(" ");
//    o = MyMath::toVectorDouble(s);
//    qDebug()<<"MYMATH seekFile"<<in.readLine().split(" ")<<o<<file<<pos * length << a;
//}
//    else
//       qDebug()<<"MYMATH seekFile error "<<o<<file;
//    return  o;
//}

bool  MainWindow::findNasaData(double lat, double lon,double latG, double latM, double latS, double lonG, double lonM,double lonS, int mode)

{ 
	QString searchValue;
	double A,B,C,D;
	QVector<double> a,b,c;
        QString keyl,key,keyDef;
        bool useInterp,errorRad;
//         QHash<QString,double> *tempHash;
        useInterp = false;
 	errorRad = false;

	QPolygonF temp;
        
        keyl = QString::number(latG) + "," + QString::number(latM) + "," + QString::number(latS) +","+QString::number(lonG)+","+QString::number(lonM)+","+QString::number(lonS);
	
        //If there is no value, even for one month only, interpolate

	if (mode==0)
	nasaData.resize(0);
	if (mode==1)
	tempDaily.resize(0);
	if (mode==2)
	windDaily.resize(0);
      

        {
                if (!nasaRad.contains(keyl+",0"))
		{
//  qDebug()<<"MW FindNasa bool"<<keyl;
                        useInterp = true;
			//Find four rectangles
			A = (lat - latG ) * (lon-lonG);
			B = (lat - latG ) * (lonG+1-lon);
			C = (latG+1-lat)*(lon-lonG);
			D = (latG+1-lat)*(lonG+1-lon);
			for(int i=0;i<12;i++){
			a.resize(0);
			b.resize(0);
			c.resize(0);
					for(int k=0;k<2;k++){
						for(int l=0;l<2;l++){
					searchValue = QString::number(latG+k)+",0,0,"+QString::number(lonG+l)+",0,0,"+QString::number(i);
					if (nasaRad.contains(searchValue)){
						a<<nasaRad.value(searchValue);
                                               // qDebug()<<"MW extract NASA ok:"<<a;
					}

					else
						{
                                               // qDebug()<<"NASA RAD EXTRATION FAILED"<<searchValue;
						errorRad=true;
					}
					if (nasaTemp.contains(searchValue))
 						b<<nasaTemp.value(searchValue);
					else
						b<<0;
					
					if (nasaWind.contains(searchValue))
 						c<<nasaWind.value(searchValue);
					else
 					c<<0;
					 
					}
					}
				if ((mode==0) && !errorRad){
                                        nasaData<<(a.at(0)*A + a.at(1)*B + a.at(2)*C +a.at(3)*D);
                                       // qDebug()<<"NASA RAD EXTRATION ADDED 0"<<searchValue;
				}
				else{
// 					qDebug()<<"NASA RAD EXTRATION NOT ADDED 0"<<searchValue<<errorRad;
					}
				if (mode==1)
					tempDaily<<b.at(0)*A + b.at(1)*B + b.at(2)*C +b.at(3)*D;
				if (mode==2)
				windDaily<<c.at(0)*A + c.at(1)*B + c.at(2)*C +c.at(3)*D;
 
			}	
		}
		else
		{
                
                for(int i=0;i<12;i++)
                        {
                                key = keyl + "," + QString::number(i);
                            
                                nasaData<<(nasaRad.value(key));
				tempDaily<<nasaTemp.value(key);
				windDaily<<nasaWind.value(key);
                        }
		}

	}
 
	
	return useInterp;
}
nasaObject   MainWindow::findNasaDataSQL(double lat, double lon,double latG, double latM, double latS, double lonG, double lonM,double lonS)
 /* This function extract nasa data from the database.*/
 /*Done June 2010*/
 {
         double A,B,C,D;
         //int numRows;

         bool useInterp;
         nasaObject tempO;
         //QHash<QString,double> *tempHash;
         useInterp = false;
        /* mode=0 FIND RAD;
           mode=1 FIND TEMP;
           mode=2 FIND WIND*/
        QStringList campiR,campiT,campiW;
 //
        campiR<<"r1"<<"r2"<<"r3"<<"r4"<<"r5"<<"r6"<<"r7"<<"r8"<<"r9"<<"r10"<<"r11"<<"r12";
        campiT<<"t1"<<"t2"<<"t3"<<"t4"<<"t5"<<"t6"<<"t7"<<"t8"<<"t9"<<"t10"<<"t11"<<"t12";
        campiW<<"v1"<<"v2"<<"v3"<<"v4"<<"v5"<<"v6"<<"v7"<<"v8"<<"v9"<<"v10"<<"v11"<<"v12";
 //
        QVector<double> r1,r2,r3,r4,t1,t2,t3,t4,v1,v2,v3,v4;
        QSqlDatabase db = QSqlDatabase::database();
        db.setDatabaseName(databaseEntry);
        QSqlQueryModel query;



        query.setQuery("SELECT " + campiR.join(",") +
                      ","+        campiT.join(",") +
                      ","+        campiW.join(",") +
                      " FROM nasaData WHERE latitude=" + QString::number(lat)+
                      " AND longitude=" + QString::number(lon));


       // QMessageBox::information(this,"Debug",query.lastError().text()+query.query().executedQuery()+","+QString::number(query.query().isActive()) + "," + QString::number(query.rowCount()));
        qDebug()<<query.lastError()<<query.query().executedQuery()<<query.query().isActive()<<query.rowCount();

        //int i=0;

        /******************* Interpolate ***********************************/
        if (query.rowCount()==0)
            {

            r1.resize(0);
            r2.resize(0);
            r3.resize(0);
            r4.resize(0);
            t1.resize(0);
            t2.resize(0);
            t3.resize(0);
            t4.resize(0);
            v1.resize(0);
            v2.resize(0);
            v3.resize(0);
            v4.resize(0);
            tempO.rad.resize(0);
            tempO.temp.resize(0);
            tempO.wind.resize(0);

            //Find four rectangles
            A = (lat - latG ) * (lon-lonG);
            B = (lat - latG ) * (lonG+1-lon);
            C = (latG+1-lat)*(lon-lonG);
            D = (latG+1-lat)*(lonG+1-lon);


            /*First point */
            query.setQuery("SELECT " + campiR.join(",") +
                          ","+        campiT.join(",") +
                          ","+        campiW.join(",") +
                          " FROM nasaData WHERE latitude=" + QString::number(latG)+
                          " AND longitude=" + QString::number(lonG));

            for(int i=0;i<12;i++){
                r1 << query.record(0).value(i).toDouble();
                t1 << query.record(0).value(i+12).toDouble();
                v1 << query.record(0).value(i+24).toDouble();
            }
            /*Second point */

            query.setQuery("SELECT " + campiR.join(",") +
                          ","+        campiT.join(",") +
                          ","+        campiW.join(",") +
                          " FROM nasaData WHERE latitude=" + QString::number(latG)+
                          " AND longitude=" + QString::number(lonG+1));

            for(int i=0;i<12;i++){
                r2 << query.record(0).value(i).toDouble();
                t2 << query.record(0).value(i+12).toDouble();
                v2 << query.record(0).value(i+24).toDouble();
            }
            /*Third point */

            query.setQuery("SELECT " + campiR.join(",") +
                          ","+        campiT.join(",") +
                          ","+        campiW.join(",") +
                          " FROM nasaData WHERE latitude=" + QString::number(latG+1)+
                          " AND longitude=" + QString::number(lonG));

            for(int i=0;i<12;i++){
                r3 << query.record(0).value(i).toDouble();
                t3 << query.record(0).value(i+12).toDouble();
                v3 << query.record(0).value(i+24).toDouble();
            }
            /*Fourth point */

            query.setQuery("SELECT " + campiR.join(",") +
                          ","+        campiT.join(",") +
                          ","+        campiW.join(",") +
                          " FROM nasaData WHERE latitude=" + QString::number(latG+1)+
                          " AND longitude=" + QString::number(lonG+1));

            for(int i=0;i<12;i++){
                r4 << query.record(0).value(i).toDouble();
                t4 << query.record(0).value(i+12).toDouble();
                v4 << query.record(0).value(i+24).toDouble();

                tempO.rad << r1.at(i)*A + r2.at(i)*B + r3.at(i)*C + r4.at(i)*D;
                tempO.temp << t1.at(i)*A + t2.at(i)*B + t3.at(i)*C + t4.at(i)*D;
                tempO.wind << v1.at(i)*A + v2.at(i)*B + v3.at(i)*C + v4.at(i)*D;

            }
           //  qDebug()<<"MW nasa stimata"<<tempO.rad<<A<<B<<C<<D<<r1;
            tempO.status = false;


            }
        else
        {

            for(int i=0;i<12;i++){
                r1<< query.record(0).value(i).toDouble();
                t1 << query.record(0).value(i+12).toDouble();
                v1 << query.record(0).value(i+24).toDouble();

                tempO.rad << r1.at(i);
                tempO.temp << t1.at(i);
                tempO.wind << v1.at(i);

           // qDebug()<<"MW nasa sql"<<tempO.rad;
            }
            tempO.status = true;
        }
        return tempO;
 }


QPolygonF MainWindow::convertListToPol(const QStringList &s)
{
	QPolygonF temp;
	for(int i=0;i<s.size();i++) {
		temp<<QPointF(i,s.at(i).toDouble());

	}
//   		qDebug()<<"MW convertList "<<temp<<temp.size();
		return temp;
}
bool MainWindow::prepareNasaTemp(QProgressBar &p,int v)
{
	QString s, sLat,sLon,keyl,key;
 	QStringList splitted ;
	int count=0; 
	bool ok=false;
	
	QFileInfo nasaFile(tempNASAFile);
	if (!nasaFile.exists()){	
			 
			return false;
	}
	else
	{
		p.setValue(v);
		QFile file(tempNASAFile);
		if (file.open(QIODevice::ReadOnly)){
			QTextStream in(&file);
			while (!in.atEnd()) {
				s = in.readLine();
				s = s.simplified();
				splitted = s.split(" ");
				p.setValue(v+count++);
				if (splitted.size()>=14){
					sLat = splitted.at(0);
					sLon = splitted.at(1);
					splitted.removeLast();
					
					splitted.removeFirst();
					splitted.removeFirst();
// 					insertNasaDatabase(sLat.toInt(),sLon.toInt(),splitted,1);//insert temp data into datiEnea.db
					 
                                        keyl = sLat + ",0,0," + sLon+",0,0";//NASA DATA do not contains decimal values!
 					for(int i=0;i<12;i++) {
 						key = keyl + "," + QString::number(i); 
 						nasaTemp[key] = splitted.at(i).toDouble();
//  						qDebug()<<key<<nasaTemp[key];
                                }
				 
				ok = true;
				}
				else{
					 
					ok = false;
					 
			}
		}
	if (ok)
		return true;
	else	return false;
	}
	else
		return false;
	}
}
bool MainWindow::prepareNasaWind(QProgressBar &p,int v)
{
	QString s, sLat,sLon,keyl,key ;
 	QStringList splitted ;
	int count=0; 
	bool ok=false;
	
	
	QFileInfo nasaFile(windNASAFile);
	if (!nasaFile.exists()){	
			 
			return false;
	}
	else
	{
  		p.setValue(v);
		QFile file(windNASAFile);
		if (file.open(QIODevice::ReadOnly)){
			QTextStream in(&file);
			while (!in.atEnd()) {
				s = in.readLine();
				s = s.simplified();
				splitted = s.split(" ");
				p.setValue(v+count++);
				if (splitted.size()>=14){
					sLat = splitted.at(0);
					sLon = splitted.at(1);
					splitted.removeLast();
					splitted.removeFirst();
					splitted.removeFirst();
// 					insertNasaDatabase(sLat.toInt(),sLon.toInt(),splitted,2);//insert temp data into datiEnea.db

                                        keyl = sLat + ",0,0," + sLon+",0,0";//NASA DATA have no decimal data!

					for(int i=0;i<12;i++) {
						key = keyl + "," + QString::number(i); 
						nasaWind[key] = splitted.at(i).toDouble();
// 						qDebug()<<key<<nasaTemp[key];
						}
				 
				ok = true;
				}
				else{
					 
					ok = false;
					 
			}
		}
	if (ok)
		return true;
	else	return false;
	}
	else
		return false;
	}
}
bool MainWindow::prepareNasaRad(QProgressBar &p, int v)
{
	

	QString s, sLat,sLon,keyl,key ;
 	QStringList splitted ;
	int count =0; 
	bool ok=false;
	
        QFileInfo nasaFile(radNASAFile);
	if (!nasaFile.exists()){	
//                          qDebug()<<"MW PREPARENASA rad not exist"<<radNASAFile;
			return false;
	}
	else
	{
 		p.setValue(v);
		QFile file(radNASAFile);
		if (file.open(QIODevice::ReadOnly)){
			QTextStream in(&file);
                        while (!in.atEnd()  ) {

				
				s = in.readLine();

				s = s.simplified();
				splitted = s.split(" ");
				p.setValue(v+count++);
				if (splitted.size()>=14){
					sLat = splitted.at(0);
					sLon = splitted.at(1);
					splitted.removeLast();
					
					splitted.removeFirst();
					splitted.removeFirst();
// 					insertNasaDatabase(sLat.toInt(),sLon.toInt(),splitted,0);//insert rad data into datiEnea.db
					keyl =  sLat  + "," +  sLon;
                                        keyl = sLat + ",0,0," + sLon+",0,0";//NASA DATA have no decimal data!
					for(int i=0;i<12;i++) {
						key = keyl + "," + QString::number(i); 
						nasaRad[key] = splitted.at(i).toDouble();
                                          //      qDebug()<<"MW PREPARE NASA RAD"<<key<<nasaTemp[key];
						}
				 
				ok = true;
				}
				else{
					  
					ok = false;
					 
			}

		}
	if (ok)
		return true;
	else	return false;
	}
	else
		return false;
	}
}
void MainWindow::insertNasaDatabase(int slat,int slon,const QStringList &data,int mode)
{
// qDebug()<<"ApplicationDir path"<<databaseEntry;
	QStringList campi,campiU;
	QString query,queryTest,queryInsert,queryUpdate;
	
	QSqlDatabase d = QSqlDatabase::database();
	if (mode>2 || mode<0) return;
	if (mode==0){
		campi<<"r1"<<"r2"<<"r3"<<"r4"<<"r5"<<"r6"<<"r7"<<"r8"<<"r9"<<"r10"<<"r11"<<"r12";
		
	}
	if (mode==1)
		campi<<"t1"<<"t2"<<"t3"<<"t4"<<"t5"<<"t6"<<"t7"<<"t8"<<"t9"<<"t10"<<"t11"<<"t12";
		
	if (mode==2)
	campi<<"v1"<<"v2"<<"v3"<<"v4"<<"v5"<<"v6"<<"v7"<<"v8"<<"v9"<<"v10"<<"v11"<<"v12";

	for(int i=0;i<12;i++) {
			campiU<<campi.at(i)+"="+data.at(i); 
			if (i<11) campiU<<",";
		}
// 	qDebug()<<campiU;
	

	
	modelRadiazione->setQuery("SELECT * from nasaData WHERE lat=" + QString::number(slat) + " AND lon=" + QString::number(slon));
	
 	queryInsert = "INSERT into nasaData (lat,lon," + campi.join(",") + ") VALUES (" +  QString::number(slat)+ ","+ QString::number(slon) + "," + data.join(",")  + ")";
	queryUpdate = "UPDATE nasaData SET " + campiU.join(" ") + "  WHERE lat=" + QString::number(slat) + " AND lon=" + QString::number(slon);
// 	query = "SELECT * from radiazione";
// 	QSqlQuery qTest;
// 	qTest.prepare(queryTest);
// 	qTest.exec();
//  
//  	qDebug()<<"nasaDatabase Test"<<modelRadiazione->rowCount()<<modelRadiazione->lastError();
	QSqlQuery q;
	if (modelRadiazione->rowCount()>0) {
// 		qDebug()<<"Update"<<queryUpdate;
                q.prepare(queryUpdate);
		q.exec();
//   		qDebug()<<"nasaDatabase"<<q.lastError()<<queryUpdate<<d.isOpen();
	}
	else {
// 		qDebug()<<"Insert"<<queryInsert;
		q.prepare(queryInsert);
		q.exec();
//  		qDebug()<<"nasaDatabase"<<q.lastError()<<queryInsert<<d.isOpen();
	}
// 	modelRadiazione->setQuery(query);
  	
}
// QPolygonF MainWindow::extractNasaTemp(int lat,int lon)
// {

// 	QPolygonF temp;
// 	QString key,keyl;
// 	keyl = QString::number(lat) + "," + QString::number(lon);
// 	for(int i=0;i<12;i++){
// 		key = keyl + "," + QString::number(i);
// 		temp<<QPoint(0,nasaTemp.value(key));
// 		qDebug()<<key<<temp;
// 		}
// 	return temp;
	
	
// 	QStringList splitted ;
// 	int sLat,sLon;
// 	QString s;
// 	QFileInfo nasaFile(tempNASAFile);
// 	if (!nasaFile.exists())
// 		tempNASAFile = QFileDialog::getOpenFileName(this, tr("File temperature NASA"), recentDir, "Text files (*.txt  )");
// 		if (!tempNASAFile.isEmpty()) {
// 		QFile file(tempNASAFile);
// 		if (file.open(QIODevice::ReadOnly)){
// 			QTextStream in(&file);
// 			while (!in.atEnd()) {
// 				s = in.readLine();
// 				s = s.simplified();
// 				splitted = s.split(" ");
// 				
// 				
// 				sLat = splitted.at(0).toInt();
// 				sLon = splitted.at(1).toInt();
// 				
// 				if ((sLat == lat) && (sLon == lon)) {
// 				      if (splitted.size()>2) {
// 					splitted.removeFirst();
// 					splitted.removeFirst();
// 					tempDataIsEdited = false;
// // 					qDebug()<<"MW findNasaData splitted"<<splitted;
// 					return convertListToPol(splitted);
// 				      }
// 				else
// 					return QPolygonF();
// 					break;
// 				}
// 			}
// 			return QPolygonF();
// 		}
// 		}
// }

void MainWindow::wizard()
{
	Suggest s;
        double tempA,r;

        if (localita.additionalArea.size()>0)
            r = localita.radRealeAnnuaDF;
        else
            r = localita.radRealeAnnuaTotale;

qDebug()<<"MW WIZARD"<<r<<localita.radRealeAnnuaTotale;
	s.setPanel(thisProjectPanel);
        /* Doppia falda? */
        if (localita.additionalArea.size()>0)
         s.setPanel2(thisProjectPanel);

	s.setInverter(thisProjectInverter);
// 	qDebug()<<"MW wizard"<<otherLosses.otherLoss;
	s.setLoss(MyMath::max(otherLosses.otherLoss));
	if ((reale->getUnit()-1)==0)
                s.setRad( r/3.6);//in kWh
	if ((reale->getUnit()-1)==1)
                s.setRad( r);//in kWh
// 	qDebug()<<"No plo present"<<reale->mainPlotPresent();
	if (!reale || !reale->mainPlotPresent())
	{
		s.setRad(-1);
	}

	if (s.exec()) {
            tempA = s.getArea();
            if (localita.additionalArea.size()>0){
                areaValue->setValue(tempA/2);
                areaValue2->setValue(tempA/2);
            }
            else
                areaValue->setValue(tempA);

                        updatePower();
		      }
	;
}
void MainWindow::printGeneral()
{
    QPrinter printer ;
    printReport(&printer,3,QPrinter::NativeFormat);
}

void MainWindow::printPS()
{
    /*Stampa su ps */
        QPrinter printer(QPrinter::HighResolution);
        printReport(&printer,1,QPrinter::PostScriptFormat);
}

void MainWindow::print()
{ 
    /*Stampa su pdf */
        QPrinter printer ;
        printReport(&printer,1,QPrinter::PdfFormat);
	
}
void MainWindow::printReport(QPrinter* p,int mode,QPrinter::OutputFormat format)
{
	
	int current = comboCurrentField->currentIndex();
	t.setDir(recentDirReport);
	if (w) {
	 
// 	 QImage sd = w->getImage();
	 
	 t.addSolarDiagram(w);

 	 t.setVersion(version);
         if (localita.additionalArea.size()>0)
         t.setNumPanels(numPanels(),numPanels2());
         else
         t.setNumPanels(numPanels(),numPanels2());
	#ifdef PLUSVERSION
         if (ecoVal!=0)
             t.setEcoParameters(ecoVal->getEcoParameters());
         if (cash!=0){
             t.addVanDiagram(cash->vanDiagram());
             t.addRawDiagram(cash->rawDiagram());

	 }
         if (loadInterface!=0){
             t.addYearlyLoad(loadInterface->getYearlyTotal());
             t.addMonthlyProfile(loadInterface->getYearProfile());
         }
	#endif 
	 
	 
	}
	if (reale)
	{
		if (current==0){
		redrawReale(0);
		t.addSolarRadiation(reale);
                //qDebug()<<"MW redrawReale for print";
		redrawReale(1);
		t.addSolarRadiation2(reale);
  		
		}
		if (current==1)
		{
                    redrawReale(1);
                    t.addSolarRadiation(reale);
                    qDebug()<<"MW redrawReale for print";
                    redrawReale(0);
                    t.addSolarRadiation2(reale);
  		
		}
		
		
	}
        if (energyOut!=0)
	{
            t.addEEnergy(energyOut);
	}
	if (validForExport){
// 		qDebug()<<"Export";
		t.addLocation(localita);
		t.addOption(otherLosses);
		 
		t.addPanel(thisProjectPanel);
		t.addInverter(thisProjectInverter);
		t.addUnitEnergy(unitE.at(energyOut->getUnit()-1));
		t.addUnitRad(unit.at(reale->getUnit()-1));
		 
		t.addRad(HinclOmbre);
		if (energyPlotPresent){
			t.addEnergy(Energy);
			t.addTotEnergy(totEnergy);
		}
		else{
		   	t.addEnergy(NULL);
			t.addTotEnergy(0);
		}

		#ifdef PLUSVERSION
                if (cash!=0){
                        t.setTable(cash->getTable());
                        t.setTax(cash->getTaxTable());
                    }
                if (inverterCheck!=0)
			t.addSystem(inverterCheck->getSystem());
		#endif
                if (mode==3)
                    t.printGeneral(p);//Let user to choose printer
                else
                    t.print(p,mode,format);
// 		if (current==0)
// 			redrawReale(0,true);
// 		if (current==1)
// 			redrawReale(1,true);
		recentDirReport = t.getDir();
	}
	

}
void MainWindow::printPreview(QPrinter* p){
    printReport(p,0,QPrinter::PdfFormat);
}
void MainWindow::printPreview(){
	        QPrinter print(QPrinter::HighResolution);
              //   print.setPageSize(QPrinter::A4);
                print.setPaperSize(QPrinter::A4);
              
		QPrintPreviewDialog preview(&print,this);
		connect(&preview, SIGNAL(paintRequested(QPrinter *)), SLOT(printPreview(QPrinter*)));
		preview.exec();
}
void MainWindow::updateTiltSurface(double d)
{
	if (localita.tipo==2)
		canvas->setTilt(QVector<double>()<<inclValue->value()<<inclValue2->value());
	else
		canvas->setTilt(QVector<double>()<<d);
	
	canvas->update();	
}
void MainWindow::updateSurface(double d)
{
	if (localita.tipo==2)
		canvas->setAzimuth(QVector<double>()<<aziValue->value()<<aziValue2->value());
	else
		canvas->setAzimuth(QVector<double>()<<aziValue->value());
	canvas->update();	
}
void MainWindow::tempChangedPower()
{
    tempUpdatePower->setEnabled(true);

}
void MainWindow::windChangedPower()
{
    windUpdatePower->setEnabled(true);

}
void MainWindow::adjustVector(QVector<double> &p)
{
	/* Resize the vector to 12 values*/
	p.resize(12);
}
void MainWindow::adjustVector(QPolygonF &p)
{
	/* Resize the vector to 12 values*/
	p.resize(12);
}
void MainWindow::enableHeight(int h)
{

        if (mountingHeightValue!=0){
            if (localita.tipo == biax){
		mountingHeightValue->setEnabled(true);
                limitDistanceValue->setVisible(true);
                limitDistanceLabel->setVisible(true);
            }
		else
		mountingHeightValue->setEnabled(false);
                if (h==rack || h==direct ){
		limitDistanceValue->setVisible(false);
                limitDistanceLabel->setVisible(false);
            }
                else{
		limitDistanceValue->setVisible(true);
                limitDistanceLabel->setVisible(true);
            }
		
        updatePower(1);
	}
}
void MainWindow::about()
{

	#ifdef PLUSVERSION
        QMessageBox::about(this,tr("Info su Solar Calc "),tr("<h2>Solar Calc - ") + version + ", " +tr(" 2009-2013</h2>"
                                "<pre style=\"font-family: Verdana, Arial, sans serif;\"> Autore       :Giuseppe De Marco (Japita Systems Engineering, IT)</pre>"
				"<pre style=\"font-family: Verdana, Arial, sans serif;\"> Collaboratori: Giovanni Iacovoni </pre>"
				"<p>&copy; Tutti i diritti riservati a studioiacovoni.org</p>"
				"<p> Solar Calc &egrave; una applicazione per progettisti di impianti solari che usa i pi&ugrave; recenti modelli di radiazione solare. </p><p>Version ID :") + versionId + "</p>");
	#else
        QMessageBox::about(this,tr("Info su Solar Calc "),tr("<h2>Solar Calc - ") + version + ", " +tr(" 2009-2013</h2>"
                                "<pre style=\"font-family: Verdana, Arial, sans serif;\"> Autore      :Giuseppe De Marco (Japita Systems Engineering, IT)</pre>"
				"<pre style=\"font-family: Verdana, Arial, sans serif;\"> Collaboratori: Giovanni Iacovoni </pre>"
				"<p>&copy; Tutti i diritti riservati a studioiacovoni.org</p>"
                                "<p> Solar Calc &egrave; una applicazione per progettisti di impianti solari che usa i pi&ugrave; recenti modelli di radiazione solare. La versione Community non contiene i moduli per l'analisi del capital budgeting (IV Conto Energia) e la verifica di compatibilit&agrave; del sistema.</p><p>Version ID :")+ versionId + "</p>");
	#endif
}
void MainWindow::newShadowEditor()
{
	
// 	editor->resetTable();
	if (editor) {
		if (editor->isHidden())
			editor->show();
		else
			editor->activateWindow();
		
			 
				
	
	}

}
void MainWindow::updateShadowFromEditor()
{
        if (w!=0 && editor!=0){


                        w->setPolyShadow(editor->getShadow(),true);
                        #ifdef DEBUG
			qDebug()<<"MW shadow from Myplot"<<editor->getShadow();
                        #endif
  			w->drawShadow(3,QPolygonF());/*Cancel the preview shadow and */
  			w->drawShadow(1,QPolygonF());/*draw the combined one*/
		}
}
void MainWindow::drawShadowFromEditor()
{
                if (w!=0 && editor!=0){
                       // qDebug()<<"MW shadow from MyPlot changed "<<editor->getShadow();
// 			w->setPolyShadow(editor->getShadow());
			w->drawShadow(2,editor->getShadow());
		}

}
void MainWindow::tableResetted()
{
// 	qDebug()<<"MW editor shadow table resetted";
	if (w)
// 		w->undoCombine();
		w->delPoly();
		
}
void MainWindow::noRad(int i)
{
	if (i==all){
		w->drawMyContents(0);
		o->drawContents(0);
	}
		reale->drawContents(0,1);
		reale->drawDailyContents(0);
// 		reale->drawDailyValue(0);
		energyOut->drawContents(0);
		hourlyPlot->draw(0);
		hourlyEOPlot->draw(0);
		validForExport = false;
		updateRadLabels(reale->getUnit());
                statusBar()->showMessage(tr("Dato di radiazione mancante, stima eseguita"),4000);
}

void MainWindow::updateFromGoogle()
{
//         double lat;
//         double lon;
	
	 
        if (support)
        {
		if (!support->coordinates().isNull())
		{
				double lat = support->coordinates().x();
				double lon = support->coordinates().y();

				google.latGradi = MyMath::degree(lat);
				google.latMin   = MyMath::minute(lat);
				google.latSec   = MyMath::seconds(lat);
		
				google.lonGradi = MyMath::degree(lon);
				google.lonMin   = MyMath::minute(lon);
				google.lonSec   = MyMath::seconds(lon);
				googleError = false;
				google.lat = lat;
				google.lon = lon;
				googleNameAvailable = true;

				/*if we do not have a name from google do not use google data */
				if (!support->googleName().isEmpty()){
				google.name     = support->googleName().replace("\"","");
				
				}
				else
				{
 				
//  				googleError = true;
// 				localita.name = "";
				google.name     = support->cityLocal();
				
				}
	
				

				
		}
		else
		{
		googleError= true;
		googleNameAvailable = false;
		}
        }
   #ifdef DEBUG
   qDebug()<<"MW ho chiamato updateGoogle...nome="<<
           google.latGradi<<
           google.latMin<<
           google.latSec<<
           google.name<<localita.name<<
           support->googleName().isEmpty()<<
           support->coordinates()<<googleNameAvailable;
    #endif
        /* If there is no name in the italian database use google */

        if (noNameAvailable && !googleError)
        {
                localita.latGradi = google.latGradi ;
                localita.latMin   = google.latMin  ;
                localita.latSec   = google.latSec ;

                localita.lonGradi = google.lonGradi  ;
                localita.lonMin   = google.lonMin  ;
                localita.lonSec   = google.lonSec  ;
                localita.name     = localita.name.isEmpty() ? google.name  : localita.name;
                localita.lat      = google.lat;
           	localita.lon      = google.lon ;
		
      qDebug()<<"MW ho chiamato updateGoogle e aggiornato...nome="<<localita.name<<googleError<<google.name<<noNameAvailable<<localita.lonSec<<localita.latGradi<<localita.latMin<<localita.latSec;
	emit gNameAvailable(localita.name);
        }
	else
		 convertLat(localita);


if (!googleNameAvailable && !bothCoord) {
	if (support)
		support->showWarn(true,tr("<font color=\"orange\">Nessun nome disponibile in Google Map. Ricontrolla le coordinate</font>"));
	}
	else
		support->showWarn(false);
if (googleError || !googleNameAvailable){

 // qDebug()<<"UPDATEGOOEL "<<useLoc<<useLoadedLoc<<bothCoord<<googleError<<googleNameAvailable;
 
        if (support!=0){
            support->showWarn(true,tr("<font color=\"red\">Dati di mappatura non disponibili. Controlla la connessione</font>"));
                useLoadedLoc = true;
                qDebug()<<"UPDATEGOOEL 2"<<useLoc<<useLoadedLoc<<bothCoord<<googleError;
        }

}
	else {
        if (support!=0)
            {
            support->showWarn(false);
            useLoadedLoc = false;
// 	    qDebug()<<"UPDATEGOOEL 3"<<useLoc<<useLoadedLoc<<bothCoord;
        }
        }

	formatCoordinates();
        comuneLat->setText(QString::number(localita.latGradi) +  "<sup>o</sup>"+ QString::number(localita.latMin) + "'" + QString::number(localita.latSec) + "''" + " ("+QString::number(localita.lat)+")" +  "<sup>o</sup>");
        comuneLon->setText(QString::number(localita.lonGradi) + "<sup>o</sup>"+ QString::number(localita.lonMin) + "'" + QString::number(localita.lonSec)+"''"   + " ("+QString::number(localita.lon)+")"+  "<sup>o</sup>");

        comuneLatS->setText(QString::number(localita.lat) +  "<sup>o</sup>");
        comuneLonS->setText(QString::number(localita.lon)+ "<sup>o</sup>");
	
//             qDebug()<<"MW ho chiamato updateGoogle in fondo..lat="<<localita.lat<<localita.lonMin;
        /* put here there result from google */
//      comuneValue->setText("");

	
}
void MainWindow::setNameDiagramPlot(const QString& a)
{
	if (!a.isEmpty()){
                if (w!=0) {
			if ((!noNameAvailable) || googleNameAvailable && !googleError && !(onlyLat||bothCoord) )
				w->setLocName(a);
			else
				w->setLocName(localita.coordinates);
			
// 			w->replot();
		}
	}
}
void MainWindow::reloadCoordinates()
{
        updateFromGoogle();
// 	qDebug()<<"MW reloadCoordintaes";
//         googleNameAvailable = true;
//      getCity();
	/* If no name in the italian database, use google and restart */
	/* It there are bothCord there is no need to redoo all graphs */
       // qDebug()<<"MW I am calling reloadCoordinates"<<localita.name;
	if ((noNameAvailable) && !bothCoord && !onlyLat)
        set(fromGoogle);
}
void MainWindow::setVersion(const QString &v,const QString &vi,const QUrl& a)
        /* This function should be called immediately after the constructor */
        /* and after the reading of settings*/
{
        version = v;
	versionId = vi;
	urlOwner = a;
	updateTitle(projectName);
        //Check for updates automatically
        ch->setVersion(versionId);
        if (checkAtStart)
            ch->doDownload(urlOwner);
	qDebug()<<"MW VERSION "<<version<<versionId;
}
QString MainWindow::normalize(const QString &s)
{
	
	/* Convert a string into the form Yxxxx; for example agropoli --> Agropoli */
	/* or AGROPOLI -->Agropoli */
	QString result,rest,firstChar;
	
	if (s.size()>1)
	{

		firstChar = s.at(0);
		firstChar = firstChar.toUpper();
		
	
		rest = s.mid(1,s.size()-1);
		rest.toLower();

		result = firstChar + rest;
		 
		return result;
	
	}
	else
	{
		 
		return s;
	}
 
}

void MainWindow::convertToDegree(double l,double lon)
{
	/* set the localita coordinates from a decimal value*/
	localita.latGradi = MyMath::degree(l);
	localita.latMin   = MyMath::minute(l);
	localita.latSec   = MyMath::seconds(l);
	
	localita.lonGradi = MyMath::degree(lon);
	localita.lonMin   = MyMath::minute(lon);
	localita.lonSec   = MyMath::seconds(lon);
	qDebug()<<"MW convertToDegreee"<<l<<lon<<localita.latGradi<<localita.latMin<<localita.latSec<<localita.lonGradi<<localita.lonMin<<localita.lonSec;
}
void MainWindow::updateComponentStatus()
{
 	if (energyOut)
		statusLabelEnergy->setText(energyOut->getStatus());
	#ifdef PLUSVERSION
  	if (inverterCheck)
  		statusLabelInverter->setText(inverterCheck->getStatusInverter());
	#else
	if (thisProjectInverter.isValid)
		statusLabelInverter->setText(tr("Inverter = ") + thisProjectInverter.fabric + " - " + thisProjectInverter.model);
	else
		statusLabelInverter->setText(tr("Inverter assente "));
	#endif
		
#ifdef PLUSVERSION2
        updateDetails();
#endif
	

}
void MainWindow::updateStatusBar(const QString &s,const QString& color)
{	
	
	updateComponentStatus();	
	statusLabelWarning->setText(tr("Rad.: ") + s);
	changeColor(*statusLabelWarning,color); 
	statusLabel->setText(tr("Sorgente: ") + source.at(localita.source));
}
void MainWindow::resetStatusBar()
{
	statusLabelInverter->setText("Inverter assente");
	if (energyOut)
	statusLabelEnergy->setText(energyOut->getStatus());
	else
	statusLabelEnergy->setText("-----");
	statusLabelWarning->setText(tr("Rad.: Database"));
        changeColor(*statusLabelWarning,"darkkhaki");
	statusLabel->setText(tr("Sorgente: ") + source.at(localita.source));

}

void MainWindow::resetFlags()
{
        doNotSetCity     = false;
        loadedProject    = false;
        doNotUpdatePower = false;
	myplotpresent    = false;
	useLoc		 = false;
	useLoadedLoc     = false;
	wrongCoordinates = true;
	noNameAvailable  = true;
	googleNameAvailable = false;
	googleError = true;
	onlyLat = false;
	bothCoord = false;
	energyPlotPresent = false;
        ombrePresent = false;
        noRadiation = true;
        validForExport = false;
        projectIsDirty = false;
	dailyValuesPresent = false;
        userYearChanged = false;
}
void MainWindow::formatCoordinates()
/* this function create a string from localita */
{
	localita.coordinates=  QString::number(localita.latGradi) + "<sup>o</sup>" + QString::number(localita.latMin) + "'" +    
	QString::number(localita.latSec) + "''," +
	QString::number(localita.lonGradi) + "<sup>o</sup>" + 
	QString::number(localita.lonMin) + "'" + QString::number(localita.lonSec) + "''";
 	
}
 
void MainWindow::computeHourlyValues(int month,int day)
/* This function get the hourly radiation for a specific day*/
/* day is the day in the month */
{
	double v,v2,e,declination, shadow,rb,rb2,r,r2,rrd,rrd2,integral,integralR;
        rbData p,p2;
        QPointF t;
	int doy;

	hourlyRR.resize(0);
	hourlyEO.resize(0);
	v=v2=integralR=integral=e=rrd=rrd2=r=r2=rb=rb2=0;
        p.date.setDate(localita.anno,month,day);
        p.slope    = localita.incl;
        p.rotation = localita.azi;
        p.model = 1; //Collareis-Pereira
        p2 = p;
     //   qDebug()<<"MW userYear"<<userYearChanged<<localita.anno;
        if ( (w!=0) && (reale!=0) )
	{
        if ( (!dailyValuesPresent || userYearChanged)   )
	{
				
				o->setYear(localita.anno);
				if (localita.additionalAzi.size()>0 && localita.additionalIncl.size()>0){

o->computeDailyRad(localita.additionalIncl.at(0)*pi/180,localita.additionalAzi.at(0)*pi/180,localita.anno);

					
					
					omegasHDaily2	= o->getOmegasHDaily();

					HhoDaily2	= o->getHhoDaily();

				}
o->computeDailyRad(localita.incl*pi/180,localita.azi*pi/180,localita.anno);

					omegasHDaily	= o->getOmegasHDaily();
					HhoDaily	= o->getHhoDaily();

				dailyValuesPresent = true;
	}			

        if (userYearChanged)
            userYearChanged = false;
	
		for (int hour=0;hour<24;hour++) {
                        p.hour  = hour;

			shadow      = w->hourlyOmbreFactor(localita.anno,month, day, hour);
			declination = w->getDeclinationPrime( month, day, hour);
			reale->setYear(localita.anno);
			energyOut->setYear(localita.anno);
			reale->setTotalDayLen(o->getTotalDayLen());
			energyOut->setTotalDayLen(o->getTotalDayLen());
			
			doy         = MyMath::dayOfYear(localita.anno,month,day) -1;//from  0 to 364! or 0 to 365
			 
			t  = w->computeSingleValue(hour,month,day,localita.anno) ;// sun position in degree

                switch (localita.tipo) {
                    case 2 :
                                /* DOUBLE FACADE */

                                reale->setOmegasDaily(omegasHDaily);
                                reale->setHhoDaily(HhoDaily);

                                if (t.y()<0.4){
                                        rb = 0;
                                        rb2= 0;
                                }
                                else{
							 
                        rb         = w->getSingleRb(p);
                        p2.slope    = localita.additionalIncl.at(0);
                        p2.rotation = localita.additionalAzi.at(0);
                        rb2  = w->getSingleRb(p2);
							 
                                }
                        rrd = w->getHDiffuseRatio(p);//Collareis-Pereira
                        r   = w->getHGlobalRatio(p, rrd);//Collareis-Pereira
                        rrd2 = w->getHDiffuseRatio(p2);//Collareis-Pereira
                        r2   = w->getHGlobalRatio(p2,rrd);//Collareis-Pereira
						 
                        v = reale->getHourlyH(hour,localita.anno,month,doy, shadow,localita.lat*pi/180,localita.incl*pi/180,declination*pi/180,rb,rrd,r,localita.tipo,pereira);

                        reale->setOmegasDaily(omegasHDaily2);

                        reale->setHhoDaily(HhoDaily2);

                        v2 = reale->getHourlyH(hour,localita.anno,month,doy, shadow,localita.lat*pi/180,localita.additionalIncl.at(0)*pi/180,declination*pi/180,rb2,rrd2,r2,localita.tipo,pereira);
                        e = energyOut->getHourlyValue(localita.area,v/3.6,month,doy) + energyOut->getHourlyValue(localita.additionalArea.at(0),v2/3.6,month,doy);
						 
						
                        break;
                        case 1 :
                        /* TRACKER */
                        reale->setOmegasDaily(omegasHDaily);
                        reale->setHhoDaily(HhoDaily);

                        if (t.y()<0.4)
                                rb = 0;
                        else{
                        p.slope    = 90 - t.y();
                        p.rotation = t.x();
                        rb  = w->getSingleRb(p);
							
                        }
						
                        rrd = w->getHDiffuseRatio(p);//Collareis-Pereira
                        r   = w->getHGlobalRatio(p,rrd);//Collareis-Pereira
                        v = reale->getHourlyH(hour,localita.anno,month,doy, shadow,localita.lat*pi/180,localita.incl*pi/180,declination*pi/180,rb,rrd,r,localita.tipo,pereira);
                        e = energyOut->getHourlyValue(localita.area,v/3.6,month,doy) ;
					break;
					
                        case 0:
                        /* SINGLE FACADE */
                        //qDebug()<<"MW case 0 single "<<HhoDaily.size();
                        reale->setOmegasDaily(omegasHDaily);
                        reale->setHhoDaily(HhoDaily);

                        if (t.y()<0.4)
                                rb = 0;
                        else{
                                rb  = w->getSingleRb(p);
                        }
                        rrd = w->getHDiffuseRatio(p);//Collareis-Pereira
                        r   = w->getHGlobalRatio(p,rrd);//Collareis-Pereira
                        v = reale->getHourlyH(hour,localita.anno,month,doy, shadow,localita.lat*pi/180,localita.incl*pi/180,declination*pi/180,rb,rrd,r,localita.tipo,pereira);
                        e = energyOut->getHourlyValue(localita.area,v/3.6,month,doy)  ;
					break;
					}
 
// 				}
				
				

              				#ifdef DEBUG
				qDebug()<<"MW hourly value hour   tilt="<<v<<v2<<e<<localita.tipo<<doy<<hour<<rb<<t.x()<<t.y()<<v<<e<<shadow<<declination<<dailyValuesPresent;
             				#endif
  //qDebug()<<"MW hourly value hour ="<<hour<<day<<month<<r<<rrd<<rb<<r<<v;
			if (comboCurrentField->currentIndex()==1)
				hourlyRR<<QPointF(hour,v2);
			else
				hourlyRR<<QPointF(hour,v);
	
			hourlyEO<<QPointF(hour,e);
		integral+=e;
		integralR += v;
   				
		}
                  #ifdef DEBUG
   		qDebug()<<"MW total day ee and rad ="<<integral<<integralR ;
                  #endif
		
	
	}
	
	
}
double MainWindow::computeHourlyValue(int month,int day,int hour,int year)
/* Return a particular value of the Energy Yield in a given date an time*/ 
{
        double v,v2,e,declination, shadow,rb,r,rrd,rb2,r2,rrd2;
        rbData p,p2;
        p.hour     = hour;
        p.date.setDate(localita.anno,month,day);
        p.slope    = localita.incl;
        p.rotation = localita.azi;
        p.model    = 1; //Collareis-Pereira
        p2   = p;
	QPointF t;
	int doy;

        rb=v=v2=e=rb2=rrd2=rrd=r=r2=0;



  //       qDebug()<<"MW computeHourlyValue top"<<HhoDaily.size();
        if ( (w!=0) && (reale!=0) )
	{
  	 
        if ( (!dailyValuesPresent)  || somethingChanged() || simYear!=year)

	{
// 				qDebug()<<"MW recompute o->Daily";
				o->setYear(localita.anno);
                                if (localita.additionalAzi.size()>0
                                    && localita.additionalIncl.size()>0)
                                {
                                    o->computeDailyRad(localita.additionalIncl.at(0)*pi/180,localita.additionalAzi.at(0)*pi/180,localita.anno);


                                    omegasHDaily2	= o->getOmegasHDaily();
                                    HhoDaily2	= o->getHhoDaily();
                                    reale->setOmegasDaily(omegasHDaily2);
                                    reale->setHhoDaily(HhoDaily2);

				}
                                o->computeDailyRad(localita.incl*pi/180,localita.azi*pi/180,localita.anno);

					omegasHDaily	= o->getOmegasHDaily();
					HhoDaily	= o->getHhoDaily();
                                        reale->setOmegasDaily(omegasHDaily);
                                        reale->setHhoDaily(HhoDaily);

			dailyValuesPresent = true;

	}				
		
        if (simYear!=year)
            simYear = year;
	
		 
			shadow      = w->hourlyOmbreFactor(year,month, day, hour);
			declination = w->getDeclinationPrime( month, day, hour);
			reale->setYear(year);
			energyOut->setYear(year);
			reale->setTotalDayLen(o->getTotalDayLen());
			reale->setMeanDayLen(o->getMeanDayLen());
			energyOut->setTotalDayLen(o->getTotalDayLen());
			
			doy         = MyMath::dayOfYear(year,month,day) -1;//from  0 to 364! or 0 to 365
			 
			t  = w->computeSingleValue(hour,month,day,year) ;// sun position in degree
				// There are asympots in trackin mode ....to check
// 				if (t.y()<0)
// 					t.setY(0);
	 
                        switch (localita.tipo) {
                        case 2 :
                        /* DOUBLE FACADE */

                        p2.slope    = localita.additionalIncl.at(0);
                        p2.rotation =  localita.additionalAzi.at(0);

						
                        if (t.y()<0.4){
                                rb = 0;
                                rb2= 0;
                        }
                        else{
                                rb  = w->getSingleRb(p);
                                rb2  = w->getSingleRb(p2);
							 
                        }
                        rrd = w->getHDiffuseRatio(p);//Collareis-Pereira
                        r   = w->getHGlobalRatio(p,rrd);//Collareis-Pereira
                        rrd2 = w->getHDiffuseRatio(p2);//Collareis-Pereira
                        r2   = w->getHGlobalRatio(p2, rrd);//Collareis-Pereira
						 
                        v = reale->getHourlyH(hour,localita.anno,month,doy, shadow,localita.lat*pi/180,localita.incl*pi/180,declination*pi/180,rb,rrd,r,localita.tipo,pereira);


						 
                        v2 = reale->getHourlyH(hour,localita.anno,month,doy, shadow,localita.lat*pi/180,localita.additionalIncl.at(0)*pi/180,declination*pi/180,rb2,rrd2,r2,localita.tipo,pereira);
                        e = energyOut->getHourlyValue(localita.area,v/3.6,month,doy) + energyOut->getHourlyValue(localita.additionalArea.at(0),v2/3.6,month,doy); /*in kWh */
						 
						
					break;
                        case 1 :
						
                         /* TRACKER */
						
                        if (t.y()<0.4)
                                rb = 0;
                        else{
                        p.slope    = 90-t.y();
                        p.rotation = t.x();
                        rb  = w->getSingleRb(p);
                        }
                        rrd = w->getHDiffuseRatio(p);//Collareis-Pereira
                        r   = w->getHGlobalRatio(p,rrd);//Collareis-Pereira
                        v = reale->getHourlyH(hour,localita.anno,month,doy, shadow,localita.lat*pi/180,localita.incl*pi/180,declination*pi/180,rb,rrd,r,localita.tipo,pereira);
                         e = energyOut->getHourlyValue(localita.area,v/3.6,month,doy); /*in kWh */
					break;
					
                        case 0:
                    /* SINGLE FACADE */


                    if (t.y()<0.4)
                        rb = 0;
                    else{
                    rb  = w->getSingleRb(p);
                    }
                    rrd = w->getHDiffuseRatio(p);//Collareis-Pereira
                    r   = w->getHGlobalRatio(p,rrd);//Collareis-Pereira
                    v = reale->getHourlyH(hour,localita.anno,month,doy, shadow,localita.lat*pi/180,localita.incl*pi/180,declination*pi/180,rb,rrd,r,localita.tipo,pereira);/*in MJ*/
                     e = energyOut->getHourlyValue(localita.area,v/3.6,month,doy) ; /*in kWh */
					 
                     break;
                     }
					
                if (e<0) {
					qDebug()<<"MW hourly value hour  DEBUG tilt="<<localita.tipo<<doy<<hour<<rb<<t.x()<<t.y()<<v<<e<<shadow<<declination<<dailyValuesPresent;
					exit(-1);
				}
                                #ifdef DEBUG
				qDebug()<<"MW hourly value hour   tilt="<<localita.tipo<<doy<<hour<<rb<<t.x()<<t.y()<<v<<e<<shadow<<declination<<dailyValuesPresent;
                                #endif
                                //qDebug()<<"MW hourly value hour ="<<hour<<day<<v<<e;
    			 


                                return e;
 
			 
   				
		 
		 
	}
	else
        return 0;
}
void MainWindow::yearChanged(int i)
{
    userYearChanged = true;
    qDebug()<<"MW yearChanged"<<userYearChanged;
}

void MainWindow::changeDays()
{
	localita.anno = annoValue->value();
        if (selectDay!=0){
		selectDay->clear();
		selectDay->addItems(MyMath::stringSerie(1,MyMath::monthEnd(selectMonth->currentIndex()+1,localita.anno)));
		selectDay->setCurrentIndex(0);
//  		qDebug()<<"MW changeDays"<<selectDay->currentIndex();
		
	}
}
void MainWindow::dayChanged(int day)
{
	if (day>=0) {
// 		qDebug()<<"MW dayChanged noRadiation"<<noRadiation<<selectDay->currentIndex();
		QPolygonF a;
		if (!noRadiation)
		{
	// 	computeHourlyValues(selectMonth->currentIndex()+1,selectDay->currentIndex()+1);
	// 	hourlyPlot->setHourlyData(hourlyRR);
	// 	hourlyEOPlot->setHourlyData(hourlyEO);
	// 	hourlyPlot->draw(1);
	// 	hourlyEOPlot->draw(1);
		drawHourlyValues();
		}
		else
		{
			hourlyPlot->draw(0);
			hourlyEOPlot->draw(0);
		}
	}

}
int MainWindow::numPanels()
{
    return numPanels(areaValue->value());
}
int MainWindow::numPanels2()
{
    return numPanels(areaValue2->value());
}
int MainWindow::numPanels(double a)
{
if (thisProjectPanel.isValid){
	 if (thisProjectPanel.H>0 && thisProjectPanel.L>0){
                 return ((int)ceil( (a*1000000.0)/(thisProjectPanel.H*thisProjectPanel.L))); /*H and L  in mm */
                qDebug()<<"MW numPanels"<<a<<(a*10000)/(thisProjectPanel.H*thisProjectPanel.L);
		}
	else
		return 0;
	}
	
else 
	return 0;
}
void MainWindow::changeNumPanels2(double a)
/* Change the num of panels based on the area a*/
{ 
	
		if (thisProjectPanel.isValid)
			numOfPanelsValue2->setText(QString::number(numPanels(a)));
		else
			numOfPanelsValue2->setText(QString(tr("<font color=\"red\"> pannello assente </font>")));
	
}
void MainWindow::changeNumPanels(double a)
/* Change the num of panels based on the area a*/
{ 
	
		if (thisProjectPanel.isValid)
			numOfPanelsValue->setText(QString::number(numPanels(a)));
		else
			numOfPanelsValue->setText(QString(tr("<font color=\"red\"> pannello assente </font>")));
	
}
void MainWindow::updateLimitDistance(double swap,double incl)
{
	double temp,elev;
	int month;
	month = w->lowestMonth(localita.lat);
        elev  = w->computeSingleValue(10,month,localita.anno).y()*pi/180;

        setWindowModified(true);
        if (!myplotpresent)
        {
            limitDistanceValue->setText(QString(tr("<p><font color=\"red\"> sito assente</font>"))) ;
        return;
            }

	if (swap==1){
	temp = thisProjectPanel.H;
	thisProjectPanel.H = thisProjectPanel.L;
	thisProjectPanel.L = temp;
	}
	if ((thisProjectPanel.isValid) && w && (localita.tipo==0)) {
		
		limitDistance = thisProjectPanel.H*sin((pi/180)*incl) / (tan( elev ) ) + thisProjectPanel.H*cos(incl*(pi/180));
                qDebug()<< limitDistance<<elev<<thisProjectPanel.H<<thisProjectPanel.L<<incl;
		limitDistanceValue->setText(QString::number(limitDistance));
		}
	if (localita.tipo==1){
			limitDistance = 1000*((mountingHeightValue->value() + trackDimValue->value()/(2*cos(elev) )) / (tan(elev)) + trackDimValue->value()/2 * sin(elev));
                        limitDistance = std::isnan(limitDistance) ? 0 :limitDistance;

			limitDistanceValue->setText(QString::number(limitDistance));
                //qDebug()<<"MW limit distance"<< limitDistance<<elev<<thisProjectPanel.H<<thisProjectPanel.L<<incl<<elev<<trackDimValue->value()<<mountingHeightValue->value();
}
		
}
void MainWindow::updateLimitDistance(double incl)

{
        localita.trackerArea = trackDimValue->value();
        projectIsDirty = true;
	updateLimitDistance(0,incl);
}
void MainWindow::updateLimitDistance()

{
        updateLimitDistance(0,localita.incl);
}
void MainWindow::swapLimitDistance()
{
    updateLimitDistance(1,localita.incl);
}
void MainWindow::simulateNew()
{
        int r = QMessageBox::question(this,tr("Nuova simulazione energetica"),tr("Avvio una nuova simulazione energetica?"),QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Cancel	);
	
	if (r== QMessageBox::Ok){

		simulate(energetics);
                firstPassDone = true;
	}
	
}

void MainWindow::simulateNewEco()
{
        int r = QMessageBox::question(this,tr("Nuova simulazione economica"),tr("Avvio una nuova simulazione economica?"),QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Cancel	);
	
	if (r== QMessageBox::Ok){
		
		simulate(economics);
	}
	
}
void MainWindow::simulate(int mode)
/* Perform the simulation of a certain number of years*/
{
#ifdef PLUSVERSION
        double eps=0.0000002;
        int anni,year,em,err,k,dayCount,npvMode;
        double credit,inflow,outflow,e,c,cumRataNPV,amm,tempE,es[24],scale,vei_;
        double initCB,einjected_,deprec,tasse,mon,tassato,trace;
        QVector<double> temp;
        QPolygonF eiToPlot,eprToPlot,OE,CUSorCor,IVA,IRPEF,IRES,IRAP,NETTO,
                  Eimmessa,Eprelev,TASSE,vEi;
        QProgressDialog progress;
        ecopara param;
        bool inflated = true;

	
		
                param = ecoVal->getEcoParameters();
                trace = 0;
                err   = 0;
                tasse = 0;
                deprec= 0;
                eprod.reserve(8784);
                if ((ecoVal!=0 && ecoVal->bandError()) && mode==economics &&
                    param.regime!=Vendita)
				err +=1;
                qDebug()<<"MW ERROR?"<<err;

                if ((ecoVal!=0) && (!noRadiation) && (thisProjectPanel.isValid) && err<1) {
			

                        ecoVal->setInstalledPower(thisProjectPanel.pnom * numPanels(localita.area)/1000);
			ecoVal->checkBands();
			
  			anni = ecoVal->dPeriodo->value();
                        progress.setLabelText(tr("Simulazione avviata...attendere"));
                        progress.setCancelButton(new QPushButton(this));
                        progress.setCancelButtonText(tr("Ferma simulazione"));
			progress.setWindowModality(Qt::WindowModal);
                        progress.setMaximum(anni);
	 		progress.setMinimum(0);
		
		
			year = localita.anno;
			credit = 0;
			/* Compute one-shot prediction of energy prices */
//     			ecoVal->processEnergyPrices(anni);
// 			for (int i=0;i<anni;i++) {
// 			year +=i;
			
			/*Build tables: Compute values for the first year */
			/* Only for the first year. We assume subsequent years similar*/
			 
                      //  qDebug()<<"MW simulate"<<firstPassDone;
                        /* Only for the first year. We assume subsequent years similar*/
                        if ( (firstPassDone == false) || mode==energetics)
                        {
                            resetEnString();
                            progress.setMaximum(12*31*24);
                            if (mode==energetics)
                                progress.setLabelText( tr("Nuova simulazione energetica avviata...")) ;
                            if (mode==economics)
                                progress.setLabelText( tr("Generazione dati energetici orari...")) ;

                            eprod.resize(0);

                            k=0;
                            dayCount = 1;



                       for(int month=0;month<12;month++) {

                         trace = 0;
                         if (progress.wasCanceled())
                         return;
                          progress.setValue(month*31*24);
                          em = MyMath::monthEnd(month+1,2004);

                          //month from 1 to 12. Default year = 366
                          scale=1;
                       for(int day=1;day<=em;day++) {

                          tempE = 0;
                        if (dayCount==MyMath::refDay(month))
                          energString +="<tr><td>" + MyMath::months(month+1) + "</td>";
                          if (otherLosses.scaling){
                              // Get total for the current day
                             for(int hour=0;hour<24;hour++){

                                  es[hour] = computeHourlyValue(month+1,day,hour,year);

                                tempE += es[hour];/*in kWh*/
                             }
                         scale = (Energy[month]/MyMath::monthEnd(month+1,year))/tempE;
                          }
                          else
                         scale = 1;

                            /***************/
                            /* HOURS CYCLE */
                            /***************/
                              for(int hour=0;hour<24;hour++){
                                  if (!otherLosses.scaling){
                                      //qDebug()<<"MW time"<<month<<day<<QTime::currentTime().msec();
                                 es[hour] = computeHourlyValue(month+1,day,hour,year);



                             }

                                 e = es[hour] * scale;
                                 trace+=e;
                                 eprod << e ; /*produced*/

                                 if (dayCount==MyMath::refDay(month))
                                   if (e>0.000000002)
                                    energString +="<td style=\"background-color : #56ab1e;\">" + QString("%L1").arg(e,0,'f',1) + "</font></td>";
                                   else
                                    energString +="<td>" + QString("%L1").arg(e,0,'f',2) + "</td>";
// 						
                                   if (std::isnan(e)) {
                                   qDebug()<<"MW simulate iterations first pass....................."<<k<<eprod.at(k)<<e;
                                   return;
                               }
                                  if (e<0){
                                  qDebug()<<"EPROD NEGATIVE..."<<k<<e<<month<<day<<hour<<year<<scale;
                                  QMessageBox::critical(this,tr("Errore"),tr("<p>L'energia prodotta &egrave; negativa. Qualche problema interno o di configurazione.</p>"));
                                  return;
                                  }
                                  k++;
                                  }
                                  if (dayCount==MyMath::refDay(month))
                                        energString +="</tr>";
                                        dayCount++;
                                }
						

  //qDebug()<<"MW month end in sim eprod"<<month<<em<<trace;
                        }

				firstPassDone = true;
                                qDebug()<<"MW time END SIM......"<<QTime::currentTime().toString()<<firstPassDone;
                                energString+="</table><p>" + tr("Dati simulati")+ + "</p><p>" + tr("Valori in kWh") + "</p>" ;

				updateHourlyTable();

                                decorateTab(innerTabEO,tabWidget,2,2,0);

                                progress.reset();
                                progress.setMaximum((1+anni)*12);
                                progress.setLabelText( tr("Generazione dati economici..."));
				
//   				qDebug()<<"MW energyString"<<energString;
				}
				else	{

                                        progress.setMaximum(12*(anni+1));
					progress.setLabelText( tr("Aggiornamento simulazione precedente..."));
					}

				if (mode==economics)
				{


                                        /**********************************/
                                        /* Start econ cycle over all the years */
                                        /**********************************/
                                        double ei_,eprod_,epr_,opr_,ec_,reduction,
                                        r,cumEprod_,raw,npv,interest,interestNPV;
                                        double consumed_,eprv_,savingsEn_,
                                               selfconsumed_,fixedCosts,
                                               costs,yearlyLoan,sgravi,interestReduction;


                                        int numBands = ecoVal->getNumBands();
                                        int bIndex;
                                        QVector<double> consumedBands,fetchedBands,injectedBands;
                                        injectedBands.fill(0,numBands);
                                        consumedBands.fill(0,numBands);
                                        fetchedBands.fill(0,numBands);




                                        /* Check the validity of ecopara */
                                        if (!sanityCheck(param))
                                            return;

                                        if ((cash!=0))
                                            cash->setEcoParameters(param);

                                        ei_=eprod_  =epr_       =opr_=inflow=ec_=
                                            interest=interestNPV=cumRataNPV =
                                            sgravi  =costs      =yearlyLoan=
                                            interestReduction=0;
					r = thisProjectPanel.gar;
                                        /********************/
                                        /*Prepare some data */
                                        /********************/
                                        // ammortamento is a % //
                                        amm = param.ammortamento*param.initialCost/100;
                                        initCB = param.initialCost -
                                        - ecoVal->getTaxVatReduction() -
                                        param.bonusPerkWp*installedPower() -
                                        (param.initialCost-param.loan)*
                                        param.benefitInitialCost/100;

                                        //npv = raw ;
					ecoVal->computeLoan();
// 					double csx[anni],csy[anni];
					/* Year of start */

//qDebug()<<"MW pedaggio"<<param.pedaggiokWh;

                                        CS.resize(0);
                                        RawCash.resize(0);
                                        NPV.resize(0);
                                        Interest.resize(0);
                                        InterestNPV.resize(0);
                                        Rata.resize(0);
                                        RataNPV.resize(0);
                                        consumedEn.resize(0);
					yearlyEprod.resize(0);
					yearlyCost.resize(0);
					yearlyCostNPV.resize(0);
					consumedEn.resize(0);
                                        selfConsumed.resize(0);
					BN.resize(0);
					CS.resize(0);
                                        CREDIT.resize(0);
                                        CUSorCor.resize(0);
                                        OE.resize(0);
                                        CEI.resize(0);
					AmmNPV.resize(0);
                                        Amm.resize(0);
                                        SavingsEn.resize(0);
                                        Eimmessa.resize(0);
                                        Eprelev.resize(0);
                                        IVA.resize(0);
                                        IRAP.resize(0);
                                        IRES.resize(0);
                                        IRPEF.resize(0);
                                        NETTO.resize(0);
                                        TASSE.resize(0);


					
                                       // loadInterface->saveState();
                                        double dec_ = 0;
                                        double ecYear=0;
					for (int i=1;i<=anni;i++){

                                            consumedBands.fill(0,numBands);
                                            fetchedBands.fill(0,numBands);

                                            if (progress.wasCanceled())
							
							break;

						k=0;
						Ei.resize(0);
						Epr.resize(0);
                                                vEi.resize(0);


						Eprod.resize(0);
						

						reduction = i>0 ? (1-r*i/100) : 1;

						year =localita.anno + i;
                                                consumed_= cumEprod_=c=0;
                                                selfconsumed_ = 0;
                                                savingsEn_    = 0;
                                                opr_          = 0;
                                                dec_    = 0;
                                                ecYear  = 0;
                                                trace   = 0;

                                                for(int month=0;month<12;month++)
                                                {
                                                    injectedBands.fill(0,numBands);
                                                    epr_=ei_=opr_=tempE=eprv_=0;
                                                    vei_    = 0;
                                                     einjected_ = 0;
                                                    progress.setValue(12*i + month);
                                                    em =
                                                            MyMath::monthEnd(month+1,year);
                                                    /*Anno non bisestile? Salta il 29 Feb*/
                                                    if (month==1 && em!=29)
                                                        k = k+24;

                                                    tempE = 0;
                                                    for(int day=1;day<=em;day++) {
                                                        for(int hour=0;hour<24;hour++){


                                                            c = loadInterface->getHourlyLoad(year,hour,day,month+1);
                                                            //qDebug()<<"MW loca"<<c<<year<<hour<<day<<month+1;
                                                            if (c<=0.00000000002)
                                                            {
                                                                c=0;
                                                            }

                                                            //Energy produced and reduced by time
                                                            eprod_ = reduction* (eprod.at(k));

                                                            dec_ += c;
                                                            ec_    = c;
                                                            //Load

                                                            // Injected cumulant
                                                            ei_   += (eprod_-ec_) >eps ? eprod_-ec_ : 0;
                                                            // Injected for this months
                                                            einjected_ = (eprod_-ec_) >eps ? eprod_-ec_ : 0; ;

                                                            epr_   = (eprod_-ec_)>eps ? 0          : ec_-eprod_;// Fetched ener.
                                                            //opr_  += epr_ *enPr;// Monetary value of fetched ener.
                                                            eprv_ += epr_;
                                                            cumEprod_ += eprod_;
                                                            // Produced energy in one year in kWh

                                                            selfconsumed_ = (eprod_ - ec_)>eps ? ec_ : eprod_; // Self-consumed

                                                            bIndex =
                                                                    ecoVal->getBandsId(hour,month,day,year);

                                                            consumedBands[bIndex] += selfconsumed_;
                                                            fetchedBands[bIndex]  += epr_;
                                                            injectedBands[bIndex] +=  einjected_;


                                                            consumed_  += selfconsumed_;
                                                            //consumed energy in one year
                                                            // paydMonth_     += epr_ * enPr;
                                                            //consumed energy in one month
                                                            ecYear+=c;
                                                            tempE += eprod_;
                                                            trace += eprod.at(k);
                                                            // 							/*****DEBUG***/
                                                            if (std::isnan(eprod_)) {
                                                                qDebug()<<"MW simulate iterations cycle........"<<k<<eprod.at(k);
                                                                exit(-1);
                                                            }
                                                            if (eprod_<0){
                                                                qDebug()<<"MW simulate iterations cycle eprod NEGATIVE........"<<k<<year<<month<<day<<hour<<eprod.size()<<reduction<<eprod_;
                                                                exit(-1);
                                                            }

                                                            k++;
                                                        }

                                                    }
               /**************** End of month *********************/
                    /* i = current year, 0,1,2....*/
                                                    for(int ib=0;ib<numBands;ib++)
                                                    {
                                                        vei_   +=
                                                        ecoVal->getInjectedPrice(ib,month,i)*
                                                        injectedBands[ib]/100;
         // qDebug()<<"MW vei "<< month<<injectedBands[i]/100<<ecoVal->getInjectedPrice(i,month,year);
                                                    }

                                           //       qDebug()<<"MW eco sim end of month"<<month<<trace<<tempE<<vei_;
                                                    Epr    <<QPointF(i,eprv_);
                                                    Ei     << QPointF(i,ei_);

                                                    // Valorizzazione nel mese dell'en. immessa per Fasce
                                                    vEi    << QPointF(i,vei_);
                                                    //Opr    <<QPointF(i,opr_);
                                                    Eprod  <<QPointF(i,tempE);



						}
 /* End of the current year. 12 values ready ********************************/

                              // Calcola il totale della prelevata //
                               opr_ = ecoVal->getYearlyEnergyCost(fetchedBands,i)*
                                      (1+param.VATonTotEnergy/100);
                                qDebug()<<"MW fetched"<<fetchedBands<<opr_<<ei_;

                              // Calcola il risp. in bolletta//
                                savingsEn_ =
                                ecoVal->getYearlyEnergyCost(consumedBands,i) +
                                        ecoVal->weightedSumTariffekWh(consumed_,i);
                                  qDebug()<<"MW consumed"<<consumedBands<<consumed_ ;

                              ///////////////////////////////


qDebug()<<"MW fixed";

                              //Calcola contributi di regime //
                               fixedCosts = ecoVal->getMonthlyTaxOnEn(i,eprv_);

                               /* 1         = contribute in unit value*/
                               /* 2         = Cei*/
                               /* 3	     = credit for next year            */
                               /* 4         = Exchanged energy                 */
                               /* 5	     = Bonus*/
                               /* 6         = Oe*/
                               /* 7         = Cus or cost/earn from sellings */
                               /* 8         = Injected Energy * k           */
                               /* 9         = Used credit or sold credit    */
 //qDebug()<<"MW fixe cost"<<fixedCosts<<eprv_;
                               temp =ecoVal->getContribute(
                                       Eprod,Epr,Ei,vEi,opr_,fixedCosts,credit,i);
qDebug()<<"MW vei"<<vEi;
                               temp.replace(4,temp.at(4)*cumEprod_);
                                inflow =temp.at(0) + temp.at(4)  + savingsEn_;
                              ///////////////////////////////

                                  // Liquidazione credito?
                                if (param.credit && param.regime==SSPIT)
                                 inflow += temp.at(8);



                    //Ammortamento
                    deprec = ecoVal->getDepreciation(i);
                    //Costi annuali
                    costs  = ecoVal->getYearlyCost(i,inflated) +
                             ecoVal->getFreqCosts(i,inflated);

                    //Tasse sui redditi - gli interessi e ammortamenti
                    // Secondo Iacovoni va messa la bolletta
                    tasse             = ecoVal->getTaxes(temp);
                    interestReduction = ecoVal->getYearlyTaxReductionOnInterest(i);
                    sgravi= (param.benefitTaxes/100)*
                            (deprec +  costs + savingsEn_ +  MyMath::inflate(i,param.inflRate/100,param.pedaggiokW+param.pedaggio ));

                                     Eprelev <<   QPointF(i,MyMath::cumSum(Epr));
                                     Eimmessa<<   QPointF(i,temp.at(7));
                                     OE      <<   QPointF(i,temp.at(5));
                                     CUSorCor<<   QPointF(i,temp.at(6));
                                     CS      <<   QPointF(i,temp.at(0));
                                     CEI     <<   QPointF(i,temp.at(1));
                                     CREDIT  <<   QPointF(i,temp.at(8));//used credit
                                     BN      <<QPointF(i,temp.at(4));
                                     IVA   <<QPointF(i,ecoVal->getIva(temp));
                                     IRPEF   <<QPointF(i,ecoVal->getIrpef(temp));
                                     IRES   <<QPointF(i,ecoVal->getIres(temp));
                                     IRAP   <<QPointF(i,ecoVal->getIrap(temp));
                                     TASSE  <<QPointF(i,tasse-sgravi-interestReduction);
                                     outflow = ecoVal->getYearlyCost(i,inflated) +
                                               ecoVal->getFreqCosts(i,inflated) +
                                               ecoVal->getYearlyAssic(i,inflated);


						
                                     eiToPlot<<QPointF(i,MyMath::cumSum(Ei));
                                     eprToPlot<<QPointF(i,MyMath::cumSum(Epr));

                                     //Credit for the next year
                                     if (!param.credit)
                                         credit += temp.at(2);
                                     else
                                         credit = 0;


                                      npvMode = 1;
                                     interest    = ecoVal->getYearlyInterest(i); //the interet amount of borrowed capital
                                     interestNPV = ecoVal->getYearlyInterestNPV(i,npvMode );// the actual value of the borrowed capital
                                     cumRataNPV += ecoVal->getYearlyLoanNPV(i);
                                     //
                                     raw = inflow-outflow  ;
                                     //                                                npv =ecoVal->getNPVFactor(inflow-outflow,i) - ecoVal->getYearlyLoanNPV(i) + ecoVal->getYearlyTaxReductionOnInterestNPV(i) + ecoVal->getDepreciationNPV(i) - ecoVal->getYearlyAssicNPV(i);
                                     mon     = raw - deprec;

                             /* VAN CALCOLATO SUI FLUSSI DI CASSA NETTI, ovvero
                             senza ammortamenti (?)*/


                             yearlyLoan = ecoVal->getYearlyLoan(i);
                             if (i>1) {
        // npv = ecoVal->getNPVFactor(inflow-outflow-tasse+sgravi
                                   // - yearlyLoan,i,npvMode)
                                  //  - ecoVal->getYearlyAssicNPV(i,npvMode);
           npv = ecoVal->getNPVFactor(inflow-outflow-
                                      tasse+sgravi,i,npvMode)
                                      - ecoVal->getYearlyAssicNPV(i,npvMode)
                                      + interestNPV;

         //tassato = raw - tasse + sgravi -
                   //ecoVal->getYearlyLoan(i);
           tassato =  raw - tasse + sgravi + interestReduction - yearlyLoan;
     }

      else{
//         npv = -initCB + ecoVal->getNPVFactor(inflow-outflow-tasse+sgravi
//                                    - yearlyLoan,i,npvMode)
//                                    - ecoVal->getYearlyAssicNPV(i,npvMode);
           npv = -initCB + ecoVal->getNPVFactor(inflow-outflow-
                                      tasse+sgravi,i,npvMode)
                                    - ecoVal->getYearlyAssicNPV(i,npvMode) + interestNPV;

//         tassato = -initCB + raw - tasse + sgravi -
//                   ecoVal->getYearlyLoan(i);
           tassato = (param.loan-param.initialCost)*
                     (1-param.benefitInitialCost/100)
                     + raw - tasse + sgravi + interestReduction - yearlyLoan;

     }
  //qDebug()<<"MW tassat"<<tassato<<param.loan<<param.initialCost<<param.initialCost<<raw<<tasse<<sgravi<<yearlyLoan<<interestNPV<<npv<<ecoVal->getNPVFactor(inflow-outflow-                                                                                                                                                      tasse+sgravi,i,npvMode)<<ecoVal->getYearlyAssicNPV(i,npvMode)<<interestNPV;

                             RawCash <<QPointF(i,raw );
                             yearlyCost<<QPointF(i,outflow);
                             yearlyCostNPV<<QPointF(i,ecoVal->getNPVFactor(outflow,i,npvMode));
                             NPV     <<QPointF(i,npv);
                             Rata   << QPointF(i,yearlyLoan);
                             RataNPV<<QPointF(i,ecoVal->getYearlyLoanNPV(i));
                             Interest <<QPointF(i,interest);
                             InterestNPV<<QPointF(i,interestNPV);
                             yearlyEprod<<QPointF(i,cumEprod_);
                             consumedEn<<QPointF(i,consumed_);//selfconsumed energy
                             AmmNPV<<QPointF(i,ecoVal->getDepreciationNPV(i));
                             Amm<<QPointF(i,deprec);
                             SavingsEn<<QPointF(i,savingsEn_);
                             NETTO<<QPointF(i,tassato);



                         }

                                        /* end of simulation */
                                        //loadInterface->reloadSavedState();

                                        cash->setFinVat(ecoVal->finWithVat());

                          if (!otherLosses.scaling)
                                            cash->setWarnings(
                          tr("<p>Attenzione: scaling non abilitato") +
                          "<br/>"+
                          tr("Fattore di perdita energia immessa ") +"=" +
                          QString::number(param.tariffe[19].at(0)) + "</p>");
                                        else
                                            cash->setWarnings(
                          tr("<p>Scaling abilitato") +
                          "<br/>"+
                          tr("Fattore di perdita energia immessa ") +"=" +
                          QString::number(param.tariffe[19].at(0)) + "</p>");
                                        cash->setFetched(Eprelev);
                                        cash->setTasse(TASSE);
                                        cash->setIVA(IVA);
                                        cash->setIrpef(IRPEF);
                                        cash->setIrap(IRAP);
                                        cash->setIres(IRES);
                                        cash->setNetto(NETTO);
                                        cash->setInjected(Eimmessa);
                                        cash->setCUSorCor(CUSorCor);
                                        cash->setOE(OE);
                                        cash->setYearlyCostNPV(yearlyCostNPV);
                                        cash->setYearlyCost(yearlyCost);
                                        cash->setRata(Rata);
                                        cash->setRataNPV(RataNPV);
                                        cash->setProduced(yearlyEprod);
                                        cash->setSelfConsumed(consumedEn);
                                        cash->setBonus(BN);
                                        cash->setCS(CS);
                                        cash->setCredit(CREDIT);
                                        cash->setCei(CEI);
                                        cash->setInterest(Interest);
                                        cash->setInterestNPV(InterestNPV);
                                        cash->setRawCash(RawCash);
                                        cash->setNPV(NPV);
                                        cash->setAmmNPV(AmmNPV);
                                        cash->setAmm(Amm);
                                        cash->setSavingsEn(SavingsEn);//money saved for not paying the electric bill
                                        //
                                        cash->drawFlowCash(1);
                                        cash->drawNPV(1);


                                       // cash->toggleInterestPlot(toggleInterest->checkState());
                                        // cash->drawInterest(1);
                                        // cash->drawInterestNPV(1);
				
					/* Copy data to tables*/
                                         cash->drawRata(1);
                                         cash->updateTable();
                                         ecoTablePresent = true;

				}
				else
					return;	
	// 			ecoVal->drawCS(csx,csy,anni);
		}
		else
		{
			switch (err){
			case 1:
                                QMessageBox::warning(this,tr("Prezzi orari energia"),tr("<p>Dati orari del costo dell'energia mancanti o errati. Controlla dal menu<br/> Strumenti->Configura parametri economici</p>"));
                                qDebug()<<"MW error"<<err<<ecoVal->bandError();
			break;
			
			}
			if (noRadiation)
                                QMessageBox::warning(this,tr("Dati radiazione"),tr("Nessun dato di radiazione presente. Hai selezionato un sito?"));
			if (!thisProjectPanel.isValid)
                                QMessageBox::warning(this,tr("Pannello assente"),tr("Nessun pannello fotovoltaico selezionato. Non posso generare i dati energetici senza un pannello. Sceglierne uno dal menu Strumenti."));
		}
// 			
		
		
	#endif
}


    void MainWindow::drawRefCurve()
{
// 	double gain;
	
        if (reale!=0){
		
		if (!refCurveShown){
			tiltButton->setText(tr("Nascondi"));
			if (!noRadiation){
			reale->viewRefCurve(true);
			reale->drawRefCurve(1);
			}
			
// 			gain = (noRadiation==false) ? MyMath::cumSumMonthly(reale->getHref(),12) : 0;
// 			gain = 100*(gain - localita.radRealeOmbreAnnuaTotale)/localita.radRealeOmbreAnnuaTotale;
// 			gainValue->setText(QString::number(gain)+" %");
			refCurveShown = true;
			
		}
		else{
			tiltButton->setText(tr("Visualizza"));
			if (!noRadiation)
				{
				reale->viewRefCurve(false);
				reale->drawRefCurve(0);
				}
			refCurveShown = false;
// 			gainValue->setText("0 %");
		}
	}
		

}    
	
 
void MainWindow::paintEvent(QPaintEvent * /* event */)
{
/*	
// 		italiaData->setVisible(showItalia);
	if (localita.source==radEnea){
	if (bF)
		bF->close();

		bF = new FaderWidget(italiaData);
		 bF->start(showItalia);
	}
	
*/

}
 void MainWindow::fadeInWidget(int start)
{ 

// italiaData->setVisible(start);
// showItalia = start;

//THIS DOES NOT WORK
if (localita.source==radEnea){
	if (bF)
		bF->close();

		bF = new FaderWidget(pagesWidget->widget(start));
                bF->start();
 }
	
}
void MainWindow::createCheckInverter()
{
#ifdef PLUSVERSION
  	if (inverterCheck && !noRadiation && o){
		inverterCheck->setDatabase(databasePanelsId);
  		inverterCheck->setInverter(thisProjectInverter);
 		inverterCheck->setPanel(thisProjectPanel);
		if (localita.additionalArea.size()>0)
		inverterCheck->setNumPanels(numPanels(localita.area) + numPanels(localita.additionalArea.at(0)));
		else
		inverterCheck->setNumPanels(numPanels(localita.area));

 		inverterCheck->setThermalModel(otherLosses.thermalModel);
		inverterCheck->setRad(HinclOmbre,reale->getUnit());
		inverterCheck->setAddRad(HinclOmbre2,reale->getUnit());
 		inverterCheck->setMeanDayLen(o->getMeanDayLen());
 	 	inverterCheck->setWind(windDaily);
 		inverterCheck->setMounting(mountingValue->currentIndex(),mountingHeightValue->value());
 		QVector<double> t;
 		t<<localita.tempMin<<localita.tempMax;
 		inverterCheck->setTemp(t);
		inverterCheck->checkAll();
	updateComponentStatus();
  	}
#endif
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    /* 2 = NO
       3 = CANCEL
       1 = YES
    */
	int a;
        writeSettings();
if (projectIsDirty)
	{
                a = ask(tr("Attenzione"),tr("Vuoi salvare le modifiche?"));
                if (a==  1){
			QSqlDatabase::removeDatabase("panels");
			save();	
		
		}
                if (a== 3) {
			event->ignore();
                        //qDebug()<<"MW CLOSE ignore";
                        return;
                    }
			

		 
	}
// Close all windows
#ifdef PLUSVERSION
if (ch!=0)
    ch->close();

if (ecoVal!=0)
    ecoVal->close();

if (loadInterface!=0)
    loadInterface->close();
#endif
	 
event->accept();
QCoreApplication::quit();
	 
 
	
}

void MainWindow::prepareNasaGlob(QProgressBar &p,int v)
{
	QString s, sLat,sLon,keyl,key;
 	QStringList splitted ;
	int count=0; 

	
	QFileInfo nasaFile(globalNASAFile);
	if (!nasaFile.exists()){	
			 
			return ;
	}
	else
	{
		p.setValue(v);
		QFile file(globalNASAFile);
		if (file.open(QIODevice::ReadOnly)){
			QTextStream in(&file);
			while (!in.atEnd()) {
			s = in.readLine();
				s = s.simplified();
				splitted = s.split(" ");
				p.setValue(v+count++);
				if (splitted.size()>=38){
					sLat = splitted.at(0);
					sLon = splitted.at(1);
					splitted.removeFirst();
					splitted.removeFirst();
// 					insertNasaDatabase(sLat.toInt(),sLon.toInt(),splitted,1);//insert temp data into datiEnea.db
					 
                                        keyl = sLat + ",0,0," + sLon+",0,0";//NASA DATA do not contains decimal values!
 					for(int i=0;i<12;i++) {
 						key = keyl + "," + QString::number(i); 
 						nasaRad[key] = splitted.at(i).toDouble();
					}
					for(int i=12;i<24;i++) {
 						key = keyl + "," + QString::number(i); 
 						nasaTemp[key] = splitted.at(i).toDouble();
					}
					for(int i=24;i<36;i++) {
 						key = keyl + "," + QString::number(i); 
 						nasaWind[key] = splitted.at(i).toDouble();
					}
				}
						


			}
		}
	}
}
void MainWindow::updateHourlyTable()
{
        if (energySummary!=0)
		energySummary->setHtml(energString);

}
void MainWindow::resetEnString()
{
#ifdef PLUSVERSION
energString = "<table style=\"font-size : 11px;\" border=1 width=\"100%\" cellspacing=\"0\" cellpadding=\"3\" bordercolor=\"#980000\" >"
		      "<tr  bgcolor=\"#C89800\"><td >" + tr("Mese") + "</td>" + MyMath::serieCellTable(0,24)+ "</tr>" ;
energySummary->setHtml("");
#endif

}
void MainWindow::enableScaling(int state)
{
	if (state==Qt::Checked){
		otherLosses.scaling = true;
		
	}
	else
	{
		otherLosses.scaling = false;
		
	}

        if (!noRadiation){
	if (selectMonth->currentIndex()<12){
		hourlyPlot->setMode(otherLosses.scaling,HinclOmbre[selectMonth->currentIndex()]);
                hourlyPlot->setTime(selectMonth->currentIndex()+1,selectDay->currentIndex()+1);
		hourlyEOPlot->setMode(otherLosses.scaling,Energy[selectMonth->currentIndex()]/MyMath::monthEnd(selectMonth->currentIndex()+1,localita.anno));
		hourlyPlot->setHourlyData(hourlyRR);
		hourlyEOPlot->setHourlyData(hourlyEO);
		hourlyPlot->draw(1);
		hourlyEOPlot->draw(1);
	}
        qDebug()<<"MW scaling"<<otherLosses.scaling;
        firstPassDone = false; // this is a flag for the simulation
    }
}

void MainWindow::enableDrawingLoads()
{
        if (checkDrawLoads!=0)
                if (hourlyEOPlot!=0)
                    drawHourlyValues();
                //hourlyEOPlot->enableDrawingLoads(checkDrawLoads->isChecked());
}

void MainWindow::checkUpdatesSilent(bool s)
/* This is called at the start up, and only if there is a new version */
{
    if (s) {
    if (ch->isHidden())
        ch->show();
    else
        ch->activateWindow();
}
}
void MainWindow::setUpdateAtStart()
{
    if (ch!=0){
        checkAtStart = ch->getUpdateAtStart();
        qDebug()<<"MW set update at start"<<checkAtStart;
    }
}

void MainWindow::checkUpdates()
{
	
	ch->setVersion(versionId);
        if (ch->isHidden())
            ch->show();
        else
            ch->activateWindow();
	 
	ch->doDownload(urlOwner);
	
			
	 
}
void MainWindow::redrawReale(int whichone)
/* whichone comes from a combo. Add 1 to match reale->drawContents*/
{
    if (!doNotUpdateField){
	if (whichone<=localita.additionalIncl.size() && !noRadiation){
	
	if (checkOmbre->isChecked())
		reale->drawContents(2,whichone+1);
	else
		reale->drawContents(1,whichone+1);
	}
	drawHourlyValues();
	updateRadLabels(reale->getUnit());
        doNotUpdateField = true;
        comboCurrentField->setCurrentIndex(whichone);
        doNotUpdateField = false;
    }
}
 
void MainWindow::redrawSelfShadow(int m)
{
    if (!doNotUpdateField){
    w->setCurrentSide(m);

        w->toggleSelfShadow(toggleSelfShadowBox->checkState());
    }
}
void MainWindow::showDetails()
{
#ifdef PLUSVERSION2
    if (projectDetails->isHidden()){
           projectDetails->show();

    }else{
        projectDetails->activateWindow();
    }
projectDetails->raise();
if (projectDetails->isMinimized())
    projectDetails->showNormal();
#endif
}
void MainWindow::showMiniWord()
{
#ifdef PLUSVERSION2
    if (miniWord->isHidden()){
            miniWord->show();

    }else{
        miniWord->activateWindow();
    }
miniWord->raise();
if (miniWord->isMinimized())
    miniWord->showNormal();
#endif
}
void MainWindow::showEcoVal()
{
#ifdef PLUSVERSION
    if (ecoVal->isHidden()){
            ecoVal->show();

    }else{
        ecoVal->activateWindow();
    }
ecoVal->raise();
if (ecoVal->isMinimized())
    ecoVal->showNormal();
ecoVal->adjustSize();
QRect rect = QApplication::desktop()->geometry();
ecoVal->move(rect.center() - ecoVal->rect().center());
#endif
}
MainWindow::~MainWindow()
{

}
void MainWindow::updateShadow()
{
    QPolygonF nearS,horizon;
// MYPLOT->Do not emit signals. We handle everything here.
if (!otherLosses.ombrePath.isEmpty())
        {
         qDebug()<<"MW UpdateProject ombrePath"<<otherLosses.ombrePath;

        horizon = readShadow(otherLosses.ombrePath);
        w->setShadow(horizon,false);


        }
if (!otherLosses.nearOmbrePath.isEmpty())
        {
         //qDebug()<<"MW UpdateProject ombrePath"<<otherLosses.ombrePath;
        nearS = (readShadow(otherLosses.nearOmbrePath));

        if (nearS.size()>0)
            w->setPolyShadow(nearS,false);


        if ((editor!=0) && nearS.size()>0)
                editor->setShadow(nearS);


        }

            if (nearS.size()>0){
           /*draw the combined shadows*/
            w->drawShadow(1,QPolygonF());
        }
            else
            {
                /*draw the shadows of horizon if present*/
                w->drawShadow(2,horizon);
            }

}
bool MainWindow::sanityCheck(ecopara p)
        /*This routine is tied to a particular economical regime*/
        /* It the sanity passes the routine returns true */
{
    double eps = 0.00000000000002;
    switch (p.regime){
    case SSPIT:
        if (installedPower()>200){
            int r = QMessageBox::warning(this,tr("Qualche errore di configurazione"),tr("<p>Il regime impostato non &egrave; compatibile con la potenza installata (>200kWp).Continuo?</p>"),QMessageBox::Ok|QMessageBox::No);
        if (r==QMessageBox::Ok)
            return true;
        else
            return false;
        }

        if (loadInterface!=0){
            if (loadInterface->zeroLoad())
               QMessageBox::warning(this,tr("Attenzione"),tr("<p>Il regime impostato &egrave; SCAMBIO SUL POSTO e hai inserito consumi nulli.</p>"),QMessageBox::Ok);
            return true;
        }
        break;
    case Vendita:
        if (loadInterface->loadInserted())
            int r = QMessageBox::warning(this,tr("Attenzione"),tr("<p>Il regime impostato &egrave; VENDITA e hai inserito consumi non nulli.</p>"),QMessageBox::Ok);
        return true;
    }
    /* Other checks */
    if (p.loan>0 && p.loanInterestRate<eps){
        QMessageBox::critical(this,tr("Parametri economici errati"),tr("<p>Il finanziamento &egrave; non nullo, ma il tasso di interesse &egrave; nullo!</p>"));
        return false;


    }

    return true;

}
void MainWindow::exportHourlyEnergy()
/*Export all data about hourly energy in one year */
/* Data taken from class variable eprod */
{

        QString fileName;


        fileName = QFileDialog::getSaveFileName(this, tr("Esporta dati energia oraria"),  recentDirHE,"Text files ( *txt)");

        if ( !fileName.isEmpty() )
        {
            fileName = MyMath::checkFormat(fileName,"txt");
            if (!MyMath::exportToText(fileName,eprod))
            QMessageBox::warning(this,tr("Esportazione dati"),tr("Qualche errore di scrittura sul file/cartella selezionata. Prova a ripetere o a cambiare cartella/nome file"),QMessageBox::Ok);
            recentDirHE = QFileInfo(fileName).absoluteDir().absolutePath();
            qDebug()<<"MW exportenergy"<<recentDirHE;
        }

    }



void MainWindow::loadHourlyEnergy()
{

//
     QString sa,fileName;
     bool ok1;
     QStringList sasp;
    QVector<double> to ;
//
  to.resize(0);
     double d,sum;
    int errorCode=0;
     int n;
//    d=0;
//
     fileName = QFileDialog::getOpenFileName(this, tr("Dati Energia oraria"),recentDir,tr("File testo")+ "(*.txt)");
//
//
    QFile file(fileName);
//
     if (file.open(QFile::ReadOnly) && !fileName.isEmpty()){
         recentDir = QFileInfo(file).absoluteDir().absolutePath();
         QTextStream in(&file);
//        qDebug()<<"MW at end"<<in.atEnd();
        n=0;
        sum = 0;
         while (!in.atEnd()){
////
             sa = in.readLine().simplified();
//
             sasp = sa.split(" ");
             if (sasp.size()!=2)
             {
                 errorCode = 111;
                 break;
             }
             d=sasp.at(1).toDouble(&ok1);
             sum +=d;

             if (!ok1)
             {
                 errorCode = 210;
                 break;
             }
             if (d<0)
             {
                 errorCode = 310;
                 break;
             }
              to.append(d);


             n++;
             }
         if (errorCode==0){
             int r =compareEnergies(sum);
             if (r == 0){
                eprod = to;
                firstPassDone = true;
                fillEnString(fileName);
                fileEnergyData = fileName;
                 decorateTab(innerTabEO,tabWidget,2,2,1);
            }
             if (r == 1)
             {
                 eprod = to;
                 firstPassDone = true;
                 fillEnString(fileName);
                 fileEnergyData = fileName;
                  decorateTab(innerTabEO,tabWidget,2,2,3);
             }

            }
         if (errorCode==111)
             QMessageBox::critical(this,tr("Errore - 111 Dati energetici errati"),tr("Il numero di colonne nel file deve essere almeno di due"));
         if (errorCode==210)
             QMessageBox::critical(this,tr("Errore - 210 Dati energetici errati"),tr("Il file contiene dati non numerici alla linea ")+QString::number(n++));
         if (errorCode==310)
             QMessageBox::critical(this,tr("Errore - 310 Dati energetici errati"),tr("Il file contiene un numero negativo alla linea ")+QString::number(n++));


     }
//
//          ;
    //


    }


void MainWindow::fillEnString(const QString &fileName)
{
    int k = 0;
    int em,dayCount;
    resetEnString();
    dayCount = 1;
    for(int month=0;month<12;month++) {


              em = MyMath::monthEnd(month+1,2004);
              //month from 1 to 12. Default year = 366

           for(int day=1;day<=em;day++) {


            if (dayCount==MyMath::refDay(month))
              energString +="<tr><td>" + MyMath::months(month+1) + "</td>";

                /***************/
                /* HOURS CYCLE */
                /***************/
                  for(int hour=0;hour<24;hour++){

                     if (dayCount==MyMath::refDay(month))
                       if (eprod.at(k)>0.0000000000000002)
                        energString +="<td style=\"background-color : #56ab1e;\">" + QString("%L1").arg(eprod.at(k),0,'f',1) + "</font></td>";
                       else
                        energString +="<td>" + QString("%L1").arg(eprod.at(k),0,'f',2) + "</td>";
//
                       if (std::isnan(eprod.at(k))) {

                       exit(-1);
                   }
                      if (eprod.at(k)<0){
                      qDebug()<<"EPROD in fillString NEGATIVE..."<<k<<month<<day<<hour;
                      exit(-1);
                      }
                      k++;
                      }
                      if (dayCount==MyMath::refDay(month))
                            energString +="</tr>";
                            dayCount++;
                    }

             }
    energString+="</table><p>" +tr("File dati caricato: ")+ fileName + "</p><p>" + tr("Valori in kWh") + "</p>";



                    updateHourlyTable();



}


int MainWindow::compareEnergies(double tot)
        /* Compare tot with the total produced energy of the*/
        /* current project*/
        /*Return values*/
        /* 0 no problem*/
        /* 1 use loaded data although they do not match */
        /* 2 do not use loaded data*/

{
    double b,cr;

    b = installedPower();
    cr = b *localita.starRatio;
  //  qDebug()<<"MW compareEn"<<tot<<localita.starRatio<<b<<cr;

    if (100*(fabs(tot-cr)/cr) > 20){

        QMessageBox msgBox(QMessageBox::Warning,tr("Energia oraria"),tr("ATTENZIONE: i dati di energia oraria (") + QString::number(tot) +"kWh) " +tr("sembrano incompatibili con il sistema corrente. Continuo ad usarli nelle simulazioni?"),QMessageBox::No);


        QPushButton *yesButton = msgBox.addButton(tr("Si"), QMessageBox::ActionRole);
        msgBox.exec();
        //int r = QMessageBox::warning(this,tr("Dati orari"),tr("ATTTENZIONE: i dati di energia oraria (") + QString::number(tot) +"kWh) " +tr("sembrano incompatibili con il sistema corrente. Continuo ad usarli nelle simulazioni?"),QMessageBox::Yes|QMessageBox::No);
        if (msgBox.clickedButton() == yesButton)
            {
            return 1;

            }
        else
            return 2;
        delete yesButton;
    }
    else
        return 0;

}
void MainWindow::viewSite()
{
    toolBox->setCurrentIndex(0);
}
void MainWindow::viewSup()
{
    toolBox->setCurrentIndex(1);
}
void MainWindow::viewMeteo()
{
    toolBox->setCurrentIndex(2);
}

void MainWindow::setSimOptions()
{
    if (simEcoOpt->exec()){
    cash->setOptions(simEcoOpt->getOptions());
    qDebug()<<"MW options"<<simEcoOpt->getOptions();
}
}
void MainWindow::showSimOptions()
{
#ifdef PLUSVERSION
    if (simEcoOpt->isHidden()){
            simEcoOpt->show();

    }else{
        simEcoOpt->activateWindow();
    }
simEcoOpt->raise();
if (simEcoOpt->isMinimized())
    simEcoOpt->showNormal();
#endif

}

void MainWindow::decorateTab(QTabWidget *wt, QTabWidget *hWidget,int num, int numH,int mode)
{
    /*mode = 0 -> simulated
      mode = 1 -> loaded
    */



    if (wt!=0)

        if (mode == 0) {
            if (num<wt->count()){
                wt->setTabIcon(num,QIcon(":/images/simulateden.bmp"));
                hWidget->setTabIcon(num,QIcon(":/images/simulateden.bmp"));
                wt->setTabToolTip(num,tr("S:Dati orari simulati"));
            }
}
        if (mode == 1)
        {
            if (numH<wt->count()){
            wt->setTabIcon(numH,QIcon(":/images/loaden.bmp"));
            hWidget->setTabIcon(numH,QIcon(":/images/loaden.bmp"));
            wt->setTabToolTip(numH,tr("L: Dati orari caricati"));
        }
        }
        if (mode == 2)
            /*reset mode */
        {
            if (numH<wt->count()){
            wt->setTabIcon(numH,QIcon(""));
            hWidget->setTabIcon(numH,QIcon(":/images/ep.png"));
            wt->setTabToolTip(numH,tr("Nessun dato orario"));
        }
        }
        if (mode == 3)
        {
            if (numH<wt->count()){
            wt->setTabIcon(numH,QIcon(":/images/loadedenw.bmp"));
            hWidget->setTabIcon(numH,QIcon(":/images/loadedenw.bmp"));
            wt->setTabToolTip(numH,tr("L: Dati orari caricati")+", " + tr("non compatibili con il sistema impostato"));
        }
        }
        
}
void MainWindow::updateTrackValue(double a)
{
    /*We selected a tracker system?*/
//    if (localita.tipo==1)
//        trackDimValue->setValue(sqrt(a));
}
void MainWindow::updateMaxTemp(double a)
{
    localita.tempMax = a;
    maxTempIsEdited = true;
    createCheckInverter();

}
void MainWindow::updateMinTemp(double a)
{
    localita.tempMin = a;
    minTempIsEdited = true;
    createCheckInverter();
}


void MainWindow::updateDetails()
{
#ifdef PLUSVERSION2
    if (miniWord){
        miniWord->setDesigner(projectDetails->getAll());
        miniWord->setPower(installedPower());
        miniWord->addEco(ecoVal->getEcoParameters());
        miniWord->addMonthlyProfile(loadInterface->getYearProfile());
        miniWord->addYearlyLoad(loadInterface->getYearlyTotal());
        miniWord->addOption(otherLosses);
        miniWord->addEnergy(Energy);
        miniWord->addRad(HinclOmbre);
        miniWord->addRadh(Hg);
        miniWord->addUnitRad(unit.at(reale->getUnit()-1));
        miniWord->addPanel(thisProjectPanel);

        miniWord->addLocation(localita);
        miniWord->setProjectPath(projectName);
        if (w!=0)
            miniWord->addSolarDiagram(w);
        if (loadInterface!=0)
            miniWord->setConsumi(loadInterface);
        if (inverterCheck!=0)
            miniWord->setSystem(inverterCheck->getSystem());
    makeDirty();
    }
#endif
}
void MainWindow::updateDbPanels(const QString &id)
{

     #ifdef DEBUG
    qDebug()<<"database pannelli="<<databasePanels;
     #endif

    QSqlDatabase db =  QSqlDatabase::database(id);
    QSqlQuery query(db);
    query.prepare("SELECT tipo FROM inverter ");
    query.exec();
    if (!query.isValid()){
        query.prepare(" ALTER TABLE inverter ADD tipo INTEGER");
        query.exec();
    }
    qDebug()<<"MW updateDbPanels"<<query.executedQuery()<<query.lastError();

    query.prepare("SELECT vout FROM inverter ");
    query.exec();
    if (!query.isValid()){
        query.prepare(" ALTER TABLE inverter ADD vout REAL");
        query.exec();
    }
    qDebug()<<"MW updateDbPanels 2"<<query.executedQuery()<<query.lastError();


    query.prepare("SELECT icc FROM inverter ");
    query.exec();
    if (!query.isValid()){
        query.prepare(" ALTER TABLE inverter ADD icc INTEGER");
        query.exec();
    }
    qDebug()<<"MW updateDbPanels"<<query.executedQuery()<<query.lastError();


    query.prepare("SELECT cosphi FROM inverter ");
    query.exec();
    if (!query.isValid()){
        query.prepare(" ALTER TABLE inverter ADD cosphi REAL");
        query.exec();
    }
    qDebug()<<"MW updateDbPanels"<<query.executedQuery()<<query.lastError();

    query.prepare("SELECT tra FROM inverter ");
    query.exec();
    if (!query.isValid()){
        query.prepare(" ALTER TABLE inverter ADD tra BOOLEAN");
        query.exec();
    }
    qDebug()<<"MW updateDbPanels"<<query.executedQuery()<<query.lastError();



}
