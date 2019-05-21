#ifndef SIMECOOPTIONS_H
#define SIMECOOPTIONS_H

#include "data.h"
#include "ui_simecooptions.h"
#include <QDialog>

class SimEcoOptions : public QDialog, public Ui::dialogSimOptions
{
    Q_OBJECT;
public:
    SimEcoOptions(QWidget* parent =0);
    ~SimEcoOptions();

    QVector<int> getOptions();
    void setOptions(const QVector<int> &o);
private slots:
    void changeOptionsMOL();
    void changeOptionsVAN();
private:
    QVector<int> options;
    bool doNotUpdate;

};
#endif // SIMECOOPTIONS_H


