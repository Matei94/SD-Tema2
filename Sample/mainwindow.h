#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QScrollBar>
#include <QTextCursor>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    static int height;
    static int width;
    QTextEdit *textArea;

private slots:
    void Cut();
    void Copy();
    void Paste();
    void Undo();
    void Redo();
    void Save();
};

#endif // MAINWINDOW_H
