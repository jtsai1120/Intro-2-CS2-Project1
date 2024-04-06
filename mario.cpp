#include "mario.h"
#include "mainwindow.h"

Mario::Mario() {

}

void Mario::game_init() {
    Mario_pic.load(":/Dataset/image/Mario_small/s_mario_stand_R.png");
    mario = new QGraphicsPixmapItem(Mario_pic);
    mario->setPos(100, 620 - floor_brick_height - Mario_pic.height());
    cur_scene->addItem(mario);
}
