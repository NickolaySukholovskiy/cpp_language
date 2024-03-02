
#include "s21_calc.h"

bool S21Calc::IsDigit_(char symbol) {
  int output_result = kFAILURE;

  if (symbol >= '0' && symbol <= '9') {
    output_result = kSUCCESS;
  }

  return output_result;
}

void S21Calc::GetNumFromStr_(std::string::iterator &it_str) {
  int flag_number = kFAILURE;

  while (IsDigit_(*it_str) == kSUCCESS) {
    this->postfix_str_ += *it_str;
    it_str += 1;
    flag_number = kSUCCESS;
  }

  if (*it_str == '.') {
    this->postfix_str_ += '.';
    it_str += 1;
    if (IsDigit_(*it_str) == kSUCCESS && flag_number) {
      while (IsDigit_(*it_str) == kSUCCESS) {
        this->postfix_str_ += *it_str;
        it_str += 1;
      }
    } else {
      throw S21CalcException(ExceptionType::ERR_5);
    }
  }
  // скорее всего переделать
  if (*it_str == 'e') {
    this->postfix_str_ += *it_str;
    it_str += 1;
    if (*it_str == '-' || *it_str == '+') {
      this->postfix_str_ += *it_str;
      it_str += 1;
      while (IsDigit_(*it_str)) {
        this->postfix_str_ += *it_str;
        it_str += 1;
      }
    } else {
      throw S21CalcException(ExceptionType::ERR_1);
    }
  }

  // перенести в отдельную функцию
  if (*it_str == 'x') {
    if (!flag_number) {
      this->postfix_str_ += *it_str;
      it_str += 1;
      this->x_flag_ = kSUCCESS;
    } else {
      throw S21CalcException(ExceptionType::ERR_5);
    }
  }
  postfix_str_ += ' ';
}

void S21Calc::GetOperatorFromStr_(std::stack<char> &func_stack,
                                  std::string::iterator &it_str) {
  int priority = -1;

  if (*it_str != '\0') {
    if (*it_str == '(' || *it_str == ')') {
      WorkWithBracket_(func_stack, it_str);
    } else {
      priority = GetOperatorPriorityInStr_(it_str);

      while (!func_stack.empty() &&
             GetOperatorPriorityInStack_(func_stack) >= priority) {
        this->postfix_str_ += func_stack.top();
        func_stack.pop();
      }

      if (CheckFunction_(it_str) == kFAILURE) {
        throw S21CalcException(ExceptionType::ERR_4);
      }

      char symbol = GetPushSymbol_(it_str);
      if (symbol == '0') {
        symbol = *it_str;
      }
      func_stack.push(symbol);
    }
    it_str += 1;
  }
}

bool S21Calc::CheckFunction_(std::string::iterator it_str) {
  bool output_result = kSUCCESS;
  std::string mas_str[] = {"sin(",  "cos(", "tan(", "acos(", "asin(", "atan(",
                           "sqrt(", "ln(",  "log(", "mod",   "+",     "-",
                           "*",     "/",    "^",    "~"};

  for (int i = 0; i < 16; i++) {
    int counter = 0;
    for (int j = 0; j < (int)mas_str[i].size(); j++) {
      if (mas_str[i][j] == *(it_str + j)) {
        counter++;
      } else {
        output_result = kFAILURE;
        break;
      }
    }
    if (counter == (int)mas_str[i].size()) {
      output_result = kSUCCESS;
      break;
    }
    counter = 0;
  }

  return output_result;
}

void S21Calc::WorkWithBracket_(std::stack<char> &func_stack,
                               std::string::iterator &it_str) {
  if (*it_str == '(') {
    func_stack.push('(');
  } else {
    while (!func_stack.empty() && func_stack.top() != '(') {
      this->postfix_str_ += func_stack.top();
      func_stack.pop();
    }
    if (func_stack.empty() || func_stack.top() != '(') {
      throw S21CalcException(ExceptionType::ERR_1);
    } else {
      func_stack.pop();
    }
    if (GetOperatorPriorityInStack_(func_stack) == kPRIORITY_4) {
      this->postfix_str_ += func_stack.top();
      func_stack.pop();
    }
  }
}

int S21Calc::GetOperatorPriorityInStack_(std::stack<char> &func_stack) {
  int output_result = -1;

  if (func_stack.empty()) {
    output_result = -1;
  } else if (func_stack.top() == '-' || func_stack.top() == '+') {
    output_result = kPRIORITY_1;
  } else if (func_stack.top() == '*' || func_stack.top() == '/' ||
             func_stack.top() == 'm') {
    output_result = kPRIORITY_2;
  } else if (func_stack.top() == '^') {
    output_result = kPRIORITY_3;
  } else if (func_stack.top() == 's' || func_stack.top() == 'c' ||
             func_stack.top() == 't' || func_stack.top() == 'o' ||
             func_stack.top() == 'i' || func_stack.top() == 'a' ||
             func_stack.top() == 'l' || func_stack.top() == 'n' ||
             func_stack.top() == 'q') {
    output_result = kPRIORITY_4;
  } else if (func_stack.top() == '~') {
    output_result = kPRIORITY_5;
  }

  return output_result;
}

int S21Calc::GetOperatorPriorityInStr_(std::string::iterator &it_str) {
  int output_result = -1;

  if (*it_str == '-' || *it_str == '+') {
    output_result = kPRIORITY_1;
  } else if (*it_str == '*' || *it_str == '/' || *it_str == 'm') {
    output_result = kPRIORITY_2;
  } else if (*it_str == '^') {
    output_result = kPRIORITY_3;
  } else if (*it_str == '~') {
    output_result = kPRIORITY_5;
  } else {
    output_result = kPRIORITY_4;
  }

  return output_result;
}

char S21Calc::GetPushSymbol_(std::string::iterator &it_str) {
  int output_result = '0';

  if (*it_str == 's') {
    if (*(it_str + 1) == 'i') {
      output_result = 's';
      it_str += 2;
    } else if (*(it_str + 1) == 'q') {
      output_result = 'q';
      it_str += 3;
    }
  } else if (*it_str == 'c') {
    output_result = 'c';
    it_str += 2;
  } else if (*it_str == 't') {
    output_result = 't';
    it_str += 2;
  } else if (*it_str == 'a') {
    if (*(it_str + 1) == 's') {
      output_result = 'i';
    } else if (*(it_str + 1) == 'c') {
      output_result = 'o';
    } else {
      output_result = 'a';
    }
    it_str += 3;
  } else if (*it_str == 'l') {
    if (*(it_str + 1) == 'o') {
      output_result = 'l';
      it_str += 2;
    } else {
      output_result = 'n';
      it_str += 1;
    }
  } else if (*it_str == 'm') {
    output_result = 'm';
    it_str += 2;
  }

  return output_result;
}