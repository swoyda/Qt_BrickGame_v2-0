#ifndef SNAKEMODEL_H
#define SNAKEMODEL_H

#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QMainWindow>
#include "../../../brick_game/snake/model.h"

namespace s21 {

enum DIRECTION { DOWN = 2, UP, LEFT, RIGHT };
enum STATUS { LIVE, END, STOP, VICTORY };

class SnakeModel : public QWidget, Model {
    // Q_OBJECT

public:
    SnakeModel(QWidget* parent = nullptr);
    void changeStatus(int status);
    void changeDirection(int direct);
    QVector<QPoint> getSnake();
    QPoint getApple();
    int getStatus();
    long getTime();
    int getScore();
signals:
    void gameStatusChanged();
public slots:
    void updateGame();

private:
    int direction;
    QVector<QPoint> snake;
    Model model;
    int game_status;
    QPoint apple;
    timespec time;
};
} // s21
#endif // SNAKEMODEL_H
