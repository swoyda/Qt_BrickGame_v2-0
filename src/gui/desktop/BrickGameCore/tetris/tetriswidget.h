#ifndef TETRISWIDGET_H
#define TETRISWIDGET_H


#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QWidget>
#include "qpainter.h"

extern "C" {

#include "../../../brick_game/tetris/core/inc/tetris.h"

#include "../../../brick_game/tetris/common/common.h"
}

namespace Ui {
class TetrisWidget;
}


class TetrisWidget : public QWidget {
    Q_OBJECT
public:
    explicit TetrisWidget(QWidget *parent = nullptr);
    ~TetrisWidget();

protected:
    void paintEvent(QPaintEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;

private:
    Ui::TetrisWidget *ui;
    QTimer *timer;

private slots:
    void update_paint(void);

signals:
    void backToMenu();
};


#endif // TETRISWIDGET_H
