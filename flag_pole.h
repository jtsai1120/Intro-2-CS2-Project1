#ifndef FLAG_POLE_H
#define FLAG_POLE_H

#include "QGraphicsPixmapItem"
#include "QPixmap"
#include "floor_brick.h"

class Flag_pole {
    public:
        Flag_pole();
        QGraphicsPixmapItem *flag_pole_item;
        void move(int dx, int dy);
        void reset();
        //x = 1400 * 5 - 200;
        static const int init_x = 1400 * 5 - 200;
        static const int init_y = 620 - Floor_brick::floor_brick_height - 500;

        bool is_touched;

    private:
        QPixmap flag_pole_pic;
        int x, y;
};

#endif // FLAG_POLE_H
