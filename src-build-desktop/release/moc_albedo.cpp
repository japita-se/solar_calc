/****************************************************************************
** Meta object code from reading C++ file 'albedo.h'
**
** Created: Mon 25. Oct 20:54:47 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/albedo.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'albedo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Albedo[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    8,    7,    7, 0x08,
      27,    7,    7,    7, 0x08,
      43,    7,    7,    7, 0x08,
      57,   55,    7,    7, 0x08,
      80,   55,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Albedo[] = {
    "Albedo\0\0i\0enableSnow(bool)\0setAlbedoType()\0"
    "setAlbedo()\0m\0setAlbedo(QModelIndex)\0"
    "setAlbedoAndExit(QModelIndex)\0"
};

const QMetaObject Albedo::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Albedo,
      qt_meta_data_Albedo, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Albedo::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Albedo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Albedo::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Albedo))
        return static_cast<void*>(const_cast< Albedo*>(this));
    if (!strcmp(_clname, "Ui::Albedo"))
        return static_cast< Ui::Albedo*>(const_cast< Albedo*>(this));
    return QDialog::qt_metacast(_clname);
}

int Albedo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: enableSnow((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: setAlbedoType(); break;
        case 2: setAlbedo(); break;
        case 3: setAlbedo((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: setAlbedoAndExit((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE