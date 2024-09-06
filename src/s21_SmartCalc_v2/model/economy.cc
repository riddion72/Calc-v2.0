#include "economy.h"

namespace s21 {

std::vector<std::vector<std::string>> credit(creditInput input) {
  std::vector<std::vector<std::string>> vOutput(
      5, std::vector<std::string>(input.mounth));
  double remainingDebt = input.sum;
  double procentMonth = 0;
  double creditMonth = 0;
  double currentPay = 0;
  double vResult = 0;
  double vInterestRate = input.interest / 1200;
  if ((input.interest == 0) || (input.mounth == 0) || (input.sum == 0)) {
    throw std::invalid_argument("Не коректно введены данные кредитки");
  }
  if (!input.type) {
    vResult = input.sum *
              (vInterestRate * pow(1 + vInterestRate, input.mounth)) /
              (pow(1 + vInterestRate, input.mounth) - 1);
  } else {
    vResult = input.sum / input.mounth;
  }
  for (int row = 0; row < input.mounth; row++) {
    procentMonth = remainingDebt * vInterestRate;
    if (!input.type) {
      currentPay = vResult;
      creditMonth = vResult - procentMonth;
    } else {
      currentPay = vResult + procentMonth;
      creditMonth = vResult;
    }
    vOutput[1][row] = std::to_string(currentPay);
    vOutput[2][row] = std::to_string(procentMonth);
    vOutput[3][row] = std::to_string(creditMonth);
    remainingDebt = remainingDebt - creditMonth;
    vOutput[4][row] = std::to_string(remainingDebt);
  }
  return vOutput;
}

std::vector<double> deposit(depositInput input) {
  std::vector<double> vOutput(3);
  double vInterestPerPeriod = 0;
  double vInterest = input.interest / 1200;
  double vTaxSale = 0;
  double vInterestPerYear = 0;
  double vInterestAtTheBegin = 0;
  double vNDFL = 0.13;
  double vTaxAmount = 0;
  double vDeposit = input.sum;
  double vInterestCharges = 0;
  if (input.tax > 0) vTaxSale = 10000 * input.tax;
  for (int i = 1; i <= input.mounth; i++) {
    if ((input.addPay > 0) && !(i % input.addPay)) {
      vDeposit = vDeposit + input.addSum;
    }
    if ((input.snyatie > 0) && !(i % input.snyatie)) {
      vDeposit = vDeposit - input.withdrawals;
    }
    vInterestCharges = vInterestCharges + (vDeposit * vInterest);
    vInterestPerPeriod = vInterestPerPeriod + (vDeposit * vInterest);
    if (input.Capitalization && !(i % input.periodPays)) {
      vDeposit = vDeposit + vInterestPerPeriod;
      vInterestPerPeriod = 0;
    }
    if (!(i % 12)) {
      vInterestPerYear = vInterestCharges - vInterestAtTheBegin;
      if ((vInterestPerYear > vTaxSale)) {
        double vYearTax = ((vInterestPerYear - vTaxSale) * vNDFL);
        vTaxAmount = vTaxAmount + vYearTax;
        if (input.Capitalization) vDeposit = vDeposit - vYearTax;
        vInterestPerYear = vInterestPerYear - vYearTax;
      }
      vInterestAtTheBegin = vInterestPerYear;
    }
  }
  std::pair<double, double> vRemainder = calc_tax_remainder(
      input.mounth, vInterestCharges, vTaxSale, vTaxAmount, vInterestPerYear,
      vInterestAtTheBegin, vDeposit, input.Capitalization);
  if (std::isnan(vInterestCharges) || std::isinf(vInterestCharges) ||
      std::isnan(vRemainder.first) || std::isinf(vRemainder.first) ||
      std::isnan(vRemainder.second) || std::isinf(vRemainder.second) ||
      vRemainder.second < 0)
    throw std::invalid_argument("Не коректно введены данные для расчета");
  vOutput[0] = vInterestCharges;
  vOutput[1] = vRemainder.first;
  vOutput[2] = vRemainder.second;
  return vOutput;
}

std::pair<double, double> calc_tax_remainder(int mounth, double interestCharges,
                                             double taxSale, double taxAmount,
                                             double interestPerYear,
                                             double interestAtTheBegin,
                                             double deposit,
                                             int capitalization) {
  if ((mounth < 12) && (interestCharges > taxSale)) {
    taxAmount = ((interestCharges - taxSale) * 0.13);
  } else {
    interestPerYear = interestCharges - interestAtTheBegin;
    if ((interestPerYear > taxSale)) {
      double vYearTax = ((interestPerYear - taxSale) * 0.13);
      taxAmount = taxAmount + vYearTax;
      if (capitalization) deposit = deposit - vYearTax;
    }
  }
  return std::make_pair(taxAmount, deposit);
}

}  // namespace s21
