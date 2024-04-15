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

        void move(QString s);

    private:
        QPixmap Mario_pic;
        QGraphicsItem *mario;

        int x, y;
        int dx, dy;
        bool is_jumping;

        static const int floor_brick_height = 100;

        QGraphicsScene *cur_scene;
};

#endif // MARIO_H
