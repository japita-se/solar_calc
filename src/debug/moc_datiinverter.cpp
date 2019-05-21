/****************************************************************************
** Meta object code from reading C++ file 'datiinverter.h'
**
** Created: Sun 7. Apr 21:23:56 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../datiinverter.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'datiinverter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DatiInverter[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   13,   14,   13, 0x0a,
      45,   13,   13,   13, 0x08,
      59,   13,   13,   13, 0x08,
      76,   74,   13,   13, 0x08,
      94,   13,   13,   13, 0x08,
     111,  109,   13,   13, 0x08,
     136,   13,   13,   13, 0x08,
     148,   13,   13,   13, 0x08,
     166,   13,   13,   13, 0x08,
     184,  180,   13,   13, 0x08,
     216,  214,   13,   13, 0x08,
     235,   74,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DatiInverter[] = {
    "DatiInverter\0\0inverter\0getSelectedInverter()\0"
    "deleteMarca()\0setupActions()\0a\0"
    "popUpMenu(QPoint)\0submitChange()\0i\0"
    "enableApply(QModelIndex)\0deleteRow()\0"
    "initializeModel()\0getInverter()\0i,r\0"
    "beforeUpdate(int,QSqlRecord&)\0s\0"
    "setFilter(QString)\0setFilter(QModelIndex)\0"
};

const QMetaObject DatiInverter::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DatiInverter,
      qt_meta_data_DatiInverter, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DatiInverter::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DatiInverter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DatiInverter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DatiInverter))
        return static_cast<void*>(const_cast< DatiInverter*>(this));
    if (!strcmp(_clname, "Ui::DatiInverter"))
        return static_cast< Ui::DatiInverter*>(const_cast< DatiInverter*>(this));
    return QDialog::qt_metacast(_clname);
}

int DatiInverter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { inverter _r = getSelectedInverter();
            if (_a[0]) *reinterpret_cast< inverter*>(_a[0]) = _r; }  break;
        case 1: deleteMarca(); break;
        case 2: setupActions(); break;
        case 3: popUpMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 4: submitChange(); break;
        case 5: enableApply((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 6: deleteRow(); break;
        case 7: initializeModel(); break;
        case 8: getInverter(); break;
        case 9: beforeUpdate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QSqlRecord(*)>(_a[2]))); break;
        case 10: setFilter((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: setFilter((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
