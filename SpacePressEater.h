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

    QString delim;
    MainWindow *boss;

public:
    SpacePressEater(MainWindow *boss);
    bool eventFilter(QObject *obj, QEvent *event);
 };

#endif
