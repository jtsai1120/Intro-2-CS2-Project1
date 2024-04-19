#include "box_brick.h"
#include <QDebug>

Box_brick::Box_brick() {
    box_brick_pic.load(":/Dataset/image/brick/box brick.png");
    stone_brick_pic.load(":/Dataset/image/brick/stone brick.png");
    box_brick_item = new QGraphicsPixmapItem(box_brick_pic);
    opened = false;
}

void Box_brick::set_xy(int new_x, int new_y) {
    x = new_x;
    y = new_y;
    box_brick_item->setPos(x, y);
}

void Box_brick::move(int dx) {
    x += dx;
    set_xy(x, y);
}

void Box_brick::crack() {
    if(!opened){
        box_brick_item->setPixmap(stone_brick_pic);
        qDebug() << "boom";
        //放上隨機觸發事件
        opened = true;
    }
}
