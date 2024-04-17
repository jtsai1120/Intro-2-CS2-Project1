#include "stone_brick.h"

Stone_brick::Stone_brick() {
    stone_brick_pic.load(":/Dataset/image/brick/stone brick.png");
    stone_brick_item = new QGraphicsPixmapItem(stone_brick_pic);
}

void Stone_brick::set_xy(int new_x, int new_y) {
    x = new_x;
    y = new_y;
    stone_brick_item->setPos(x, y);
}

void Stone_brick::move(int dx) {
    x += dx;
    set_xy(x, y);
}


