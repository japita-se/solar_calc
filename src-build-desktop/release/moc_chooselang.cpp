/****************************************************************************
** Meta object code from reading C++ file 'chooselang.h'
**
** Created: Mon 25. Oct 20:54:49 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/chooselang.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chooselang.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ChooseLang[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   12,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ChooseLang[] = {
    "ChooseLang\0\0i\0setLang(int)\0"
};

const QMetaObject ChooseLang::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ChooseLang,
      qt_meta_data_ChooseLang, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ChooseLang::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ChooseLang::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ChooseLang::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ChooseLang))
        return static_cast<void*>(const_cast< ChooseLang*>(this));
    if (!strcmp(_clname, "Ui::ChooseLang"))
        return static_cast< Ui::ChooseLang*>(const_cast< ChooseLang*>(this));
    return QDialog::qt_metacast(_clname);
}

int ChooseLang::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setLang((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
