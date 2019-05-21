/****************************************************************************
** Meta object code from reading C++ file 'load.h'
**
** Created: Sat 6. Apr 22:49:28 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../load.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'load.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Load[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      39,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x05,

 // slots: signature, parameters, type, tag, flags
      16,    5,    5,    5, 0x0a,
      25,    5,    5,    5, 0x0a,
      32,    5,    5,    5, 0x0a,
      39,    5,    5,    5, 0x0a,
      50,   48,    5,    5, 0x0a,
      73,   48,    5,    5, 0x0a,
      95,    5,    5,    5, 0x0a,
     108,    5,    5,    5, 0x08,
     124,    5,    5,    5, 0x08,
     145,    5,    5,    5, 0x08,
     158,    5,    5,    5, 0x08,
     176,    5,    5,    5, 0x08,
     186,    5,    5,    5, 0x08,
     203,  201,    5,    5, 0x08,
     225,  201,    5,    5, 0x08,
     251,  247,    5,    5, 0x08,
     273,    5,    5,    5, 0x08,
     289,  287,    5,    5, 0x08,
     320,    5,    5,    5, 0x08,
     347,   48,    5,    5, 0x08,
     365,  363,    5,    5, 0x08,
     387,  363,    5,    5, 0x08,
     409,    5,    5,    5, 0x08,
     426,  420,    5,    5, 0x08,
     448,    5,    5,    5, 0x08,
     468,  420,    5,    5, 0x08,
     490,  363,    5,    5, 0x08,
     519,  363,    5,    5, 0x08,
     562,  554,    5,    5, 0x08,
     591,    5,    5,    5, 0x08,
     605,    5,    5,    5, 0x08,
     622,    5,    5,    5, 0x08,
     638,    5,    5,    5, 0x08,
     647,    5,    5,    5, 0x08,
     664,  662,    5,    5, 0x08,
     702,  695,    5,    5, 0x08,
     737,    5,    5,    5, 0x08,
     757,    5,    5,    5, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Load[] = {
    "Load\0\0updated()\0notify()\0load()\0save()\0"
    "saveAs()\0i\0setMonthlyProfile(int)\0"
    "setHourlyProfile(int)\0setDefault()\0"
    "clearSelected()\0clearSelectedHours()\0"
    "uniformize()\0uniformizeHours()\0popMenu()\0"
    "popMenuHours()\0m\0setSatNormOption(int)\0"
    "setSunNormOption(int)\0m,y\0"
    "updateQuotas(int,int)\0updateTitle()\0"
    "t\0updateHoursProfileDetails(int)\0"
    "updateHoursFromSelection()\0setRestDay(int)\0"
    "c\0setSunPercent(double)\0setSatPercent(double)\0"
    "settings()\0month\0updateWeeklyPlot(int)\0"
    "updateMonthlyPlot()\0updateHourlyPlot(int)\0"
    "storeItem(QTableWidgetItem*)\0"
    "checkHourlyData(QTableWidgetItem*)\0"
    "current\0checkData(QTableWidgetItem*)\0"
    "saveProfile()\0montlhyChanged()\0"
    "hourlyChanged()\0update()\0updateMonths()\0"
    "a\0updateHours(QTableWidgetItem*)\0"
    "a,mode\0updateHours(QTableWidgetItem*,int)\0"
    "updateHourlyItems()\0updateMonthlyItems()\0"
};

const QMetaObject Load::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Load,
      qt_meta_data_Load, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Load::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Load::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Load::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Load))
        return static_cast<void*>(const_cast< Load*>(this));
    if (!strcmp(_clname, "Ui::widgetConsumi"))
        return static_cast< Ui::widgetConsumi*>(const_cast< Load*>(this));
    return QWidget::qt_metacast(_clname);
}

int Load::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updated(); break;
        case 1: notify(); break;
        case 2: load(); break;
        case 3: save(); break;
        case 4: saveAs(); break;
        case 5: setMonthlyProfile((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: setHourlyProfile((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: setDefault(); break;
        case 8: clearSelected(); break;
        case 9: clearSelectedHours(); break;
        case 10: uniformize(); break;
        case 11: uniformizeHours(); break;
        case 12: popMenu(); break;
        case 13: popMenuHours(); break;
        case 14: setSatNormOption((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: setSunNormOption((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: updateQuotas((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 17: updateTitle(); break;
        case 18: updateHoursProfileDetails((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: updateHoursFromSelection(); break;
        case 20: setRestDay((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: setSunPercent((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 22: setSatPercent((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 23: settings(); break;
        case 24: updateWeeklyPlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: updateMonthlyPlot(); break;
        case 26: updateHourlyPlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: storeItem((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 28: checkHourlyData((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 29: checkData((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 30: saveProfile(); break;
        case 31: montlhyChanged(); break;
        case 32: hourlyChanged(); break;
        case 33: update(); break;
        case 34: updateMonths(); break;
        case 35: updateHours((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 36: updateHours((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 37: updateHourlyItems(); break;
        case 38: updateMonthlyItems(); break;
        default: ;
        }
        _id -= 39;
    }
    return _id;
}

// SIGNAL 0
void Load::updated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
