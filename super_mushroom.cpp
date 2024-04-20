#include "super_mushroom.h"
#include <QDebug>

Super_mushroom::Super_mushroom() {
    super_mushroom_pic.load(":/Dataset/image/item/super mushroom.png");
    super_mushroom_item = new QGraphicsPixmapItem(super_mushroom_pic);
    opened = false;
}

void Super_mushroom::set_xy(int new_x, int new_y) {
    x = new_x;
    y = new_y;
    super_mushroom_item->setPos(x, y);
}

void Super_mushroom::move(int dx) {
    x += dx;
    set_xy(x, y);
}

