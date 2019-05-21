/****************************************************************************
** Meta object code from reading C++ file 'documentedit.h'
**
** Created: Mon 25. Oct 20:57:07 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/documentedit.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'documentedit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DocumentEdit[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      31,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   14,   13,   13, 0x0a,
      41,   39,   13,   13, 0x0a,
      65,   39,   13,   13, 0x0a,
      89,   13,   13,   13, 0x08,
     107,   13,   13,   13, 0x08,
     118,   13,   13,   13, 0x08,
     139,   13,  131,   13, 0x08,
     154,   13,   13,   13, 0x08,
     168,   13,   13,   13, 0x08,
     178,   13,   13,   13, 0x08,
     194,   13,  189,   13, 0x08,
     205,   13,  189,   13, 0x08,
     218,   13,   13,   13, 0x08,
     230,   13,   13,   13, 0x08,
     249,   13,   13,   13, 0x08,
     264,   13,   13,   13, 0x08,
     270,   13,   13,   13, 0x08,
     277,   13,   13,   13, 0x08,
     285,   13,   13,   13, 0x08,
     293,   13,   13,   13, 0x08,
     304,   13,   13,   13, 0x08,
     320,   13,   13,   13, 0x08,
     335,  333,   13,   13, 0x08,
     357,  355,   13,   13, 0x08,
     386,  375,   13,   13, 0x08,
     401,   13,   13,   13, 0x08,
     413,   39,   13,   13, 0x08,
     440,  433,   13,   13, 0x08,
     482,   13,   13,   13, 0x08,
     506,   13,   13,   13, 0x08,
     529,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DocumentEdit[] = {
    "DocumentEdit\0\0de\0setDesigner(designer)\0"
    "a\0setHeaderText(QString&)\0"
    "setFooterText(QString&)\0loadModGenerale()\0"
    "loadEnel()\0loadTSheet()\0Editor*\0"
    "createEditor()\0updateMenus()\0fileNew()\0"
    "fileOpen()\0bool\0fileSave()\0fileSaveAs()\0"
    "filePrint()\0filePrintPreview()\0"
    "filePrintPdf()\0cut()\0copy()\0paste()\0"
    "image()\0textBold()\0textUnderline()\0"
    "textItalic()\0f\0textFamily(QString)\0p\0"
    "textSize(QString)\0styleIndex\0"
    "textStyle(int)\0textColor()\0"
    "textAlign(QAction*)\0format\0"
    "currentCharFormatChanged(QTextCharFormat)\0"
    "cursorPositionChanged()\0clipboardDataChanged()\0"
    "printPreview(QPrinter*)\0"
};

const QMetaObject DocumentEdit::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_DocumentEdit,
      qt_meta_data_DocumentEdit, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DocumentEdit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DocumentEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DocumentEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DocumentEdit))
        return static_cast<void*>(const_cast< DocumentEdit*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int DocumentEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setDesigner((*reinterpret_cast< designer(*)>(_a[1]))); break;
        case 1: setHeaderText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: setFooterText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: loadModGenerale(); break;
        case 4: loadEnel(); break;
        case 5: loadTSheet(); break;
        case 6: { Editor* _r = createEditor();
            if (_a[0]) *reinterpret_cast< Editor**>(_a[0]) = _r; }  break;
        case 7: updateMenus(); break;
        case 8: fileNew(); break;
        case 9: fileOpen(); break;
        case 10: { bool _r = fileSave();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 11: { bool _r = fileSaveAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 12: filePrint(); break;
        case 13: filePrintPreview(); break;
        case 14: filePrintPdf(); break;
        case 15: cut(); break;
        case 16: copy(); break;
        case 17: paste(); break;
        case 18: image(); break;
        case 19: textBold(); break;
        case 20: textUnderline(); break;
        case 21: textItalic(); break;
        case 22: textFamily((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 23: textSize((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 24: textStyle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: textColor(); break;
        case 26: textAlign((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 27: currentCharFormatChanged((*reinterpret_cast< const QTextCharFormat(*)>(_a[1]))); break;
        case 28: cursorPositionChanged(); break;
        case 29: clipboardDataChanged(); break;
        case 30: printPreview((*reinterpret_cast< QPrinter*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 31;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
