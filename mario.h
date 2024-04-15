#ifndef MARIO_H
#define MARIO_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class Mario {
    public:
        Mario();
        void move(int dx, int dy);
        QGraphicsPixmapItem *mario;
        void set_x(int new_x) { x = new_x; }

        static const int floor_brick_height = 100;
        static const int small_mario_height = 52;
        static const int init_x = 450, init_y = 620 - floor_brick_height - small_mario_height;
    private:
        QPixmap Mario_pic;
        int x, y;
        bool is_jumping;


};

#endif // MARIO_H
