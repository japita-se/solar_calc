/****************************************************************************
** Meta object code from reading C++ file 'hourlyplot.h'
**
** Created: Sun 7. Apr 21:24:49 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../hourlyplot.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hourlyplot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_HourlyPlot[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   12,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      31,   11,   11,   11, 0x09,
      43,   11,   11,   11, 0x09,
      54,   11,   11,   11, 0x09,
      65,   11,   11,   11, 0x09,
      77,   11,   11,   11, 0x09,
      89,   11,   11,   11, 0x09,
     101,   11,   11,   11, 0x09,
     117,  113,   11,   11, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_HourlyPlot[] = {
    "HourlyPlot\0\0i\0unitChanged(int)\0"
    "updateSet()\0settings()\0printOut()\0"
    "exportSVG()\0exportPNG()\0exportPDF()\0"
    "exportTXT()\0pos\0popUpMenu(QPoint)\0"
};

const QMetaObject HourlyPlot::staticMetaObject = {
    { &QwtPlot::staticMetaObject, qt_meta_stringdata_HourlyPlot,
      qt_meta_data_HourlyPlot, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &HourlyPlot::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *HourlyPlot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *HourlyPlot::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HourlyPlot))
        return static_cast<void*>(const_cast< HourlyPlot*>(this));
    return QwtPlot::qt_metacast(_clname);
}

int HourlyPlot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QwtPlot::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: unitChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: updateSet(); break;
        case 2: settings(); break;
        case 3: printOut(); break;
        case 4: exportSVG(); break;
        case 5: exportPNG(); break;
        case 6: exportPDF(); break;
        case 7: exportTXT(); break;
        case 8: popUpMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void HourlyPlot::unitChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
