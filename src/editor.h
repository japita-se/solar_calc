#ifndef EDITOR_H
#define EDITOR_H

#include <QTextEdit>
static int documentNum = 1;
class QAction;
class tableprop;
class Editor : public QTextEdit
{
    Q_OBJECT;
public:
    Editor(QWidget* parent=0);

public:
    QString getRecentDir();

    void setRecentDir(QString &a);
    void fileNew();
    bool fileSave();
    bool fileSaveAs();
    bool save();
    bool saveAs();
    bool open();
    void close_(QCloseEvent *e);
    void insertImage();
    void insertTable();
    bool openFile(const QString &fileName);
    QAction *windowMenuAction() const { return action; }

public slots:
    void setCurrentFile(const QString &fileName);
//    void fileOpen();
//    bool fileSave();
//    bool fileSaveAs();
//    void filePrint();
//    void filePrintPreview();
//    void filePrintPdf();
//
//    void textBold();
//    void textUnderline();
//    void textItalic();
//    void textFamily(const QString &f);
//    void textSize(const QString &p);
//    void textStyle(int styleIndex);
//    void textColor();
//    void textAlign(QAction *a);
//
//    void currentCharFormatChanged(const QTextCharFormat &format);
//    void cursorPositionChanged();
//
//    void clipboardDataChanged();
//
//    void printPreview(QPrinter *);
protected:
    void closeEvent(QCloseEvent* event);
private slots:

    void documentWasModified();
private:
    bool writeFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    bool readFile(const QString &fileName);
    bool okToContinue();
    QString strippedName(const QString &fullFileName);
private:
    QAction* action;
    QString fileFilters;
    QString curFile,fileName,recentDir;
    tableprop *table;

    bool isUntitled;

};

#endif // EDITOR_H
