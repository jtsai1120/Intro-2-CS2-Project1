#include "mario.h"
#include "mainwindow.h"
#include <QString>
#include <QDebug>
#include <QTimer>
#include <QObject>
#include <QCoreApplication>
#include <QRectF>
#include <QLabel>

Mario::Mario(QWidget *parent) : QObject(parent) {
    mario_stand_R.load(":/Dataset/image/Mario_small/s_mario_stand_R.png");
    mario_stand_L.load(":/Dataset/image/Mario_small/s_mario_stand_L.png");
    mario_jump_R.load(":/Dataset/image/Mario_small/s_mario_jump1_R.png");
    mario_jump_L.load(":/Dataset/image/Mario_small/s_mario_jump1_L.png");
    mario_die.load(":/Dataset/image/Mario_small/s_mario_die.png");
    mario_run1_L.load(":/Dataset/image/Mario_small/s_mario_run1_L.png");
    mario_run1_R.load(":/Dataset/image/Mario_small/s_mario_run1_R.png");
    mario_run2_L.load(":/Dataset/image/Mario_small/s_mario_run2_L.png");
    mario_run2_R.load(":/Dataset/image/Mario_small/s_mario_run2_R.png");
    mario = new QGraphicsPixmapItem(mario_stand_R);
    x = init_x;
    y = init_y;
    dx = 0;
    dy = 0;
    mario->setPos(x, y);
    cur_direction = 'R';
    cur_size = "small";
    cur_pixmap = "stand_R";
    is_moving = 0;
    //qDebug() << "width=" << mario_stand_R.width();
    //qDebug() << "height=" << mario_stand_R.height();
    is_passed_jump_cd = 1;
    immune_status = 0;
    movable = 1;
}

void Mario::change(){
    if (movable) {
        if (cur_direction == 'R') {
            if (is_grounded()) {
                if (is_moving) {
                    if (cur_pixmap != "run1_R")
                        cur_pixmap = "run1_R";
                    else
                        cur_pixmap = "run2_R";
                }
            }
       }
       else{
            if (is_grounded()) {
                if (is_moving) {
                   if (cur_pixmap != "run1_L")
                        cur_pixmap = "run1_L";
                    else
                        cur_pixmap = "run2_L";
                }
            }
        }
        //qDebug()<<"change";
        change_direction_picture(cur_pixmap);
    }
}

void Mario::move() {
    if (movable) {
        if (cur_direction == 'R') {
            if (is_grounded()) {
                if (!is_moving)
                    cur_pixmap = "stand_R";
                else if (!is_passed_jump_cd)
                    cur_pixmap = "stand_R";
            }
            else {
                cur_pixmap = "jump_R";
            }
        } else {
            if (is_grounded()) {
                if (!is_moving)
                    cur_pixmap = "stand_L";
                else if (!is_passed_jump_cd)
                    cur_pixmap = "stand_L";
            }
            else {
                cur_pixmap = "jump_L";
            }
        }
        change_direction_picture(cur_pixmap);

        //移動時活化毒蘑菇
        for (Toxic_mushroom* i : toxic_mushrooms)
            if(abs(i -> x - x) > 700) i -> still = true;
            else i -> still = false;

        /*
        if (is_hit_left_side())
            qDebug() << "hit left side!";
        if (is_hit_right_side())
            qDebug() << "hit right side!";
        if (is_crack_head())
            qDebug() << "is crack head";
        */
        x += dx;
        dx = 0;

        y += dy;
        if (is_crack_head()) dy = 1;
        else if (!is_grounded()) dy += ay;
        else dy = 0;

        mario->setPos(x, y);
    }
}

void Mario::change_direction_picture(QString s) {
    if (s == "stand_R")
        mario->setPixmap(mario_stand_R);
    else if (s == "stand_L")
        mario->setPixmap(mario_stand_L);
    else if (s == "run1_L")
        mario->setPixmap(mario_run1_L);
    else if (s == "run2_L")
        mario->setPixmap(mario_run2_L);
    else if (s == "run1_R")
        mario->setPixmap(mario_run1_R);
    else if (s == "run2_R")
        mario->setPixmap(mario_run2_R);
    else if (s == "die")
        mario->setPixmap(mario_die);
    else if (s == "jump_L")
        mario->setPixmap(mario_jump_L);
    else if (s == "jump_R")
        mario->setPixmap(mario_jump_R);
    else qDebug() << "Mario Pixmap Error";
}

void Mario::jump() {
    if (is_grounded() && is_passed_jump_cd) { // 防止二次跳
        dy = vy0;
    }
}

void Mario::jump_cd_trigger() {
    jump_cd.stop();
    //qDebug() << "jump cd passed!";
    is_passed_jump_cd = 1;
}

void Mario::immune_time() {
    immune.stop();
    immune_status = 0;
}

void Mario::is_taller(int i){
    if (y < toxic_mushrooms[i]->y - 42 && dy >= 0){ //扣掉毒菇本身高度&&確保馬力歐不是在上升
        toxic_mushrooms[i]->dead = 1;
    }
    else if(!immune_status && !toxic_mushrooms[i]->dead){ //非免疫狀態且毒菇沒死
        hp->sub_hp(1); //扣血
        immune_status = 1;
        QObject::connect(&immune, SIGNAL(timeout()), this, SLOT(immune_time()));
        immune.start(2000);
    }
}


bool Mario::is_grounded() {
    QList<QGraphicsItem *> items = cur_scene->items();
    bool _is_grounded = 0;
    for (QGraphicsItem *item : items) {
        QGraphicsPixmapItem *PixmapItem = qgraphicsitem_cast<QGraphicsPixmapItem*>(item);
        if (item->contains(item->mapFromScene(x + 10, y + ((cur_size=="small")? small_mario_height : big_mario_height)))) {  
            if(check_whether_ground_brick(PixmapItem)) {
                //qDebug() << "left foot is grounded";
                _is_grounded = 1;
            }
        }
        if (item->contains(item->mapFromScene(x + ((cur_size=="small")? small_mario_width : big_mario_width), (y + ((cur_size=="small")? small_mario_height : big_mario_height))))) {
            if(check_whether_ground_brick(PixmapItem)) {
                //qDebug() << "right foot is grounded";
                _is_grounded = 1;
            }
        }
    }
    return _is_grounded;
}

bool Mario::check_whether_ground_brick(QGraphicsPixmapItem *PixmapItem) {
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


bool Mario::is_crack_head() {
    QList<QGraphicsItem *> items = cur_scene->items();
    bool _is_crack_head = 0;
    bool _is_crack_noraml_brick = 0;
    bool _is_crack_broken_brick = 0;
    bool _is_crack_box_brick = 0;

    Normal_brick *hit_normal_brick;
    Broken_brick *hit_broken_brick;
    Box_brick *hit_box_brick;

    for (QGraphicsItem *item : items) {
        QGraphicsPixmapItem *PixmapItem = qgraphicsitem_cast<QGraphicsPixmapItem*>(item);
        if (item->contains(item->mapFromScene(x + 10, y))) {
            if(check_whether_ground_brick(PixmapItem)) {
                _is_crack_head = 1;
                for (Normal_brick *i : normal_bricks)
                    if (i->normal_brick_item == PixmapItem) {
                        _is_crack_noraml_brick = 1;
                        hit_normal_brick = i;
                    }
                for (Broken_brick *i : broken_bricks)
                    if (i->broken_brick_item == PixmapItem) {
                        _is_crack_broken_brick = 1;
                        hit_broken_brick = i;
                    }
                for (Box_brick *i : box_bricks)
                    if (i->box_brick_item == PixmapItem) {
                        _is_crack_box_brick = 1;
                        hit_box_brick = i;
                    }

            }
        }
        if (item->contains(item->mapFromScene(x + ((cur_size=="small")? small_mario_width : big_mario_width), y))) {
            if(check_whether_ground_brick(PixmapItem)) {
                _is_crack_head = 1;
                for (Normal_brick *i : normal_bricks)
                    if (i->normal_brick_item == PixmapItem) {
                        _is_crack_noraml_brick = 1;
                        hit_normal_brick = i;
                    }
                for (Broken_brick *i : broken_bricks)
                    if (i->broken_brick_item == PixmapItem) {
                        _is_crack_broken_brick = 1;
                        hit_broken_brick = i;
                     }
                for (Box_brick *i : box_bricks)
                    if (i->box_brick_item == PixmapItem) {
                        _is_crack_box_brick = 1;
                        hit_box_brick = i;
                    }
            }
        }
        if (_is_crack_head && _is_crack_noraml_brick) {
            hit_normal_brick->crack();
            is_passed_jump_cd = 0;
            QObject::connect(&jump_cd, SIGNAL(timeout()), this, SLOT(jump_cd_trigger()));
            jump_cd.start(520);
        }
        if (_is_crack_head && _is_crack_broken_brick) {
            hit_broken_brick->crack();
            is_passed_jump_cd = 0;
            QObject::connect(&jump_cd, SIGNAL(timeout()), this, SLOT(jump_cd_trigger()));
            jump_cd.start(520);
        }
        if (_is_crack_head && _is_crack_box_brick) {
            hit_box_brick->crack();
            is_passed_jump_cd = 0;
            QObject::connect(&jump_cd, SIGNAL(timeout()), this, SLOT(jump_cd_trigger()));
            jump_cd.start(520);
        }


    }
    return _is_crack_head;
}

bool Mario::is_hit_left_side() {
    QList<QGraphicsItem *> items = cur_scene->items();
    bool _is_hit_left_side = 0;
    QRectF rect1 = mario->sceneBoundingRect();
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

bool Mario::is_hit_right_side() {
    QList<QGraphicsItem *> items = cur_scene->items();
    bool _is_hit_right_side = 0;
    QRectF rect1 = mario->sceneBoundingRect();
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

void Mario::reset(){
    x = 700;
    y = 100;
    mario->setPos(x,y);
}

