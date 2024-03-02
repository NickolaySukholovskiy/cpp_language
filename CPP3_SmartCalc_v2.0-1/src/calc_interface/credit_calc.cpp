#include "credit_calc.h"

credit_calc::credit_calc(QWidget *parent)
    : QDialog(parent), ui(new Ui::credit_calc) {
  ui->setupUi(this);
}

credit_calc::~credit_calc() { delete ui; }

void credit_calc::on_pushButton_x_clicked() {
  S21Converter calc_converter;
  S21Converter::CreditCalcInputApi input_credit_struct = {
      ui->doubleSpinBox_ammount->value(), ui->doubleSpinBox_percent->value(),
      ui->spinBox_months->text().toInt(), 0};

  try {
    if (ui->radioButton_1->isChecked()) {
      calc_converter.CreditCalcResult(input_credit_struct);
      ui->lineEdit_7->setText(QString::number(
          calc_converter.credit_result.month_payment_min, 'f', 2));
    } else {
      input_credit_struct.calculator_type = 1;
      calc_converter.CreditCalcResult(input_credit_struct);
      ui->lineEdit_7->setText(
          QString::number(calc_converter.credit_result.month_payment_min, 'f',
                          2) +
          " - " +
          QString::number(calc_converter.credit_result.month_payment_max, 'f',
                          2));
    }
    ui->lineEdit_8->setText(
        QString::number(calc_converter.credit_result.gained_percent, 'f', 2));
    ui->lineEdit_9->setText(
        QString::number(calc_converter.credit_result.total_ammount, 'f', 2));
  } catch (S21CalcException &ex) {
    QString error_msg = QString::fromStdString(ex.get_message());
    QMessageBox::warning(this, "Error", error_msg);
  }
}
