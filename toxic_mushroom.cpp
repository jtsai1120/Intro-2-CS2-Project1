#include "toxic_mushroom.h"
#include "mainwindow.h"
#include <QCoreApplication>
#include <QRandomGenerator>
#include <QDebug>

Toxic_mushroom::Toxic_mushroom(){
    //隨機取數決定開場向右還是左
    QRandomGenerator::securelySeeded();
    int randomNumber = QRandomGenerator::global()->bounded(0, 1);
    if (randomNumber) facing_right = false;
    else facing_right = false;//好像全部往左比較多樣

    toxic_mushroom_pic_1.load(":/Dataset/image/toxic mushroom1.png");
    toxic_mushroom_pic_2.load(":/Dataset/image/toxic mushroom2.png");
    toxic_mushroom_pic_3.load(":/Dataset/image/toxic mushroom3.png");
    toxic_mushroom_item = new QGraphicsPixmapItem(toxic_mushroom_pic_1);
    pic = "toxic_mushroom_pic_1";
    dx = 0;
    dy = 0;
}

void Toxic_mushroom::set_xy(int new_x, int new_y) {
    x = new_x;
    y = new_y;
    toxic_mushroom_item->setPos(x, y);
}

void Toxic_mushroom::move() {
    //檢查是否撞擊左右，若有則旋轉
    if(is_hit_right_side()){
        facing_right = false;
    }
    else if(is_hit_right_side()){
        facing_right = true;
    }


    //檢查是否撞擊左右，若有則旋轉
    if(is_hit_right_side()){
        facing_right = true;
    }
    else if(is_hit_left_side()){
        facing_right = false;
    }

    x += dx;
    dx = 0;

    y += dy;
    if (!dead && !is_grounded() && y < 1000) dy += ay;//死亡時飛出地圖
    else if(!dead){//若不是在掉落則移動
        dy = 0;
        if(facing_right){
            x += walk_speed;
            walk_distance += walk_speed;
        }
        else
            x -= walk_speed;
        walk_distance += walk_speed;
    }

    //更改移動造型
    if(walk_distance > 30){
        walk_distance = 0;
        if(pic == "toxic_mushroom_pic_1"){
            toxic_mushroom_item->setPixmap(toxic_mushroom_pic_2);
             pic = "toxic_mushroom_pic_2";
        }
        else{
            toxic_mushroom_item->setPixmap(toxic_mushroom_pic_1);
            pic = "toxic_mushroom_pic_1";
       }

    }

    if(dead){//死亡
        toxic_mushroom_item->setPixmap(toxic_mushroom_pic_3);
        dy += vy0;
    }

    set_xy(x, y);
}

bool Toxic_mushroom::is_grounded() {
    QList<QGraphicsItem *> items = cur_scene->items();
    bool _is_grounded = 0;

    for (QGraphicsItem *item : items) {
        QGraphicsPixmapItem *PixmapItem = qgraphicsitem_cast<QGraphicsPixmapItem*>(item);
        if (item->contains(item->mapFromScene(x + 10, y + 50))) {
            if(check_whether_ground_brick(PixmapItem)) {
                //qDebug() << "left foot is grounded";
                _is_grounded = 1;
            }
        }
        if (item->contains(item->mapFromScene(x + 50, (y + 50)))) {
            if(check_whether_ground_brick(PixmapItem)) {
                //qDebug() << "right foot is grounded";
                _is_grounded = 1;
            }
        }
    }
    return _is_grounded;

}

bool Toxic_mushroom::check_whether_ground_brick(QGraphicsPixmapItem *PixmapItem) {
    bool is_ground_brick = 0;
    // check whether floor brick(s)
    for (Floor_brick *i : floor_bricks)
        if (i->floor_brick_item == PixmapItem)
            is_ground_brick = 1;

    // check whether stone brick
    for (Stone_brick *i : stone_bricks)
        if (i->stone_brick_item == PixmapItem)
            is_ground_brick = 1;

    // check whether broken brick
    for (Broken_brick *i : broken_bricks)
        if (i->broken_brick_item == PixmapItem)
            is_ground_brick = 1;

    // check whether normal brick
    for (Normal_brick *i : normal_bricks)
        if (i->normal_brick_item == PixmapItem)
            is_ground_brick = 1;

    // check whether box brick
    for (Box_brick *i : box_bricks)
        if (i->box_brick_item == PixmapItem)
            is_ground_brick = 1;

    // check whether water pipe
    for (Water_pipe *i : water_pipes)
        if (i->water_pipe_item == PixmapItem)
            is_ground_brick = 1;

    // check whether invisible brick
    for (Invisible_brick *i : invisible_bricks)
        if (i->invisible_brick_item == PixmapItem)
            is_ground_brick = 1;

    return is_ground_brick;
}


bool Toxic_mushroom::is_hit_left_side() {
    QList<QGraphicsItem *> items = cur_scene->items();
    bool _is_hit_left_side = 0;
    QRectF rect1 = toxic_mushroom_item->sceneBoundingRect();
    for (QGraphicsItem *item : items) {
        QGraphicsPixmapItem *PixmapItem = qgraphicsitem_cast<QGraphicsPixmapItem*>(item);
        if (check_whether_ground_brick(PixmapItem)) {
            QRectF rect2 = item->sceneBoundingRect();
            if (rect1.right()>rect2.left()&&rect1.left()<rect2.left())
                if (rect1.bottom() - 10 > rect2.top() && rect1.top() < rect2.bottom())
                    _is_hit_left_side = 1;
        }
    }
    return _is_hit_left_side;
}

bool Toxic_mushroom::is_hit_right_side() {
    QList<QGraphicsItem *> items = cur_scene->items();
    bool _is_hit_right_side = 0;
    QRectF rect1 = toxic_mushroom_item->sceneBoundingRect();
    for (QGraphicsItem *item : items) {
        QGraphicsPixmapItem *PixmapItem = qgraphicsitem_cast<QGraphicsPixmapItem*>(item);
        if (check_whether_ground_brick(PixmapItem)) {
            QRectF rect2 = item->sceneBoundingRect();
            if (rect1.left()<rect2.right()&&rect1.right()>rect2.right())
                if (rect1.bottom() - 10 > rect2.top() && rect1.top() < rect2.bottom())
                    _is_hit_right_side = 1;
        }
    }
    return _is_hit_right_side;
}
