#ifndef HP_H
#define HP_H

#include <QGraphicsItem>
#include <QString>

class Hp {
    public:
        Hp();
        QGraphicsTextItem *hp_text;
        QGraphicsPixmapItem *hp_item;

        const int x = 115;
        const int y = 0;

        int get_hp() { return hp_point; }
        void add_hp(int n);
        void sub_hp(int n);
        void set_xy(int new_x,int new_y);

    private:
        QPixmap hp_pic;
        int hp_point;
        void set_text();

};

#endif // HP_H
