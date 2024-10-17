#include "snakewidget.h"
using namespace s21;
SnakeWidget::SnakeWidget(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::SnakeWidget),
      gameTimer(new QTimer(this)),
      elapsedTimer(new QElapsedTimer()),
      level(0),
      start(0) {
  ui->setupUi(this);
  setFocusPolicy(Qt::StrongFocus);
  gameModel = new SnakeModel(this);
  ui->FieldWidget->setLayout(new QVBoxLayout());
  ui->FieldWidget->layout()->addWidget(gameModel);
  setWindowTitle("Snake");
  connect(ui->backButton, &QPushButton::clicked, this,
          &SnakeWidget::backToMenu);
  fastMode = 0;
  connect(gameTimer, &QTimer::timeout, gameModel, &SnakeModel::updateGame);
  connect(gameTimer, &QTimer::timeout, this, &SnakeWidget::inWindow);
  connect(gameModel, &SnakeModel::gameStatusChanged, this,
          &SnakeWidget::updateGameTimer);
  seconds_for_timer = gameModel->getTime();
  ui->FieldWidget->resize(SNAKE_EDGE * X_FIELD + 19, SNAKE_EDGE * Y_FIELD + 16);
  high_score = 0;
  openFile();
  ui->background->resize(491, 264);
}
void SnakeWidget::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter painter(this);
  painter.setBrush(Qt::black);
  painter.drawRect(0, 23, width(), height());

  painter.setBrush(Qt::green);
  QVector<QPoint> snake = gameModel->getSnake();

  for (const QPoint &point : snake) {
    painter.drawRect(point.x() * SNAKE_EDGE, point.y() * SNAKE_EDGE, SNAKE_EDGE,
                     SNAKE_EDGE);
  }
  painter.setBrush(Qt::red);
  QPoint apple = gameModel->getApple();
  painter.drawRect(apple.x() * SNAKE_EDGE, apple.y() * SNAKE_EDGE, SNAKE_EDGE,
                   SNAKE_EDGE);
}
SnakeWidget::~SnakeWidget() { delete ui; }

void SnakeWidget::keyPressEvent(QKeyEvent *event) {
  if (!start) {
    start = 1;
    gameTimer->start(seconds_for_timer);
    elapsedTimer->start();
  }
  if (event->key() == Qt::Key_W || event->key() == Qt::Key_Up) {
    gameModel->changeDirection(UP);
    if (event->isAutoRepeat()) fastMode = 1;
  } else if (event->key() == Qt::Key_S || event->key() == Qt::Key_Down) {
    gameModel->changeDirection(DOWN);
    if (event->isAutoRepeat()) fastMode = 1;
  } else if (event->key() == Qt::Key_Right || event->key() == Qt::Key_D) {
    gameModel->changeDirection(RIGHT);
    if (event->isAutoRepeat()) fastMode = 1;
  } else if (event->key() == Qt::Key_Left || event->key() == Qt::Key_A) {
    gameModel->changeDirection(LEFT);
    if (event->isAutoRepeat()) fastMode = 1;
  } else if (event->key() == Qt::Key_Escape || event->key() == Qt::Key_Q)
    gameModel->changeStatus(END);
  else if (event->key() == Qt::Key_P)
    gameModel->changeStatus(STOP);
  else if (event->key() == Qt::Key_F) {
    gameModel->changeDirection('f');
    if (event->isAutoRepeat()) fastMode = 1;
  }
}

void SnakeWidget::updateGameTimer() {
  int status = gameModel->getStatus();

  if (status == STOP) {
    gameTimer->stop();
  } else if (status == END) {
    gameTimer->stop();
  } else if (fastMode) {
    int elapsed = elapsedTimer->elapsed();
    int remaining = gameTimer->interval() - elapsed;
    if (remaining > 10) {
      if (gameTimer->isActive()) {
        gameTimer->stop();
      }
      gameTimer->setInterval(seconds_for_timer * 0.6);
      gameTimer->start(remaining);
    } else {
      gameTimer->start(seconds_for_timer * 0.6);
    }
    elapsedTimer->start();
  } else {
    gameTimer->start(seconds_for_timer);
  }
  checkEnd();
}
void SnakeWidget::keyReleaseEvent(QKeyEvent *event) {
  if (event->isAutoRepeat()) {
    return;
  }

  if (event->key() == Qt::Key_W || event->key() == Qt::Key_Up ||
      event->key() == Qt::Key_S || event->key() == Qt::Key_Down ||
      event->key() == Qt::Key_Right || event->key() == Qt::Key_D ||
      event->key() == Qt::Key_Left || event->key() == Qt::Key_A ||
      event->key() == Qt::Key_F) {
    fastMode = 0;
  }
}

void SnakeWidget::inWindow() {
  QString score = QString::number(gameModel->getScore());
  ui->score_label->setText(score);
  if (gameModel->getScore() <= 50) {
    if (gameModel->getScore() % 5 == 0 && gameModel->getScore() / 5 > level) {
      level++;
      seconds_for_timer -= 20;
      gameTimer->setInterval(seconds_for_timer);
    }
    QString qlevel = QString::number(level);
    ui->level_label->setText(qlevel);
  }

  QString appDir = QCoreApplication::applicationDirPath();
  QDir dir(appDir);
  dir.cd("../../../../../../High_score");
  QString filePath = dir.absoluteFilePath("high_score.txt");

  QFile qfile_out(filePath);
  if (!qfile_out.open(QIODevice::WriteOnly | QIODevice::Text)) {
    qDebug() << "Failed to open the file for reading";
    ui->high_score_label->setText(QString::number(gameModel->getScore()));
  } else {
    QTextStream out(&qfile_out);
      // qDebug() << filePath << gameTimer;
    if (high_score < gameModel->getScore()) {
      QTextStream out(&qfile_out);
      out << gameModel->getScore();
      ui->high_score_label->setText(QString::number(gameModel->getScore()));
    }

    qfile_out.close();
  }
}
void SnakeWidget::openFile() {
  QString appDir = QCoreApplication::applicationDirPath();
  QDir dir(appDir);
  dir.cd("../../../../../../High_score");
  QString filePath = dir.absoluteFilePath("high_score.txt");

  QFile qfile_out(filePath);
  QFile qfile(filePath);
  if (!qfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "Failed to open the file for reading";
    ui->high_score_label->setText(QString::number(gameModel->getScore()));
  } else {
    QTextStream in(&qfile);
    while (!in.atEnd()) {
      QString line = in.readLine();
      ui->high_score_label->setText(line);
      high_score = line.toInt();
      ui->high_score_label->setText(QString::number(high_score));
    }
    qfile.close();
  }
}
void SnakeWidget::checkEnd() {
  if (gameModel->getStatus() == END) {
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setText("Unluck");
    msgBox.setWindowTitle("YOU LOSE");
    msgBox.exec();
  } else if (gameModel->getStatus() == VICTORY) {
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText("Good job");
    msgBox.setWindowTitle("YOU WIN!");
    msgBox.exec();
  }
}
