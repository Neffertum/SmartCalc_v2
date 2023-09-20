#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "../CalcController.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;

 private slots:
  void digits_numbers();
  void check_text();
  void off_func();
  void on_func();
  void off_digit();
  void on_digit();
  void off_sumsub();
  void on_sumsub();
  void off_multdivpow();
  void on_multdivpow();
  void my_magic();
  void my_back();
  void my_graph();
  void on_c();
  void deposit();
  void credit();
};
#endif  // MAINWINDOW_H
