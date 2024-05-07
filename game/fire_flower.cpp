#include "fire_flower.h"
#include "mario.h"

#include <QDebug>

Fire_flower::Fire_flower() {
    fire_flower_pic.load(":/Dataset/image/item/Fire Flower.png");
    fire_flower_item = new QGraphicsPixmapItem(fire_flower_pic);

}

void Fire_flower::set_xy(int new_x, int new_y) {
    x = new_x;
    y = new_y;
    posx = x;
    posy = y;
    fire_flower_item->setPos(x, y);
}

void Fire_flower::show(){
    set_xy(x,y-50);
    opened = true;
    qDebug()<<"fire?";
}

void Fire_flower::move(int dx) {
    x += dx;
    set_xy(x, y);
}

void Fire_flower::used(){
    set_xy(0,1000);
}

