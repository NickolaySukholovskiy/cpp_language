
#include "api.h"

void S21Converter::CalculatorResult(CalcInputApi input) {
  calculator.set_string(input.input_expression);
  this->calc_result.calc_result = calculator.GetExpressionResult();
}

void S21Converter::GraphResult(MasGraphInputApi input) {
  calculator.set_string(input.input_expression);
  MasGraph graph_output = calculator.GetValueForGraph(input.min_x, input.max_x);
  this->graph_result.mas_of_x = graph_output.mas_of_x;
  this->graph_result.mas_of_y = graph_output.mas_of_y;
  this->graph_result.number_of_points = graph_output.number_of_points;
}

void S21Converter::CreditCalcResult(CreditCalcInputApi input) {
  if (input.calculator_type == 0) {
    CreditCalcStruct credit_output = calculator.AnnuitentFunction(
        input.ammount, input.percent, input.months);
    this->credit_result.month_payment_min = credit_output.month_payment_min;
    this->credit_result.gained_percent = credit_output.gained_percent;
    this->credit_result.total_ammount = credit_output.total_ammount;
  } else if (input.calculator_type == 1) {
    CreditCalcStruct credit_output = calculator.DifferentialFunction(
        input.ammount, input.percent, input.months);
    this->credit_result.month_payment_min = credit_output.month_payment_min;
    this->credit_result.month_payment_max = credit_output.month_payment_max;
    this->credit_result.gained_percent = credit_output.gained_percent;
    this->credit_result.total_ammount = credit_output.total_ammount;
  }
}

void S21Converter::ContributionCalcResult(ContributionCalcInputApi input) {
  ContributionCalcStructInput contribution_input = {
      input.ammount,
      input.percent,
      input.months,
      input.taxes,
      input.capitalization_of_interest,
      input.pereodicity_of_payments};

  ContributionCalcStructOutput contribution_output =
      calculator.ContributionFunction(contribution_input);

  this->contribution_result.output_ammount = contribution_output.output_ammount;
  this->contribution_result.taxes_ammount = contribution_output.taxes_ammount;
}