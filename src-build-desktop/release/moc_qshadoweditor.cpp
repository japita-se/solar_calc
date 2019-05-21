/****************************************************************************
** Meta object code from reading C++ file 'qshadoweditor.h'
**
** Created: Mon 25. Oct 20:56:10 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/qshadoweditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qshadoweditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QShadowEditor[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      31,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      47,   14,   14,   14, 0x08,
      56,   14,   14,   14, 0x08,
      69,   14,   14,   14, 0x08,
      84,   14,   14,   14, 0x08,
      95,   93,   14,   14, 0x08,
     107,   14,   14,   14, 0x08,
     119,   14,   14,   14, 0x08,
     140,  135,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QShadowEditor[] = {
    "QShadowEditor\0\0shadowChanged()\0"
    "tableResetted()\0delRow()\0clearTable()\0"
    "updateShadow()\0addRow()\0i\0addRow(int)\0"
    "updateExt()\0updateAndExit()\0item\0"
    "update(QTableWidgetItem*)\0"
};

const QMetaObject QShadowEditor::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QShadowEditor,
      qt_meta_data_QShadowEditor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QShadowEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QShadowEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QShadowEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QShadowEditor))
        return static_cast<void*>(const_cast< QShadowEditor*>(this));
    return QDialog::qt_metacast(_clname);
}

int QShadowEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: shadowChanged(); break;
        case 1: tableResetted(); break;
        case 2: delRow(); break;
        case 3: clearTable(); break;
        case 4: updateShadow(); break;
        case 5: addRow(); break;
        case 6: addRow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: updateExt(); break;
        case 8: updateAndExit(); break;
        case 9: update((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void QShadowEditor::shadowChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QShadowEditor::tableResetted()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
