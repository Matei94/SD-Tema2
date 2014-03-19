#include <QObject>
#include <QKeyEvent>
#include <QEvent>
#include <iostream>

class SpacePressEater : public QObject
 {
     Q_OBJECT

 public:
     bool eventFilter(QObject *obj, QEvent *event) {
	     if (event->type() == QEvent::KeyPress) {
	     	QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
	     	//std::cout << "Ate key press ";// << keyEvent->key();
	     	if (keyEvent->key() == Qt::Key_Space) {
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