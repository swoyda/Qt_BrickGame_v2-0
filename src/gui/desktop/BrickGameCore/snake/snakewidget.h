#ifndef SNAKEVIEW_H
#define SNAKEVIEW_H

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QMessageBox>
#include "ui_snakewidget.h"
#include "qboxlayout.h"
#include "snakemodel.h"
#include "QObject"
#include "qpainter.h"
#include <QElapsedTimer>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QTextStream>
namespace Ui {
class SnakeView;
}

namespace s21 {
#define X_FIELD 20
#define Y_FIELD 10
#define SNAKE_EDGE 25

class SnakeWidget : public QWidget
{
    Q_OBJECT
signals:
    void backToMenu();
public:
    explicit SnakeWidget(QWidget *parent = nullptr);
    ~SnakeWidget();
    void updateGameTimer();
    void openFile();
    void checkEnd();
protected:
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

public slots:
    void inWindow();
private:
    Ui::SnakeWidget *ui;
    QTimer *gameTimer;
    QElapsedTimer *elapsedTimer;
    SnakeModel *gameModel;
    int seconds_for_timer;
    int level;
    bool start;
    bool fastMode;
    int high_score;
};
}
#endif // SNAKEVIEW_H
