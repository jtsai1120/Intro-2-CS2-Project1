#include "mainwindow.h"
#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsItem>
#include <QPushButton>
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
            mario.move();
            view->setScene(&game_scene);
            break;
        case 2:
            view->setScene(&end_scene);
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
        } else if (view_x >= 1400 * 5 - 1402 + Mario::init_x) { // 螢幕不能再往右了，讓 mario 移動
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
            } else if (right_key_state && view_x < 1400 * 5 ) {
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
                cur_scene->removeItem(coins[i]->coin_item);
                coins[i]->set_xy(0, 1000);
                score.add_score(1);
            }
        }

    } else {
        mario.is_moving = 0;
    }
}

void MainWindow::all_horizontal_move(int moving_unit) {
    for (Game_bg* i : game_bgs) i->move(moving_unit, 0);
    for (Coin* i : coins) i->move(moving_unit, 0);
    for (Floor_brick* i : floor_bricks) i->move(moving_unit);
    for (Stone_brick* i : stone_bricks) i->move(moving_unit);
    for (Normal_brick* i : normal_bricks) i->dx = moving_unit;
    for (Box_brick* i : box_bricks) i->move(moving_unit);
    for (Broken_brick* i : broken_bricks) i->move(moving_unit);
    for (Water_pipe* i : water_pipes) i->move(moving_unit);

}


