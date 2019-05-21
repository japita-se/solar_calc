#include "mymath.h"
#include "outreport.h"
#include "qwt_plot.h"
#include "myplot.h"
#include <QTextDocument>
#include <QtGui>
 #include <QTextTableFormat>
#include <QPointF>
#include <QPolygonF>
#include <QFileInfo>

static inline double mmToInches(double mm) { return mm * 0.039370147; }

OutReport::OutReport(QWidget* parent): m_document(new QTextDocument()),
        m_cursor(m_document), printer_(new QPrinter ),QWidget(parent)

{
        leftmargin_ =  20;
        rightmargin_ = 20;
        topmargin_ = 100;
        bottommargin_ = 10;
	version = "";
        recentDir = QDir::homePath();

        profile << tr("Uniforme")<<
                tr("Prevalenza Estate")<<tr("Prevalenza Inverno")<<
                tr("Stagionale Inverno")<<
                tr("Stagionale Estate")<<
                tr("Personalizzato")<<
                tr("Commercial")<<
                tr("Industriale");
	 
      //  m_document->setDefaultStyleSheet(cssTable());
        m_document->setDefaultFont(QFont("Arial",9));
	models <<QObject::tr("UNI 8477 ")<<QObject::tr("ENEA")<<QObject::tr("Erbs");
	types  <<QObject::tr("Tilt Fisso")<<QObject::tr("Inseguitore Biassiale")<<QObject::tr("Doppia falda");
	sources<<QObject::tr("ENEA SolarEnergy")<<QObject::tr("Custom")<<QObject::tr("PVGIS")<<QObject::tr("NASA SSE");
	mounting<<QObject::tr("Su guida")<<QObject::tr("BIPV")<<QObject::tr("Schiera e/o palo");
        regime << QObject::tr("Vendita") << QObject::tr("SSP Italia") << QObject::tr("Semplice Scambio");
	Hset = false;
	Eset = false;
	ecoIsPresent = false;
	totEnergy=0;
        numPanels = 0;
        numPanels2 = 0;
	opt.otherLoss.fill(0,12);
	opt.temperatures.fill(0,12);
	opt.wind.fill(0,12);
	opt.thermalLosses.fill(1,12);
	opt.shadows.fill(1,12);
	
	opt.totalLossTemp = 0;
	inv.isValid=false;
        inv.model = tr("Non specificato");
	summaryTable="";
        summaryTax  ="";
	systemDetails.campiVector.fill(0,1);
	
	
	 
}

OutReport::~OutReport()
{
delete m_document;
}
 void OutReport::addSolarDiagram( MyPlot * p)
 {
 	solarDiagram  = p;
 	
 }


 void OutReport::addSolarRadiation(const QwtPlot * p)
 {
 	solarRadiation  = p;
 	
 }
void OutReport::addSolarRadiation2(const QwtPlot * p)
 {
 	solarRadiation2  = p;
 	
 }
 void OutReport::addEEnergy(const QwtPlot * p)
 {
 	eEnergy  = p;
 	
 }
void OutReport::addVanDiagram(const QwtPlot* p)
{
	vanDiagram = p;
}
void OutReport::addRawDiagram(const QwtPlot* p)
{
	rawDiagram = p;
}

void OutReport::addTotEnergy(double a)
{
	totEnergy = a;
}
void OutReport::addLocation(loc l)
{
	localita = l;
// 	qDebug()<<l.radCorrModel;
}
//int OutReport::numPanels()
//{
//	int numPanels=0;;
//	if (localita.area != 0){
//		if ((pan.H*pan.L)>0)
//			numPanels = ceil(localita.area/(0.001*0.001*pan.H*pan.L));
//		else
//			if (pan.eff>0 & pan.eff<100)
//
//			numPanels = ceil(localita.area*pan.eff/pan.pnom);
//			else
//			numPanels = -1;
//
//	}
//        return numPanels;
//}
void OutReport::setNumPanels(int n1,int n2)
{
    numPanels = n1;
    numPanels2= n2;
}

void OutReport::addPanel(panel p)
{
	pan = p;
	
}
void OutReport::addEnergy(const double* e)
{
	if (e!=NULL){
	E = e;
	Eset = true;
	}
}
void OutReport::addRad(const double* rad)
{
	if (rad!=NULL){
	H = rad;
	Hset = true;
	}
}
void OutReport::addInverter(inverter i)
	
{
	inv = i;
        if (inv.isValid==0 || inv.model.isEmpty())
            inv.model=tr("Non specificato");
        qDebug()<<"ADDED INVERTE"<<inv.model<<inv.isValid;
}
void OutReport::addOption(option o)
	
{
	opt = o;
	if (opt.wind.isEmpty())
		opt.wind.fill(0,12);
	if (opt.temperatures.isEmpty())
		opt.temperatures.fill(0,12);
	

		
}
void OutReport::addUnitRad(const QString &s)
{
	unit = s;
}
void OutReport::addUnitEnergy(const QString &s)
{
	unitEnergy = s;
}
QString OutReport::getDir()
{
	return recentDir;
}
void OutReport::setDir(const QString& s)
{
	recentDir = s;
}
void OutReport::printGeneral(QPrinter *printer)
{
    QPrintDialog printDialog(printer);
    if (printDialog.exec()){
        print(printer,3,QPrinter::NativeFormat);
}
}
QString OutReport::cssTable()
{
    QString a;
    a = "<style type=\"text/css\">\n"
                    ".bc1 {"
                            "border-top: 1px solid ;"
                            "border-collapse: collapse;"
                            "table-layout: fixed;"
                            "width:100%;"
                            " word-wrap:break-word;"

                            "}"
                    ".bc1 th, .bc1 td{"
                            "padding: 2px;"
                            "border-top: 1px solid ;"
                            "border-left: 1px solid ;"
                            "border-right: 1px solid ;"
                            "border-bottom: 1px solid ;"

                            "}"
                    ".bc1 th{"
                            "padding: 20px;"
                            "background: #b4a8f3;"
                            "color: #a40;"
                            "}"
                     "</style>";
    return a;
}

QString OutReport::makeTable()
{
    QString s,site,model,coll,medie,totale,sistema;
    QString lat = (QString("%L1").arg(localita.latGradi) + "<sup>o</sup> " +
                            QString("%L1").arg(localita.latMin)+ "' "
                           +QString("%L1").arg(localita.latSec)+"''");
    QString lon =(QString("%L1").arg(localita.lonGradi) +  "<sup>o</sup> " +
                           QString("%L1").arg(localita.lonMin)+  "' " +
                           QString("%L1").arg(localita.lonSec)+"''");

    QStringList projectPath = localita.projectName.split("/");
    QString projectName = projectPath.last();
    QString details = QDate::currentDate().toString() + ", " + QTime::currentTime().toString() + " - ProjectName: " + projectName;
    s += " <!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\"         \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\"><html xmlns=\"http://www.w3.org/1999/xhtml\" lang=\"en\" xml:lang=\"en\"><body><h1>SolarCalc "+ version+ " - report </h1> ";
    s += " <h5>" + details + "</h5>";

    /***************SITE**********************************/
    site =" <table  width=680 border=\"0\"><tbody><tr  bgcolor=\"lightGray\" ><td colspan=\"3\" >"
          +        QObject::tr("Sito") +"</td></tr>";
    site += "<tr><td>" + QObject::tr("Comune") +        "</td>";
    site += "<td>" + localita.name +                    "</td><td></td></tr>";
    site += "<tr><td>" +   QObject::tr("Latitudine") +  "</td>";
    site += "<td>"     +   QString("%L1").arg(localita.lat) +"</td>";
    site += "<td>"     +   lat +"</td></tr>";
    site += "<tr><td>" +   QObject::tr("Longitudine") +  "</td>";
    site += "<td>"     +   QString("%L1").arg(localita.lon) +"</td>";
    site += "<td>"     +   lon +"</td></tr>";
    site += "<tr><td>" +   QObject::tr("Albedo") +        "</td>";
    site += "<td>"     +   QString("%L1").arg(localita.albedo) +"</td><td></td></tr>";
    site += "<tr><td>" +   QObject::tr("Vel. vento media annuale")+         "</td>";
    site += "<td>"     +   QString("%L1").arg(MyMath::mean(opt.wind)) + " m/s</td><td></td></tr>";
    site += "</tbody></table>";

    /*************** MODELLO **********************************/
    model+=" <table  width=\"680\" border=\"0\"><tbody><tr bgcolor=\"lightGray\" ><td colspan=\"3\" >" +        QObject::tr("Modello radiazione") +"</td></tr>";
    model += "<tr><td>" + QObject::tr("Modello diffusa/diretta") +        "</td>";
    model += "<td>" + models.at(localita.radCorrModel-1) +  "</td><td></td></tr>";
    model += "<tr><td>" + QObject::tr("Calcolo ombre")   + "</td>";
    model += "<td>" + QObject::tr("Integrazione diretta")   + "</td><td></td></tr>";
    model += "<tr><td>" +QObject::tr("Sorgente") + "</td>";
    model += "<td>"     + sources.at(localita.source) + "</td><td></td></tr>";
    model += "</tbody></table>";

//qDebug()<<"OO"<<site + model;
    /*************** COLLETTORE **********************************/
    coll = " <table   width=\"680\" border=\"0\"><tbody><tr bgcolor=\"lightGray\" ><td colspan=\"3\"  >"+        QObject::tr("Collettore") +"</td></tr>";
    coll += "<tr><td>" + QObject::tr("Tilt") +        "</td>";

    if (localita.additionalIncl.size()>0)
            coll += "<td>" + QString("%L1").arg(localita.incl)+ "<sup>o</sup>" + "/" +
                    QString("%L1").arg(localita.additionalIncl.at(0)) +
                    "<sup>o</sup></td><td></td></tr>";
    else
            coll += "<td>" + QString("%L1").arg(localita.incl)+
                    "<sup>o</sup></td><td></td></tr>";

    coll += "<tr><td>" + QObject::tr("Azimuth") +        "</td><td>";
    if (localita.additionalAzi.size()>0)
             coll += QString("%L1").arg(localita.azi)+ "<sup>o</sup>" + "/" + QString("%L1").arg(localita.additionalAzi.at(0)) + "<sup>o</sup></td><td></td></tr>";
    else
             coll +=QString("%L1").arg(localita.azi)+ "<sup>o</sup></td><td></td></tr>";

    coll += "<tr><td>" + QObject::tr("Area captante") +        "</td><td>";
    if (localita.additionalArea.size()>0)
           coll += QString("%L1").arg(localita.area) + "m<sup>2</sup>" + "/" + QString("%L1").arg(localita.additionalArea.at(0)) +  "m<sup>2</sup></td><td></td></tr>";
    else
           coll += QString("%L1").arg(localita.area) + "m<sup>2</sup></td><td></td></tr>";

    coll += "<tr><td>" + QObject::tr("Tipo installazione") +        "</td>";
    coll += "<td>" + mounting.at(localita.mounting)+       "</td><td></td></tr>";
    coll += "<tr><td>" + QObject::tr("Fattore concentrazione") +        "</td>";
    coll += "<td>" + QString("%L1").arg(localita.concRatio)+       "</td><td></td></tr>";
    coll += "<tr><td colspan=3>";
    coll +="<table  cellspacing=0 cellpadding=0  width=\"100%\"  ><tr>";
    coll += "<td>" + QObject::tr("Radiazione") + "</td>";
    for(int i=1;i<=12;i++) {

    coll += "<td>" + MyMath::months(i) + "</td>";

    }
    coll += "</tr><tr><td>["+unit+"]</td>";

    double k;
    if (unit=="kWh/m2")
        k = 1/3.6;
    else
        k = 1;

    for(int i=0;i<12;i++) {
                if (Hset)
                    coll += "<td>" + QString("%L1").arg(H[i]*k,0,'f',2) + "</td>";
                else
                    coll += "<td>" + QString("0") + "</td>";
        }

    coll += "</tr></table></td></tr>";
    coll += "</tbody></table>";

    /***************SISTEMA **********************************/
    if (localita.additionalArea.size()>0)
    {
        sistema = " <table   width=\"680\" border=\"0\"><tbody><tr bgcolor=\"lightGray\" ><td colspan=\"3\"  >"+        QObject::tr("Sistema a doppia falda") +"</td></tr>";

    }
    else
    {
        sistema = "<table   width=\"680\" border=\"0\"><tbody><tr bgcolor=\"lightGray\" ><td colspan=\"3\"  >"+   QObject::tr("Sistema") +"</td> </tr>";

    }

 sistema += "<tr><td>" + QObject::tr("Fabbricante/Modulo") +        "</td>";
    if (pan.isValid)
        sistema += "<td>" + pan.fabric + "</td>";
        else
        sistema += "<td>" + QObject::tr("Non disponibile") + "</td>";


    if (pan.isValid)
        sistema += "<td>" + pan.model +"</td>";
        else
        sistema +="<td>"  + QObject::tr("Non disponibile") +"</td>";

    sistema +="</tr>";

    sistema +="<tr><td>" + QObject::tr("Potenza nominale modulo/Efficienza") + "</td>";
    if (pan.isValid){
        sistema += "<td>"+  QString("%L1").arg(pan.pnom) + " Wp</td>";

     }
        else
    sistema += "<td></td>";

    if (pan.eff!=0 & pan.eff<100 & pan.isValid)
                sistema += "<td>" + QString("%L1").arg(pan.eff,0,'f',2)+ " %</td>";
    else
                 sistema += "<td>- %</td>";

    sistema += "</tr>";
    sistema  += "<tr><td>"+ QObject::tr("Usura annua") + "</td>";
    if (pan.isValid)
    {
        sistema   += "<td>" + QString::number(pan.gar) + "%</td><td></td></tr>";

    }
    else
    {
        sistema   += "<td>- %</td><td></td></tr>";

    }
     sistema +="<tr><td>" + QObject::tr("Voc/Isc (modulo)") + "</td>";

    if (pan.isValid){
         sistema += "<td>" +  QString("%L1").arg(pan.voc)+" V</td>";
        sistema += "<td>"+  QString("%L1").arg(pan.isc) + " A</td>";
}
    else{
        sistema +="<td> - V</td>";
         sistema += "<td>- A</td>";
 }
    sistema += "</tr>";


    sistema +="<tr><td>" + QObject::tr("Numero moduli/Pot. installata") + "</td>";
    if (localita.additionalArea.size()==0)
    {
    if (numPanels>0)
        sistema += "<td>" + QString("%L1").arg(numPanels) + "</td>";

    if (numPanels>0)
         sistema += "<td>" + QString("%L1").arg(numPanels*pan.pnom) + " Wp</td>" ;
        else
         sistema += "<td>-</td><td> - Wp</td>";
    }
    else
    {
         sistema += "<td>" + QString("%L1").arg(numPanels) + "/" +
                    QString("%L1").arg(numPanels2) + "</td>";
          sistema += "<td>" + QString("%L1").arg((numPanels+numPanels2)*pan.pnom) +"Wp</td>";
    }
    sistema += "</tr>";


    if (systemDetails.models.isEmpty()  || !systemDetails.systemValid){
             sistema +="<tr><td>" + QObject::tr("Modello Inverter  ") + "</td>";
             sistema +="<td>" + inv.fabric +"-"+ inv.model + "</td>";
                if (inv.isValid)
                   sistema +="<td>" +QString("%L1").arg(inv.eff) + "%</td>";
                else
                 sistema += "<td>" "- %</td>";
        }
        else
        {
                sistema +="<tr><td>" + QObject::tr("Modello Inverter(*)") + "</td>";

                sistema +="<td>" + QString("%L1").arg(systemDetails.campiVector.size()) +"</td>";

                  sistema +="<td>" + tr("(*)") + "</td>";
        }
    sistema += "</tr>";

   sistema +="<tr><td>" + QObject::tr("Perdite termiche totali") + "</td>";
   sistema +="<td>" +QString("%L1").arg(opt.totalLossTemp,0,'f',2)+ " %</td><td></td>";
   sistema += "</tr>";

   sistema +="<tr><td>" + QObject::tr("Perdite annuali per ombreggiamento") + "</td>";
   sistema +="<td>" +QString("%L1").arg(opt.totalShadowLossFactor*100,0,'f',2)+ " %</td><td></td>";
   sistema += "</tr>";

   sistema +="<tr><td>" + QObject::tr("Fattore ombregg. medio mensile") + "</td>";
   sistema +="<td>" +QString("%L1").arg(opt.meanShadowLossFactor,0,'f',2)+ "</td><td></td>";
   sistema += "</tr>";

   sistema +="<tr><td>" + QObject::tr("BOS medio") + "</td>";
   sistema +="<td>" +QString("%L1").arg(MyMath::mean(opt.otherLoss))+ "</td><td></td></tr>";
   sistema += "</tbody></table>";

    /*************** MEDIE **********************************/
   medie = " <table width=\"680\"><tbody><tr bgcolor=\"lightGray\" ><td colspan=\"3\"  >"+        QObject::tr("Valori medi mensili") +"</td></tr>";
   medie +="<tr><td colspan=\"3\">";
   medie +="<table  width=\"100%\" border=1 cellspacing=\"0\" cellpadding=\"3\" ><tr><td></td>";
   medie += "<td>" + QObject::tr("Energia[")+unitEnergy+"]" + "</td>";
   medie += "<td>" + QObject::tr("Fattore Ombre[%]") + "</td>";
   medie += "<td>" + QObject::tr("Perdite termiche[%]") + "</td>";
   medie += "<td>" + QObject::tr("Altre perdite[%]") + "</td>";
   medie += "<td>" + QObject::tr("Temp. medie[<sup>o</sup>]") + "</td>";
   medie += "<td>" + QObject::tr("Vento medio[m/s]") + "</td>";
   medie += "</tr>";

   for(int i=0;i<12;i++) {
       medie +=  "<tr>";
       medie += "<td>" + MyMath::months(i+1) + "</td>";
        /* Energia*/
        if (Eset)
            medie += "<td>" + QString("%L1").arg(E[i],0,'f',2) + "</td>";
        else
            medie += "<td>" + QString("%L1").arg(0) + "</td>";

        /*Ombre*/
        medie += "<td>" + QString("%L1").arg((opt.shadows.at(i))*100,0,'f',2) + "</td>";

        /*Perdite termiche*/
        medie += "<td>" +QString("%L1").arg((1-
                                             opt.thermalLosses.at(i))*100,0,'f',2) +"</td>";
        /*Altre perdite*/
        medie += "<td>" + QString("%L1").arg((opt.otherLoss.at(i))*100,0,'f',2) +"</td>";

        /*Temperature*/
        medie += "<td>" + QString("%L1").arg(opt.temperatures.at(i),0,'f',2) +"</td>";
        /*vento*/
         medie += "<td>" +QString("%L1").arg(opt.wind.at(i),0,'f',2) + "</td>";

    medie += "</tr>";
    }
   medie += "</table>";

   medie += "</td></tr></tbody></table>";


   QString t= "<strong>" + QString("%L1").arg(totEnergy) + " "+ unitEnergy+"</strong>";
   QString t2 = "<strong>" + QString("%L1").arg(localita.starRatio,0,'f',2) + " kWh/kWp "+"</strong>";

   totale = " <table  ><tbody><tr><td>"+  QObject::tr("Totale annuo") +"</td><td></td><td>" + t + "</td></tr>";
   totale +="<tr><td>"  +  QObject::tr("Rendimento")  + "</td><td></td><td>" + t2 +"</td></tr></tbody></table>";

    s +=   site  + coll + model + sistema + medie   + totale + "</body></html>";
//qDebug()<<s;

    return s;
}
QString OutReport::makeEcoTable()
{
    QString summary;
    summary  =" <table  border=0   width=\"680\" ><tbody><tr  bgcolor=\"lightGray\"><td colspan=\"3\">" + QObject::tr("Aspetti Economici") +"</td></tr> ";


    summary += "<tr>";
    summary += "<td>" + QObject::tr("Costo totale impianto (IVA esclusa), IVA") +"</td>";
    summary += "<td>" + QString("%L1").arg(eco.initialCost,0,'f',2) +"</td>";
    summary += "<td>" + QString("%L1").arg(eco.vat) +        "%</td>";
    summary +="</tr><tr>";
    summary += "<td>" + QObject::tr("Sgravio IVA, Sgravio spese iniziali") +"</td>";
    summary += "<td>" + QString("%L1").arg(eco.benefitVATCost,0,'f',2)+"%" +"</td>";
    summary += "<td>" + QString("%L1").arg(eco.benefitInitialCost,0,'f',2)+"%" +"</td>";
    summary +="</tr><tr>";
    summary += "<td>" + QObject::tr("Sgravio Interessi, Altri sgravi") +"</td>";
    summary += "<td>" + QString("%L1").arg(eco.benefitTotalInterest,0,'f',2) +"</td>";
    summary += "<td>" + QString("%L1").arg(eco.benefitTaxes,0,'f',2)+"%" +"</td>";
    summary +="</tr><tr>";
    summary += "<td>" + QObject::tr("IVA su Incentivo/CS/Vendita") +"</td>";
    summary += "<td>" + QString("%L1").arg(eco.taxes[0],0,'f',2) + "%/" +
                        QString("%L1").arg(eco.taxes[1],0,'f',2) +"%/"+
                        QString("%L1").arg(eco.taxes[2],0,'f',2) +"%</td>";
    summary +="</tr><tr>";
    summary += "<td>" + QObject::tr("IRAP su Incentivo/CS/Vendita") +"</td>";
    summary += "<td>" + QString("%L1").arg(eco.taxes[6],0,'f',2) + "%/" +
                        QString("%L1").arg(eco.taxes[7],0,'f',2) +"%/"+
                        QString("%L1").arg(eco.taxes[8],0,'f',2) +"%</td>";
    summary +="</tr><tr>";
    summary += "<td>" + QObject::tr("IRES Incentivo/CS/Vendita") +"</td>";
    summary += "<td>" + QString("%L1").arg(eco.taxes[9],0,'f',2) + "%/" +
                        QString("%L1").arg(eco.taxes[10],0,'f',2) +"%/"+
                        QString("%L1").arg(eco.taxes[11],0,'f',2) +"%</td>";
    summary +="</tr><tr>";
    summary += "<td>" + QObject::tr("IRPEF su Incentivo/CS/Vendita") +"</td>";
    summary += "<td>" + QString("%L1").arg(eco.taxes[3],0,'f',2) + "%/" +
                        QString("%L1").arg(eco.taxes[4],0,'f',2) +"%/"+
                        QString("%L1").arg(eco.taxes[5],0,'f',2) +"%</td>";
    summary +="</tr><tr>";

    summary += "<td>" + QObject::tr("Tassi inflazione,Inflazione costo energia") + "</td>";
    summary += "<td>" + QString("%L1").arg(eco.inflRate)+"%" + "</td>";
    summary += "<td>" + QString("%L1").arg(eco.fasceInflazione)+"%" + "</td>";
    summary +="</tr><tr>";
    summary += "<td>" + QObject::tr("Tasso di sconto, interesse su finanziamento") +"</td>";

    summary += "<td>" + QString("%L1").arg(eco.discountRate)+"%"+ "</td>";

    summary += "<td>" +QString("%L1").arg(eco.loanInterestRate)+"%"+ "</td>";
    summary +="</tr><tr>";

    summary += "<td>" + QObject::tr("Incentivi ")+ "</td>";

    summary += "<td>" + QString("%L1").arg(eco.bonuses)+" c/kWh"+ "</td>";

    summary += "<td>" +QString("%L1").arg(eco.bonusesYears)+ tr(" anni")+"</td>";
    summary +="</tr><tr>";
    summary += "<td>" +QObject::tr("Ammortamento, Durata ammortamento")+ "</td>";

    summary += "<td>"+QString("%L1").arg(eco.ammortamento)+"%"+ "</td>";

    summary += "<td>"+QString("%L1").arg(eco.ammortamentoAnni)+tr(" anni")+ "</td>";
    summary +="</tr><tr>";
    summary += "<td>"+QObject::tr("Durata finanziamento")+ "</td>";

    summary += "<td>"+QString("%L1").arg(eco.loanYears)+tr(" anni")+ "</td>";
    summary +="<td></td></tr><tr>";
    summary += "<td>"+QObject::tr("Regime")+ "</td>";

    summary += "<td>"+regime.at(eco.regime)+ "</td>";
    summary +="<td></td></tr><tr>";
    summary += "<td>"+QObject::tr("Periodo di analisi")+ "</td>";

    summary += "<td>"+QString("%L1").arg(eco.life)+  tr(" anni") + "</td>";
    summary +="<td></td></tr> </tbody></table>";
    summary  +=" <table  border=0   width=\"680\"><tbody><tr  bgcolor=\"lightGray\"><td colspan=\"3\">" + QObject::tr("Consumi utenze") +"</td></tr> ";
    summary  +="<tr>";
    summary  +="<td>" + QObject::tr("Totale annuo, Profilo consumi mensili") + "</td>";
    summary  +="<td>" + QString("%L1").arg(yearlyLoad,0,'f',2) + "kWh"+ "</td>";
    if (monthlyProfile < profile.size())
     summary  +="<td>" + profile.at(monthlyProfile) +  "</td>";
    summary   +="</tr></tbody></table>";
     qDebug()<<"OUT ECO TABLE"<<summary;
    return summary;



}
QRectF OutReport::contentRect(QPaintDevice *device)
{
    // calculate size of content (paper - margins)
    QRectF rect = paperRect(device);

    rect.adjust(mmToInches(leftmargin_) * device->logicalDpiX(),
                mmToInches(topmargin_) * device->logicalDpiY(),
                -mmToInches(rightmargin_) * device->logicalDpiX(),
                -mmToInches(bottommargin_) * device->logicalDpiY());



    return rect;
}

// paperRect() ////////////////////////////////////////////////////////////////
// Return the size of the paper, adjusted for DPI
QRectF OutReport::paperRect(QPaintDevice *device)
{
    // calculate size of paper
    QRectF rect = printer_->paperRect();
    // adjust for DPI
    rect.setWidth(rect.width() *
                  device->logicalDpiX() / printer_->logicalDpiX());
    rect.setHeight(rect.height() *
                  device->logicalDpiY() / printer_->logicalDpiY());

    return rect;
}
void OutReport::print(QPrinter *printer,int mode,QPrinter::OutputFormat format)
{
    QString fileName;
   // printer->setResolution(1200);
  //  m_document->setUseDesignMetrics(true);
   printer->setPaperSize(QPrinter::A4);
   m_document->setPageSize(contentRect(printer).size());
    QTextFrameFormat fmt = m_document->rootFrame()->frameFormat();
    fmt.setMargin(0);
    m_document->rootFrame()->setFrameFormat(fmt);
   // printer->setFullPage(true);


	if (mode==1)
	{
            if (format==QPrinter::PdfFormat){

                fileName =
                        QFileDialog::getSaveFileName(this,
                        QObject::tr("Nome file da esportare"),  recentDir,"Acrobat ( *.pdf)");
                 fileName = MyMath::checkFormat(fileName,"pdf");
            }
            if (format==QPrinter::PostScriptFormat){
                fileName =
                        QFileDialog::getSaveFileName(this,
                        QObject::tr("Nome file da esportare"),  recentDir,"Post Script ( *.ps)");
            fileName = MyMath::checkFormat(fileName,"ps");
            }



		QFileInfo fileInfo(fileName);
		recentDir = fileInfo.absoluteDir().absolutePath();
                //qDebug()<<"OR file"<<recentDir;
		if ( !fileName.isEmpty() ) {

                printer_->setOutputFormat(format);
		printer->setOutputFileName(fileName);
		}
		else
			return;
        }

        if (mode==3)
             printer->setOutputFormat(QPrinter::NativeFormat);


      QPainter p(printer);
      p.setRenderHints(QPainter::Antialiasing |
                             QPainter::TextAntialiasing |
                             QPainter::SmoothPixmapTransform, true);



        // Nov 2010
        m_document->documentLayout()->setPaintDevice(p.device());


        m_document->clear();
        //qDebug()<<cssTable()+makeTable();


        m_cursor.insertHtml(cssTable()+makeTable());

        QwtPlotPrintFilter filter;

        int options = QwtPlotPrintFilter::PrintAll;
        options &= ~QwtPlotPrintFilter::PrintBackground;
        options |= QwtPlotPrintFilter::PrintFrameWithScales;
        filter.setOptions(options);

        int pw 	  =  printer->pageRect().width();
        int ph        =  printer->pageRect().height();

        double paperH =  floor(printer->paperSize(QPrinter::DevicePixel).height());







        //p.save();
        //m_document->adjustSize();
	QTransform tra;

/* For Qt 4.5.0 there is a bug in qprintpreview dialog? */
        if (mode==0){
#ifdef Q_WS_WIN
        /* In Qt 4.5 it seems there is a problem with print preview*/
        tra.scale(floor(0.52*paperH/printer->resolution()),floor(0.52*paperH/printer->resolution()));
        qDebug()<<"SCALE FOR WINDOWS";
#else
        tra.scale(floor(paperH/printer->resolution()),floor(paperH/printer->resolution()));
        qDebug()<<"SCALE FOR LINUX";
#endif
    }else{
        if (mode==3)
        {
            tra.translate(mmToInches(leftmargin_)*printer->logicalDpiX(),
                          mmToInches(topmargin_)*printer->logicalDpiY());
            tra.scale(floor(ph/printer->resolution())-1,floor(ph/printer->resolution())-1);
          //  p.setTransform(tra);
       //     printer->setPageMargins(400.0,400.0,400.0,400.0,QPrinter::DevicePixel);



        }
        else{
            tra.translate(mmToInches(leftmargin_)*printer->logicalDpiX(),
                          mmToInches(topmargin_)*printer->logicalDpiY());
            tra.scale(floor(ph/printer->resolution()),floor(ph/printer->resolution()));
        //    p.setTransform(tra);
        }
    }


        //RECT for printing
        QRect recCenter(-10,0.4*ph,pw-10,0.6*ph);
        QRect recTop(-10 ,0,pw-10,0.5*ph);
        QRect recTop2(-10,0,pw-10,(int)(0.5*ph));
        QRect recBottom2(-10,(int)(0.5*ph),pw-10,(int)(0.5*ph));
        QRect recBottomE(-10,0.4*ph,pw-10,0.4*ph);
        QRect recBottom(-10,0.5*ph,pw-10,0.5*ph);
        QRect recBottomLeft(-10,0.6*ph,(int)(pw*0.5),(int)(0.4*ph));
        QRect recBottomRight(pw*0.5,0.6*ph,(int)(pw*0.5),(int)(0.4*ph));

//        QRectF rect = contentRect(p.device());
//        p.translate(rect.left(), rect.top() -  rect.height());
//        QRectF clip(0,  rect.height(), rect.width(), rect.height());

        /********************* DETTAGLI INVERTERS**********/
        QString preamble = "<p><center><br/><h4>(*)Dettagli inverters</h4><table border=1 width=\"580\" cellspacing=0 cellpadding=3 bordercolor=\"#980000\" >";
                QString header   = "<tr width=\"100%\" bgcolor=\"#C89800\"><td >" + tr("Inverter") + "</td><td >" + tr("Efficienza(%)") + "</td><td>" + tr("Stringhe")    + "</td><td>" + tr("Pannelli x Stringa") + "</td></tr>";
                QString line = preamble + header;

        if (!systemDetails.models.isEmpty() && systemDetails.systemValid) {

                for(int i=0;i<systemDetails.campiVector.size();i++){

                        line += "<tr><td>" + systemDetails.models.at(i) + "</td><td>" + QString("%L1").arg(systemDetails.efficiencies.at(i)) + "</td><td>" + QString("%L1").arg(systemDetails.campiVector.at(i)) + 		"</td><td>" + QString("%L1").arg(systemDetails.panelVector.at(i)) + "</td></tr>";
        }

        }
        else
        {
                        line += "<tr><td>-</td></tr>";
        }
        line+="</table></center><p>";


     /**************************************************************************/
//qDebug()<<"OO system details print"<<systemDetails.systemValid<<systemDetails.models.isEmpty()<<systemDetails.campiVector.size();
        /* DRAW FIRST PAGE */
         if (!systemDetails.models.isEmpty() &&
                systemDetails.systemValid &&
                systemDetails.campiVector.size()<=2)
        {
             m_cursor.insertHtml(line);

         }

        m_document->drawContents(&p,printer->paperRect());
	
  //  qDebug()<<"OOOOOOOOOOOOOO"<<printer->pageRect()<<printer->paperSize(QPrinter::DevicePixel)<<printer->paperRect()<<printer->pageSize()<<p.viewport()<<pw<<ph<<ph/printer->resolution()<<ph/printer->resolution()<<printer->resolution();

        //p.restore();

        if (!systemDetails.models.isEmpty() && systemDetails.systemValid){
            if (systemDetails.campiVector.size()>2){
                 m_document->clear();
                // p.save();
               //  p.setTransform(tra);
                 printer->newPage();
                 m_cursor.insertHtml(line);
                 m_document->drawContents(&p,printer->pageRect());

              //   p.restore();
                 qDebug()<<"OO inverter"<<line;
             }

            }


	printer->newPage();



       // QString tempFile = QDir::homePath() +"/_sc_sd_del.png";
        if (solarDiagram){
                 solarDiagram->print(&p,recTop,filter);
//                solarDiagram->exportPNG(tempFile);
//                qDebug()<<"OO "<<tempFile;
            //    QFile(tempFile).remove();
            }

//         m_cursor.insertHtml("<img src=\""+tempFile+"\"/>");
//          p.save();
//         p.setTransform(tra);
//          m_document->drawContents(&p,printer->pageRect());
//          p.restore();

        /***********ENERGY DIAGRAM ****************/


        if (eEnergy!=0)
            eEnergy->print(&p,recBottom,filter);

if (ecoIsPresent && !summaryTable.isEmpty()){
	printer->newPage();
	
        /******************ECO Page******************/
	m_document->clear();
       // m_document->setPageSize(paperRect(printer).size());
      //  printer->setPageMargins(400.0,400.0,400.0,400.0,QPrinter::DevicePixel);

        m_cursor.insertHtml( makeEcoTable().replace("width=\"100%\"","width=800"));


        /*******************************************************/
        /* Risultati simulazione                               */
        /*******************************************************/
        if (!summaryTable.isEmpty()){


             m_cursor.insertHtml(tr("<br/><h2>Esploso risultati principali: MOL</h2><br/>") + summaryTable);
              //  p.save();
             //   p.setTransform(tra);
            //    qDebug()<<"OO"<<summaryTable;
                m_document->drawContents(&p,printer->paperRect());
             //   p.restore();

        }
        if (!summaryTable.isEmpty()){
            if (ecoIsPresent && eco.life>=13){
                 printer->newPage();
                 m_document->clear();

             }

             m_cursor.insertHtml(tr("<br/><h2>Esploso risultati principali: Flusso di cassa e VAN</h2><br/>") +summaryTax);
              //  p.save();
             //   p.setTransform(tra);
                m_document->drawContents(&p,printer->paperRect());
            //    p.restore();
             
        }
       // printer->setPageMargins(0.0,0.0,0.0,0.0,QPrinter::DevicePixel);
        if (!summaryTable.isEmpty())
            printer->newPage();
        if (rawDiagram!=0 && vanDiagram!=0){
                rawDiagram->print(&p,recTop,filter);
                vanDiagram->print(&p,recBottom,filter);
	}


}
	p.end();
 
        if (mode==1)
        //NOW try to open the exported file
        QDesktopServices::openUrl(fileName);
 
	
	
 

}
void OutReport::setEcoParameters(ecopara o)
{
	eco = o;
	ecoIsPresent = true;
}
void OutReport::setVersion(const QString &s)
{
	version = s;
}
void OutReport::setTable(const QString &s)
{
	summaryTable = s;
}
void OutReport::setTax(const QString &s)
{
	summaryTax = s;
}
void OutReport::addSystem(sy  a)
{
	systemDetails = a;
        qDebug()<<"OO system is valid?"<<systemDetails.systemValid;
}
void OutReport::addYearlyLoad(double a)
{
    yearlyLoad = a;
}
void OutReport::addMonthlyProfile(int a)
{
    monthlyProfile = a;
}
