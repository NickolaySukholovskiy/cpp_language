#ifndef CREDIT_CALC_H
#define CREDIT_CALC_H

#include <QDialog>
#include <QMessageBox>

#include "../back/api.h"
#include "ui_credit_calc.h"

namespace Ui {
class credit_calc;
}

class credit_calc : public QDialog {
  Q_OBJECT

 public:
  explicit credit_calc(QWidget *parent = nullptr);
  ~credit_calc();

 private slots:
  void on_pushButton_x_clicked();

 private:
  Ui::credit_calc *ui;
};

#endif  // CREDIT_CALC_H
