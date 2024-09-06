#ifndef __S21_SMARTCLC_V2_CONTROLLER_CONTROLLER_H__
#define __S21_SMARTCLC_V2_CONTROLLER_CONTROLLER_H__

#include "../model/calculate.h"
#include "../model/economy.h"

namespace s21 {
/// @brief вызывает вункцию вычисления выражения
/// @param input строка с выражением
/// @param xValue значение переменной Х
/// @return результат вычисления
double calculate_example(std::string input, double xValue);

/// @brief вызывает функцию вычисления координат точек графика
/// @param xMin левая граница области определения
/// @param xMax правая граница области определения
/// @param yMin нижняя граница области значений
/// @param yMax верхняя граница области значений
/// @param points кол-во точек для вычисления
/// @param input строка с выражением
/// @return массив координат точек
std::vector<std::vector<double>> calculate_graph(double xMin, double xMax,
                                                 double yMin, double yMax,
                                                 unsigned points,
                                                 std::string input);

/// @brief вызывает функцию вычисления кредита
/// @param input структура с данными для расчета кредита
/// @return двумерный масив строк с данными платежей по кредиту
std::vector<std::vector<std::string>> calculate_credit(creditInput input);

/// @brief вызывает функцию вычисления депозита
/// @param input структура с данными для расчета депозитного вклада
/// @return масив с данными депозита
std::vector<double> calculate_deposit(depositInput input);

}  // namespace s21

#endif  //  __S21_SMARTCLC_V2_CONTROLLER_CONTROLLER_H__
