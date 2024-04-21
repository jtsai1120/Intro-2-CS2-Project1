#ifndef FLAG_H
#define FLAG_H

#include "QGraphicsPixmapItem"
#include "QPixmap"
#include "flag_pole.h"
#include "mario.h"
#include "QTimer"


class Flag : public QObject {
    Q_OBJECT
    public:
        Flag();
        QGraphicsPixmapItem *flag_item;
        void move(int dx, int dy);
        void reset();

        static const int init_x = Flag_pole::init_x - 60;
        static const int init_y = Flag_pole::init_y;

        void fall();

        Mario *mario;

        bool is_touched_mario;

    private:
        QPixmap flag_pic;
        int x, y;
        QTimer fall_timer;

    private slots:
        void fall_until_touch_mario();
};

#endif // FLAG_H
