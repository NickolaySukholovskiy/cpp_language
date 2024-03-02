#ifndef SmartCalc_v2_back_S21CALC_API_H
#define SmartCalc_v2_back_S21CALC_API_H

#include "s21_calc.h"
#include "s21_calc_exception.h"

/**
 * @brief класс-прослойка для калькулятора по модели MVC
 *
 */
class S21Converter {
 public:
  /**
   * @brief Структура входных данных для калькулятора
   *
   */
  struct CalcInputApi {
    std::string input_expression;  // строка-функция из lineEdit
  };

  /**
   * @brief структура выходных данных для калькулятора
   *
   */
  struct CalcOutputApi {
    double calc_result;  // результат, посчитанного выражения
  };

  /**
   * @brief структура входных данных для графика
   *
   */
  struct MasGraphInputApi {
    std::string input_expression;  // строка-функция из lineEdit
    double min_x;  // минимальное значение x на графике
    double max_x;  // максимальное значение x на графике
  };

  /**
   * @brief структура выходных данных для графика
   *
   */
  struct MasGraphOutputApi {
    std::vector<double> mas_of_x;  // вектор точек x для графика
    std::vector<double> mas_of_y;  // вектор точек y для графика
    int number_of_points;  // количество точек в векторе
  };

  /**
   * @brief структура входных данных для кредитного калькулятора
   *
   */
  struct CreditCalcInputApi {
    double ammount;  // сумма кредита
    double percent;  // процент по кредиту в десятичном виде
    int months;  // срок кредита
    int calculator_type;  // тип платежей, 0 — аннуитентный, 1 —
                          // дифференциальный
  };

  /**
   * @brief структура выходных данных для кредитного калькулятора
   *
   */
  struct CreditCalcOutputApi {
    double month_payment_min;  // минимальный месячный платёж при
                               // дифференциальных выплатах/ежемесячный платёж
                               // при аннуитентных функциях
    double month_payment_max;  // максимальный месячный платёж при
                               // дифференциальных выплатах
    double gained_percent;  // сумма полученных процентов
    double total_ammount;  // сумма, которую нужно будет вернуть за весь срок
                           // пользования кредитом
  };

  /**
   * @brief структура входных данных для вкладового калькулятора
   *
   */
  struct ContributionCalcInputApi {
    double ammount;  // сумма вклада
    double percent;  // процент по вкладу в десятичном виде
    int months;    // срок вклада
    double taxes;  // налог в десятичном виде
    bool capitalization_of_interest;  // капитализация процентов(0 — выключена,
                                      // 1 — включена)
    int pereodicity_of_payments;  // переодичность выплат(при включённой
                                  // капитализации процентов)
  };

  /**
   * @brief структура входных данных для вкладового калькулятора
   *
   */
  struct ContributionCalcOutputApi {
    double output_ammount;  // сумма, полученная по закрытие вклада, с вычтеным
                            // налогом
    double taxes_ammount;   // сумма уплоченных налогов
  };

  /**
   * @brief функция-прослойка для вкладового калькулятора
   *
   * @param input структура входных данных для вкладового калькулятора
   */
  void ContributionCalcResult(ContributionCalcInputApi input);

  /**
   * @brief функция-прослойка для графика
   *
   * @param input структура входных данных для графика
   */
  void GraphResult(MasGraphInputApi input);

  /**
   * @brief функция-прослойка для калькулятора
   *
   * @param input структура входных данных для калькулятора
   */
  void CalculatorResult(CalcInputApi input);

  /**
   * @brief функция-прослойка для кредитного калькулятора
   *
   * @param input структура входных данных для кредитного калькулятора
   */
  void CreditCalcResult(CreditCalcInputApi input);

  CalcOutputApi calc_result;  // структура с выходными данными для калькулятора
  MasGraphOutputApi graph_result;  // структура с выходными данными для графика
  CreditCalcOutputApi credit_result;  // структура с выходными данными для
                                      // кредитного калькулятора
  ContributionCalcOutputApi
      contribution_result;  // структура с выходными данными для вкладового
                            // калькулятора

 private:
  S21Calc calculator;
};

#endif