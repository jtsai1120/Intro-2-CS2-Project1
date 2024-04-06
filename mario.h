#ifndef MARIO_H
#define MARIO_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class Mario {
    public:
        Mario();

        void game_init();
        void set_cur_scene(QGraphicsScene *s) { cur_scene = s; }
        void set_floor_brick_height(int h) { floor_brick_height = h; }

        void move(QString s);

    private:
        QPixmap Mario_pic;
        QGraphicsItem *mario;

        int x, y;
        int dx, dy;
        bool is_jumping;

        QGraphicsScene *cur_scene;

        int floor_brick_height;
};

#endif // MARIO_H
