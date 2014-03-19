#ifndef SPACEEATER_H
#define SPACEEATER_H

#include <QObject>
#include <QKeyEvent>
#include <QEvent>
#include <iostream>
#include <QTextEdit>
#include <QScrollBar>
#include <QTextCursor>
#include "mainwindow.h"

class MainWindow;

class SpacePressEater : public QObject
{
     Q_OBJECT

    QTextEdit *boss;
    QString delim;
    MainWindow *newboss;

public:
    SpacePressEater(QTextEdit *boss, MainWindow *newboss);
    bool eventFilter(QObject *obj, QEvent *event);
 };

#endif
