#include "mario.h"
#include "mainwindow.h"
#include <QString>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QObject>
#include <QCoreApplication>

Mario::Mario() {
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
}

void Mario::move() {
    if (cur_direction == 'R') {
        if (is_grounded()) {
            if (is_moving) {
                if (cur_pixmap != "run1_R")
                    cur_pixmap = "run1_R";
                else
                    cur_pixmap = "run2_R";
            }
            else {
                cur_pixmap = "stand_R";
            }
        } else {
            cur_pixmap = "jump_R";
        }
    } else {
        if (is_grounded()) {
            if (is_moving) {
               if (cur_pixmap != "run1_L")
                    cur_pixmap = "run1_L";
                else
                    cur_pixmap = "run2_L";
            }
            else
                cur_pixmap = "stand_L";
        } else {
            cur_pixmap = "jump_L";
        }
    }
    change_direction_picture(cur_pixmap);
    x += dx;
    dx = 0;
    y += dy;
    if (is_crack_head()) dy = 1;
    else if (!is_grounded()) dy += ay;
    else dy = 0;

    mario->setPos(x, y);

}

void Mario::change_direction_picture(QString s) {
    if (s == "stand_R")
        mario->setPixmap(mario_stand_R);
    else if (s == "stand_L")
        mario->setPixmap(mario_stand_L);
    else if (s == "run1_L")
        mario->setPixmap(mario_run1_L);
    else if (s == "run2_L")
        mario->setPixmap(mario_run1_L);
    else if (s == "run1_R")
        mario->setPixmap(mario_run1_L);
    else if (s == "run2_R")
        mario->setPixmap(mario_run1_L);
    else if (s == "die")
        mario->setPixmap(mario_die);
    else if (s == "jump_L")
        mario->setPixmap(mario_jump_L);
    else if (s == "jump_R")
        mario->setPixmap(mario_jump_R);
    else qDebug() << "Mario Pixmap Error";
}

bool Mario::is_grounded() {
    QList<QGraphicsItem *> items = cur_scene->items();
    bool _is_grounded = 0;
    for (QGraphicsItem *item : items) {
        if (item->contains(item->mapFromScene(x, y + ((cur_size=="small")? small_mario_height : big_mario_height)))) {
            QGraphicsPixmapItem *PixmapItem = qgraphicsitem_cast<QGraphicsPixmapItem*>(item);
            if(check_whether_ground_brick(PixmapItem)) {
                //qDebug() << "left foot is grounded";
                _is_grounded = 1;
            }
        }
        if (item->contains(item->mapFromScene(x + ((cur_size=="small")? small_mario_width : big_mario_width), (y + ((cur_size=="small")? small_mario_height : big_mario_height))))) {
            QGraphicsPixmapItem *PixmapItem = qgraphicsitem_cast<QGraphicsPixmapItem*>(item);
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

    // check whether normal brick

    // check whether box brick

    // check whether water pipe

    return is_ground_brick;
}

void Mario::jump() {
    if (is_grounded()) { // 防止二次跳
        dy = vy0;
    }
}

bool Mario::is_crack_head() {
    QList<QGraphicsItem *> items = cur_scene->items();
    bool _is_crack_head = 0;
    for (QGraphicsItem *item : items) {
        if (item->contains(item->mapFromScene(x, y))) {
            QGraphicsPixmapItem *PixmapItem = qgraphicsitem_cast<QGraphicsPixmapItem*>(item);
            if(check_whether_ground_brick(PixmapItem)) {
                _is_crack_head = 1;
            }
        }
        if (item->contains(item->mapFromScene(x + ((cur_size=="small")? small_mario_width : big_mario_width), y))) {
            QGraphicsPixmapItem *PixmapItem = qgraphicsitem_cast<QGraphicsPixmapItem*>(item);
            if(check_whether_ground_brick(PixmapItem)) {
                _is_crack_head = 1;
            }
        }
    }
    return _is_crack_head;
}

bool Mario::is_hit_side() {
    QList<QGraphicsItem *> items = cur_scene->items();
    bool _is_hit_side = 0;
    for (QGraphicsItem *item : items) {
        if (item->contains(item->mapFromScene(x, y + ((cur_size=="small")? small_mario_height : big_mario_height)/2))) {
            QGraphicsPixmapItem *PixmapItem = qgraphicsitem_cast<QGraphicsPixmapItem*>(item);
            if(check_whether_ground_brick(PixmapItem)) {
                _is_hit_side = 1;
            }
        }
        if (item->contains(item->mapFromScene(x + ((cur_size=="small")? small_mario_width : big_mario_width), y + ((cur_size=="small")? small_mario_height : big_mario_height)/2))) {
            QGraphicsPixmapItem *PixmapItem = qgraphicsitem_cast<QGraphicsPixmapItem*>(item);
            if(check_whether_ground_brick(PixmapItem)) {
                _is_hit_side = 1;
            }
        }
    }
    return _is_hit_side;
}


