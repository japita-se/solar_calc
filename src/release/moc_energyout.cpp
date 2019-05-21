/****************************************************************************
** Meta object code from reading C++ file 'energyout.h'
**
** Created: Sat 6. Apr 22:49:03 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../energyout.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'energyout.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EnergyOut[] = {

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
      11,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      25,   10,   10,   10, 0x0a,
      37,   10,   10,   10, 0x08,
      55,   10,   10,   10, 0x08,
      66,   10,   10,   10, 0x08,
      78,   10,   10,   10, 0x08,
      90,   10,   10,   10, 0x08,
     102,   10,   10,   10, 0x08,
     113,   10,   10,   10, 0x08,
     129,  125,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_EnergyOut[] = {
    "EnergyOut\0\0unitChanged()\0exportPDF()\0"
    "popUpMenu(QPoint)\0printOut()\0exportSVG()\0"
    "exportPNG()\0exportTXT()\0settings()\0"
    "updateSet()\0pos\0moved(QPoint)\0"
};

const QMetaObject EnergyOut::staticMetaObject = {
    { &QwtPlot::staticMetaObject, qt_meta_stringdata_EnergyOut,
      qt_meta_data_EnergyOut, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EnergyOut::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EnergyOut::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EnergyOut::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EnergyOut))
        return static_cast<void*>(const_cast< EnergyOut*>(this));
    return QwtPlot::qt_metacast(_clname);
}

int EnergyOut::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QwtPlot::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: unitChanged(); break;
        case 1: exportPDF(); break;
        case 2: popUpMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 3: printOut(); break;
        case 4: exportSVG(); break;
        case 5: exportPNG(); break;
        case 6: exportTXT(); break;
        case 7: settings(); break;
        case 8: updateSet(); break;
        case 9: moved((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void EnergyOut::unitChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
