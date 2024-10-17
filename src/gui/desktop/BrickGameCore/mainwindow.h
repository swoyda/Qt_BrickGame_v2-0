#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace s21 {
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showTetris();
    void showSnake();
    void showRacing();
    void showMainMenu();

private:
    Ui::MainWindow *ui;
    QStackedWidget *stackedWidget;
};
}
#endif // MAINWINDOW_H
