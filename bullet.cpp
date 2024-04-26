#include "bullet.h"
#include "mario.h"

#include <QDebug>

Bullet::Bullet() {
    bullet_pic.load(":/Dataset/image/bullet.png");
    bullet_item = new QGraphicsPixmapItem(bullet_pic);

}

void Bullet::set_xy(int new_x, int new_y) {
    x = new_x;
    y = new_y;
    posx = x;
    posy = y;
    x2 = x;
    y2 = y;
    bullet_item->setPos(x, y);
}



void Bullet::move(int dx) {
    x += dx;
    set_xy(x, y);
}

void Bullet::shoot(float m , int x0, int y0, int tx){
    set_xy(x0,y0+2);
    already_shot = true;
    m1 = m;
    if (tx >= x){  //the target is on the right
        direction = 2;
    }
    else direction = -2; //the target is on the left
}

void Bullet::fly(){
    x2 += direction;
    y2 += direction * m1;
    set_xy(x2,y2);
    if (y2<=0 || y2>=620 || x2<=0 || is_grounded() || is_hit_left_side() || is_hit_right_side()){
        set_xy(0,1000);
        already_shot = false;
    }
    // shoot toxic mushroom
    for (int i = 0; i < static_cast<int>(toxic_mushrooms.size()); i++) {
        if ((bullet_item)->collidesWithItem(toxic_mushrooms[i]->toxic_mushroom_item)) {
            //qDebug()<<"shoot mushroom";
            toxic_mushrooms[i]->dead = 1;
            already_shot = false;
            set_xy(0,1000);
        }
    }

}

bool Bullet::is_grounded() {
    QList<QGraphicsItem *> items = cur_scene->items();
    bool _is_grounded = 0;

    for (QGraphicsItem *item : items) {
        QGraphicsPixmapItem *PixmapItem = qgraphicsitem_cast<QGraphicsPixmapItem*>(item);
        if (item->contains(item->mapFromScene(x + 5, y + 5))) {
            if(check_whether_ground_brick(PixmapItem)) {
                //qDebug() << "left foot is grounded";
                _is_grounded = 1;
            }
        }
        if (item->contains(item->mapFromScene(x + 5, (y + 5)))) {
            if(check_whether_ground_brick(PixmapItem)) {
                //qDebug() << "right foot is grounded";
                _is_grounded = 1;
            }
        }
    }
    return _is_grounded;

}

bool Bullet::check_whether_ground_brick(QGraphicsPixmapItem *PixmapItem) {
    // exit it
    //if(still)return 0;

    bool is_ground_brick = 0;
    // check whether floor brick(s)
    for (Floor_brick *i : floor_bricks)
        if (i->floor_brick_item == PixmapItem)
            is_ground_brick = 1;

    // check whether stone brick
    for (Stone_brick *i : stone_bricks)
        if (i->stone_brick_item == PixmapItem)
            is_ground_brick = 1;

    // check whether broken brick
    for (Broken_brick *i : broken_bricks)
        if (i->broken_brick_item == PixmapItem && i->broken == false)
            is_ground_brick = 1;

    // check whether normal brick
    for (Normal_brick *i : normal_bricks)
        if (i->normal_brick_item == PixmapItem)
            is_ground_brick = 1;

    // check whether box brick
    for (Box_brick *i : box_bricks)
        if (i->box_brick_item == PixmapItem)
            is_ground_brick = 1;

    // check whether water pipe
    for (Water_pipe *i : water_pipes)
        if (i->water_pipe_item == PixmapItem)
            is_ground_brick = 1;

    // check whether invisible brick
    for (Invisible_brick *i : invisible_bricks)
        if (i->invisible_brick_item == PixmapItem)
            is_ground_brick = 1;

    return is_ground_brick;
}


bool Bullet::is_hit_left_side() {
    QList<QGraphicsItem *> items = cur_scene->items();
    bool _is_hit_left_side = 0;
    QRectF rect1 = bullet_item->sceneBoundingRect();
    for (QGraphicsItem *item : items) {
        QGraphicsPixmapItem *PixmapItem = qgraphicsitem_cast<QGraphicsPixmapItem*>(item);
        if (check_whether_ground_brick(PixmapItem)) {
            QRectF rect2 = item->sceneBoundingRect();
            if (rect1.right()>rect2.left()&&rect1.left()<rect2.left())
                if (rect1.bottom() - 10 > rect2.top() && rect1.top() < rect2.bottom())
                    _is_hit_left_side = 1;
        }
    }
    return _is_hit_left_side;
}

bool Bullet::is_hit_right_side() {
    QList<QGraphicsItem *> items = cur_scene->items();
    bool _is_hit_right_side = 0;
    QRectF rect1 = bullet_item->sceneBoundingRect();
    for (QGraphicsItem *item : items) {
        QGraphicsPixmapItem *PixmapItem = qgraphicsitem_cast<QGraphicsPixmapItem*>(item);
        if (check_whether_ground_brick(PixmapItem)) {
            QRectF rect2 = item->sceneBoundingRect();
            if (rect1.left()<rect2.right()&&rect1.right()>rect2.right())
                if (rect1.bottom() - 10 > rect2.top() && rect1.top() < rect2.bottom())
                    _is_hit_right_side = 1;
        }
    }
    return _is_hit_right_side;
}


