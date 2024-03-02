
#include "s21_calc.h"

double S21Calc::GetNumFromPostfixStr_(std::string::iterator &it_postfix) {
  double result = 0;
  bool point_flag = 0;
  int ten = 1;

  while (IsDigit_(*it_postfix) == kSUCCESS || *it_postfix == 'x') {
    if (*it_postfix == 'x') {
      result = this->x_;
    } else {
      if (!point_flag) {
        result = result * 10 + (*it_postfix - '0');
      } else {
        ten *= 10;
        double add_value = *it_postfix - '0';
        add_value /= ten;
        result += add_value;
      }
    }

    it_postfix += 1;

    if (*it_postfix == '.') {
      point_flag = 1;
      it_postfix += 1;
    }
  }

  return result;
}

void S21Calc::GetOperatorFromPostfixStr_(std::string::iterator &it_postfix,
                                         std::stack<double> &num_stack) {
  if (*it_postfix == '-' || *it_postfix == '+') {
    ImplementPlusMinusOperator_(it_postfix, num_stack);
  } else if (*it_postfix == '/' || *it_postfix == '*' || *it_postfix == 'm') {
    ImplementDivMulOperator_(it_postfix, num_stack);
  } else if (*it_postfix == '^') {
    ImplementPowOperator_(num_stack);
  } else if (*it_postfix == 's' || *it_postfix == 'c' || *it_postfix == 't' ||
             *it_postfix == 'o' || *it_postfix == 'i' || *it_postfix == 'a' ||
             *it_postfix == 'l' || *it_postfix == 'n' || *it_postfix == 'q') {
    ImplementFunctionOperator_(it_postfix, num_stack);
  } else {
    ImplemntUminusOperator_(num_stack);
  }

  it_postfix += 1;
}

void S21Calc::ImplementPlusMinusOperator_(std::string::iterator &it_postfix,
                                          std::stack<double> &num_stack) {
  double num_1 = 0, num_2 = 0;

  if (num_stack.size() > 1) {
    num_1 = num_stack.top();
    num_stack.pop();
    num_2 = num_stack.top();
    num_stack.pop();

    if (*it_postfix == '-') {
      num_stack.push(num_2 - num_1);
    } else {
      num_stack.push(num_2 + num_1);
    }
  } else {
    throw S21CalcException(ExceptionType::ERR_1);
  }
}

void S21Calc::ImplementDivMulOperator_(std::string::iterator &it_postfix,
                                       std::stack<double> &num_stack) {
  double num_1 = 0, num_2 = 0;

  if (num_stack.size() > 1) {
    num_1 = num_stack.top();
    num_stack.pop();
    num_2 = num_stack.top();
    num_stack.pop();

    if (*it_postfix == '*') {
      num_stack.push(num_2 * num_1);
    } else if (*it_postfix == '/') {
      if (num_1 == 0) {
        throw S21CalcException(ExceptionType::ERR_2);
      } else {
        num_stack.push(num_2 / num_1);
      }
    } else {
      if (num_1 == 0) {
        throw S21CalcException(ExceptionType::ERR_2);
      } else {
        num_stack.push(fmod(num_2, num_1));
      }
    }
  } else {
    throw S21CalcException(ExceptionType::ERR_1);
  }
}

void S21Calc::ImplementPowOperator_(std::stack<double> &num_stack) {
  double num_1 = 0, num_2 = 0;

  if (num_stack.size() > 1) {
    num_1 = num_stack.top();
    num_stack.pop();
    num_2 = num_stack.top();
    num_stack.pop();

    if (num_1 > 0 && num_1 < 1 && num_2 < 0) {
      throw S21CalcException(ExceptionType::ERR_2);
    }

    num_stack.push(pow(num_2, num_1));
  } else {
    throw S21CalcException(ExceptionType::ERR_1);
  }
}

void S21Calc::ImplementFunctionOperator_(std::string::iterator &it_postfix,
                                         std::stack<double> &num_stack) {
  double num_1 = 0, result = 0;

  if (num_stack.size() > 0) {
    num_1 = num_stack.top();
    num_stack.pop();

    if (*it_postfix == 's') {
      num_stack.push(sin(num_1));
    } else if (*it_postfix == 'c') {
      num_stack.push(cos(num_1));
    } else if (*it_postfix == 't') {
      num_stack.push(tan(num_1));
    } else if (*it_postfix == 'o') {
      num_stack.push(acos(num_1));
    } else if (*it_postfix == 'i') {
      num_stack.push(asin(num_1));
    } else if (*it_postfix == 'a') {
      num_stack.push(atan(num_1));
    } else if (*it_postfix == 'q') {
      if (num_1 < 0) {
        throw S21CalcException(ExceptionType::ERR_2);
      } else {
        num_stack.push(sqrt(num_1));
      }
    } else if (*it_postfix == 'l' || *it_postfix == 'n') {
      if (num_1 <= 0) {
        throw S21CalcException(ExceptionType::ERR_1);
      } else {
        result = *it_postfix == 'l' ? log10(num_1) : log(num_1);
        num_stack.push(result);
      }
    }
  } else {
    throw S21CalcException(ExceptionType::ERR_1);
  }
}

void S21Calc::ImplemntUminusOperator_(std::stack<double> &num_stack) {
  if (num_stack.size() > 0) {
    double num_1 = num_stack.top();
    num_stack.pop();
    num_stack.push(num_1 * -1);
  } else {
    throw S21CalcException(ExceptionType::ERR_1);
  }
}