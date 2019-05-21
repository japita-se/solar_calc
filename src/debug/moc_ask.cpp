/****************************************************************************
** Meta object code from reading C++ file 'ask.h'
**
** Created: Sun 7. Apr 21:27:09 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ask.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ask.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Ask[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       5,    4,    4,    4, 0x08,
      27,    4,    4,    4, 0x08,
      42,    4,    4,    4, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Ask[] = {
    "Ask\0\0setOnlyCurrentMonth()\0setAllMonths()\0"
    "setDoNotAsk()\0"
};

const QMetaObject Ask::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Ask,
      qt_meta_data_Ask, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Ask::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Ask::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Ask::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Ask))
        return static_cast<void*>(const_cast< Ask*>(this));
    if (!strcmp(_clname, "Ui::Ask"))
        return static_cast< Ui::Ask*>(const_cast< Ask*>(this));
    return QDialog::qt_metacast(_clname);
}

int Ask::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setOnlyCurrentMonth(); break;
        case 1: setAllMonths(); break;
        case 2: setDoNotAsk(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
