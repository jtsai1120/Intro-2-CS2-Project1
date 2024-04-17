#include "mario.h"
#include "mainwindow.h"
#include <QString>
#include <QDebug>
#include <QTimer>
#include <QThread>

Mario::Mario() {
    mario_stand_R.load(":/Dataset/image/Mario_small/s_mario_stand_R.png");
    mario_stand_L.load(":/Dataset/image/Mario_small/s_mario_stand_L.png");
    mario_jump_R.load(":/Dataset/image/Mario_small/s_mario_jump1_R.png");
    mario_jump_L.load(":/Dataset/image/Mario_small/s_mario_jump1_L.png");
    mario = new QGraphicsPixmapItem(mario_stand_R);
    x = init_x;
    y = init_y;
    mario->setPos(x, y);
    cur_direction = 'R';
    cur_size = "small";
    //qDebug() << "width=" << mario_stand_R.width();
    //qDebug() << "height=" << mario_stand_R.height();
}

void Mario::move(int dx, int dy) {
    cur_direction = (dx>=0)? 'R':'L';
    change_direction_picture((dx>=0)? "stand_R":"stand_L");
    x += dx;
    y += dy;
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
                qDebug() << "left foot is grounded";
                _is_grounded = 1;
            }
        }
        if (item->contains(item->mapFromScene(x + ((cur_size=="small")? small_mario_width : big_mario_width), (y + ((cur_size=="small")? small_mario_height : big_mario_height))))) {
            QGraphicsPixmapItem *PixmapItem = qgraphicsitem_cast<QGraphicsPixmapItem*>(item);
            if(check_whether_ground_brick(PixmapItem)) {
                qDebug() << "right foot is grounded";
                _is_grounded = 1;
            }
        }
    }
    if (_is_grounded) change_direction_picture((cur_direction=='R')? "stand_R" : "stand_L");
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
    /*
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
         timer.start(1000);
    });
    */
    //if (is_grounded()) {
        change_direction_picture((cur_direction=='R')? "jump_R" : "jump_L");
        y -= 50;
        mario->setPos(x,y);
        qDebug() << ((is_grounded())? "grounded" : "not grounded");
        /*
        vy = vy0;
        while(!is_grounded()) {
            //if (coliision) {}
            y += vy;
            mario->setPos(x, y);
            vy += ay;
            QThread::sleep(1000);

        }
    }*/
}

