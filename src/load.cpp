#include "ask.h"
#include "doubledelegate.h"
#include <qwt_interval_data.h>
#include "histogram_item.h"
#include "load.h"
#include <QDebug>
#include <qwt_plot_curve.h>
#include "mymath.h"
#include <qwt_scale_draw.h>
#include <qwt_scale_widget.h>
#include <qwt_painter.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_canvas.h>
#include <QFileDialog>
#include <QMessageBox>
#include <QDate>
#include <QMenu>
#define pi 3.1415926535897900000

Load::Load(QWidget* parent) :  QWidget(parent)
{
	setupUi(this);
        createActions();
        numDecimals = 6;
        setWindowTitle(tr("Consumi elettrici") + " - " + tr("Nessun nome") + "[*]");
        this->setWindowModified(false);
        grayStyle = " border: 2px solid gray;border-radius: 10px;padding: 0 8px;background: gray;";
        yellowStyle = " border: 2px solid gray;border-radius: 10px;padding: 0 8px;background: yellow; selection-background-color: darkgray;";



 	dFactor->setEnabled(false);
	restDay.resize(0);

	sundayPercent   = 0;
	doNotAskAgain = false;
	onlyCurrentMonth =false;
        doNotUpdate      =false;
        doNotModifyWin     =false;
	
// 	setWindowIcon(QIcon(":/images/)
	monthlyProfile = Uniform;
	 
	year 	       = 2010;
	valueDirty     = false;
	monthsList = MyMath::monthsList();
	fileCustom = "";
	recentSave = QDir::homePath();
	recentDirCarichi = QDir::homePath();
  	setDefault();
	
	typicalProfile<<3<<2<<2<<2<<1<<1<<2<<4<<4.2<<4.4<<4.2<<4.2<<4.4<<4.4<<4.8<<4.8<<4.6<<4.4<<5<<7<<8<<7.6<<6<<5;
	typicalCommercial<<1.1428571428571428<<1.1428571428571428<<1.1428571428571428<<1.1428571428571428<<1.1428571428571428<<1.1428571428571428<<1.1428571428571428<<1.1428571428571428<<1.1428571428571428<<8.4<<8.4<<8.4<<8.4<<8.4<<8.4<<8.4<<8.4<<8.4<<8.4<<1.1428571428571428<<1.1428571428571428<<1.1428571428571428<<1.1428571428571428<<1.1428571428571428;

	typicalIndustrial<<1.1428571428571428<<1.1428571428571428<<1.1428571428571428<<1.1428571428571428<<1.1428571428571428<<1.1428571428571428<<1.1428571428571428<<1.1428571428571428<<1.1428571428571428<<8.4<<8.4<<8.4<<8.4<<8.4<<8.4<<8.4<<8.4<<8.4<<8.4<<1.1428571428571428<<1.1428571428571428<<1.1428571428571428<<1.1428571428571428<<1.1428571428571428;


         tableMonthly->setCurrentCell(0,0);
         tableHourly->setCurrentCell(0,0);


	QVector<int> d(12);
	
	tableMonthly->setItemDelegate(new DoubleDelegate(MyMath::serie(0,12),100000000,0,2));
	tableHourly->setItemDelegate(new DoubleDelegate(MyMath::serie(0,24),100,0,2));
        connect(pushApply,SIGNAL(clicked()),SLOT(notify()));
        connect(pushCancel,SIGNAL(clicked()),SLOT(close()));

        connect(lineAnnui,SIGNAL(editingFinished()),SLOT(update()));
        connect(lineAnnui,SIGNAL(editingFinished()),SLOT(updateTitle()));
	connect(tableMonthly,SIGNAL(itemChanged(QTableWidgetItem*)),SLOT(updateMonthlyItems()));
	connect(tableMonthly,SIGNAL(itemChanged(QTableWidgetItem*)),SLOT(checkData(QTableWidgetItem*)));
connect(tableMonthly,SIGNAL(itemClicked(QTableWidgetItem*)),SLOT(updateHours(QTableWidgetItem* )));
connect(tableMonthly,SIGNAL(itemSelectionChanged()),SLOT(updateHoursFromSelection()));
 tableMonthly->setContextMenuPolicy(Qt::CustomContextMenu);
 tableHourly->setContextMenuPolicy(Qt::CustomContextMenu);
 connect(tableMonthly,SIGNAL(customContextMenuRequested(const QPoint &  )),this,SLOT(popMenu( )));
 connect(tableHourly,SIGNAL(customContextMenuRequested(const QPoint &  )),this,SLOT(popMenuHours( )));


connect(tableHourly,SIGNAL(itemChanged(QTableWidgetItem*)),SLOT(checkHourlyData(QTableWidgetItem*)));
	connect(tableHourly,SIGNAL(itemChanged(QTableWidgetItem*)),SLOT(updateHourlyItems()));
	connect(comboMonthly,SIGNAL(currentIndexChanged(int)),SLOT(setMonthlyProfile(int)));
 	connect(dFactor,SIGNAL(valueChanged(double)),SLOT(updateMonths()));
	connect(comboHourly,SIGNAL(activated(int)),SLOT(setHourlyProfile(int)));
	connect(buttonSave,SIGNAL(clicked()),SLOT(save()));
	connect(buttonSaveAs,SIGNAL(clicked()),SLOT(saveAs()));
	connect(buttonCarica,SIGNAL(clicked()),SLOT(load()));
	connect(checkCurrentMonths,SIGNAL(clicked()),SLOT(settings()));

	connect(dQuotaSabato,SIGNAL(valueChanged(double)),SLOT(setSatPercent(double)));
	connect(dQuotaDomenica,SIGNAL(valueChanged(double)),SLOT(setSunPercent(double)));
	connect(comboChiusura,SIGNAL(currentIndexChanged(int)),SLOT(setRestDay(int)));
 
        connect(checkNormSat,SIGNAL(stateChanged(int)),SLOT(setSatNormOption(int)));
        connect(checkNormSun,SIGNAL(stateChanged(int)),SLOT(setSunNormOption(int)));

        /* At begin, no closing day */
        dQuotaDomenica->setEnabled(false);

	w1 = QObject::tr("Attenzione: dati orari inconsistenti! Totale diverso 100%");
	w2 = QObject::tr("Attenzione: dati mensili inconsistenti! Totale diverso di 100%");

// 	tableMonthly->setCurrentCell(0,0);

	qwtHourly->enableAxis(QwtPlot::yLeft,true);
	qwtHourly->setCanvasBackground(QColor(Qt::white));

	qwtMonthly->enableAxis(QwtPlot::yLeft,true);
	qwtMonthly->setCanvasBackground(QColor(Qt::white));

	qwtWeekly->enableAxis(QwtPlot::yLeft,true);
	qwtWeekly->setCanvasBackground(QColor(Qt::white));
	
// 	plot = new QwtPlotCurve();

	QwtText tWlabel(tr("Consumo nella settimana - Mese") + MyMath::months(1));
        tWlabel.setFont(QFont("Times",10,QFont::Normal));
        

	plotW = new HistogramItem();
	plotW->attach(qwtWeekly);
	plotW->setColor(Qt::darkYellow);
	
	qwtWeekly->setTitle(tWlabel);
	

	plot = new HistogramItem();
	plot->attach(qwtHourly);
	plot->setColor(Qt::darkYellow);

	plotM = new HistogramItem();
	plotM->attach(qwtMonthly);
	plotM->setColor(Qt::darkYellow);
	
// 	plot->setStyle(QwtPlotCurve::Sticks);
	
	tableMonthly->setCurrentCell(0,0); //default is jan
	
	QwtText tMlabel(tr("Consumo totale mensile "));
        tMlabel.setFont(QFont("Times",10,QFont::Normal));

  	QwtText tlabel(tr("Consumo orario - Mese di ") + MyMath::months(1));
        tlabel.setFont(QFont("Times",10,QFont::Normal));
	QwtText xlabel(tr("Ora"));
	QwtText xMlabel(tr("Mese"));	
	QwtText ylabel(tr("[kWh]"));
        ylabel.setFont(QFont("Times",10,QFont::Normal));
        xlabel.setFont(QFont("Times",10,QFont::Normal));
        xMlabel.setFont(QFont("Times",10,QFont::Normal));

	QwtText xGlabel(tr("Giorno"));
        xGlabel.setFont(QFont("Times",10,QFont::Normal));


	qwtHourly->setAxisTitle(QwtPlot::xBottom,xlabel);
        qwtHourly->setAxisTitle(QwtPlot::yLeft,ylabel);
  	qwtHourly->setTitle(tlabel);
	qwtHourly->setAxisAutoScale(QwtPlot::yLeft);
        qwtHourly->setAxisScale(QwtPlot::xBottom,0.5,24.5);
        

	qwtMonthly->setAxisTitle(QwtPlot::xBottom,xMlabel);
        qwtMonthly->setAxisTitle(QwtPlot::yLeft,ylabel);
  	qwtMonthly->setTitle(tMlabel);
        qwtMonthly->setAxisScale(QwtPlot::xBottom,0.5,12.5,1);
	qwtMonthly->setAxisAutoScale(QwtPlot::yLeft);
	 

	qwtWeekly->setAxisTitle(QwtPlot::yLeft,ylabel);
	qwtWeekly->setAxisTitle(QwtPlot::xBottom,xGlabel);
	qwtWeekly->setAxisAutoScale(QwtPlot::yLeft);
	qwtWeekly->setAxisScale(QwtPlot::xBottom,0.5,7.5);
	alignScales();

	someError = false;
	updateHourlyPlot(0);
	doNotCheck = false;

	
	lineAnnui->setReadOnly(false);
	lineAnnui->setValidator(new QDoubleValidator(lineAnnui));
        update();
}
void Load::setRestDay(int i)
/*restdays from 0 to 6*/
/* update the view and the model*/
{
    if (!doNotUpdate){
	int m =tableMonthly->currentItem()->column();/*current month*/
        if (m>=0 && m<12){
            if (i==0){
                    restDay[m] = 7;
                    dQuotaDomenica->setEnabled(false);
                    checkNormSun->setEnabled(false);
                    //quotaSun[m] = 0;
                }
            if (i==1){
                    restDay[m] = 6;
                    dQuotaDomenica->setEnabled(true);
                    checkNormSun->setEnabled(true);
                }
            if (i>1){
                    restDay[m] = i-2;
                    dQuotaDomenica->setEnabled(true);
                    checkNormSun->setEnabled(true);
                }
            updateQuotas(m,year);
            updateHours(tableMonthly->currentItem(),user_);
    }
    }
    pushApply->setEnabled(true);
}
void Load::setSunPercent(double v)
{
    if (!doNotUpdate){
	int m =tableMonthly->currentItem()->column();/*current month*/
	sundayPercent = v;
	quotaSun[m] = v;
        /* Reset Sat options */
       // qDebug()<<"LOAD setSunPercent"<<checkNormSat->isChecked();
        if (checkNormSat->isChecked())
            setSatNormOption(Qt::Checked);
        else
        updateHours(tableMonthly->currentItem(),user_);
    }
    pushApply->setEnabled(true);
}
void Load::setSatPercent(double v)
{
    if (!doNotUpdate){
	int m =tableMonthly->currentItem()->column();/*current month*/

	quotaSat[m] = v;
        /* Reset Sun options */
        if (checkNormSun->isChecked())
            setSunNormOption(Qt::Checked);
        else
        updateHours(tableMonthly->currentItem(),user_);
    }
    pushApply->setEnabled(true);
}
void Load::settings()
{
// 	Ask a;
// 	 {
// 		if (a.exec()) {
		
			onlyCurrentMonth = checkCurrentMonths->isChecked();
			
			/*
		}
	}*/
}
bool Load::isError()
{
	return someError;
}

void Load::storeItem(QTableWidgetItem* current)
{
        currentItemValue = current->text().toDouble();
}
void Load::checkHourlyData(QTableWidgetItem* current)
        /* Called when a cell in the tableHourly is edited */
{
        double  valuePercent,total ;
        double  sum,sum2;
	int month,hour;
	QVector<double> res;

	month = tableMonthly->currentItem()->column(); // the value is mLoadValue[month];


	hour= current->row();
        pushApply->setEnabled(true);

        valuePercent	= tableHourly->item(hour,0)->text().toDouble();


	sum = 0;
	sum2=0;

	if (month<12 && month>=0){
		
		if (!doNotCheckHours) {

                         res = getMonthlyLoad(month,year);
                         total = res.at(0);/*normal days*/
                         gNormLoad[month] = res.at(0);
                         gSatLoad[month ] = res.at(1);/*The same profile as in normal days */
                         gSunLoad[month ] = res.at(2);/*The same profile as in normal days */

			doNotCheckHours = true;

		 	hLoad[month*24 + hour] 	   = valuePercent*total/100;
			hLoadPercent[month*24+hour] = valuePercent;

			if (mLoadValue[month]<0.0000002)
				tableHourly->item(hour,1)->setText(QString::number(0));
			else
                                tableHourly->item(hour,1)->setText(QString::number(hLoad[month*24 + hour]));

			for(int i=0; i<24;i++) {
				sum+= hLoad.at(i + month*24);
// 				sum2+=tableHourly->item(i,1)->text().toDouble();
				sum2+=hLoadPercent.at(i + month*24);

//   				qDebug()<<"LOAD Hourly sum "<<month<<total<<sum<<sum2<<hLoad.at(i+ month*24)<<hLoadPercent[month*24+hour]<<valuePercent<<mLoadValue[month]<<(sum>mLoadValue[month]);
				
				
			}

		
                        if ( fabs(sum2-100)>0.0002 && total>0.0000000002) {
					 
					labelWarningHours->setText("<font color=\'red\'>" + w1 +"</font>");
					someError |= true;
	// 				current->setBackground(QBrush(QColor("red")));
// 					qDebug()<<"LOAD Hourly ----------------------------"<<total<<sum2-100;
					}
				else
					{
					labelWarningHours->setText("");
					someError |= false;
	// 				current->setBackground(QBrush());
					}


                labelTotal->setText(QString("%L1").arg(sum));
                labelTotalPercent->setText(QString::number(sum2));
  		comboHourly->setCurrentIndex(hCustom);	
                hourlyProfile.replace(month,hCustom);

		doNotCheckHours = false;

	updateHourlyPlot(month); 
		}
	}
}
void Load::checkData(QTableWidgetItem* current)
/* Check data on the monthly values table */
{
if (!doNotCheck) {
        double c, total;
        double  sum,sum2;
	int col;
	col = tableMonthly->column(current);
	c = QLocale().toDouble(current->text());
	sum = 0;
	sum2=0;
// 	a = annuiDSpin->value();
	
        pushApply->setEnabled(true);
	
	doNotCheck = true;
	mLoadValue[col] = c;
	total = MyMath::cumSum(mLoadValue);
// 	tableMonthly->item(1,col)->setText(QString::number(c*100/a,'f',2));
		for(int i=0; i<12;i++) {
			sum+= mLoadValue.at(i);
// 			sum2+= mLoadValue.at(i);
                        //qDebug()<<"LOAD check data sum "<<sum<<i<<mLoadValue.at(i);
			
			tableMonthly->item(0,i)->setText(QString("%L1").arg(mLoadValue[i]));
 			if (total>=0.00000002)
			 
				
				tableMonthly->item(1,i)->setText(QString("%L1").arg(mLoadValue[i]*100/total,0,'f',2));
			else
					tableMonthly->item(1,i)->setText(QString::number(0));
			

			
		}
// 	doNotCheck = true;
        tableMonthly->item(0,12)->setText(QString("%L1").arg(sum));

// 	annuiDSpin->setValue(sum);
        lineAnnui->setText(QString::number(sum));
	updateMonthlyPlot();

        updateHours(current);

	if (total>0.0000002)
	tableMonthly->item(1,12)->setText(QString("%L1").arg(sum*100/total,0,'f',2));
	else
	tableMonthly->item(1,12)->setText(QString::number(0));
	comboMonthly->setCurrentIndex(Custom);
	doNotCheck = false;


	}
}

void Load::updateHourlyItems()
{
	
	tableHourly->resizeColumnsToContents();
	
}
void Load::updateMonthlyItems()
{
        updateTitle();
	tableMonthly->resizeColumnsToContents();
	
}
void Load::updateHoursProfileDetails(int t)
        /* Update the view */
{
doNotUpdate = true;
if (t<12){
    if (restDay[t]== 7)
        comboChiusura->setCurrentIndex(0);
    if (restDay[t]== 6)
        comboChiusura->setCurrentIndex(1);
    if (restDay[t]!=6 && restDay[t]<6 && restDay[t]>=0)
        comboChiusura->setCurrentIndex(restDay[t]+2);
   // qDebug()<<"LOAD UpdateProfile-"<<quotaSat[t]<<checkNormSat->isChecked();
    dQuotaSabato->setValue(quotaSat[t]);
    dQuotaDomenica->setValue(quotaSun[t]);
    checkNormSat->setChecked(equalSat.at(t));
    checkNormSun->setChecked(equalSun.at(t));

    if (checkNormSat->isChecked())
        dQuotaSabato->setEnabled(false);
    else
        dQuotaSabato->setEnabled(true);

    if (checkNormSun->isChecked())
        dQuotaDomenica->setEnabled(false);
    else
        dQuotaDomenica->setEnabled(true);

    }
//qDebug()<<"LOAD UPDATE HOURS PROFILE DETAILS";
doNotUpdate = false;
}
void Load::update()
{



    int t = tableMonthly->currentItem()->column();
	updateMonths();
        updateHoursProfileDetails(t);
        updateHours(tableMonthly->currentItem(),user_);

        pushApply->setEnabled(true);
        setWindowModified(true);
}
QVector<double> Load::getMonthlyLoad(int month,int y)
{
        /* Compute the load of week days different from weekends and closing days */
	/* o(0) = load for normal days; o(1)=load for sat; o(2) = load of sunday*/
	/* month =0-11*/
	QVector<int> numOfWeeksAndRestDays;
	QVector<double> o;
	double numF,numSat,numSun;

        /* Check if we have to normalize saturday and sunday percents */
        if (month>11 || month<0)
        {
            qDebug()<<"WARNING MONTH>11 in LOAD::getMonthlyLoad!";
            return QVector<double>();
        }
numOfWeeksAndRestDays = restDay[month]==7 ?
                        MyMath::numOfWeekendsAndRests(QDate(y,month+1,1),0):
                        MyMath::numOfWeekendsAndRests(QDate(y,month+1,1),restDay[month]+1);





	/*NO REST DAY?*/
	if (restDay[month]==7){
		numF =  mLoadValue[month]*(1-(quotaSat[month])/100);/*normal days*/
		numSun = numF;

	}
	else
	{
		numF = mLoadValue[month]*(1-(quotaSat[month]+quotaSun[month])/100);/*normal days*/
		numSun = mLoadValue[month]*( quotaSun[month])/100;/*weekend sunday or closing*/

	}

	 numSat = mLoadValue[month]*( quotaSat[month]  )/100;/*weekend saturday*/
 	
// 	o << numF/(MyMath::monthEnd(month+1,year) - numOfWeeksAndRestDays.at(0) - numOfWeeksAndRestDays.at(1) - numOfWeeksAndRestDays.at(2)) <<
// 	     numSat/(numOfWeeksAndRestDays.at(0)  )<<
// 	     numSun/(numOfWeeksAndRestDays.at(1)  );

	/* Closing days are considered as sundays and viceversa */
	int numOfDays = MyMath::monthEnd(month+1,year);
	
	o << numF/( numOfDays - numOfWeeksAndRestDays.at(0) - numOfWeeksAndRestDays.at(2)) <<
	     numSat/(numOfWeeksAndRestDays.at(0)  );

	if (restDay[month]==7)
	     o<<numSun/(numOfDays - numOfWeeksAndRestDays.at(0) - numOfWeeksAndRestDays.at(2) );
	else
	     o<<numSun/(numOfWeeksAndRestDays.at(2)  );

       // qDebug()<<"LOAD getMonthly Load"<<restDay[month]<<numF<<numSun<<numSat<<numOfWeeksAndRestDays.at(0)<<numOfWeeksAndRestDays.at(1)<<numOfWeeksAndRestDays.at(2)<<month;
	return o; 
}
void Load::updateHoursFromSelection()
        // Update by taking only the first item of the selection
{
    QList<QTableWidgetItem*> a = tableMonthly->selectedItems();
    if (a.size()>0)
    {
        updateHours(a.at(0),user_);
    }
    updateTitle();
}
void Load::updateHours(QTableWidgetItem *a)
{
    updateHours(a,user_);
}

void Load::updateHours(QTableWidgetItem* c,int mode)
{
//qDebug()<<"UPDATE HOURS"<<mode<<gSunLoad <<restDay ;
	// Pick the current month value
	double v,y;
	QVector<double> res;
	 
	int m = c->column();

// 	int mtableMonthly->currentColumn();


	if (m==-1 || m>11)
                m=0;//Jan as defaults


       //  qDebug()<<"UPDATE HOURS"<<m<<mode<<y<<gSunLoad[m]<<restDay[m];
        updateQuotas(m,year);
	switch (hourlyProfile[m]){
		case hUniform:
                //Save the state of the check box

		labelWarningHours->setText("");

                res = getMonthlyLoad(m,year);
                y    = res.at(0);
                gNormLoad[m ] = res.at(0);
                gSatLoad[m  ] = res.at(1);/*The same profile as in normal days */
                gSunLoad[m  ] = res.at(2);/*The same profile as in normal days */
		doNotCheckHours = true;

              //   qDebug()<<"LOAD UpdateHours UNIFORM ----------------------"<<m<<gNormLoad<<gSatLoad<<gSunLoad<<restDay;
               //  qDebug()<<"LOAD UpdateHours UNIFORM ----------------------"<<m<<gNormLoad[m]<<gSatLoad[m]<<gSunLoad[m]<<restDay[m];
		v = y /24;
			for(int i=0;i<24;i++){
                                /*Update the model and the View*/
				hLoad[i+24*m] = v; 
				hLoadPercent[i+24*m] = 100.0/24;
                                tableHourly->item(i,1)->setText(QString("%L1").arg(v));
				if (v<0.000000002)
				tableHourly->item(i,0)->setText(QString::number(0));
				else
                                tableHourly->item(i,0)->setText(QString("%L1").arg(hLoadPercent[i+24*m]));
				
				}
                labelTotal->setText(QString("%L1").arg(y));
		if (v<0.000000002)
                        labelTotalPercent->setText(QString("%L1").arg(0));
		else
			labelTotalPercent->setText(QString::number(100));
                labelTotal->setText(QString::number(y));
                labelTotalSat->setText(QString("%L1").arg(gSatLoad[m]));
                labelTotalRest->setText(QString("%L1").arg(gSunLoad[m]));
		doNotCheckHours = false;
		break;
		case hTipico:

                res = getMonthlyLoad(m,year);
                y    = res.at(0);
                gNormLoad[m ] = res.at(0);
                gSatLoad[m  ] = res.at(1);/*The same profile as in normal days */
                gSunLoad[m  ] = res.at(2);/*The same profile as in normal days */
		labelWarningHours->setText("");
                //qDebug()<<"LOAD UpdateHours summer TIPICO-----------------"<<m;
		doNotCheckHours = true;
			for(int i=0;i<24;i++){
				v = y*typicalProfile[i]/100.0;
				hLoad[i+24*m] 	     = v; 
				hLoadPercent[i+24*m] = typicalProfile[i];
			
				tableHourly->item(i,1)->setText(QString("%L1").arg(v,0,'f',2));
				if (v<0.000000000002)
                                        tableHourly->item(i,0)->setText(QString("%L1").arg(0));
				else
					tableHourly->item(i,0)->setText(QString("%L1").arg(typicalProfile[i]));
				}
		labelTotal->setText(QString::number(y));
		if (mLoadValue[m]<0.0000000002)
			labelTotalPercent->setText(QString::number(0));
		else
			labelTotalPercent->setText(QString::number(100));
		
                labelTotal->setText(QString::number(y));
                labelTotalSat->setText(QString("%L1").arg(gSatLoad[m]));
                labelTotalRest->setText(QString("%L1").arg(gSunLoad[m]));
		doNotCheckHours = false;
			
		break;
		case hCustom:
			 
			doNotCheckHours = true;
                        //qDebug()<<"LOAD updateHours CUSTOM";
// 			s=0;
// 			p=0;
// 			s = MyMath::cumSum(hLoad,m*24,m*24+23);
// 			p = MyMath::cumSum(hLoadPercent,m*24,m*24+23);
			
                        for(int i=0;i<24;i++){
//
//
//// 				v =hLoad[i+24*m];
////  				s += v;
//// //  				p+= v;
//// 				tableHourly->item(i,1)->setText(QString("%L1").arg(hLoad[i+24*m]));
                                tableHourly->item(i,1)->setText(QString::number(hLoad[i+24*m]));
                                tableHourly->item(i,0)->setText(QString("%L1").arg(hLoadPercent[i+24*m]));

//
                                }
			
// 			tableHourly->item(24,1)->setText(QString::number(p*100.0/s));

  			doNotCheckHours = false;


                        //checkHourlyData(tableHourly->currentItem());

// 		labelTotal->setText(QString::number(s));
// 		labelTotalPercent->setText(QString::number(p));
		break;
		case hCommercial:
                /* Commercial: default rest day is Sanday and equalized Sat */
                doNotUpdate = true;

                if (mode==default_){
                    restDay[m] = 6;
                    //checkNormSat->setChecked(true);
                    equalSat.replace(m,true);
                }




               // dQuotaSabato->setEnabled(false);
                updateQuotas(m,year);
                dQuotaSabato->setValue(quotaSat[m]);



                res = getMonthlyLoad(m,year);
                y    = res.at(0);
                gNormLoad[m ] = res.at(0);
                gSatLoad[m  ] = res.at(1);/*The same profile as in normal days */
                gSunLoad[m  ] = res.at(2);/*The same profile as in normal days */
		labelWarningHours->setText("");
                //qDebug()<<"LOAD UpdateHours summer COMMERCIAL-----------------"<<m;
		doNotCheckHours = true;
			for(int i=0;i<24;i++){
				v = y*typicalCommercial[i]/100.0;
                                hLoad[i+24*m] 	     = y*typicalIndustrial[i]/100.0;;
				hLoadPercent[i+24*m] = typicalCommercial[i];
                                tableHourly->item(i,1)->setText(QString("%L1").arg(v));
				if (v<0.000000000002)
                                        tableHourly->item(i,0)->setText(QString("%L1").arg(0));
				else
                                        tableHourly->item(i,0)->setText(QString("%L1").arg(typicalCommercial[i]));
				}
		labelTotal->setText(QString::number(y));
                labelTotalSat->setText(QString("%L1").arg(gSatLoad[m]));
                labelTotalRest->setText(QString("%L1").arg(gSunLoad[m]));
		if (mLoadValue[m]<0.0000000002)
			labelTotalPercent->setText(QString::number(0));
		else
			labelTotalPercent->setText(QString::number(100));
		


                doNotUpdate = false;
		doNotCheckHours = false;

		break;
		case hIndustrial:
                    /* Industrial: default Sunday as rest and 0 for % sat */
                    doNotUpdate = true;
                    if (mode==default_){
                        restDay[m]  = 6;
                        equalSat.replace(m,false);
                        quotaSat[m] = 0;
                    }
                    dQuotaSabato->setValue(quotaSat[m]);
                    updateQuotas(m,year);


                    res = getMonthlyLoad(m,year);
                    y    = res.at(0);
                    gNormLoad[m ] = res.at(0);
                    gSatLoad[m  ] = res.at(1);/*The same profile as in normal days */
                    gSunLoad[m  ] = res.at(2);/*The same profile as in normal days */

                    labelWarningHours->setText("");
                    //qDebug()<<"LOAD UpdateHours summer TIPICO-----------------"<<m;
                    doNotCheckHours = true;
                            for(int i=0;i<24;i++){
                                    v = y*typicalIndustrial[i]/100.0;
                                    hLoad[i+24*m] 	     = v;
                                    hLoadPercent[i+24*m] = typicalIndustrial[i];
                                    tableHourly->item(i,1)->setText(QString("%L1").arg(v));
                                    if (v<0.000000002)
                                            tableHourly->item(i,0)->setText(QString::number(0));
                                    else
                                            tableHourly->item(i,0)->setText(QString("%L1").arg(typicalIndustrial[i]));
                                    }
                    labelTotal->setText(QString::number(y));
                    if (mLoadValue[m]<0.00000002)
                            labelTotalPercent->setText(QString::number(0));
                    else
                            labelTotalPercent->setText(QString::number(100));
                    labelTotal->setText(QString::number(y));
                    labelTotalSat->setText(QString("%L1").arg(gSatLoad[m]));
                    labelTotalRest->setText(QString("%L1").arg(gSunLoad[m]));
                    doNotCheckHours = false;
                    doNotUpdate     = false;
		break;
                default:
		labelWarningHours->setText("");
               // qDebug()<<"LOAD UpdateHours NONE---------------------"<<m<<hourlyProfile[m];
		doNotCheckHours = true;
		 
		v = 0;
			for(int i=0;i<24;i++){
				
				hLoad[i+24*m] = v; 
				hLoadPercent[i+24*m] = 0;
                                tableHourly->item(i,1)->setText(QString("%L1").arg(v));
				 
				tableHourly->item(i,0)->setText(QString::number(0));
				 
				
				}
		labelTotal->setText(QString::number(0));
		 
			labelTotalPercent->setText(QString::number(0));
                //qDebug()<<"LOAD update end before break";
		doNotCheckHours = false;
		break;
	}

	comboHourly->setCurrentIndex(hourlyProfile[m]);
        updateHoursProfileDetails(m);
	updateHourlyItems();
	updateHourlyPlot(m); 
	updateWeeklyPlot(m); 
        updateTitle();
}
void Load::updateWeeklyPlot(int m)
{
	QwtArray<QwtDoubleInterval> intervals(7);
	QwtArray<double> values(7);
	int pivot;
	double pos=0.5;
	
	for(int i=0;i<7;i++)
	{
		if (restDay[m]==7)
			pivot = 6;
		else
			pivot = restDay[m];

		intervals[i] = QwtDoubleInterval(pos, pos + 1);
		pos += 1;
		if (i==5)
			values[i] = gSatLoad[m];
                else {
                    if (i==pivot)
                            values[i] = gSunLoad[m];
                    else
                            values[i] = gNormLoad[m];
                }
//qDebug()<<"LOAD UpdateWeeklyPlot"<< restDay[m] <<gSunLoad[m]<<gSatLoad[m]<<values[i];
	}
	
	plotW->setData(QwtIntervalData(intervals, values));
	
 
	qwtWeekly->replot();

}
void Load::updateMonthlyPlot()
{
	QwtArray<QwtDoubleInterval> intervals(12);
	QwtArray<double> values(12);
	double pos=0.5;
	for(int i=0;i<12;i++)
	{
		intervals[i] = QwtDoubleInterval(pos, pos + 1);
		pos += 1;
		values[i] = mLoadValue[i];
	}
	
	plotM->setData(QwtIntervalData(intervals, values));
	

	qwtMonthly->replot();
}
void Load::updateHourlyPlot(int month)
{
	QwtArray<QwtDoubleInterval> intervals(24);
	QwtArray<double> values(24);
        double pos=0.5;


	
	for(int i=0;i<24;i++)
	{
		intervals[i] = QwtDoubleInterval(pos, pos + 1);
		pos += 1;
		values[i] = hLoad[month*24 + i];
	}
	
		
		
		plot->setData(QwtIntervalData(intervals, values));
	
	QwtText tlabel(tr("Consumo orario - Mese di ") + MyMath::months(month+1));
	QwtText tWlabel(tr("Consumo nella settimana - Mese di ") + MyMath::months(month+1));
        tlabel.setFont(QFont("Times",10,QFont::Normal));
        tWlabel.setFont(QFont("Times",10,QFont::Normal));
	qwtHourly->setTitle(tlabel);
	qwtWeekly->setTitle(tWlabel);
	qwtHourly->replot();
	qwtWeekly->replot();
        groupBox_2->setTitle(tr("Ripartizione settimanale e profili orari") + " - " + MyMath::months(month+1));
}
double Load::getYearlyLoadPercent(int y,int month)
        /* month<12 >=0 */
        /* Percent for Uniform distribution */
{

    return 1.0*QDate(y,month+1,1).daysInMonth()/QDate(y,month+1,1).daysInYear();

}
bool Load::zeroLoad()
{
   // qDebug()<<"LOAD sum"<<MyMath::cumSum(monthlyLoad)<<monthlyLoad;
    if (MyMath::cumSum(mLoadValue)>0.000002)
        return false;
                else
        return true;

}
void Load::resetAll()
{
    lineAnnui->setText("0");
    fileCustom = "";

    mLoadValue.fill(0,12);
    gNormLoad.fill(0,12);
    gSunLoad.fill(0,12);
    gSatLoad.fill(0,12);
    quotaSat.fill(0,12);
    quotaSun.fill(0,12);
    ML.fill(0,12);
    equalSat.fill(true,12);
    equalSun.fill(false,12);
    hourlyProfile.fill(Uniform,12);
    update();

}

void Load::updateMonths()
{
        double a,total,v,vp;
        a          = QLocale().toDouble(lineAnnui->text());
        yearlyLoad = a;
// 	qDebug()<<"updateMOnth begin"<<monthlyProfile;
	switch (monthlyProfile) {
        pushApply->setEnabled(true);
	case (Uniform):
		monthlyLoadPrev  = monthlyLoad;
		
// 		labelWarning->setText("");
		monthlyLoad.resize(0);
		doNotCheck = true;
		for(int mm=0;mm<12;mm++){
                      //  v= a * getYearlyLoadPercent(year,mm);

                      //  vp = 100.0/12;
                        vp=getYearlyLoadPercent(year,mm);
                        v= a * vp;
                        tableMonthly->item(1,mm)->setText(QString("%L1").arg(vp*100,0,'f',2));
			tableMonthly->item(1,mm)->setBackground(QBrush());
			tableMonthly->item(0,mm)->setText(QString("%L1").arg(v,0,'f',2));
			tableMonthly->item(0,mm)->setBackground(QBrush());
			monthlyLoad<< v;
			
		}
// 		qDebug()<<"updateMOnth begin2"<<monthlyProfile;
		tableMonthly->item(0,12)->setText(QString::number(a));
		tableMonthly->item(1,12)->setText(QString::number(100));
		tableMonthly->item(0,12)->setBackground(QBrush());
		
		doNotCheck = false;
		valueDirty = true;
		mLoadValue.resize(0);
		mLoadValue = monthlyLoad;
               // qDebug()<<"updateMOnth begin2"<<mLoadValue;
	break;
	case Summer:
		doNotCheck = true;
// 		labelWarning->setText("");
		monthlySummerLoadPrev = monthlySummerLoad;
		monthlySummerLoad.resize(0);
		for(int mm=0;mm<12;mm++){
			if (mm>4 && mm<9) {
                                tableMonthly->item(1,mm)->setText(QString("%L1").arg(15));
                                tableMonthly->item(0,mm)->setText(QString("%L1").arg(a*15/100.0));
                                monthlySummerLoad<<a*15/100;
			}
			else
			{
                                tableMonthly->item(1,mm)->setText(QString("%L1").arg(5));
                                tableMonthly->item(0,mm)->setText(QString("%L1").arg(a*5/100.0));
                                monthlySummerLoad<<a*5/100;
			}
		
		}
		tableMonthly->item(0,12)->setText(QString::number(a));
		tableMonthly->item(1,12)->setText(QString::number(100));
		mLoadValue = monthlySummerLoad;
		doNotCheck = false;
		valueDirty = true;
	break;
	case Winter:
		doNotCheck = true;
// 		labelWarning->setText("");
		monthlyWinterLoadPrev = monthlyWinterLoad;
		monthlyWinterLoad.resize(0);
		for(int mm=0;mm<12;mm++){
			if (mm>5 && mm<8) {
                                tableMonthly->item(1,mm)->setText(QString("%L1").arg(5));
                                tableMonthly->item(0,mm)->setText(QString("%L1").arg(a*5/100.0));
                                monthlyWinterLoad<<a*5/100;
			}
			else
			{
                                tableMonthly->item(1,mm)->setText(QString("%L1").arg(15));
                                tableMonthly->item(0,mm)->setText(QString("%L1").arg(a*15/100.0));
                                monthlyWinterLoad<<a*15/100;
			}
		
		}
		tableMonthly->item(0,12)->setText(QString("%L1").arg(a));
		tableMonthly->item(1,12)->setText(QString::number(100));
		mLoadValue = monthlyWinterLoad;
		doNotCheck = false;
		valueDirty = true;
	break;
	case SeasonalWinter:
	doNotCheck = true;
// 		labelWarning->setText("");
		mLoadValue.resize(0);
		monthlyWinterLoadPrev = monthlyWinterLoad;
		monthlyWinterLoad.resize(0);

		for(int mm=0;mm<12;mm++){
			v= (10+dFactor->value()*sin(2*pi*(mm-9)/12))/10 *a/12;
                        vp = v/a * 100;
// 			qDebug()<<"LOAD SEASONAL WINTER-----------------------"<<v;
                        tableMonthly->item(1,mm)->setText(QString("%L1").arg(vp,0,'f',2));
			tableMonthly->item(1,mm)->setBackground(QBrush());
                        tableMonthly->item(0,mm)->setText(QString("%L1").arg(v,0,'f',2));
			tableMonthly->item(0,mm)->setBackground(QBrush());
			mLoadValue<< v;
		
		}
		tableMonthly->item(0,12)->setText(QString("%L1").arg(a));
		tableMonthly->item(1,12)->setText(QString::number(100));
	 
		doNotCheck = false;
		valueDirty = true;
	break;
	case SeasonalSummer:
		doNotCheck = true;
// 		labelWarning->setText("");
		mLoadValue.resize(0);
		monthlyWinterLoadPrev = monthlyWinterLoad;
		monthlyWinterLoad.resize(0);
		for(int mm=0;mm<12;mm++){
			v= (10+dFactor->value()*sin(2*pi*(mm-3)/12))/10 *a/12;
                         vp = v/a * 100;
// 			qDebug()<<"LOAD SEASONAL SUMMER-----------------------"<<v;
                        tableMonthly->item(1,mm)->setText(QString("%L1").arg(vp,0,'f',2));
			tableMonthly->item(1,mm)->setBackground(QBrush());
			tableMonthly->item(0,mm)->setText(QString("%L1").arg(v,0,'f',2));
			tableMonthly->item(0,mm)->setBackground(QBrush());
			mLoadValue<< v;
		
		}
		tableMonthly->item(0,12)->setText(QString("%L1").arg(a));
		tableMonthly->item(1,12)->setText(QString::number(100));
	 
		doNotCheck = false;
		valueDirty = true;
	break;
	case Custom:
		doNotCheck = true;
// 		labelWarning->setText("");
		monthlyCustomLoadPrev = monthlyCustomLoad;
		monthlyCustomLoad.resize(0);
 		
		total = MyMath::cumSum(mLoadValue);
        //	qDebug()<<"LOAD updateMonths custom total"<<total;
	
		for(int mm=0;mm<12;mm++){
		
				tableMonthly->item(0,mm)->setText(QString("%L1").arg(mLoadValue[mm]));
				
				if (total>0.000000002)
 				tableMonthly->item(1,mm)->setText(QString("%L1").arg(mLoadValue[mm]*100.0/total));
 				else
 				tableMonthly->item(1,mm)->setText(QString::number(0));
				
		}
		
		doNotCheck = false;
  		checkData(tableMonthly->item(0,0));
		valueDirty = true;
	break;
	
	}
updateMonthlyPlot();
}

 
void Load::setMonthlyProfile(int i)
{
	if (i>0 && i<=5)
			monthlyProfile = i;
	else
			monthlyProfile = Uniform;
	
        if (i!=Custom){
		lineAnnui->setReadOnly(false);
                lineAnnui->setEnabled(true);
                lineAnnui->setStyleSheet(yellowStyle);

            }
        else{
		lineAnnui->setReadOnly(true);
                lineAnnui->setEnabled(false);
                lineAnnui->setStyleSheet(grayStyle);
            }
	if (i==3 || i==4)
		dFactor->setEnabled(true);
	else
		dFactor->setEnabled(false);
	
	if (!doNotCheck){
// 		qDebug()<<"LOAD setMonthlyProfile notcheck..."<<doNotCheck;
		updateMonths();
		if (tableMonthly->currentItem())
                        updateHours(tableMonthly->currentItem(),user_);
		else{
			tableMonthly->setCurrentCell(0,0);
                        updateHours(tableMonthly->currentItem(),user_);
		}

	}
	
}
 
 void Load::setHourlyProfile(int i)
/* Called when the comboHourly changes */
{

	QList<QTableWidgetSelectionRange> sel;	
	sel = tableMonthly->selectedRanges();
// 	int m = tableMonthly->currentColumn(); // current month

	for(int k=0;k<sel.size();k++){
		for(int m=sel.at(k).leftColumn();m<=sel.at(k).rightColumn();m++){
			if (i>0 && i<=5)
					hourlyProfile.replace(m,i);
			else
					hourlyProfile.replace(m,Uniform);

                        //quotaSat[m] = dQuotaSabato->value();
                        //quotaSun[m] = dQuotaDomenica->value();
                         restDay[m]  = getClosingDay();
                        equalSat.replace(m,checkNormSat->isChecked());
                        equalSun.replace(m,checkNormSun->isChecked());
                         if (!equalSat.at(m))
                             quotaSat[m] = dQuotaSabato->value();
                         if (!equalSun.at(m))
                             quotaSun[m] = dQuotaDomenica->value();

                        if (equalSat.at(m) || equalSun.at(m))
                            updateQuotas(m,year);

                        updateHours(tableMonthly->item(0,m),default_);
		}
	}
/*	if (tableMonthly->currentItem())
			updateHours(tableMonthly->currentItem());
		else{
			tableMonthly->setCurrentCell(0,0);
			updateHours(tableMonthly->currentItem());
		}*/
//   	updateHours();
        pushApply->setEnabled(true);
}
void Load::setDefault()
/* Uniform distribution and zero values. Initialization of Headers */
{
        int  startMonth,startDay,kk;
	QStringList he(monthsList);
	he<<"Totale";
	startMonth = 1;
	startDay   =1;
	kk=0;
	QString a;
	QStringList l,l2;
	l<<"kWh"<<"%";
	l2<<"%"<<"kWh";
	//Header of Months
	tableMonthly->setHorizontalHeaderLabels(he);
	tableMonthly->setVerticalHeaderLabels(l);
	

	
	

	
	 
	
 	for(int mm=1;mm<=12;mm++) {
		
		QTableWidgetItem *item = new QTableWidgetItem;
		QTableWidgetItem *itemPercent = new QTableWidgetItem;
		
		item->setText( QString::number(0000.00));
		
		itemPercent->setText(QString::number(00.00));
		item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		itemPercent->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		tableMonthly->setItem(0,mm-1,item);
		tableMonthly->setItem(1,mm-1,itemPercent);
		/* Take care of February forever*/
// 		if (mm==2)
// 			endMonth = 29;
// 		else
// 			endMonth = MyMath::monthEnd(mm,year);
		 
		mLoadValue<<0.0;
		gNormLoad<< 0.0;
		gSunLoad << 0.0;
		gSatLoad << 0.0;	
                quotaSat << 0.0;
                quotaSun << 0.0;
                ML       << 0.0;
                equalSat<<true;
                equalSun<<false;
		
		restDay  << getClosingDay();
		hourlyProfile<< Uniform; //default value
			for(int h=0;h<24;h++)
			{
				 
					QTableWidgetItem *itemH = new QTableWidgetItem;
					QTableWidgetItem *itemHPercent = new QTableWidgetItem;
					itemH->setText(QString::number(00000.00));
					itemH->setFlags(Qt::ItemIsSelectable);
					itemHPercent->setText(QString::number(00.00));
					itemPercent->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable);
					tableHourly->setItem(h,1,itemH);
					tableHourly->setItem(h,0,itemHPercent);
				 
				hLoad<< 0.0;
                                hLoadPercent<< 100.0/24;//default Uniform
				loadValue<< 0.0;
				kk++;
			}
		 
	}	
	//ADD the total
	QTableWidgetItem *item = new QTableWidgetItem;
	QTableWidgetItem *itemPercent = new QTableWidgetItem;
	item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	itemPercent->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	item->setText( QString("%L1").arg(00));
	itemPercent->setText( QString("%L1").arg(00));
	tableMonthly->setItem(0,12,item);
	tableMonthly->setItem(1,12,itemPercent);

	tableMonthly->resizeColumnsToContents();
	
	tableHourly->resizeColumnsToContents();
	tableHourly->horizontalHeader()->setStretchLastSection(true);
	tableHourly->setHorizontalHeaderLabels(l2);
}
void Load::saveProfile()
{
}
void Load::montlhyChanged()
{
}
 
void Load::hourlyChanged()
{
}
void Load::setYear(int i)
{
	year = i;
}
Load::~Load()
{
}
void Load::alignScales()
{
    // The code below shows how to align the scales to
    // the canvas frame, but is also a good example demonstrating
    // why the spreaded API needs polishing.

    
    qwtHourly->canvas()->setFrameStyle(QFrame::Box | QFrame::Plain );
    qwtHourly->canvas()->setLineWidth(1);

    qwtMonthly->canvas()->setFrameStyle(QFrame::Box | QFrame::Plain );
    qwtMonthly->canvas()->setLineWidth(1);
   
    qwtWeekly->canvas()->setFrameStyle(QFrame::Box | QFrame::Plain );
    qwtWeekly->canvas()->setLineWidth(1);

    for ( int i = 0; i < qwtHourly->QwtPlot::axisCnt; i++ )
    {
        QwtScaleWidget *scaleWidget = (QwtScaleWidget *)(qwtHourly->axisWidget(i));
        if ( scaleWidget )
            scaleWidget->setMargin(0);

        QwtScaleDraw *scaleDraw = (QwtScaleDraw *)qwtHourly->axisScaleDraw(i);
        if ( scaleDraw )
            scaleDraw->enableComponent(QwtAbstractScaleDraw::Backbone, false);
    }
for ( int i = 0; i < qwtMonthly->QwtPlot::axisCnt; i++ )
    {
        QwtScaleWidget *scaleWidget = (QwtScaleWidget *)(qwtMonthly->axisWidget(i));
        if ( scaleWidget )
            scaleWidget->setMargin(0);

        QwtScaleDraw *scaleDraw = (QwtScaleDraw *)qwtMonthly->axisScaleDraw(i);
        if ( scaleDraw )
            scaleDraw->enableComponent(QwtAbstractScaleDraw::Backbone, false);
    } 
for ( int i = 0; i < qwtWeekly->QwtPlot::axisCnt; i++ )
    {
        QwtScaleWidget *scaleWidget = (QwtScaleWidget *)(qwtWeekly->axisWidget(i));
        if ( scaleWidget )
            scaleWidget->setMargin(0);

        QwtScaleDraw *scaleDraw = (QwtScaleDraw *)qwtWeekly->axisScaleDraw(i);
        if ( scaleDraw )
            scaleDraw->enableComponent(QwtAbstractScaleDraw::Backbone, false);
    }
}
void Load::saveState()
{
    //Save current quotas //
    quotaSatB = QVector<double>(quotaSat);
    quotaSunB = QVector<double>(quotaSun);
    if (monthlyProfile == Uniform){
        for(int m=0; m < 12; m++){
        mLoadValue[m-1] = yearlyLoad * getYearlyLoadPercent(year,m-1);
        ML[m-1] = mLoadValue[m-1];
    }
    }
}
void Load::reloadSavedState()
{

    //Reload current quotas //
    QVector<double> res;
    quotaSat = QVector<double>(quotaSatB);
    quotaSun = QVector<double>(quotaSunB);
    for(int m=0; m < 12; m++){
        if (monthlyProfile == Uniform)
            mLoadValue[m-1] = ML[m-1];

        updateQuotas(m,year);
        res = getMonthlyLoad(m,year);
        gNormLoad[m ] = res.at(0);
        gSatLoad[m  ] = res.at(1);/*The same profile as in normal days */
        gSunLoad[m  ] = res.at(2);/*The same profile as in normal days */
    }
}

double Load::getHourlyLoad(int y,int hour,int day, int month)
/* Values are only for typical days of every month */
/* month are counted from 1 to 12 */
/* hour between 0 and 23*/
{
             //   int currentMonth = tableMonthly->currentIndex().column();
                double dailyValue,satValue,sunValue,tempML;
		QDate da(y,month,day); 
		int d = da.dayOfWeek();
                tempML = 0;
                QVector<double> res;


	if ((month>0 && month<13) && (hour>=0 && hour<24) )	
		{
//            // Save the current month load //
//
//            if (monthlyProfile == Uniform){
//                mLoadValue[month-1] = yearlyLoad * getYearlyLoadPercent(y,month-1);
//                tempML = mLoadValue[month-1];
//            }
//            //Save current quotas //
//            quotaSatB = QVector<double>(quotaSat);
//            quotaSunB = QVector<double>(quotaSun);
            
           updateQuotas(month-1,y); //We must recompute the quotas for every year (?)
                res = getMonthlyLoad(month-1,y);
		dailyValue = res.at(0);/*The daily value for normal days */
 		satValue   = res.at(1);/*The same profile as in normal days */
 		sunValue   = res.at(2);/*The same profile as in normal days */
	 
	
//		if (d==restDay[month])
//			return 0;
	
		switch (d  )
		{	
			case (6):
				return  satValue *hLoadPercent[hour+24*(month-1)]/100; 
			break;
			case (7):
				return  sunValue *hLoadPercent[hour+24*(month-1)]/100; 
			break;
			default:
			 	return  dailyValue *hLoadPercent[hour+24*(month-1)]/100; 
			break;
		}
		

		
	}
        else{
                qDebug()<<"ERROR IN LOAD GETHOURYLOAD";
		return -1;

            }
}
QPolygonF Load::getHourlyLoads(int y,int day, int month)
/* Values are only for typical days of every month */
/* month are counted from 1 to 12 */
/* hour between 0 and 23*/
{

                double dailyValue,satValue,sunValue,tempML;
		QDate da(y,month,day); 
		int d = da.dayOfWeek();
double value;
QPolygonF out;
	if ((month>0 && month<13) ){

            // Save the current month load //

            if (monthlyProfile == Uniform){
                mLoadValue[month-1] = yearlyLoad * getYearlyLoadPercent(y,month-1);
                tempML = mLoadValue[month-1];
            }

               updateQuotas(month-1,y); //We must recompute the quotas for every year (?)
		// Default: load are computed for non leap years. Therefore, adjust if it is necessary
               QVector<double> res = getMonthlyLoad(month-1,y);
               dailyValue = res.at(0);/*The daily value for normal days */
               satValue   = res.at(1);/*The same profile as in normal days */
               sunValue   = res.at(2);/*The same profile as in normal days */

	for(int hour=0;hour<24;hour++) {
 

	 
	
//		if (d==restDay[month])
//			return QPolygonF();
	
		switch (d )
		{	
			case (6):
				
				value =  satValue *hLoadPercent[hour+24*(month-1)]/100; 
                             //  qDebug()<<"GETHOURLYLOADS---------6---value="<<value<<day<<d<<month<<y;
			break;
			case (7):
				value =  sunValue *hLoadPercent[hour+24*(month-1)]/100; 
                             //   qDebug()<<"GETHOURLYLOADS---------7---value="<<value<<day<<d<<month<<y;
			break;
			default:
			 	value =  dailyValue *hLoadPercent[hour+24*(month-1)]/100; 
                              //  qDebug()<<"GETHOURLYLOADS---------0-5---value="<<dailyValue<<hLoadPercent[hour+24*(month-1)]<<day<<d<<month<<y;
			break;
		}


          if (monthlyProfile == Uniform)
                 mLoadValue[month-1] = tempML;
	out<<QPointF(hour,value);
	}
	}
	else
		out = QPolygonF();
	return out;
}
void Load::save()
{
// 	Ask a;
// 	if (!doNotAskAgain) {
// 		if (a.exec()) {
// 		
// 			onlyCurrentMonth = a.onlyCurrentMonth();
// 			doNotAskAgain = a.doNotAskAgain();
// 			
// 		}
// 	}

	if (fileCustom.isEmpty())
		saveAs();
	else
		saveCustom(fileCustom);

        if (!fileCustom.isEmpty())
            this->setWindowModified(false);
        qDebug()<<"LOAD Filecustom"<<fileCustom;
        doNotModifyWin=true;
        updateTitle();
        doNotModifyWin=true;

}
void Load::saveAs()
{
		
        onlyCurrentMonth = checkCurrentMonths->isChecked();
	
        QString fileName;
        fileName = QFileDialog::getSaveFileName(this, tr("Salva consumi"), recentSave, tr(" (*.txt)"));
	if (!fileName.isEmpty()){
		fileCustom = fileName;
                saveCustom(fileCustom);
                doNotModifyWin=true;
                updateTitle();
                doNotModifyWin=false;
	}
}
void Load::saveCustom(  QString &fileName)
{
	int e;
	fileName = MyMath::checkFormat(fileName,"txt");
	QFile file(fileName);
	if (!fileName.isEmpty() && file.open(QFile::WriteOnly) ) {
		
		
		fileCustom = fileName;
		QFileInfo fileInfo(fileName);
		recentSave = fileInfo.absoluteDir().absolutePath();
		
		QTextStream out(&file);
             //   qDebug()<<"LOAD salvo file"<<fileName<<file.fileName();
	if (onlyCurrentMonth)
		 e = 1;
	else
		e = 12;
	
		out<<"Monthly"<<"="<<monthlyProfile<<"\n";
		out<<"Factor"<<"="<<dFactor->value()<<"\n";
		out<<"Profiles"<<"\n";
		for(int m=0;m<12;m++)
                        out<<mLoadValue[m]<<"\t"<<quotaSat[m]<<"\t"<<quotaSun[m]<<"\t"<<hourlyProfile[m]<<"\t"<<restDay[m]<<"\t"<<equalSat.at(m)<<"\t"<<equalSun.at(m)<<"\n";
		out<<"Hourly percents"<<"\n";
		for(int i=0;i<e;i++)
			for(int k=0;k<24;k++)
				out<<i*24 + k<<"\t"<<hLoad.at(i*24+k)<<"\t"<<hLoadPercent.at(i*24+k)<<"\n";
		
		
	}
	else
	{
        qDebug()<<"LOAD salvo file"<<fileName<<file.fileName();
        QMessageBox::warning(this,tr("Carichi elettrici"),tr("<p>Errore di scrittura nella cartella selezionata.<br>")+recentSave+"</p>",QMessageBox::Ok);
	}
}
void Load::load()
{

	if (loadCustom(""))
		{
		doNotCheck = true;
		doNotCheckHours = true;

                doNotModifyWin=true;
                lineAnnui->setText(QString::number(MyMath::cumSum(mLoadValue)));
                doNotModifyWin=false;
		comboMonthly->setCurrentIndex(monthlyProfile);

                doNotCheck = false;
  		doNotCheckHours = false;
//  
 		
 
  		update();
                this->setWindowModified(false);
		
		}
		
		
}
void Load::load(const QString &input)
{
    /* Used to load data from a file externally set  */
    if (loadCustom(input))
    {
        doNotCheck = true;
        doNotCheckHours = true;

        doNotModifyWin=true;
        lineAnnui->setText(QString::number(MyMath::cumSum(mLoadValue)));
        doNotModifyWin=false;
        comboMonthly->setCurrentIndex(monthlyProfile);

        doNotCheck = false;
        doNotCheckHours = false;
//





    }
    else
    {
        /* The file does not exist or there are errors */
        fileCustom = "";

    }
    update();
    setWindowModified(false);
}

bool Load::loadCustom(const QString &input)
{
	QString s,fileName;
        int count,countProfile,test,error;
	QVector<double> temp,temp2;
	bool startReadProfile,startReadHourly;
	startReadProfile = false;
	startReadHourly= false;
	QStringList splitted;
	if (input.isEmpty())
                 fileName = QFileDialog::getOpenFileName(this, tr("File consumi"), recentDirCarichi, "Text files (*.txt)");
	else
		fileName = input;

	
	QFile file(fileName);
	if (!fileName.isEmpty() &&  file.open(QFile::ReadOnly)) {
  		recentDirCarichi = QFileInfo(fileName).absoluteDir().absolutePath();
		QTextStream in(&file);
                count =countProfile=test=error=0;
		 while (!in.atEnd()) {
 			s = in.readLine();
			s = s.simplified();
			splitted = s.split("=");
  			
			if ((splitted.size()==2) && (splitted.at(0)=="Monthly") ){
                                //qDebug()<<"LOAD READ MONTHLY ="<<splitted.at(1);
                                monthlyProfile = (splitted.at(1).toInt());
				test++;
				continue;
			}
			if ((splitted.size()==2) && (splitted.at(0).simplified()=="Factor") ){
                                dFactor->setValue((splitted.at(1).toDouble()));
                                //qDebug()<<"LOAD READ FActor ="<<splitted.at(1);
				test++;
				continue;
			}
			if (s=="Profiles"){
                                //qDebug()<<"LOAD READ STARTPROFILE ="<<s;
				startReadProfile = true;
				mLoadValue.resize(0);
				hourlyProfile.resize(0);
				quotaSat.resize(0);
				quotaSun.resize(0);
                                restDay.resize(0);
                                equalSat.resize(0);
                                equalSun.resize(0);

				countProfile =1;
				test++;
				continue;
				}
// 			
// 	
			if (startReadProfile) {	

				splitted = s.split(" ");
                                if (splitted.size()>5){

                                mLoadValue<<(splitted.at(0).toDouble());
                                quotaSat<< (splitted.at(1).toDouble());
                                quotaSun<< (splitted.at(2).toDouble());
                                hourlyProfile << (splitted.at(3).toInt());
                                restDay<<(splitted.at(4).toInt());
                                qDebug()<<"LOAD READ mLoad ="<<mLoadValue;
                                if (splitted.at(5).toInt()==1)
                                    equalSat<<true;
                                else
                                    equalSat<<false;
                                if (splitted.at(6).toInt()==1)
                                    equalSun<<true;
                                else
                                    equalSun<<false;

                            }else
                                error=10;

				
				if (countProfile>=12){
					startReadProfile = false;
					test++;
				}
				countProfile++;
				
				continue;
			}
			
// 			qDebug()<<"LOAD READ"<<s;
			if (s=="Hourly percents"){
				startReadHourly=true;	
				test++;
				continue;
			}

			if (startReadHourly){

				splitted = s.split(" ");
                                temp << splitted.at(1).toDouble();
                                temp2<< splitted.at(2).toDouble();
// 			mPrezziEnergia[count] = s.toDouble();

   				count++;
  			}
	
		}
	
                 if (error==10 ){
                     QMessageBox::critical(this,tr("Errore 10"),tr("Errore nei profili orari. File corrotto o dati mancanti."),QMessageBox::Ok);

                     return false;
                 }

		if ((count!=288) || (test!=5)){
			QMessageBox::critical(this,tr("Caricamento carichi elettrici"),tr("Troppi pochi dati.Ricontrolla il contenuto del file"),QMessageBox::Ok);
			 
			return false;
		}
		else
			{
			
  			fileCustom = fileName;
    	
  			hLoad.resize(0);
			hLoadPercent.resize(0);
  			hLoad = temp;
			hLoadPercent= temp2;

			return true;
			}
	}
	else
		return false;
}
QString Load::getFileCustom()
{
	return fileCustom;
}
void Load::setFileCustom(const QString& g)
{
	fileCustom = g;
        load(fileCustom);
}
void Load::notify()
{
	emit updated();
        pushApply->setEnabled(false);

}

int Load::getClosingDay()
/*restDay must be between 0 and 6*/
{
        if (comboChiusura!=0)
		if (comboChiusura->currentIndex()==0)
			return 7;
		if (comboChiusura->currentIndex()==1)
			return 6;
		if (comboChiusura->currentIndex()>1)
			return comboChiusura->currentIndex()-2;
}
//void Load::createActions()
//{
//
//    a_copia_profile = new QAction(this,tr("Ricopia profilo"))
//    a_copia_profile->setToolTip(tr("<p>Ricopia il profilo oraro del primo elemento della selezione sui restanti</p>"));
//    connect(a_copia_profile,SIGNAL(triggered()),SLOT())
//}
//
void Load::popMenuHours( )
{

            QMenu menu;
            menu.addAction(a_clear_hours);
            menu.addAction(a_copy_hours);
            menu.exec(QCursor::pos());


}
void Load::popMenu()
{

            QMenu menu;
            menu.addAction(a_clear);
            menu.addAction(a_copy);
            menu.exec(QCursor::pos());


}
void Load::createActions()
{
        a_clear = new QAction(tr("Azzera"),this);
        a_clear->setToolTip(tr("Azzera tutte le celle selezionate"));
        connect(a_clear,SIGNAL(triggered()),SLOT(clearSelected()));

        a_copy = new QAction(tr("Copia"),this);
        a_copy->setToolTip(tr("Copia il primo valore della selezione su tutte le celle selezionate"));
        connect(a_copy,SIGNAL(triggered()),SLOT(uniformize()));

        a_clear_hours = new QAction(tr("Azzera"),this);
        a_clear_hours->setToolTip(tr("Azzera tutte le celle selezionate"));
        connect(a_clear_hours,SIGNAL(triggered()),SLOT(clearSelectedHours()));

        a_copy_hours = new QAction(tr("Copia"),this);
        a_copy_hours->setToolTip(tr("Copia il primo valore della selezione su tutte le celle selezionate"));
        connect(a_copy_hours,SIGNAL(triggered()),SLOT(uniformizeHours()));
    }
void Load::uniformize()
{
     doNotCheckHours = true;
     QVector<int> indici;
    QList<QTableWidgetSelectionRange> sel = tableMonthly->selectedRanges();

     double value= tableMonthly->item(0,sel.at(0).leftColumn())->data(0).toDouble();

    for(int k=0;k<sel.size();k++){
            for(int m=sel.at(k).leftColumn();m<=sel.at(k).rightColumn();m++){

                   mLoadValue.replace(m,value);

                    indici<<m;
                    tableMonthly->item(0,m)->setText(QString("%L1").arg(value));
            }

}
    doNotCheckHours = false;

    for(int i= 0;i<indici.size();i++){

        checkData(tableMonthly->item(0,indici.at(i)));
    }
pushApply->setEnabled(true);
}
void Load::uniformizeHours()
{

   QVector<int> indici;
   QList<QTableWidgetSelectionRange> sel = tableHourly->selectedRanges();
   double value= tableHourly->item(sel.at(0).topRow(),0)->data(0).toDouble();
   doNotCheckHours = true;
   for(int k=0;k<sel.size();k++){
           for(int m=sel.at(k).topRow();m<=sel.at(k).bottomRow();m++){
                   indici<<m;
                   tableHourly->item(m,0)->setText(QString("%L1").arg(value));

           }

}
   doNotCheckHours = false;
   for(int i= 0;i<indici.size();i++){

       checkHourlyData(tableHourly->item(indici.at(i),0));
   }
   pushApply->setEnabled(true);
}

void Load::clearSelected()
{
        QList<QTableWidgetSelectionRange> sel = tableMonthly->selectedRanges();


       doNotCheckHours = true;



        for(int k=0;k<sel.size();k++){
                for(int m=sel.at(k).leftColumn();m<=sel.at(k).rightColumn();m++){
                        mLoadValue.replace(m,0);

                        tableMonthly->item(0,m)->setText(QString::number(0));
                }

}
        doNotCheckHours = false;
        updateHours(tableMonthly->currentItem(),user_);
pushApply->setEnabled(true);
}
void Load::clearSelectedHours()
{
        QList<QTableWidgetSelectionRange> sel = tableHourly->selectedRanges();


       doNotCheckHours = true;

        QVector<int> indici;

        for(int k=0;k<sel.size();k++){
                for(int m=sel.at(k).topRow();m<=sel.at(k).bottomRow();m++){
                         tableHourly->item(m,0)->setText(QString::number(0));
                         indici<<m;
                }

}
        doNotCheckHours = false;
        for(int i= 0;i<indici.size();i++){

            checkHourlyData(tableHourly->item(indici.at(i),0));
        }
        pushApply->setEnabled(true);
}
void Load::updateTitle()
{

    if (!doNotModifyWin)
     this->setWindowModified(true);

    if (!fileCustom.isEmpty() && !fileCustom.isNull())
        setWindowTitle(tr("Consumi elettrici") + " - " + QFileInfo(fileCustom).absoluteFilePath() + "[*]");
    else
        setWindowTitle(tr("Consumi elettrici") + " - " + tr("Nessun nome") + "[*]"  );



}
void Load::setSatNormOption(int state)
{



    if (!doNotUpdate){
        doNotUpdate = true;
      qDebug()<<"LOAD setSat"<<state;
        int m = tableMonthly->currentColumn();
       // restDay[m] = getClosingDay();
        if (m<12 && m >=0){


            if (state==Qt::Checked)
            {
                equalSat.replace(m,true);
                checkNormSat->setChecked(true);
                dQuotaSabato->setEnabled(false);
            }
            else{
                equalSat.replace(m,false);
                checkNormSat->setChecked(false);
                dQuotaSabato->setEnabled(true);
            }
            updateQuotas(m,year);
            //updateHoursProfileDetails(m);
            updateHours(tableMonthly->currentItem(),user_);

        }
        doNotUpdate = false;
}
}
void Load::setSunNormOption(int state)
{
    if (!doNotUpdate){
      //  qDebug()<<"LOAD setSun"<<state;
        int m = tableMonthly->currentColumn();
        if (m<12 && m >=0){
            if (state==Qt::Checked){
                equalSun.replace(m,true);
                dQuotaDomenica->setEnabled(false);
            }
            else{
                equalSun.replace(m,false);
                dQuotaDomenica->setEnabled(true);
            }
            updateQuotas(m,year);
            //updateHoursProfileDetails(m);
            updateHours(tableMonthly->currentItem(),user_);

        }
}
}

void Load::updateQuotas(int month,int y)
{
    QVector<int> numOfWeeksAndRestDays;
     int numOfDays;

     if (month>=0 && month<12) {
         numOfWeeksAndRestDays = restDay[month]==7 ?
                                 MyMath::numOfWeekendsAndRests(QDate(y,month+1,1),0):
                                 MyMath::numOfWeekendsAndRests(QDate(y,month+1,1),restDay[month]+1);

         numOfDays = QDate(y,month+1,1).daysInMonth();

       // qDebug()<<"LOAD updateQuotas-----------"<<month<<numOfWeeksAndRestDays<<restDay[month];
         if (restDay[month] == 7){
             // No rest day
             if (equalSat.at(month)){
                 quotaSat[month] = 100.0 * numOfWeeksAndRestDays.at(0)/numOfDays;
                // qDebug()<<"PIPPO"<<numOfWeeksAndRestDays.at(0)<<numOfDays<<y ;
             }
             else
                 quotaSat[month] = dQuotaSabato->value();
       // qDebug()<<"A REST DAY, equalSat, equalSun"<<restDay[month]<<equalSat.at(month)<<equalSun.at(month)<<quotaSat[month];
         }
         else
         {
             if (equalSun.at(month) && equalSat.at(month)){
                   //Normalize all days
                     quotaSat[month] = 100.0 * (numOfWeeksAndRestDays.at(0))/numOfDays;
                     quotaSun[month] = 100.0 * (numOfWeeksAndRestDays.at(2))/numOfDays;
                     //qDebug()<<"B REST DAY, equalSat, equalSun"<<restDay[month]<<equalSat.at(month)<<equalSun.at(month)<<quotaSat[month];
             }
             if (!equalSun.at(month) && equalSat.at(month)){
                 quotaSun[month] = dQuotaDomenica->value();
                      quotaSat[month] = 100.0* (1-quotaSun[month]/100)*(numOfWeeksAndRestDays.at(0))/(numOfDays-numOfWeeksAndRestDays.at(2));

                //   qDebug()<<"C REST DAY, equalSat, equalSun"<<restDay[month]<<equalSat.at(month)<<equalSun.at(month)<<quotaSat[month]<<quotaSun[month];
              }
             if (!equalSun.at(month) && !equalSat.at(month)){
                    quotaSun[month] = dQuotaDomenica->value();
                    quotaSat[month] = dQuotaSabato->value();
                   // qDebug()<<"D REST DAY, equalSat, equalSun"<<restDay[month]<<equalSat.at(month)<<equalSun.at(month)<<quotaSat[month];
             }
             if (equalSun.at(month) && !equalSat.at(month)){
                    quotaSat[month] = dQuotaSabato->value();
                    quotaSun[month] = 100.0 * (1-quotaSat[month]/100)*
                                      numOfWeeksAndRestDays.at(2)/
                                      (numOfDays - numOfWeeksAndRestDays.at(0));
                    //qDebug()<<"E REST DAY, equalSat, equalSun"<<restDay[month]<<equalSat.at(month)<<equalSun.at(month)<<quotaSun[month]<<numOfWeeksAndRestDays.at(2)<<numOfWeeksAndRestDays.at(0)<<numOfDays;
             }
         }


      }
}
bool Load::loadInserted()
{
    if (MyMath::cumSum(mLoadValue)>0.000002)
        return true;
    else
        return false;

}
double Load::getYearlyTotal()
{
    return yearlyLoad;
}

int Load::getYearProfile()
{
    return monthlyProfile;
}
