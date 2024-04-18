#include "normal_brick.h"
#include <QDebug>

Normal_brick::Normal_brick() {
    normal_brick_pic.load(":/Dataset/image/brick/normal brick.png");
    normal_brick_item = new QGraphicsPixmapItem(normal_brick_pic);
    dx = 0;
    dy = 0;

}

void Normal_brick::set_xy(int new_x, int new_y) {
    x = new_x;
    y = new_y;
    normal_brick_item->setPos(x, y);
}

void Normal_brick::move() {

    x += dx;
    dx = 0;

    y += dy;
    if (y > init_y) {
        y = init_y;
        dy = 0;
    } else if (y < init_y){
        dy += ay;
    } else {
        dy = 0;
    }

    set_xy(x, y);
}

void Normal_brick::crack() {
    if (y == init_y) // 確保不會在下落過程中再被頂起來
        dy = vy0;
}
