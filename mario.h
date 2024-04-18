#ifndef MARIO_H
#define MARIO_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPixmap>
#include <QString>
#include <QTimer>
#include "stone_brick.h"
#include "normal_brick.h"
#include "floor_brick.h"
#include "box_brick.h"
#include "broken_brick.h"
#include "water_pipe.h"

class Mario : public QObject {
    Q_OBJECT
    public:
        Mario(QWidget *parent = nullptr);
        void move();
        QGraphicsPixmapItem *mario;
        void set_x(int new_x) { x = new_x; }
        int get_y() { return y; }
        void change_direction_picture(QString s);
        void jump();
        void change();

        QGraphicsScene *cur_scene;
        std::vector<Floor_brick*> floor_bricks;
        std::vector<Stone_brick*> stone_bricks;
        std::vector<Normal_brick*> normal_bricks;
        std::vector<Box_brick*> box_bricks;
        std::vector<Broken_brick*> broken_bricks;
        std::vector<Water_pipe*> water_pipes;


        static const int small_mario_height = 52;
        static const int big_mario_height = 80;
        static const int small_mario_width = 36; // original = 50
        static const int big_mario_width = 40; // original = 56
        static const int init_x = 450;
        static const int init_y = 620 - Floor_brick::floor_brick_height - small_mario_height;

        int dx;
        double dy;
        char cur_direction;
        bool is_moving;
        bool is_grounded();
        bool check_whether_ground_brick(QGraphicsPixmapItem *PixmapItem);
        bool is_crack_head(); // 撞到頭
        bool is_hit_left_side(); // 撞到方塊兩左側
        bool is_hit_right_side(); // 撞到方塊兩右側
        bool movable;

    private:
        QPixmap mario_stand_R, mario_stand_L;
        QPixmap mario_run1_L, mario_run2_L;
        QPixmap mario_run1_R, mario_run2_R;
        QPixmap mario_die;
        QPixmap mario_jump_L, mario_jump_R;

        int x; double y;
        const double vy0 = -6;
        const double ay = 0.18;
        // since one jump = 100 pixels = v^2/(2*a)
        // let a = 0.18, v(initial) = -6
        QString cur_size;
        QString cur_pixmap;

        QTimer jump_cd;
        bool is_passed_jump_cd;

    private slots:
        void jump_cd_trigger();

};

#endif // MARIO_H
