/****************************************************************************
** Meta object code from reading C++ file 'gridset.h'
**
** Created: Sun 7. Apr 21:24:28 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gridset.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gridset.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GridSet[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,    9,    8,    8, 0x08,
      28,    9,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GridSet[] = {
    "GridSet\0\0i\0updateAsseX(int)\0"
    "updateAsseY(int)\0"
};

const QMetaObject GridSet::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_GridSet,
      qt_meta_data_GridSet, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GridSet::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GridSet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GridSet::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GridSet))
        return static_cast<void*>(const_cast< GridSet*>(this));
    if (!strcmp(_clname, "Ui::GridSet"))
        return static_cast< Ui::GridSet*>(const_cast< GridSet*>(this));
    return QDialog::qt_metacast(_clname);
}

int GridSet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateAsseX((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: updateAsseY((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
