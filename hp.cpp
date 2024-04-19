#include "hp.h"

Hp::Hp() {
    hp_point = 3;
    hp_text = new QGraphicsTextItem;
    hp_text->setDefaultTextColor(Qt::red);
    hp_text->setScale(1.3);
    hp_text->setPos(x, y);
    set_text();
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
