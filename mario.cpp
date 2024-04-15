#include "mario.h"
#include "mainwindow.h"
#include <QString>
#include <QDebug>

Mario::Mario() {
    Mario_pic.load(":/Dataset/image/Mario_small/s_mario_stand_R.png");
    mario = new QGraphicsPixmapItem(Mario_pic);
    //qDebug() << Mario_pic.height();
    x = init_x;
    y = init_y;
    mario->setPos(x, y);
    is_jumping = false;
}

void Mario::move(int dx, int dy) {
    x += dx;
    y += dy;
    mario->setPos(x, y);
}
