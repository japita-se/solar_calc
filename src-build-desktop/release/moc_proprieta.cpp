/****************************************************************************
** Meta object code from reading C++ file 'proprieta.h'
**
** Created: Mon 25. Oct 20:56:08 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/proprieta.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'proprieta.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Proprieta[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   11,   10,   10, 0x0a,
      31,   10,   10,   10, 0x0a,
      55,   53,   10,   10, 0x0a,
      77,   11,   10,   10, 0x0a,
      97,   11,   10,   10, 0x0a,
     117,   11,   10,   10, 0x0a,
     141,   53,   10,   10, 0x0a,
     157,   11,   10,   10, 0x0a,
     174,   53,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Proprieta[] = {
    "Proprieta\0\0a\0enableProxy(bool)\0"
    "updateNumOfDecimals()\0i\0setNumOfDecimals(int)\0"
    "updateHost(QString)\0updateUser(QString)\0"
    "updatePassword(QString)\0updateType(int)\0"
    "updatePorta(int)\0updateLang(int)\0"
};

const QMetaObject Proprieta::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Proprieta,
      qt_meta_data_Proprieta, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Proprieta::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Proprieta::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Proprieta::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Proprieta))
        return static_cast<void*>(const_cast< Proprieta*>(this));
    if (!strcmp(_clname, "Ui::Proprieta"))
        return static_cast< Ui::Proprieta*>(const_cast< Proprieta*>(this));
    return QDialog::qt_metacast(_clname);
}

int Proprieta::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: enableProxy((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: updateNumOfDecimals(); break;
        case 2: setNumOfDecimals((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: updateHost((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: updateUser((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: updatePassword((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: updateType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: updatePorta((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: updateLang((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
