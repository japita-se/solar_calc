/****************************************************************************
** Meta object code from reading C++ file 'simecooptions.h'
**
** Created: Mon 25. Oct 20:56:55 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/simecooptions.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'simecooptions.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SimEcoOptions[] = {

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
      15,   14,   14,   14, 0x08,
      34,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SimEcoOptions[] = {
    "SimEcoOptions\0\0changeOptionsMOL()\0"
    "changeOptionsVAN()\0"
};

const QMetaObject SimEcoOptions::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SimEcoOptions,
      qt_meta_data_SimEcoOptions, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SimEcoOptions::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SimEcoOptions::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SimEcoOptions::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SimEcoOptions))
        return static_cast<void*>(const_cast< SimEcoOptions*>(this));
    if (!strcmp(_clname, "Ui::dialogSimOptions"))
        return static_cast< Ui::dialogSimOptions*>(const_cast< SimEcoOptions*>(this));
    return QDialog::qt_metacast(_clname);
}

int SimEcoOptions::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: changeOptionsMOL(); break;
        case 1: changeOptionsVAN(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
