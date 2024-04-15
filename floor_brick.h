#ifndef FLOOR_BRICK_H
#define FLOOR_BRICK_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

class Floor_brick {
    public:
        Floor_brick();
        //std::vector<QGraphicsPixmapItem*> floor_brick_items;
        QGraphicsPixmapItem *floor_brick_item;

        static const int floor_brick_width = 50;
        static const int floor_brick_height = 100;
        const int init_y = 620 - floor_brick_height;

        void set_x(int new_x);
        void move(int dx);

    private:
        QPixmap floor_brick;
        int x;
};

#endif // FLOOR_BRICK_H
