#ifndef CASHFLOW_H
#define CASHFLOW_H
#include <QtGui>
#include "data.h"
 
#include <qwt_plot_marker.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
 #include "ui_cashflow.h"
class Settings;
class QwtPlotPicker;
class QPos;
class GridSet;
class QPoint;
class QActions;
class QwtPlotGrid;
class QPolygonF;
class HistogramItem;
class QwtPlotCurve;
class QwtLegend;
 
class CashFlowPlot  :  public QWidget, public Ui::widgetCashFlow
{
	Q_OBJECT 
public:
  CashFlowPlot( QWidget *par =NULL);
  ~CashFlowPlot();

        void setFinVat(double a);
        void setWarnings(const QString& q);
        void setNumOfDec(int i);
        void reset();
        void setOptions(const QVector<int> &y);
	QString getTable();
        QString getTaxTable();
        void setTasse(const QPolygonF& a);
        void setInjected(const QPolygonF& a);
        void setFetched(const QPolygonF& a);
        void setSavingsEn(const QPolygonF& a);
	void setYearlyCostNPV(const QPolygonF& a);
        void setIVA(const QPolygonF &a);
        void setIres(const QPolygonF &a);
        void setIrpef(const QPolygonF &a);
        void setIrap(const QPolygonF &a);
        void setNetto(const QPolygonF &a);
        void setCUSorCor(const QPolygonF& a);
        void setOE(const QPolygonF& a);
        void setCredit(const QPolygonF& a);
        void setCei(const QPolygonF& a);
	void setYearlyCost(const QPolygonF& a);
	void setAmmNPV(const QPolygonF& a);
        void setAmm(const QPolygonF& a);
	void setEcoParameters(const ecopara e);
	void setRataNPV(const QPolygonF &a);
	void setRata(const QPolygonF &a);
	void setNPV(const QPolygonF &a);
	void setRawCash(const QPolygonF &a);
	void setInterestNPV(const QPolygonF &a);
	void setInterest(const QPolygonF &a);
	void setCS(const QPolygonF &a);
	void setBonus(const QPolygonF &a);
        void setSelfConsumed(const QPolygonF &a);
	void setProduced(const QPolygonF &a);

        void drawRata(int mode);
        void drawRataNPV(int mode);
        void drawInterest(int mode );
        void drawInterestNPV(int mode );
        void drawFlowCash( int mode);
        void drawNPV(int mode );
	QwtPlot* vanDiagram();
	QwtPlot* rawDiagram();
protected:
        double suggestFinYears();
        static double functionFin(double n,double A, double Fin, double r );
        static double functionFin2(double n, QPolygonF A, double Fin, double r );
	void sanityCheck();
	void alignScales();
	void setPlots(int years);
	void createActions();
public slots:
        void updateTable();
private slots:
        void toggleInterestPlot(int state);
        void changeDrawData();
        void changeDraw(int s);
	void settings();
	void updateSet();
	void updateSetVan();
	void gridset();

        void movedMOL(const QPoint &pos);
        void movedVAN(const QPoint &pos);
	void updateGrid();
        void exportPNG(int w);
        void exportMOLPNG();
        void exportVANPNG();
        void exportSVG(int w);
        void exportMOLSVG();
        void exportVANSVG();
        void printOut(int w);
        void printOutMOL();
        void printOutVAN();
        void exportPDF(int w);
        void exportMOLPDF();
        void exportVANPDF();
        void exportTXT(int w);
        void exportMOLTXT();
        void exportVANTXT();
	void popUpMenu(const QPoint &p);
        void popUpMenuVAN(const QPoint &p);
protected:
        QAction *a_print,*a_export,*a_exportPNG,*a_exportPDF,*a_create_grid,
        *a_proprieta,*a_export_txt,
        *a_print_van,*a_export_van,*a_exportPNG_van,*a_exportPDF_van,*a_export_txt_van;;
        QwtPlotPicker *pickerVAN,*pickerMOL;
	QwtPlotGrid *grid,*grid2;	
	GridSet* gridSettings;
	QwtPlotCurve *csPlot;
        QwtLegend* legend;
	QPointF cursorPos;
	HistogramItem *vanPlot,*rawPlot,*interestPlot,*interestNPVPlot,*rataPlot,*rataNPVPlot;
        QString recentExportPath,s,sOther,recentDir,warnings;
        QPolygonF npv,npvCum,npvToUse,rawcash,rawcashToUse,rawcashCum,
        interest,interestNPV,csData,tasse,
        produced,consumed,fetched,injected,
        bonus,cs,cei,oe,cusOrCor,credit,rata,rataNPV,amm,ammNPV,
        yearlyCost,yearlyCostNPV,savingsEn,tassato,
        tassatoCum,tassatoToUse,iva,ires,irap,irpef,rawPlusTax,flowToUse,
        rawPlusTaxCum,rataCum;
	bool drawInterestFlag;
        double MOLx,loan;
	Settings *set,*setVan;
	ecopara eco;
        int numOfDec;
        QVector<int> simOptions;
enum{
	Vendita,
	SSPIT,
	SSP
	};
};
#endif
