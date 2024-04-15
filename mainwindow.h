#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ButtonItem.h"
#include "mario.h"
#include "game_bg.h"
#include "floor_brick.h"
#include <vector>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QPushButton>
#include <QKeyEvent>
#include <QLabel>

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);

    protected:
        void keyPressEvent(QKeyEvent *event);

    private slots:
        void update_frame(); // 畫面更新

        void on_start_button_clicked();

    private:
        int game_status; // 0:開始畫面, 1:遊戲中, 2:結束畫面

        void start_init();
        void game_init();
        //void end_init();

        QString key_press;
        void all_move(QString s);

        QGraphicsView *view = new QGraphicsView;

        QGraphicsScene *cur_scene;
        QGraphicsScene start_scene, game_scene, end_scene;

        QPixmap start_bg;
        QGraphicsPixmapItem *start_bg_item;

        QPushButton *start_button = new QPushButton;
        QPixmap start_button_pic;
        ButtonItem *start_button_item;

        Game_bg game_bg;

        Floor_brick floor_bricks;

        Mario mario;

        QTimer *refreshing_timer;


};
#endif // MAINWINDOW_H
