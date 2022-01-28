/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "codeeditor.h"

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
CodeEditor::CodeEditor(QWidget *parent, QString fileName)
    : QMainWindow(parent)
{
    m_FileName = fileName;

    m_sSettingsFile = INI_FILE;

    setupFileMenu();
    setupHelpMenu();
    setupToolsMenu();
    setupToolBar();

    m_textEdit = new QsciScintilla;
    setCentralWidget(m_textEdit);

    m_textEdit->setCaretLineVisible(true);
    m_textEdit->setCaretLineBackgroundColor(QColor("gainsboro"));

    m_textEdit->setAutoIndent(true);
    m_textEdit->setIndentationGuides(false);
    m_textEdit->setIndentationsUseTabs(true);
    m_textEdit->setIndentationWidth(4);

    m_textEdit->setMarginsBackgroundColor(QColor("gainsboro"));
    m_textEdit->setMarginLineNumbers(1, true);
    m_textEdit->setMarginWidth(1, 50);

    m_textEdit->setAutoCompletionSource(QsciScintilla::AcsAll);
    m_textEdit->setAutoCompletionReplaceWord(true);
    m_textEdit->setAutoCompletionCaseSensitivity(false);
    m_textEdit->setAutoCompletionUseSingle(QsciScintilla::AcusAlways);
    m_textEdit->setAutoCompletionThreshold(0);

    m_textEdit->setBraceMatching(QsciScintilla::SloppyBraceMatch);
    m_textEdit->setMatchedBraceBackgroundColor(Qt::yellow);
    m_textEdit->setUnmatchedBraceForegroundColor(Qt::blue);

    QsciLexerPython *m_lexer = new QsciLexerPython(this);
    m_textEdit->setLexer(m_lexer);

    setupEditor();

    resize(QDesktopWidget().availableGeometry(this).size() * 0.8);

    setWindowTitle(tr("Startup Script Editor") + " - " + m_FileName);
 }

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void CodeEditor::about()
{
    QMessageBox::about(this, tr("About Python Startup Script Editor"),
                tr("<p>The <b>Syntax Highlighter</b> example shows how " \
                   "to perform simple syntax highlighting by subclassing " \
                   "the QSyntaxHighlighter class and describing " \
                   "highlighting rules using regular expressions.</p>"));
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void CodeEditor::newFile()
{
    m_textEdit->clear();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void CodeEditor::saveFile()
{
    QString fileName = m_FileName;

    if (!fileName.isEmpty()) {

        QFile file(fileName);

        if (file.open(QFile::WriteOnly | QFile::Text)) {

            QTextStream stream(&file);
            stream << m_textEdit->text();

            m_textEdit->setModified(false);

            statusBar()->showMessage(tr("File successfull saved..."));
        }
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void CodeEditor::setupEditor()
{
    QFile file(m_FileName);
    if (file.open(QFile::ReadWrite | QFile::Text)) {
        m_textEdit->setText(file.readAll());
    }

    m_textEdit->setModified(false);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void CodeEditor::setupFileMenu()
{
    QMenu *fileMenu = new QMenu(tr("&File"), this);
    menuBar()->addMenu(fileMenu);

    fileMenu->addAction(tr("&Save..."), this, SLOT(saveFile()), QKeySequence::Save);
    fileMenu->addAction(tr("E&xit"), this, SLOT(closeEditor()), QKeySequence::Quit);
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void CodeEditor::closeEditor()
{
    this->close();
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void CodeEditor::openSettingFont()
{
    bool ok;

    QFont font = QFontDialog::getFont(
                    &ok,
                    QFont( "Arial", 18 ),
                    this,
                    tr("Pick a font") );

    if (true) {
        m_lexer->setDefaultFont(font );
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void CodeEditor::setupToolsMenu()
{
    QMenu *toolMenu = new QMenu(tr("&Settings"), this);
    menuBar()->addMenu(toolMenu);

    toolMenu->addAction(tr("Font"), this, SLOT( openSettingFont() ) );
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void CodeEditor::setupHelpMenu()
{
    QMenu *helpMenu = new QMenu(tr("&Help"), this);
    menuBar()->addMenu(helpMenu);

    helpMenu->addAction(tr("&About"), this, SLOT(about()));
    helpMenu->addAction(tr("About &Qt"), qApp, SLOT(aboutQt()));
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void CodeEditor::setFileName(QString fileName) {

    m_FileName = fileName;
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void CodeEditor::compileFile() {

    QStringList arguments;
    QString     output;

    saveFile();

    QString program = "pylint";

    arguments << "--max-line-length=240" << m_FileName;

    qDebug() << "start..." << program << arguments << m_stdOutLines;

    this->ExecuteProgram(program, arguments, true, false);

    qDebug() << "finish..." << program << m_stdOutLines;

    foreach (QString line, m_stdOutLines) {
       output = output + line + "\n";
    }

    QMessageBox::information(this, "PyLint output...", output );
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void CodeEditor::setupToolBar()
{
    QToolBar *fileToolBar = addToolBar(tr("File"));

    QAction *exitAct = new QAction(QIcon(":/icon/toolbar/blue/images/toolbar/blue/exit.ico"), tr("Ex&it"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("close the editor"));

    connect(exitAct, SIGNAL(triggered()), this, SLOT( closeEditor() ) );

    fileToolBar->addAction( exitAct );

    QAction *saveAct = new QAction(QIcon(":/icon/farious/blue/images/farious/blue/save.ico"), tr("Sav&e"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Cut the current selection's contents to the clipboard"));

    connect(saveAct, SIGNAL(triggered()), this, SLOT( saveFile() ) );

    fileToolBar->addAction( saveAct );

    QAction *compileAct = new QAction(QIcon(":/icon/farious/blue/images/farious/blue/magic.ico"), tr("C&ompile"), this);

    compileAct->setStatusTip(tr("Compiles the script with AutoIt"));

    connect(compileAct, SIGNAL(triggered()), this, SLOT( compileFile() ) );

    fileToolBar->addAction( compileAct );
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void CodeEditor::closeEvent(QCloseEvent *event) {

    if ( m_textEdit->isModified() ) {

        QMessageBox msgBox;

        msgBox.setWindowTitle("Startup Script Editor");
        msgBox.setText("File was changed - Save?");

        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.addButton(QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Yes);

        int retVal = msgBox.exec();

        if(retVal == QMessageBox::Yes){
            saveFile();
        } else if(retVal == QMessageBox::Cancel){
            event->ignore();
        }
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void CodeEditor::printOutput()
{
    QByteArray byteArray = m_proc->readAllStandardOutput();

    m_stdOutLines.clear();
    m_stdOutLines = QString(byteArray).split("\n");

    foreach (QString line, m_stdOutLines){
       qDebug() << "-I-" << line;
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
void CodeEditor::printError()
{
    QByteArray byteArray = m_proc->readAllStandardError();

    m_stdErrLines.clear();
    m_stdErrLines = QString(byteArray).split("\n");

    foreach (QString line, m_stdErrLines){
       qDebug() << "-E-" << line;
    }
}

/**********************************************************************************************************************
 *
 *********************************************************************************************************************/
bool CodeEditor::ExecuteProgram(QString program, QStringList arguments, bool wait, bool exitinfo) {

    bool retVal = true;
    QString errorLine;
    QString infotxt;

    m_stdErrLines.clear();
    m_stdOutLines.clear();

    m_proc = new QProcess;

    connect (m_proc, SIGNAL(readyReadStandardOutput()), this, SLOT(printOutput()));
    connect (m_proc, SIGNAL(readyReadStandardError()), this, SLOT(printError()));

    qDebug() << "start..." << QDir::toNativeSeparators(program) << arguments;

    QString value = m_settings.loadStringSetting(m_sSettingsFile, "Executables", program);
    if ( value.isEmpty() ) {

        QString exeFile = QFileDialog::getOpenFileName(this, tr("ExecuteProgram: exe not found! ..." ) + program, QDir::homePath()  );

        m_settings.saveStringSetting(m_sSettingsFile, "Executables", program, exeFile);

        program = exeFile;

    } else {

        QFileInfo fi( QDir::toNativeSeparators(value) );

        if ( ! fi.exists() ) {

            m_settings.Delete(m_sSettingsFile, "Executables", program);

            value = QFileDialog::getOpenFileName(this, tr("ExecuteProgram: exe not found! ..." ) + program, QDir::homePath()  );

            m_settings.saveStringSetting(m_sSettingsFile, "Executables", program, value);

            program = value;

        } else {

            program = value;
        }
    }

    QFileInfo fi( QDir::toNativeSeparators(program) );

    m_proc->setWorkingDirectory(fi.absolutePath());
    m_proc->setProcessChannelMode(QProcess::MergedChannels);

#ifdef WIN32
    if ( arguments.isEmpty() ) {
        m_proc->start("\"" + QDir::toNativeSeparators(program) + "\"");
    } else {
        m_proc->start("\"" + QDir::toNativeSeparators(program) + "\"", arguments);
    }
#endif

#ifdef linux
    if ( arguments.isEmpty() ) {
        m_proc->start( QDir::toNativeSeparators(program) );
    } else {
        m_proc->start( QDir::toNativeSeparators(program) , arguments);
    }
#endif

    if (wait) {

        while ( m_proc->state() == QProcess::Running ) {

            QCoreApplication::processEvents();

            QThread::msleep(100);
        } ;

        if ( m_proc->waitForFinished(-1) ) {

            if ( m_proc->exitCode() != 0 && exitinfo ) {

                errorLine.clear();

                if ( ! m_stdErrLines.isEmpty() ) {
                    foreach (QString line, m_stdErrLines){
                        if ( ! line.isEmpty() )
                            errorLine.append(line);
                    }
                }

                qDebug() << m_stdErrLines;
                qDebug() << errorLine;

                infotxt = QString("Something went wrong - %1\n\n%2\n\nExitCode: %3\n\nContinue?").arg(program).arg(errorLine).arg(m_proc->exitCode());

                qDebug() << infotxt;

                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(this, this->windowTitle(), infotxt , QMessageBox::Yes|QMessageBox::No );

                if (reply == QMessageBox::Yes) {
                } else {
                    retVal = false;
                }
            } else {
                qDebug() << "ExecuteProgram" << program << m_proc->exitCode();
            }

            delete m_proc;

        } else {
            retVal = false;
        }
    }

    return(retVal);
}
