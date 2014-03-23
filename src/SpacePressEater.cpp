#include "SpacePressEater.h"
#define DELMODE 0
#define NORMMODE 1

SpacePressEater::SpacePressEater(MainWindow *boss)
{
    this->boss = boss;
    this->delim = " ";
    this->mode = NORMMODE;
    this->sel_start = 0;
    this->sel_end = 0;
    this->insertAtMiddle = false;
}

bool SpacePressEater::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
       QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        //std::cout << "mode: " << this->mode << "\n";

        // Manage backspace key press
        if (keyEvent->key() == Qt::Key_Backspace) {
            if (this->mode == NORMMODE) {
                if (!this->boss->selectWordAtCursor()) {
                    return false;
                }

                this->mode = DELMODE;
                this->sel_start = this->boss->textArea->textCursor().selectionStart();
                this->sel_end = this->boss->textArea->textCursor().selectionEnd();


            } else if (this->mode == DELMODE) {
                // Cut only if the selection is still valid
                if (this->sel_start == this->boss->textArea->textCursor().selectionStart() &&
                       this->sel_end == this->boss->textArea->textCursor().selectionEnd()) {
                    this->boss->Cut();
                }

                this->mode = NORMMODE;
                this->sel_start = this->sel_end = 0;
            }

            return true;
        }

        this->mode = NORMMODE;

        // Manage space key press
        if (keyEvent->key() == Qt::Key_Space) {
            return this->manageSpaceKeyPress();
        }

        return false;

    } else {
        // Standard event processing
        return QObject::eventFilter(obj, event);
    }
}

bool SpacePressEater::manageSpaceKeyPress() {
    const QString text = this->boss->textArea->toPlainText();
    QTextCursor cursor = this->boss->textArea->textCursor();

    // We are in the middle of a word (that includes just at it's end
    /*
    if (cursor.position() - 1 >= -1 && ' ' != text.at(cursor.position() - 1)) {
        int oldPos = cursor.position();

        cursor.movePosition(QTextCursor::EndOfWord);

        if (text.at(cursor.position()) == ' ') {
           cursor.movePosition(QTextCursor::StartOfWord);
           this->boss->textArea->setTextCursor(cursor);
           return true;

        } else {
            cursor.setPosition(oldPos);
        }
    }
    */
    this->boss->textArea->insertPlainText(this->delim);
    this->boss->sendNewText();

    return true;
}
