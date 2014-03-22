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

    int oldPos = cursor.position();

    if (cursor.position() - 1 > 0 && ' ' == text.at(cursor.position() - 1)) {
        cursor.movePosition(QTextCursor::StartOfWord);
        this->boss->textArea->setTextCursor(cursor);
        return true;
    }

    this->boss->sendNewText();
    this->boss->textArea->insertPlainText(this->delim);

    return true;

    // Cursor is at the end of document
    /*
    if (cursor.atEnd()) {
        this->boss->textArea->insertPlainText(this->delim);

        this->insertAtMiddle = false;

        qDebug("atEnd");
        return true;
    }
    
    this->insertAtMiddle = true;

    if (!insertAtMiddle) {
        // Cursor is in the middle of the word
        if (cursor.position() - 1 > 0 && ' ' != text.at(cursor.position() - 1)) {
            // Move cursor at the begining of the current word
            cursor.movePosition(QTextCursor::StartOfWord);
            this->boss->textArea->setTextCursor(cursor);

            this->insertAtMiddle = true;
            this->newWordStart = cursor.position();

            qDebug("iM false");
            return true;
        }

        if (cursor.position() - 1 > 0 && ' ' == text.at(cursor.position() - 1)) {
            this->insertAtMiddle = true;
            this->newWordStart = cursor.position();

            qDebug("DO NOTHING");
            return true;
        }
    } else {
        if (cursor.position() - 1 > 0 && ' ' != text.at(cursor.position() - 1)) {
            cursor.movePosition(QTextCursor::StartOfWord);
            this->boss->textArea->setTextCursor(cursor);
        }

            cursor.setPosition(oldPos);
            this->boss->sendNewText();
            this->boss->textArea->insertPlainText(this->delim);


                qDebug("Aleluia");
                return true;
            } else {
                cursor.setPosition(oldPos);

                qDebug("BAD BAD BAD");
                return true;
            }
        }
    }

    return false;
    */
}
