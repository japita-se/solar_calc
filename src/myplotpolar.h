#ifndef MYPLOTPOLAR_H
#define MYPLOTPOLAR_H
#include <qpen.h>
#include <qwt_data.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <qwt_polar_grid.h>
#include <qwt_polar_curve.h>
#include <qwt_polar_marker.h>
#include <qwt_scale_engine.h>

class MyPlotPolar : QwtPolarPlot
{
    Q_OBJECT
public:

    MyPlotPolar(QWidget*parent=0);
    setData()
private:
    QwtPolarCurve *dSolar[12];
};

#endif // MYPLOTPOLAR_H
