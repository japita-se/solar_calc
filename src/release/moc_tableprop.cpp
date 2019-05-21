/****************************************************************************
** Meta object code from reading C++ file 'tableprop.h'
**
** Created: Sat 6. Apr 22:51:04 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../tableprop.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tableprop.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_tableprop[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   11,   10,   10, 0x08,
      28,   11,   10,   10, 0x08,
      43,   11,   10,   10, 0x08,
      61,   11,   10,   10, 0x08,
      78,   11,   10,   10, 0x08,
      95,   11,   10,   10, 0x08,
     118,   11,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_tableprop[] = {
    "tableprop\0\0a\0updateRow(int)\0updateCol(int)\0"
    "updateBorder(int)\0updateAlign(int)\0"
    "updateWidth(int)\0updateCellSpacing(int)\0"
    "updateCellPadding(int)\0"
};

const QMetaObject tableprop::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_tableprop,
      qt_meta_data_tableprop, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &tableprop::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *tableprop::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *tableprop::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_tableprop))
        return static_cast<void*>(const_cast< tableprop*>(this));
    if (!strcmp(_clname, "Ui::tableprop"))
        return static_cast< Ui::tableprop*>(const_cast< tableprop*>(this));
    return QDialog::qt_metacast(_clname);
}

int tableprop::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateRow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: updateCol((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: updateBorder((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: updateAlign((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: updateWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: updateCellSpacing((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: updateCellPadding((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
