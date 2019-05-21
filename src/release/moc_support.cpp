/****************************************************************************
** Meta object code from reading C++ file 'support.h'
**
** Created: Sat 6. Apr 22:50:12 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../support.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'support.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Support[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,
      34,   28,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      71,    8,    8,    8, 0x08,
      94,   88,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Support[] = {
    "Support\0\0coordinatesValid()\0a,b,c\0"
    "pointChanged(double,double,QString&)\0"
    "setCoordinates()\0a,b,s\0"
    "updatePoint(double,double,QString&)\0"
};

const QMetaObject Support::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Support,
      qt_meta_data_Support, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Support::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Support::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Support::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Support))
        return static_cast<void*>(const_cast< Support*>(this));
    return QWidget::qt_metacast(_clname);
}

int Support::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: coordinatesValid(); break;
        case 1: pointChanged((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 2: setCoordinates(); break;
        case 3: updatePoint((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Support::coordinatesValid()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Support::pointChanged(double _t1, double _t2, QString & _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
