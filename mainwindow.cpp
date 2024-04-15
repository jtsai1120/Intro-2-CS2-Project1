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
    refreshing_timer->start(1); // 每 1ms更新一次
    connect(refreshing_timer, SIGNAL(timeout()), this, SLOT(update_frame())); // 連接訊號
    /* 這段首先建立了一個計時器 refreshing_timer，
     * 並設定計時器時長為 1ms，也就是每過 1ms，
     * 計時器的 timeout() 成員函數會觸發一次。
     * 再來，我們把此計時器的 timeout()訊號(Signal)連接到 this(此MainWindow物件) 的 update_object()訊號槽(Slot)
     * 也就是每當計時器的 timeout() 被觸發，就會執行 this 的 update_object() -> 每 1 ms更新一次畫面
     */
}

void MainWindow::update_frame() {
    switch(game_status) {
        case 0:
            view->setScene(&start_scene);
            break;
        case 1:
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

void MainWindow::game_init() {
    game_status = 1;
    cur_scene = &game_scene;
    view_x = Mario::init_x; // Equals to mario's x coordinates between the scenes;

    // add game_bg
    cur_scene->addItem(game_bg.game_bg_item);

    // add floor_bricks_item(s)
    for (QGraphicsPixmapItem* item : floor_bricks.floor_brick_items)
        cur_scene->addItem(item);

    // add mario
    cur_scene->addItem(mario.mario);

}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (game_status == 1) {
        if (event->key() == Qt::Key_A) // a (left)
            all_move_detection("left");
        else if (event->key() == Qt::Key_D) // d (right)
            all_move_detection("right");
        else if (event->key() == Qt::Key_W) // w (up)
            all_move_detection("up");
    }
}

void MainWindow::all_move_detection(QString s) {
    // Move Left or Right
    const int moving_unit = 10;
    if(view_x <= Mario::init_x) { // 螢幕不能再往左了，讓 mario 移動
        if (s == "left" && view_x > 0) {
            view_x -= moving_unit;
            mario.move(-1 * moving_unit, 0);
        } else if (s == "right") {
            if (view_x == Mario::init_x)
                all_horizontal_move(-1 * moving_unit);
            else
                mario.move(moving_unit, 0);
            view_x += moving_unit;
        }
    } else if (view_x >= 1400 * 5 - 1402 + Mario::init_x) { // 螢幕不能再往右了，讓 mario 移動
        if (s == "left") {
            if (view_x == 1400 * 5 - 1402 + Mario::init_x)
                all_horizontal_move(moving_unit);
            else
                mario.move(-1 * moving_unit, 0);
            view_x -= moving_unit;
        } else if (s == "right" && view_x < 1400 * 5 ) {
            if (view_x == 1400 * 5 - 1402 + Mario::init_x)
                mario.set_x(view_x);
            view_x += moving_unit;
            mario.move(moving_unit, 0);
        }
    } else {
        if (s == "left") {
            view_x -= moving_unit;
            all_horizontal_move(moving_unit);
        } else if (s == "right") {
            view_x += moving_unit;
            all_horizontal_move(-1 * moving_unit);
        }
    }

    // Jump
    if (s == "up") {

    }
}

void MainWindow::all_horizontal_move(int moving_unit) {
    game_bg.move(moving_unit, 0);
}


