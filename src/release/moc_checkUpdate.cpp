/****************************************************************************
** Meta object code from reading C++ file 'checkUpdate.h'
**
** Created: Sat 6. Apr 22:51:14 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../checkUpdate.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'checkUpdate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CheckUpdate[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   13,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      28,   26,   12,   12, 0x08,
      57,   53,   45,   12, 0x08,
      95,   81,   76,   12, 0x08,
     132,  126,   12,   12, 0x08,
     165,   13,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CheckUpdate[] = {
    "CheckUpdate\0\0a\0done(bool)\0i\0"
    "updateStart(int)\0QString\0url\0"
    "saveFileName(QUrl)\0bool\0filename,data\0"
    "saveToDisk(QString,QIODevice*)\0reply\0"
    "downloadFinished(QNetworkReply*)\0"
    "checkVersion(QString&)\0"
};

const QMetaObject CheckUpdate::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CheckUpdate,
      qt_meta_data_CheckUpdate, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CheckUpdate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CheckUpdate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CheckUpdate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CheckUpdate))
        return static_cast<void*>(const_cast< CheckUpdate*>(this));
    if (!strcmp(_clname, "Ui::CheckUpdate"))
        return static_cast< Ui::CheckUpdate*>(const_cast< CheckUpdate*>(this));
    return QDialog::qt_metacast(_clname);
}

int CheckUpdate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: done((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: updateStart((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: { QString _r = saveFileName((*reinterpret_cast< const QUrl(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 3: { bool _r = saveToDisk((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QIODevice*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: downloadFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 5: checkVersion((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void CheckUpdate::done(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
