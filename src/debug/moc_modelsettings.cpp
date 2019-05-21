/****************************************************************************
** Meta object code from reading C++ file 'modelsettings.h'
**
** Created: Sun 7. Apr 21:25:15 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../modelsettings.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modelsettings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModelSettings[] = {

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
      17,   15,   14,   14, 0x08,
      33,   15,   14,   14, 0x08,
      56,   15,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ModelSettings[] = {
    "ModelSettings\0\0i\0updateView(int)\0"
    "setModelSettings(bool)\0setOmbreSettings(bool)\0"
};

const QMetaObject ModelSettings::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ModelSettings,
      qt_meta_data_ModelSettings, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModelSettings::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModelSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModelSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModelSettings))
        return static_cast<void*>(const_cast< ModelSettings*>(this));
    if (!strcmp(_clname, "Ui::ModelSettings"))
        return static_cast< Ui::ModelSettings*>(const_cast< ModelSettings*>(this));
    return QDialog::qt_metacast(_clname);
}

int ModelSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateView((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: setModelSettings((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: setOmbreSettings((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
