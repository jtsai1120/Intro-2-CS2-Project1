#ifndef TOXIC_MUSHROOM_H
#define TOXIC_MUSHROOM_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsScene>
#include <QObject>
#include <QRectF>
#include <QString>
#include <QTimer>
#include "stone_brick.h"
#include "normal_brick.h"
#include "floor_brick.h"
#include "box_brick.h"
#include "broken_brick.h"
#include "water_pipe.h"
#include "invisible_brick.h"


class Toxic_mushroom{
public:
    Toxic_mushroom();
    QGraphicsPixmapItem *toxic_mushroom_item;

    void set_xy(int new_x, int new_y);
    void move();
    void go_die();

    bool is_grounded();
    bool check_whether_ground_brick(QGraphicsPixmapItem *PixmapItem);
    bool is_hit_left_side(); // 撞到方塊兩左側
    bool is_hit_right_side(); // 撞到方塊兩右側

    QGraphicsScene *cur_scene;
    std::vector<Floor_brick*> floor_bricks;
    std::vector<Stone_brick*> stone_bricks;
    std::vector<Normal_brick*> normal_bricks;
    std::vector<Box_brick*> box_bricks;
    std::vector<Broken_brick*> broken_bricks;
    std::vector<Water_pipe*> water_pipes;
    std::vector<Invisible_brick*> invisible_bricks;

    static const int toxic_mushroom_height = 50;
    static const int toxic_mushroom_width = 50;

    int init_y;

    int dx;
    double dy;

    double y;//為了讓別人好判斷高度，放在外面

    bool dead = false;

private:
    QPixmap toxic_mushroom_pic_1;
    QPixmap toxic_mushroom_pic_2;
    QPixmap toxic_mushroom_pic_3;
    QString pic;

    int x;

    int walk_distance = 0;//換造型用
    const double vy0 = 0.06;
    const double ay = 0.18;

    const int walk_speed = 1;
    bool facing_right = true;
};

#endif // TOXIC_MUSHROOM_H
