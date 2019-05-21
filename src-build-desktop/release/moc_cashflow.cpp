/****************************************************************************
** Meta object code from reading C++ file 'cashflow.h'
**
** Created: Mon 25. Oct 20:56:39 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/cashflow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cashflow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CashFlowPlot[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      28,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      34,   28,   13,   13, 0x08,
      58,   13,   13,   13, 0x08,
      77,   75,   13,   13, 0x08,
      93,   13,   13,   13, 0x08,
     104,   13,   13,   13, 0x08,
     116,   13,   13,   13, 0x08,
     131,   13,   13,   13, 0x08,
     145,  141,   13,   13, 0x08,
     162,  141,   13,   13, 0x08,
     179,   13,   13,   13, 0x08,
     194,  192,   13,   13, 0x08,
     209,   13,   13,   13, 0x08,
     224,   13,   13,   13, 0x08,
     239,  192,   13,   13, 0x08,
     254,   13,   13,   13, 0x08,
     269,   13,   13,   13, 0x08,
     284,  192,   13,   13, 0x08,
     298,   13,   13,   13, 0x08,
     312,   13,   13,   13, 0x08,
     326,  192,   13,   13, 0x08,
     341,   13,   13,   13, 0x08,
     356,   13,   13,   13, 0x08,
     371,  192,   13,   13, 0x08,
     386,   13,   13,   13, 0x08,
     401,   13,   13,   13, 0x08,
     418,  416,   13,   13, 0x08,
     436,  416,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CashFlowPlot[] = {
    "CashFlowPlot\0\0updateTable()\0state\0"
    "toggleInterestPlot(int)\0changeDrawData()\0"
    "s\0changeDraw(int)\0settings()\0updateSet()\0"
    "updateSetVan()\0gridset()\0pos\0"
    "movedMOL(QPoint)\0movedVAN(QPoint)\0"
    "updateGrid()\0w\0exportPNG(int)\0"
    "exportMOLPNG()\0exportVANPNG()\0"
    "exportSVG(int)\0exportMOLSVG()\0"
    "exportVANSVG()\0printOut(int)\0printOutMOL()\0"
    "printOutVAN()\0exportPDF(int)\0"
    "exportMOLPDF()\0exportVANPDF()\0"
    "exportTXT(int)\0exportMOLTXT()\0"
    "exportVANTXT()\0p\0popUpMenu(QPoint)\0"
    "popUpMenuVAN(QPoint)\0"
};

const QMetaObject CashFlowPlot::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CashFlowPlot,
      qt_meta_data_CashFlowPlot, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CashFlowPlot::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CashFlowPlot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CashFlowPlot::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CashFlowPlot))
        return static_cast<void*>(const_cast< CashFlowPlot*>(this));
    if (!strcmp(_clname, "Ui::widgetCashFlow"))
        return static_cast< Ui::widgetCashFlow*>(const_cast< CashFlowPlot*>(this));
    return QWidget::qt_metacast(_clname);
}

int CashFlowPlot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateTable(); break;
        case 1: toggleInterestPlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: changeDrawData(); break;
        case 3: changeDraw((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: settings(); break;
        case 5: updateSet(); break;
        case 6: updateSetVan(); break;
        case 7: gridset(); break;
        case 8: movedMOL((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 9: movedVAN((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 10: updateGrid(); break;
        case 11: exportPNG((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: exportMOLPNG(); break;
        case 13: exportVANPNG(); break;
        case 14: exportSVG((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: exportMOLSVG(); break;
        case 16: exportVANSVG(); break;
        case 17: printOut((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: printOutMOL(); break;
        case 19: printOutVAN(); break;
        case 20: exportPDF((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: exportMOLPDF(); break;
        case 22: exportVANPDF(); break;
        case 23: exportTXT((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: exportMOLTXT(); break;
        case 25: exportVANTXT(); break;
        case 26: popUpMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 27: popUpMenuVAN((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 28;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
