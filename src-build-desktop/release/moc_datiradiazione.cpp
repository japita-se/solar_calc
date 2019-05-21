/****************************************************************************
** Meta object code from reading C++ file 'datiradiazione.h'
**
** Created: Mon 25. Oct 20:55:03 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/datiradiazione.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'datiradiazione.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DatiRadiazione[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      34,   15,   15,   15, 0x0a,
      47,   45,   15,   15, 0x08,
      64,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DatiRadiazione[] = {
    "DatiRadiazione\0\0sorgenteChanged()\0"
    "setDirty()\0i\0emitSignal(bool)\0"
    "on_pushCarica_clicked()\0"
};

const QMetaObject DatiRadiazione::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DatiRadiazione,
      qt_meta_data_DatiRadiazione, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DatiRadiazione::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DatiRadiazione::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DatiRadiazione::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DatiRadiazione))
        return static_cast<void*>(const_cast< DatiRadiazione*>(this));
    if (!strcmp(_clname, "Ui::DatiRadiazione"))
        return static_cast< Ui::DatiRadiazione*>(const_cast< DatiRadiazione*>(this));
    return QDialog::qt_metacast(_clname);
}

int DatiRadiazione::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sorgenteChanged(); break;
        case 1: setDirty(); break;
        case 2: emitSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: on_pushCarica_clicked(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void DatiRadiazione::sorgenteChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
