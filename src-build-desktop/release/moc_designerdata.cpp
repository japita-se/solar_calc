/****************************************************************************
** Meta object code from reading C++ file 'designerdata.h'
**
** Created: Mon 25. Oct 20:57:16 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/designerdata.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'designerdata.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DesignerData[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      26,   24,   13,   13, 0x0a,
      51,   24,   13,   13, 0x0a,
      76,   24,   13,   13, 0x0a,
      91,   24,   13,   13, 0x0a,
     114,   24,   13,   13, 0x0a,
     140,   24,   13,   13, 0x0a,
     158,   13,   13,   13, 0x0a,
     169,   24,   13,   13, 0x0a,
     186,   24,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DesignerData[] = {
    "DesignerData\0\0isDirty()\0a\0"
    "setDesignerName(QString)\0"
    "setReviewerName(QString)\0setDate(QDate)\0"
    "setClientName(QString)\0setClientAddress(QString)\0"
    "setTitle(QString)\0setNotes()\0"
    "setAlbo(QString)\0setCompany(QString)\0"
};

const QMetaObject DesignerData::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DesignerData,
      qt_meta_data_DesignerData, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DesignerData::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DesignerData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DesignerData::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DesignerData))
        return static_cast<void*>(const_cast< DesignerData*>(this));
    if (!strcmp(_clname, "Ui::formDesigner"))
        return static_cast< Ui::formDesigner*>(const_cast< DesignerData*>(this));
    return QWidget::qt_metacast(_clname);
}

int DesignerData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: isDirty(); break;
        case 1: setDesignerName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: setReviewerName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: setDate((*reinterpret_cast< QDate(*)>(_a[1]))); break;
        case 4: setClientName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: setClientAddress((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: setTitle((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: setNotes(); break;
        case 8: setAlbo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: setCompany((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void DesignerData::isDirty()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
