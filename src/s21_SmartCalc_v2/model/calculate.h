#ifndef __S21_SMARTCLC_V2_MODEL_CALCULATE_H__
#define __S21_SMARTCLC_V2_MODEL_CALCULATE_H__

#include <cmath>
#include <cstring>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

namespace s21 {

typedef struct nodeStack {
  std::pair<std::string, int> operate;
  double value;
} nodeS;

class S21CalCoolAtions {
 public:
  S21CalCoolAtions(){};
  S21CalCoolAtions(std::string infix);
  S21CalCoolAtions(const S21CalCoolAtions& other);
  ~S21CalCoolAtions(){};

  /// @brief Функция производит подсчет по ПН
  /// @param infix  входная строка с инфиксной записью
  /// @param xValue  значение переменной Х
  /// @return результат вычисления
  double calculate(std::string infix, double xValue);

  /// @brief Функция производит подсчет точек графика
  /// @param xRange границы области определения
  /// @param yRange границы области значений
  /// @param pAmount кол-во точек для вычисления
  /// @param infix строка с выражением
  /// @return массив координат точек
  std::vector<std::vector<double>> calculate_graf(
      std::pair<double, double> xRange, std::pair<double, double> yRange,
      unsigned pAmount, std::string infix);

 private:
  void validation_(std::string infix);
  double calculation_(double xValue);
  int case_number_(int i);
  int case_function_(int i);
  void case_close_braket_();
  void case_simple_operator_(int i, bool binory);
  int case_operator_(int i, bool binory);
  void case_pow_(bool binory);
  void end_notation_();
  void calculate_single_();
  void calculate_binory_();
  int check_ans_(double value) const noexcept;
  void reverse_stack_();
  std::string inPut_;
  std::stack<nodeS> operators_;
  std::stack<nodeS> pNotation_;
};

}  // namespace s21

#endif  //  __S21_SMARTCLC_V2_MODEL_CALCULATE_H__
