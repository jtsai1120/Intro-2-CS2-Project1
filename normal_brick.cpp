#include "normal_brick.h"

Normal_brick::Normal_brick() {
    normal_brick_pic.load(":/Dataset/image/brick/normal brick.png");
    normal_brick_item = new QGraphicsPixmapItem(normal_brick_pic);
}

void Normal_brick::set_xy(int new_x, int new_y) {
    x = new_x;
    y = new_y;
    normal_brick_item->setPos(x, y);
}

void Normal_brick::move(int dx) {
    x += dx;
    set_xy(x, y);
}

void Normal_brick::crack(double dy) {
    y += dy;
    set_xy(x, y);
}
