/****************************************************************************
** Meta object code from reading C++ file 'surfacewidget.h'
**
** Created: Mon 25. Oct 20:56:33 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/surfacewidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'surfacewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SurfaceWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      27,   25,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SurfaceWidget[] = {
    "SurfaceWidget\0\0swapped()\0i\0setType(int)\0"
};

const QMetaObject SurfaceWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SurfaceWidget,
      qt_meta_data_SurfaceWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SurfaceWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SurfaceWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SurfaceWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SurfaceWidget))
        return static_cast<void*>(const_cast< SurfaceWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int SurfaceWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: swapped(); break;
        case 1: setType((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void SurfaceWidget::swapped()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
