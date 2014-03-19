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

    this->spe = new SpacePressEater(this->textArea, this);
    textArea->installEventFilter(this->spe);
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
