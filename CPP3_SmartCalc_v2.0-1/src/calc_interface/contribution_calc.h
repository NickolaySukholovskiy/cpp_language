#ifndef CONTRIBUTION_CALC_H
#define CONTRIBUTION_CALC_H

#include <QDialog>

#include "../back/api.h"

namespace Ui {
class Contribution_calc;
}

class Contribution_calc : public QDialog {
  Q_OBJECT

 public:
  explicit Contribution_calc(QWidget *parent = nullptr);
  ~Contribution_calc();

 private slots:
  void on_pushButton_count_clicked();

 private:
  Ui::Contribution_calc *ui;
  bool withdrawal_flag;
  bool replenishment_flag;
};

#endif  // CONTRIBUTION_CALC_H
