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

        // Avoid writing at begging of words
        int key = keyEvent->key();
        const QString text = this->boss->textArea->toPlainText();
        QTextCursor cursor = this->boss->textArea->textCursor();    

        if (0x41 <= key && key <= 0x5a) { // A letter was pressed
            if (cursor.position() == 0 && !cursor.atEnd()) {
                qDebug("Don't write it 1");
                return true;
            }
            if (!cursor.atEnd() && text.at(cursor.position() - 1) == ' ' && !this->insertAtMiddle) {
                qDebug("Don't write it 2");
                return true;
            }
        }

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

    // No empty words allowed
    if (cursor.position() == 0 || text.at(cursor.position() - 1) == ' ') {
        this->newWordStart = cursor.position();

        qDebug("No empty words allowed");
        return true;
    }

    // Cursor is at the end of document
    if (cursor.atEnd()) {
        this->boss->textArea->insertPlainText(this->delim);

        this->insertAtMiddle = false;

        qDebug("atEnd");
        return true;
    }

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
            int oldPos = cursor.position();
            cursor.movePosition(QTextCursor::StartOfWord);

            if (this->newWordStart == cursor.position()) {
                cursor.setPosition(oldPos);
                this->boss->textArea->insertPlainText(this->delim);

                cursor.movePosition(QTextCursor::End);
                this->boss->textArea->setTextCursor(cursor);

                this->insertAtMiddle = false;

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
}
