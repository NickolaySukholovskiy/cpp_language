#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QWidget>

#include "ui_mainwindow.h"

// #include "../back/s21_calc.h"
#include "../back/api.h"
#include "contribution_calc.h"
#include "credit_calc.h"
#include "graph_window.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 private slots:
  void GetOperatorNumberFromButton();
  void GetFunctionFromButton();
  void on_pushButton_graph_clicked();
  void on_pushButton_equal_clicked();

  void on_pushButton_delete_clicked();

  void on_pushButton_credit_clicked();

  void on_pushButton_contribution_clicked();

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  int symbol_flag = 0;
};
#endif  // MAINWINDOW_H
