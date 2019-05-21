#ifndef MODELSETTINGS_H
#define MODELSETTINGS_H
#include "ui_modelsettings.h"

class ModelSettings : public QDialog, public Ui::ModelSettings
{
    Q_OBJECT

public:
    ModelSettings(QWidget* parent=0);
    ~ModelSettings();
    int getOmbreSettings();
    int getModelSettings();

private slots:
    void updateView(int i);
    void setModelSettings(bool i);
    void setOmbreSettings(bool i);
    private:
        int modelRad,ombreCombine;
};
#endif // MODELSETTINGS_H
