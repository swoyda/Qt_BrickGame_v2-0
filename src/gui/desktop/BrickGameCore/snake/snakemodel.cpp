#include "snakemodel.h"

#include <QDebug>
#include <QPainter>
using namespace s21;
SnakeModel::SnakeModel(QWidget* parent) : QWidget(parent) {
  for (const auto& pair : model.getSnake()) {
    snake.append(QPoint(pair.second + 1, pair.first + 1));
  }
  direction = model.getDirection();
  apple = {model.getApple().second, model.getApple().first + 1};
  model.setStatus(STOP);
  game_status = model.getStatus();
  time = model.getTimer();
}
long SnakeModel::getTime() { return time.tv_nsec / 1000000; }
void SnakeModel::changeStatus(int status) {
  model.setStatus(status);
  game_status = model.getGameStatus();
  emit gameStatusChanged();
}
void SnakeModel::changeDirection(int direct) {
  if (game_status != END) {
    model.changeDirection(direct);
    direction = model.getDirection();
  }
}

QVector<QPoint> SnakeModel::getSnake() { return snake; }

QPoint SnakeModel::getApple() { return apple; }
int SnakeModel::getStatus() { return game_status; }
int SnakeModel::getScore() { return model.getScore(); }
void SnakeModel::updateGame() {
  model.s21_update();
  game_status = model.getGameStatus();
  emit gameStatusChanged();

  for (const auto& pair : snake) {
    snake.pop_back();
  }
  for (const auto& pair : model.getSnake()) {
    snake.append(QPoint(pair.second, pair.first + 1));
  };
  apple = {model.getApple().second, model.getApple().first + 1};
  update();
}
