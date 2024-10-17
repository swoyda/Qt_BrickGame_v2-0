QT       += core gui widgets
# win32 {
#     message("Building on Windows")
#     INCLUDEPATH += C:\Users\Dima\source\PDCurses
#     LIBS += -LC:\Users\Dima\source\PDCurses\wincon -lpdcurses
# } else:unix {
#     message("Building on Unix-like OS")
#     LIBS += -lncurses
# }
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
TEMPLATE = app
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../../brick_game/snake/model.cpp \
    ../../../brick_game/tetris/core/figures.c \
    ../../../brick_game/tetris/core/fsm.c \
    ../../../brick_game/tetris/core/tetris.c \
    main.cpp \
    mainwindow.cpp \
    snake/snakemodel.cpp \
    snake/snakewidget.cpp \
    tetris/tetriswidget.cpp

HEADERS += \
    ../../../brick_game/defines.h \
    ../../../brick_game/snake/model.h \
    ../../../brick_game/tetris/common/common.h \
    ../../../brick_game/tetris/core/inc/figures.h \
    ../../../brick_game/tetris/core/inc/fsm.h \
    ../../../brick_game/tetris/core/inc/objects.h \
    ../../../brick_game/tetris/core/inc/tetris.h \
    mainwindow.h \
    snake/snakemodel.h \
    snake/snakewidget.h \
    tetris/tetriswidget.h

FORMS += \
    mainwindow.ui \
    snake/snakewidget.ui \
    tetris/tetriswidget.ui

# Default rules for deployment.
# qnx: target.path = /tmp/$${TARGET}/bin
# else: unix:!android: target.path = /opt/$${TARGET}/bin
# !isEmpty(target.path): INSTALLS += target
