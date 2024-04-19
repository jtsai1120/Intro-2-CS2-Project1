#include "broken_brick.h"
#include "mario.h"

#include <QDebug>

Broken_brick::Broken_brick() {
    broken_brick_pic.load(":/Dataset/image/brick/broken brick.png");
    broken_brick_item = new QGraphicsPixmapItem(broken_brick_pic);
    dx = 0;
    dy = 0;
}

void Broken_brick::set_xy(int new_x, int new_y) {
    x = new_x;
    y = new_y;
    broken_brick_item->setPos(x, y);
}

void Broken_brick::move() {

    x += dx;
    dx = 0;

    y += dy;
    if (y > init_y) {
        y = 100000;
    }
    else if (y < init_y){
        dy += ay;
    }
    else {
        dy = 0;
    }

    set_xy(x, y);
}

void Broken_brick::crack() {
    if (y == init_y) // 確保不會在下落過程中再被頂起來
        dy = vy0;
}

