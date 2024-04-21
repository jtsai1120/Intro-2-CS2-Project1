#include "mainwindow.h"
#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsItem>
#include <QPushButton>
#include <QGraphicsRectItem>
#include <QGraphicsDropShadowEffect>
#include "ButtonItem.h"
#include "mario.h"

#include "mainwindow_game_init.h"

/*
 * gamestatus:
 * 0 => 開始畫面
 * 1 => 遊戲中
 * 2 => 結算畫面
 */

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // 設定 view 視窗相關設定
    view->setFixedSize(1402, 622);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // 呼叫 start_init() 新增開始畫面物件、基本遊戲設定；
    start_init();
    // 將開始按鈕連接至訊號槽
    connect(start_button, SIGNAL(clicked()), this, SLOT(on_start_button_clicked()));
    // 每 1ms 觸發畫面更新
    refreshing_timer = new QTimer(this); // 建立計時器
    refreshing_timer->start(10); // 每 10ms更新一次
    connect(refreshing_timer, SIGNAL(timeout()), this, SLOT(update_frame())); // 連接訊號
    /* 這段首先建立了一個計時器 refreshing_timer，
     * 並設定計時器時長為 1ms，也就是每過 1ms，
     * 計時器的 timeout() 成員函數會觸發一次。
     * 再來，我們把此計時器的 timeout()訊號(Signal)連接到 this(此MainWindow物件) 的 update_object()訊號槽(Slot)
     * 也就是每當計時器的 timeout() 被觸發，就會執行 this 的 update_object() -> 每 1 ms更新一次畫面
     */
    left_key_state = 0;
    right_key_state = 0;
    up_key_state = 0;
    restart_button_item = new ButtonItem(restart_button);
}

void MainWindow::update_frame() {
    // 設定視窗(view)的場景(scene)
    switch (game_status) {
        case 0:
            view->setScene(&start_scene);
            break;
        case 1:
            all_move_detection();
            for(Normal_brick *i : normal_bricks) i->move();
            for(Broken_brick *i : broken_bricks) i->move();
            for(Toxic_mushroom *i : toxic_mushrooms) i->move();


            mario.move();
            view->setScene(&game_scene);
            if (flag.is_touched_mario) end_init();
            if (hp.get_hp() == 0) end_init();
            if (mario.get_y() > 620) end_init();
            break;
        case 2:
            view->setScene(&game_scene);
            break;
    }
    this->setCentralWidget(view);
}

void MainWindow::on_start_button_clicked() {
    qDebug() << "Start Button Clicked!";
    // 呼叫 game_init() 新增遊戲畫面物件：
    game_init();
}

void MainWindow::start_init() {
    // 設定遊戲狀態為初始畫面
    game_status = 0;
    // 將要提交給 view 的 (ptr)cur_scene 設為 &start_scene
    cur_scene = &start_scene;
    // add start_bg
    start_bg.load(":/Dataset/image/start_screen.png");
    start_bg = start_bg.scaled(1400, 618, Qt::IgnoreAspectRatio);
    start_bg_item = new QGraphicsPixmapItem(start_bg);
    cur_scene->addItem(start_bg_item);
    // add start_button
    start_button_pic.load(":/Dataset/image/start_btn.png");
    start_button->setIcon(QIcon(start_button_pic));
    start_button->setIconSize(start_button_pic.size());
    start_button_item = new ButtonItem(start_button);
    start_button_item->setPos(1400 / 2- start_button->width() / 2, 450);
    cur_scene->addItem(start_button_item);
}

// void MainWindow::game_init() 已移植到 mainwindow_game_init.h

void MainWindow::end_init() {
    qDebug() << "end_init() Called";
    game_status = 2;

    // game over objects' x coordinate;
    game_over_object_x = 1400;

    // add white Rect bar
    rectItem = new QGraphicsRectItem(0, 100, 1400, 300);
    rectItem->setBrush(Qt::white);
    cur_scene->addItem(rectItem);

    // add game over bg
    game_over_bg.load(":/Dataset/image/game_over.png");
    game_over_bg = game_over_bg.scaled(1400, 620, Qt::IgnoreAspectRatio);
    game_over_bg_item = new QGraphicsPixmapItem(game_over_bg);
    game_over_bg_item->setPos(game_over_object_x ,-200);
    cur_scene->addItem(game_over_bg_item);

    // add win or lose
    win_or_lose_text = new QGraphicsTextItem;
    QFont font("Consolas");
    win_or_lose_text->setFont(font);

    win_or_lose_text->setDefaultTextColor(Qt::red);
    win_or_lose_text->setScale(2);
    win_or_lose_text->setPos(game_over_object_x + 350, 200);
    QString win_or_lose_text_combined = "You ";
    if (mario.get_y() > 620) {
        win_or_lose_text_combined = win_or_lose_text_combined + "Lose, Fall UnderGround";
    } else
    if (hp.get_hp() == 0) {
        win_or_lose_text_combined = win_or_lose_text_combined + "Lose, HP -> 0";
    } else if (score.get_score() <= 20) {
        win_or_lose_text_combined = win_or_lose_text_combined + "Lose, Score <= 20)";
    } else { // win
        win_or_lose_text_combined = win_or_lose_text_combined + "Win";
    }

    win_or_lose_text_combined =
        win_or_lose_text_combined + " \n" + "  ( Total : " + QString::number(score.get_score()) + " Coin(s) )";
    win_or_lose_text->setPlainText(win_or_lose_text_combined);
    cur_scene->addItem(win_or_lose_text);

    fade_in_timer = new QTimer;
    QObject::connect(fade_in_timer, SIGNAL(timeout()), this, SLOT(game_over_fade_in()));
    fade_in_timer->start(1);

}

void MainWindow::game_over_fade_in() {
    game_over_object_x -= 5;
    rectItem->setX(game_over_object_x);
    game_over_bg_item->setX(game_over_object_x);
    win_or_lose_text->setX(game_over_object_x + 350);
    if (game_over_object_x <= 0) {
        fade_in_timer->stop();
        delete fade_in_timer;
        restart_button_pic.load(":/Dataset/image/restart_button.png");
        restart_button_pic = restart_button_pic.scaled(100, 100, Qt::IgnoreAspectRatio);
        restart_button->setIcon(QIcon(restart_button_pic));
        restart_button->setIconSize(restart_button_pic.size());
        restart_button->raise();
        restart_button_item->setPos(700-restart_button_pic.width()/2, 400-restart_button_pic.height()/2);
        QObject::connect(restart_button, SIGNAL(clicked()), this, SLOT(on_restart_button_clicked()));
        cur_scene->addItem(restart_button_item);
    }
}

void MainWindow::on_restart_button_clicked() {
    qDebug() << "restart button clicked !";

    // 移除動畫
    game_over_object_x = 10000;
    rectItem->setX(game_over_object_x);
    game_over_bg_item->setX(game_over_object_x);
    win_or_lose_text->setX(game_over_object_x + 350);
    restart_button_item->setPos(10000, 0);

    // 呼叫 game_restart() 重置遊戲畫面物件：
    game_status = 1;
    game_restart();
    left_key_state = 0;
    right_key_state = 0;
    up_key_state = 0;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (game_status == 1) {
        if (event->key() == Qt::Key_A) {// a (left)
            left_key_state = 1;
            //qDebug() << "mario left";
        }
        else if (event->key() == Qt::Key_D) {// d (right)
            right_key_state = 1;
            //qDebug() << "mario right";
        }
        else if (event->key() == Qt::Key_W) // w (up)
            up_key_state = 1;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (game_status == 1) {
        if (event->key() == Qt::Key_A) // a (left)
            left_key_state = 0;
        else if (event->key() == Qt::Key_D)  // d (right)
            right_key_state = 0;
        else if (event->key() == Qt::Key_W) // w (up)
            up_key_state = 0;
    }
}

void MainWindow::all_move_detection() {
    if (left_key_state || right_key_state || up_key_state) {
        mario.is_moving = 1;
        //qDebug() << "mario is moving";
        // Move Left or Right
        const int moving_unit = 5;
        int distance=0;
        if(view_x <= Mario::init_x) { // 螢幕不能再往左了，讓 mario 移動
            if (left_key_state && view_x > 0) {
                mario.cur_direction = 'L';
                if (!mario.is_hit_right_side()) {
                    view_x -= moving_unit;
                    mario.dx = -1 * moving_unit;
                    distance+=5;
                    if (distance==moving_unit){
                        mario.change();
                        distance=0;
                   }
                }
            } else if (right_key_state) {
                mario.cur_direction = 'R';
                if (!mario.is_hit_left_side()) {
                    if (view_x == Mario::init_x)
                        all_horizontal_move(-1 * moving_unit);
                    else
                        mario.dx = moving_unit;
                    view_x += moving_unit;
                    distance+=5;
                    if (distance==moving_unit){
                        mario.change();
                        distance=0;
                   }
                }
            }
        }
        else if (view_x >= 1400 * 5 - 1402 + Mario::init_x) { // 螢幕不能再往右了，讓 mario 移動
            if (left_key_state) {
                mario.cur_direction = 'L';
                if (!mario.is_hit_right_side()) {
                    if (view_x == 1400 * 5 - 1402 + Mario::init_x)
                        all_horizontal_move(moving_unit);
                    else
                        mario.dx = -1 * moving_unit;
                    view_x -= moving_unit;
                    distance+=5;
                    if (distance==moving_unit){
                        mario.change();
                        distance=0;
                   }
                }
            }
            else if (right_key_state && view_x < 1400 * 5 ) {
                mario.cur_direction = 'R';
                if (!mario.is_hit_left_side()) {
                    if (view_x == 1400 * 5 - 1402 + Mario::init_x)
                        mario.set_x(view_x);
                    view_x += moving_unit;
                    mario.dx = moving_unit;
                    distance+=5;
                    if (distance==moving_unit){
                        mario.change();
                        distance=0;
                   }
                }
            }
        } else {
            if (left_key_state) {
                mario.cur_direction = 'L';
                if (!mario.is_hit_right_side()) {
                    view_x -= moving_unit;
                    all_horizontal_move(moving_unit);
                    distance+=5;
                    if (distance==moving_unit){
                        mario.change();
                        distance=0;
                   }
                }
            } else if (right_key_state) {
                mario.cur_direction = 'R';
                if (!mario.is_hit_left_side()) {
                    view_x += moving_unit;
                    all_horizontal_move(-1 * moving_unit);
                    distance+=5;
                    if (distance==moving_unit){
                        mario.change();
                        distance=0;
                   }
                }
            }
        }

        // Jump
        if (up_key_state) {
            //qDebug() << "mario jump";
            mario.jump();

        }

        // 偵測移動過程是否與其他物件碰撞
        // coins
        for (int i = 0; i < static_cast<int>(coins.size()); i++) {
            if (mario.mario->collidesWithItem(coins[i]->coin_item)) {
                qDebug() << "mario get coin !";
                coins[i]->set_xy(0, 1000);
                score.add_score(1);
            }
        }

        // toxic mushroom
        for (int i = 0; i < static_cast<int>(toxic_mushrooms.size()); i++) {
            if (mario.mario->collidesWithItem(toxic_mushrooms[i]->toxic_mushroom_item)) {
                qDebug() << "Ow";
                mario.is_taller(i);
            }
        }

        // flag pole
        if (mario.mario->collidesWithItem(flag_pole.flag_pole_item) && !flag_pole.is_touched) {
            qDebug() << "mario touch flag pole !";
            flag_pole.is_touched = 1;
            mario.movable = 0;
            flag.fall();
        }

    } else {
        mario.is_moving = 0;

        // toxic mushroom
        for (int i = 0; i < static_cast<int>(toxic_mushrooms.size()); i++) {
            if (mario.mario->collidesWithItem(toxic_mushrooms[i]->toxic_mushroom_item)) {
                qDebug() << "Ow";
                mario.is_taller(i);
            }
        }
    }
}

void MainWindow::all_horizontal_move(int moving_unit) {
    for (Game_bg* i : game_bgs) i->move(moving_unit, 0);
    flag_pole.move(moving_unit, 0);
    flag.move(moving_unit, 0);
    for (Coin* i : coins) i->move(moving_unit, 0);
    for (Floor_brick* i : floor_bricks) i->move(moving_unit);
    for (Stone_brick* i : stone_bricks) i->move(moving_unit);
    for (Normal_brick* i : normal_bricks) i->dx = moving_unit;
    for (Broken_brick* i : broken_bricks) i->dx = moving_unit;
    for (Box_brick* i : box_bricks) i->move(moving_unit);
    for (Box_brick* i : box_bricks) i->super_mushroom.move(moving_unit);
    for (Water_pipe* i : water_pipes) i->move(moving_unit);
    for (Invisible_brick* i : invisible_bricks) i->move(moving_unit);
    for (Toxic_mushroom* i : toxic_mushrooms) i->dx = moving_unit;
}


