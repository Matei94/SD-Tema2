#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SpacePressEater.h"

#include <iostream>

int MainWindow::height = 640;
int MainWindow::width = 480;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("SD super editor");
    this->resize(this->height, this->width);

    //Cut button
    QPushButton *cut = new QPushButton("cut", this);
    cut->setGeometry(1, 16, 35, 25);
    connect(cut, SIGNAL(clicked()), this, SLOT(Cut()));

    //Copy button
    QPushButton *copy = new QPushButton("copy", this);
    copy->setGeometry(37, 16, 35, 25);
    connect(copy, SIGNAL(clicked()), this, SLOT(Copy()));

    //Paste button
    QPushButton *paste = new QPushButton("paste", this);
    paste->setGeometry(73, 16, 35, 25);
    connect(paste, SIGNAL(clicked()), this, SLOT(Paste()));

    //Undo button
    QPushButton *undo = new QPushButton("undo", this);
    undo->setGeometry(108, 16, 35, 25);
    connect(undo, SIGNAL(clicked()), this, SLOT(Undo()));

    //Redo button
    QPushButton *redo = new QPushButton("redo", this);
    redo->setGeometry(144, 16, 35, 25);
    connect(redo, SIGNAL(clicked()), this, SLOT(Redo()));

    //Save button
    QPushButton *save = new QPushButton("save", this);
    save->setGeometry(400, 16, 35, 25);
    connect(save, SIGNAL(clicked()), this, SLOT(Save()));

    //Text area
    this->textArea = new QTextEdit(this);
    this->textArea->setGeometry(1, 50, 638, 429);

    this->spe = new SpacePressEater(this);
    textArea->installEventFilter(this->spe);
}

// Function that gets called each time we get a space_button press
// Sends to the backend the last piece of added text and
void MainWindow::sendNewText()
{
    const QString text = this->textArea->toPlainText();
    int start = text.lastIndexOf(' ', this->textArea->textCursor().position() - 2) + 1;
    int len = text.indexOf(' ', start + 1) - start;

    std::cout << "New text \"" << text.mid(start, len).toUtf8().constData() << "\" from " << start << std::endl;
}

bool MainWindow::selectWordAtCursor()
{
    int old_pos = -1;
    const QString text = this->textArea->toPlainText();
    QTextCursor cursor = this->textArea->textCursor();

    // Don't erase the first word
    old_pos = cursor.position();
    cursor.movePosition(QTextCursor::Left);

    // We're on the first position in text, don't select anything
    if (old_pos == cursor.position()) {
        std::cout << "case 1\n";
        return false;
    }

    // Use StartOfWord and EndOfWord selection only when we have
    // a valid word (lenght > 0)
    if (cursor.position() - 1 > 0 && ' ' != text.at(cursor.position() - 1)) {

        // Position the cursor
        cursor.movePosition(QTextCursor::StartOfWord);
        std::cout << cursor.anchor() << " " << cursor.position() << " \n";
        cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);

    }
    // We should select only words that have 1 space after them
    // (That have been submitted already)
    old_pos = cursor.position();
    cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor);
    std::cout << cursor.anchor() << " " << cursor.position() << " \n";

    if (old_pos == cursor.position()) {
        std::cout << "case 2\n";
        return false;
    }


    // Since we can't alter the text cursor in the text area directly we need
    // to replace the cursor with ours
    QTextCursor &x = cursor;
    this->textArea->setTextCursor(x);

    std::cout << "case ok\n";
    return true;
}

void MainWindow::Cut()
{
    QTextCursor cursor = this->textArea->textCursor();
    int start = cursor.selectionStart();
    int stop = cursor.selectionEnd();

    std::cout << "Cut from " << start << " to " << stop << "\n";
}

void MainWindow::Copy()
{
    QTextCursor cursor = this->textArea->textCursor();
    int start = cursor.selectionStart();
    int stop = cursor.selectionEnd();

    std::cout << "Copy from " << start << " to " << stop << "\n";
}

void MainWindow::Paste()
{
    QTextCursor cursor = this->textArea->textCursor();
    int position = cursor.position();

    std::cout << "Paste at " << position << "\n";
}

void MainWindow::Undo()
{
    std::cout << "Undo\n";
}

void MainWindow::Redo()
{
    std::cout << "Redo\n";
}

void MainWindow::Save()
{
    std::cout << this->textArea->toPlainText().toUtf8().constData() << std::endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}
