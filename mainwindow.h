#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QPushButton>

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);

    private slots:
        void update_frame(); // 畫面更新

        void on_start_button_clicked();

    private:
        int game_status; // 0:開始畫面, 1:遊戲中, 2:結束畫面

        void start_init();
        void game_init();
        //void end_init();

        QGraphicsView *view = new QGraphicsView;

        QGraphicsScene *cur_scene;
        QGraphicsScene start_scene, game_scene, end_scene;

        QPixmap start_bg;
        QPushButton *start_button = new QPushButton;
        QPixmap start_button_pic;


        QTimer *refreshing_timer;

        //void game_frame();

};
#endif // MAINWINDOW_H
