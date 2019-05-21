#ifndef ADDPV_H_
#define ADDPV_H_
#include "ui_addpv.h"
#include <QDialog>
class QSqlTableModel;

class AddPv : public QDialog, public Ui::AddPV
{
	Q_OBJECT
public:
	AddPv(QWidget* parent=0);
	~AddPv();
	
	void setModel(QString &s);

public:
	void setConnId(const QString &model);
private slots: 
	void updatePanelWidget();
	void updateModel();
	void updateEffWidget(int state);
	void updateEff();
	void checkAndExit();
private:
	bool checkData();
	bool checkDataInverter();
private:
	QString connId;
	double panelEff;
};
#endif
