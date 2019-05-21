#ifndef _ALBEDOUI_
#define _ALBEDOUI_

#include "ui_albedo.h"
class QStandardItemModel;

class Albedo : public QDialog, public Ui::Albedo
{
	Q_OBJECT
public:
	Albedo(QWidget *parent =0 );
	~Albedo();
	
	 
	double getAlbedo();
	int getAlbedoModel();
	void setAlbedoType(int m);
	void setAlbedo(double a);
private slots:
	void enableSnow(bool i);
	void setAlbedoType();
	void setAlbedo();
	void setAlbedo(const QModelIndex &m);
	void setAlbedoAndExit(const QModelIndex &m);	

private:
	void createValues();
	void createModel();

private:
	QStringList albedoValue,albedoType;
	QStandardItemModel *model;
	double albedo;
	int albedoModel;
	
	enum{
	con,
	variable_high_snow,
	variable_low_snow
	};
};
#endif