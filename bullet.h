#ifndef BULLET_H
#define BULLET_H

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
#include "toxic_mushroom.h"

class Bullet
{
public:
    Bullet();
    QGraphicsPixmapItem *bullet_item;

    void set_xy(int new_x, int new_y);
    void move(int dx);
    bool is_grounded();
    bool check_whether_ground_brick(QGraphicsPixmapItem *PixmapItem);
    bool is_hit_left_side(); // 撞到方塊兩左側
    bool is_hit_right_side(); // 撞到方塊兩右側
    void shoot(float m , int x0, int y0, int tx);
    void fly();
    void reset();
    bool already_shot = false;

    int posx,posy;
    float direction;
    float m1;
    float x2,y2;

    QGraphicsScene *cur_scene;
    std::vector<Floor_brick*> floor_bricks;
    std::vector<Stone_brick*> stone_bricks;
    std::vector<Normal_brick*> normal_bricks;
    std::vector<Box_brick*> box_bricks;
    std::vector<Broken_brick*> broken_bricks;
    std::vector<Water_pipe*> water_pipes;
    std::vector<Invisible_brick*> invisible_bricks;
    std::vector<Toxic_mushroom*> toxic_mushrooms;



private:
    QPixmap bullet_pic;
    int x, y;


};

#endif // BULLET_H

