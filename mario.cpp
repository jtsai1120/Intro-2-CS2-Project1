#include "mario.h"
#include "mainwindow.h"
#include <QString>

Mario::Mario() {

}

void Mario::game_init() {
    Mario_pic.load(":/Dataset/image/Mario_small/s_mario_stand_R.png");
    mario = new QGraphicsPixmapItem(Mario_pic);
    x = 300;
    y = 620 - floor_brick_height - Mario_pic.height();
    mario->setPos(x, y);
    cur_scene->addItem(mario);

    is_jumping = false;
}

void Mario::move(QString s) {
    if (s == "left") {
        dx = -5;
        dy = 0;
    }
    else if (s == "right") {
        dx = 5;
        dy = 0;
    }
    else if (s == "up" && !is_jumping) {
        is_jumping = true;
        dx = 0;
        dy = 0;
    }

    x = x + dx;
    y = y + dy;

    mario->setPos(x, y);

}
