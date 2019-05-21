/****************************************************************************
** Meta object code from reading C++ file 'radiazioneReale.h'
**
** Created: Sun 7. Apr 21:25:35 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../radiazioneReale.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'radiazioneReale.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RadiazioneReale[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   17,   16,   16, 0x05,
      36,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      50,   16,   16,   16, 0x0a,
      61,   16,   16,   16, 0x0a,
      78,   73,   16,   16, 0x0a,
      96,   16,   16,   16, 0x08,
     105,   16,   16,   16, 0x08,
     123,   16,   16,   16, 0x08,
     134,   16,   16,   16, 0x08,
     146,   16,   16,   16, 0x08,
     158,   16,   16,   16, 0x08,
     174,  170,   16,   16, 0x08,
     188,   16,   16,   16, 0x08,
     199,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RadiazioneReale[] = {
    "RadiazioneReale\0\0i\0unitChanged(int)\0"
    "computeDone()\0swapUnit()\0exportPDF()\0"
    "mode\0drawRefCurve(int)\0redraw()\0"
    "popUpMenu(QPoint)\0printOut()\0exportSVG()\0"
    "exportTXT()\0exportPNG()\0pos\0moved(QPoint)\0"
    "settings()\0updateSet()\0"
};

const QMetaObject RadiazioneReale::staticMetaObject = {
    { &QwtPlot::staticMetaObject, qt_meta_stringdata_RadiazioneReale,
      qt_meta_data_RadiazioneReale, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RadiazioneReale::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RadiazioneReale::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RadiazioneReale::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RadiazioneReale))
        return static_cast<void*>(const_cast< RadiazioneReale*>(this));
    return QwtPlot::qt_metacast(_clname);
}

int RadiazioneReale::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QwtPlot::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: unitChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: computeDone(); break;
        case 2: swapUnit(); break;
        case 3: exportPDF(); break;
        case 4: drawRefCurve((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: redraw(); break;
        case 6: popUpMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 7: printOut(); break;
        case 8: exportSVG(); break;
        case 9: exportTXT(); break;
        case 10: exportPNG(); break;
        case 11: moved((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 12: settings(); break;
        case 13: updateSet(); break;
        default: ;
        }
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void RadiazioneReale::unitChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RadiazioneReale::computeDone()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
