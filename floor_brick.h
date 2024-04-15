#ifndef FLOOR_BRICK_H
#define FLOOR_BRICK_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

class Floor_brick {
    public:
        Floor_brick();
        std::vector<QGraphicsPixmapItem*> floor_brick_items;
    private:
        QPixmap floor_brick;
};

#endif // FLOOR_BRICK_H
