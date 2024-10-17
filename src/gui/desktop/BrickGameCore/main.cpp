#include <QApplication>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "mainwindow.h"
// #include <QtGui>
using namespace s21;

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  MainWindow *mainWindow = new MainWindow();
  // mainWindow.setWindowTitle("Главное Меню");
  // mainWindow.resize(400, 300);
  mainWindow->show();

  return app.exec();
}
