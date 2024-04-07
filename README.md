# Intro-2-CS2-Project1
This is a C++ OOP project with using Qt to build a Mario game.

# Lesson
Introduction to Computer Science 2 lectured by Prof. Yean-Ru Chen, in 2024 NCKUEE.

# Group 
- Group Number : 16
- Group Member :
  - 蔡承希
  - 蔡辰鑫 (✅)

# 0407 Log

這次把 mario 加入進去了，但在寫 mario.move() 時發現應該不是 mario 要動，而是所有物件要動。

所以下次的任務：
1. 把所有物件(start_bg, game_bg, start_button, floor) 都寫成個別的 Class，且都要個別加上 x, y 屬性
2. 再把 mario 的 move() 移植到 mainwindow() 的 move()，讓 mainwindow 來呼叫所有物件 move

思考要怎麼實現的部分：
1. mario jump
2. mario 改變方向時也改圖片方向(換成反方向的圖片)
 

