#include "contribution_calc.h"

#include "ui_contribution_calc.h"

Contribution_calc::Contribution_calc(QWidget *parent)
    : QDialog(parent), ui(new Ui::Contribution_calc) {
  ui->setupUi(this);
  withdrawal_flag = 0;
  replenishment_flag = 0;
}

Contribution_calc::~Contribution_calc() { delete ui; }

void Contribution_calc::on_pushButton_count_clicked() {
  S21Converter calc_converter;
  S21Converter::ContributionCalcInputApi input_contribution_struct;

  input_contribution_struct.ammount = ui->doubleSpinBox_ammount->value();
  input_contribution_struct.percent = ui->doubleSpinBox_percent->value();
  input_contribution_struct.months = ui->spinBox_month->value();
  input_contribution_struct.taxes = ui->doubleSpinBox_taxes->value();
  input_contribution_struct.capitalization_of_interest =
      ui->checkBox_capitalization->isChecked();
  qInfo() << ui->checkBox_capitalization->isChecked();

  if (ui->comboBox_replenishment_pereodicity_of_payment->currentIndex() == 0) {
    input_contribution_struct.pereodicity_of_payments =
        input_contribution_struct.months;
  } else if (ui->comboBox_replenishment_pereodicity_of_payment
                 ->currentIndex() == 5) {
    input_contribution_struct.pereodicity_of_payments = 6;
  } else if (ui->comboBox_replenishment_pereodicity_of_payment
                 ->currentIndex() == 6) {
    input_contribution_struct.pereodicity_of_payments = 12;
  } else {
    input_contribution_struct.pereodicity_of_payments =
        ui->comboBox_replenishment_pereodicity_of_payment->currentIndex();
  }

  calc_converter.ContributionCalcResult(input_contribution_struct);

  ui->lineEdit_earned_ammount->setText(QString::number(
      calc_converter.contribution_result.output_ammount, 'f', 2));
  ui->lineEdit_taxe_ammount->setText(QString::number(
      calc_converter.contribution_result.taxes_ammount, 'f', 2));
}
