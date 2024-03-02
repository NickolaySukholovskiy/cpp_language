#ifndef SmartCalc_v2_back_S21CALC_S21_CALC_H
#define SmartCalc_v2_back_S21CALC_S21_CALC_H

#include <math.h>

#include <iostream>
#include <stack>
#include <vector>

#include "s21_calc_exception.h"

/**
 * @brief сруктура с выходными значениями из кредитной функции для кредитного
 * калькулятора
 *
 */
struct CreditCalcStruct {
  double month_payment_min;
  double month_payment_max;
  double gained_percent;
  double total_ammount;
};

/**
 * @brief структура с входными значениями для вкладового калькулятора
 *
 */
struct ContributionCalcStructInput {
  double ammount;
  double percent;
  int months;
  double taxes;
  bool capitalization_of_interest;
  int pereodicity_of_payments;
};

/**
 * @brief структура с выходными значениями для вкладового калькулятора
 *
 */
struct ContributionCalcStructOutput {
  double output_ammount;
  double taxes_ammount;
};

/**
 * @brief структура выходных значений для графика
 *
 */
struct MasGraph {
  std::vector<double> mas_of_x;
  std::vector<double> mas_of_y;
  int number_of_points;
};

/**
 * @brief класс для работы с функциями калькулятора
 *
 */
class S21Calc {
 public:
  /**
   * @brief стандартный конструктор класса
   *
   */
  S21Calc();

  /**
   * @brief стандартный деструктор класса
   *
   */
  ~S21Calc();

  /**
   * @brief функция задаёт строку-выражение, по которой дальше будет происходить
   * вычисление итогового значения
   *
   * @param infix_str строка в инфиксной записи
   */
  void set_string(std::string infix_str);

  /**
   * @brief функция возвращает значение посчитанного результата
   *
   * @return double результат, посчитанный из данной входной строки
   */
  double GetExpressionResult();

  /**
   * @brief функция подсчитывает множество точек для последующего построения
   * графика
   *
   * @param min_x минимальная граница для x
   * @param max_x максимальная граница для x
   * @return MasGraph
   */
  MasGraph GetValueForGraph(double min_x, double max_x);

  /**
   * @brief функция подсчитывает значения для ануитентного кредитного
   * калькулятора
   *
   * @param ammount сумма кредита
   * @param percent процент по кредиту
   * @param months продолжительность кредита
   * @return CreditCalcStruct структура, возвращающая минимальный и максимальный
   * платёж по кредиту, полученные проценты и общую сумму кредита
   */
  CreditCalcStruct AnnuitentFunction(double ammount, double percent,
                                     int months);

  /**
   * @brief функция подсчитывает значения для дифференциального кредитного
   * калькулятора
   *
   * @param ammount сумма кредита
   * @param percent процент по кредиту
   * @param months продолжительность кредита
   * @return CreditCalcStruct структура, возвращающая минимальный и максимальный
   * платёж по кредиту, полученные проценты и общую сумму кредита
   */
  CreditCalcStruct DifferentialFunction(double ammount, double percent,
                                        int months);

  /**
   * @brief функция подтчитывает значения для вкладового калькулятора
   *
   * @param input
   * @return ContributionCalcStructOutput
   */
  ContributionCalcStructOutput ContributionFunction(
      ContributionCalcStructInput input);

 private:
  /**
   * @brief список приоритетов для обработки операторов в строке-выражении
   *
   */
  enum {
    kPRIORITY_0,  // скобки
    kPRIORITY_1,  // плюс/минус
    kPRIORITY_2,  // умножить/делить
    kPRIORITY_3,  // степень
    kPRIORITY_4,  // тригонометрия/корень
    kPRIORITY_5,  // унарный минус
  };

  /**
   * @brief вспомогательный список для обработки разных флагов
   *
   */
  enum { kFAILURE, kSUCCESS };

  std::string postfix_str_;  // строка в постфиксном значении
  double x_;  // значение x для подсчёта выражения
  double result_value_;  // число, полученное в результате
  bool x_flag_;

  //--------------------------
  // Вспомогательные функции
  //--------------------------
  bool IsDigit_(char symbol);

  //--------------------------
  // Вспомогательные функции FromInfixToPostfix_
  //--------------------------
  void GetNumFromStr_(std::string::iterator &it_str);
  void GetOperatorFromStr_(std::stack<char> &func_stack,
                           std::string::iterator &it_str);
  void WorkWithBracket_(std::stack<char> &func_stack,
                        std::string::iterator &it_str);
  int GetOperatorPriorityInStr_(std::string::iterator &it_str);
  int GetOperatorPriorityInStack_(std::stack<char> &func_stack);
  char GetPushSymbol_(std::string::iterator &it_str);

  //--------------------------
  // Вспомогательные функции FromPostfixToResult_
  //--------------------------
  double GetNumFromPostfixStr_(std::string::iterator &it_postfix);
  void GetOperatorFromPostfixStr_(std::string::iterator &it_postfix,
                                  std::stack<double> &num_stack);

  void ImplementPlusMinusOperator_(std::string::iterator &it_postfix,
                                   std::stack<double> &num_stack);
  void ImplementDivMulOperator_(std::string::iterator &it_postfix,
                                std::stack<double> &num_stack);
  void ImplementPowOperator_(std::stack<double> &num_stack);
  void ImplementFunctionOperator_(std::string::iterator &it_postfix,
                                  std::stack<double> &num_stack);
  void ImplemntUminusOperator_(std::stack<double> &num_stack);
  bool CheckFunction_(std::string::iterator it_str);

  //--------------------------
  // Основные функции
  //--------------------------
  void FromInfixToPostfix_(std::string infix_str);
  void FromPostfixToResult_();
};

#endif