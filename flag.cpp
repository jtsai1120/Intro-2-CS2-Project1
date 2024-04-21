#include "flag.h"
#include <QDebug>
#include "mainwindow.h"

Flag::Flag() {
    flag_pic.load(":/Dataset/image/item/flag.png");
    flag_item = new QGraphicsPixmapItem(flag_pic);
    x = init_x;
    y = init_y;
    flag_item->setPos(x, y);
    is_touched_mario = 0;
}

void Flag::move(int dx, int dy) {
    x += dx;
    y += dy;
    flag_item->setPos(x, y);
}

void Flag::fall() {
    QObject::connect(&fall_timer, SIGNAL(timeout()), this, SLOT(fall_until_touch_mario()));
    fall_timer.start(5);
}

void Flag::fall_until_touch_mario() {
    move(0, 2);

    if (flag_item->collidesWithItem(mario->mario)) {
        fall_timer.stop();
        qDebug() << "flag touch mario !";
        is_touched_mario = 1;
    }
}

void Flag::reset(){
    x = init_x;
    y = init_y;
    flag_item->setPos(x, y);
    is_touched_mario = 0;
}
