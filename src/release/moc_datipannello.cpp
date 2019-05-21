/****************************************************************************
** Meta object code from reading C++ file 'datipannello.h'
**
** Created: Sat 6. Apr 22:48:46 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../datipannello.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'datipannello.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DatiPannello[] = {

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
      20,   13,   14,   13, 0x0a,
      39,   13,   13,   13, 0x08,
      53,   13,   13,   13, 0x08,
      70,   68,   13,   13, 0x08,
      88,   13,   13,   13, 0x08,
     105,  103,   13,   13, 0x08,
     130,   13,   13,   13, 0x08,
     142,   13,   13,   13, 0x08,
     160,   13,   13,   13, 0x08,
     171,  103,   13,   13, 0x08,
     191,  189,   13,   13, 0x08,
     210,  189,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DatiPannello[] = {
    "DatiPannello\0\0panel\0getSelectedPanel()\0"
    "deleteMarca()\0setupActions()\0a\0"
    "popUpMenu(QPoint)\0submitChange()\0i\0"
    "enableApply(QModelIndex)\0deleteRow()\0"
    "initializeModel()\0getPanel()\0"
    "beforeUpdate(int)\0s\0setFilter(QString)\0"
    "setFilter(QModelIndex)\0"
};

const QMetaObject DatiPannello::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DatiPannello,
      qt_meta_data_DatiPannello, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DatiPannello::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DatiPannello::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DatiPannello::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DatiPannello))
        return static_cast<void*>(const_cast< DatiPannello*>(this));
    if (!strcmp(_clname, "Ui::DatiPannello"))
        return static_cast< Ui::DatiPannello*>(const_cast< DatiPannello*>(this));
    return QDialog::qt_metacast(_clname);
}

int DatiPannello::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { panel _r = getSelectedPanel();
            if (_a[0]) *reinterpret_cast< panel*>(_a[0]) = _r; }  break;
        case 1: deleteMarca(); break;
        case 2: setupActions(); break;
        case 3: popUpMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 4: submitChange(); break;
        case 5: enableApply((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 6: deleteRow(); break;
        case 7: initializeModel(); break;
        case 8: getPanel(); break;
        case 9: beforeUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: setFilter((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: setFilter((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
