#include "s21_calc.h"

S21Calc::S21Calc() {}

S21Calc::~S21Calc() {}

void S21Calc::FromInfixToPostfix_(std::string infix_str) {
  this->x_flag_ = kFAILURE;
  if (infix_str.size() > 255 || infix_str.size() == 0) {
    throw S21CalcException(ExceptionType::ERR_3);
  }
  std::stack<char> func_stack;
  std::string::iterator it_inf_str = infix_str.begin();

  while (it_inf_str != infix_str.end()) {
    if (IsDigit_(*it_inf_str) == kSUCCESS || *it_inf_str == 'x' ||
        *it_inf_str == '.') {
      GetNumFromStr_(it_inf_str);
    } else {
      if (*it_inf_str == '-') {
        if (it_inf_str == infix_str.begin()) {
          *it_inf_str = '~';
        } else {
          if (*(it_inf_str - 1) == '(') {
            *it_inf_str = '~';
          }
        }
      }
      GetOperatorFromStr_(func_stack, it_inf_str);
    }
  }

  while (!func_stack.empty()) {
    if (func_stack.top() == '(') {
      throw S21CalcException(ExceptionType::ERR_1);
    } else {
      this->postfix_str_ += func_stack.top();
    }
    func_stack.pop();
  }
}

void S21Calc::FromPostfixToResult_() {
  std::stack<double> num_stack;
  std::string::iterator postfix_it = this->postfix_str_.begin();
  while (postfix_it != this->postfix_str_.end()) {
    if (IsDigit_(*postfix_it) == kSUCCESS || *postfix_it == 'x') {
      num_stack.push(GetNumFromPostfixStr_(postfix_it));
    } else if (*postfix_it == ' ') {
      postfix_it += 1;
    } else {
      GetOperatorFromPostfixStr_(postfix_it, num_stack);
    }
  }

  if (num_stack.size() != 1) {
    throw S21CalcException(ExceptionType::ERR_1);
  } else {
    this->result_value_ = num_stack.top();
  }
}

void S21Calc::set_string(std::string infix_str) {
  FromInfixToPostfix_(infix_str);
}

double S21Calc::GetExpressionResult() {
  FromPostfixToResult_();
  return this->result_value_;
}

MasGraph S21Calc::GetValueForGraph(double min_x, double max_x) {
  MasGraph result_otput;
  if (min_x >= max_x) {
    throw S21CalcException(ExceptionType::ERR_1);
  }

  double h = 0.001;  // шаг измерения
  int number_of_points = (max_x - min_x) / h + 1;
  std::vector<double> vector_of_x(number_of_points),
      vector_of_y(number_of_points, GetExpressionResult());
  int counter = 0;
  if (this->x_flag_ == kSUCCESS) {
    for (double x_value = min_x; x_value < max_x && counter < number_of_points;
         x_value += h) {
      this->x_ = x_value;
      vector_of_x[counter] = x_value;
      vector_of_y[counter] = GetExpressionResult();
      counter++;
    }
  } else {
    for (double x_value = min_x; x_value < max_x && counter < number_of_points;
         x_value += h) {
      vector_of_x[counter] = x_value;
      counter++;
    }
  }
  result_otput.mas_of_x = vector_of_x;
  result_otput.mas_of_y = vector_of_y;
  result_otput.number_of_points = number_of_points;

  return result_otput;
}

CreditCalcStruct S21Calc::AnnuitentFunction(double ammount, double percent,
                                            int months) {
  if (ammount < 0) {
    throw S21CalcException(ExceptionType::ERR_1);
  }
  if (percent < 0) {
    throw S21CalcException(ExceptionType::ERR_1);
  }
  if (months < 1) {
    throw S21CalcException(ExceptionType::ERR_1);
  }
  CreditCalcStruct output_result;
  double interest_rate = percent / 1200;

  output_result.month_payment_min =
      (interest_rate * pow(1 + interest_rate, months)) /
      (pow(1 + interest_rate, months) - 1);
  output_result.month_payment_min *= ammount;
  output_result.gained_percent =
      output_result.month_payment_min * months - ammount;
  output_result.total_ammount = output_result.gained_percent + ammount;

  return output_result;
}

CreditCalcStruct S21Calc::DifferentialFunction(double ammount, double percent,
                                               int months) {
  if (ammount < 0) {
    throw S21CalcException(ExceptionType::ERR_1);
  }
  if (percent < 0) {
    throw S21CalcException(ExceptionType::ERR_1);
  }
  if (months < 1) {
    throw S21CalcException(ExceptionType::ERR_1);
  }

  CreditCalcStruct output_result;
  double month_payment = ammount / months;
  output_result.month_payment_min = month_payment + ammount * percent / 1200;
  output_result.total_ammount = ammount;

  for (int i = 0; i < months; i++) {
    output_result.gained_percent += ammount * percent / 1200;
    output_result.month_payment_max = ammount * percent / 1200 + month_payment;
    ammount -= month_payment;
  }

  output_result.total_ammount += output_result.gained_percent;

  return output_result;
}

ContributionCalcStructOutput S21Calc::ContributionFunction(
    ContributionCalcStructInput input) {
  if (input.ammount < 0 || input.percent < 0 || input.months < 1) {
    throw S21CalcException(ExceptionType::ERR_1);
  }

  ContributionCalcStructOutput output_struct;
  input.taxes /= 100;
  input.percent /= 100;
  double earned_ammout = 0;

  // добавить добавление процентов, если срок не делиться нацело на количество
  // выплат

  if (input.capitalization_of_interest == kSUCCESS) {
    earned_ammout = input.ammount;
    for (int i = 0; i < input.months / input.pereodicity_of_payments; i++) {
      earned_ammout +=
          earned_ammout * input.percent * input.pereodicity_of_payments / 12;
    }
    earned_ammout += input.ammount * input.percent *
                     (input.months % input.pereodicity_of_payments) / 12;

    output_struct.taxes_ammount = earned_ammout * input.taxes;
    output_struct.output_ammount = earned_ammout - output_struct.taxes_ammount;
  } else {
    earned_ammout = input.ammount * input.percent * input.months / 12;
    output_struct.taxes_ammount = earned_ammout * input.taxes;
    output_struct.output_ammount = earned_ammout - output_struct.taxes_ammount;
  }

  return output_struct;
}
