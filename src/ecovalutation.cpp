#include "qintervaleditor.h"
#include "infodialog.h"
#include "ecovalutation.h"
#include "doubledelegate.h"
#include <QDebug>
 
#include "mymath.h"
#include "math.h"
#include "histogram_item.h"
 
#include <qwt_interval_data.h>


 #include <qwt_plot_layout.h>
#include "data.h"
 
#include <qwt_plot_panner.h>
#include <qwt_picker.h>
#include <qwt_plot_picker.h>
#include <qwt_curve_fitter.h>
#include <qwt_spline.h>
#include <qwt_plot_canvas.h>
#include <qwt_scale_draw.h>
#include <qwt_scale_widget.h>
#include <qwt_painter.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_marker.h>
 
 
#include <qwt_legend.h>
#include <QPolygonF>
#include <cstdlib>
EcoVal::EcoVal(QWidget* parent)
{

        setupUi(this);

        bandsError= false;
        /*********** Setup of Prices **********/
        qDebug()<<"ECO start setup prices";
        mPrezziEnergia.resize(12);

        for(int i=0;i<12;i++)
        {
                mPrezziEnergia[i].resize(ecoParameters.numBands);
                ecoParameters.prezziMinEnergia[i] = 10;
                for(int j=0;j<ecoParameters.numBands;j++)
                {
                    //qDebug()<<"ECO start setup prices "<< i << j;
                    ecoParameters.prezziEnergia[i][j]    = 10;
                    mPrezziEnergia[i][j]                 = 10;
                }

        }

        /**************************************/
        ecoParameters.useImmIntervals = false;

        groupImmIntervals->setEnabled(false);
        tableMinPrezziEnergia->setEnabled(true);
        this->setGeometry(QRect(parent->frameGeometry().x(),parent->frameGeometry().y(),300,300));
        /********* Setup of Bands *************/
        /* Here, 1 interval (0,0)for Consumo  */
        /* which mean no inteval at all       */
        /**************************************/
        intervalEditor = new IntervalEditor(this);
        intervalEditor->setTitle(tr("Editor di intervalli di consumo totale"));

        connect(intervalEditor,SIGNAL(accepted()),SLOT(updateIntervals()));
     //   connect(intervalEditor, SIGNAL(tableResetted()),SLOT(tableResetted()));
        connect(comboIntervals,SIGNAL(currentIndexChanged(int)),SLOT(updateTableAndSpin()));
        connect(intervalEditor, SIGNAL(intervalChanged()),SLOT(updateIntervals()));
        numOfWBands = 6;
        //numBands  = comboBands->count();
        numBands    = 12;
        QStringList s;
        /* FORMAT of s: Da,A,Value in the first interval */
        s<<"0"<<"0"<<"0";

        ecoParameters.intervalConsumo = 1;
        ecoParameters.intervals << QPointF(0,0);
        for(int i=0;i<numBands;i++){
           bands<<s;
           bandsPrevious<<s;
           bandsDefault<<s;
        }
        /**************************************/
        /*       SETUP TARIFFE IMMISSIONE     */
        /**************************************/
        pIntervalEditor = new IntervalEditor(this);
        pIntervalEditor->setLabels(QStringList()<<"Da MWh"<<"A MWh");
        pIntervalEditor->setMax(1000000);
        pIntervalEditor->setTitle(tr("Editor di intervalli di immissione"));
        connect(pIntervalEditor,SIGNAL(accepted()),SLOT(updatePIntervals()));
        connect(comboImmissione,SIGNAL(currentIndexChanged(int)),SLOT(updateImmissioneView()));
        connect(pIntervalEditor,SIGNAL(intervalChanged()),SLOT(updatePIntervals()));
        connect(checkImmIntervals,SIGNAL(stateChanged(int)),SLOT(enableMinPrices(int)));


        /**************************************/
        /*       SETUP TARIFFE CONSUMO        */
        /**************************************/

        tIntervalEditor = new IntervalEditor(this);
        tIntervalEditor->setTitle(tr("Editor di intervalli di consumo totale Oneri"));
        connect(tIntervalEditor,SIGNAL(accepted()),SLOT(updateTIntervals()));
        connect(comboTariffeIntervals,SIGNAL(currentIndexChanged(int)),SLOT(updateTariffeView()));
        connect(tIntervalEditor,SIGNAL(intervalChanged()),SLOT(updateTIntervals()));



        connect(treeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)),SLOT(showTab()));

	createActions();
       // listBands->installEventFilter(this);

	/* SETUP THE MODEL */
        f<<"B1"<<"B2"<<"B3"<<"B4"<<"B5"<<"B6"<<tr("B1 sabato")<<tr("B2 sabato")<<tr("B3 sabato")<<
                tr("B1 domenica")<<tr("B2 domenica")<<tr("B3 domenica");

        g<<"DA"<<"A";
        ecoParameters.bands = bands;

        qwtMinPrezzi->setCanvasBackground(QColor(Qt::white));


        /* Nov 2010 - dismissed */
//        prezziPlot	= new QwtPlotCurve();
//        prezziPlot->attach(qwtPrezzi);

        minPrezziPlot = new QwtPlotCurve();
        minPrezziPlot->attach(qwtMinPrezzi);

// 	rawPlot = new QwtPlotCurve();

        //bandPricesPlots = new QwtPlotCurve*[12];
        QwtSymbol sym;
        QPen pen;

        QwtText tlabel(tr("Evoluzione bande nel tempo"));
        tlabel.setFont(QFont("Times",10,QFont::Normal));
        qwtBands->setTitle(tlabel);
        qwtBands->setAxisScale(QwtPlot::xBottom,0,30);
        for(int i=0;i<12;i++){
            sym.setStyle((QwtSymbol::Style)(i+1));
            if (i==2)
                pen.setColor(18);
            else
                pen.setColor(i+1);
            sym.setSize(5);
            bandPricesPlots[i] = new QwtPlotCurve((f.at(i)));
            bandPricesPlots[i]->setPen(pen);
            bandPricesPlots[i]->setSymbol(sym);
            bandPricesPlots[i]->attach(qwtBands);
        }

        setPlots(20);
        alignScales();

        ecoParameters.pedaggiokWh = 0;
	doNotChange  = false;
        doNotUpdate  = false;
        doNotLoad    = false;
        doNotUpdateIntervals = false;
        doNotUpdateTariffeIntervals = false;
        doNotUpdateImmissioneIntervals = false;
        TARIFFESIZE  = ecoParameters.tariffe_size;

        TASSESIZE    = ecoParameters.taxes_size;


        /*********************************************************/
        /* SETUP OF MIN PRICE FOR RID                            */
        /********************************************************/

        ecoParameters.immissione.fill(0,10);


         /*********************************************************/
         /* SETUP OF TARIFFE                                      */
         /********************************************************/

         QVector<double> tv;
         tv << 0;
         for(int i=0;i<TARIFFESIZE;i++)
               ecoParameters.tariffe << tv;



         for(int i=0;i<TASSESIZE;i++) ecoParameters.taxes[i] =0;

        doNotEmit = true;
        setYearlyMinPrice();

        setLife();

        setTras();
        setDist();
	setAuc();
        setDisp();
        setMisura();
        setLossFactor();
        setProdFactors();
        setDefault();
        setEco();

	setEcoInvestment();

        setTax();
        setTaxOnEn();
        updatePower();
        doNotEmit = false;


// qDebug()<<"ECO at start"<<ecoParameters.bands;
        
	numOfTariffe = 7;
	projectFolder ="";
        infoTariffe=infoPrezzi=infoBands=infoPrezziMinimi=infoTax="";

        connect(pushClearAllBands,SIGNAL(clicked()),SLOT(clearAllBands()));

        /* SIGNALS FOR MODEL VIEW */
        connect(dYearlyMinPrice,SIGNAL(valueChanged(double)),SLOT(setYearlyMinPrice()));
        connect(pushImmissione,SIGNAL(clicked()),SLOT(addImmissione()));

       // connect(dIVATariffe,SIGNAL(valueChanged(double)),SLOT(resetTariffe()));
        connect(pushTariffeIntervals,SIGNAL(clicked()),SLOT(addTariffeConsumo()));
        connect(pushAddConsumo,SIGNAL(clicked()),SLOT(addBandsConsumo()));

        connect(dVATonEn,SIGNAL(valueChanged(double)),SLOT(setTaxOnEn()));
        connect(dIMPkWh,SIGNAL(valueChanged(double)),SLOT(setTaxOnEn()));

        connect(dTAltroBonus,SIGNAL(valueChanged(double)),SLOT(setTax()));
        connect(dTAltroCS,SIGNAL(valueChanged(double)),SLOT(setTax()));
        connect(dTAltroEn,SIGNAL(valueChanged(double)),SLOT(setTax()));

        connect(dTIvaBonus,SIGNAL(valueChanged(double)),SLOT(setTax()));
        connect(dTIvaCS,SIGNAL(valueChanged(double)),SLOT(setTax()));
        connect(dTIvaEn,SIGNAL(valueChanged(double)),SLOT(setTax()));

        connect(dTIrpefBonus,SIGNAL(valueChanged(double)),SLOT(setTax()));
        connect(dTIrpefCS,SIGNAL(valueChanged(double)),SLOT(setTax()));
        connect(dTIrpefEn,SIGNAL(valueChanged(double)),SLOT(setTax()));

        connect(dTIrapBonus,SIGNAL(valueChanged(double)),SLOT(setTax()));
        connect(dTIrapCS,SIGNAL(valueChanged(double)),SLOT(setTax()));
        connect(dTIrapEn,SIGNAL(valueChanged(double)),SLOT(setTax()));

        connect(dTIresBonus,SIGNAL(valueChanged(double)),SLOT(setTax()));
        connect(dTIresCS,SIGNAL(valueChanged(double)),SLOT(setTax()));
        connect(dTIresEn,SIGNAL(valueChanged(double)),SLOT(setTax()));

        connect(this,SIGNAL(isDirtyBands()),SLOT(setDirtyBands()));
        connect(dBandsInflationRate,SIGNAL(valueChanged(double)),SLOT(setEco()));

        connect(dCTRkWh,SIGNAL(valueChanged(double)),SLOT(setProdFactors()));
        connect(dFattCTR,SIGNAL(valueChanged(double)),SLOT(setProdFactors()));
        connect(dAltriCostiMensili,SIGNAL(valueChanged(double)),SLOT(setProdFactors()));

        connect(dPerditaTrasmissione,SIGNAL(valueChanged(double)),SLOT(setProdFactors()));
       // connect(dPerditaDistribuzione,SIGNAL(valueChanged(double)),SLOT(setProdFactors()));
        connect(dCostiAmm,SIGNAL(valueChanged(double)),SLOT(setProdFactors()));
        connect(dLimitCostiAmm,SIGNAL(valueChanged(double)),SLOT(setProdFactors()));

        connect(dTrasmissionekWh,SIGNAL(valueChanged(double)),SLOT(setTras()));
        connect(dTrasmissioneAnno,SIGNAL(valueChanged(double)),SLOT(setTras()));
        connect(dTrasmissionekW,SIGNAL(valueChanged(double)),SLOT(setTras()));

        connect(dDistribuzioneAnno,SIGNAL(valueChanged(double)),SLOT(setDist()));
        connect(dDistribuzionekW,SIGNAL(valueChanged(double)),SLOT(setDist()));
        connect(dDistribuzionekWh,SIGNAL(valueChanged(double)),SLOT(setDist()));

        connect(dMisurakWh,SIGNAL(valueChanged(double)),SLOT(setMisura()));
        connect(dMisurakW,SIGNAL(valueChanged(double)),SLOT(setMisura()));
        connect(dMisuraAnno,SIGNAL(valueChanged(double)),SLOT(setMisura()));

        connect(dMCTkWh,SIGNAL(valueChanged(double)),SLOT(setAuc()));
        connect(dAUCkW,SIGNAL(valueChanged(double)),SLOT(setAuc()));
        connect(dAUCanno,SIGNAL(valueChanged(double)),SLOT(setAuc()));
        connect(dAUCkWh,SIGNAL(valueChanged(double)),SLOT(setAuc()));

        connect(dDISP,SIGNAL(valueChanged(double)),SLOT(setDisp()));
        connect(dDISPkW,SIGNAL(valueChanged(double)),SLOT(setDisp()));
        connect(dDISPkWh,SIGNAL(valueChanged(double)),SLOT(setDisp()));

        connect(dLoss,SIGNAL(valueChanged(double)),SLOT(setLossFactor()));
        connect(dPotenzakW,SIGNAL(valueChanged(double)),SLOT(updatePower(double)));
	connect(comboBands,SIGNAL(currentIndexChanged(int)),SLOT(updateView(int)));
	connect(spinDa,SIGNAL(valueChanged(int)),SLOT(updateBandsDa(int)));
	connect(spinA,SIGNAL(valueChanged(int)),SLOT(updateBandsA(int)));
	connect(dValue,SIGNAL(valueChanged(double)),SLOT(updateBandsVal(double)));
	


        connect(pushCutBandFile,SIGNAL(clicked()),SLOT(deleteBandsFile()));
        connect(pushCutOneriFile,SIGNAL(clicked()),SLOT(deleteOneriFile()));
        connect(pushCutPrezziFile,SIGNAL(clicked()),SLOT(deletePrezziFile()));
        connect(pushCutMinPrezziFile,SIGNAL(clicked()),SLOT(deleteMinPrezziFile()));
        connect(pushCutTaxFile,SIGNAL(clicked()),SLOT(deleteTaxFile()));




        connect(checkCredit,SIGNAL(stateChanged(int)),SLOT(setEco()));
        connect(radioSimpleInflation,SIGNAL(clicked()),SLOT(setEco()));
        connect(radioSimpleInflation_2,SIGNAL(clicked()),SLOT(setEco()));
        connect(dEnergyInflationRate2,SIGNAL(valueChanged(double)),SLOT(setEco()));
        connect(dEnergyInflationRateSell,SIGNAL(valueChanged(double)),SLOT(setEco()));
//        connect(da1,SIGNAL(valueChanged(double)),SLOT(setEco()));
//        connect(db1,SIGNAL(valueChanged(double)),SLOT(setEco()));
//        connect(dO,SIGNAL(valueChanged(double)),SLOT(setEco()));
//        connect(dMu,SIGNAL(valueChanged(double)),SLOT(setEco()));

        connect(dminPricesA1,SIGNAL(valueChanged(double)),SLOT(setEco()));
        connect(dminPricesB1,SIGNAL(valueChanged(double)),SLOT(setEco()));
        connect(dminPricesO1,SIGNAL(valueChanged(double)),SLOT(setEco()));
        connect(dminPricesMu,SIGNAL(valueChanged(double)),SLOT(setEco()));

        connect(dBonusesYears,SIGNAL(valueChanged(int)),SLOT(setEcoInvestment()));
        connect(dIncentivi,SIGNAL(valueChanged(double)),SLOT(setEcoInvestment()));
        connect(dIncentiviPerkWp,SIGNAL(valueChanged(double)),SLOT(setEcoInvestment()));
        connect(dAssicurazione,SIGNAL(valueChanged(double)),SLOT(setEcoInvestment()));
        connect(dAssicurazioneAnni,SIGNAL(valueChanged(int)),SLOT(setEcoInvestment()));
        connect(dAmmortamento,SIGNAL(valueChanged(double)),SLOT(setEcoInvestment()));
        connect(comboRegime,SIGNAL(currentIndexChanged(int)),SLOT(setEcoInvestment()));


        connect(dManutenzioneAnno,SIGNAL(valueChanged(double)),SLOT(setEcoInvestment()));
         connect(dAffitti,SIGNAL(valueChanged(double)),SLOT(setEcoInvestment()));
        connect(dManutenzioneS,SIGNAL(valueChanged(double)),SLOT(setEcoInvestment()));
        connect(dManutenzioneSFreq,SIGNAL(valueChanged(int)),SLOT(setEcoInvestment()));
        connect(dAltro,SIGNAL(valueChanged(double)),SLOT(setEcoInvestment()));
        connect(dReductionInitialCost,SIGNAL(valueChanged(double)),SLOT(setEcoInvestment()));
        connect(dTaxReductionInterest,SIGNAL(valueChanged(double)),SLOT(setEcoInvestment()));
        connect(dTaxReduction,SIGNAL(valueChanged(double)),SLOT(setEcoInvestment()));

        connect(dTaxReductionVAT,SIGNAL(valueChanged(double)),SLOT(setEcoInvestment()));
        connect(dVAT,SIGNAL(valueChanged(double)),SLOT(setEcoInvestment()));
        connect(dCostoIniziale,SIGNAL(valueChanged(double)),SLOT(setEcoInvestment()));
        connect(dFinanziamento,SIGNAL(valueChanged(double)),SLOT(setEcoInvestment()));
        connect(dFinAnni,SIGNAL(valueChanged(int)),SLOT(setEcoInvestment()));
        connect(dLoanInterestRate,SIGNAL(valueChanged(double)),SLOT(setEcoInvestment()));
        connect(dTassoInflazione,SIGNAL(valueChanged(double)),SLOT(setEcoInvestment()));
        connect(dDiscountRate,SIGNAL(valueChanged(double)),SLOT(setEcoInvestment()));
        connect(dPeriodo,SIGNAL(valueChanged(int)),SLOT(setLife(int)));


	connect(tablePrezziEnergia,SIGNAL(itemChanged(QTableWidgetItem* )),SLOT(updatePrezzi(QTableWidgetItem* )));
        connect(comboImmBand,SIGNAL(currentIndexChanged(int)),SLOT(updatePrezziView()));

        /* Tasse */
        connect(pushSaveTax,SIGNAL(clicked()),SLOT(saveTax()));
        connect(pushSaveTaxAs,SIGNAL(clicked()),SLOT(saveTaxAs()));
        connect(pushLoadTax,SIGNAL(clicked()),SLOT(loadTax()));
        connect(listTaxes,SIGNAL(clicked(QModelIndex)),SLOT(loadTaxFromList(QModelIndex)));

	/*Tariffe*/
        
	connect(pushSavePrezzi,SIGNAL(clicked()),SLOT(save()));
	connect(pushSavePrezziAs,SIGNAL(clicked()),SLOT(saveAs()));
	connect(pushLoadPrezzi,SIGNAL(clicked()),SLOT(loadTariffe()));
	/*Fasce*/
	connect(pushSaveBands,SIGNAL(clicked()),SLOT(saveBands()));
	connect(pushLoadBands,SIGNAL(clicked()),SLOT(loadB()));
	connect(pushSaveBandsAs,SIGNAL(clicked()),SLOT(saveBandsAs()));
	/*Prezzi Energia*/
	connect(pushSavePrezziEnergiaAs,SIGNAL(clicked()),SLOT(savePrezziAs()));
	connect(pushSavePrezziEnergia,SIGNAL(clicked()),SLOT(saveP()));
	connect(pushLoadPrezziEnergia,SIGNAL(clicked()),SLOT(loadP()));


	/* Prezzi minimi garantiti dell'energia */
	connect(tableMinPrezziEnergia,SIGNAL(itemChanged(QTableWidgetItem* )),SLOT(updateMinPrezzi(QTableWidgetItem* )));
	connect(pushSaveMinPrezziEnergiaAs,SIGNAL(clicked()),SLOT(saveMinPrezziAs()));
	connect(pushSaveMinPrezziEnergia,SIGNAL(clicked()),SLOT(saveMinP()));
	connect(pushLoadMinPrezziEnergia,SIGNAL(clicked()),SLOT(loadMinP()));
	connect(dminPricesO1,SIGNAL(valueChanged(double)),SLOT(processMinEnergyPrices()));
	connect(dminPricesMu,SIGNAL(valueChanged(double)),SLOT(processMinEnergyPrices()));
	connect(dminPricesA1,SIGNAL(valueChanged(double)),SLOT(processMinEnergyPrices()));
	connect(dminPricesB1,SIGNAL(valueChanged(double)),SLOT(processMinEnergyPrices()));
	
	connect(radioGARCH_2,SIGNAL(toggled(bool)),SLOT(reProcessMinEnergyPrices(bool)));
	connect(dEnergyInflationRateSell,SIGNAL(valueChanged(double)),SLOT(processMinEnergyPrices()));
	connect(dDiscountRate,SIGNAL(valueChanged(double)),SLOT(processMinEnergyPrices()));


        connect(listBands,SIGNAL(clicked(QModelIndex )),SLOT(loadBandFromList(QModelIndex )));
	connect(listEnergyPrices,SIGNAL(clicked(QModelIndex )),SLOT(loadPricesFromList(QModelIndex)));
        connect(listMinEnergyPrices,SIGNAL(clicked(QModelIndex )),SLOT(loadMinPricesFromList(QModelIndex)));
        connect(listTariffe,SIGNAL(clicked(QModelIndex )),SLOT(loadTariffeFromList(QModelIndex)));

        connect(comboRegime,SIGNAL(currentIndexChanged(int)),SLOT(toggleCoeff(int )));
	/* Prezzi energia */
       // connect(dPeriodo,SIGNAL(valueChanged(int)),SLOT(processEnergyPrices( )));
	
        //connect(dPeriodo,SIGNAL(valueChanged(int)),SLOT(processMinEnergyPrices( )));

        /* Nov 2010 - dismissed for now */
//	connect(dO,SIGNAL(valueChanged(double)),SLOT(processEnergyPrices()));
//	connect(dMu,SIGNAL(valueChanged(double)),SLOT(processEnergyPrices()));
//	connect(da1,SIGNAL(valueChanged(double)),SLOT(processEnergyPrices()));
//	connect(db1,SIGNAL(valueChanged(double)),SLOT(processEnergyPrices()));
	
//	connect(radioGARCH,SIGNAL(toggled(bool)),SLOT(reProcessEnergyPrices(bool)));
//	connect(dEnergyInflationRate2,SIGNAL(valueChanged(double)),SLOT(processEnergyPrices()));

//	connect(dDiscountRate,SIGNAL(valueChanged(double)),SLOT(processEnergyPrices()));

        //connect(dPeriodo,SIGNAL(valueChanged(int)),SLOT(computeLoan( )));
	connect(dFinanziamento,SIGNAL(valueChanged(double)),SLOT(computeLoan( )));		
	connect(dLoanInterestRate,SIGNAL(valueChanged(double)),SLOT(computeLoan( )));	
	connect(dFinAnni,SIGNAL(valueChanged(int)),SLOT(computeLoan( )));	

        connect(dPotenzakW,SIGNAL(valueChanged(double)),SLOT(updatePedaggiokW()));


	connect(tableBandsView,SIGNAL(clicked(const QModelIndex&)),SLOT(changeSelectedBand(const QModelIndex&)));

        /* Info */

	connect(pushInfoTariffe,SIGNAL(clicked()),SLOT(updateInfo()));
	connect(pushInfoBands,SIGNAL(clicked()),SLOT(updateInfoBands()));
	connect(pushInfoPrezzi,SIGNAL(clicked()),SLOT(updateInfoPrezzi()));
	connect(pushInfoPrezziMinimi,SIGNAL(clicked()),SLOT(updateInfoPrezziMinimi()));
        connect(pushInfoTax,SIGNAL(clicked()),SLOT(updateTaxInfo()));

        connect(pushUndo,SIGNAL(clicked()),SLOT(undoDel()));

	installedPower = 0;
        pushUndo->setEnabled(false);

	
	w1 = tr("Attenzione: fascia orarie non valide");
	w2 = tr("Sovrapposizione di fasce");
	w3 = tr("Qualche errore di sovrapposizione e/o fasce vuote nelle fasce weekend");
	w4 = tr("Qualche errore di sovrapposizione e/o fasce vuote");

	/*ToolTip*/
        dTaxReductionInterest->setToolTip(tr("<p>Sgravi fiscali dovuti agli interessi che si pagano per il finanziamento. Possono essere dedotti dal reddito imponibile, ove previsto.</p>"));

        groupTariffe->setToolTip(tr("<p>Per clienti domestici, le tariffe di Trasmissione, Distribuzione e Misura sono accorpate nelle cosiddette tariffe D2 e D3, a seconda della potenza installata. Le tariffe D2 e D3 prevedono due tipi di costo: uno variabile per kWh e uno fisso per kW. Per clienti domestici usare una qualsiasi entry a scelta fra Trasmissione/Distribuzione/Misura.</p>"));

        groupGenerali->setToolTip(tr("<p>Le tariffe A,UC,MCT sono considerate tariffe per oneri generali</p>"));

	/*Some init*/
	fileTariffe = "";
	filePrezzi  = "";
	fileMinPrezzi = "";
	fileBands   ="";
        recentSaveTariffe  = QDir::homePath();
        recentDirTariffe   = QDir::homePath(); /*Tariffe*/
        recentDir          = QDir::homePath(); /*Bands*/
        recentSave =        QDir::homePath();
        recentDirPrezzi    = QDir::homePath();
        recentSavePrezzi    = QDir::homePath();
        recentSaveMinPrezzi = QDir::homePath();
	recentDirMinPrezzi = QDir::homePath();
        recentDirTax       = QDir::homePath();
        recentSaveTax       = QDir::homePath();
        titleBox  = tr("Prezzi energia immessa(c/kWh)");
        titleBox2 = tr("Prezzi di vendita energia garantiti(c/kWh)");
        titleBox3 = tr("Imposte");
	titleBandBox = tr("Valori orari") ;
        titleTariffeBox = tr("Oneri accessori e dispacciamento");
	groupBandsTitle = titleBandBox + " - ";
        groupTariffeTitle      = titleTariffeBox + " - ";
	groupPrezziTitle       = titleBox + " - ";
        groupMinPrezziTitle    = titleBox2 + " - ";
        groupTaxTitle          = titleBox3 + " - ";
	
	groupBands->setTitle(groupBandsTitle );
	groupTariffe->setTitle(groupTariffeTitle);
	groupPrezzi->setTitle(groupPrezziTitle);
	groupMinPrices->setTitle(groupMinPrezziTitle);
	
	doNotCheck = false;
		
// 	recentBands<<"";
// 	recentBandsFileName<<"";
        modelTax = new QStringListModel(this);
        modelTax->setStringList(recentBandsFileName);
        listTaxes->setModel(modelTax);
        listTaxes->setEditTriggers(QAbstractItemView::NoEditTriggers);

       // MousePressEater* mouseTracker = new  MousePressEater(this);
        model = new QStringListModel(this);
	model->setStringList(recentBandsFileName);
        model->installEventFilter(this);

        
	listBands->setModel(model);
        listBands->setEditTriggers(QAbstractItemView::NoEditTriggers);




	modelInj = new QStringListModel(this);
	modelInj->setStringList(recentPricesFileName);
	listEnergyPrices->setModel(modelInj);
        listEnergyPrices->setEditTriggers(QAbstractItemView::NoEditTriggers);

	modelSell = new QStringListModel(this);
	modelSell->setStringList(recentMinPricesFileName);
	listMinEnergyPrices->setModel(modelSell);
        listMinEnergyPrices->setEditTriggers(QAbstractItemView::NoEditTriggers);
	 
        modelTariffe = new QStringListModel(this);
        modelTariffe->setStringList(recent);
        listTariffe->setModel(modelTariffe);
        listTariffe->setEditTriggers(QAbstractItemView::NoEditTriggers);

        // processEnergyPrices( );

        // reProcessEnergyPrices(radioGARCH->isChecked());

	processMinEnergyPrices();
	reProcessMinEnergyPrices(radioGARCH_2->isChecked());

	computeLoan();
	recentExportPath =QDir::homePath();
// 	createActions();
// 	this->setContextMenuPolicy(Qt::CustomContextMenu);
// 	connect(this,SIGNAL(customContextMenuRequested(const QPoint &  )),this,SLOT(popUpMenu(const QPoint &)));

	QVector<int> d;
	d<<0;
        tablePrezziEnergia->setContextMenuPolicy(Qt::CustomContextMenu);
        tableMinPrezziEnergia->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(tablePrezziEnergia,SIGNAL(customContextMenuRequested(const QPoint &  )),this,SLOT(popUpMenu(const QPoint &)));
	connect(tableMinPrezziEnergia,SIGNAL(customContextMenuRequested(const QPoint &  )),this,SLOT(popUpMenuMinPrezzi(const QPoint &)));
	tablePrezziEnergia->setItemDelegate(new DoubleDelegate(d,10000000,0,2));
	tablePrezziEnergia->horizontalHeader()->setStretchLastSection(true);
	tableMinPrezziEnergia->setItemDelegate(new DoubleDelegate(d,10000000,0,2));
	tableMinPrezziEnergia->horizontalHeader()->setStretchLastSection(true);
	tablePrezziEnergia->setHorizontalHeaderLabels(QStringList()<<tr("Valore"));
	tablePrezziEnergia->horizontalHeader()->setStretchLastSection(true);
	tableMinPrezziEnergia->setHorizontalHeaderLabels(QStringList()<<tr("Valore"));

        backupEco = ecoParameters;

        checkImmIntervals->setChecked(true);


}
 
void EcoVal::setPlots(int years)
{
	
  	
	QwtText xlabel(tr("Mese"));
        QwtText xlabel2(tr("Anno"));
	QwtText ylabel(tr("c/[kWh]"));
	ylabel.setFont(QFont("Times",12,QFont::Normal));
	xlabel.setFont(QFont("Times",12,QFont::Normal));
        xlabel2.setFont(QFont("Times",12,QFont::Normal));

	

//	qwtPrezzi->setAxisTitle(QwtPlot::xBottom,xlabel);
//        qwtPrezzi->setAxisTitle(QwtPlot::yLeft,ylabel);
  	
	qwtMinPrezzi->setAxisTitle(QwtPlot::xBottom,xlabel);
	qwtMinPrezzi->setAxisTitle(QwtPlot::yLeft,ylabel);

	 
        qwtBands->setAxisTitle(QwtPlot::xBottom,xlabel2);
        qwtBands->setAxisTitle(QwtPlot::yLeft,ylabel);



	 
}
void EcoVal::setDefault()
{
	doNotCheck = true;
	for(int i=0;i<12;i++){

                for (int j=0;j<ecoParameters.numBands;j++)
                    mPrezziEnergia[i][j] = 10; //valore simbolico

                minEnergyPrices <<10; // valore simbolico

		QTableWidgetItem *item   = new QTableWidgetItem;
		QTableWidgetItem *item2   = new QTableWidgetItem;
		item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
                item->setText(QString::number(10.0));
                item2->setText(QString::number(10.0));
  		tablePrezziEnergia->setItem(i,0,item);
		tableMinPrezziEnergia->setItem(i,0,item2);
	}
	tablePrezziEnergia->resizeColumnsToContents();
	tableMinPrezziEnergia->resizeColumnsToContents();
	doNotCheck =false;
	QStringList he = MyMath::monthsList();
	tablePrezziEnergia->setVerticalHeaderLabels(he);
	tableMinPrezziEnergia->setVerticalHeaderLabels(he);
	tableBandsView->setHorizontalHeaderLabels(MyMath::listOfNumber(0,23));
        //Now set the table of bands

        tableBandsView->setVerticalHeaderLabels(f);
        for(int i=0;i<12;i++)
        {
            for (int j=0;j<24;j++){
                QTableWidgetItem *item3 = new QTableWidgetItem;
                item3->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
                item3->setText(" ");
                item3->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                tableBandsView->setItem(i,j,item3);
	    }
        }
tableBandsView->resizeColumnsToContents();

/* Set summary table of bands */
/* Dec 2010 */
tableSummaryBands->setVerticalHeaderLabels(f);
tableSummaryBands->setHorizontalHeaderLabels(g);
for(int i=0;i<12;i++)
{
    for (int j=0;j<2;j++){
        QTableWidgetItem *item4 = new QTableWidgetItem;
        item4->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        item4->setText("0");
        item4->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        tableSummaryBands->setItem(i,j,item4);
    }
}
tableBandsView->resizeColumnsToContents();



}
void EcoVal::updatePrezziView()
{	
        doNotCheck      = true;
        int currentBand = comboImmBand->currentIndex() < numBands ? comboImmBand->currentIndex() : 0;

	for(int i=0;i<12;i++){
		
		 
                tablePrezziEnergia->item(i,0)->setText(QString::number(mPrezziEnergia[i][currentBand]));
	}
        //tablePrezziEnergia->resizeColumnsToContents();
	doNotCheck =false;

        //updatePrezziPlot();
	

}
void EcoVal::updateMinPrezziView()
{
	doNotCheck = true;
	for(int i=0;i<12;i++){
		
		 
  		tableMinPrezziEnergia->item(i,0)->setText(QString::number(minEnergyPrices[i]));
	}
	tableMinPrezziEnergia->resizeColumnsToContents();
	doNotCheck =false;
	updateMinPrezziPlot();

}
void EcoVal::updateMinPrezzi(QTableWidgetItem* current )
{
	emit isDirty();
        int currentBand;
        currentBand = comboImmBand->currentIndex() > 0 ? comboImmBand->currentIndex() : 0;
//         qDebug()<<"ECO current"<<current->row();
        if ( (current->row()>=0) && (!doNotCheck) )
        {
//
                double t = current->text().toDouble();
////     		if (*ok)
                if (t>0){
                        minEnergyPrices[current->row()] = t;
			ecoParameters.prezziMinEnergia[current->row()] = t;
                        labelWarnMin->setText("");
                    }
                else {
                    labelWarnMin->setText("<font color=\"red\"> " + tr("Un prezzo &egrave; negativo o nullo") + "</font>");
                        mPrezziEnergia[current->row()][currentBand]= 10; //Valore simbolico;
                        ecoParameters.prezziMinEnergia[current->row()] =10;
                }
//// 		else
//// 			current->setText(previous->text());
	groupMinPrices->setTitle(groupMinPrezziTitle + "*");
        processMinEnergyPrices();
        updateMinPrezziPlot();
        }
//
}

void EcoVal::updatePrezzi(QTableWidgetItem* current )
{
    if (!doNotEmit)
	emit isDirty();
	bool* ok;
// 	qDebug()<<"ECO current"<<current->row();
	if ( (current->row()>=0) && (!doNotCheck) )
	{
                int currentBand;
                currentBand = comboImmBand->currentIndex()<numBands ? comboImmBand->currentIndex() : 0;
                qDebug()<<"ECO currentBand " << currentBand;
  		double t = current->text().toDouble(ok);
		if (t>0)
		{
                        mPrezziEnergia[current->row()][currentBand] = t;
                        ecoParameters.prezziEnergia[current->row()][currentBand]
                                = mPrezziEnergia.at(current->row()).at(currentBand);
            		labelWarn->setText("");
		}
 		else
		{
			labelWarn->setText("<font color=\"red\"> " + tr("Un prezzo &egrave; negativo o nullo") + "</font>");
                        mPrezziEnergia[current->row()][currentBand]                 = 10; //Valore simbolico;
                        ecoParameters.prezziEnergia[current->row()][currentBand]    = 10;
		}
// 			current->setText(previous->text());
        /* Nov 2010 - dismissed for now */
        // processEnergyPrices();
        //updatePrezziPlot();
	groupPrezzi->setTitle(groupPrezziTitle+"*");
	
	}
	
}
void EcoVal::updateMinPrezziPlot()
{
	QPolygonF a;

        int index = comboImmissione->currentIndex();
        index = index <0 ? 0 : index;
        if (ecoParameters.useImmIntervals) {
            for(int i=0;i<ecoParameters.life;i++)
                for (int j=0;j<12;j++)
                a << QPointF(i*12+j,MyMath::inflate(i,ecoParameters.prezziMinEnergiaInflazione/100,ecoParameters.immissione.at(index)));

        }
        else
        {
 	for(int i=0;i<minEnergyPrices.size();i++){
   		a<<QPointF(i+1,minEnergyPrices.at(i));
 //    	qDebug()<<"ECO PLOT MIN prezziEnergia"<<mPrezziEnergiaSpan.size()<<i<<minEnergyPrices.at(i);
	}
        }
   	minPrezziPlot->setData(a);
  	qwtMinPrezzi->replot();
}

//void EcoVal::updatePrezziPlot()
//{
//	QPolygonF a;
//        int currentBand;
//        currentBand = comboImmBand->currentIndex() > 0 ? comboImmBand->currentIndex() : 0;
//// 	processEnergyPrices();
//        for(int i=0;i<mPrezziEnergiaSpan.at(currentBand).size();i++){
//                a<<QPointF(i+1,mPrezziEnergiaSpan.at(currentBand).at(i));
////   	qDebug()<<"ECO PLOT prezziEnergia"<<mPrezziEnergiaSpan.size()<<i<<mPrezziEnergiaSpan.at(i);
//	}
	
//   	prezziPlot->setData(a);
//         qwtPrezzi->replot();
//}
QStringList EcoVal::fromIntervalsToString(const QPolygonF &a)
{
    QStringList s;
    for(int i=0;i<a.size();i++)
        s << tr("Da") + " " +
                QString::number(a.at(i).x())
                + " " + tr("A") + " " +
                QString::number(a.at(i).y());
    return s;
}
void EcoVal::setEcoBands()
{
    ecoParameters.bands.clear();
    ecoParameters.bands = bands;
    ecoParameters.intervals.resize(0);
    ecoParameters.intervals = intervals;


}
void EcoVal::updateImmIntervals()
        /*
          * Modify the min prices intervals
        */
{
    QVector<double> temp;
    double currentValue;
    int index = comboImmissione->currentIndex();

    index   = index<0 ? 0 : index;

    if (pIntervals.size()==0)
    {
        /* No intervals */

        temp = ecoParameters.immissione;
        ecoParameters.immissione.clear();
        ecoParameters.immissione << temp.at(0);

    }
        /* Update in the eco struct */

        //qDebug()<<"ECOVAL NO MINPRICES INTERVALS at all:" << ecoParameters.immissione;


    if (pIntervals.size() > ecoParameters.immissione.size() )
        /* The user added some intervals */
    {
        /*Update all bands    */

        currentValue = dYearlyMinPrice->value();
        qDebug()<<"UpdateImmIntevals"<<currentValue<<dYearlyMinPrice->value();
              for(int k=0; k < pIntervals.size() - ecoParameters.immissione.size(); k++)
                  if (k==index)
                     ecoParameters.immissione.append(currentValue);
              else
                  ecoParameters.immissione.append(0);

    }
    if (pIntervals.size() < ecoParameters.immissione.size() && !pIntervals.isEmpty())
    {
        /* The user deleted some intervals */
        temp = ecoParameters.immissione;
        ecoParameters.immissione.clear();
        ecoParameters.immissione = temp.mid(0,pIntervals.size());
     }

    if (pIntervals.size() == ecoParameters.immissione.size())
        /* The user just changed or viewed some intervals*/
    {

    }


}
void EcoVal::updateTariffeIntervals()
        /*
          * Modify the structure of Tariffe
        */
{
    QVector<double> temp;
    double currentValue;
    int index = comboTariffeIntervals->currentIndex();

    index   = index<0 ? 0 : index;

    if (tIntervals.size()==0)
    {
        /* No intervals */
        for(int i= 0; i<ecoParameters.tariffe.size();i++){
        temp = ecoParameters.tariffe.at(i);
        ecoParameters.tariffe[i].clear();
        ecoParameters.tariffe[i] << temp.at(0);

        }
        /* Update in the eco struct */

        //qDebug()<<"ECOVAL NO TARIFFE INTERVALS at all:" << ecoParameters.tariffe;
    }

    if (tIntervals.size() > ecoParameters.tariffe.at(0).size() )
        /* The user added some intervals */
    {
        /*Update all bands    */

        for(int i= 0; i< ecoParameters.tariffe.size();i++){
            currentValue = getTariffeValueFromId(i);
              for(int k=0; k < tIntervals.size() - ecoParameters.tariffe[i].size(); k++)
                  if (k==index)
                     ecoParameters.tariffe[i].append(currentValue);
              else
                  ecoParameters.tariffe[i].append(0);
              }
    }
    if (tIntervals.size() < ecoParameters.tariffe[0].size() && !tIntervals.isEmpty())
    {
        /* The user deleted some intervals */
        for(int i= 0; i<ecoParameters.tariffe[0].size();i++){
        temp = ecoParameters.tariffe[i];
        ecoParameters.tariffe[0].clear();
        ecoParameters.tariffe[i] = temp.mid(0,tIntervals.size());
        }
    }
    if (tIntervals.size() == ecoParameters.tariffe[0].size())
        /* The user just changed or viewed some intervals*/
    {

    }
    //setEcoBands();

}

void EcoVal::updateBandsIntervals()
        /*
          * Modify the structure of  bands
        */
{


    QStringList temp,tempValues;
    int b     = comboBands->currentIndex();
    int index = comboIntervals->currentIndex();

    double currentValue = dValue->value();

    b       = b<0     ? 0 : b;
    index   = index<0 ? 0 : index;




    if (intervals.size()==0)
    {
        /* No intervals */
        for(int i= 0; i<bands.size();i++){
        temp = bands[i];
        bands[i].clear();
        bands[i] << temp.at(0) << temp.at(1) << temp.at(2) ;
       // ecoParameters.bands[i] = bands[i];
        }
        /* Update in the eco struct */

        qDebug()<<"ECOVAL NO INTERVALS at all:" << bands;
    }

    if (intervals.size() > bands[0].size()-2 )
        /* The user added some intervals */
    {
        /*Update all bands    */

        for(int i= 0; i<bands.size();i++){

            //temp = bands[i];
//            bands[i].clear();
//            bands[i] << temp.at(0) << temp.at(1);
               for(int k=0; k < intervals.size() - bands[i].size()+2; k++)
                   if (b == i)
                       bands[i].append(QString::number(currentValue));
                   else
                   bands[i].append("0");
        }
    }

    if (intervals.size() < bands[0].size()-2 && !intervals.isEmpty())
    {
        /* The user deleted some intervals */
        for(int i= 0; i<bands.size()-2;i++){
        temp = bands[i];
        bands[i].clear();
        bands[i] = temp.mid(2,intervals.size());
    }
    }
    if (intervals.size() == bands[0].size()-2)
        /* The user just changed or viewed some intervals*/
    {

    }
    setEcoBands();
    //qDebug()<<"ECOVAL update intervals" << bands;
}

void EcoVal::updateTIntervalsView()
    {
        QStringList s;
        doNotUpdateTariffeIntervals = true;

        s = fromIntervalsToString(tIntervals);
        comboTariffeIntervals->clear();
        comboTariffeIntervals->addItems(s);
        comboTariffeIntervals->setCurrentIndex(0);
        if (tIntervalEditor!=0){
            tIntervalEditor->setInterval(tIntervals);

        }

        doNotUpdateTariffeIntervals = false;
    }
void EcoVal::updatePIntervalsView()
    {
        QStringList s;
        doNotUpdateImmissioneIntervals = true;

        s = fromIntervalsToString(pIntervals);
        comboImmissione->clear();
        comboImmissione->addItems(s);
        comboImmissione->setCurrentIndex(0);
        if (pIntervalEditor!=0){
            pIntervalEditor->setInterval(pIntervals);

        }

        doNotUpdateImmissioneIntervals = false;
    }
void EcoVal::updateIntervalsView()
{

    QStringList s;
    doNotUpdateIntervals = true;
 
    s = fromIntervalsToString(intervals);
    comboIntervals->clear();
    comboIntervals->addItems(s);
    comboIntervals->setCurrentIndex(0);
    if (intervalEditor!=0){
        intervalEditor->setInterval(intervals);

    }
    updateTableBandsView();
    doNotUpdateIntervals = false;
}

void EcoVal::updateIntervals()
{
    QStringList s;
    doNotUpdateIntervals = true;
    intervals = intervalEditor->getInterval(); // Returns a QPolygonF(start,finish)
    s = fromIntervalsToString(intervals);
    ecoParameters.intervals = intervals;

    comboIntervals->clear();

    comboIntervals->addItems(s);
    comboIntervals->setCurrentIndex(0);



    updateBandsIntervals();
    updateTableBandsView();
    doNotUpdateIntervals = false;
}
void EcoVal::updatePIntervals()
{
    QStringList s;
    qDebug()<<"ECO PINTERVALS";
    doNotUpdateImmissioneIntervals = true;
    pIntervals = pIntervalEditor->getInterval(); // Returns a QPolygonF(start,finish)
    s = fromIntervalsToString(pIntervals);
    ecoParameters.pIntervals = pIntervals;

    comboImmissione->clear();

    comboImmissione->addItems(s);
    comboImmissione->setCurrentIndex(0);



    updateImmIntervals();

    doNotUpdateImmissioneIntervals = false;
}
void EcoVal::updateTIntervals()
{
    QStringList s;
    doNotUpdateTariffeIntervals = true;
    tIntervals = tIntervalEditor->getInterval(); // Returns a QPolygonF(start,finish)
    s = fromIntervalsToString(tIntervals);
    ecoParameters.tIntervals = tIntervals;

    comboTariffeIntervals->clear();

    comboTariffeIntervals->addItems(s);
    comboTariffeIntervals->setCurrentIndex(0);



    updateTariffeIntervals();

    doNotUpdateTariffeIntervals = false;
}
void EcoVal::addImmissione()
{
    if (pIntervalEditor!=0) {
            if (pIntervalEditor->isHidden())
                    pIntervalEditor->show();
            else
                    pIntervalEditor->activateWindow();
    }
}
void EcoVal::addTariffeConsumo()
{
    if (intervalEditor!=0) {
            if (tIntervalEditor->isHidden())
                    tIntervalEditor->show();
            else
                    tIntervalEditor->activateWindow();
    }
}

void EcoVal::addBandsConsumo()
{
    if (intervalEditor!=0) {
            if (intervalEditor->isHidden())
                    intervalEditor->show();
            else
                    intervalEditor->activateWindow();
    }
}

void EcoVal::updateBandsDa(int v)
{
	int b = comboBands->currentIndex();
	bands[b].replace(0,QString::number(v));
        ecoParameters.bands[b].replace(0,QString::number(v));
        if (!doNotChange) {
                        if (v > bands[b].at(1).toInt()){
                                label_3->setText("<font color=\"red\">" + w1 + "(" + comboBands->currentText() +  ")</font>");

                                    updateTableBandsView(error,b);

                        }
                        else
                                {
                                label_3->setText("");
                                updateTableBandsView(noError,b);
                                }
	/* Update the model */

        /*Dec 2010 */
        tableSummaryBands->item(b,0)->setText(QString::number(v));

        checkBands();

        }
        groupBands->setTitle(groupBandsTitle +"*");
        drawBandsPrices(ecoParameters.life);

        if (!doNotEmit)
            emit isDirty();
} 
void EcoVal::updateBandsA(int v)
{
	int b = comboBands->currentIndex();

        bands[b].replace(1,QString::number(v));
	/* Update the model */
	ecoParameters.bands[b].replace(1,QString::number(v));
        if (!doNotChange){
             // qDebug()<<"ECOVAL updateBandsDa";
                    if ((v) < bands[b].at(0).toInt())
                    {
                            label_3->setText("<font color=\"red\">" + w1 + "(" + comboBands->currentText() +  ")</font>");
                            if (!doNotChange)
                                updateTableBandsView(error,b);
                    }
                    else
                    {
                            label_3->setText("");
                            updateTableBandsView(noError,b);
                    }
          /*Dec 2010 */
          tableSummaryBands->item(b,1)->setText(QString::number(v));
          checkBands();
    }
	
        groupBands->setTitle(groupBandsTitle + "*");
        drawBandsPrices(ecoParameters.life);
        emit isDirtyBands();
}
void EcoVal::updateBandsVal(double v)
{
    /* We must get the Consumo interval to set the value v */
        QStringList temp;
        int b     = comboBands->currentIndex();
        int index = comboIntervals->currentIndex();

        index = index <0 ? 0 : index;

        if (!doNotChange) {
        bands[b].replace(index+2,QString::number(v));




        //bands[b].replace(2,QString::number(v));
	/* Update the model */
        ecoParameters.bands[b].replace(2+index,QString::number(v));

        updateTableBandsView();

        checkBands();
        groupBands->setTitle(groupBandsTitle + "*");
        drawBandsPrices(ecoParameters.life);
        emit isDirtyBands();
    }

}
void EcoVal::updateView(int i)
{

        doNotChange = true;
        int index   = comboIntervals->currentIndex();
        index = index <0 ? 0 : index;

	if (!bands.isEmpty()){

	spinDa->setValue(bands[i].at(0).toInt());
	spinA->setValue(bands[i].at(1).toInt());
        dValue->setValue(bands[i].at(2+index).toDouble());
	}
	else{
	spinDa->setValue(bandsDefault[i].at(0).toInt());
	spinA->setValue(bandsDefault[i].at(1).toInt());
        dValue->setValue(bandsDefault[i].at(2).toDouble());
	}
        doNotChange = false;

        checkBands();
}
void EcoVal::checkBands()
{

        int index = comboIntervals->currentIndex();
        index = index <0 ? 0 : index;
        int v,a,b,errLine;
        double epsilon = 0.0000002;
        double c;
        bool satError = false;
        bool domError = false;
	/* We suppose that the weekend bands are in number of 6, 3 for saturday and 3 for sunday */
	v=0;
        errLine = -1;
        a=b=0;
        c = 0.0;
	if (bands.isEmpty())
		bands = bandsDefault;
	for(int i=0;i< comboBands->count()-numOfWBands;i++)

	{
		a = bands[i].at(1).isEmpty() ? 0 : bands[i].at(1).toInt();
		b = bands[i].at(0).isEmpty() ? 0 : bands[i].at(0).toInt();
                c = bands[i].at(2+index).isEmpty() ? 0 : bands[i].at(2+index).toDouble();
                if (a<b)
                       errLine= i;
                c = (c>epsilon) ? 1 : 0;
                v+= (!(a!=0) && !(b!=0) )  ? (int)(c) : a - b+1;
	}
        if (errLine>=0)
            updateRowBandsView(error,errLine);

	if (v!=24)
		{
		label_3->setText("<font color=\"red\">" + w4 + "</font>");
		bandsError = true;

	}
        else{
		bandsError = false;
                label_3->setText(" ");
            }

	v =0;
        /*SABATO*/
	for(int i=comboBands->count()-numOfWBands;i<comboBands->count()-3;i++)
	{
		
		a = bands[i].at(1).isEmpty() ? 0 : bands[i].at(1).toInt();
		b = bands[i].at(0).isEmpty() ? 0 : bands[i].at(0).toInt();
                c = bands[i].at(2+index).isEmpty() ? 0 : bands[i].at(2+index).toDouble();

                if (a<b)
                       errLine= i;
                c = (c>epsilon) ? 1 : 0;
                v+= (!(a!=0) && !(b!=0) )  ? (int)(c) : a - b+1;
                //qDebug()<<"Fasce festive"<< i<<v;
		
	}
        if (errLine>=0)
            updateRowBandsView(error,errLine);
        if ((v!=24) )
		{
		label_4->setText("<font color=\"red\">" + w3 + "</font>");
                bandsError |= true;
                satError = true;

	}
        else{

                bandsError |= false;
                satError    = false;
                if (!domError)
                    label_4->setText("");
            }

        /*DOMENICA*/
	v = 0;
	for(int i=comboBands->count()-3;i<comboBands->count();i++)
	{
		
		a = bands[i].at(1).isEmpty() ? 0 : bands[i].at(1).toInt();
		b = bands[i].at(0).isEmpty() ? 0 : bands[i].at(0).toInt();
                c = bands[i].at(2+index).isEmpty() ? 0 : bands[i].at(2+index).toDouble();

                if (a<b)
                       errLine= i;
                 c = (c>epsilon) ? 1 : 0;
                v+= (!(a!=0) && !(b!=0) )  ? (int)(c) : a - b+1;
		
	}	
        if (errLine>=0)
            updateRowBandsView(error,errLine);
	if (v!=24)
		{
		label_4->setText("<font color=\"red\">" + w3 + "</font>"); 
                bandsError |= true;
                domError = true;

	}
	else
		{
                bandsError |= false;
                domError = false;
                if (!satError)
                    label_4->setText(tr(""));
		}

 
}
void EcoVal::saveBands()
{
	if (fileBands.isEmpty())
		saveBandsAs();
	else
		saveBandsValues(fileBands);

}
void EcoVal::saveBandsAs()
{
	QString fileName;
        fileName = QFileDialog::getSaveFileName(this, tr("File costi energia per fasce orarie"), recentSave, tr(" (*.scb)"));
	if (!fileName.isEmpty()){
		fileBands = fileName;
                QFileInfo fileInfo(fileName);
                recentSave = fileInfo.absoluteDir().absolutePath();
		updateRecentBands(fileName);
		saveBandsValues(fileBands);
	}
}
void EcoVal::saveBandsValues(QString fileName)
{
        QStringList header;
	if (!fileName.isEmpty() ) {
		
		fileName = MyMath::checkFormat(fileName,"scb");
		fileBands = fileName;
		QFileInfo fileInfo(fileName);
                recentSave = fileInfo.absoluteDir().absolutePath();
		QFile file(fileName);
		if( file.open(QFile::WriteOnly)){

			QTextStream out(&file);
                      //  qDebug()<<"ECO salvo file fasce"<<fileName<<file.fileName()<<bands.size();

                        //Header info
                        header = infoBands.split("\n");
                        for(int i=0;i<header.size();i++) {
                           if (!header.at(i).isEmpty())
                                out<<"#"<<header.at(i)<<"\n";

                        }

                        out<<"IVA="<<ecoParameters.VATonTotEnergy<<"\n";
                        out<<"IMP="<<ecoParameters.IMPonEnergy<<"\n";

                        for(int i=0;i<intervals.size();i++)
                            out<<"LI"<<"\t"<<QString::number(ecoParameters.intervals.at(i).x())
                               <<"\t"<<QString::number(ecoParameters.intervals.at(i).y())<<"\n";
			out<<"-SolarCalc-"<<"\t"<<"Bande"<<"\n";
                        //qDebug()<<"ECO SALVO BANDS A"<<bands.size();
			for (int i=0;i<bands.size();i++){

				out<<i<<"\t";
                                for(int j=0;j<bands[i].size();j++){
                                        //qDebug()<<"ECO SALVO BANDS B"<<bands[i].size()<<bands[i].at(j);
					out<<bands[i].at(j)<<"\t";
                                    }
		
					out<<"\n";
			}
		}
		
		
        groupBands->setTitle(groupBandsTitle );
        bandsDirty = false;
	}
	else
	{
        QMessageBox::warning(this,tr("Errore 600"),tr("Errore di scrittura nella cartella selezionata. Prova Salva come."),QMessageBox::Ok);
	}
}


int EcoVal::getBandsId(int hour,int month,int day,int year)
{
    QDate date(year,month,day);
    int d = date.dayOfWeek();
    double v;
     switch (d) {
            /* Pickup the bands for the saturday */

    case 6:
            v =  findBandId(comboBands->count()-numOfWBands,comboBands->count()-3,hour);


    break;
    case 7:
            /* Pickup the bands for the sunday */
            v =  findBandId(comboBands->count()-3,comboBands->count(),hour);

    break;
    default:
            v = findBandId(0,comboBands->count()-numOfWBands,hour);

    }
     return v;

}
double EcoVal::weightedSumTariffekW(double en, int nthYear)
{
    double a         = 0;
    double tv        = 0;
    double remEnergy = 0;
    double delta     = 0;
    int k            = 0;
    double eps       = 0.00000000002;
    remEnergy = en;
    k         = 0;
    /*Find the energy in the interval */
    if (tIntervals.isEmpty())
        return      ecoParameters.power * (
                    ecoParameters.tariffe[1].at(k) +
                    ecoParameters.tariffe[4].at(k) +
                    ecoParameters.tariffe[18].at(k) +
                    ecoParameters.tariffe[7].at(k)  +
                    ecoParameters.tariffe[9].at(k)  )/100;

    while ((remEnergy>eps) && k<=tIntervals.size()){
        delta = tIntervals.at(k).y()-tIntervals.at(k).x();
        /*pedaggiokWh wrt to the  interval*/
        tv =    ecoParameters.power * (
                ecoParameters.tariffe[1].at(k) +
                ecoParameters.tariffe[4].at(k) +
                ecoParameters.tariffe[18].at(k) +
                ecoParameters.tariffe[7].at(k)  +
                ecoParameters.tariffe[9].at(k)  )/100;

        /* we ar the end?*/
        if (remEnergy >= delta ){
            a +=   MyMath::inflate(nthYear,ecoParameters.inflRate/100,tv);
            remEnergy -= delta;
        }else{
            a +=  MyMath::inflate(nthYear,ecoParameters.inflRate/100,tv);
            remEnergy = -1;
        }

        k++;
}
   // qDebug()<<"ECO wsTkw"<<tIntervals<<remEnergy<<a;
    return a;
}

double EcoVal::weightedSumTariffekWh(double en, int nthYear)
{
    double a         = 0;
    double tv        = 0;
    double remEnergy = 0;
    double delta     = 0;
    int k            = 0;
    double eps       = 0.00000002;
    remEnergy = en;
    k         = 0;
    /*Find the energy in the interval */
    tv = (ecoParameters.tariffe[3].at(0) +
          ecoParameters.tariffe[17].at(0) +
          ecoParameters.tariffe[0].at(0) +
          ecoParameters.tariffe[6].at(0) +
          ecoParameters.tariffe[8].at(0) +
          ecoParameters.tariffe[21].at(0))/100;
    if (tIntervals.isEmpty())
    {
        //qDebug()<<"ECO wsTkwh 1 interval"<<tv<<remEnergy<<a<<k<<en<<MyMath::inflate(nthYear,ecoParameters.inflRate/100,tv);
        return  en * MyMath::inflate(nthYear,ecoParameters.inflRate/100,tv);
    }

    while ((remEnergy>eps) && k<=tIntervals.size()){
        delta = tIntervals.at(k).y()-tIntervals.at(k).x();
        /*pedaggiokWh wrt to the  interval*/
        tv =   (ecoParameters.tariffe[3].at(k) +
                ecoParameters.tariffe[17].at(k) +
                ecoParameters.tariffe[0].at(k) +
                ecoParameters.tariffe[6].at(k) +
                ecoParameters.tariffe[8].at(k) +
                ecoParameters.tariffe[21].at(k)
                )/100;

        /* we ar the end?*/
        if (remEnergy >= delta ){
            a += delta * MyMath::inflate(nthYear,ecoParameters.inflRate/100,tv);
            remEnergy -= delta;
        }else{
            a += remEnergy *MyMath::inflate(nthYear,ecoParameters.inflRate/100,tv);
            remEnergy = -1;
        }

        k++;
}
   // qDebug()<<"ECO wsTkwh"<<tIntervals<<remEnergy<<a<<k<<en;
    return a;
}

double EcoVal::weightedSumCus(double en, double es, int nthYear)
{
    /* en prelevata*/
    /* es scambiata */
    double a         = 0;
    double tv        = 0;
    double remEnergy = 0;
    double delta     = 0;
    int k            = 0;
    int start        = 0;
    double eps       = 0.00000002;




    /* Cerca intervallo */

    for(int i = tIntervals.size()-1; i>=0;i--){
       if ((tIntervals.at(i).y()-en> eps)
           &&
                   (tIntervals.at(i).x()- en<= eps) )    {
           start = i;
           break;
        }
   }


    /*Find the energy in the interval */
    /* Per il Cus si prendono si parte dagli scaglioni + alti */

    tv = (ecoParameters.tariffe[3].at(start) +
          ecoParameters.tariffe[17].at(start) +
          ecoParameters.tariffe[0].at(start) +
          ecoParameters.tariffe[6].at(start) +
          ecoParameters.tariffe[8].at(start)
          )/100;

    if (tIntervals.isEmpty())
        return    MyMath::inflate(nthYear,ecoParameters.inflRate/100,tv);

//    if (es < tIntervals.at(0).y()){
//        delta = tIntervals.at(0).y() - es;
//        remEnergy -= delta;
//        a += delta * MyMath::inflate(nthYear,ecoParameters.inflRate/100,tv);
//        return a;
//    }
    remEnergy = es;

    k     = start;
     // qDebug()<<"ECO wsCus START"<<remEnergy<<k<<delta<<tv<<delta*tv<<a;
    while ((remEnergy>eps) && k>=0){



        if (k==start)
            delta = en -tIntervals.at(k).x();
        else
            delta = tIntervals.at(k).y() - tIntervals.at(k).x();


        /*pedaggiokWh wrt to the  interval*/
        tv =   (ecoParameters.tariffe[3].at(k) +
                ecoParameters.tariffe[17].at(k) +
                ecoParameters.tariffe[0].at(k) +
                ecoParameters.tariffe[6].at(k) +
                ecoParameters.tariffe[8].at(k)
                )/100;
        tv = MyMath::inflate(nthYear,ecoParameters.inflRate/100,tv);

        /* we are the end?*/
        if (remEnergy >= delta ){
            a += delta * tv;
            remEnergy -= delta;
        //  qDebug()<<"ECO wsCus"<<remEnergy<<k<<delta<<tv<<delta*tv<<a;
        }else{
            a += remEnergy * tv;
     //       qDebug()<<"ECO wsCus"<<remEnergy<<k<<delta<<tv<<delta*tv<<a;
            remEnergy = -1;
        }

        k--;
}


    return a/es; //weighted sum
}

double EcoVal::weightedSumBands(double en,int whichone, int nthYear)
{
    double a         = 0;
    double bv        = 0;
    double remEnergy = 0;
    double delta     = 0;
    int k            = 0;
    double eps       = 0.0000002;
    remEnergy = en;
    k         = 0;
    /*Find the energy in the interval */
//qDebug()<<"ECOVAL weightBands"<<en<<(remEnergy>eps);
//NO CONSUMPTION?
if (en<eps)
    return 0;
    if (intervals.isEmpty())
{
        if (whichone<bands.size())
        {
            qDebug()<<"ECO exit in wsumbands";
            return remEnergy*inflateBandPrice(bands[whichone].at(2).toDouble()/100,nthYear);
        }
        else
        {
            qDebug()<<"ERRORE DI DIMESNIONE IN ecoval"<<whichone;
            exit(-1);
        }
 }

    while ((remEnergy>eps) && k<=intervals.size()){
        delta = intervals.at(k).y()-intervals.at(k).x();
        /*cost of energy wrt to the band and int.*/
        bv = bands[whichone].at(k+2).toDouble();
        /* we ar the end?*/
        if (remEnergy >= delta ){
            a += delta * inflateBandPrice(bv/100,nthYear);
            remEnergy -= delta;
        }else{
            a += remEnergy * inflateBandPrice(bv/100,nthYear);
            remEnergy = -1;
        }

        k++;
}
//qDebug()<<"ECOVAL weightBands end"<<a;
    return a;
}

double EcoVal::getYearlyEnergyCost(const QVector<double> &f,int nthYear)
        /* Returns the energy cost by considering  the */
        /* energy f in one year  and the */
        /* load intervals                             */
        /* f must be the same size of bands           */
{
    double a         = 0;

    if (f.size()!=bands.size())
    {
    qDebug()<<"*****************ECOVAL WARNING ****************************";
    qDebug()<<"in getEnergyCost(QVector<double> f"<<f;
    exit(-1);
    }
    // findValue return a value in cents

    /* For every band...*/
    for(int i=0; i< f.size(); i++ )
    {
        a = a + weightedSumBands(f.at(i),i,nthYear);

     }


     // qDebug()<<"ECO GETYEARLYENERGYCOST"<<a;
 return a;
}




double EcoVal::getEnergyCost(int hour,int month,int day,int year,int nthYear)
{
	/* For now we forget month and year */
	/* The result is given in cents */
	QDate date(year,month,day);
	int d = date.dayOfWeek();
        double v;
	 switch (d) {
		/* Pickup the bands for the saturday */
		
	case 6:
                v =  findValue(comboBands->count()-numOfWBands,comboBands->count()-3,hour);
		
		
	break;
	case 7:
                /* Pickup the bands for the sunday */
                v =  findValue(comboBands->count()-3,comboBands->count(),hour);
		
	break;
	default:
                v = findValue(0,comboBands->count()-numOfWBands,hour);
		
	}
         return inflateBandPrice(v,nthYear);
	
}


double EcoVal::findValue(int whichBand, double en)
{
    /*Find the band value according to the load intervals */

    int i = whichBand;

        if (intervals.size()!=0){
          for(int k=0;k<intervals.size();k++){
           /* We are inside some interval OR  */
           /* outside all unbounded intervals */
            if ((en >= intervals.at(k).x()  &&
                 en <= intervals.at(k).y()) ){

                if (bands[i].size()< k+3){
                    qDebug()<<"ECOVAL findValue(int,double) WARNING"<<bands<<i<<k;
                    exit(-1);
                }
                else

                return bands[i].at(k+2).toDouble();
            }
           }

        }
         else
           return bands[i].at(2).toDouble();


        return 0;
}
int EcoVal::findTariffeIntervalId(int i, double epr)
        /*Given the index of the Tariffe */
        /* return the correct value      */
        /* according to epr              */
{

    if (ecoParameters.tIntervals.size()!=0){
      for(int k=0;k<ecoParameters.tIntervals.size();k++){
       /* We are inside some interval OR  */
       /* outside all unbounded intervals */
        if ((epr >= ecoParameters.tIntervals.at(k).x()  &&
             epr <= ecoParameters.tIntervals.at(k).y()) ){

            if (ecoParameters.tariffe[i].size()<k ){
                qDebug()<<"ECOVAL findTariffeInterval ERROR"<<k<<ecoParameters.tariffe[i].size();
            exit(-1);
            }
            else
                return k;
        }
       }

    }
     else
       return 0;


    return 0;
}

int EcoVal::findBandId(int startBand, int endBand,int hour)
{
    for(int i=startBand;i<endBand;i++)
    {
        if (hour >= bands[i].at(0).toInt() && hour<= bands[i].at(1).toInt() )
         return i;
    }

    return 0;
}

double EcoVal::getInjectedPrice(int b,int month,int year)
{
    // qDebug()<<"ECO mPrezziEnergi get Injected Pricesa"<<mPrezziEnergia<<month<<b<<ecoParameters.inflEnergyRate/100<<year;
        if ((month<12) && (b<12))
            return MyMath::inflate(year,ecoParameters.inflEnergyRate/100,mPrezziEnergia.at(month).at(b));
        else
            return 0;
}

double EcoVal::findImmPrice(double a,int year)
/* Level is in kWh */
/* while pIntervals in MWh */
/* prices immissione are in c/MWh*/
/* Return the value in unit money by considering the injected energy divided in intervals */
/* This is valid for RITIRO DEDICATO */
{
    double level = a/1000;
    double v = 0;
    double price = 0;
    if (pIntervals.size() == 0)
    {
        if (ecoParameters.immissione.isEmpty())
            return 0;
        else
            return ecoParameters.immissione.at(0);
    }
    for(int i=0;i<pIntervals.size();i++)
    {
        price = MyMath::inflate(year,ecoParameters.prezziMinEnergiaInflazione/100,
                                ecoParameters.immissione.at(i));
        if (level >  pIntervals.at(i).y())
        {
            v += price * (pIntervals.at(i).y()-pIntervals.at(i).x());

            continue;
        }
        else
        {
        if (level >= pIntervals.at(i).x()
            &&
           level <= pIntervals.at(i).y())
            v += price * (level - pIntervals.at(i).x() );
    }
    }
    return v;
}

double EcoVal::findValue(int startBand, int endBand,int hour)
{
    /*Find the 1st energy price of the right band value  */
	for(int i=startBand;i<endBand;i++)
	{
		if (hour >= bands[i].at(0).toInt() && hour<= bands[i].at(1).toInt() )
// 				qDebug()<<"ECOVAL findValue"<<bands[i].at(2).toDouble();
				return bands[i].at(2).toDouble();
	}
	return 0;
}
void EcoVal::loadB()
{
	if (loadBands(""))
    {
                updateRecentBands(fileBands);
              //  qDebug()<<"loadBands FILENAME"<<fileBands;
                checkBands();
                setEcoBands();

                updateIntervalsView();
                updateTableBandsView();
                dVATonEn->setValue(ecoParameters.VATonTotEnergy);
                dIMPkWh->setValue(ecoParameters.IMPonEnergy);
                //updateEcoParView();
                if (ecoParameters.life==0)
                    drawBandsPrices(30);
                else
                    drawBandsPrices(30);

    }
 }
bool EcoVal::loadBands(QString input)
{
        QString s,fileName,asterisk,w;
        int count,li;
        bool ok1,ok2;
        double d1,d2,d;


        QPolygonF tempIntervals;
	QStringList splitted;
	QList<QStringList> tempBands(bandsDefault);
	if (input.isEmpty())
                 fileName = QFileDialog::getOpenFileName(this, tr("File costi energia per fasce orarie"), recentDir, tr("Prezzi orari ")+" (*.scb )");
	else
		fileName = input;

	QFile file(fileName);
        if (!fileName.isEmpty() && !file.exists()){
            qDebug()<<"loadBands ERROR"<<fileName;
            QMessageBox::warning(this,tr("File fasce orarie"),tr("Il file non esiste"));
            return false;
        }

	if (!fileName.isEmpty() &&  file.open(QFile::ReadOnly)) {
                recentDir = QFileInfo(fileName).absoluteDir().absolutePath();
		QTextStream in(&file);
                count = 1;
                li    = 0;
		infoBands ="";
		 while (!in.atEnd()) {
		 
                        s = in.readLine().simplified();
                        if (s.isEmpty() || s.isNull())
                            continue;
			asterisk = s;
                        
                        if (s.split("=").size()>0 && s.split("=").at(0).simplified()=="IVA"){
                            w = s.split("=").at(1);
                            w.replace(" ","");
                            d = w.toDouble(&ok1);
                            if (!ok1)
                                fireError(500);
                            else
                                ecoParameters.VATonTotEnergy = d;

                            continue;
                        }
                        if (s.split("=").size()>0 && s.split("=").at(0).simplified()=="IMP"){
                            w = s.split("=").at(1);
                            w.replace(" ","");
                            d = w.toDouble(&ok1);
                            //qDebug()<<"ECOVAL loadBands"<<d<<ok1;
                            if (!ok1)
                                fireError(500);
                            else
                                ecoParameters.IMPonEnergy = d;

                            continue;
                        }
                        if (s.split(" ").size()==3 && s.split(" ").at(0).simplified()=="LI"){
                            w1 = s.split(" ").at(1);
                            w2 = s.split(" ").at(2);
                            w1.replace(" ","");
                            w2.replace(" ","");
                            d1  = w1.toDouble(&ok1);
                            d2  =  w2.toDouble(&ok2);
                            li++;
                            if (!ok1 && !ok2)
                                fireError(500);
                            else{
                                tempIntervals << QPointF(d1,d2);

                                }
                            continue;
                        }
			if (asterisk.indexOf("#") == 0 ) {
                            infoBands += asterisk.replace("#","") + "\n";
					continue;
			}
                        else
                        {


                                if (count==1){

                                        
                                        splitted = s.split(" ");
                                        if ((splitted.at(0)!="-SolarCalc-") && splitted.at(1)!="Bande" ){
                                                QMessageBox::warning(this,tr("Bande orarie - Errore 700"),tr("SolarCalc non riesce a leggere il contenuto del file. Controlla se il file risulta corrotto."),QMessageBox::Ok);
                                                qDebug()<<"ECOVAL BANDSLOAD ERROR"<<s<<splitted;
                                                return false;
                                                }

                                                count+=1;
                                }
                                else
                                {

                                        s = s.simplified();
                                        splitted = s.split(" ");
                                        ok1 = true;
                                        ok2 = true;
                                        for(int i=0;i < splitted.size();i++){
                                           d1 = splitted.at(i).toDouble(&ok1);
                                           ok2 = ok2 & ok1;
                                       }
                                        //TO FINISH!!//
                                        if ((((splitted.size()-3) != li) &&
                                            tempIntervals.size()>0)

                                            || !ok2 ||
                                            (tempIntervals.size()==0 && splitted.size()!=4))
                                            {
                                        QMessageBox::warning(this,tr("Bande orarie - Errore 701"),tr("Il file sembra non contenere dati corretti"),QMessageBox::Ok);
                                        qDebug()<<"ECOVAL ERROR 701"<<splitted<<li<<splitted.size()<<ok2;
                                                return false;
                                        }
                                        else
                                        {
                                         fileBands = fileName;
                                         ecoParameters.fileBands = fileBands;

                                        if (count<=numBands+1){
						
                                                tempBands[count-2] = splitted.mid(1);
                                                //  qDebug()<<"ECO loaded band"<<splitted.mid(1)<<count<<tempBands[count-2]<<numBands;
                                        count+=1;
                                        }

                                        }
                                }
                        }
		}
	
        //updateView(0);
	bands.clear();
	bands = tempBands;
        intervals.resize(0);
        intervals = tempIntervals;

        return true;
	
	}
	
}
bool EcoVal::bandError()
{
	return bandsError;
}
EcoVal::~EcoVal()
{
	
}
void EcoVal::alignScales()
{
    // The code below shows how to align the scales to
    // the canvas frame, but is also a good example demonstrating
    // why the spreaded API needs polishing.

    
//    qwtPrezzi->canvas()->setFrameStyle(QFrame::Box | QFrame::Plain );
//    qwtPrezzi->canvas()->setLineWidth(1);
    qwtMinPrezzi->canvas()->setFrameStyle(QFrame::Box | QFrame::Plain );
    qwtMinPrezzi->canvas()->setLineWidth(1);

    qwtBands->canvas()->setFrameStyle(QFrame::Box | QFrame::Plain );
    qwtBands->canvas()->setLineWidth(1);
    

    for ( int i = 0; i < qwtMinPrezzi->QwtPlot::axisCnt; i++ )
    {
        QwtScaleWidget *scaleWidget = (QwtScaleWidget *)(qwtMinPrezzi->axisWidget(i));
        if ( scaleWidget )
            scaleWidget->setMargin(0);

        QwtScaleDraw *scaleDraw = (QwtScaleDraw *)qwtMinPrezzi->axisScaleDraw(i);
        if ( scaleDraw )
            scaleDraw->enableComponent(QwtAbstractScaleDraw::Backbone, false);
    }
// for ( int i = 0; i < qwtPrezzi->QwtPlot::axisCnt; i++ )
//    {
//        QwtScaleWidget *scaleWidget = (QwtScaleWidget *)(qwtPrezzi->axisWidget(i));
//        if ( scaleWidget )
//            scaleWidget->setMargin(0);

//        QwtScaleDraw *scaleDraw = (QwtScaleDraw *)qwtPrezzi->axisScaleDraw(i);
//        if ( scaleDraw )
//            scaleDraw->enableComponent(QwtAbstractScaleDraw::Backbone, false);
//    }

 for ( int i = 0; i < qwtBands->QwtPlot::axisCnt; i++ )
    {
        QwtScaleWidget *scaleWidget = (QwtScaleWidget *)(qwtBands->axisWidget(i));
        if ( scaleWidget )
            scaleWidget->setMargin(0);

        QwtScaleDraw *scaleDraw = (QwtScaleDraw *)qwtBands->axisScaleDraw(i);
        if ( scaleDraw )
            scaleDraw->enableComponent(QwtAbstractScaleDraw::Backbone, false);
    }
     
}


QVector<double> EcoVal::getContribute(QPolygonF &EProd,QPolygonF &Epr,QPolygonF &Ei,QPolygonF &vEi,double oe_,double fc,double c, int year)
/* This function returns the yearly contribute due to the exchanged energy with the public grid */
/* Input are 12 values vector*/
/* If year = 0 we use mPrezziEnergia, otherwise we use the predicted values. Years start from 0. */
/* 1         = contribute in unit value*/
/* 2         = Cei*/
/* 3	     = credit for next year            */
/* 4         = Exchanged energy             */
/* 5	     = Bonus*/
/* 6         = Oe*/
/* 7         = Cus or cost/earn from sellings in case of Selling regime*/
/* 8         = Injected Energy * k       */
/* 9         = Used credit               */

/* Oe = Costo energia prelevata = B(h)xEpr(h)   */
 
/*For Producers, only the first term is set as  */
{
        double price = 0;
        double Cei,epr,ei,Es,Cus,credit,o,oe,CusEs,tot,cor,corInflated,os,usedCredit,
        camm,v_amm,v_costs,v_tra,v_ctr;
        o = tot =   cor = corInflated = os = camm = 0;
        Cei=epr=ei=Es=Cus=credit=oe= CusEs =0;
       v_amm = v_costs = v_tra = v_ctr=0;
	QVector<double> Output;

        int index;
        int type = ecoParameters.regime;

        epr   = MyMath::cumSum(Epr); //Fetched
        index = findTariffeIntervalId(0,epr);

        //oe  = MyMath::cumSum(Oe);  //Fetched energy cost
        oe = oe_;


        if ((EProd.size()!=12)||Ei.size()!=12)
            qDebug()<<"ECO EPROD size"<<EProd.size()<<Ei.size();
	switch (type) {
		/* All values are in cents!*/
		case Vendita:


                        index = 0; //TO CHECK!!
                        // Sold energy/////////////////////////////////////////
                        // If the intervals are enabled, do not Use min prices //
                        // tot = Energia immessa annualmente
                        // o   = controvalore monetario
                        if (ecoParameters.useImmIntervals)
                        {
                            tot = MyMath::cumSum(Ei); /*this is in kWh */
                            price = findImmPrice(tot,year)/100;/* this is in c/Mwh*/
                            o += ecoParameters.tariffe[19].at(index) * price;
                        //   qDebug()<<"ECOVENDITA price"<<o<<price<<tot<<ecoParameters.prezziMinEnergiaInflazione/100;
                        }
                        else
                        {
                        for(int i=0;i<Ei.size();i++){
                        // Moltiplica l'energia immessa per il f.d.perdita
			if ((minEnergyPrices.size()<=12))
                                 o+= ecoParameters.tariffe[19].at(index)*
                                     Ei.at(i).y() * minEnergyPrices.at(i)/100;
			else
                                o+=  ecoParameters.tariffe[19].at(index)*
                                     Ei.at(i).y() * minEnergyPrices.at(year*12 + i)/100;

                        tot +=Ei.at(i).y(); //Totale Energia immessa
                    }
                        //qDebug()<<"ECOVAL CONTRIBUTE EN"<<minEnergyPrices.at(year*12 + i)/100 -ecoParameters.tariffe[15]/100;
			}
		/* Subtract passive values or costs*/


                v_tra = ecoParameters.tariffe[11].at(index)/100 * tot; // Perdita per trasmissione;

                // CTRkWh di En. immessa x
                // x Fatt CTR x En. immessa  maggiorata
                v_ctr = ecoParameters.tariffe[14].at(index)*
                       ecoParameters.tariffe[13].at(index)*tot/100 ;


                v_costs = ecoParameters.tariffe[15].at(index)*12;


                // Altri Costi mensili
                camm = ecoParameters.tariffe[12].at(index)/100 * o;    // Costi Amministrativi
                                                                       // relativi a val. En.
                if (camm < ecoParameters.ammCostLimit)
                    v_amm = camm;
                else
                    v_amm = ecoParameters.ammCostLimit;

                cor = v_ctr - v_tra - v_amm - v_costs;

                corInflated = MyMath::inflate(year,ecoParameters.fasceInflazione/100,cor);
                o += corInflated; //Aggiungo i corrispettivi inflazionati
               // qDebug()<<"COR "<<v_ctr<<v_costs<<v_tra<<v_amm;
                // qDebug()<<"ECOVAL VENDITA"<<o<<cor<<corInflated<<tot<<camm
                         //<<ecoParameters.ammCostLimit;
                Output<<o<<0<<0<<0<<getBonuses(year)<<0<<corInflated<< tot*ecoParameters.tariffe[19].at(index);
		break;
                case SSPIT || SSP:
                /* SCAMBIO SUL POSTO GENERICO AGGIORNATO 2009/10*/
                //Injected * loss factor
                ei  = ecoParameters.tariffe[19].at(index) * MyMath::cumSum(Ei);
                Es = MyMath::min(epr,ei);
                        for(int i=0;i<Ei.size();i++){

                             //moltiplica per il loss factor
                             // vEi is in euro
                             Cei  += ecoParameters.tariffe[19].at(0)*
                             vEi.at(i).y();
                             //*sold energy*/

			}


			
                        oe += fc; //Costi fissi quali IVA e Erario

                        credit  = MyMath::max(0,c+Cei-oe);




                        //MCT ([21]) is not added //
                        if (Es>0.00000002){
                            Cus = weightedSumCus(epr,Es,year);//contiene inflazione

                        }
                        else
                        {
                            Cus   = -1;

                        }

                          // qDebug()<<"ECO cUS"<<Cus<<Es;
   			
                        // Liquidazione credito?
                        if (!ecoParameters.credit){
                           /* c is the credit of the previous year*/
                            credit     = MyMath::max(0,c+Cei-oe);
                            usedCredit = MyMath::max(0,MyMath::min(c,oe-Cei));
                            os = (MyMath::min(Cei,oe) + usedCredit +  Cus*Es);
                           Output<< os;
                         }
                         else
                         {
                           // Se i crediti sono liquidati, non usiamo
                           // il credito precedente
                           credit     = MyMath::max(0,Cei-oe);
                           usedCredit = credit;
                           os = (MyMath::min(Cei,oe) +  Cus*Es);
                           Output<< os;
                         }


                 //  qDebug()<<"ECOVAL CONTR"<<year<<oe<<Cei<<Cus<<Es<<os<<fc;
                        Output<<Cei<<credit<<Es<<getBonuses(year)<<oe<<Cus<<ei<<usedCredit;


			
		break;

                default:
                    Output.fill(0,5);
                    break;

                }
        return Output;
    }
void EcoVal::loadMinP()
{
	if (loadMinPrezzi(""))
		{
		updateMinPrezziView();
		updateMinPrezziLabel(fileMinPrezzi);
		}
}
bool EcoVal::loadMinPrezzi(QString input)
{
	QString s,fileName,asterisk;
	int count;
        bool neg = false;
	QVector<double> temp;
	QStringList splitted;
	if (input.isEmpty() ){
		 /* Check in the project Folder */
		 fileName = QFileDialog::getOpenFileName(this, tr("File prezzi minimi energia"), recentDirPrezzi, "Text files (*.scpm)");
		 }
	else
		fileName = input;

// 	qDebug()<<"ECO loadPrezzi minimi"<<fileName;
	QFile file(fileName);
	if (!fileName.isEmpty() &&  file.open(QFile::ReadOnly)) {
  		recentDirMinPrezzi = QFileInfo(fileName).absoluteDir().absolutePath();
		QTextStream in(&file);
		count =0;
		infoPrezziMinimi = "";
		 while (!in.atEnd()) {
 			s = in.readLine();
                        if (s.isEmpty() || s.isNull())
                            continue;
			asterisk = s;
			if (asterisk.indexOf("#") == 0 ){
                            infoPrezziMinimi += asterisk.replace("#","") + "\n";
				continue;
			}
                        else
                        {
			s = s.simplified();
			
 			temp<<s.toDouble();
                        if (s.toDouble()<0)
                                neg = true;
// 			mPrezziEnergia[count] = s.toDouble();
//   			qDebug()<<"ECO loadPrezzi"<<s<<count<<s.toDouble()<<mPrezziEnergia[count];
  			count++;
                    }
	
		}
	
		if (count!=12)
                        return false;
		else
                        {

                                if (temp.contains(0) || neg)
                                {
                                        labelWarnMin->setText("<font color=\"red\"> " + tr("Un prezzo &egrave; negativo o nullo") + "</font>");

                                }
                                else
                                {
                                        labelWarnMin->setText("");
                                }
			
  			fileMinPrezzi = fileName;
//   	qDebug()<<"ECO loadPrezzi inside"<<fileName<<count<<dPeriodo->value();
  			minEnergyPrices.resize(0);
  			minEnergyPrices = temp;
			processMinEnergyPrices( );
                        return true;
			}
	}
	else
                return false;
}
void EcoVal::loadP()
{
	if (loadPrezzi(""))
		{
		updatePrezziView();
                qDebug()<<"ECO loadP "<<filePrezzi;
		updatePrezziLabel(filePrezzi);
		}
}
bool EcoVal::loadPrezzi(QString input)
{
	QString s,fileName,asterisk;
	int count;
	bool neg=false;
        QVector< QVector<double> > temp;
	QStringList splitted;

	if (input.isEmpty())
		 fileName = QFileDialog::getOpenFileName(this, tr("File prezzi energia"), recentDirPrezzi, tr("File prezzi") +  "(*.scp)");
	else
		fileName = input;

//
	QFile file(fileName);
	if (!fileName.isEmpty() &&  file.open(QFile::ReadOnly)) {

  		recentDirPrezzi = QFileInfo(fileName).absoluteDir().absolutePath();
		QTextStream in(&file);
		count =0;
		infoPrezzi = "";
                temp.resize(12);

		 while (!in.atEnd()) {

                        s = in.readLine().simplified();
                        if (s.isEmpty() || s.isNull())
                            continue;
			asterisk = s;
			if (asterisk.indexOf("#") == 0 ){
                            infoPrezzi += asterisk.replace("#","") + "\n";
				continue;
			}
                        else
                        {

                                temp[count].resize(ecoParameters.numBands);
                                splitted = s.split(" ");
                                temp[count]  << MyMath::toVectorDouble(splitted);
                                if (temp[count].contains(-1))
                                        neg = true;

                                qDebug()<<"ECO loadPrezzi"<<splitted;
                                count++;

                        }
                    }

                        if (count!=12)
                                return false;
                        else
                        {

                                filePrezzi = fileName;
        //   			qDebug()<<"ECO loadPrezzi inside"<<fileName<<count<<dPeriodo->value();
//                                if (temp.contains(0) || neg)
//                                {
//                                        labelWarn->setText("<font color=\"red\"> " + tr("Un prezzo &egrave; negativo o nullo") + "</font>");

//                                }
//                                else
//                                {
//                                        labelWarn->setText("");
//                                }
                                mPrezziEnergia.resize(12);
                                for(int i=0;i<12;i++)
                                mPrezziEnergia[i] << temp.at(i);
                                /* Dismissed for now */
                                //processEnergyPrices( );
                                return true;

                        }
	}
	else
                return false;

}
void EcoVal::loadTax()
{
    if (getTaxFromFile("")){
                updateRecentTax(fileTax);
                doNotUpdate = true;
                /*Update View*/
                updateTaxView();
                doNotUpdate = false;
            }

}
void EcoVal::loadTariffe()
{
    if (getTariffeFromFile("")){
		updateRecent(fileTariffe);
                /* Update Model special data function*/
                /* not handled in the load() */
                updateTIntervalsView();
                updatePedaggiokWh();
                updatePedaggiokW();
                setLossFactor( );
                doNotUpdate = true;
                /*Update View*/
                updateTariffeView();
                doNotUpdate = false;
            }
		 
}
bool EcoVal::getTaxFromFile(QString input)
{
        QString s,fileName,asterisk;
        int count,d1;
        QStringList splitted;
        bool ok1,ok2;
        double d2;



        if (input.isEmpty())
                fileName = QFileDialog::getOpenFileName(this, tr("File imposte"), recentDirTax, "Taxes files (*.tax  )");
        else
                fileName = input;
        QFile file(fileName);
        if (!file.exists() && !fileName.isEmpty()){
            QMessageBox::warning(this,tr("File imposte"),tr("Il file non esiste"));
            return false;
        }
        if (!fileName.isEmpty() &&  file.open(QFile::ReadOnly)) {
                QFileInfo fileInfo(fileName);
                QTextStream in(&file);
                count =1;
                recentDirTax = fileInfo.absoluteDir().absolutePath();
                infoTax = "";
                 while (!in.atEnd()) {
                        s = in.readLine();
                        if (s.isEmpty() || s.isNull())
                            continue;
                        asterisk = s;
                        //qDebug()<<"ECO asterisk"<<asterisk.split("#");
                        if (asterisk.indexOf("#") == 0)
                        {

                            infoTax +=asterisk.replace("#","") + "\n";

                                        continue;
                        }
                        else {


                                if (count==1){

                                        s =s.simplified();
                                        splitted = s.split(" ");
                                        if ((splitted.at(0)!="-SolarCalc-") ){
                                                QMessageBox::warning(this,tr("File non corretto"),tr("SolarCalc non riesce a leggere il contenuto del file. Controlla se il file risulta corrotto."),QMessageBox::Ok);
                                                return false;
                                                }

                                                count+=1;
                                }
                                else
                                {

                                        s = s.simplified();
                                        splitted = s.split(" ");

                                        d1 = splitted.at(0).toInt(&ok1);
                                        d2 = splitted.at(1).toDouble(&ok2);
                                        if ((splitted.size()!=2) || !ok1 || !ok2 ){
                                                QMessageBox::warning(this,tr("File non corretto"),tr("Il file sembra non contenere dati corretti"),QMessageBox::Ok);
                                                qDebug()<<"LOAD TAX ERRORS"<<ok1<<ok2;
                                                return false;
                                        }
                                        else
                                    {
                                        fileTax = fileName;
                                        ecoParameters.fileTax = fileTax;



                           if (d1>=0 && d1 <TASSESIZE){
                                ecoParameters.taxes[d1] = d2;
                               //qDebug()<<"ECO LOAD tasee"<<d1<<d2<<ecoParameters.taxes[d1];

                                        }

                                    }
                        }
                    }
                }

         return true;
        }
        return false;
}

bool EcoVal::getTariffeFromFile(QString input)
{
        QString s,fileName,asterisk,w1,w2;
        int count,ti;
	QStringList splitted;
        bool ok1,ok2;
        double d1,d2,d3,d4,v;
        QPolygonF tempTIntervals;

        d1 = d2 = d3 = d4  = v =0;

	if (input.isEmpty())
                fileName = QFileDialog::getOpenFileName(this, tr("File oneri accessori"), recentDirTariffe, "Text files (*.scta  )");
	else
		fileName = input;
	QFile file(fileName);
        if (!file.exists() && !fileName.isEmpty()){
        qDebug()<<"ECOVAL TARIFFE LOAD ERROR"<<fileName;
            QMessageBox::warning(this,tr("File Tariffe"),tr("Il file non esiste"));
            return false;
        }
	if (!fileName.isEmpty() &&  file.open(QFile::ReadOnly)) {
                QFileInfo fileInfo(fileName);
		QTextStream in(&file);
		count =1;
                ti    =0;
                recentDirTariffe = fileInfo.absoluteDir().absolutePath();
		infoTariffe="";
		 while (!in.atEnd()) {
			s = in.readLine();
                        s =s.simplified();
                        if (s.isEmpty() || s.isNull())
                            continue;
			asterisk = s;
                        //qDebug()<<"ECO asterisk"<<asterisk.split("#");
			if (asterisk.indexOf("#") == 0)
			{

                            infoTariffe +=asterisk.replace("#","") + "\n";
                                        qDebug()<<"ECO info"<<infoTariffe;
					continue;
			}
                        else {
                            //qDebug()<<"ECOVAL CARICA TARIFFE"<<s;
                            if (s.split(" ").size()==3 &&
                                s.split(" ").at(0).simplified()=="TI"){
                                    w1 = s.split(" ").at(1);
                                    w2 = s.split(" ").at(2);
                                    w1.replace(" ","");
                                    w2.replace(" ","");
                                    d3  = w1.toDouble(&ok1);
                                    d4  =  w2.toDouble(&ok2);
                                    ti++;

                                    if (!ok1 && !ok2)
                                        fireError(500);
                                    else{
                                        tempTIntervals << QPointF(d3,d4);

                                        }
                                    continue;
                          }


                                if (count==1){

                                    splitted = s.split(" ");




                                        if ((splitted.at(0)!="-SolarCalc-") ){
                                                QMessageBox::warning(this,tr("Oneri - Errore 700"),tr("SolarCalc non riesce a leggere il contenuto del file. Controlla se il file risulta corrotto."),QMessageBox::Ok);
                                                qDebug()<<"ECOVAL"<<splitted;
                                                return false;
                                                }
                                        else
                                        {

                                         count+=1;
                                         continue;
                                        }



                                 }
                                 else
                                 {
                                   //CHECK DATA CONSISTENCY//
                                    ok1 = ok2 = true;
                                    s = s.simplified();
                                    splitted = s.split(" ");
                                    for(int i=0;i < splitted.size();i++){
                                        d1 = splitted.at(i).toDouble(&ok1);
                                        ok2 = ok2 & ok1;
                                    }
                                    //CHECK FORMAT         //
                                    if (((splitted.size()-1!= ti) &&
                                        tempTIntervals.size()>0)
                                        || !ok2 ||
                                       (tempTIntervals.size()==0 && splitted.size()!=2))
                                        {
                                                QMessageBox::warning(this,tr("Tariffe - Errore 702"),tr("Il file sembra non contenere dati corretti"),QMessageBox::Ok);
                                                qDebug()<<"ECOVAL ERROR 702"<<splitted<<ti<<splitted.size()<<ok2;
                                                        return false;
                                                }
                                    else
                                    {

                                    fileTariffe = fileName;
                                    ecoParameters.fileTariffe = fileTariffe;
                                    v 	  = splitted.at(1).toDouble();

                                        if (count<=ecoParameters.tariffe.size()+1){

                                             ecoParameters.tariffe[count-2].clear();
                                             ecoParameters.tariffe[count-2] =
                                                     QVector<double>(MyMath::toVectorDouble(splitted.mid(1)));
                                                //  qDebug()<<"ECO loaded band"<<splitted.mid(1)<<count<<tempBands[count-2]<<numBands;
                                                count+=1;

                                        }
                                    }
                                }
		}

		
	}
        tIntervals.clear();
        tIntervals = tempTIntervals;
        ecoParameters.tIntervals.clear();
        ecoParameters.tIntervals = tIntervals;
        return true;
    }
        return false;
}
void EcoVal::deleteBandsFile()
{
    model->removeRow(listBands->currentIndex().row());
    recentBandsFileName = model->stringList();
}

void EcoVal::updateRecentBands(QString s )
{
        QFileInfo file(s);
        int i  = recentBandsFileName.indexOf(file.fileName());
	if (i<0){
		

                recentBandsFileName<<file.fileName();
		recentBands<<s;
		/* View only the file name*/
                int row = model->stringList().size();
                model->insertRows(row,1);
                QModelIndex index = model->index(row);
                model->setData(index,file.fileName());
                listBands->setCurrentIndex(index);


		groupBandsTitle = titleBandBox + " - "+ file.fileName();
		groupBands->setTitle(groupBandsTitle);
                groupBox_11->setToolTip(file.absoluteFilePath());

	}
}
void EcoVal::updateRecent( QString s )
{
    QFileInfo file(s);
    int i  = recentFileName.indexOf(file.fileName());
    if (i<0){

            QFileInfo file(s);
            recentFileName<<file.fileName();
            recent<<s;
          //  qDebug()<<"ECOVAL updateRecent tariffe"<<i<<s<<file.fileName();
            /* View only the file name*/
            int row = modelTariffe->stringList().size();
            modelTariffe->insertRows(row,1);
            QModelIndex index = modelTariffe->index(row);
            modelTariffe->setData(index,file.fileName());
            listTariffe->setCurrentIndex(index);

        groupTariffeTitle = titleTariffeBox + " - " + file.fileName();
        groupTariffe->setTitle(groupTariffeTitle);
       listTariffe->setToolTip(file.absoluteFilePath());

}
}
void EcoVal::updateRecentTax(QString s)
{
    QFileInfo file(s);
    int i  = recentTaxFileName.indexOf(file.fileName());
    if (i<0){


            recentTaxFileName<<file.fileName();
            recentTax<<s;
            /* View only the file name*/
            int row = modelTax->stringList().size();
            modelTax->insertRows(row,1);
            QModelIndex index = modelTax->index(row);
            modelTax->setData(index,file.fileName());
            listTaxes->setCurrentIndex(index);

        groupTaxTitle = titleBox3 + " - " + file.fileName();
        groupTax->setTitle(groupTaxTitle);
        listTaxes->setToolTip(file.absoluteFilePath());

}
}
void EcoVal::deleteTaxFile()
{
    modelTax->removeRow(listTaxes->currentIndex().row());
    recentTaxFileName = modelTax->stringList();
}

void EcoVal::deleteOneriFile()
{

    modelTariffe->removeRow(listTariffe->currentIndex().row());
    recentFileName = modelTariffe->stringList();
}


void EcoVal::saveMinPrezziAs()
{
	QString fileName;
        fileName = QFileDialog::getSaveFileName(this, tr("Salva prezzi minimi energia"), recentSaveMinPrezzi, tr(" (*.scpm)"));
	if (!fileName.isEmpty()){
		fileName = MyMath::checkFormat(fileName,"scpm");
		fileMinPrezzi = fileName;
		
		updateMinPrezziLabel(fileMinPrezzi);
		saveMinPrezzi(fileMinPrezzi);
	}
}
void EcoVal::saveMinPrezzi(QString fileName)
{
        QStringList header;
	if (!fileName.isEmpty()  ) {
		
//                fileName = MyMath::checkFormat(fileName,"scpm");
		fileMinPrezzi = fileName;
		QFileInfo fileInfo(fileName);
                recentSaveMinPrezzi = fileInfo.absoluteDir().absolutePath();
		QFile file(fileMinPrezzi);
		if ( file.open(QFile::WriteOnly)){
			 
			QTextStream out(&file);
                        //Header info
                        header = infoPrezziMinimi.split("\n");
                        for(int i=0;i<header.size();i++) {
                          if (!header.at(i).isEmpty())
                                out<<"#"<<header.at(i)<<"\n";

                        }

			for(int i=0;i<12;i++)
				out<<minEnergyPrices[i]<<"\n";
		
		groupMinPrices->setTitle(groupMinPrezziTitle);
		}
		else
		{
		QMessageBox::warning(this,tr("Non riesco a scrivere nella cartella"),tr("Errore di scrittura nella cartella selezionata"),QMessageBox::Ok);
		}
}
}

void EcoVal::savePrezziAs()
{
	QString fileName;
        fileName = QFileDialog::getSaveFileName(this, tr("Salva prezzi energia"), recentSavePrezzi, tr(" (*.scp)"));
	if (!fileName.isEmpty()){

		fileName = MyMath::checkFormat(fileName,"scp");
		filePrezzi = fileName;
		
		updatePrezziLabel(filePrezzi);
		savePrezzi(filePrezzi);
	}
}

void EcoVal::deleteMinPrezziFile()
{
    modelSell->removeRow(listMinEnergyPrices->currentIndex().row());
    recentMinPricesFileName = modelSell->stringList();
}
void EcoVal::deletePrezziFile()
{
    modelInj->removeRow(listEnergyPrices->currentIndex().row());
    recentPricesFileName = modelInj->stringList();
}

void EcoVal::updatePrezziLabel(QString s)
{
	QFileInfo f(s);
	groupPrezziTitle = titleBox + " - " + f.fileName();
	groupPrezzi->setTitle(groupPrezziTitle);
        listEnergyPrices->setToolTip(f.absoluteFilePath());
        int i  = recentPricesFileName.indexOf(f.fileName());

	if (i<0){
		
                recentPricesFileName<<f.fileName();
		recentPrices<<s;
		/* View only the file name*/
		
               // modelInj->setStringList(recentPricesFileName);
                int row = modelInj->stringList().size();

                    modelInj->insertRows(row,1);



                QModelIndex index = modelInj->index(row);
                modelInj->setData(index,f.fileName());
                listEnergyPrices->setCurrentIndex(index);
                //listEnergyPrices->edit(index);
               // qDebug()<<"ECO add prezzi file"<<modelInj->stringList()<<s<<recentPrices<<s<<row;
	}
	
}
void EcoVal::updateMinPrezziLabel(QString s)
{
	QFileInfo f(s);
        groupMinPrezziTitle = titleBox2 + " - " + f.fileName();
	groupMinPrices->setTitle(groupMinPrezziTitle);
        listMinEnergyPrices->setToolTip(f.absoluteFilePath());
        int i  = recentMinPricesFileName.indexOf(s);
	if (i<0){
		
		
		recentMinPricesFileName<<f.fileName();
		recentMinPrices<<s;
		/* View only the file name*/
		
                int row = modelSell->stringList().size();

                modelSell->insertRows(row,1);



                QModelIndex index = modelSell->index(row);
                modelSell->setData(index,f.fileName());
                listMinEnergyPrices->setCurrentIndex(index);
		
                //qDebug()<<"ECO add prezzi file"<<modelSell->stringList()<<s<<recentMinPrices<<s;
	}
	
}
void EcoVal::saveMinP()
{
	if (fileMinPrezzi.isEmpty())
		saveMinPrezziAs();
	else
                saveMinPrezzi(fileMinPrezzi);
		
}
void EcoVal::saveP()
{
	if (filePrezzi.isEmpty())
		savePrezziAs();
	else
		savePrezzi(filePrezzi);
		
}
void EcoVal::savePrezzi(QString fileName)
{
        QStringList header;
	if (!fileName.isEmpty()  ) {
		
// 		fileName = MyMath::checkFormat(fileName,"scp");
		filePrezzi = fileName;
		QFileInfo fileInfo(fileName);

		QFile file(filePrezzi);
		if (file.open(QFile::WriteOnly)){
                recentSavePrezzi = fileInfo.absoluteDir().absolutePath();
                        header = infoPrezzi.split("\n");
			QTextStream out(&file);
                        //Header info
                        header = infoPrezzi.split("\n");
                        for(int i=0;i<header.size();i++) {
                            if (!header.at(i).isEmpty())
                                out<<"#"<<header.at(i)<<"\n";

                        }

			for(int i=0;i<12;i++){
                                for(int j=0;j<ecoParameters.numBands;j++)
                                out << mPrezziEnergia[i][j] << "\t";

                                out << "\n";
                                //qDebug()<<"ECO save Prezzi"<<mPrezziEnergia[i]<<fileName;
			}
		groupPrezzi->setTitle(groupPrezziTitle);
		
		}
		else
		{
			QMessageBox::warning(this,tr("Non riesco a scrivere nella cartella"),tr("Errore di scrittura nella cartella selezionata"),QMessageBox::Ok);
		}
}
}
void EcoVal::saveAs()
{
	QString fileName;
        fileName = QFileDialog::getSaveFileName(this, tr("Salva oneri accessori"), recentSaveTariffe, tr(" (*.scta)"));
	if (!fileName.isEmpty()){

		fileTariffe = fileName;
                ecoParameters.fileTariffe = fileTariffe;
                doNotLoad = true;
		updateRecent(fileName);
		saveTariffe(fileTariffe);
                doNotLoad = false;
	}
}
void EcoVal::saveTaxAs()
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this, tr("Salva imposte"), recentSaveTax, tr(" (*.tax)"));
    if (!fileName.isEmpty()){

            fileTax = fileName;
            ecoParameters.fileTax = fileTax;
            doNotLoad = true;
            updateRecentTax(fileName);
            saveTax(fileTax);
            doNotLoad = false;
    }
}

void EcoVal::saveTax()
{
    if (fileTax.isEmpty())
        saveTaxAs();
    else
        saveTax(fileTax);

}
void EcoVal::saveTax(QString  fileName)
{
    QStringList header;
    fileName = MyMath::checkFormat(fileName,"tax");
    QFile file(fileName);
    if (!fileName.isEmpty() && file.open(QFile::WriteOnly) ) {


            fileTax = fileName;
            QFileInfo fileInfo(fileName);
            recentSaveTax = fileInfo.absoluteDir().absolutePath();
            QTextStream out(&file);
            header = infoTax.split("\n");
           //qDebug()<<"ECO salvo file"<<fileName<<file.fileName();

            //Header info
            for(int i=0;i<header.size();i++) {
                    if (!header.at(i).isEmpty())
                    out<<"#"<<header.at(i)<<"\n";

            }
            out<<"-SolarCalc-"<<"\t"<<"Tasse"<<"\n";
            for(int j=0;j<TASSESIZE;j++){
                    out <<j<<"\t"<<ecoParameters.taxes[j]<<"\n";

        }

    groupTariffe->setTitle(groupTariffeTitle);

    }
    else
    {
    QMessageBox::warning(this,tr("Non riesco a scrivere nella cartella"),tr("Errore di scrittura nella cartella selezionata"),QMessageBox::Ok);
    }

}

void EcoVal::save()
{
	if (fileTariffe.isEmpty())
		saveAs();
	else
		saveTariffe(fileTariffe);
}
 
void EcoVal::saveTariffe(QString fileName)
{

	QStringList header;
        fileName = MyMath::checkFormat(fileName,"scta");
	QFile file(fileName);
	if (!fileName.isEmpty() && file.open(QFile::WriteOnly) ) {
		
		
		fileTariffe = fileName;
		QFileInfo fileInfo(fileName);

                recentSaveTariffe = fileInfo.absoluteDir().absolutePath();
		QTextStream out(&file);
                header = infoTariffe.split("\n");
                //qDebug()<<"ECO salvo file"<<fileName<<file.fileName();

                //Header info
                for(int i=0;i<header.size();i++) {
                        if (!header.at(i).isEmpty())
                        out<<"#"<<header.at(i)<<"\n";

                }


                for(int i=0;i<tIntervals.size();i++)
                    out<<"TI"<<"\t"<<
                            QString::number(ecoParameters.tIntervals.at(i).x())<<
                            "\t"<<
                            QString::number(ecoParameters.tIntervals.at(i).y())<<
                            "\n";
                out<<"-SolarCalc-"<<"\t"<<"Tariffe"<<"\n";


                for(int j=0;j<ecoParameters.tariffe.size();j++){
                    out <<j<<"\t";
                    for(int k=0; k<ecoParameters.tariffe[j].size();k++)
                        out <<ecoParameters.tariffe[j].at(k)<<"\t";
                    out<<"\n";
                 //qDebug()<<"ECO SAVE TARIFFE"<<ecoParameters.tariffe[j];
            }



	groupTariffe->setTitle(groupTariffeTitle);
	
	}
	else
	{
	QMessageBox::warning(this,tr("Non riesco a scrivere nella cartella"),tr("Errore di scrittura nella cartella selezionata"),QMessageBox::Ok);
	}
}

void EcoVal::loadBandFromList(QModelIndex index)
{
	if (index.isValid()) {	
		
		QString name = recentBands.at(index.row());
 //qDebug()<<"ECO loadBandFromList"<<index.row()<<fileBands<<recentBandsFileName<<name;
                if (loadBands(name)){
                  //  qDebug()<<"ECO loadBandFromList"<<index.row()<<fileBands<<recentBandsFileName<<name;
                //updateRecentBands(fileBands);
                setEcoBands();
                updateIntervalsView();
		updateTableBandsView();

                dVATonEn->setValue(ecoParameters.VATonTotEnergy);
                dIMPkWh->setValue(ecoParameters.IMPonEnergy);
                //updateEcoParView();
                groupBandsTitle = titleBandBox + " - "+ model->data(index,Qt::DisplayRole).toString();

                groupBands->setTitle(groupBandsTitle);
                listBands->setToolTip(name);

		

	
	}
            }
    }



void EcoVal::loadPricesFromList(QModelIndex index)
{
	if (index.isValid()) {	
                //qDebug()<<"ECO loadPricesFromList"<<index.row()<<recentPricesFileName;
		QString name = recentPrices.at(index.row());
		loadPrezzi(name);
		groupPrezziTitle = titleBox + " - " + recentPricesFileName.at(index.row());
		groupPrezzi->setTitle(groupPrezziTitle);
                listEnergyPrices->setToolTip(name);
		updatePrezziView();
	
	}
}
void EcoVal::loadMinPricesFromList(QModelIndex index)
{
	if (index.isValid()) {	
// 		qDebug()<<"ECO loadPricesFromList"<<index.row();
		QString name = recentMinPrices.at(index.row());
		loadMinPrezzi(name);
                groupMinPrezziTitle = titleBox2 + " - " + recentMinPricesFileName.at(index.row());
		groupMinPrices->setTitle(groupMinPrezziTitle);
		updateMinPrezziView();
                listMinEnergyPrices->setToolTip(name);
	
	}
}
void EcoVal::loadTaxFromList(QModelIndex index)
{
    if (index.isValid()) {

            QString name = recentTax.at(index.row());
            getTaxFromFile(name);
            groupTaxTitle = titleBox3 + " - " + recentTaxFileName.at(index.row());
            groupTax->setTitle(groupTaxTitle);
            updateTaxView();

}
}
void EcoVal::loadTariffeFromList(QModelIndex  index)
{
    if (index.isValid()) {	
// 		qDebug()<<"ECO loadPricesFromList"<<index.row();
            QString name = recent.at(index.row());
            QFileInfo s(name);
           getTariffeFromFile(name);
           updateTIntervalsView();
           updatePedaggiokWh();
           updatePedaggiokW();
           setLossFactor( );
           groupTariffeTitle = titleTariffeBox + " - " + recentFileName.at(index.row());
           groupTariffe->setTitle(groupTariffeTitle);
           doNotUpdate = true;
           /*Update View*/
           updateTariffeView();
           doNotUpdate = false;
           listTariffe->setToolTip(s.absoluteFilePath());
    
    }
    
    
        //updateRecent(fileTariffe);
        updateTariffeView();
}


//void EcoVal::processEnergyPrices()
///* This function applies a predictive model to future prices of injected energy */
///* Check the zeroicity of the input file */
///* Nov 2010: THIS FUNCTION HAS BEEN DISMISSED FOR NOW */
//{
//        int maxYear = ecoParameters.life;
//        double a1 = da1->value();
//	double b1 = db1->value();
//	double om = dO->value();
//	double mu = dMu->value();
//        double variance[(maxYear+1)*12],increments[(maxYear+1)*12];
//	double rn,sqr;
//	mPrezziEnergiaSpan.resize(0);
//for(int g=0;g<ecoParameters.numBands;g++)
//{
//        increments[0] = mPrezziEnergia.at(0).at(g);
//        for(int i=0;i<12;i++){
//            mPrezziEnergiaSpan.at(g).at(i) << mPrezziEnergia.at(i).at(g) ; /*first year copy */
//	    if (i>0){
//                increments[i] = log(mPrezziEnergia.at(i).at(g)) - log(mPrezziEnergia.at(i-1).at(g)); /* FOR GARCH MODEL */
//		variance[i]=0;
//		}
	    
//// 	    qDebug()<<"ECO processEnergyPrices first copy"<<mPrezziEnergiaSpan.at(i)<<i<<increments[i]<<maxYear;
	  
//	}
//        // Calcola la varianza del primo mese
//        QVector tempV;
//        for(int n = 0; n <12;n++)
//        {
//           tempV << mPrezziEnergia.at(n).at(g);
//        }
//        variance[11] = MyMath::var(tempV);


//        /* TO CHECK THE FOLLOWING FORMULA */
//	double D   = (1+dDiscountRate->value()/100)/(dEnergyInflationRate2->value()/100+1)-1;
//	D = - (dEnergyInflationRate2->value()/100 / (dEnergyInflationRate2->value()/100 + 1) );/*En inflates regardless of discount? */
//	double pwf = 0;
//  	for(int i=1;i<=maxYear;i++){
 
//	      pwf = 1/pow((1+D),i);
//              for(int j=0;j<12;j++){
//		if (radioGARCH->isChecked()){
			
//			variance[i*12+j]    =  om  + a1*pow(increments[i-1],2) + b1*variance[i*12 + j-1];
			
//			sqr = sqrt(variance[i*12+j]);
//			rn = MyMath::randn()*sqr;
//			increments[i*12+j]  = mu    -0.2*increments[i*12+j-1] +rn*sqr;

//                        mPrezziEnergiaSpan.at(g) << mPrezziEnergiaSpan.at(g).at((i-1)*12 + j) * exp(increments[i*12+j]);
////                        qDebug()<<"ECO processEnergyPrices "<<increments[i*12+j-1]<<increments[i*12+j]<<maxYear<<mu<<om<<rn<<variance[i*12+j]<<variance[i*12 + j-1]<<sqr<<i<<j<<mu<<mPrezziEnergiaSpan.at((i-1)*12 + j)<<mPrezziEnergiaSpan.at((i)*12 + j);
//		}
//		else
//		{
				
//                                mPrezziEnergiaSpan.at(g) << mPrezziEnergiaSpan.at(g).at( j) * pwf ;
//				#ifdef DEBUG
//                                qDebug()
//                                        <<"ECO processEnergyPrices
//                                        SIMPLAE INFLATION"<<mPrezziEnergiaSpan.at(i*12+j)<<pwf;
//				#endif
//		}
//                 }
//  	}
// }
//updatePrezziPlot();
//// free(e);
//}
double EcoVal::inflateBandPrice(double d,int year)
{


    double D = - (ecoParameters.fasceInflazione/100 / (ecoParameters.fasceInflazione/100 + 1) );
    double pwf = 1/pow((1+D),year);
    return d * pwf;
}



void EcoVal::drawBandsPrices(int years)
{
    /*Prepare band to draw */
    QPolygonF a;
    double v;
    int index = comboIntervals->currentIndex();
    index = index < 0 ? 0 : index;
    for(int i=0;i<12;i++){
        a.resize(0);
        v = bands[i].at(2+index).toDouble();
            if (v > 0.000000000000002){
                for(int j=0;j<years;j++){
                    a << QPointF(j+1,inflateBandPrice(v,j));

                }



            bandPricesPlots[i]->setData(a);
        }
            else
            bandPricesPlots[i]->setRawData(0,0,0);
    }
    qwtBands->replot();
}

void EcoVal::processMinEnergyPrices()
/* This function applies a predictive model to future prices of injected energy */
{
	int maxYear = dPeriodo->value();
	double a1 = dminPricesA1->value();
	double b1 = dminPricesB1->value();
	double om = dminPricesO1->value();
	double mu = dminPricesMu->value();
        double variance[(maxYear+1)*12],increments[(maxYear+1)*12];
	
	
        increments[0] = minEnergyPrices.at(0);
	minEnergyPrices.remove(12,minEnergyPrices.size()-12);
        for(int i=0;i<12;i++){
        
	    if (i>0){
	    	increments[i] = log(minEnergyPrices.at(i)) - log(minEnergyPrices.at(i-1)); /* FOR GARCH MODEL */
		variance[i]=0;
		}
	    variance[11] = MyMath::var(minEnergyPrices);
//   	    qDebug()<<"ECO processMinEnergyPrices first copy"<<minEnergyPrices.at(i)<<maxYear;
	  
	}

	
	

	double D   = (1+dDiscountRate->value()/100)/(dEnergyInflationRateSell->value()/100+1)-1;
	D = - (dEnergyInflationRateSell->value()/100 / (dEnergyInflationRateSell->value()/100 + 1) );/*En inflates regardless of discount? */
	double pwf = 0;
  	for(int i=1;i<=maxYear;i++){

	      pwf = 1/pow((1+D),i);
              for(int j=0;j<12;j++){
		if (radioGARCH_2->isChecked()){
			variance[i*12+j]    =  om  + a1*pow(increments[i-1],2) + b1*variance[i*12 + j-1];
			increments[i*12+j]  = mu   + -0.2*increments[i*12+j-1]  + MyMath::randn()*sqrt(variance[i*12+j]);
			
			

 			minEnergyPrices << minEnergyPrices.at((i-1)*12 + j) * exp(increments[i*12+j]);
//                          qDebug()<<"ECO processEnergyPrices minimum"<<minEnergyPrices.at(i*12+j)<<maxYear<<i<<j;
		}
		else
		{
				
				minEnergyPrices << minEnergyPrices.at(    j) * pwf ;
// 				qDebug()<<"ECO processEnergyPrices minimum SIMPLAE INFLATION"<<minEnergyPrices.at(i*12+j)<<pwf;
		}
                 }
  	}
updateMinPrezziPlot();
// free(e);
}
//void EcoVal::reProcessEnergyPrices(bool i)
//{
//	if (i==true)
//	{
//		da1->setEnabled(true);
//		db1->setEnabled(true);
//		dMu->setEnabled(true);
//		dO->setEnabled(true);
//		dMu->setEnabled(true);

//		dEnergyInflationRate2->setEnabled(false);
//		processEnergyPrices();
//	}
//	else
//	{
//		da1->setEnabled(false);
//		db1->setEnabled(false);
//		dMu->setEnabled(false);
//		dO->setEnabled(false);
//		dMu->setEnabled(false);
	
//		dEnergyInflationRate2->setEnabled(true);
//	}
	
//}
void EcoVal::reProcessMinEnergyPrices(bool i)
{
	if (i==true)
	{
		dminPricesA1->setEnabled(true);
		dminPricesB1->setEnabled(true);
		dminPricesMu->setEnabled(true);
		dminPricesO1->setEnabled(true);
		

		dEnergyInflationRateSell->setEnabled(false);
		processMinEnergyPrices();
	}
	else
	{
		dminPricesA1->setEnabled(false);
		dminPricesB1->setEnabled(false);
		dminPricesMu->setEnabled(false);
		dminPricesO1->setEnabled(false);
		
	
		dEnergyInflationRateSell->setEnabled(true);
	}
	
}

void EcoVal::toggleCoeff(int i)
{
	if (i==Vendita)
	{
		groupMinPrices->setEnabled(true);
                groupCoeffVendita->setEnabled(true);
//                groupTras->setEnabled(false);
//                groupDisp->setEnabled(false);
//                groupDist->setEnabled(false);
//                groupGenerali->setEnabled(false);
	}
	else{
	
                groupCoeffVendita->setEnabled(false);
		groupMinPrices->setEnabled(false);
                groupTras->setEnabled(true);
                groupDisp->setEnabled(true);
                groupDist->setEnabled(true);
                groupGenerali->setEnabled(true);
	}
}
int EcoVal::getRegime()
{
	return comboRegime->currentIndex();
}
double EcoVal::getYearlyAssic(int i,bool inflated)
{
        assicurazione = installedPower*ecoParameters.assicurazione;

        if (inflated)
            return MyMath::inflate(i,ecoParameters.inflRate/100,assicurazione);
        else
            return assicurazione;
	
}

double EcoVal::getYearlyAssicNPV(int year,int mode)
{
    double rw = 0;

    /* CLASSIC */
    if (mode == 0)
         rw = (1+ecoParameters.discountRate/100) / (1 + ecoParameters.inflRate/100) -1;

    /*WACC */
    if (mode == 1){
        double P = (ecoParameters.loan/ecoParameters.initialCost);
        rw = P*ecoParameters.loanInterestRate/100 +
             (1-P)*ecoParameters.discountRate/100;
        //qDebug()<<"ECOVAL NPVFACTOR"<<rw<<P<<ecoParameters.loan;
         }
        if (year<= ecoParameters.assicurazioneAnni)
		return assicurazione/(pow(1+rw,year));
	else
		return 0;
}
double EcoVal::getYearlyCost(int i,bool inflated)
/* Return the total cost (maintenance, taxes, and so on) */
/* i = current year */
{
    //qDebug()<<"ECO Cost"<<ecoParameters.maintenanceCost<<ecoParameters.affitti <<ecoParameters.otherCost;
    if (inflated)
    return MyMath::inflate(i,ecoParameters.inflRate/100,ecoParameters.maintenanceCost  + ecoParameters.affitti + ecoParameters.otherCost);
    else
        return ecoParameters.maintenanceCost  + ecoParameters.affitti + ecoParameters.otherCost;
}

double EcoVal::getNPVFactor(double C,int year,int mode)
/* Return a single factor of the NPV summation. C is the cash flow*/
{
        double rw,P;
        P = rw = 0;

        /* CLASSIC */
        if (mode == 0)
             rw = (1+ecoParameters.discountRate/100) / (1 + ecoParameters.inflRate/100) -1;

        /*WACC */
        if (mode == 1){
          P = ecoParameters.initialCost>0 ?
              (ecoParameters.loan/ecoParameters.initialCost) :0;

            rw = P*ecoParameters.loanInterestRate/100 +
                 (1-P)*ecoParameters.discountRate/100;

             }


	double den = pow((1+rw),year);

	if (year<=0) 
		return 1;
	else
		return C/den;
}


double EcoVal::getInitialCost()
{
        return ecoParameters.initialCost;
}
double EcoVal::getYearlyLoan( int year)
{
        if (year<=ecoParameters.loanYears)
	return loan;
	else
	return 0;
}
double EcoVal::getYearlyLoanNPV(int year)
{
        if (year<=ecoParameters.loanYears)
        return loan* (1/pow((ecoParameters.discountRate/100+1),year));
	else
	return 0;
}
double EcoVal::finWithVat()
{
    double fin     = ecoParameters.loan*
                     (1+ (1-ecoParameters.benefitVATCost/100) *
                      (ecoParameters.vat/100 ));
    return fin;
}

void EcoVal::computeLoan()
{
    double epsilon = 0.0000000002;
        int    nfin    = ecoParameters.loanYears;
        double fin     = finWithVat();

        double rate    = ecoParameters.loanInterestRate/100;
        if (nfin>0 && fin>epsilon && rate>epsilon)
            loan =  fin * rate /(1 - pow(1+rate,-nfin));
	else
	loan = 0;
	
}
double ::EcoVal::getYearlyInterestNPV(int year, int mode)
{
    /* mode = 0 classic */
    /* mode = 1 APV with interest rate */
        double D,o ;
        if (mode==0){
            D = (1+dDiscountRate->value()/100)/(1+dLoanInterestRate->value()/100) - 1;

	return  getYearlyInterest(year)*1/(pow(1+D,year));
    }
        if (mode ==1)
        {
            D = ecoParameters.loanInterestRate/100;
              o = getYearlyInterest(year)*
                    (ecoParameters.benefitTotalInterest/100) *1/(pow(1+D,year));
              //qDebug()<<"InteresNPV"<<o;
              return o;
        }
}
double EcoVal::getYearlyInterest(int year)
{
        int    nfin    = ecoParameters.loanYears;
        double fin     = finWithVat();
        double rate    = ecoParameters.loanInterestRate/100;
        int    n    = MyMath::min(ecoParameters.life,nfin);
        if (n>0 && fin>0 && year>0 && year<=n)
                 return fin*rate *(pow((1+rate),n) -
                        pow(1+rate,year-1))/(pow(1+rate,n)-1);

		else
		return 0;
}
double EcoVal::getTaxReduction()
{
        return (dTaxReduction->value()/100)*dCostoIniziale->value();
}

double EcoVal::getDepreciation(int year)
{
        //ammPeriodo = ecoParameters.ammortamento > 0.000000002 ? floor(100/ecoParameters.ammortamento) : 0;
    double toDeprec = ecoParameters.initialCost*(1+ecoParameters.vat/100 * (1-ecoParameters.benefitVATCost/100));
        int e = (int)(MyMath::min(ecoParameters.life,ammPeriodo));
        if (e!=0){
            if (year<=ecoParameters.ammortamentoAnni){
                 //qDebug()<<"ECO VAL AMM A"<<year<<ceil(ecoParameters.ammortamentoAnni);
               return ecoParameters.ammortamento *
                      toDeprec /100;
           }
            else
            {
                if (year==ceil(ecoParameters.ammortamentoAnni)){
                    //qDebug()<<"ECO VAL AMM B"<<year<<ceil(ecoParameters.ammortamentoAnni);
                   return toDeprec*(1 -
                           ecoParameters.ammortamento*(year-1)/100);}
            }


        } else{
                    //qDebug()<<"ECO ammperiodo 0"<<ammPeriodo;
                    return 0;
                }
	return 0;

}
double EcoVal::getDepreciationNPV(int year)

{
        double toDeprec = ecoParameters.initialCost*(1+ecoParameters.vat/100);
        int e = (int)(MyMath::min(ecoParameters.life,ammPeriodo));
	if (year<=e)
        return (ecoParameters.ammortamento/100) * toDeprec/pow(1+ecoParameters.discountRate/100,year);
	else
	return 0;
}
 double EcoVal::getYearlyTaxReductionOnInterest(int year)
{

         return (ecoParameters.benefitTotalInterest *getYearlyInterest(year)/100);
}

double EcoVal::getYearlyTaxReductionOnInterestNPV(int year)
{

	double t = pow((1+dLoanInterestRate->value()/100 ),dFinAnni->value());
	double d = dDiscountRate->value()/100;

	double m    = dLoanInterestRate->value()/100;
	double Ds   = (1+d)/(1+m) -1;
	double factor = (t * 1/pow(1+d,year) - ((1/pow(1+Ds,year)) * 1/(1+m)))/( t -1);
	if ((int)t==1)
	return 0;
	else
	return (dTaxReductionInterest->value() * m * dFinanziamento->value() *factor);


}

// void EcoVal::createActions()
// {
// 	a_print       =  new QAction(tr("&Stampa"),this);
// 	a_print->setShortcut(tr("Ctrl+P"));
// 	a_export      = new QAction(tr("&SVG"),this);
// 
// 	a_export->setShortcut(tr("Ctrl+S+V"));
// 
// // 	a_proprieta   = new QAction(tr("Impostazioni"),this);
// 
// // 	a_create_grid = new QAction(tr("Griglia"),this);
// 
// 	a_exportPNG   = new QAction(tr("PNG"),this);
// 	
// 	a_exportPDF = new QAction(tr("PDF"),this);
// 	a_exportPDF->setIcon(QIcon(":/images/pdf.jpeg"));
// 
// 
// 	connect(a_print,SIGNAL(triggered()),this,SLOT(printOut()));
// 	connect(a_export,SIGNAL(triggered()),this,SLOT(exportSVG()));
// 	 
// // 	connect(a_create_grid,SIGNAL(triggered()),this,SLOT(gridset()));
// 	connect(a_exportPNG,SIGNAL(triggered()),this,SLOT(exportPNG()));
// 	connect(a_exportPDF,SIGNAL(triggered()),this,SLOT(exportPDF()));
// 	 
// }
// void EcoVal::exportSVG()
// {
// }
//  
//  void EcoVal::printOut()
// {
// 	 QPrinter printer(QPrinter::HighResolution);
// 	#ifdef Q_WS_X11
// 	 printer.setOutputFileName(tr("diagrammasolare.pdf"));
// 	#endif
// 	 printer.setCreator("Solar Calc");
//          printer.setOrientation(QPrinter::Landscape);
// 	 
// 	 QPrintDialog dialog(&printer);
//    	 if ( dialog.exec() )
//     	{	
// 		QwtPlotPrintFilter filter;
// 	//          if ( printer.colorMode() == QPrinter::GrayScale )
//         
//             int options = QwtPlotPrintFilter::PrintAll;
//             options &= ~QwtPlotPrintFilter::PrintBackground;
//             options |= QwtPlotPrintFilter::PrintFrameWithScales;
//             filter.setOptions(options);
//         
// 	if (cursorPos.y()<=qwtVan->geometry().y()+qwtVan->geometry().height())
//         	qwtVan->print(printer,filter );
// 	if (cursorPos.y()>qwtVan->geometry().y()+qwtVan->geometry().height())
// 		qwtPlot->print(printer,filter );
// 	
// 	}
// }
// void EcoVal::exportPDF()
// {
// 	 QString fileName;
// 	 fileName = QFileDialog::getSaveFileName(this, tr("Nome file da esportare"),   recentExportPath,"Acrobat ( *pdf)");
// 	QFileInfo fileInfo(fileName);
//         recentExportPath = fileInfo.absoluteDir().absolutePath();
// 	if ( !fileName.isEmpty() ) {
// 	   fileName = MyMath::checkFormat(fileName,"pdf");
// 	 QPrinter printer(QPrinter::HighResolution);
// 	 printer.setOutputFormat(QPrinter::PdfFormat);
// 	 printer.setOutputFileName(fileName);
// 	 printer.setCreator("Solar Calc");
//          printer.setOrientation(QPrinter::Landscape);
// 	 
// 	 
//      
//        
// 	    QwtPlotPrintFilter filter;
// //          if ( printer.colorMode() == QPrinter::GrayScale )
//          
//             int options = QwtPlotPrintFilter::PrintAll;
//             options &= ~QwtPlotPrintFilter::PrintBackground;
//             options |= QwtPlotPrintFilter::PrintFrameWithScales;
//             filter.setOptions(options);
//         
// 
// // 	qwtVan->print(printer,filter);
// // 	printer.newPage();
// // 	qwtPlot->print(printer,filter);
// 
// QPainter painter;
// painter.begin(&printer);
// qwtVan->print(&painter,printer.pageRect(),filter);
// printer.newPage();
// qwtPlot->print(&painter,printer.pageRect(),filter);
// painter.end();
// 
//       }
// }	
// void EcoVal::popUpMenu(const QPoint &pos)
// { 
// 	 
//  	QMenu menu;
// 	QMenu exMenu(tr("&Esporta"),&menu);
// 	
// 	
// 	exMenu.addAction(a_export);
// 	exMenu.addAction(a_exportPNG);
// 	exMenu.addAction(a_exportPDF);
// 	
// 		
// // 	menu.addAction(a_undo_combine);
// 	menu.addAction(a_print);
// 	menu.addMenu(&exMenu);
// 		
// 	
// // 	menu.addAction(a_create_grid);
// 	cursorPos = this->mapFromGlobal(QCursor::pos());
// 	#ifdef Q_WS_X11
// 	menu.popup(pos);	
// 	#endif
// 	menu.exec(QCursor::pos());
// 	qDebug()<<"qwtPlot Poistion ="<<qwtVan->geometry().y()<<qwtVan->geometry().y()+qwtVan->geometry().height()
// 				      <<qwtPlot->geometry().y()<<qwtPlot->geometry().height()+qwtPlot->geometry().y()
// 				      <<QCursor::pos()<<this->mapFromGlobal(QCursor::pos());
// }
// void EcoVal::exportPNG()
// {	QString fileName;
//  
//         fileName = QFileDialog::getSaveFileName(this, tr("Nome file da esportare"),  recentExportPath,"Graphic files (*.png  )");
// 	QFileInfo fileInfo(fileName);
//         recentExportPath = fileInfo.absoluteDir().absolutePath();
// 
//     if ( !fileName.isEmpty() )
//     {
// 	 fileName = MyMath::checkFormat(fileName,"png");
// 	QwtPlotPrintFilter filter;
//     	int options = QwtPlotPrintFilter::PrintAll;
//                options  = ~QwtPlotPrintFilter::PrintBackground;
//                options |= QwtPlotPrintFilter::PrintFrameWithScales;
//  	 
// 	filter.setOptions(options);
// 	//QImage pixmap(800,600,QImage::Format_RGB32);
// // 	QPixmap pixmap= QPixmap::grabWidget(p);
// 	QPixmap pixmap(1024,800);
// 	pixmap.fill(Qt::white);
//       	
// 	if (cursorPos.y()<=qwtVan->geometry().y()+qwtVan->geometry().height())
//         	qwtVan->print(pixmap,filter );
// 	if (cursorPos.y()>qwtVan->geometry().y()+qwtVan->geometry().height())
// 		qwtPlot->print(pixmap,filter );
// 
// 	 if ( pixmap.save(fileName, "png" ))
// 		qDebug()<<"Ok";
//   	 else
// 		qDebug()<<"Error";
// 	 
//     
// }
// }
double EcoVal::getDepreciationYears()
{
    return ecoParameters.ammortamentoAnni;
}

ecopara EcoVal::getEcoParameters()
{

        return ecoParameters;
}
void EcoVal::setLife()
{
    ecoParameters.life			= dPeriodo->value();
}

void EcoVal::setLife(int years)
{
    ecoParameters.life			= years;
    computeLoan();
    /* Nov 2010 dismissed for now
    / processEnergyPrices();
    */
    processMinEnergyPrices();
    drawBandsPrices(years);
}

void EcoVal::setEcoInvestment()
{
    if (!doNotUpdate){
            ecoParameters.bonusPerkWp	    = dIncentiviPerkWp->value();
            ecoParameters.assicurazione     = dAssicurazione->value();
            ecoParameters.assicurazioneAnni = dAssicurazioneAnni->value();
            ecoParameters.ammortamento      = dAmmortamento->value();
            ammPeriodo = dAmmortamento->value() > 0.0000000002 ? (100.0/dAmmortamento->value()) : 0;
            ecoParameters.ammortamentoAnni  = ammPeriodo;
            ecoParameters.regime            = comboRegime->currentIndex();
            if (ecoParameters.regime == Vendita)
                checkCredit->setEnabled(false);
            else
                checkCredit->setEnabled(true);
            ecoParameters.fileBands         = fileBands;
            ecoParameters.bonuses	    = dIncentivi->value();
            ecoParameters.bonusesYears      = dBonusesYears->value();
            ecoParameters.affitti           = dAffitti->value();
            ecoParameters.maintenanceCost       = dManutenzioneAnno->value();
            ecoParameters.maintenanceS		= dManutenzioneS->value();
            ecoParameters.maintenanceSFreq	= dManutenzioneSFreq->value();

            ecoParameters.taxesCost		= 0;
            ecoParameters.otherCost		= dAltro->value();
            ecoParameters.benefitInitialCost	= dReductionInitialCost->value();
            ecoParameters.benefitTaxes          = dTaxReduction->value();
            ecoParameters.benefitTotalInterest  = dTaxReductionInterest->value();


            ecoParameters.benefitVATCost	= dTaxReductionVAT->value();
            ecoParameters.initialCost		= dCostoIniziale->value();

            ecoParameters.loan			= dFinanziamento->value();
            ecoParameters.loanYears		= dFinAnni->value();
            ecoParameters.loanInterestRate	= dLoanInterestRate->value();
            ecoParameters.inflRate		= dTassoInflazione->value();
        // 	o.inflEnergyRate	= dEnergyInflationRate2->value();
            ecoParameters.discountRate		= dDiscountRate->value();

            ecoParameters.vat                   = dVAT->value();
            if (!doNotEmit)
                emit isDirty();
        }






}

void EcoVal::setEco()
{
    if (!doNotUpdate){
            for(int i=0;i<12;i++)
            {

                    ecoParameters.prezziMinEnergia[i] = minEnergyPrices.at(i);
                    for(int j=0;j<numBands;j++)
                    {
                        ecoParameters.prezziEnergia[i][j]    = mPrezziEnergia.at(i).at(j);

                    }

            }
            ecoParameters.fileTariffe              = fileTariffe;
            ecoParameters.fileBands                = fileBands;
            ecoParameters.filePrezziEnergia        = filePrezzi;
            ecoParameters.filePrezziMinimi         = fileMinPrezzi;
            ecoParameters.prezziEnergiaModel       = radioSimpleInflation->isChecked();
            ecoParameters.prezziEnergiaInflazione = dEnergyInflationRate2->value();
            ecoParameters.fasceInflazione         = dBandsInflationRate->value();
            ecoParameters.prezziMinEnergiaInflazione = dEnergyInflationRateSell->value();
            ecoParameters.prezziEnergiaGARCH.resize(0);
            ecoParameters.prezziEnergiaGARCH<< 0 << 0 << 0 << 0;
//             ecoParameters.prezziEnergiaGARCH<< da1->value() << db1->value() << dO->value() << dMu->value();
             ecoParameters.prezziMinEnergiaModel = radioSimpleInflation_2->isChecked();
             ecoParameters.minPrezziEnergiaGARCH.resize(0);
             ecoParameters.minPrezziEnergiaGARCH<< dminPricesA1->value() << dminPricesB1->value() << dminPricesO1->value() << dminPricesMu->value();

            ecoParameters.inflEnergyRate          = dBandsInflationRate->value();
             if (ecoParameters.regime == Vendita)
                 ecoParameters.credit = false;
             else
                ecoParameters.credit = checkCredit->isChecked();

             if (ecoParameters.life==0)
                 drawBandsPrices(30);
             else
                drawBandsPrices(ecoParameters.life);
             if (!doNotEmit)
                emit isDirty();
}

}
void EcoVal::updateTaxView()
{
    doNotUpdate = true;
    dTIvaBonus->setValue(ecoParameters.taxes[0]);
    dTIvaCS->setValue(ecoParameters.taxes[1]);
    dTIvaEn->setValue(ecoParameters.taxes[2]);

    dTIrpefBonus->setValue(ecoParameters.taxes[3]);
    dTIrpefCS->setValue(ecoParameters.taxes[4]);
    dTIrpefEn->setValue(ecoParameters.taxes[5]);

    dTIrapBonus->setValue(ecoParameters.taxes[6]);
    dTIrapCS->setValue(ecoParameters.taxes[7]);
    dTIrapEn->setValue(ecoParameters.taxes[8]);

    dTIresBonus->setValue(ecoParameters.taxes[9]) ;
    dTIresCS->setValue(ecoParameters.taxes[10]) ;
    dTIresEn->setValue(ecoParameters.taxes[11]);

    dTAltroBonus->setValue(ecoParameters.taxes[12]);
    dTAltroCS->setValue(ecoParameters.taxes[13]);
    dTAltroEn->setValue(ecoParameters.taxes[14]);
    doNotUpdate = false;
}
double EcoVal::getTariffeValueFromId(int index)
{
    switch (index){
    case 0:
        return dTrasmissionekWh->value();
        break;
    case 1:
         return dTrasmissionekW->value();
        break;
    case 2:
         return dTrasmissioneAnno->value();
        break;
    case 3:
        return dDistribuzionekWh->value();
        break;
    case 4:
         return dDistribuzionekW->value();
        break;
    case 5:
        return  dDistribuzioneAnno->value();
        break;
    case 6:
         return dMisurakWh->value();
        break;
    case 7:
         return dMisurakW->value();
        break;
    case 8:
         return dAUCkWh->value();
        break;
    case 9:
         return dAUCkW->value();
        break;
    case 10:
        return dAUCanno->value();
        break;
    case 11:
        return dPerditaTrasmissione->value();
        break;
    case 12:
      //  return dPerditaDistribuzione->value();
         return dCostiAmm->value();
        break;
    case 13:
        return dCTRkWh->value();
        break;
    case 14:
        return dFattCTR->value();
        break;
    case 15:
        return dAltriCostiMensili->value();
        break;
    case 16:
        return dDISP->value();
        break;
    case 17:
        return dDISPkWh->value();
        break;
    case 18:
        return dDISPkW->value();
        break;
    case 19:
        return dLoss->value();
        break;
    case 20:
        return dMisuraAnno->value();
        break;
    default:
        qDebug()<<"ECOVAL WARNING IN getTariffeValueFromId"<<index;
        return 0;

    }
}
void EcoVal::updateImmissioneView()
{

    doNotUpdate = true;
    int index = comboImmissione->currentIndex();
    index     = index <0 ? 0 : index;

    if (!ecoParameters.immissione.isEmpty())
        dYearlyMinPrice->setValue(ecoParameters.immissione.at(index));
    else
        dYearlyMinPrice->setValue(0);

    doNotUpdate = false;
}

void EcoVal::updateTariffeView()
{
     doNotUpdate = true;
     int index = comboTariffeIntervals->currentIndex();
     index     = index <0 ? 0 : index;
    dTrasmissionekWh->setValue(ecoParameters.tariffe[0].at(index));
    dTrasmissionekW->setValue(ecoParameters.tariffe[1].at(index));
    dTrasmissioneAnno->setValue(ecoParameters.tariffe[2].at(index));
    dDistribuzionekWh->setValue(ecoParameters.tariffe[3].at(index));
    dDistribuzionekW->setValue(ecoParameters.tariffe[4].at(index));
    dDistribuzioneAnno->setValue(ecoParameters.tariffe[5].at(index));
    dMisurakWh->setValue( ecoParameters.tariffe[6].at(index));
    dMisurakW->setValue( ecoParameters.tariffe[7].at(index));
    dMisuraAnno->setValue(ecoParameters.tariffe[20].at(index));
    dMCTkWh->setValue(ecoParameters.tariffe[21].at(index));
    dAUCkWh->setValue(ecoParameters.tariffe[8].at(index));
    dAUCkW->setValue(ecoParameters.tariffe[9].at(index));
    dAUCanno->setValue(ecoParameters.tariffe[10].at(index));
    dPerditaTrasmissione->setValue( ecoParameters.tariffe[11].at(index));
 //   dPerditaDistribuzione->setValue(ecoParameters.tariffe[12].at(index));

    dCostiAmm->setValue(ecoParameters.tariffe[12].at(index));
    dLimitCostiAmm->setValue(ecoParameters.ammCostLimit);
    dCTRkWh->setValue(ecoParameters.tariffe[13].at(index));
    dFattCTR->setValue(ecoParameters.tariffe[14].at(index));
    dAltriCostiMensili->setValue(ecoParameters.tariffe[15].at(index));
    dDISP->setValue(ecoParameters.tariffe[16].at(index));
    dDISPkWh->setValue(ecoParameters.tariffe[17].at(index));
    dDISPkW->setValue(ecoParameters.tariffe[18].at(index));
    dLoss->setValue(ecoParameters.tariffe[19].at(index));

    dLimitCostiAmm->setValue(ecoParameters.tariffe[22].at(index));
    doNotUpdate = false;
}

void EcoVal::updateEcoParView()
{
    doNotUpdate = true;
        dIncentiviPerkWp->setValue(ecoParameters.bonusPerkWp);
        dAssicurazione->setValue(ecoParameters.assicurazione);
        dAssicurazioneAnni->setValue(ecoParameters.assicurazioneAnni);
        dAmmortamento->setValue(ecoParameters.ammortamento);
        ammPeriodo = (ecoParameters.ammortamentoAnni);
        

        comboRegime->setCurrentIndex(ecoParameters.regime);
        if (ecoParameters.regime == SSPIT)
            checkCredit->setEnabled(true);
      //  
        dIncentivi->setValue(ecoParameters.bonuses);
        dBonusesYears->setValue(ecoParameters.bonusesYears);
    // 	qDebug()<<"ECO VAL ecopara"<<ecoParameters.bands;
    
        updateTariffeView();
        doNotUpdate = true;

      
    radioSimpleInflation->setChecked(ecoParameters.prezziEnergiaModel);
    dEnergyInflationRate2->setValue(ecoParameters.prezziEnergiaInflazione);
    dEnergyInflationRateSell->setValue(ecoParameters.prezziMinEnergiaInflazione);
    dBandsInflationRate->setValue(ecoParameters.fasceInflazione);
//    da1->setValue(ecoParameters.prezziEnergiaGARCH.at(0));
//    db1->setValue(ecoParameters.prezziEnergiaGARCH.at(1));
//    dO->setValue(ecoParameters.prezziEnergiaGARCH.at(2));
//    dMu->setValue(ecoParameters.prezziEnergiaGARCH.at(3));
    radioSimpleInflation_2->setChecked(ecoParameters.prezziMinEnergiaModel);
    dminPricesA1->setValue(ecoParameters.minPrezziEnergiaGARCH.at(0));
    dminPricesB1->setValue(ecoParameters.minPrezziEnergiaGARCH.at(1));
    dminPricesO1->setValue(ecoParameters.minPrezziEnergiaGARCH.at(2));
    dminPricesMu->setValue(ecoParameters.minPrezziEnergiaGARCH.at(3));
    dManutenzioneAnno->setValue(ecoParameters.maintenanceCost);
    dManutenzioneS->setValue(ecoParameters.maintenanceS);
    dManutenzioneSFreq->setValue(ecoParameters.maintenanceSFreq);
    dAffitti->setValue(ecoParameters.affitti);
    // 	dTasse->setValue(ecoParameters.taxesCost);
    dAltro->setValue(ecoParameters.otherCost);
    dReductionInitialCost->setValue(ecoParameters.benefitInitialCost);
    dTaxReduction->setValue(ecoParameters.benefitTaxes);
    dTaxReductionInterest->setValue(ecoParameters.benefitTotalInterest);
    dTaxReductionVAT->setValue(ecoParameters.benefitVATCost);
    dCostoIniziale->setValue(ecoParameters.initialCost);

    dFinanziamento->setValue(ecoParameters.loan);
    dFinAnni->setValue(ecoParameters.loanYears);
    dLoanInterestRate->setValue(ecoParameters.loanInterestRate);
    dTassoInflazione->setValue(ecoParameters.inflRate);
    // 	dEnergyInflationRate->setValue(ecoParameters.inflEnergyRate);
    dDiscountRate->setValue(ecoParameters.discountRate);
    dPeriodo->setValue(ecoParameters.life);
    dVAT->setValue(ecoParameters.vat);


    dPotenzakW->setValue(ecoParameters.power);
    checkCredit->setChecked(ecoParameters.credit);




    dVATonEn->setValue(ecoParameters.VATonTotEnergy);
    dIMPkWh->setValue(ecoParameters.IMPonEnergy);

   // dIVATariffe->setValue(ecoParameters.tariffe[21]);


    // 	if (!filePrezzi.isEmpty()){
    // 		loadPrezzi(filePrezzi);
        updatePrezziView();
     //   updatePrezziLabel(filePrezzi);
    // 	}
    groupPrezziTitle = titleBox + " - " + QFileInfo(filePrezzi).fileName();
    groupPrezzi->setTitle(groupPrezziTitle);

    // 	if (!fileMinPrezzi.isEmpty()){
    // 		loadMinPrezzi(fileMinPrezzi);
         updateMinPrezziView();
     //   updateMinPrezziLabel(fileMinPrezzi);
    // 	}
    groupMinPrezziTitle = titleBox2 + " - " + QFileInfo(fileMinPrezzi).fileName();
    groupMinPrices->setTitle(groupMinPrezziTitle);
      //  if (!fileBands.isEmpty()){
    //                 loadBands(fileBands);
    //    updateRecentBands(fileBands);
   // }
    groupBandsTitle = titleBandBox + " - "+ QFileInfo(fileBands).fileName();
    groupBands->setTitle(groupBandsTitle);
     //   updateView(0);
    // 	}
  //  if (!fileTariffe.isEmpty()){
    // 		getTariffeFromFile(fileTariffe);
    //    updateRecent(fileTariffe);//aggiorna il nome del file
    //}
    groupTariffeTitle = titleTariffeBox + " - " + QFileInfo(fileTariffe).fileName();
    groupTariffe->setTitle(groupTariffeTitle);

    groupTaxTitle = titleBox3 + " - " + QFileInfo(fileTax).fileName();
    groupTax->setTitle(groupTaxTitle);
  doNotUpdate = false;
}

void EcoVal::setEcoParameters(const ecopara o)
/* FROM OUTSIDE */
/* Set the model and update the view*/
{
    doNotUpdate = true;

        ecoParameters = o;

        ammPeriodo = ecoParameters.ammortamentoAnni;


        // BANDS //////////////////////////////////////////
	bands.clear();
	if (!ecoParameters.bands.isEmpty()){
        for(int i=0;i<12;i++)
                 bands.append(ecoParameters.bands[i]);
    	}
    	else
                bands = bandsDefault;

        bandsPrevious = bands;
        if(!ecoParameters.intervals.isEmpty())
                intervals = ecoParameters.intervals;
        else
                intervals = QPolygonF();
        if(!ecoParameters.tIntervals.isEmpty())
                tIntervals = ecoParameters.tIntervals;
        else
                tIntervals = QPolygonF();
        if(!ecoParameters.pIntervals.isEmpty())
        {
            if (ecoParameters.pIntervals.size()!=ecoParameters.immissione.size()){
                    QMessageBox::warning(this,tr("Intervalli di produzione"),
                                         tr("<p>Il numero di intervalli di immissione &egrave; diverso dal numero di prezzi. Controlla il file .sc</p>"));
                    pIntervals =               QPolygonF();
                    ecoParameters.immissione.fill(0,10);
                    ecoParameters.pIntervals = pIntervals;
            }
            else
                pIntervals = ecoParameters.pIntervals;
        }
        else
                pIntervals = QPolygonF();


        //qDebug()<<"ECO SETECO INTERVALS"<<intervals;
        pushClearAllBands->setEnabled(true);
        pushUndo->setEnabled(false);

	for(int i=0;i<12;i++)
    		{
                        for(int j=0;j<o.numBands;j++)
                            ecoParameters.prezziEnergia[i][j]=o.prezziEnergia[i][j];
                        minEnergyPrices[i]     = o.prezziMinEnergia[i];
                        ecoParameters.prezziMinEnergia[i]=o.prezziEnergia[i][0];

                        for(int j=0;j<numBands;j++)
                        mPrezziEnergia[i][j] = o.prezziEnergia[i][j] ;

    		}
        fileTariffe     = ecoParameters.fileTariffe;
        fileBands       =ecoParameters.fileBands ;
        filePrezzi      =ecoParameters.filePrezziEnergia;
        fileMinPrezzi   =ecoParameters.filePrezziMinimi;
        fileTax         =ecoParameters.fileTax;
        updatePedaggiokWh();// in unit values;
        updatePedaggiokW();
        updatePedaggio();
       // qDebug()<<"ECO EnInflRate"<<ecoParameters.prezziEnergiaInflazione;
         

        updateEcoParView();
//        intervals  = ecoParameters.intervals;
        updateIntervalsView();


        updatePIntervalsView();
        checkImmIntervals->setChecked(ecoParameters.useImmIntervals);

        tIntervals = ecoParameters.tIntervals;
        updateTIntervalsView();

        updateTaxView();
        setLossFactor( );


// 	if (!filePrezzi.isEmpty()){
// 		loadPrezzi(filePrezzi);
//		updatePrezziView();
//		updatePrezziLabel(filePrezzi);
// 	}
	
// 	if (!fileMinPrezzi.isEmpty()){
// 		loadMinPrezzi(fileMinPrezzi);
//		updateMinPrezziView();
//		updateMinPrezziLabel(fileMinPrezzi);
// 	}
// 	if (!fileBands.isEmpty()){
//                 loadBands(fileBands);
//		updateRecentBands(fileBands);
                 updateTableBandsView();
// 	}
//        if (!fileTariffe.isEmpty()){
// 		getTariffeFromFile(fileTariffe);
//                updateRecent(fileTariffe);//aggiorna il nome del file
 //        }
  doNotUpdate = false;
}
void EcoVal::setProjectFolder(const QString &f)
{
	projectFolder = f;
}
// QwtPlot* EcoVal::vanDiagram()
// {
// 	return qwtVan;
// }
// QwtPlot* EcoVal::rawDiagram()
// {
// 	return qwtPlot;
// }

double EcoVal::getTaxVatReduction()
{
        return (ecoParameters.vat/100)*ecoParameters.initialCost*ecoParameters.benefitVATCost/100;
}
double EcoVal::getFreqCosts(int i,bool inflated)
{
    if (ecoParameters.maintenanceSFreq == 0)
        return 0;

    if (i % ecoParameters.maintenanceSFreq == 0)
        if (!inflated)
            return ecoParameters.maintenanceS;
    else
        return MyMath::inflate(i,ecoParameters.inflRate/100,ecoParameters.maintenanceS);

    else
        return 0;
}

void EcoVal::updateRowBandsView(int status,int x)
{
    for (int j=0;j<24;j++)
    {
        if (status==error)
        {
                tableBandsView->item(x,j)->setBackground(QBrush(QColor("red")));
        }
    else
    {
        tableBandsView->item(x,j)->setBackground(QBrush(QColor("red")));
    }

}
}
void EcoVal::updateTableBandsView(int status,int x)
        /*Update a particular row x with the status */
{
//         qDebug()<<"ECO updateTableBands"<<status<<x;
    int index    = comboIntervals->currentIndex();
    index = index<0 ? 0 : index;
    QString value = 0;
	for(int i=0;i<12;i++)
	{
		for (int j=0;j<24;j++)
		{
			/*From*/
			if (status==error)
			{
				tableBandsView->item(x,j)->setBackground(QBrush(QColor("red")));
			}
			else
			{
				if ( (bands[i].at(0).toInt()<=j) && (bands[i].at(1).toInt()>=j))
				{
		
                                    if (bands[i].at(2).toDouble()>0.00000000002){
                                        value = bands[i].at(2+index);
                                        tableBandsView->item(i,j)->setText(value);
                                    }
                                    else{
					tableBandsView->item(i,j)->setText((" "));
					tableBandsView->item(i,j)->setBackground(QBrush());
                                    }
				}		
				else
				{
					tableBandsView->item(i,j)->setText(" ");
					tableBandsView->item(i,j)->setBackground(QBrush());
				}
			}

                }

	}
         tableBandsView->resizeColumnsToContents();
         drawBandsPrices(ecoParameters.life);

}


void EcoVal::updateTableAndSpin()
{
    updateView(comboBands->currentIndex());
    updateTableBandsView();
}

void EcoVal::updateTableBandsView()
{
    if (!doNotUpdateIntervals) {
    int index = comboIntervals->currentIndex();
    index = index < 0 ? 0 : index;
    QString value ;
       //  qDebug()<<"ECO()---"<<bands;
	for(int i=0;i<12;i++)
	{
                /* Update the summary */
                /* Dec 2010           */
                tableSummaryBands->item(i,0)->setText((bands[i].at(0)));
                tableSummaryBands->item(i,1)->setText((bands[i].at(1)));
		for (int j=0;j<24;j++)
		{
		/*From*/
		 if ( (bands[i].at(0).toInt()<=j) && (bands[i].at(1).toInt()>=j)){

			
                     if (bands[i].at(2+index).toDouble()>0.000000000000000002){

                                value = bands[i].at(2+index);

                                tableBandsView->item(i,j)->setText(value);
                            }
				else
				tableBandsView->item(i,j)->setText(" ");
				
//  				qDebug()<<"ECO()"<<i<<bands[i].at(2);
                }
				else
				tableBandsView->item(i,j)->setText(" ");
			
		}

	}
        tableBandsView->resizeColumnsToContents();
    }
}
 
void EcoVal::changeSelectedBand(const QModelIndex& index)
{
        //qDebug()<<"ECO row clicked"<<index.row();
	comboBands->setCurrentIndex(index.row());
}
 
void EcoVal::setInstalledPower(double a)
{
	installedPower = a;
}
void EcoVal::updateTaxInfo()
{
        InfoDialog s;
        s.setString(infoTax);
                if (s.exec()){
                        infoTax = s.getString();

                }


}
void EcoVal::updateInfo()
{
	InfoDialog s;
	s.setString(infoTariffe);
		if (s.exec()){
			infoTariffe = s.getString();
// 			qDebug()<<infoTariffe;
		}

	
}
void EcoVal::updateInfoBands()
{
	InfoDialog s;
	s.setString(infoBands);
		if (s.exec()){
			infoBands = s.getString();
			
		}

	
}
void EcoVal::updateInfoPrezzi()
{
	InfoDialog s;
	s.setString(infoPrezzi);
		if (s.exec()){
			infoPrezzi = s.getString();
			
		}

	
}
void EcoVal::updateInfoPrezziMinimi()
{
	InfoDialog s;
	s.setString(infoPrezziMinimi);
		if (s.exec()){
			infoPrezziMinimi = s.getString();
			
		}

	
}
double EcoVal::getBonuses(int year)
{
    if (year <= ecoParameters.bonusesYears)
        return ecoParameters.bonuses/100;//they are in c/kWh
    else
        return 0;

}




/* TO REMEMBER */




//void EcoVal::resetTariffe()
//{
//
//    ecoParameters.tariffe[21] = dIVATariffe->value();
//
//    emit isDirty();
//
//}
void EcoVal::setYearlyMinPrice()
{

    if (!doNotUpdate){
    int index = comboImmissione->currentIndex();
    index = index < 0 ? 0 : index;
    ecoParameters.immissione.replace(index,dYearlyMinPrice->value());

    }
    if (!doNotEmit)
        emit isDirty();
    updateMinPrezziPlot();

}

void EcoVal::setTras( )
{

    if (!doNotUpdate){
    int index = comboTariffeIntervals->currentIndex();
    index = index < 0 ? 0 : index;
    groupTariffe->setTitle(groupTariffeTitle+"*");
    ecoParameters.tariffe[0].replace(index,dTrasmissionekWh->value());
    ecoParameters.tariffe[1].replace(index,dTrasmissionekW->value());
    ecoParameters.tariffe[2].replace(index,dTrasmissioneAnno->value());
   updatePedaggiokWh();
   updatePedaggiokW();
   updatePedaggio();
   setLossFactor( );

   if (!doNotEmit)
    emit isDirty();
    }	

}

void EcoVal::setDist( )
{
if (!doNotUpdate){
    int index = comboTariffeIntervals->currentIndex();
    index = index < 0 ? 0 : index;
	groupTariffe->setTitle(groupTariffeTitle+"*");
    ecoParameters.tariffe[3].replace(index,dDistribuzionekWh->value());
    ecoParameters.tariffe[4].replace(index,dDistribuzionekW->value());
    ecoParameters.tariffe[5].replace(index,dDistribuzioneAnno->value());
    updatePedaggiokWh();
    updatePedaggiokW();
    updatePedaggio();
    setLossFactor( );
    if (!doNotEmit)
        emit isDirty();
}
}
void EcoVal::setDisp( )
{
if (!doNotUpdate){
    int index = comboTariffeIntervals->currentIndex();
    index = index < 0 ? 0 : index;
    groupTariffe->setTitle(groupTariffeTitle+"*");
    ecoParameters.tariffe[16].replace(index,dDISP->value());
    ecoParameters.tariffe[17].replace(index,dDISPkWh->value());
    ecoParameters.tariffe[18].replace(index,dDISPkW->value());
   updatePedaggiokWh();
   updatePedaggiokW();
   updatePedaggio();
   setLossFactor( );
   if (!doNotEmit)
    emit isDirty();
}
}
void EcoVal::setMisura( )
{
if (!doNotUpdate){
    int index = comboTariffeIntervals->currentIndex();
    index = index < 0 ? 0 : index;
    groupTariffe->setTitle(groupTariffeTitle+"*");
    ecoParameters.tariffe[6].replace(index,dMisurakWh->value());
    ecoParameters.tariffe[7].replace(index,dMisurakW->value());
    ecoParameters.tariffe[20].replace(index,dMisuraAnno->value());
   // qDebug()<<"ECO SETMISURA"<<ecoParameters.tariffe[20]<<ecoParameters.tariffe[7]<<ecoParameters.tariffe[6];
   updatePedaggiokWh();
   updatePedaggiokW();
   updatePedaggio();
   setLossFactor( );
   if (!doNotEmit)
    emit isDirty();
}
}
void EcoVal::setAuc()
{
if (!doNotUpdate){
    int index = comboTariffeIntervals->currentIndex();
    index = index < 0 ? 0 : index;
    groupTariffe->setTitle(groupTariffeTitle+"*");
    ecoParameters.tariffe[8].replace(index,dAUCkWh->value());
    ecoParameters.tariffe[9].replace(index,dAUCkW->value());
    ecoParameters.tariffe[10].replace(index,dAUCanno->value());
    ecoParameters.tariffe[21].replace(index,dMCTkWh->value());
   // qDebug()<<"ECOVAL MCT"<<ecoParameters.tariffe[21];
   updatePedaggiokWh();
   updatePedaggiokW();
   updatePedaggio();
   setLossFactor( );
   if (!doNotEmit)
    emit isDirty();
}
}
void EcoVal::setLossFactor( )
{/* We suppose that the Loss Factor does not depends on the consumption intervals */
    if (!doNotUpdate){
//    int index = comboTariffeIntervals->currentIndex();
//    index = index < 0 ? 0 : index;
    int index = tIntervals.size();

    if (index==0)
        ecoParameters.tariffe[19].replace(0,dLoss->value());
    else
        ecoParameters.tariffe[19].fill(dLoss->value(),index);

     groupTariffe->setTitle(groupTariffeTitle+"*");
     if (!doNotEmit)
        emit isDirty();
}
}

void EcoVal::setProdFactors()
{
if (!doNotUpdate){
    int index = comboTariffeIntervals->currentIndex();
    index = index < 0 ? 0 : index;
    groupTariffe->setTitle(groupTariffeTitle+"*");
    ecoParameters.tariffe[11].replace(index,dPerditaTrasmissione->value());
  //  ecoParameters.tariffe[12].replace(index,dPerditaDistribuzione->value());
    ecoParameters.tariffe[12].replace(index,dCostiAmm->value());
    ecoParameters.tariffe[13].replace(index,dCTRkWh->value());
    ecoParameters.tariffe[14].replace(index,dFattCTR->value());
    ecoParameters.tariffe[15].replace(index,dAltriCostiMensili->value());
    ecoParameters.tariffe[22].replace(index,dLimitCostiAmm->value());

    ecoParameters.ammCostLimit = dLimitCostiAmm->value();
    if (!doNotEmit)
        emit isDirty();
}
}

void EcoVal::popUpMenu(const QPoint& a)
{

	QMenu menu;
	menu.addAction(a_clear);
	menu.addAction(a_copy);
	menu.exec(QCursor::pos());
	
}
void EcoVal::popUpMenuMinPrezzi(const QPoint& a)
{

        QMenu menu;
        menu.addAction(a_clear_min);
        menu.addAction(a_copy_min);
        menu.exec(QCursor::pos());

}
void EcoVal::createActions()
{ 
	a_clear = new QAction(tr("Azzera"),this);
	a_clear->setToolTip(tr("Azzera tutte le celle selezionate"));
	connect(a_clear,SIGNAL(triggered()),SLOT(clearSelected()));
	
	a_copy = new QAction(tr("Copia"),this);
	a_copy->setToolTip(tr("Copia il primo valore della selezione su tutte le celle selezionate"));
	connect(a_copy,SIGNAL(triggered()),SLOT(uniformize())); 

        a_clear_min = new QAction(tr("Azzera"),this);
        a_clear_min->setToolTip(tr("Azzera tutte le celle selezionate"));
        connect(a_clear_min,SIGNAL(triggered()),SLOT(clearSelectedMin()));

        a_copy_min = new QAction(tr("Copia"),this);
        a_copy_min->setToolTip(tr("Copia il primo valore della selezione su tutte le celle selezionate"));
        connect(a_copy_min,SIGNAL(triggered()),SLOT(uniformizeMin()));
}


void EcoVal::clearSelected()
{
	QList<QTableWidgetSelectionRange> sel = tablePrezziEnergia->selectedRanges();
        doNotCheck = true;
        int currentBand = comboImmBand->currentIndex();
	for(int k=0;k<sel.size();k++){
                for(int m=sel.at(k).topRow();m<=sel.at(k).bottomRow();m++){

                        mPrezziEnergia[m][currentBand] = 0;
                        ecoParameters.prezziEnergia[m][currentBand] = 0;
			tablePrezziEnergia->item(m,0)->setText(QString::number(0));
		}
        doNotCheck = false;
        tablePrezziEnergia->resizeColumnsToContents();

}
  tablePrezziEnergia->resizeColumnsToContents();
}
void EcoVal::clearSelectedMin()
{
        QList<QTableWidgetSelectionRange> sel = tableMinPrezziEnergia->selectedRanges();

        for(int k=0;k<sel.size();k++){
                for(int m=sel.at(k).topRow();m<=sel.at(k).bottomRow();m++){
                        minEnergyPrices.replace(m,0);
                        ecoParameters.prezziMinEnergia[m] = 0;
                        tableMinPrezziEnergia->item(m,0)->setText(QString::number(0));
                }

}
  tableMinPrezziEnergia->resizeColumnsToContents();
}
void EcoVal::uniformize()
{
	QList<QTableWidgetSelectionRange> sel = tablePrezziEnergia->selectedRanges();
        double value    = tablePrezziEnergia->item(sel.at(0).topRow(),0)->data(0).toDouble();
        int currentBand = comboImmBand->currentIndex();
	
	
	for(int k=0;k<sel.size();k++){
		for(int m=sel.at(k).topRow();m<=sel.at(k).bottomRow();m++){
                        mPrezziEnergia[m][currentBand] = value ;
                        ecoParameters.prezziEnergia[m][currentBand] = value;
			tablePrezziEnergia->item(m,0)->setText(QString::number(value));
		}
	tablePrezziEnergia->resizeColumnsToContents();

	
}
}
void EcoVal::uniformizeMin()
{
        QList<QTableWidgetSelectionRange> sel = tableMinPrezziEnergia->selectedRanges();
        double value= tableMinPrezziEnergia->item(sel.at(0).topRow(),0)->data(0).toDouble();



        for(int k=0;k<sel.size();k++){
                for(int m=sel.at(k).topRow();m<=sel.at(k).bottomRow();m++){
                        minEnergyPrices.replace(m,value);
                        ecoParameters.prezziMinEnergia[m] = value;
                        tableMinPrezziEnergia->item(m,0)->setText(QString::number(value));
                }
        tableMinPrezziEnergia->resizeColumnsToContents();


}
}
void EcoVal::clearAllBands()
{
    bandsPrevious = bands;
    bands.clear();
    bands = bandsDefault;
    intervalsPrevious = intervals;
    intervals.resize(0);
    if (intervalEditor!=0)
        intervalEditor->resetTable();
    comboIntervals->clear();

    for(int i=0;i<12;i++)
    {
            for (int j=0;j<24;j++)
            {
                    tableBandsView->item(i,j)->setText(" ");
                    tableBandsView->item(i,j)->setBackground(QBrush());
    }
            pushClearAllBands->setEnabled(false);
            pushUndo->setEnabled(true);

}
    tableBandsView->resizeColumnsToContents();
 //   drawBandsPrices(ecoParameters.life);

}
void EcoVal::saveAll()
{
    //If the file exist overwrite with changes, otherwise do nothing //
    QFileInfo fb(fileBands),fp(filePrezzi),fmp(fileMinPrezzi),ft(fileTariffe);

    if (!fileTariffe.isEmpty() && ft.exists())
        saveTariffe(fileTariffe);
    if (!fileBands.isEmpty()   && fb.exists())
        saveBandsValues(fileBands);
    if (!filePrezzi.isEmpty()  && fp.exists())
        savePrezzi(filePrezzi);
    if (!fileMinPrezzi.isEmpty() && fmp.exists())
        saveMinPrezzi(fileMinPrezzi);
}
void EcoVal::undoDel()
{
    bands     = bandsPrevious;
    intervals = intervalsPrevious;

    intervalEditor->setInterval(intervals);
    updateIntervals();
    updateTableBandsView();
    pushClearAllBands->setEnabled(true);
    pushUndo->setEnabled(false);
}

double EcoVal::findPedaggiokWh(double energy)
        /*In unit values*/
{
   // double iva = (1+ecoParameters.tariffe[21]/100);
    double iva = 1;
    int index = findTariffeIntervalId(0,energy);
    return  (ecoParameters.tariffe[3].at(index) +
                                  ecoParameters.tariffe[17].at(index) +
                                  ecoParameters.tariffe[0].at(index) +
                                  ecoParameters.tariffe[6].at(index) +
                                  ecoParameters.tariffe[8].at(index) +
                                  ecoParameters.tariffe[21].at(index)
                                  )*iva/100;

}

void EcoVal::updatePedaggiokWh()
        /*In unit values*/
         /* PedggiokWh only for 1 or no intervals */
{
   // double iva = (1+ecoParameters.tariffe[21]/100);
    double iva = 1;
     ecoParameters.pedaggiokWh = (ecoParameters.tariffe[3].at(0) +
                                  ecoParameters.tariffe[17].at(0) +
                                  ecoParameters.tariffe[0].at(0) +
                                  ecoParameters.tariffe[6].at(0) +
                                  ecoParameters.tariffe[8].at(0)
                                  )*iva/100;
}
double EcoVal::findPedaggio(double energy)
{
    // Find the interval for a generic Tariffa
    int index = findTariffeIntervalId(0,energy);
    return (ecoParameters.tariffe[2].at(index) +
                                  ecoParameters.tariffe[5].at(index) +
                                  ecoParameters.tariffe[10].at(index) +
                                  ecoParameters.tariffe[20].at(index) +
                                  ecoParameters.tariffe[18].at(index))/100;
}

void EcoVal::updatePedaggio()
        /* Pedaggio only for 1 or no intervals */
{
    ecoParameters.pedaggio =  (ecoParameters.tariffe[2].at(0) +
                              ecoParameters.tariffe[5].at(0) +
                              ecoParameters.tariffe[10].at(0) +
                              ecoParameters.tariffe[20].at(0) +
                              ecoParameters.tariffe[18].at(0))/100;

}
double EcoVal::findPedaggiokW(double energy)
{
    // Find the interval for a generic Tariffa
    int index = findTariffeIntervalId(0,energy);
    return                        ecoParameters.power * (
                                  ecoParameters.tariffe[1].at(index) +
                                  ecoParameters.tariffe[4].at(index) +
                                  ecoParameters.tariffe[18].at(index) +
                                  ecoParameters.tariffe[7].at(index)  +
                                  ecoParameters.tariffe[9].at(index)  )/100;
}
void EcoVal::updatePedaggiokW()
        /*In unit values*/
{


    ecoParameters.pedaggiokW = ecoParameters.power *
                               (ecoParameters.tariffe[1].at(0)+
                               ecoParameters.tariffe[4].at(0)+
                               ecoParameters.tariffe[18].at(0)+
                               ecoParameters.tariffe[7].at(0)+
                               ecoParameters.tariffe[9].at(0))/100;

}
void EcoVal::setDirtyBands()
{
    bandsDirty = true;
}
void EcoVal::setTax()
{
    if (!doNotUpdate){
    ecoParameters.taxes[0] = dTIvaBonus->value();
    ecoParameters.taxes[1] = dTIvaCS->value();
    ecoParameters.taxes[2] = dTIvaEn->value();

    ecoParameters.taxes[3] = dTIrpefBonus->value();
    ecoParameters.taxes[4] = dTIrpefCS->value();
    ecoParameters.taxes[5] = dTIrpefEn->value();

    ecoParameters.taxes[6] = dTIrapBonus->value();
    ecoParameters.taxes[7] = dTIrapCS->value();
    ecoParameters.taxes[8] = dTIrapEn->value();

    ecoParameters.taxes[9] = dTIresBonus->value();
    ecoParameters.taxes[10] = dTIresCS->value();
    ecoParameters.taxes[11] = dTIresEn->value();

    ecoParameters.taxes[12] = dTAltroBonus->value();
    ecoParameters.taxes[13] = dTAltroCS->value();
    ecoParameters.taxes[14] = dTAltroEn->value();
}

}
double EcoVal::getTaxes(const QVector<double> &i)
        /* 0 = contribute in unit value, CS or Injected(sold) Energy*/
        /* 1 = Cei*/
        /* 2 = credit for next year or payed in the current year(liq)*/
        /* 3 = Exchanged energy */
        /* 4 = Bonus*/
        /* 5 = Oe*/
        /* 6 = Cus*/
        /* 7 = Injected Energy * k */
        /* 8 = Used credi */

{
    double vEnergyInjected = 0;
    if ((ecoParameters.regime == SSPIT) )
        vEnergyInjected = (ecoParameters.taxes[2] +
                          ecoParameters.taxes[5]  +
                          ecoParameters.taxes[8]  +
                          ecoParameters.taxes[11] +
                          ecoParameters.taxes[14]) * i.at(8)/100;
    if (ecoParameters.regime == Vendita)
        vEnergyInjected = (ecoParameters.taxes[2] +
                          ecoParameters.taxes[5]  +
                          ecoParameters.taxes[8]  +
                          ecoParameters.taxes[11] +
                          ecoParameters.taxes[14] ) * i.at(0)/100;
//qDebug()<<"ECO VAL GETTAXE"<<vEnergyInjected<<i.at(1)<<i.at(0)<<ecoParameters.taxes[2]<<ecoParameters.taxes[8]<<ecoParameters.taxes[5]<<ecoParameters.taxes[11]<<ecoParameters.taxes[14];
            return (ecoParameters.taxes[0] +
                   ecoParameters.taxes[3]  +
                   ecoParameters.taxes[6]  +
                   ecoParameters.taxes[9]  +
                   ecoParameters.taxes[12] )* i.at(4)/100 +
                   (ecoParameters.taxes[1] +
                   ecoParameters.taxes[4]  +
                   ecoParameters.taxes[7]  +
                   ecoParameters.taxes[10] +
                   ecoParameters.taxes[13] )* i.at(0)/100 +
                   vEnergyInjected;

}
double EcoVal::getAltro(const QVector<double> &i)
{
    double vEnergyInjected = 0;
    if ((ecoParameters.regime == SSPIT) )
        vEnergyInjected = ecoParameters.taxes[14] * i.at(8)/100;
    if (ecoParameters.regime == Vendita)
           vEnergyInjected = ecoParameters.taxes[14] * i.at(0)/100;
// Bonus + CS + En.
    return (ecoParameters.taxes[12] * i.at(4) +
            ecoParameters.taxes[13] * i.at(0))/100 +
            vEnergyInjected;

}

double EcoVal::getIva(const QVector<double> &i)
{
    double vEnergyInjected = 0;
    if ((ecoParameters.regime == SSPIT) )
        vEnergyInjected = ecoParameters.taxes[2] * i.at(8)/100;
    if (ecoParameters.regime == Vendita)
           vEnergyInjected = ecoParameters.taxes[2] * i.at(0)/100;
// Bonus + CS + En.
    return (ecoParameters.taxes[0] * i.at(4) +
            ecoParameters.taxes[1] * i.at(0))/100 +
            vEnergyInjected;

}
double EcoVal::getIrpef(const QVector<double> &i)
{
    double vEnergyInjected = 0;
    if ((ecoParameters.regime == SSPIT) )
        vEnergyInjected = ecoParameters.taxes[5] * i.at(8)/100;
    if (ecoParameters.regime == Vendita)
           vEnergyInjected = ecoParameters.taxes[5] * i.at(0)/100;
// Bonus + CS + En.
    return (ecoParameters.taxes[3] * i.at(4) +
            ecoParameters.taxes[4] * i.at(0))/100 +
            vEnergyInjected;
}
double EcoVal::getIrap(const QVector<double> &i)
{
    double vEnergyInjected = 0;
    if ((ecoParameters.regime == SSPIT)  )
        vEnergyInjected = ecoParameters.taxes[8] * i.at(8)/100;
    if (ecoParameters.regime == Vendita)
           vEnergyInjected = ecoParameters.taxes[8] * i.at(0)/100;
    // Bonus + CS + En.
    return (ecoParameters.taxes[6] * i.at(4) +
            ecoParameters.taxes[7] * i.at(0))/100 +
            vEnergyInjected;
}
double EcoVal::getIres(const QVector<double> &i)
{
    double vEnergyInjected = 0;
    if ((ecoParameters.regime == SSPIT)  )
        vEnergyInjected = ecoParameters.taxes[11] * i.at(1)/100;
    if (ecoParameters.regime == Vendita)
           vEnergyInjected = ecoParameters.taxes[11] * i.at(0)/100;
    // Bonus + CS + En.
    return (ecoParameters.taxes[9] * i.at(4) +
            ecoParameters.taxes[10] * i.at(0))/100 +
            vEnergyInjected;
}
double EcoVal::getAltro()
{/* Return only the percent value /100*/
    return (ecoParameters.taxes[12]
            + ecoParameters.taxes[13]
            + ecoParameters.taxes[14])/100;
}

double EcoVal::getIrap()
/* Return only the percent value /100*/
{
    return (ecoParameters.taxes[6]
            + ecoParameters.taxes[7]
            + ecoParameters.taxes[8])/100;
}
double EcoVal::getIrpef()
{
    return (ecoParameters.taxes[3] +
            ecoParameters.taxes[4] +
            ecoParameters.taxes[5])/100;
}

double EcoVal::getIres()
{
    return (ecoParameters.taxes[9] +
            ecoParameters.taxes[10]+
            ecoParameters.taxes[11])/100;
}


void EcoVal::setTaxOnEn()
{
    if (!doNotUpdate){
    ecoParameters.VATonTotEnergy = dVATonEn->value();
    ecoParameters.IMPonEnergy   = dIMPkWh->value();
}
}

double EcoVal::getMonthlyTaxOnEn(int year, double mEnergy )
        /* This function gets the VAT on the payed */
        /* energy to the Provider . */

        /* mEnergy = consumed Energy  in one year*/
{
    double imp,tot,pedaggiokWh;
    pedaggiokWh = weightedSumTariffekWh(mEnergy,year);

    //1. Compute the Energy and Power component
    imp = MyMath::inflate(year,ecoParameters.inflRate/100,
                          pedaggiokWh + ecoParameters.pedaggiokW +
                          ecoParameters.pedaggio);
    //2. Compute the VAT
         tot = (imp + mEnergy * ecoParameters.IMPonEnergy/100)*
               ecoParameters.VATonTotEnergy/100;
//        qDebug()<<"ECO MTAXES"<<year<<
//                tot<<
//                ecoParameters.inflRate<<
//                ecoParameters.VATonTotEnergy<<
//                ecoParameters.IMPonEnergy<<
//                mEnergy<<
//                imp<<
//                pedaggiokWh<<
//                ecoParameters.pedaggiokW<<
//                ecoParameters.pedaggio;
         return tot;
}
//CHECK THE FOLLOWING
//double EcoVal::getMonthlyTaxOnEn(int year, double mEnergy )
//        /* This function gets the VAT on the payed */
//        /* energy to the Provider . */
//
//        /* mEnergy = consumed Energy  in one year*/
//{
//    double imp,fix,tot,pedaggiokWh,pedaggiokW;
//    pedaggiokWh = weightedSumTariffekWh(mEnergy,year);
//
//    //1. Compute the Energy and Power component
//    imp = MyMath::inflate(year,ecoParameters.inflRate/100,
//                          pedaggiokWh);
//    fix = MyMath::inflate(year,ecoParameters.inflRate/100,
//                          ecoParameters.pedaggiokW + ecoParameters.pedaggio);
//    //2. Compute the VAT
//        // tot = (imp + mEnergy * ecoParameters.IMPonEnergy/100)*
//           //    ecoParameters.VATonTotEnergy/100;
//
//    //Test101 Giugno2010
//    tot = (imp + mEnergy)*(ecoParameters.VATonTotEnergy/100 + ecoParameters.IMPonEnergy/100) +  fix;
//        qDebug()<<"ECO MTAXES"<<year<<
//                tot<<
//                ecoParameters.inflRate<<
//                ecoParameters.VATonTotEnergy<<
//                ecoParameters.IMPonEnergy<<
//                mEnergy<<
//                imp<<
//                pedaggiokWh<<
//                ecoParameters.pedaggiokW<<
//                ecoParameters.pedaggio;
//         return tot;
//}
void EcoVal::fireError(int num)
{
    switch (num)
    {
    case 500:
        QMessageBox::critical(this,tr("Errore 500"),tr("Il file sembra contenere dati non numerici."));
        break;
    }
}
bool EcoVal::eventFilter(QObject* obj, QEvent *event)
{
    if (obj == model) {
         // qDebug()<<"ECO eventfilter nessuno"<<event->type();
        if (event->type()== QEvent::MouseButtonRelease) {
       // qDebug()<<"ECO eventfilter";
        QMouseEvent *pMouseEvent = static_cast<QMouseEvent *>(event);
        if (pMouseEvent->button() == Qt::RightButton){//qDebug()<<"ECO eventfilter destro";
        }

        if (pMouseEvent->button() == Qt::LeftButton){
            loadBandFromList(listBands->currentIndex());
            //qDebug()<<"ECO eventfilter sinistro";
        }
    return true;
    }
    else
        return false;
    }
    else{
        qDebug()<<"ECO eventfilter nessuno"<<event->type();
        return QObject::eventFilter(obj, event);

     }
}

void EcoVal::showTab( )
{
    int index=  (treeWidget->currentIndex().row());
    if (index < stackedWidget->count())
        stackedWidget->setCurrentIndex(index);
}
int EcoVal::getNumBands()
{
    return numBands;
}
void EcoVal::updatePower()
{
    ecoParameters.power = dPotenzakW->value();
}

void EcoVal::updatePower(double d)
{
        ecoParameters.power = d;
    }


void EcoVal::enableMinPrices(int i)
{
    if (i==Qt::Checked){
        ecoParameters.useImmIntervals = true;
        tableMinPrezziEnergia->setEnabled(false);
        groupImmIntervals->setEnabled(true);
        groupBoxPM->setEnabled(false);
    }
    else{
        ecoParameters.useImmIntervals = false;
        tableMinPrezziEnergia->setEnabled(true);
        groupImmIntervals->setEnabled(false);
        groupBoxPM->setEnabled(true);
    }

updateMinPrezziPlot();
}
void EcoVal::resetAll()
{
    qDebug()<<"BACKUPECO"<<backupEco.prezziEnergia[0];
    /* Do not emit the "dirty" signal because a cleared project has not to be saved*/
    doNotEmit = true;
    setEcoParameters(backupEco);
    doNotEmit = false;
    updateEcoParView();
    updateTariffeView();
    updatePIntervalsView();
    updateIntervalsView();
    updateTIntervalsView();
    updateTaxView();

}
