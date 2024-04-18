#include "broken_brick.h"

Broken_brick::Broken_brick() {
    broken_brick_pic.load(":/Dataset/image/brick/broken brick.png");
    broken_brick_item = new QGraphicsPixmapItem(broken_brick_pic);
}

void Broken_brick::set_xy(int new_x, int new_y) {
    x = new_x;
    y = new_y;
    broken_brick_item->setPos(x, y);
}

void Broken_brick::move(int dx) {
    x += dx;
    set_xy(x, y);
}

void Broken_brick::crack() {
}
