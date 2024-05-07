#include "floor_brick.h"
#include <QDebug>

Floor_brick::Floor_brick() {
    floor_brick.load(":/Dataset/image/brick/floor brick.png");
    floor_brick_item = new QGraphicsPixmapItem(floor_brick);
}

void Floor_brick::set_x(int new_x) {
    x = new_x;
    floor_brick_item->setPos(x, init_y);
}

void Floor_brick::move(int dx) {
    x += dx;
    set_x(x);
}
