#include "flag_pole.h"
#include <QDebug>

Flag_pole::Flag_pole() {
    flag_pole_pic.load(":/Dataset/image/item/flag-pole.png");
    flag_pole_item = new QGraphicsPixmapItem(flag_pole_pic);
    x = init_x;
    y = init_y;
    flag_pole_item->setPos(x, y);
    is_touched = 0;
}

void Flag_pole::move(int dx, int dy) {
    x += dx;
    y += dy;
    flag_pole_item->setPos(x, y);
}

void Flag_pole::reset(){
    x = init_x;
    y = init_y;
    flag_pole_item->setPos(x, y);
    is_touched = 0;
}
