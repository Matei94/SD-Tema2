#include "SpacePressEater.h"

SpacePressEater::SpacePressEater(QTextEdit *boss, MainWindow *newboss)
{
    this->boss = boss;
    this->delim = " ";
    this->newboss = newboss;
}

bool SpacePressEater::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
       QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
       //std::cout << "Ate key press ";// << keyEvent->key();

       if (keyEvent->key() == Qt::Key_Space) {
           this->newboss->textArea->insertPlainText(this->delim);
           qDebug("Spatiu");
           return true;
       }

       return false;

    } else {
       // standard event processing
       return QObject::eventFilter(obj, event);

    }
}
