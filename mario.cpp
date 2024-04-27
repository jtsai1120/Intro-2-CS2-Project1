#include "mario.h"
#include "mainwindow.h"
#include <QString>
#include <QDebug>
#include <QTimer>
#include <QObject>
#include <QCoreApplication>
#include <QRectF>
#include <QLabel>

Mario::Mario(QWidget *parent) : QObject(parent) {
    mario_stand_R.load(":/Dataset/image/Mario_small/s_mario_stand_R.png");
    mario_stand_L.load(":/Dataset/image/Mario_small/s_mario_stand_L.png");
    mario_jump_R.load(":/Dataset/image/Mario_small/s_mario_jump1_R.png");
    mario_jump_L.load(":/Dataset/image/Mario_small/s_mario_jump1_L.png");
    mario_die.load(":/Dataset/image/Mario_small/s_mario_die.png");
    mario_run1_L.load(":/Dataset/image/Mario_small/s_mario_run1_L.png");
    mario_run1_R.load(":/Dataset/image/Mario_small/s_mario_run1_R.png");
    mario_run2_L.load(":/Dataset/image/Mario_small/s_mario_run2_L.png");
    mario_run2_R.load(":/Dataset/image/Mario_small/s_mario_run2_R.png");

    mario_big_stand_R.load(":/Dataset/image/Mario_big/mario_R_stand.png");
    mario_big_stand_L.load(":/Dataset/image/Mario_big/mario_L_stand.png");
    mario_big_jump_R_1.load(":/Dataset/image/Mario_big/mario_R_jump1.png");
    mario_big_jump_L_1.load(":/Dataset/image/Mario_big/mario_L_jump1.png");
    mario_big_jump_R_2.load(":/Dataset/image/Mario_big/mario_R_jump2.png");
    mario_big_jump_L_2.load(":/Dataset/image/Mario_big/mario_L_jump2.png");
    mario_big_jump_R_3.load(":/Dataset/image/Mario_big/mario_R_jump3.png");
    mario_big_jump_L_3.load(":/Dataset/image/Mario_big/mario_L_jump3.png");
    mario_big_jump_R_4.load(":/Dataset/image/Mario_big/mario_R_jump4.png");
    mario_big_jump_L_4.load(":/Dataset/image/Mario_big/mario_L_jump4.png");
    mario_big_die.load(":/Dataset/image/Mario_big/b_mario_die.png");
    mario_big_run0_L.load(":/Dataset/image/Mario_big/mario_L_run0.png");
    mario_big_run0_R.load(":/Dataset/image/Mario_big/mario_R_run0.png");
    mario_big_run1_L.load(":/Dataset/image/Mario_big/mario_L_run1.png");
    mario_big_run1_R.load(":/Dataset/image/Mario_big/mario_R_run1.png");
    mario_big_run2_L.load(":/Dataset/image/Mario_big/mario_L_run2.png");
    mario_big_run2_R.load(":/Dataset/image/Mario_big/mario_R_run2.png");
    mario = new QGraphicsPixmapItem(mario_stand_R);
    x = init_x;
    y = init_y;
    dx = 0;
    dy = 0;
    mario->setPos(x, y);
    cur_direction = 'R';
    cur_size = "small";
    cur_pixmap = "stand_R";
    is_moving = 0;
    //qDebug() << "width=" << mario_stand_R.width();
    //qDebug() << "height=" << mario_stand_R.height();
    is_passed_jump_cd = 1;
    immune_status = 0;
    movable = 1;
}

int Mario::walking = 0;

void Mario::change(){
    if (movable) {
        if (!big){
            if (cur_direction == 'R') {
                if (is_grounded()) {
                    if (is_moving) {
                        if (cur_pixmap != "run1_R")
                            cur_pixmap = "run1_R";
                        else
                            cur_pixmap = "run2_R";
                    }
                }
           }
           else{
                if (is_grounded()) {
                    if (is_moving) {
                       if (cur_pixmap != "run1_L")
                            cur_pixmap = "run1_L";
                        else
                            cur_pixmap = "run2_L";
                    }
                }
            }
            //qDebug()<<"change";
        }

        if (big){
            if (cur_direction == 'R'){
                if (walking == 0){
                    cur_pixmap = "big_run0_R";
                    walking++;
                }
                else if (walking == 1){
                    cur_pixmap = "big_run1_R";
                    walking++;
                }
                else if (walking == 2){
                    cur_pixmap = "big_run2_R";
                    walking = 0;
                }
            }
            else{
                if (walking == 0){
                    cur_pixmap = "big_run0_L";
                    walking++;
                }
                else if (walking == 1){
                    cur_pixmap = "big_run1_L";
                    walking++;
                }
                else if (walking == 2){
                    cur_pixmap = "big_run2_L";
                    walking = 0;
                }
            }

        }

        change_direction_picture(cur_pixmap);
    }
}

int Mario::jumping = 0;

void Mario::move() {
    if (movable) {
        if (!big){
            if (cur_direction == 'R') {
                if (is_grounded()) {
                    if (!is_moving)
                        cur_pixmap = "stand_R";
                    else if (!is_passed_jump_cd)
                        cur_pixmap = "stand_R";
                }
                else {
                    cur_pixmap = "jump_R";
                }
            } else {
                if (is_grounded()) {
                    if (!is_moving)
                        cur_pixmap = "stand_L";
                    else if (!is_passed_jump_cd)
                        cur_pixmap = "stand_L";
                }
                else {
                    cur_pixmap = "jump_L";
                }
            }
        }
        if (big){
            if (cur_direction == 'R') {
                if (is_grounded()) {
                    if (!is_moving)
                        cur_pixmap = "big_stand_R";
                    else if (!is_passed_jump_cd)
                        cur_pixmap = "big_stand_R";
                }
                else {
                    if (jumping == 0)
                        cur_pixmap = "big_jump1_R";
                    if (jumping == 1)
                        cur_pixmap = "big_jump2_R";
                    if (jumping == 2)
                        cur_pixmap = "big_jump3_R";
                    if (jumping == 3)
                        cur_pixmap = "big_jump4_R";
                }
            } else {
                if (is_grounded()) {
                    if (!is_moving)
                        cur_pixmap = "big_stand_L";
                    else if (!is_passed_jump_cd)
                        cur_pixmap = "big_stand_L";
                }
                else {
                    if (jumping == 0)
                        cur_pixmap = "big_jump1_L";
                    if (jumping == 1)
                        cur_pixmap = "big_jump2_L";
                    if (jumping == 2)
                        cur_pixmap = "big_jump3_L";
                    if (jumping == 3)
                        cur_pixmap = "big_jump4_L";

                }
            }
        }

        change_direction_picture(cur_pixmap);

        //移動時活化毒蘑菇
        if(x > 6300 || x < 700){
            for (Toxic_mushroom* i : toxic_mushrooms)
                if(abs(i -> x - x) > 1400) i -> still = true;
                else i -> still = false;

        }
        else
            for (Toxic_mushroom* i : toxic_mushrooms)
                if(abs(i -> x - x) > 800) i -> still = true;
                else i -> still = false;

        /*
        if (is_hit_left_side())
            qDebug() << "hit left side!";
        if (is_hit_right_side())
            qDebug() << "hit right side!";
        if (is_crack_head())
            qDebug() << "is crack head";
        */
        x += dx;
        dx = 0;

        y += dy;

        if (!big)
            ay = 0.18;
        else if (big)
            ay = 0.2;

        if (is_crack_head()) dy = 1;
        else if (!is_grounded()) {
            dy += ay;
            if (big)
                jumping_distance+=y;
            if (jumping_distance > 8000){
                if (jumping < 4){
                    jumping ++;
                    qDebug()<<jumping;
                }
                else jumping = 0;
                jumping_distance = 0;
            }
        }
        else dy = 0;

        if (!big){
            mario->setPos(x, y);
        }
        if (big){
            mario->setPos(x, y-32);
        }
    }
}

void Mario::change_direction_picture(QString s) {
    if (s == "stand_R")
        mario->setPixmap(mario_stand_R);
    else if (s == "stand_L")
        mario->setPixmap(mario_stand_L);
    else if (s == "run1_L")
        mario->setPixmap(mario_run1_L);
    else if (s == "run2_L")
        mario->setPixmap(mario_run2_L);
    else if (s == "run1_R")
        mario->setPixmap(mario_run1_R);
    else if (s == "run2_R")
        mario->setPixmap(mario_run2_R);
    else if (s == "die")
        mario->setPixmap(mario_die);
    else if (s == "jump_L")
        mario->setPixmap(mario_jump_L);
    else if (s == "jump_R")
        mario->setPixmap(mario_jump_R);

    else if (s == "big_stand_R")
        mario->setPixmap(mario_big_stand_R);
    else if (s == "big_stand_L")
        mario->setPixmap(mario_big_stand_L);
    else if (s == "big_run0_L")
        mario->setPixmap(mario_big_run0_L);
    else if (s == "big_run1_L")
        mario->setPixmap(mario_big_run1_L);
    else if (s == "big_run2_L")
        mario->setPixmap(mario_big_run2_L);
    else if (s == "big_run0_R")
        mario->setPixmap(mario_big_run0_R);
    else if (s == "big_run1_R")
        mario->setPixmap(mario_big_run1_R);
    else if (s == "big_run2_R")
        mario->setPixmap(mario_big_run2_R);
    else if (s == "big_jump1_L")
        mario->setPixmap(mario_big_jump_L_1);
    else if (s == "big_jump2_L")
        mario->setPixmap(mario_big_jump_L_2);
    else if (s == "big_jump3_L")
        mario->setPixmap(mario_big_jump_L_3);
    else if (s == "big_jump4_L")
        mario->setPixmap(mario_big_jump_L_4);
    else if (s == "big_jump1_R")
        mario->setPixmap(mario_big_jump_R_1);
    else if (s == "big_jump2_R")
        mario->setPixmap(mario_big_jump_R_2);
    else if (s == "big_jump3_R")
        mario->setPixmap(mario_big_jump_R_3);
    else if (s == "big_jump4_R")
        mario->setPixmap(mario_big_jump_R_4);
    else if (s == "big_die")
        mario->setPixmap(mario_big_die);

    else qDebug() << "Mario Pixmap Error";
}

void Mario::jump() {
    if (is_grounded() && is_passed_jump_cd) { // 防止二次跳
        if (!big)
            vy0 = -6;
        if (big)
            vy0 = -8;
        dy = vy0;
    }
}

void Mario::jump_cd_trigger() {
    jump_cd.stop();
    //qDebug() << "jump cd passed!";
    is_passed_jump_cd = 1;
}

void Mario::immune_time() {
    immune.stop();
    immune_status = 0;
}

void Mario::is_taller(int i){
    if (y < toxic_mushrooms[i]->y - 42 && dy >= 0 || y < toxic_mushrooms[i]->y - 35 && dy >= 0 && big == true){ //扣掉毒菇本身高度&&確保馬力歐不是在上升
        toxic_mushrooms[i]->dead = 1;
    }
    else if(!immune_status && !toxic_mushrooms[i]->dead){ //非免疫狀態且毒菇沒死
        hp->sub_hp(1); //扣血
        hps[hp->get_hp()]->set_xy(0,1000);
        big = false;
        immune_status = 1;
        qDebug() << "Ow";
        QObject::connect(&immune, SIGNAL(timeout()), this, SLOT(immune_time()));
        immune.start(2000);
    }
}

void Mario::touch_super_mushroom(){
    if (hp->get_hp()<3){
        hp->add_hp(1);
        hps[hp->get_hp()-1]->set_xy(70+40*hp->get_hp(),7);
    }
    big = true;

}

void Mario::touch_fire_flower(){
    bullet = 3;
}

void Mario::shoot(int tx, int ty){
    m = static_cast<float>(ty-y)/static_cast<float>(tx-x);
    qDebug()<<"mario shoot"<<bullet;
    qDebug()<<m;
    for (Bullet *i : bullets){
        if (i->posx == 0 && i->posy == 1000 && bullet >= 1){
            qDebug()<<"enter shoot function";
            i->shoot(m,x,y,tx);
            bullet --;
            break;
        }
    }
}


bool Mario::is_grounded() {
    QList<QGraphicsItem *> items = cur_scene->items();
    bool _is_grounded = 0;
    for (QGraphicsItem *item : items) {
        QGraphicsPixmapItem *PixmapItem = qgraphicsitem_cast<QGraphicsPixmapItem*>(item);
        if (item->contains(item->mapFromScene(x + 10, y + ((cur_size=="small")? small_mario_height : big_mario_height)))) {
            if(check_whether_ground_brick(PixmapItem)) {
                //qDebug() << "left foot is grounded";
                _is_grounded = 1;
            }
        }
        if (item->contains(item->mapFromScene(x + ((cur_size=="small")? small_mario_width : big_mario_width), (y + ((cur_size=="small")? small_mario_height : big_mario_height))))) {
            if(check_whether_ground_brick(PixmapItem)) {
                //qDebug() << "right foot is grounded";
                _is_grounded = 1;
            }
        }
    }
    return _is_grounded;
}

bool Mario::check_whether_ground_brick(QGraphicsPixmapItem *PixmapItem) {
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
        if (i->broken_brick_item == PixmapItem)
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


bool Mario::is_crack_head() {
    QList<QGraphicsItem *> items = cur_scene->items();
    bool _is_crack_head = 0;
    bool _is_crack_noraml_brick = 0;
    bool _is_crack_broken_brick = 0;
    bool _is_crack_box_brick = 0;
    bool mushroom_move = false;

    Normal_brick *hit_normal_brick;
    Broken_brick *hit_broken_brick;
    Box_brick *hit_box_brick;
    //Super_mushroom *show_super_mushroom;

    for (QGraphicsItem *item : items) {
        QGraphicsPixmapItem *PixmapItem = qgraphicsitem_cast<QGraphicsPixmapItem*>(item);
        if (item->contains(item->mapFromScene(x + 10, y))) {
            if(check_whether_ground_brick(PixmapItem)) {
                _is_crack_head = 1;
                for (Normal_brick *i : normal_bricks)
                    if (i->normal_brick_item == PixmapItem) {
                        _is_crack_noraml_brick = 1;
                        hit_normal_brick = i;
                    }
                for (Broken_brick *i : broken_bricks)
                    if (i->broken_brick_item == PixmapItem) {
                        _is_crack_broken_brick = 1;
                        hit_broken_brick = i;
                    }
                for (Box_brick *i : box_bricks)
                    if (i->box_brick_item == PixmapItem) {
                        _is_crack_box_brick = 1;
                        hit_box_brick = i;

                    }


            }
        }
        if (item->contains(item->mapFromScene(x + ((cur_size=="small")? small_mario_width : big_mario_width), y))) {
            if(check_whether_ground_brick(PixmapItem)) {
                _is_crack_head = 1;
                for (Normal_brick *i : normal_bricks)
                    if (i->normal_brick_item == PixmapItem) {
                        _is_crack_noraml_brick = 1;
                        hit_normal_brick = i;
                    }
                for (Broken_brick *i : broken_bricks)
                    if (i->broken_brick_item == PixmapItem) {
                        _is_crack_broken_brick = 1;
                        hit_broken_brick = i;
                     }
                for (Box_brick *i : box_bricks)
                    if (i->box_brick_item == PixmapItem) {
                        _is_crack_box_brick = 1;
                        hit_box_brick = i;
                    }

            }
        }
        if (_is_crack_head && _is_crack_noraml_brick) {
            hit_normal_brick->crack();
            is_passed_jump_cd = 0;
            QObject::connect(&jump_cd, SIGNAL(timeout()), this, SLOT(jump_cd_trigger()));
            jump_cd.start(520);
        }
        if (_is_crack_head && _is_crack_broken_brick) {
            hit_broken_brick->crack();
            is_passed_jump_cd = 0;
            for (Toxic_mushroom* i : toxic_mushrooms){
                i->hitted_left = false;
                i->locked_in = false;
            }
            QObject::connect(&jump_cd, SIGNAL(timeout()), this, SLOT(jump_cd_trigger()));
            jump_cd.start(520);
        }
        if (_is_crack_head && _is_crack_box_brick) {
            hit_box_brick->crack();
            mushroom_move = false;
            for (Super_mushroom *i : super_mushrooms){
                if ((i->posx == hit_box_brick->x_corresonding) && (i->posy == hit_box_brick->y_corresponding) && mushroom_move == false){
                    i->show();
                    mushroom_move=true;
                    break;
                }
            }
            for (Fire_flower *i : fire_flowers){
                if ((i->posx == hit_box_brick->x_corresonding) && (i->posy == hit_box_brick->y_corresponding) && mushroom_move == false){
                    i->show();
                    break;
                }
            }
            is_passed_jump_cd = 0;
            QObject::connect(&jump_cd, SIGNAL(timeout()), this, SLOT(jump_cd_trigger()));
            jump_cd.start(520);
        }



    }
    return _is_crack_head;
}

bool Mario::is_hit_left_side() {
    QList<QGraphicsItem *> items = cur_scene->items();
    bool _is_hit_left_side = 0;
    QRectF rect1 = mario->sceneBoundingRect();
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

bool Mario::is_hit_right_side() {
    QList<QGraphicsItem *> items = cur_scene->items();
    bool _is_hit_right_side = 0;
    QRectF rect1 = mario->sceneBoundingRect();
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

void Mario::reset(){
    x = init_x;
    y = init_y;
    dx = 0;
    dy = 0;
    mario->setPos(x, y);
    cur_direction = 'R';
    cur_size = "small";
    cur_pixmap = "stand_R";
    is_moving = 0;
    //qDebug() << "width=" << mario_stand_R.width();
    //qDebug() << "height=" << mario_stand_R.height();
    is_passed_jump_cd = 1;
    immune_status = 0;
    big = false;
    movable = 1;
    bullet = 0;
    m = 0;
}

