#include "modelsettings.h"

ModelSettings::ModelSettings(QWidget* parent): QDialog(parent)
{
    setupUi(this);
  //  connect(radioUNI,SIGNAL(toggled(bool)),this,SLOT(setModelSettings(bool)));
  //  connect(radioOmbreLineari,SIGNAL(toggled(bool)),this,SLOT(setOmbreSettings(bool)));

    connect(comboType,SIGNAL(currentIndexChanged(int)),SLOT(updateView(int)));
    comboType->setCurrentIndex(0);
    labelType->setPixmap(QPixmap(":/images/fisso.jpg"));
}
void ModelSettings::updateView(int i)
{
	switch (i) {
	case 0:
	labelType->setPixmap(QPixmap(":/images/fisso.jpg"));
	break;
	case 1:
	labelType->setPixmap(QPixmap(":/images/vela.jpg"));
	break;
	case 2:
	labelType->setPixmap(QPixmap(":/images/doppio.jpg"));
	break;
	}

}
int ModelSettings::getModelSettings()
{
        return  modelRad;
}

int ModelSettings::getOmbreSettings()
{
    return ombreCombine;
}

void ModelSettings::setModelSettings(bool i)
{
    if (radioUNI->isChecked())
        modelRad = 1;
    else
        modelRad = 0;
}

void ModelSettings::setOmbreSettings(bool i)
{
    if (radioOmbreLineari->isChecked())
        ombreCombine = 0;
    else
        ombreCombine = 1;
}

ModelSettings::~ModelSettings()
{
};
