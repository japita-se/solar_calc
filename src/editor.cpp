#include "editor.h"
#include "tableprop.h"

#include <QtGui>

Editor::Editor(QWidget* parent) : QTextEdit(parent)
{
    table = new tableprop;
    action = new QAction(this);
    action->setCheckable(true);
    connect(action, SIGNAL(triggered()),SLOT(show()));
    connect(action,SIGNAL(triggered()),SLOT(setFocus()));
    recentDir = QDir::homePath();

    isUntitled = true;
    fileFilters = tr("File testo (*.txt)\n"
                 "Html (*.html)\n"
                 "Tutti i file (*)");

    connect(document(),SIGNAL(contentsChanged()),SLOT(documentWasModified()));

    setWindowIcon(QPixmap(":/images/document.png"));
    setAttribute(Qt::WA_DeleteOnClose);
}

void Editor::fileNew()
{

    curFile = tr("documento%1.txt").arg(documentNum);
    setWindowTitle(curFile + "[*]");
    action->setText(curFile);
    isUntitled = true;
    ++documentNum;
}
bool Editor::open()
{
    QString fileName =
            QFileDialog::getOpenFileName(this, tr("Open"), recentDir,
                                         fileFilters);
    if (fileName.isEmpty())
        return false;

    recentDir = QFileInfo(fileName).absoluteDir().absolutePath();
    return openFile(fileName);
}
void Editor::setRecentDir(QString &a)
{
    recentDir = a;
}

QString Editor::getRecentDir()
{
    return recentDir;
}

bool Editor::openFile(const QString &fileName)
{
    if (readFile(fileName)) {
        setCurrentFile(fileName);
        return true;
    } else {
        return false;
    }
}
bool Editor::readFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Gestione documenti"),
                             tr("Non riesco a leggere il file %1:\n%2.")
                             .arg(file.fileName())
                             .arg(file.errorString()));
        return false;
    }

    QApplication::setOverrideCursor(Qt::WaitCursor);
    QTextStream in(&file);
    QByteArray data = file.readAll();
    QTextCodec *codec = Qt::codecForHtml(data);
    QString str = codec->toUnicode(data);
      if (Qt::mightBeRichText(str)) {
           setHtml(str);
        } else {
             str = QString::fromLocal8Bit(data);
             setPlainText(str);
        }

    QApplication::restoreOverrideCursor();
    return true;
}

void Editor::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    isUntitled = false;
    action->setText(strippedName(curFile));
    document()->setModified(false);
    setWindowTitle(strippedName(curFile) + "[*]");
    setWindowModified(false);
}
bool Editor::fileSaveAs()
{
    QString fn = QFileDialog::getSaveFileName(this, tr("Salva come..."),
                                              recentDir, tr("HTML-Files (*.htm *.html);;ODF files (*.odt);;All Files (*)"));
    if (fn.isEmpty())
        return false;
    recentDir = QFileInfo(fileName).absoluteDir().absolutePath();
    if (! (fn.endsWith(".odt", Qt::CaseInsensitive) || fn.endsWith(".htm", Qt::CaseInsensitive) || fn.endsWith(".html", Qt::CaseInsensitive)) )
        fn += ".odt"; // default
    setCurrentFile(fn);
    return fileSave();
}
void Editor::closeEvent(QCloseEvent *event)
{
    if (okToContinue()) {
        event->accept();
        documentNum = documentNum == 0 ? 0 : documentNum--;
    } else {
        event->ignore();
    }
}
bool Editor::okToContinue()
{
    if (document()->isModified()) {
        int r = QMessageBox::warning(this, tr("Gestione documenti"),
                        tr("<p>File %1 &egrave; stato modificato.</p>"
                           "Vuoi salvare le modifiche?")
                        .arg(strippedName(curFile)),
                        QMessageBox::Yes | QMessageBox::Default,
                        QMessageBox::No,
                        QMessageBox::Cancel | QMessageBox::Escape);
        if (r == QMessageBox::Yes) {
            return save();
        } else if (r == QMessageBox::Cancel) {
            return false;
            if (r == QMessageBox::No){
                documentNum = documentNum == 0 ? 0 : documentNum--;

                return false;
                }
        }
    }
    return true;
}
bool Editor::save()
{
    if (isUntitled) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}
bool Editor::fileSave()
{
    if (fileName.isEmpty())
        return saveAs();


    QTextDocumentWriter writer(fileName);
    bool success = writer.write(document());
    if (success)
        document()->setModified(false);
    return success;
}
bool Editor::saveAs()
{

    QString fn = QFileDialog::getSaveFileName(this, tr("Salva come..."),
                                          QString(), tr("HTML-Files (*.htm *.html);;ODF files (*.odt);;All Files (*)"));

     if (! (fn.endsWith(".odt", Qt::CaseInsensitive) || fn.endsWith(".htm", Qt::CaseInsensitive) || fn.endsWith(".html", Qt::CaseInsensitive)) )

         if (fn.isEmpty())
               return false;

         if (! (fn.endsWith(".odt", Qt::CaseInsensitive) || fn.endsWith(".htm", Qt::CaseInsensitive) || fn.endsWith(".html", Qt::CaseInsensitive)) )
               fn += ".odt"; // default
           //setCurrentFileName(fn);

           return saveFile(fn);

}
bool Editor::writeFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("SC - Gestione documenti"),
                             tr("Non riesco a scrivere il file %1:\n%2.")
                             .arg(file.fileName())
                             .arg(file.errorString()));
        return false;
    }


    QTextDocumentWriter writer(fileName);
    bool success = writer.write(document());
    if (success)
        document()->setModified(false);

    return success;


}

bool Editor::saveFile(const QString &fileName)
{
    if (writeFile(fileName)) {
        qDebug()<<"EDITOR writeFile";
        setCurrentFile(fileName);
        return true;
    } else {
        return false;
    }
}


void Editor::documentWasModified()
{
    setWindowModified(true);
}
QString Editor::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}
void Editor::insertTable()
{
    int col,row,border,width,align,cellpadding,cellspacing;

    QString s="";
    qDebug()<<"EDITOR siamo qua";
    if (table->exec())
    {
         border = table->getBorder();
         col    = table->getCols();
         row    = table->getRows();
         width  = table->getWidth();
         align  = table->getAlign();
         cellpadding = table->getCellpadding();
         cellspacing = table->getCellpadding();


    switch (align)
    {
        case 1:
        s = "<center>";
        break;
    case 2:
        s = "<div align=\"right\">";
        break;
    }
    s += "<table border=" + QString::number(border)
                          +" width="  + QString::number(width) +
                          "% cellspacing=" + QString::number(cellspacing) +
                          " cellpadding=" + QString::number(cellpadding) + ">";
    for(int i=0;i<row;i++){
        s += "<tr>";
        for(int j=0;j<col;j++)
             s += "<td></td>";
        s += "</tr>";
    }
    s += "</table>";
    switch (align)
    {
        case 1:
        s += "</center>";
        break;
        s += "</div>";
        break;
    }
    QTextDocumentFragment fragment = QTextDocumentFragment::fromHtml(s);
    this->textCursor().insertFragment(fragment);
    qDebug()<<"EDITOR "<<fragment.toPlainText()<<s<<col<<row;
     }
}
void Editor::insertImage()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Carica immagine..."),
                                                QString(), tr("Image files(*.jpeg *.png *.gif *.tif *bmp);;All Files (*)"));

    if (!file.isEmpty())
    {
        QFile f(file);
        if (f.open(QIODevice::ReadOnly))
        {
                //
                QTextDocumentFragment fragment = QTextDocumentFragment::fromHtml(("<img src=\""+file+"\""));
                this->textCursor().insertFragment(fragment);
                qDebug()<<"EDITOR "<<fragment.toPlainText();
        }
        else
         qDebug()<<"EDITOR ERROR A ";

    }
    else
         qDebug()<<"EDITOR ERROR B";
}
void Editor::close_(QCloseEvent *e)
{
    closeEvent(e);
}
