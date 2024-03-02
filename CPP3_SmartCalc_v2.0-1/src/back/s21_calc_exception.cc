
#include "s21_calc_exception.h"

S21CalcException::S21CalcException(const std::string &msg) : msg_(msg) {}

S21CalcException::S21CalcException(ExceptionType error) {
  if (error == ExceptionType::ERR_1) {
    this->msg_ = "Invalid input";
  } else if (error == ExceptionType::ERR_2) {
    this->msg_ = "Invalid arithmetic";
  } else if (error == ExceptionType::ERR_3) {
    this->msg_ = "String is empty or it's size is more than 255 sympols";
  } else if (error == ExceptionType::ERR_4) {
    this->msg_ = "There is no such operator in list";
  } else if (error == ExceptionType::ERR_5) {
    this->msg_ = "Invalid number entry";
  }
}

std::string S21CalcException::get_message() { return this->msg_; }