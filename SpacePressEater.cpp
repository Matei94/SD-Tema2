#include "SpacePressEater.h"

SpacePressEater::SpacePressEater(MainWindow *boss)
{
    this->boss = boss;
    this->delim = " ";
}

bool SpacePressEater::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
       QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
       //std::cout << "Ate key press ";// << keyEvent->key();

       if (keyEvent->key() == Qt::Key_Space) {
           this->boss->textArea->insertPlainText(this->delim);
           this->boss->sendNewText();
           qDebug("Spatiu");
           return true;
       }

       return false;

    } else {
       // standard event processing
       return QObject::eventFilter(obj, event);

    }
}
