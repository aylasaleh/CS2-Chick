#include "FireBoy.h"
#include <QBrush>
#include <QTimer>

FireBoy::FireBoy(QGraphicsItem* parent) : Players(parent) {
    setRect(0, 0, 50, 50); //edit later
    setBrush(Qt::red);
}

void FireBoy::keyPressEvent(QKeyEvent* event) {
    if ((event->key() == Qt::Key_Up)&&(event->key() == Qt::Key_Right)) {
        if (!isJumping) {
            isJumping = true;
            originalY = y();
            jump(0);
        }
    }else if ((event->key() == Qt::Key_Up)&&(event->key() == Qt::Key_Left)) {
        if (!isJumping) {
            isJumping = true;
            originalY = y();
            jump(5);
        }
    }else if (event->key() == Qt::Key_Up) {
        if (!isJumping) {
            isJumping = true;
            originalY = y();
            jump(10);
        }
    } else if (event->key() == Qt::Key_Left) {
        moveBy(-10, 0);
    } else if (event->key() == Qt::Key_Right) {
        moveBy(10, 0);
    }
}

void FireBoy::jump(int jumpStep) {
    if (jumpStep < 5) {    //if jumping right
        moveBy(10, -10);
        ++jumpStep;
        QTimer::singleShot(20, this, [this, jumpStep]() { jump(jumpStep); });
    }else if (jumpStep < 10) { //if jumping left
        moveBy(-10, -10);
        ++jumpStep;
        QTimer::singleShot(20, this, [this, jumpStep]() { jump(jumpStep); });
    }else if (jumpStep < 15) { //if jumping only
        moveBy(0, -10);
        ++jumpStep;
        QTimer::singleShot(20, this, [this, jumpStep]() { jump(jumpStep); });
    }else {                         //why do we need this else?
        isJumping = false;
        while (y() != originalY)
        {
            QTimer::singleShot(20, this, [this]() { moveBy(0, 10); });
        }
        setPos(x(), originalY);
    }
}
