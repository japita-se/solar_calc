#ifndef _GRIDSETTINGSUI_
#define _GRIDSETTINGSUI_

#include "ui_gridset.h"

class GridSet : public QDialog, public Ui::GridSet
{
	Q_OBJECT
public:
	GridSet(QWidget *parent =0 );
	~GridSet();
	
	int getAsseX( );
	int getAsseY( );
	void setAsseX(int i);
	void setAsseY(int i);
	
	
	
	
private slots:
	 
	void updateAsseX(int i);
	void updateAsseY(int i);
	 
 
	
private:
	 int assex, assey;
	
};
#endif