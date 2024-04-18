#ifndef HP_H
#define HP_H

#include <QGraphicsItem>
#include <QString>

class Hp {
    public:
        Hp();
        QGraphicsTextItem *hp_text;

        const int x = 115;
        const int y = 0;

        void add_hp(int n);
        void sub_hp(int n);

    private:
        int hp_point;
        void set_text();
};

#endif // HP_H
