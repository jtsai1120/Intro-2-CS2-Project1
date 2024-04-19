QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    box_brick.cpp \
    broken_brick.cpp \
    coin.cpp \
    flag.cpp \
    flag_pole.cpp \
    floor_brick.cpp \
    game_bg.cpp \
    hp.cpp \
    invisible_brick.cpp \
    main.cpp \
    mainwindow.cpp \
    mario.cpp \
    normal_brick.cpp \
    score.cpp \
    stone_brick.cpp \
    water_pipe.cpp

HEADERS += \
    ButtonItem.h \
    box_brick.h \
    broken_brick.h \
    coin.h \
    flag.h \
    flag_pole.h \
    floor_brick.h \
    game_bg.h \
    hp.h \
    invisible_brick.h \
    mainwindow.h \
    mainwindow_game_init.h \
    mario.h \
    normal_brick.h \
    score.h \
    stone_brick.h \
    water_pipe.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    data.qrc
