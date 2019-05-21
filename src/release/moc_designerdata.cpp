/****************************************************************************
** Meta object code from reading C++ file 'designerdata.h'
**
** Created: Sat 6. Apr 22:51:00 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../designerdata.h"
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
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      26,   24,   13,   13, 0x0a,
      47,   24,   13,   13, 0x0a,
      72,   24,   13,   13, 0x0a,
      97,   24,   13,   13, 0x0a,
     112,   24,   13,   13, 0x0a,
     135,   24,   13,   13, 0x0a,
     161,   24,   13,   13, 0x0a,
     179,   13,   13,   13, 0x0a,
     190,   24,   13,   13, 0x0a,
     207,   24,   13,   13, 0x0a,
     227,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DesignerData[] = {
    "DesignerData\0\0isDirty()\0a\0"
    "setLogoPath(QString)\0setDesignerName(QString)\0"
    "setReviewerName(QString)\0setDate(QDate)\0"
    "setClientName(QString)\0setClientAddress(QString)\0"
    "setTitle(QString)\0setNotes()\0"
    "setAlbo(QString)\0setCompany(QString)\0"
    "loadLogo()\0"
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
        case 1: setLogoPath((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: setDesignerName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: setReviewerName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: setDate((*reinterpret_cast< QDate(*)>(_a[1]))); break;
        case 5: setClientName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: setClientAddress((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: setTitle((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: setNotes(); break;
        case 9: setAlbo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: setCompany((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: loadLogo(); break;
        default: ;
        }
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void DesignerData::isDirty()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
