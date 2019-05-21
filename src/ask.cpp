#include "ask.h"

Ask::Ask(QWidget* parent): QDialog(parent)
{
	setupUi(this);
	
	
	
	
	connect(checkNoMore,SIGNAL(stateChanged(int)),SLOT(setDoNotAsk()));
// 	connect(this,SIGNAL(accepted()),SLOT(setDoNotAsk()));
	connect(pushYes,SIGNAL(clicked()),SLOT(setOnlyCurrentMonth()));
	connect(pushNo,SIGNAL(clicked()),SLOT(setAllMonths()));
					
}
void Ask::setOnlyCurrentMonth()
{
	oneMonth = true;	
	setDoNotAsk();
	accept();
}
void Ask::setAllMonths()
{
		oneMonth = false;
		setDoNotAsk();
		accept();
}
void Ask::setDoNotAsk()
{
	doNot= checkNoMore->isChecked();
	
	 
}
bool Ask::doNotAskAgain()
{
	return doNot;
}
bool Ask::onlyCurrentMonth()
{
	return oneMonth;
}
 