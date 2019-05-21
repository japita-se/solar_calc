

#ifndef DocumentEdit_H
#define DocumentEdit_H
#include "data.h"

#include <QMainWindow>
#include <QMap>
#include <QPointer>

QT_FORWARD_DECLARE_CLASS(QAction)
QT_FORWARD_DECLARE_CLASS(QComboBox)
QT_FORWARD_DECLARE_CLASS(QFontComboBox)
QT_FORWARD_DECLARE_CLASS(QTextEdit)
QT_FORWARD_DECLARE_CLASS(QTextCharFormat)
QT_FORWARD_DECLARE_CLASS(QMenu)
QT_FORWARD_DECLARE_CLASS(QToolBar)
QT_FORWARD_DECLARE_CLASS(TextPrinter)
QT_FORWARD_DECLARE_CLASS(QWorkspace)
QT_FORWARD_DECLARE_CLASS(Editor)
class QwtPlot;
class MyPlot;
class Load;
class DocumentEdit : public QMainWindow
{
    Q_OBJECT

public:
    DocumentEdit(QWidget *parent = 0);
    void addYearlyLoad(double a);
    void addMonthlyProfile(int a);
    void setFooter(const QString &s);
    void setHeader(const QString &s);
    void setSystem(sy a);
    void setConsumi(Load *p);
    void setProjectPath(QString &a);
    void addSystem(sy a);
    void addVanDiagram(const QwtPlot* p);
    void addRawDiagram(const QwtPlot* p);
    void addSolarRadiation(const QwtPlot* p);
    void addSolarRadiation2(const QwtPlot* p);
    void addEEnergy(const QwtPlot* p);
    void setVersion(const QString &version);
    void addLocation(loc localita);
    void addPanel(panel p);
    void addInverter(inverter inv);
    void addOption(option o);
    void addRad(  double *H);
     void addRadh(  double *H);
    void addEnergy(  double *E);
    void addUnitRad(const QString &s);
   // void addUnitRadh(const QString &s);
    void addUnitEnergy(const QString &s);
    void addTotEnergy(double a);
    void addSolarDiagram(MyPlot *p);
    void addEco(ecopara eco);
    void setPower(double d);


protected:
    virtual void closeEvent(QCloseEvent *e);

private:
    void    parseHeader();
    QString parseTemplate(QString &a);
    void parseTemplateMore(QString &a);
    Editor* activeEditor();
    QString readTemplateFile(const QString& a);
    void setupMenu();
    void setupModelsActions();
    void setupFileActions();
    void setupEditActions();
    void setupTextActions();
    void load(const QString &f);
    bool maybeSave();
    void setCurrentFileName(const QString &fileName);

public slots:
    void setDesigner(designer de);
    void setHeaderText(QString& a);
    void setFooterText(QString& a);

private slots:

    void getFont();
    void loadModGenerale();
    void loadTemplate();
    void loadEnel();
    void loadTSheet();

    Editor* createEditor();
    void updateMenus();
    void fileNew();
    void fileOpen();
    void fileSave();
    void fileSaveAs();
    void filePrint();
    void filePrintPreview();
    void filePrintPdf();

    void cut();
    void copy();
    void paste();
    void image();
    void table();

    void textBold();
    void textUnderline();
    void textItalic();
    void textFamily(const QString &f);
    void textSize(const QString &p);
    void textStyle(int styleIndex);
    void textColor();
    void textAlign(QAction *a);

    void currentCharFormatChanged(const QTextCharFormat &format);
    void cursorPositionChanged();

    void clipboardDataChanged();

    void printPreview(QPrinter *);

private:

    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
    void fontChanged(const QFont &f);
    void colorChanged(const QColor &c);
    void alignmentChanged(Qt::Alignment a);

    QAction *actionNew,
        *actionOpen,
        *actionPrint,
        *actionPrintPreview,
        *actionSave,
        *actionSaveAs,
        *actionPdf,
        *actionQuit,
        *actionTextBold,
        *actionTextUnderline,
        *actionTextItalic,
        *actionTextColor,
        *actionAlignLeft,
        *actionAlignCenter,
        *actionAlignRight,
        *actionAlignJustify,
        *actionUndo,
        *actionRedo,
        *actionCut,
        *actionCopy,
        *actionPaste,
        *actionImage,
        *actionTable,
        *a_modello_generale,
        *a_enel,
        *a_scheda_tecnica,
        *a_modello_custom;
        QAction *closeAction;
        QAction *closeAllAction;
        QAction *tileAction;
        QAction *cascadeAction;
        QAction *nextAction;
        QAction *previousAction,*separatorAction;

    QComboBox *comboStyle;
    QFontComboBox *comboFont;
    QComboBox *comboSize;
    QMenu* menu,*menuEdit,*windowMenu;

    QToolBar *tb;
    QString fileName,headerText,
            footerText,coverPage,
            techPage,projectPath,
            recentDir,
            invString,header,unitRad,currTemplate;
    QStringList models,sources,profile;
    QTextEdit *textEdit;
    QWorkspace* workspace;
    Load *loadInterface;

    double yearlyLoad;
    int    monthlyProfile;
    double power;
    double* H,*E,*Hg;
    bool Hset,Hgset,Eset;

    TextPrinter* textprinter_;
    designer details;
    MyPlot* solarDiagram;
    ecopara ecoParameters;
    loc localita;
    option opt;
    panel panels;
    sy system;

    enum{
    Vendita,
    SSPIT,
    SSP
    };

};

#endif
