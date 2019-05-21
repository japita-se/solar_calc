#include "simecooptions.h"

SimEcoOptions::SimEcoOptions(QWidget* parent) : QDialog(parent) {
    setupUi(this);
    doNotUpdate = false;

    options << 0 << 0; //for now only 2 kind of options

  //  connect(radioMOLMin,SIGNAL(toggled(bool)),this,SLOT(changeOptionsMOL()));
  //  connect(radioMOLMean,SIGNAL(toggled(bool)),this,SLOT(changeOptionsMOL()));
  //  connect(radioNettoRIB,SIGNAL(toggled(bool)),this,SLOT(changeOptionsMOL()));
    connect(radioNettoMean,SIGNAL(toggled(bool)),this,SLOT(changeOptionsMOL()));
    connect(radioBonusOnly,SIGNAL(toggled(bool)),this,SLOT(changeOptionsMOL()));
    connect(radioRIBCS,SIGNAL(toggled(bool)),this,SLOT(changeOptionsMOL()));

   // connect(radioCumNettoMean,SIGNAL(toggled(bool)),this,SLOT(changeOptionsMOL()));


}

void SimEcoOptions::changeOptionsVAN()
{
//    if (radioWACC->isChecked())
//        options.replace(1,1);
//    if (radioAdjustedDiscount->isChecked())
//        options.replace(1,0);
}

void SimEcoOptions::changeOptionsMOL()
{
    if (!doNotUpdate){
  //  if (radioMOLMin->isChecked())
   //     options.replace(0,0);
  //  if (radioMOLMean->isChecked())
  //      options.replace(0,1);
 //   if (radioNettoRIB->isChecked())
   //     options.replace(0,2);
 //   if (radioNettoMin->isChecked())
 //       options.replace(0,3);
    if (radioNettoMean->isChecked())
        options.replace(0,0);
    if (radioBonusOnly->isChecked())
        options.replace(0,1);
    if (radioRIBCS->isChecked())
        options.replace(0,2);

}

}
QVector<int> SimEcoOptions::getOptions()
{
    return options;
}
void SimEcoOptions::setOptions(const QVector<int> &o)
{
    if (o.isEmpty())
        qDebug()<<"WARNING SIMECOPTIONS null options";
    else
    options = o;

    /* Update the view */
    doNotUpdate = true;
    switch (options.at(0)){
    case 0:
        radioNettoMean->setChecked(true);
        break;
    case 1:
        radioBonusOnly->setChecked(true);
        break;
    case 2:
        radioRIBCS->setChecked(true);
        break;
    default:
        radioNettoMean->setChecked(true);
       }

doNotUpdate = false;
}

SimEcoOptions::~SimEcoOptions()
{
}
