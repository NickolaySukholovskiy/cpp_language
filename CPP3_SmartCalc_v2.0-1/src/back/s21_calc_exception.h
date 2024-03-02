
#ifndef SmartCalc_v2_back_S21CALC_EXCEPTION_H
#define SmartCalc_v2_back_S21CALC_EXCEPTION_H

#include <exception>
#include <iostream>

enum class ExceptionType {
  ERR_1,  // неверный ввод
  ERR_2,  // неверная арифметика
  ERR_3,  // Строка пуста или диннее 255 символов
  ERR_4,  // Оператор не существует
  ERR_5   // Неверная запись числа
};

/**
 * @brief класс-обработчик ошибок для калькулятора
 *
 */
class S21CalcException : public std::exception {
 public:
  /**
   * @brief стандартный конструктор класса, который устанавливает в класс
   * сообщение, которое вернётся пользователю при ошибке
   *
   * @param msg сообщение об ошибке, указанное в функции throw
   */
  S21CalcException(const std::string &msg);

  /**
   * @brief Construct a new S21CalcException object
   *
   * @param error тип ошибки
   */
  S21CalcException(ExceptionType error);

  /**
   * @brief функция возращает сообщение об ошибке
   *
   * @return std::string сообщение об ошибке
   */
  std::string get_message();

 private:
  std::string msg_;  // сообщение, возвращающееся при прерывании программы
};

#endif