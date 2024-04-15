#ifndef MARIO_H
#define MARIO_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QString>
#include "floor_brick.h"

class Mario {
    public:
        Mario();
        void move(int dx, int dy);
        QGraphicsPixmapItem *mario;
        void set_x(int new_x) { x = new_x; }
        void change_direction_picture(QString s);

        static const int small_mario_height = 52;
        static const int init_x = 450, init_y = 620 - Floor_brick::floor_brick_height - small_mario_height;
    private:
        QPixmap mario_stand_R, mario_stand_L;
        QPixmap mario_run1_L, mario_run2_L;
        QPixmap mario_run1_R, mario_run2_R;
        QPixmap mario_die;
        int x, y;
        bool is_jumping;

};

#endif // MARIO_H
