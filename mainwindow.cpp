#include "mainwindow.h"

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsItem>
#include <QPushButton>
#include "ButtonItem.h"

/*
 * gamestatus:
 * 0 => 開始畫面
 * 1 => 遊戲中
 * 2 => 結算畫面
 */

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // 設定 view
    view->setFixedSize(1400, 620);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // 開始畫面
    game_status = 0;
    connect(start_button, SIGNAL(clicked()), this, SLOT(on_start_button_clicked()));
    start_init();
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
    qDebug() << "Start Button Clicked!\n";
    game_init();
}

void MainWindow::start_init() {
    game_status = 0;
    cur_scene = &start_scene;
    // add start_bg
    start_bg.load(":/Dataset/image/start_screen.png");
    start_bg = start_bg.scaled(1400, 618, Qt::IgnoreAspectRatio);
    QGraphicsPixmapItem *start_bg_item = new QGraphicsPixmapItem(start_bg);
    cur_scene->addItem(start_bg_item);

    // add start_button
    start_button_pic.load(":/Dataset/image/start_btn.png");
    start_button->setIcon(QIcon(start_button_pic));
    start_button->setIconSize(start_button_pic.size());
    ButtonItem *start_button_item = new ButtonItem(start_button);
    start_button_item->setPos(1400 / 2- start_button->width() / 2, 450);
    cur_scene->addItem(start_button_item);
}

void MainWindow::game_init() {
    game_status = 1;
    cur_scene = &game_scene;
    // add game_bg
    QPixmap game_bg(":/Dataset/image/background.png");
    game_bg = game_bg.scaled(1400, 618, Qt::IgnoreAspectRatio);
    QGraphicsPixmapItem *game_bg_item = new QGraphicsPixmapItem(game_bg);
    cur_scene->addItem(game_bg_item);
}


