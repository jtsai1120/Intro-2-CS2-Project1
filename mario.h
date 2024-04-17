#ifndef MARIO_H
#define MARIO_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QString>
#include "floor_brick.h"
#include "stone_brick.h"

class Mario {
    public:
        Mario();
        void move();
        QGraphicsPixmapItem *mario;
        void set_x(int new_x) { x = new_x; }
        void change_direction_picture(QString s);
        void jump();

        QGraphicsScene *cur_scene;
        QGraphicsPixmapItem *game_bg_item;
        std::vector<Floor_brick*> floor_bricks;
        std::vector<Stone_brick*> stone_bricks;

        static const int small_mario_height = 52;
        static const int big_mario_height = 80;
        static const int small_mario_width = 36; // original = 50
        static const int big_mario_width = 40; // original = 56
        static const int init_x = 450, init_y = 620 - Floor_brick::floor_brick_height - small_mario_height;

        int dx;
        double dy;
        char cur_direction;
        bool is_moving;

    private:
        QPixmap mario_stand_R, mario_stand_L;
        QPixmap mario_run1_L, mario_run2_L;
        QPixmap mario_run1_R, mario_run2_R;
        QPixmap mario_die;
        QPixmap mario_jump_L, mario_jump_R;

        int x; double y;
        bool is_grounded();
        bool check_whether_ground_brick(QGraphicsPixmapItem *PixmapItem);
        bool is_crack_head(); // 撞到頭

        const double vy0 = -6;
        const double ay = 0.18;
        // since one jump = 100 pixels = v^2/(2*a)
        // let a = -2, v(initial) = 20
        QString cur_size;
        QString cur_pixmap;



};

#endif // MARIO_H
