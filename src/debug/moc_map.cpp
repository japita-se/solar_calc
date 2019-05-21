/****************************************************************************
** Meta object code from reading C++ file 'map.h'
**
** Created: Sun 7. Apr 21:25:12 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../map.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'map.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Map[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
       5,    4,    4,    4, 0x05,
      17,    4,    4,    4, 0x05,
      32,   26,    4,    4, 0x05,

 // slots: signature, parameters, type, tag, flags
      81,    4,   73,    4, 0x0a,
      91,    4,    4,    4, 0x0a,
     102,    4,    4,    4, 0x0a,
     116,    4,    4,    4, 0x0a,
     143,  123,    4,    4, 0x0a,
     178,    4,    4,    4, 0x0a,
     211,    4,    4,    4, 0x0a,
     241,    4,    4,    4, 0x0a,
     259,    4,    4,    4, 0x0a,
     287,  283,    4,    4, 0x0a,
     325,  318,    4,    4, 0x0a,
     346,    4,    4,    4, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Map[] = {
    "Map\0\0reloadMap()\0reload()\0a,b,s\0"
    "coordinatesReady(double,double,QString&)\0"
    "QString\0getName()\0waitPage()\0examinePage()\0"
    "test()\0latitude,longitud,n\0"
    "setValues(QString,QString,QString)\0"
    "populateJavaScriptWindowObject()\0"
    "replyFinished(QNetworkReply*)\0"
    "loadCoordinates()\0loadCoordinatesSignal()\0"
    "a,b\0loadCoordinates(double,double)\0"
    "a,mode\0geoCode(QString,int)\0"
    "clearCoordinates()\0"
};

const QMetaObject Map::staticMetaObject = {
    { &QWebView::staticMetaObject, qt_meta_stringdata_Map,
      qt_meta_data_Map, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Map::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Map::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Map::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Map))
        return static_cast<void*>(const_cast< Map*>(this));
    return QWebView::qt_metacast(_clname);
}

int Map::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWebView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: reloadMap(); break;
        case 1: reload(); break;
        case 2: coordinatesReady((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 3: { QString _r = getName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 4: waitPage(); break;
        case 5: examinePage(); break;
        case 6: test(); break;
        case 7: setValues((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 8: populateJavaScriptWindowObject(); break;
        case 9: replyFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 10: loadCoordinates(); break;
        case 11: loadCoordinatesSignal(); break;
        case 12: loadCoordinates((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 13: geoCode((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 14: clearCoordinates(); break;
        default: ;
        }
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void Map::reloadMap()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Map::reload()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void Map::coordinatesReady(double _t1, double _t2, QString & _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
