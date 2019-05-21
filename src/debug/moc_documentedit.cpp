/****************************************************************************
** Meta object code from reading C++ file 'documentedit.h'
**
** Created: Sun 7. Apr 21:26:41 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../documentedit.h"
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
      34,   14, // methods
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
      99,   13,   13,   13, 0x08,
     117,   13,   13,   13, 0x08,
     132,   13,   13,   13, 0x08,
     143,   13,   13,   13, 0x08,
     164,   13,  156,   13, 0x08,
     179,   13,   13,   13, 0x08,
     193,   13,   13,   13, 0x08,
     203,   13,   13,   13, 0x08,
     214,   13,   13,   13, 0x08,
     225,   13,   13,   13, 0x08,
     238,   13,   13,   13, 0x08,
     250,   13,   13,   13, 0x08,
     269,   13,   13,   13, 0x08,
     284,   13,   13,   13, 0x08,
     290,   13,   13,   13, 0x08,
     297,   13,   13,   13, 0x08,
     305,   13,   13,   13, 0x08,
     313,   13,   13,   13, 0x08,
     321,   13,   13,   13, 0x08,
     332,   13,   13,   13, 0x08,
     348,   13,   13,   13, 0x08,
     363,  361,   13,   13, 0x08,
     385,  383,   13,   13, 0x08,
     414,  403,   13,   13, 0x08,
     429,   13,   13,   13, 0x08,
     441,   39,   13,   13, 0x08,
     468,  461,   13,   13, 0x08,
     510,   13,   13,   13, 0x08,
     534,   13,   13,   13, 0x08,
     557,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DocumentEdit[] = {
    "DocumentEdit\0\0de\0setDesigner(designer)\0"
    "a\0setHeaderText(QString&)\0"
    "setFooterText(QString&)\0getFont()\0"
    "loadModGenerale()\0loadTemplate()\0"
    "loadEnel()\0loadTSheet()\0Editor*\0"
    "createEditor()\0updateMenus()\0fileNew()\0"
    "fileOpen()\0fileSave()\0fileSaveAs()\0"
    "filePrint()\0filePrintPreview()\0"
    "filePrintPdf()\0cut()\0copy()\0paste()\0"
    "image()\0table()\0textBold()\0textUnderline()\0"
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
        case 3: getFont(); break;
        case 4: loadModGenerale(); break;
        case 5: loadTemplate(); break;
        case 6: loadEnel(); break;
        case 7: loadTSheet(); break;
        case 8: { Editor* _r = createEditor();
            if (_a[0]) *reinterpret_cast< Editor**>(_a[0]) = _r; }  break;
        case 9: updateMenus(); break;
        case 10: fileNew(); break;
        case 11: fileOpen(); break;
        case 12: fileSave(); break;
        case 13: fileSaveAs(); break;
        case 14: filePrint(); break;
        case 15: filePrintPreview(); break;
        case 16: filePrintPdf(); break;
        case 17: cut(); break;
        case 18: copy(); break;
        case 19: paste(); break;
        case 20: image(); break;
        case 21: table(); break;
        case 22: textBold(); break;
        case 23: textUnderline(); break;
        case 24: textItalic(); break;
        case 25: textFamily((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 26: textSize((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 27: textStyle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 28: textColor(); break;
        case 29: textAlign((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 30: currentCharFormatChanged((*reinterpret_cast< const QTextCharFormat(*)>(_a[1]))); break;
        case 31: cursorPositionChanged(); break;
        case 32: clipboardDataChanged(); break;
        case 33: printPreview((*reinterpret_cast< QPrinter*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 34;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
