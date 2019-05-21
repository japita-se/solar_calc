/****************************************************************************
** Meta object code from reading C++ file 'inverterCheck.h'
**
** Created: Sun 7. Apr 21:26:12 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../inverterCheck.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'inverterCheck.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_InverterCheck[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      35,   33,   14,   14, 0x0a,
      58,   33,   14,   14, 0x0a,
      81,   14,   14,   14, 0x0a,
      92,   14,   14,   14, 0x0a,
     126,  110,  103,   14, 0x0a,
     156,   14,  152,   14, 0x0a,
     171,   14,   14,   14, 0x0a,
     181,   14,   14,   14, 0x08,
     198,   14,   14,   14, 0x08,
     216,  214,   14,   14, 0x08,
     239,   14,   14,   14, 0x08,
     258,   14,   14,   14, 0x08,
     272,   14,   14,   14, 0x08,
     285,   14,   14,   14, 0x08,
     303,  301,   14,   14, 0x08,
     323,  319,   14,   14, 0x08,
     350,   14,   14,   14, 0x08,
     367,   14,  362,   14, 0x08,
     386,   14,  379,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_InverterCheck[] = {
    "InverterCheck\0\0componentStatus()\0t\0"
    "minTempChanged(double)\0maxTempChanged(double)\0"
    "resetAll()\0checkAll()\0QPoint\0"
    "s,p,numinverter\0checkVoltage(int,int,int)\0"
    "int\0checkVoltage()\0suggest()\0"
    "chooseInverter()\0fillInverters()\0s\0"
    "enableSuggest(QString)\0updateComboModel()\0"
    "enableCheck()\0parseCampi()\0parsePannelli()\0"
    "i\0updateView(int)\0a,c\0test(QTreeWidgetItem*,int)\0"
    "warnLabel()\0bool\0updateLed()\0double\0"
    "installedPower()\0"
};

const QMetaObject InverterCheck::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_InverterCheck,
      qt_meta_data_InverterCheck, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &InverterCheck::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *InverterCheck::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *InverterCheck::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InverterCheck))
        return static_cast<void*>(const_cast< InverterCheck*>(this));
    if (!strcmp(_clname, "Ui::inverterCheck"))
        return static_cast< Ui::inverterCheck*>(const_cast< InverterCheck*>(this));
    return QWidget::qt_metacast(_clname);
}

int InverterCheck::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: componentStatus(); break;
        case 1: minTempChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: maxTempChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: resetAll(); break;
        case 4: checkAll(); break;
        case 5: { QPoint _r = checkVoltage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QPoint*>(_a[0]) = _r; }  break;
        case 6: { int _r = checkVoltage();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 7: suggest(); break;
        case 8: chooseInverter(); break;
        case 9: fillInverters(); break;
        case 10: enableSuggest((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: updateComboModel(); break;
        case 12: enableCheck(); break;
        case 13: parseCampi(); break;
        case 14: parsePannelli(); break;
        case 15: updateView((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: test((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 17: warnLabel(); break;
        case 18: { bool _r = updateLed();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 19: { double _r = installedPower();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void InverterCheck::componentStatus()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
