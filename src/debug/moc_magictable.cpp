/****************************************************************************
** Meta object code from reading C++ file 'magictable.h'
**
** Created: Sun 7. Apr 21:27:06 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../magictable.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'magictable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MagicTable[] = {

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
      12,   11,   11,   11, 0x08,
      30,   28,   11,   11, 0x08,
      50,   48,   11,   11, 0x08,
      76,   11,   11,   11, 0x08,
      89,   11,   11,   11, 0x08,
     102,   11,   11,   11, 0x08,
     113,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MagicTable[] = {
    "MagicTable\0\0clearSelected()\0a\0"
    "popUpMenu(QPoint)\0i\0update(QTableWidgetItem*)\0"
    "uniformize()\0clearTable()\0setTable()\0"
    "updateTable()\0"
};

const QMetaObject MagicTable::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MagicTable,
      qt_meta_data_MagicTable, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MagicTable::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MagicTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MagicTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MagicTable))
        return static_cast<void*>(const_cast< MagicTable*>(this));
    if (!strcmp(_clname, "Ui::MagicTable"))
        return static_cast< Ui::MagicTable*>(const_cast< MagicTable*>(this));
    return QDialog::qt_metacast(_clname);
}

int MagicTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clearSelected(); break;
        case 1: popUpMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 2: update((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 3: uniformize(); break;
        case 4: clearTable(); break;
        case 5: setTable(); break;
        case 6: updateTable(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE