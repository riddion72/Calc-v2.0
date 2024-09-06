#include "calculate.h"

namespace s21 {

S21CalCoolAtions::S21CalCoolAtions(std::string infix) {
  S21CalCoolAtions();
  inPut_ = infix;
}

S21CalCoolAtions::S21CalCoolAtions(const S21CalCoolAtions& other) {
  S21CalCoolAtions(other.inPut_);
  operators_ = other.operators_;
  pNotation_ = other.pNotation_;
}

double S21CalCoolAtions::calculate(std::string infix, double xValue) {
  validation_(infix);
  reverse_stack_();
  return calculation_(xValue);
}

std::vector<std::vector<double>> S21CalCoolAtions::calculate_graf(
    std::pair<double, double> xRange, std::pair<double, double> yRange,
    unsigned pAmount, std::string infix) {
  std::stack<nodeS> vBuffer;
  std::vector<std::vector<double>> vXYOutPut(2, std::vector<double>());
  double vXStep = (xRange.second - xRange.first) / pAmount;
  double vX = xRange.first;
  double vY = 0;
  if ((xRange.second < xRange.first) || (yRange.second < yRange.first)) {
    throw std::invalid_argument(
        "Не коректно введены граници отображения графика");
  }
  validation_(infix);
  reverse_stack_();
  vBuffer = pNotation_;
  for (unsigned i = 0; i < pAmount; i++) {
    try {
      vY = calculation_(vX);
      if (vY >= yRange.first && vY <= yRange.second) {
        vXYOutPut[1].push_back(vY);
        vXYOutPut[0].push_back(vX);
      }
    } catch (std::exception const&) {
      vXYOutPut[1].push_back(NAN);
      vXYOutPut[0].push_back(NAN);
    }
    while (!operators_.empty()) {
      operators_.pop();
    }
    pNotation_ = vBuffer;
    vX += vXStep;
  }
  if (vXYOutPut[0].empty()) {
    throw std::invalid_argument(
        "ни одна из точек не находится в заданной области значений");
  }
  return vXYOutPut;
}

void S21CalCoolAtions::validation_(std::string infix) {
  unsigned int vLength = infix.length();
  bool vBinoryFl = false;
  if (vLength > 300)
    throw std::invalid_argument("превышина максимальная длина строки");
  inPut_ = infix + "\0";
  for (unsigned int i = 0; i < vLength; i++) {
    if ((inPut_[i] >= '0' && inPut_[i] <= '9') ||
        ((inPut_[i] == '.') &&
         (inPut_[i + 1] >= '0' && inPut_[i + 1] <= '9'))) {
      i = case_number_(i);
      vBinoryFl = true;
    } else if (inPut_[i] == '(') {
      operators_.push({{"(", 0}, 0});
      vBinoryFl = false;
    } else if (strchr("sctal", inPut_[i])) {
      i = case_function_(i);
      if (vBinoryFl)
        throw std::invalid_argument("пропущен оператор унарной функции");
      vBinoryFl = false;
    } else if (inPut_[i] == ')') {
      if (!vBinoryFl) throw std::invalid_argument("(поблемма) в скобках");
      case_close_braket_();
      vBinoryFl = true;
    } else if (strchr("+-", inPut_[i])) {
      case_simple_operator_(i, vBinoryFl);
      vBinoryFl = false;
    } else if ((inPut_[i] == 'x') || (inPut_[i] == 'X')) {
      pNotation_.push({{"x", -1}, 0});
      vBinoryFl = true;
    } else if (strchr("*/mod", inPut_[i])) {
      i = case_operator_(i, vBinoryFl);
      vBinoryFl = false;
    } else if (inPut_[i] == '^') {
      case_pow_(vBinoryFl);
      vBinoryFl = false;
    } else {
      throw std::invalid_argument("присутствуют недопустимые символы");
    }
  }
  end_notation_();
}

double S21CalCoolAtions::calculation_(double xValue) {
  while (!pNotation_.empty()) {
    if (pNotation_.top().operate.first == "v") {
      operators_.push(pNotation_.top());
    } else if (pNotation_.top().operate.first == "x") {
      operators_.push(pNotation_.top());
      operators_.top().value = xValue;
    } else if (strchr("sctla~", pNotation_.top().operate.first[0])) {
      calculate_single_();
    } else if (strchr("-+*/m^", pNotation_.top().operate.first[0])) {
      calculate_binory_();
    } else {
      throw std::invalid_argument("что-то пошло не так");
    }
    pNotation_.pop();
  }
  if (operators_.size() > 1) {
    throw std::invalid_argument("введены лишние аргументы");
  } else if (operators_.size() == 0) {
    throw std::invalid_argument("тут нечего счетать?");
  }
  return operators_.top().value;
}

int S21CalCoolAtions::case_number_(int i) {
  double vNum = 0;
  std::size_t vSizeNum = 0;
  vNum = std::stod(&(inPut_[i]),
                   &vSizeNum);  // можнт выкидывать std::invalid_argument
  pNotation_.push({{"v", -1}, vNum});
  return (i + (int)vSizeNum - 1);
}

int S21CalCoolAtions::case_function_(int i) {
  int vIter = i;
  std::string vOperate = "";
  if (!(strncmp("sin", &inPut_[i], 3))) {
    vOperate = "sin";
    vIter += 2;
  } else if (!(strncmp("cos", &inPut_[i], 3))) {
    vOperate = "cos";
    vIter += 2;
  } else if (!(strncmp("tan", &inPut_[i], 3))) {
    vOperate = "tan";
    vIter += 2;
  } else if (!(strncmp("log", &inPut_[i], 3))) {
    vOperate = "log";
    vIter += 2;
  } else if (!(strncmp("sqrt", &inPut_[i], 4))) {
    vOperate = "sqrt";
    vIter += 3;
  } else if (!(strncmp("acos", &inPut_[i], 4))) {
    vOperate = "acos";
    vIter += 3;
  } else if (!(strncmp("asin", &inPut_[i], 4))) {
    vOperate = "asin";
    vIter += 3;
  } else if (!(strncmp("atan", &inPut_[i], 4))) {
    vOperate = "atan";
    vIter += 3;
  } else if (!(strncmp("ln", &inPut_[i], 2))) {
    vOperate = "ln";
    vIter += 1;
  } else {
    throw std::invalid_argument("неправильно задана унарная функция");
  }
  operators_.push({{vOperate, 5}, 0});
  return vIter;
}

void S21CalCoolAtions::case_close_braket_() {
  bool vOpenBraketFind = false;
  while ((!operators_.empty()) && (!vOpenBraketFind)) {
    if (operators_.top().operate.first == "(") {
      vOpenBraketFind = true;
    } else {
      pNotation_.push({operators_.top()});
    }
    operators_.pop();
  }
  if (!vOpenBraketFind)
    throw std::invalid_argument("пропущена открывающая скобка");
}

void S21CalCoolAtions::case_simple_operator_(int i, bool binory) {
  if (binory) {
    std::string vOperator = "";
    vOperator.push_back(inPut_[i]);
    while (!operators_.empty()) {
      if (operators_.top().operate.second > 1) {
        pNotation_.push({operators_.top()});
        operators_.pop();
      } else {
        break;
      }
    }
    operators_.push({{vOperator, 1}, 0});
  } else if (inPut_[i] == '-') {
    operators_.push({{"~", 3}, 0});
  } else if (inPut_[i] != '+') {
    throw std::invalid_argument("пропущен оператор функции (+,-)");
  }
}

int S21CalCoolAtions::case_operator_(int i, bool binory) {
  int vIter = i;
  std::string vOperator = "";
  vOperator.push_back(inPut_[i]);
  if (inPut_[i] == 'm') {
    if (strncmp("mod", &inPut_[i], 3)) {
      throw std::invalid_argument("неправильно задана функция (mod)");
    } else {
      vIter += 2;
    }
  }
  if (!binory)
    throw std::invalid_argument("пропущен оператор функции (*,/,mod)");
  while (!operators_.empty()) {
    if (operators_.top().operate.second > 2) {
      pNotation_.push({operators_.top()});
      operators_.pop();
    } else {
      break;
    }
  }
  operators_.push({{vOperator, 2}, 0});
  return vIter;
}

void S21CalCoolAtions::case_pow_(bool binory) {
  if (binory) {
    while (!operators_.empty()) {
      if (operators_.top().operate.second > 3) {
        pNotation_.push({operators_.top()});
        operators_.pop();
      } else {
        break;
      }
    }
    operators_.push({{"^", 3}, 0});
  } else {
    throw std::invalid_argument(
        "пропущен оператор функции возведения в степень");
  }
}

void S21CalCoolAtions::end_notation_() {
  while (!operators_.empty()) {
    if (operators_.top().operate.first != "(") {
      pNotation_.push({operators_.top()});
      operators_.pop();
    } else {
      throw std::invalid_argument("пропущена закрывающая скобка");
    }
  }
}

void S21CalCoolAtions::calculate_single_() {
  if (!operators_.empty()) {
    if (pNotation_.top().operate.first == "sin") {
      operators_.top().value = sin(operators_.top().value);
    } else if (pNotation_.top().operate.first == "cos") {
      operators_.top().value = cos(operators_.top().value);
    } else if (pNotation_.top().operate.first == "tan") {
      operators_.top().value = tan(operators_.top().value);
    } else if (pNotation_.top().operate.first == "acos") {
      operators_.top().value = acos(operators_.top().value);
    } else if (pNotation_.top().operate.first == "asin") {
      operators_.top().value = asin(operators_.top().value);
    } else if (pNotation_.top().operate.first == "atan") {
      operators_.top().value = atan(operators_.top().value);
    } else if (pNotation_.top().operate.first == "sqrt") {
      operators_.top().value = sqrt(operators_.top().value);
    } else if (pNotation_.top().operate.first == "ln") {
      operators_.top().value = log(operators_.top().value);
    } else if (pNotation_.top().operate.first == "log") {
      operators_.top().value = log10(operators_.top().value);
    } else if (pNotation_.top().operate.first == "~") {
      operators_.top().value = operators_.top().value * -1;
    } else {
      throw std::invalid_argument("что-то пошло не так?");
    }
    if (check_ans_(operators_.top().value))
      throw std::invalid_argument(
          "произошла ошибка при вычеслении унарного оператора");
  } else {
    throw std::invalid_argument("пропущен оператор функции");
  }
}

void S21CalCoolAtions::calculate_binory_() {
  double vValue = 0;
  if (operators_.size() > 1) {
    vValue = operators_.top().value;
    operators_.pop();
    if (pNotation_.top().operate.first == "-") {
      operators_.top().value = operators_.top().value - vValue;
    } else if (pNotation_.top().operate.first == "+") {
      operators_.top().value = operators_.top().value + vValue;
    } else if (pNotation_.top().operate.first == "*") {
      operators_.top().value = operators_.top().value * vValue;
    } else if (pNotation_.top().operate.first == "/") {
      operators_.top().value = operators_.top().value / vValue;
    } else if (pNotation_.top().operate.first == "m") {
      operators_.top().value = fmod(operators_.top().value, vValue);
    } else if (pNotation_.top().operate.first == "^") {
      operators_.top().value = pow(operators_.top().value, vValue);
    } else {
      throw std::invalid_argument("что-то пошло не так?");
    }
    if (check_ans_(operators_.top().value))
      throw std::invalid_argument(
          "произошла ошибка при вычеслении бинарного оператора");
  } else {
    throw std::invalid_argument("пропущен оператор бинарной функции");
  }
}

int S21CalCoolAtions::check_ans_(double value) const noexcept {
  int vError = 0;
  if (std::isnan(value) || std::isinf(value)) vError = 1;
  return vError;
}

void S21CalCoolAtions::reverse_stack_() {
  std::stack<nodeS> vBuffer;
  while (!pNotation_.empty()) {
    vBuffer.push(pNotation_.top());
    pNotation_.pop();
  }
  pNotation_ = vBuffer;
}

}  // namespace s21
