/****************************************************************************
** Meta object code from reading C++ file 'myplot.h'
**
** Created: Mon 25. Oct 20:55:57 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/myplot.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myplot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyPlot[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
      23,    7,    7,    7, 0x0a,
      41,   36,    7,    7, 0x0a,
      65,   63,    7,    7, 0x0a,
      83,    7,    7,    7, 0x0a,
      97,    7,    7,    7, 0x0a,
     115,    7,    7,    7, 0x0a,
     126,    7,    7,    7, 0x0a,
     137,    7,    7,    7, 0x0a,
     149,    7,    7,    7, 0x0a,
     161,   63,    7,    7, 0x0a,
     181,    7,    7,    7, 0x0a,
     197,  193,    7,    7, 0x0a,
     219,    7,    7,    7, 0x0a,
     244,    7,    7,    7, 0x0a,
     256,    7,    7,    7, 0x0a,
     269,    7,    7,    7, 0x0a,
     281,  279,    7,    7, 0x0a,
     301,    7,    7,    7, 0x0a,
     314,    7,    7,    7, 0x0a,
     333,  329,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MyPlot[] = {
    "MyPlot\0\0ombreChanged()\0resetOmbre()\0"
    "mode\0toggleSelfShadow(int)\0a\0"
    "toggleSpline(int)\0undoCombine()\0"
    "popUpMenu(QPoint)\0printOut()\0settings()\0"
    "exportSVG()\0exportPNG()\0exportPNG(QString&)\0"
    "exportPDF()\0pos\0moved(QwtDoublePoint)\0"
    "selected(QwtDoublePoint)\0updateSet()\0"
    "updateGrid()\0gridset()\0s\0loadShadow(QString)\0"
    "loadShadow()\0deleteShadow()\0i,d\0"
    "drawShadow(int,QPolygonF)\0"
};

const QMetaObject MyPlot::staticMetaObject = {
    { &QwtPlot::staticMetaObject, qt_meta_stringdata_MyPlot,
      qt_meta_data_MyPlot, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyPlot::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyPlot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyPlot::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyPlot))
        return static_cast<void*>(const_cast< MyPlot*>(this));
    return QwtPlot::qt_metacast(_clname);
}

int MyPlot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QwtPlot::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ombreChanged(); break;
        case 1: resetOmbre(); break;
        case 2: toggleSelfShadow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: toggleSpline((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: undoCombine(); break;
        case 5: popUpMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 6: printOut(); break;
        case 7: settings(); break;
        case 8: exportSVG(); break;
        case 9: exportPNG(); break;
        case 10: exportPNG((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: exportPDF(); break;
        case 12: moved((*reinterpret_cast< const QwtDoublePoint(*)>(_a[1]))); break;
        case 13: selected((*reinterpret_cast< const QwtDoublePoint(*)>(_a[1]))); break;
        case 14: updateSet(); break;
        case 15: updateGrid(); break;
        case 16: gridset(); break;
        case 17: loadShadow((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 18: loadShadow(); break;
        case 19: deleteShadow(); break;
        case 20: drawShadow((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QPolygonF(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void MyPlot::ombreChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
