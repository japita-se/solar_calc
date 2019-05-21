

#include "documentedit.h"
#include "load.h"
#include "myplot.h"
//#include "data.h"
#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QColorDialog>
#include <QComboBox>
#include <QFontComboBox>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFontDatabase>
#include <QMenu>
#include <QMenuBar>
#include <QPrintDialog>
#include <QPrinter>
#include <QTextCodec>
#include <QTextEdit>
#include <QToolBar>
#include <QTextCursor>
#include <QTextDocumentWriter>
#include <QTextList>
#include <QtDebug>
#include <QCloseEvent>
#include <QMessageBox>
#include <QPrintPreviewDialog>
#include <QGraphicsView>
#include <QGraphicsView>
#include <QWorkspace>
#include "textprinter.h"
#include "editor.h"
#ifdef Q_WS_MAC
const QString rsrcPath = ":/images/mac";
#else
const QString rsrcPath = ":/images/win";
#endif
Editor* DocumentEdit::activeEditor()
{
    return qobject_cast<Editor *>(workspace->activeWindow());
}

Editor* DocumentEdit::createEditor()
{


    Editor* editor = new Editor;

    connect(editor,SIGNAL(copyAvailable(bool)),actionCut,SLOT(setEnabled(bool)));
    connect(editor,SIGNAL(copyAvailable(bool)),actionCopy,SLOT(setEnabled(bool)));
    connect(editor,SIGNAL(cursorPositionChanged()),SLOT(getFont()));
    workspace->addWindow(editor);
qDebug()<<"Create editor....B";
    /*TODO ADD TO WINDOW LIST */
    connect(editor, SIGNAL(cursorPositionChanged()),this, SLOT(cursorPositionChanged()));

    return editor;
//
//    connect(textEdit, SIGNAL(currentCharFormatChanged(const QTextCharFormat &)),
//            this, SLOT(currentCharFormatChanged(const QTextCharFormat &)));

//
//    textEdit->setFocus();
}

DocumentEdit::DocumentEdit(QWidget *parent)
    : QMainWindow(parent)
{

    Hset        = false;
    Hgset       = false;
    Eset        = false;

//    for(int i=0;i<12;i++)
//        {H[i] = 0; E[i]=0;}
    power       = 0;
    projectPath ="";
    recentDir   = QDir::homePath();
    profile << tr("Uniforme")<<
            tr("Prevalenza Estate")<<tr("Prevalenza Inverno")<<
            tr("Stagionale Inverno")<<
            tr("Stagionale Estate")<<
            tr("Personalizzato")<<
            tr("Commercial")<<
            tr("Industriale");
    yearlyLoad     = 0;
    monthlyProfile = 0;
    sources<<QObject::tr("ENEA SolarEnergy")<<QObject::tr("Custom")<<QObject::tr("PVGIS")<<QObject::tr("NASA SSE");
    models <<QObject::tr("UNI 8477 ")<<QObject::tr("ENEA")<<QObject::tr("Erbs");
    invString   = "<br/><h2>Dettagli inverters</h2><br/><table border=1 width=800 cellspacing=0 cellpadding=3 bordercolor=\"#980000\" >";
    header      = "<tr  bgcolor=\"#C89800\"><td >" + tr("Inverter") + "</td><td >" + tr("Efficienza(%)") + "</td><td>" + tr("Stringhe")    + "</td><td>" + tr("Pannelli x Stringa") + "</td></tr>";

    coverPage = QCoreApplication::applicationDirPath() + "/bs/coverrel.html";
    techPage = QCoreApplication::applicationDirPath() + "/bs/schedatec.html";

    /* Only &date is parsed by Editor. Others tags can be parse here */
    headerText =
        "<table width=\"100%\">"
        "  <tr>"
        "    <td align=\"left\"><img src=\"&logo\" width=150 height=60/></td>"
        "    <td align=\"right\"><strong>&date;</strong></td>"
        "  </tr>"
        "</table>";
    footerText = tr("<p>Il presente progetto &egrave; tutelato dalle leggi sulle opere dell'ingegno, art.2575-2579 del codice civile.")+ "<p align=\"left\">%1</p><p align=\"right\"><strong>&page;</strong></p>";

    setWindowIcon(QIcon(":images/textIcon.png"));
    workspace = new QWorkspace;


    setupFileActions();

    setupMenu();
    setupEditActions();
    setupTextActions();

    textprinter_ = new TextPrinter;
    textprinter_->setHeaderSize(10);
    textprinter_->setFooterSize(10);
    textprinter_->setDateFormat("MMMM dd yyyy");

    setCentralWidget(workspace);

    connect(workspace,SIGNAL(windowActivated(QWidget*)),SLOT(updateMenus()));

    setCurrentFileName(QString());


 //   fontChanged(textEdit->font());
//    colorChanged(textEdit->textColor());
//    alignmentChanged(textEdit->alignment());

//    connect(activeEditor(), SIGNAL(modificationChanged(bool)),
 //           actionSave, SLOT(setEnabled(bool)));
//    connect(textEdit->document(), SIGNAL(modificationChanged(bool)),
//            this, SLOT(setWindowModified(bool)));
//    connect(textEdit->document(), SIGNAL(undoAvailable(bool)),
//            actionUndo, SLOT(setEnabled(bool)));
//    connect(textEdit->document(), SIGNAL(redoAvailable(bool)),
//            actionRedo, SLOT(setEnabled(bool)));
//
//    setWindowModified(activeEditor()->document()->isModified());
//    actionSave->setEnabled(activeEditor()->document()->isModified());
//    actionUndo->setEnabled(textEdit->document()->isUndoAvailable());
//    actionRedo->setEnabled(textEdit->document()->isRedoAvailable());

//    connect(actionUndo, SIGNAL(triggered()), textEdit, SLOT(undo()));
//    connect(actionRedo, SIGNAL(triggered()), textEdit, SLOT(redo()));

//    actionCut->setEnabled(false);
 //   actionCopy->setEnabled(false);

//    connect(actionCut, SIGNAL(triggered()), textEdit, SLOT(cut()));
//    connect(actionCopy, SIGNAL(triggered()), textEdit, SLOT(copy()));
//    connect(actionPaste, SIGNAL(triggered()), textEdit, SLOT(paste()));
//
//    connect(textEdit, SIGNAL(copyAvailable(bool)), actionCut, SLOT(setEnabled(bool)));
//    connect(textEdit, SIGNAL(copyAvailable(bool)), actionCopy, SLOT(setEnabled(bool)));

    connect(QApplication::clipboard(), SIGNAL(dataChanged()), this, SLOT(clipboardDataChanged()));
qDebug()<<"Create editor....D"<<localita.name;
    QString initialFile = ":/example.html";
    const QStringList args = QCoreApplication::arguments();
    if (args.count() == 2)
        initialFile = args.at(1);

//    if (!load(initialFile))
//        fileNew();

    details.title = "";
    details.albo  = "";
    details.clientAddress = "";
    details.clientName    = "";
    details.company       = "";
    details.name          = "";
    details.date          = QDate();
    details.name_r        = "";
    details.title         ="";

}
void DocumentEdit::updateMenus()
{
    bool hasEditor      = (activeEditor() !=0);
    bool hasSelection   = (activeEditor() &&
                           activeEditor()->textCursor().hasSelection());
    actionSave->setEnabled(hasEditor);
    actionUndo->setEnabled(hasEditor);
    actionRedo->setEnabled(hasEditor);
    actionCopy->setEnabled(hasSelection);
    actionPaste->setEnabled(hasEditor);
    actionCut->setEnabled(hasSelection);
    closeAction->setEnabled(hasEditor);
    closeAllAction->setEnabled(hasEditor);
    tileAction->setEnabled(hasEditor);
    cascadeAction->setEnabled(hasEditor);
    nextAction->setEnabled(hasEditor);
    previousAction->setEnabled(hasEditor);
    separatorAction->setVisible(hasEditor);


  //  if (activeEditor())
    //       activeEditor()->windowMenuAction()->setChecked(true);

}

void DocumentEdit::closeEvent(QCloseEvent *event)
{
    workspace->closeAllWindows();
//    QWidgetList w = workspace->windowList();


//    for (int i=0;i<w.size();i++)
//    {
//       Editor *e = qobject_cast<Editor *>(w.at(i));
//       e->close_(event);
//   }
       if (activeEditor()) {
           event->ignore();
       } else {
           event->accept();
       }
}

void DocumentEdit::setupFileActions()
{

    tb = new QToolBar(this);
    tb->setWindowTitle(tr("File"));
    addToolBar(tb);

    actionNew = new QAction(QIcon(":/images/new.png"), tr("&Nuovo"), this);
    actionNew->setShortcut(QKeySequence::New);
    connect(actionNew, SIGNAL(triggered()), this, SLOT(fileNew()));
    tb->addAction(actionNew);
   // menu->addAction(a);

    actionOpen = new QAction(QIcon(":/images/open.png"), tr("&Apri..."), this);
    actionOpen->setShortcut(QKeySequence::Open);
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(fileOpen()));
    tb->addAction(actionOpen);
 //   menu->addAction(a);

  //  menu->addSeparator();

    actionSave =  new QAction(QIcon(":/images/save.png"), tr("&Salva"), this);
    actionSave->setShortcut(QKeySequence::Save);
    connect(actionSave, SIGNAL(triggered()), this, SLOT(fileSave()));
    actionSave->setEnabled(false);
    tb->addAction(actionSave);
  //  menu->addAction(a);

    actionSaveAs = new QAction(tr("Salv&a con nome..."), this);
    connect(actionSaveAs, SIGNAL(triggered()), this, SLOT(fileSaveAs()));
   // menu->addAction(a);
   // menu->addSeparator();

#ifndef QT_NO_PRINTER
    actionPrint = new QAction(QIcon(":/images/print.png"), tr("Stam&pa..."), this);
    actionPrint->setShortcut(QKeySequence::Print);
    connect(actionPrint, SIGNAL(triggered()), this, SLOT(filePrint()));
    tb->addAction(actionPrint);
   // menu->addAction(a);

    actionPrintPreview = new QAction(QIcon(rsrcPath + "/fileprint.png"), tr("Anteprima stampa..."), this);
    connect(actionPrintPreview, SIGNAL(triggered()), this, SLOT(filePrintPreview()));
   // menu->addAction(a);

    actionPdf = new QAction(QIcon(":/images/adobe.png"), tr("&Esporta PDF..."), this);
    actionPdf->setShortcut(Qt::CTRL + Qt::Key_D);
    connect(actionPdf, SIGNAL(triggered()), this, SLOT(filePrintPdf()));
  //  tb->addAction(a);
   // menu->addAction(a);

   // menu->addSeparator();
#endif

    actionQuit = new QAction(tr("&Esci"), this);
    actionQuit->setShortcut(Qt::CTRL + Qt::Key_Q);
    connect(actionQuit, SIGNAL(triggered()), this, SLOT(close()));
  //  menu->addAction(a);

    separatorAction = new QAction(this);
    separatorAction->setSeparator(true);
    closeAction = new QAction(tr("Cl&ose"), this);
    closeAction->setShortcut(tr("Ctrl+W"));
    closeAction->setStatusTip(tr("Chiudi la finestra corrente"));
    connect(closeAction, SIGNAL(triggered()),
            workspace, SLOT(closeActiveWindow()));

    closeAllAction = new QAction(tr("Chiudi &tutto"), this);
    closeAllAction->setStatusTip(tr("Chiudi tutte le finestre"));
    connect(closeAllAction, SIGNAL(triggered()),
            workspace, SLOT(closeAllWindows()));

    tileAction = new QAction(tr("&Allinea"), this);
    tileAction->setStatusTip(tr("Allinea le finestre"));
    connect(tileAction, SIGNAL(triggered()), workspace, SLOT(tile()));

    cascadeAction = new QAction(tr("&Cascata"), this);
    cascadeAction->setStatusTip(tr("A cascata"));
    connect(cascadeAction, SIGNAL(triggered()),
            workspace, SLOT(cascade()));

    nextAction = new QAction(tr("Ne&xt"), this);
    nextAction->setShortcut(tr("Ctrl+F6"));
    nextAction->setStatusTip(tr("Attiva la finestra successiva"));
    connect(nextAction, SIGNAL(triggered()),
            workspace, SLOT(activateNextWindow()));

    previousAction = new QAction(tr("Preceden&te"), this);
    previousAction->setShortcut(tr("Ctrl+Shift+F6"));
    previousAction->setStatusTip(tr("Attiva la finestra precedente"));
    connect(previousAction, SIGNAL(triggered()),
            workspace, SLOT(activatePreviousWindow()));

    QToolBar *tb = new QToolBar(this);
    tb->setWindowTitle(tr("Modelli documenti"));
    addToolBar(tb);

    a_modello_generale = new QAction(QIcon(":/images/models.png"),tr("Relazione generale"),this);
    a_modello_generale->setToolTip(tr("Modello relazione generale"));
    connect(a_modello_generale,SIGNAL(triggered()),SLOT(loadModGenerale()));

    a_scheda_tecnica = new QAction(QIcon(":/images/models.png"),tr("Scheda tecnica"),this);
    a_scheda_tecnica->setToolTip(tr("Genera la scheda tecnica di impianto"));
    connect(a_scheda_tecnica,SIGNAL(triggered()),SLOT(loadTSheet()));

    a_modello_custom = new QAction(tr("Carica modello custom"),this);
    a_modello_custom->setToolTip(tr("Carica modello custom"));
    connect(a_modello_custom,SIGNAL(triggered()),SLOT(loadTemplate()));

    a_enel = new QAction(QIcon(":/images/models.png"),tr("Domanda allacciamento"),this);
    a_enel->setToolTip(tr("Genera richiesta allacciamento a ENEL"));
    connect(a_modello_generale,SIGNAL(triggered()),SLOT(loadEnel()));



}
void DocumentEdit::setupMenu()
{




    menu = menuBar()->addMenu(tr("&File"));
    menu->addAction(actionNew);

    QMenu* modelMenu = menu->addMenu(tr("Modelli"));

    modelMenu->addAction(a_modello_generale);
    modelMenu->addAction(a_scheda_tecnica);
     modelMenu->addAction(a_modello_custom);
  //  modelMenu->addAction(a_enel);


    menu->addAction(actionOpen);
    menu->addAction(actionSave);
    menu->addAction(actionSaveAs);
    menu->addAction(actionPdf);
    menu->addAction(actionPrint);
    menu->addAction(actionPrintPreview);
    menu->addAction(actionQuit);


      //windowMenu->addAction(separatorAction);
}

void DocumentEdit::setupEditActions()
{
    QToolBar *tbEdit = new QToolBar(this);
    tbEdit->setWindowTitle(tr("Formattazione"));
    addToolBar(tbEdit);

    menuEdit = menuBar()->addMenu(tr("&Edit"));
    windowMenu = menuBar()->addMenu(tr("&Finestre"));
    windowMenu->addAction(closeAction);
    windowMenu->addAction(closeAllAction);
    windowMenu->addSeparator();
    windowMenu->addAction(tileAction);
    windowMenu->addAction(cascadeAction);
    windowMenu->addSeparator();
    windowMenu->addAction(nextAction);
    windowMenu->addAction(previousAction);


    QAction *a;
    a = actionUndo = new QAction(QIcon(rsrcPath + "/editundo.png"), tr("Ann&ulla"), this);
    a->setShortcut(QKeySequence::Undo);
    tbEdit->addAction(a);
    menuEdit->addAction(a);


    a = actionRedo = new QAction(QIcon(rsrcPath + "/editredo.png"), tr("&Ripeti"), this);
    a->setShortcut(QKeySequence::Redo);
    tbEdit->addAction(a);
    menuEdit->addAction(a);
    menuEdit->addSeparator();

    a = actionCut = new QAction(QIcon(rsrcPath + "/editcut.png"), tr("&Taglia"), this);
    a->setShortcut(QKeySequence::Cut);
    connect(actionCut, SIGNAL(triggered()), this, SLOT(cut()));
    tbEdit->addAction(a);
    menuEdit->addAction(a);

    a = actionCopy = new QAction(QIcon(rsrcPath + "/editcopy.png"), tr("&Copia"), this);
    a->setShortcut(QKeySequence::Copy);
    connect(actionCopy, SIGNAL(triggered()), this, SLOT(copy()));
    tbEdit->addAction(a);
    menuEdit->addAction(a);

    a = actionPaste = new QAction(QIcon(rsrcPath + "/editpaste.png"), tr("&Incolla"), this);
    a->setShortcut(QKeySequence::Paste);
    connect(actionPaste, SIGNAL(triggered()), this, SLOT(paste()));
    tbEdit->addAction(a);
    menuEdit->addAction(a);
    actionPaste->setEnabled(!QApplication::clipboard()->text().isEmpty());

    menuEdit->addSeparator();

   actionImage = new QAction(QIcon(rsrcPath + "/insertimage.png"), tr("Inserisci im&magine"),this);
    connect(actionImage,SIGNAL(triggered()),SLOT(image()));
    tbEdit->addAction(actionImage);
    menuEdit->addAction(actionImage);

    actionTable = new QAction(QIcon(rsrcPath + "/inserttable.png"),tr("Inserisci ta&bella"),this);
    connect(actionTable,SIGNAL(triggered()),SLOT(table()));
    tbEdit->addAction(actionTable);
    menuEdit->addAction(actionTable);


}

void DocumentEdit::setupTextActions()
{


    QToolBar *tb = new QToolBar(this);
    tb->setWindowTitle(tr("Formato"));
    addToolBar(tb);

    QMenu *menu = new QMenu(tr("F&ormato"), this);
    menuBar()->addMenu(menu);

    actionTextBold = new QAction(QIcon(":/images/textbold.png"), tr("Grassetto"), this);
    actionTextBold->setShortcut(Qt::CTRL + Qt::Key_B);
    QFont bold;
    bold.setBold(true);
    actionTextBold->setFont(bold);
    connect(actionTextBold, SIGNAL(triggered()), this, SLOT(textBold()));
    tb->addAction(actionTextBold);
    menu->addAction(actionTextBold);
    actionTextBold->setCheckable(true);

    actionTextItalic = new QAction(QIcon(":/images/textitalics.png"), tr("&Italic"), this);
    actionTextItalic->setShortcut(Qt::CTRL + Qt::Key_I);
    QFont italic;
    italic.setItalic(true);
    actionTextItalic->setFont(italic);
    connect(actionTextItalic, SIGNAL(triggered()), this, SLOT(textItalic()));
    tb->addAction(actionTextItalic);
    menu->addAction(actionTextItalic);
    actionTextItalic->setCheckable(true);

    actionTextUnderline = new QAction(QIcon(":/images/textunderline.png"), tr("&Underline"), this);
    actionTextUnderline->setShortcut(Qt::CTRL + Qt::Key_U);
    QFont underline;
    underline.setUnderline(true);
    actionTextUnderline->setFont(underline);
    connect(actionTextUnderline, SIGNAL(triggered()), this, SLOT(textUnderline()));
    tb->addAction(actionTextUnderline);
    menu->addAction(actionTextUnderline);
    actionTextUnderline->setCheckable(true);

    menu->addSeparator();

    QActionGroup *grp = new QActionGroup(this);
    connect(grp, SIGNAL(triggered(QAction *)), this, SLOT(textAlign(QAction *)));

    // Make sure the alignLeft  is always left of the alignRight
    if (QApplication::isLeftToRight()) {
        actionAlignLeft = new QAction(QIcon(":/images/left.png"), tr("Sinistra"), grp);
        actionAlignCenter = new QAction(QIcon(":/images/center.png"), tr("C&enter"), grp);
        actionAlignRight = new QAction(QIcon(":/images/right.png"), tr("Dest&ra"), grp);
    } else {
        actionAlignRight = new QAction(QIcon(":/images/right.png"), tr("Dest&ra"), grp);
        actionAlignCenter = new QAction(QIcon(":/images/center.png"), tr("C&entero"), grp);
        actionAlignLeft = new QAction(QIcon(":/images/left.png"), tr("Sinistra"), grp);
    }
    actionAlignJustify = new QAction(QIcon(":/images/justify.png"), tr("&Giustificato"), grp);

    actionAlignLeft->setShortcut(Qt::CTRL + Qt::Key_L);
    actionAlignLeft->setCheckable(true);
    actionAlignCenter->setShortcut(Qt::CTRL + Qt::Key_E);
    actionAlignCenter->setCheckable(true);
    actionAlignRight->setShortcut(Qt::CTRL + Qt::Key_R);
    actionAlignRight->setCheckable(true);
    actionAlignJustify->setShortcut(Qt::CTRL + Qt::Key_J);
    actionAlignJustify->setCheckable(true);

    tb->addActions(grp->actions());
    menu->addActions(grp->actions());

    menu->addSeparator();

    QPixmap image(":/images/colorText.png");
    QPixmap pix ;
    pix.fill(Qt::transparent);
    QPainter p;
    p.begin(&image);
    p.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    p.drawPixmap(pix.rect(),image);
    p.end();
    actionTextColor = new QAction(QIcon(image),tr("&Color..."), this);
   // actionTextColor->setIcon(QIcon(":/images/colorText.png"));
    connect(actionTextColor, SIGNAL(triggered()), this, SLOT(textColor()));
    tb->addAction(actionTextColor);
    menu->addAction(actionTextColor);


    tb = new QToolBar(this);
    tb->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    tb->setWindowTitle(tr("Format Actions"));
    addToolBarBreak(Qt::TopToolBarArea);
    addToolBar(tb);

    comboStyle = new QComboBox(tb);
    tb->addWidget(comboStyle);
    comboStyle->addItem("Standard");
    comboStyle->addItem(tr("Lista a pallini )"));
    comboStyle->addItem(tr("Lista a aerchietti"));
    comboStyle->addItem(tr("Lista a quadratini"));
    comboStyle->addItem(tr("Lista numerica"));
    comboStyle->addItem(tr("Lista alfanumerica(Alpha in fondo"));
    comboStyle->addItem("Lista alfanumerica (Alpha sopra)");
    connect(comboStyle, SIGNAL(activated(int)),
            this, SLOT(textStyle(int)));

    comboFont = new QFontComboBox(tb);
    tb->addWidget(comboFont);
    connect(comboFont, SIGNAL(activated(const QString &)),
            this, SLOT(textFamily(const QString &)));

    comboSize = new QComboBox(tb);
    comboSize->setObjectName("comboSize");
    tb->addWidget(comboSize);
    comboSize->setEditable(true);

    QFontDatabase db;
    foreach(int size, db.standardSizes())
        comboSize->addItem(QString("%L1").arg(size));

    connect(comboSize, SIGNAL(activated(const QString &)),
            this, SLOT(textSize(const QString &)));
    comboSize->setCurrentIndex(comboSize->findText(QString("%L1").arg(QApplication::font()
                                                                   .pointSize())));
}
void DocumentEdit::setupModelsActions()
{
    QToolBar *tb = new QToolBar(this);
    tb->setWindowTitle(tr("Modelli documenti"));
    addToolBar(tb);

    a_modello_generale = new QAction(QIcon(":/images/models.png"),tr("Modelli"),this);
    a_modello_generale->setToolTip(tr("Modello relazione generale"));
    connect(a_modello_generale,SIGNAL(triggered()),SLOT(loadModGenerale()));


    QMenu* modelMenu = menuBar()->addMenu(tr("Modelli"));
    modelMenu->addAction(tr("Relazione Generale"));
    tb->addAction(a_modello_generale);
}

void DocumentEdit::load(const QString &f)
{
//    if (!QFile::exists(f))
//        return false;
//    QFile file(f);
//    if (!file.open(QFile::ReadOnly))
//        return false;
//
//    QByteArray data = file.readAll();
//    QTextCodec *codec = Qt::codecForHtml(data);
//    QString str = codec->toUnicode(data);
//    if (Qt::mightBeRichText(str)) {
//        activeEditor()->setHtml(str);
//    } else {
//        str = QString::fromLocal8Bit(data);
//        activeEditor()->setPlainText(str);
//    }
//
//    setCurrentFileName(f);
//    activeEditor()->setCurrentFile(f);
//    return true;
    Editor *editor = createEditor();
    if (editor->openFile(f)) {
        editor->show();
    } else {
        editor->close();
    }
}

bool DocumentEdit::maybeSave()
{
//    if (!activeEditor()->document()->isModified())
//        return true;
//    if (fileName.startsWith(QLatin1String(":/")))
//        return true;
//    QMessageBox::StandardButton ret;
//    ret = QMessageBox::warning(this, tr("Attenzione"),
//                               tr("Il documento non &egrave; stato salvato.Vuoi salvare le modifiche?"),
//                               QMessageBox::Save | QMessageBox::Discard
//                               | QMessageBox::Cancel);
//    if (ret == QMessageBox::Save)
//        return fileSave();
//    else if (ret == QMessageBox::Cancel)
//        return false;
//    return true;
}

void DocumentEdit::setCurrentFileName(const QString &fileName)
{
    this->fileName = fileName;
   // activeEditor()->document()->setModified(false);

    QString shownName;
    if (fileName.isEmpty())
        shownName = "Gestione documenti";
    else
        shownName = QFileInfo(fileName).fileName();

    setWindowTitle(tr("%1[*]").arg(shownName));
   // setWindowModified(false);
}

void DocumentEdit::fileNew()
{
//    if (maybeSave()) {
//        textEdit->clear();
//        setCurrentFileName(QString());
//    }

    Editor* editor = createEditor();
    editor->fileNew();
    editor->show();

}

void DocumentEdit::fileOpen()
{
    QString fn = QFileDialog::getOpenFileName(this, tr("Open File..."),
                                              QString(), tr("HTML-Files (*.htm *.html);;All Files (*)"));
    if (!fn.isEmpty())
        load(fn);
}

void DocumentEdit::fileSave()
{
  if (activeEditor())
      activeEditor()->save();
}

void DocumentEdit::fileSaveAs()
{
    if (activeEditor())
        activeEditor()->saveAs();
}

void DocumentEdit::filePrint()
{

    #ifndef QT_NO_PRINTER
    if (activeEditor()){
        QPrinter printer(QPrinter::HighResolution);
        QPrintDialog *dlg = new QPrintDialog(&printer, this);
        if (activeEditor()->textCursor().hasSelection())
            dlg->addEnabledOption(QAbstractPrintDialog::PrintSelection);
        dlg->setWindowTitle(tr("Stampa documento"));
        if (dlg->exec() == QDialog::Accepted) {
            textprinter_->setHeaderText(headerText.arg(this->fileName));
            textprinter_->setFooterText(footerText.arg(this->fileName));
            textprinter_->print(activeEditor()->document());
        }
        delete dlg;
    }
    #endif

}

void DocumentEdit::filePrintPreview()
{
#ifndef QT_NO_PRINTER
    if (activeEditor()){
    textprinter_->setHeaderText(headerText.arg(this->fileName));
    textprinter_->setFooterText(footerText.arg(this->fileName));
    textprinter_->preview(activeEditor()->document(),"Print");
}
#endif
}

void DocumentEdit::printPreview(QPrinter *printer)
{
#ifdef QT_NO_PRINTER
    Q_UNUSED(printer);
#else

#endif
}


void DocumentEdit::filePrintPdf()
{
#ifndef QT_NO_PRINTER
//! [0]
    QString fileName = QFileDialog::getSaveFileName(this, "Export PDF",
                                                    QString(), "*.pdf");
    if (!fileName.isEmpty()) {
        if (QFileInfo(fileName).suffix().isEmpty())
            fileName.append(".pdf");
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);;
        printer.setOutputFileName(fileName);

        textprinter_->setHeaderText(headerText.arg(this->fileName));
        textprinter_->setFooterText(footerText.arg(this->fileName));
        qDebug()<<"DE sono qua";
        textprinter_->exportPdf(activeEditor()->document(),tr("Esporta PDF"),QFileInfo(fileName).absoluteFilePath());

    }
//! [0]
#endif
}

void DocumentEdit::textBold()
{
    QTextCharFormat fmt;
    fmt.setFontWeight(actionTextBold->isChecked() ? QFont::Bold : QFont::Normal);
    mergeFormatOnWordOrSelection(fmt);
}

void DocumentEdit::textUnderline()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(actionTextUnderline->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}

void DocumentEdit::textItalic()
{
    QTextCharFormat fmt;
    fmt.setFontItalic(actionTextItalic->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}

void DocumentEdit::textFamily(const QString &f)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(f);
    mergeFormatOnWordOrSelection(fmt);
}

void DocumentEdit::textSize(const QString &p)
{
    qreal pointSize = p.toFloat();
    if (p.toFloat() > 0) {
        QTextCharFormat fmt;
        fmt.setFontPointSize(pointSize);
        mergeFormatOnWordOrSelection(fmt);
    }
}

void DocumentEdit::textStyle(int styleIndex)
{
    QTextCursor cursor = activeEditor()->textCursor();

    if (styleIndex != 0) {
        QTextListFormat::Style style = QTextListFormat::ListDisc;

        switch (styleIndex) {
            default:
            case 1:
                style = QTextListFormat::ListDisc;
                break;
            case 2:
                style = QTextListFormat::ListCircle;
                break;
            case 3:
                style = QTextListFormat::ListSquare;
                break;
            case 4:
                style = QTextListFormat::ListDecimal;
                break;
            case 5:
                style = QTextListFormat::ListLowerAlpha;
                break;
            case 6:
                style = QTextListFormat::ListUpperAlpha;
                break;
        }

        cursor.beginEditBlock();

        QTextBlockFormat blockFmt = cursor.blockFormat();

        QTextListFormat listFmt;

        if (cursor.currentList()) {
            listFmt = cursor.currentList()->format();
        } else {
            listFmt.setIndent(blockFmt.indent() + 1);
            blockFmt.setIndent(0);
            cursor.setBlockFormat(blockFmt);
        }

        listFmt.setStyle(style);

        cursor.createList(listFmt);

        cursor.endEditBlock();
    } else {
        // ####
        QTextBlockFormat bfmt;
        bfmt.setObjectIndex(-1);
        cursor.mergeBlockFormat(bfmt);
    }
}

void DocumentEdit::textColor()
{
    if (activeEditor()){
    QColor col = QColorDialog::getColor(activeEditor()->textColor(), this);
    if (!col.isValid())
        return;
    QTextCharFormat fmt;
    fmt.setForeground(col);
    mergeFormatOnWordOrSelection(fmt);
    colorChanged(col);
}
}

void DocumentEdit::textAlign(QAction *a)
{
    if (activeEditor()){
    if (a == actionAlignLeft)
        activeEditor()->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
    else if (a == actionAlignCenter)
        activeEditor()->setAlignment(Qt::AlignHCenter);
    else if (a == actionAlignRight)
        activeEditor()->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
    else if (a == actionAlignJustify)
        activeEditor()->setAlignment(Qt::AlignJustify);
}
}

void DocumentEdit::currentCharFormatChanged(const QTextCharFormat &format)
{
    fontChanged(format.font());
    colorChanged(format.foreground().color());
}

void DocumentEdit::cursorPositionChanged()
{
  //  qDebug()<<"SIMA QUI";
   // alignmentChanged(activeEditor()->alignment());
}

void DocumentEdit::clipboardDataChanged()
{
    actionPaste->setEnabled(!QApplication::clipboard()->text().isEmpty());
}

//void DocumentEdit::about()
//{
//    QMessageBox::about(this, tr("About"), tr("This example demonstrates Qt's "
//        "rich text editing facilities in action, providing an example "
//        "document for you to experiment with."));
//}

// Sep. 2010
// Get the property of the selected font in the document
void DocumentEdit::getFont()
{
    if (activeEditor()){

        QTextCursor cursor = activeEditor()->textCursor();
        if (!cursor.hasSelection())
        {

            cursor.select(QTextCursor::WordUnderCursor);


             QTextCharFormat fmt = cursor.charFormat();
             QFont f = fmt.font();
             colorChanged(fmt.foreground().color());
             comboFont->setCurrentIndex(comboFont->findText(QFontInfo(f).family()));
             comboSize->setCurrentIndex(comboSize->findText(QString::number(f.pointSize())));

             if (f.italic())
                    actionTextItalic->setChecked(true);
                 else
                     actionTextItalic->setChecked(false);
             if (f.bold())
                    actionTextBold->setChecked(true);
                     else
                     actionTextBold->setChecked(false);
             if (f.underline())
                 actionTextUnderline->setChecked(true);
             else
                 actionTextUnderline->setChecked(false);
         }
    }
}

void DocumentEdit::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    if (activeEditor()){
    QTextCursor cursor = activeEditor()->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    activeEditor()->mergeCurrentCharFormat(format);
}
}

void DocumentEdit::fontChanged(const QFont &f)
{
    comboFont->setCurrentIndex(comboFont->findText(QFontInfo(f).family()));
    comboSize->setCurrentIndex(comboSize->findText(QString::number(f.pointSize())));
    actionTextBold->setChecked(f.bold());
    actionTextItalic->setChecked(f.italic());
    actionTextUnderline->setChecked(f.underline());
}

void DocumentEdit::colorChanged(const QColor &c)
{
//    QPixmap pix(16, 16);
//    pix.fill(c);
//    actionTextColor->setIcon(pix);
    QPixmap image(":/images/colorText.png");
    QPixmap pix(image.size());
    pix.fill(c);
    QPainter p;
    p.begin(&image);
    p.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    p.drawPixmap(pix.rect(),pix);
    p.end();
    actionTextColor->setIcon(QIcon(image));
}

void DocumentEdit::alignmentChanged(Qt::Alignment a)
{
    qDebug()<<"SIMA QUA"<<a;
    if (a & Qt::AlignLeft) {
        actionAlignLeft->setChecked(true);
    } else if (a & Qt::AlignHCenter) {
        actionAlignCenter->setChecked(true);
    } else if (a & Qt::AlignRight) {
        actionAlignRight->setChecked(true);
    } else if (a & Qt::AlignJustify) {
        actionAlignJustify->setChecked(true);
    }
}
void DocumentEdit::setHeaderText(QString& a)
{
    headerText = a;
}
void DocumentEdit::setFooterText(QString& a)
{
    footerText = a;
}
void DocumentEdit::setDesigner(designer name)
{
    details = name;
    headerText =
        "<table width=\"100%\">"
        "  <tr>"
        "    <td align=\"left\"><img src=\"&logo\" width=150 height=60/></td>"
        "    <td align=\"right\"><strong>&date;</strong></td>"
        "  </tr>"
        "</table>";
    parseHeader();
    qDebug()<<"DD details changed"<<details.title<<details.name<<details.logoPath;
}
QString DocumentEdit::readTemplateFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Gestione documenti"),
                             tr("Non riesco a leggere il file %1:\n%2.")
                             .arg(file.fileName())
                             .arg(file.errorString()));
        return QString();
    }

    QApplication::setOverrideCursor(Qt::WaitCursor);
    QTextStream in(&file);
    QString data = in.readAll();
//qDebug()<<"DD readTemplateFile"<<data;
    QApplication::restoreOverrideCursor();
    return data;
}
void DocumentEdit::loadModGenerale()
{
    /*Put the cover page */
    qDebug()<<"DD cover"<<projectPath;
    if (projectPath.isEmpty() || projectPath.isNull()){
        QMessageBox::warning(this,tr("Errore"),
                             tr("<p>Devi prima scegliere almeno la localit&agrave; e salvare il progetto per poter generare la relazione generale</p>"));
        return;
        }
    QFile file(coverPage);
    QString temp;
    if (file.exists())

    {
        Editor *editor = createEditor();
        editor->fileNew();

        QApplication::setOverrideCursor(Qt::WaitCursor);
        temp = readTemplateFile(coverPage);
        qDebug()<<"DD start reading file";
      //  qDebug()<<"DD temp"<<temp<<details.title;
        /* Replace tags */
        if (!temp.isEmpty()) {

            temp = parseTemplate(temp);
            parseTemplateMore(temp);
            qDebug()<<"DD temp"<<temp<<details.title;
            editor->document()->setHtml(temp);
            editor->show();
        } else {
            editor->close();
        }
        qDebug()<<"DD temp finale";
        /*Put the content */

         QTextCursor mc;
         mc.movePosition(QTextCursor::Start,QTextCursor::MoveAnchor,1);
       //  editor->setTextCursor(mc);
         editor->show();


    }
    else
    {
        QMessageBox::critical(this,tr("Errore di lettura"),tr("<p>Non riesco a caricare il modello di copertina. Controlla la tua installazione.</P><p>File:")+coverPage);
    }


    QApplication::restoreOverrideCursor();
}


void DocumentEdit::loadTSheet()
{
    /*Put the cover page */
  //  qDebug()<<"DD cover"<<projectPath;
    if (projectPath.isEmpty() || projectPath.isNull()){
        QMessageBox::warning(this,tr("Errore"),
                             tr("<p>Devi prima scegliere almeno la localit&agrave; e salvare il progetto per poter generare la scheda tecnica</p>"));
        return;
        }
    QFile file(techPage);
    QString temp;
     if (file.exists())

     {
         Editor *editor = createEditor();
        editor->fileNew();

         QApplication::setOverrideCursor(Qt::WaitCursor);
        qDebug()<<"DD start reading file tech";
         temp = readTemplateFile(techPage);
         parseTemplateMore(temp);



//        /* Replace tags */
        if (!temp.isEmpty()) {



            editor->document()->setHtml(temp);
             editor->show();
         } else {
             editor->close();
         }
//        qDebug()<<"DD temp finale";
////        /*Put the content */




        editor->document()->setHtml(temp);



//         QTextCursor mc;
//         mc.movePosition(QTextCursor::Start,QTextCursor::MoveAnchor,1);
//       //  editor->setTextCursor(mc);
         editor->show();

 }
     else
     {
          QMessageBox::critical(this,tr("Errore di lettura"),tr("<p>Non riesco a caricare il modello di copertina. Controlla la tua installazione.</P><p>File:")+techPage);
     }

    QApplication::restoreOverrideCursor();
}

void DocumentEdit::loadEnel()
{

}

void DocumentEdit::setPower(double d)
{
    power = d;
}

void DocumentEdit::addSystem(sy a)
{

}

void DocumentEdit::addVanDiagram(const QwtPlot* p)
{

}

void DocumentEdit::addRawDiagram(const QwtPlot* p)
{

}

void DocumentEdit::addSolarRadiation(const QwtPlot* p)
{

}
void DocumentEdit::addSolarRadiation2(const QwtPlot* p)
{
}

void DocumentEdit::addEEnergy(const QwtPlot* p)
{

}

void DocumentEdit::setVersion(const QString &version)
{

}

void DocumentEdit::addLocation(loc l)
{
    localita = l;
}

void DocumentEdit::addPanel(panel p)
{
    panels = p;

}

void DocumentEdit::addInverter(inverter inv)
{

}

void DocumentEdit::addOption(option o)
{
    opt = o;


}

void DocumentEdit::addRad( double *rad)
{
    if (rad!=NULL){
    H = rad;
    Hset = true;
    }
}
void DocumentEdit::addRadh( double *rad)
{
    if (rad!=NULL){
    Hg = rad;
    Hgset = true;
    }
}
void DocumentEdit::addEnergy(  double *e)
{
    if (e!=NULL){
    E = e;
    Eset = true;
    }
}

void DocumentEdit::addUnitRad(const QString &s)
{
    unitRad = s;
}

void DocumentEdit::addUnitEnergy(const QString &s)
{
}

void DocumentEdit::addTotEnergy(double a)
{

}

void DocumentEdit::addSolarDiagram(MyPlot *p)
{
    solarDiagram = p;
}
void DocumentEdit::addEco(ecopara p)
{
    ecoParameters = p;
}

void DocumentEdit::setProjectPath(QString &a)
{
    projectPath = a;
    qDebug()<<"DD set project path"<<a;
}
void DocumentEdit::setConsumi(Load *p)
{
    loadInterface = p;
}
void DocumentEdit::setSystem(sy s)
{
    system = s;
    qDebug()<<"DD ssystem set"<<MyMath::isEtero(system.models);

}
void DocumentEdit::cut()
{
    if (activeEditor())
        activeEditor()->cut();
}

void DocumentEdit::copy()
{
    if (activeEditor())
        activeEditor()->copy();
}

void DocumentEdit::paste()
{
    if (activeEditor())
        activeEditor()->paste();

}
void DocumentEdit::image()
{
    if (activeEditor())
        activeEditor()->insertImage();
}
void DocumentEdit::table()
{
    if (activeEditor())
        activeEditor()->insertTable();
}
void DocumentEdit::setFooter(const QString &s)
{
    if (textprinter_ != 0)
    textprinter_->setFooterText(s);
}
void DocumentEdit::setHeader(const QString &s)
{
    if (textprinter_ != 0)
    textprinter_->setHeaderText(s);

    parseHeader();
}
void DocumentEdit::parseHeader()
{

    if (!details.logoPath.isEmpty())
        headerText.replace("&logo",details.logoPath);

}

void DocumentEdit::loadTemplate()
{
    QString fn = QFileDialog::getOpenFileName(this, tr("Open File..."),
                                              recentDir, tr("HTML-Files (*.htm *.html);;All Files (*)"));
    QFile file(fn);
    if (!fn.isEmpty() && !file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this,tr("Errore di apertura"),tr("Non riesco a caricare il template"));
        return;
    }
    if (!fn.isEmpty())
    {


        QTextStream in(&file);
        QString temp;
        temp = in.readAll();
        currTemplate = parseTemplate(temp);
        recentDir = QFileInfo(file).absoluteDir().absolutePath();
        Editor *editor = new Editor;
        editor->fileNew();
        editor->document()->setHtml(currTemplate);
        editor->show();

    }
}
QString DocumentEdit::parseTemplate(QString &temp)
{
    QString tempFile,line;

    temp.replace("#title#",details.title);
    temp.replace("#name_r#",details.name_r);
    temp.replace("#name#",details.name);
    temp.replace("#company#",details.company);
    temp.replace("#date#",details.date.toString("dd.MM.yyyy"));
    temp.replace("#committ#",details.clientName+"<br/>&nbsp;"+details.clientAddress);
    temp.replace("#albo#",details.albo);
    temp.replace("#notes#",details.notes);
    temp.replace("#potcont#",QString("%L1").arg(ecoParameters.power));
    temp.replace("#loc#",localita.name);
    temp.replace("#albedo#",QString("%L1").arg(localita.albedo));
    if (monthlyProfile < profile.size())
        temp.replace("#profilo#",profile.at(monthlyProfile));
    temp.replace("#consumi#",QString("%L1").arg(yearlyLoad));
    temp.replace("#totpot#","<strong>"+QString("%L1").arg(power)+"kWp</strong>");
    temp.replace("#corrmodel#",models.at(localita.radCorrModel-1));
    temp.replace("#radsorgente#",sources.at(localita.source));
    if (power>200)
        temp.replace("#bt#"," in Media Tensione");
    else
        temp.replace("#bt#"," in Bassa Tensione (BT) (o in MT qualora l'ente distributore lo richieda)");

    if (ecoParameters.regime== Vendita){
            if (loadInterface->zeroLoad())
                temp.replace("#regime#","venduta in toto al");
            else
                temp.replace("#regime#","venduta, al netto degli autoconsumi, al");
        }

    if (ecoParameters.regime== SSPIT){
        temp.replace("#regime#","ceduta secondo il regime di scambio sul posto");
    }
    /************* INSERIMENTO DIAGRAMMA SOLARE ****************************/
    if (solarDiagram!=0){
        QFileInfo pp(projectPath);
        QDir  t(pp.absoluteDir());
        bool a = t.cd("sc.images");
        if (a)
        {
        /* The dir exists */
            if (QFile::exists("sc.images/_~sc_sd_del" +QString::number(documentNum)+"_" +
                              QFileInfo(projectPath).baseName() +".png") )
                QFile::remove("sc.images/_~sc_sd_del" +QString::number(documentNum)+"_" +
                              QFileInfo(projectPath).baseName() +".png");
                tempFile = "sc.images/_~sc_sd_del"+QString::number(documentNum)+"_" +
                   QFileInfo(projectPath).baseName() +".png";
                solarDiagram->exportPNG(tempFile);

        }
        else
        {
        /* The dir does not exist, try to make it */
            a = t.mkdir("sc.images");
            if (a)
            {
                if (QFile::exists("sc.images/_~sc_sd_del" +QString::number(documentNum)+"_" +
                                  QFileInfo(projectPath).baseName() +".png") )
                    QFile::remove("sc.images/_~sc_sd_del" +QString::number(documentNum)+"_" +
                                  QFileInfo(projectPath).baseName() +".png");
            tempFile =  "sc.images/_~sc_sd_del"+QString::number(documentNum)+
               QFileInfo(projectPath).baseName() +".png";
            solarDiagram->exportPNG(tempFile);

            }
            else
            {
               qDebug()<<"DD error in creating dir"<<t.absolutePath()<<tempFile;
             }


        }
        /* Insert schema file */
        QFile f(QCoreApplication::applicationDirPath() + "/bs/schema1.png");
        if (!f.exists())
            QMessageBox::warning(this,tr("Errore di sistema"),tr("Un file di sistema di SC sembra non essere presente nella cartella di installaazione") );

        if (QFile::exists("sc.images/schemalog.png"))
            QFile::remove("sc.images/schemalog.png");

        if (!f.copy("sc.images/schemalog.png"))
        {
            QMessageBox::warning(this,tr("Errore"),tr("Errore di scrittura nella cartella sc.images") );
            qDebug()<<"DD file copy"<< f.error();
        }


    temp.replace("#schemalog#"," <img widht=400 height=400 src=\"sc.images/schemalog.png\" />");
    temp.replace("#solardiag#"," <img width=600 height=600 src=\""+ tempFile + "\"/> ");

}

    line = invString + header;
    if (!system.models.isEmpty() && system.systemValid) {

        for(int i=0;i<system.campiVector.size();i++){

            line += "<tr><td>" + system.models.at(i) +
                    "</td><td>" +
                    QString("%L1").arg(system.efficiencies.at(i)) +
                    "</td><td>" + QString("%L1").arg(system.campiVector.at(i)) +
                    "</td><td>" + QString("%L1").arg(system.panelVector.at(i)) +
                    "</td></tr>";
        }
        line+= "</table>";

    }
    else
    {
        qDebug()<<"DD inverter non presenti";
        line += "<tr><td>-</td></tr></table>";
    }
    temp.replace("#inverter#",line);
    return temp;
}

void DocumentEdit::parseTemplateMore(QString &temp)
{
    temp.replace("#loc#",localita.name);
    temp.replace("#commit#",details.clientName);
    temp.replace("#clientAddress#",details.clientAddress);
    temp.replace("#lat#",   QString("%L1").arg(localita.lat)+"<sup>o</sup>");
    temp.replace("#long#",  QString("%L1").arg(localita.lon)+"<sup>o</sup>");
    temp.replace("#alt#",   QString("%L1").arg(localita.alt)+"m");
    temp.replace("#tilt#",  QString("%L1").arg(localita.incl)+"<sup>o</sup>");
    temp.replace("#shadow#",QString("%L1").arg(opt.totalShadowLossFactor*100)+"%");
    double rad,radh,ene,mT,wind,k;
    rad=ene=mT=wind=radh=0;

    k = (unitRad=="kWh/m2") ? 1 : 1/3.6;

    for(int i=0;i<12;i++)
       {

        ene  += Eset ?  E[i] : 0;
        mT     += opt.temperatures.at(i);
        wind   += opt.wind.at(i);
        }
    temp.replace("#radh#",QString("%L1").arg(localita.radRealeAnnuaOrizzontale)+" kWh/m<sup>2</sup>");
    temp.replace("#rad#",  QString("%L1").arg(localita.radRealeOmbreAnnuaTotale*k)+" kWh/m<sup>2</sup>");
    temp.replace("#eout#",  QString("%L1").arg(ene)+" kWh");
    temp.replace("#temp#", QString("%L1").arg(mT/12)+"<sup>o</sup>");
    temp.replace("#wind#", QString("%L1").arg(wind/12)+" m/sec");
    temp.replace("#pn#",QString("%L1").arg(power) + " Wp");


    QVector<double> Isc, Vmpp, Voc , Im;
    QString a;
            a="/";
    int t,tot;
    bool etereo=false;

    if (system.systemValid && !system.campiVector.isEmpty() && system.campiVector.size()==system.panelVector.size())
    {
        t = system.campiVector.at(0);
        Isc << system.campiVector.at(0)  * panels.isc;
        Im << system.campiVector.at(0)  * panels.imp;
        Vmpp << system.panelVector.at(0) * panels.vmp;
        Voc  << system.panelVector.at(0) * panels.voc;
        tot = system.campiVector.at(0) * system.panelVector.at(0);
        for(int i=1;i<system.campiVector.size();i++)
        {
            if (t!=system.campiVector.at(i))
                etereo= true;
               Isc  << system.campiVector.at(i)*panels.isc;
               Im  << system.campiVector.at(i)*panels.imp;
               Vmpp << system.panelVector.at(i)*panels.vmp;
               Voc  << system.panelVector.at(i)*panels.voc;
               tot += system.campiVector.at(i) * system.panelVector.at(i);
        }

        if (!etereo)
        {
            temp.replace("#vmpp#",QString("%L1").arg(Vmpp.at(0)) + " V");
            temp.replace("#isc#",QString("%L1").arg(Isc.at(0))   + " A");
            temp.replace("#impp#",QString("%L1").arg(Im.at(0))   + " A");
            temp.replace("#voc#",QString("%L1").arg(Voc.at(0))   + " V");
            temp.replace("#conf#",tr("Sistema omogeneo"));
        }
        {
            temp.replace("#vmpp#",MyMath::toString(Vmpp,a) + " V");
            temp.replace("#isc#",MyMath::toString(Isc,a) + " A");
            temp.replace("#impp#",MyMath::toString(Im,a)   + " A");
            temp.replace("#voc#",MyMath::toString(Voc,a) + " V");
            temp.replace("#conf#",tr("Sistema eterogeneo"));
         }


        temp.replace("#totmoduli#",QString("%L1").arg(tot) );
        temp.replace("#stringhe#",QString("%L1").arg(MyMath::cumSum(system.campiVector)) );

       if (panels.isValid)
        {
        temp.replace("#modulo-marca#",panels.fabric+","+panels.model);
        temp.replace("#modulo-pn#",  QString("%L1").arg(panels.pnom)  + " Wp");
        temp.replace("#modulo-vmpp#",QString("%L1").arg(panels.vmp) + " V");
        temp.replace("#modulo-im#",  QString("%L1").arg(panels.imp)  + " A");
        temp.replace("#modulo-voc#", QString("%L1").arg(panels.voc) + " V");
        temp.replace("#modulo-isc#", QString("%L1").arg(panels.isc)  + " A");
        temp.replace("#eff#",QString("%L1").arg(panels.eff) + " %");
       }

   // INVERTER DETAILS //
       temp.replace("#totinverter#", QString("%L1").arg(MyMath::cumSum(system.campiVector)));
       if (MyMath::isEtero(system.models))
       {
           temp.replace("#inverter-marca#","(Vedi nota)");
       }
       else
       {
           temp.replace("#inverter-marca#",system.models.at(0));
           temp.replace("#inverter-pn#",   QString("%L1").arg(system.inverters.at(0).pin) + " W");
           temp.replace("#inverter-in#",   QString("%L1").arg(system.inverters.at(0).imax)+ " A");
           temp.replace("#inverter-vmax#", QString("%L1").arg(system.inverters.at(0).vmax)+ " V");
           temp.replace("#inverter-pca#", QString("%L1").arg(system.inverters.at(0).pnom)+ " W");
           temp.replace("#inverter-vca#", QString("%L1").arg(system.inverters.at(0).vout)+ " V");
           temp.replace("#inverter-ica#", QString("%L1").arg(system.inverters.at(0).imax)+ " A");
           temp.replace("#inverter-icc#", QString("%L1").arg(system.inverters.at(0).icc)+ " A");
           temp.replace("#inverter-eff#", QString("%L1").arg(system.inverters.at(0).eff)+ " %");
           if (system.inverters.at(0).trasformer)
               temp.replace("#inverter-tras#", tr("<p>S&igrave;</p>"));
           else
               temp.replace("#inverter-tras#", tr("<p>No</p>"));
           temp.replace("#inverter-cosf#", QString("%L1").arg(system.inverters.at(0).cosphi));

       }

    }

}
void DocumentEdit::addYearlyLoad(double a)
{
    yearlyLoad = a;
}
void DocumentEdit::addMonthlyProfile(int a)
{
    monthlyProfile = a;
}
