#ifndef SUPER_MUSHROOM_H
#define SUPER_MUSHROOM_H

#include <vector>
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

class Super_mushroom{
public:
    Super_mushroom();
    QGraphicsPixmapItem *super_mushroom_item;

    void set_xy(int new_x, int new_y);
    void show();
    void move();


    static const int super_mushroom_height = 50;
    static const int super_mushroom_width = 50;

    QGraphicsScene *cur_scene;
    std::vector<Floor_brick*> floor_bricks;
    std::vector<Stone_brick*> stone_bricks;
    std::vector<Normal_brick*> normal_bricks;
    std::vector<Box_brick*> box_bricks;
    std::vector<Broken_brick*> broken_bricks;
    std::vector<Water_pipe*> water_pipes;
    std::vector<Invisible_brick*> invisible_bricks;

    bool is_grounded();
    bool check_whether_ground_brick(QGraphicsPixmapItem *PixmapItem);
    bool is_hit_left_side(); // 撞到方塊兩左側
    bool is_hit_right_side(); // 撞到方塊兩右側

    int dx;
    double dy;

    int x;//為了辨識距離，距離過遠則癱瘓
    double y;//為了讓別人好判斷高度，放在外面

    bool still = true;


private:
    QPixmap super_mushroom_pic;

    const double vy0 = 0.06;
    const double ay = 0.18;

    const int walk_speed = 1;
    bool facing_right = true;



};


#endif // SUPER_MUSHROOM_H
