#ifndef _RADGUI_
#define _RADGUI_
#include <QString>
#include "ui_datiradiazione.h"
class QPollygonF;

class DatiRadiazione : public QDialog, public Ui::DatiRadiazione
{
	Q_OBJECT
public:
	DatiRadiazione(QWidget *parent =0 );
	~DatiRadiazione();
	
	QPolygonF getCustomHg();
	void loadCustomRad(const QString &f);
	QString getSourceName();
	bool isDirty();
	void setDirty(bool state);
public slots:
	void setDirty();
 signals:
	void sorgenteChanged();
private slots:
	 
 	void emitSignal(bool i);
	 
	
	void on_pushCarica_clicked();
private:
	void updateLinePath(const QString &);
	void resizeCustomHg(int i);
private:
	int status;
	bool dirty;
	QString recentDir;
	QString sourceName;
	QPolygonF customHg;
 
	 
	
	
};
#endif
