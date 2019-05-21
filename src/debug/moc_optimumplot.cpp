/****************************************************************************
** Meta object code from reading C++ file 'optimumplot.h'
**
** Created: Sun 7. Apr 21:25:25 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../optimumplot.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'optimumplot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_OptimumPlot[] = {

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
      15,   13,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      32,   12,   12,   12, 0x0a,
      44,   12,   12,   12, 0x0a,
      55,   12,   12,   12, 0x08,
      73,   12,   12,   12, 0x08,
      84,   12,   12,   12, 0x08,
     100,   96,   12,   12, 0x08,
     114,   12,   12,   12, 0x08,
     135,   12,   12,   12, 0x08,
     147,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_OptimumPlot[] = {
    "OptimumPlot\0\0i\0unitChanged(int)\0"
    "exportPDF()\0swapUnit()\0popUpMenu(QPoint)\0"
    "printOut()\0exportSVG()\0pos\0moved(QPoint)\0"
    "selected(QwtPolygon)\0updateSet()\0"
    "settings()\0"
};

const QMetaObject OptimumPlot::staticMetaObject = {
    { &QwtPlot::staticMetaObject, qt_meta_stringdata_OptimumPlot,
      qt_meta_data_OptimumPlot, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &OptimumPlot::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *OptimumPlot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *OptimumPlot::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OptimumPlot))
        return static_cast<void*>(const_cast< OptimumPlot*>(this));
    return QwtPlot::qt_metacast(_clname);
}

int OptimumPlot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QwtPlot::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: unitChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: exportPDF(); break;
        case 2: swapUnit(); break;
        case 3: popUpMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 4: printOut(); break;
        case 5: exportSVG(); break;
        case 6: moved((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 7: selected((*reinterpret_cast< const QwtPolygon(*)>(_a[1]))); break;
        case 8: updateSet(); break;
        case 9: settings(); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void OptimumPlot::unitChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
