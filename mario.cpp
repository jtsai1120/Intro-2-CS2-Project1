#include "mario.h"
#include "mainwindow.h"
#include <QString>
#include <QDebug>

Mario::Mario() {
    mario_stand_R.load(":/Dataset/image/Mario_small/s_mario_stand_R.png");
    mario_stand_L.load(":/Dataset/image/Mario_small/s_mario_stand_L.png");
    mario = new QGraphicsPixmapItem(mario_stand_R);
    //qDebug() << Mario_pic.height();
    x = init_x;
    y = init_y;
    mario->setPos(x, y);
    is_jumping = false;
}

void Mario::move(int dx, int dy) {
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
    else qDebug() << "Mario Pixmap Error";
}
