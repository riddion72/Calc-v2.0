#include "controller.h"

namespace s21 {

double calculate_example(std::string input, double xValue) {
  S21CalCoolAtions example(input);
  return example.calculate(input, xValue);
}

std::vector<std::vector<double>> calculate_graph(double xMin, double xMax,
                                                 double yMin, double yMax,
                                                 unsigned points,
                                                 std::string input) {
  S21CalCoolAtions graph(input);
  return graph.calculate_graf(std::make_pair(xMin, xMax),
                              std::make_pair(yMin, yMax), points, input);
}

std::vector<std::vector<std::string>> calculate_credit(creditInput input) {
  return credit(input);
}

std::vector<double> calculate_deposit(depositInput input) {
  return deposit(input);
}

}  // namespace s21
