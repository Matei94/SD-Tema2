#ifndef SPACEEATER_H
#define SPACEEATER_H

#include <QObject>
#include <QKeyEvent>
#include <QEvent>
#include <iostream>
#include <QTextEdit>
#include <QScrollBar>
#include <QTextCursor>


class SpacePressEater : public QObject
{
     Q_OBJECT

    QTextEdit *boss;
    QString delim;

public:
    SpacePressEater(QTextEdit *boss) {
        this->boss = boss;
        this->delim = " ";
    }


     bool eventFilter(QObject *obj, QEvent *event) {
	     if (event->type() == QEvent::KeyPress) {
	     	QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
	     	//std::cout << "Ate key press ";// << keyEvent->key();
	     	if (keyEvent->key() == Qt::Key_Space) {
                this->boss->insertPlainText(this->delim);
	     		qDebug("Spatiu");
	     		return true;
	     	}
	        return false;
	     } else {
	        // standard event processing
	       	return QObject::eventFilter(obj, event);
	     }
     }
 };

#endif
