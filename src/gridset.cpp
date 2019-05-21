#define DEBUG
#include "gridset.h"
#include <QDebug>
GridSet::GridSet(QWidget *parent ) : QDialog(parent)

{	
	setupUi(this);
	
	
	
	connect(checkAsseX,SIGNAL(stateChanged(int )),SLOT(updateAsseX(int )));
	connect(checkAsseY,SIGNAL(stateChanged(int )),SLOT(updateAsseY(int )));
	
	
}

void GridSet::updateAsseX(int i)
{
	assex = i;
}

void GridSet::updateAsseY(int i)
{
	assey = i;
}
int GridSet::getAsseX( )
{
	return assex;
}

int GridSet::getAsseY( )
{
	return assey;
}
void GridSet::setAsseX(int i)
{
	if (i==0)
		checkAsseX->setChecked(Qt::Unchecked);
	if (i>=1)
		checkAsseX->setChecked(Qt::Checked);
	assex = i > 0 ? i : 0;
}

void GridSet::setAsseY(int i)
{
	if (i==0)
		checkAsseY->setChecked(Qt::Unchecked);
	if (i>=1)
		checkAsseY->setChecked(Qt::Checked);
	assey = i > 0 ? i : 0;
}
 GridSet::~GridSet()
{
}