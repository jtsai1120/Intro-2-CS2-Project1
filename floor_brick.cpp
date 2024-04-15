#include "floor_brick.h"

Floor_brick::Floor_brick() {
    floor_brick.load(":/Dataset/image/brick/floor brick.png");
    const int floor_num = 1400 / floor_brick.width();
    for (int i = 0 ; i < floor_num ; i++) {
        floor_brick_items.push_back(new QGraphicsPixmapItem(floor_brick));
        floor_brick_items[i]->setPos(i * floor_brick.width(), 620 - floor_brick.height());
    }
}
