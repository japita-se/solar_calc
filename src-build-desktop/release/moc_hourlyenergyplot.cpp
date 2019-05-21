/****************************************************************************
** Meta object code from reading C++ file 'hourlyenergyplot.h'
**
** Created: Mon 25. Oct 20:55:23 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/hourlyenergyplot.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hourlyenergyplot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_HourlyEnergyPlot[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   18,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      37,   18,   17,   17, 0x0a,
      62,   17,   17,   17, 0x09,
      74,   17,   17,   17, 0x09,
      86,   17,   17,   17, 0x09,
      97,   17,   17,   17, 0x09,
     108,   17,   17,   17, 0x09,
     120,   17,   17,   17, 0x09,
     132,   17,   17,   17, 0x09,
     148,  144,   17,   17, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_HourlyEnergyPlot[] = {
    "HourlyEnergyPlot\0\0i\0unitChanged(int)\0"
    "enableDrawingLoads(bool)\0exportTXT()\0"
    "updateSet()\0settings()\0printOut()\0"
    "exportSVG()\0exportPNG()\0exportPDF()\0"
    "pos\0popUpMenu(QPoint)\0"
};

const QMetaObject HourlyEnergyPlot::staticMetaObject = {
    { &QwtPlot::staticMetaObject, qt_meta_stringdata_HourlyEnergyPlot,
      qt_meta_data_HourlyEnergyPlot, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &HourlyEnergyPlot::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *HourlyEnergyPlot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *HourlyEnergyPlot::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HourlyEnergyPlot))
        return static_cast<void*>(const_cast< HourlyEnergyPlot*>(this));
    return QwtPlot::qt_metacast(_clname);
}

int HourlyEnergyPlot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QwtPlot::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: unitChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: enableDrawingLoads((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: exportTXT(); break;
        case 3: updateSet(); break;
        case 4: settings(); break;
        case 5: printOut(); break;
        case 6: exportSVG(); break;
        case 7: exportPNG(); break;
        case 8: exportPDF(); break;
        case 9: popUpMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void HourlyEnergyPlot::unitChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
