#include "invisible_brick.h"

Invisible_brick::Invisible_brick(){
    //invisible_brick_pic.load(":/Dataset/image/brick/invisible brick.png");
    invisible_brick_pic.load(":/Dataset/image/brick/stone brick.png");

    invisible_brick_item = new QGraphicsPixmapItem(invisible_brick_pic);
}

void Invisible_brick::set_xy(int new_x, int new_y) {
    x = new_x;
    y = new_y;
    invisible_brick_item->setPos(x, y);
}

void Invisible_brick::move(int dx) {
    x += dx;
    set_xy(x, y);
}
