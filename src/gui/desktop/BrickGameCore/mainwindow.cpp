#include "mainwindow.h"

#include <QDir>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "snake/snakewidget.h"
#include "tetris/tetriswidget.h"
#include "ui_mainwindow.h"
using namespace s21;

class RacingWidget : public QWidget {
 public:
  RacingWidget(QWidget *parent = nullptr) : QWidget(parent) {
    QPushButton *racingButton = new QPushButton("Гонки", this);
  }
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      stackedWidget(new QStackedWidget(this)) {
  ui->setupUi(this);
  QString appDir = QCoreApplication::applicationDirPath();
  QDir dir(appDir);
  dir.cd("../../../images");
  QString imagePath = dir.absoluteFilePath("back.png");

  ui->background->setStyleSheet(
      QString("QFrame#background { border-image: url(%1); }").arg(imagePath));
  ui->background->show();

  ui->background->autoFillBackground();

  stackedWidget = ui->stackedWidget;
  TetrisWidget *tetrisWidget = new TetrisWidget(this);
  SnakeWidget *snakeWidget = new SnakeWidget(this);

  // layout->addWidget(ui->tetrisButton);
  // layout->addWidget(ui->snakeButton);
  // layout->addWidget(ui->racingButton);

  connect(ui->tetrisButton, &QPushButton::clicked, this,
          &MainWindow::showTetris);
  connect(ui->snakeButton, &QPushButton::clicked, this, &MainWindow::showSnake);
  // connect(ui->racingButton, &QPushButton::clicked, this,
  // &MainWindow::showRacing);

  // stackedWidget->addWidget(mainMenuWidget);
  connect(tetrisWidget, &TetrisWidget::backToMenu, this,
          &MainWindow::showMainMenu);
  connect(snakeWidget, &SnakeWidget::backToMenu, this,
          &MainWindow::showMainMenu);
  // // Добавляем главный экран и экраны игр в QStackedWidget

  stackedWidget->addWidget(tetrisWidget);
  stackedWidget->addWidget(snakeWidget);
  // stackedWidget->addWidget(new RacingWidget(this));

  setCentralWidget(stackedWidget);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::showTetris() {
  stackedWidget->setCurrentIndex(1);  // Показать виджет Тетриса
}

void MainWindow::showSnake() {
  this->resize(625, 323);
  stackedWidget->setCurrentIndex(2);  // Показать виджет Змейки
}

void MainWindow::showRacing() {
  stackedWidget->setCurrentIndex(3);  // Показать виджет Гонок
}

void MainWindow::showMainMenu() {
  this->resize(409, 277);
  stackedWidget->setCurrentIndex(0);  // Показать главное меню
}
