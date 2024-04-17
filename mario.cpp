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
    mario = new QGraphicsPixmapItem(mario_stand_R);
    x = init_x;
    y = init_y;
    dx = 0;
    dy = 0;
    mario->setPos(x, y);
    cur_direction = 'R';
    cur_size = "small";
    //qDebug() << "width=" << mario_stand_R.width();
    //qDebug() << "height=" << mario_stand_R.height();
}

void Mario::move() {
    if (cur_direction == 'R') {
        if (is_grounded())
            change_direction_picture("stand_R");
        else
            change_direction_picture("jump_R");
    } else {
        if (is_grounded())
            change_direction_picture("stand_L");
        else
            change_direction_picture("jump_L");
    }
    x += dx;
    dx = 0;
    y += dy;
    if (!is_grounded()) dy += ay;
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
    //if(items.empty()) qDebug() << "no item";
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
    for (QGraphicsPixmapItem *i : floor_brick_items)
        if (i == PixmapItem)
            is_ground_brick = 1;

    return is_ground_brick;
}

void Mario::jump() {
    if (is_grounded()) { // 防止二次跳
        dy = vy0;
    }
}



