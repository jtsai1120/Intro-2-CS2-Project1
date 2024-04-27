#include "hp.h"

Hp::Hp() {
    hp_point = 3;
    hp_text = new QGraphicsTextItem;
    hp_pic.load(":/Dataset/image/heart.png");
    hp_item = new QGraphicsPixmapItem(hp_pic);
    hp_text->setDefaultTextColor(Qt::red);
    hp_text->setScale(1.3);
    hp_text->setPos(x, y);
    set_text();
    hp_text->setZValue(100);
    hp_item->setZValue(100);
}

void Hp::set_xy(int new_x, int new_y) {
    hp_item->setPos(new_x, new_y);
}

void Hp::add_hp(int n = 1) {
    hp_point += n;
    set_text();
}

void Hp::sub_hp(int n = 1) {
    hp_point -= n;
    set_text();
}

void Hp::set_text() {
    QString hp_text_combined = "HP: " + QString::number(hp_point);
    hp_text->setPlainText(hp_text_combined);
}
