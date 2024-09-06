#ifndef __S21_SMARTCLC_V2_MODEL_ECONOMY_H__
#define __S21_SMARTCLC_V2_MODEL_ECONOMY_H__

#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>

namespace s21 {

/// @brief структура с входными данными для раячета кредита
/// @param [in] sum сумма кредита
/// @param [in] mounth количество месяцев для выплаты кредита
/// @param [in] interest процентная ставка по кредиту
/// @param [in] type тип платяжей по кредиту
typedef struct {
  double sum;
  int mounth;
  double interest;
  int type;
} creditInput;

/// @brief структура с входными данными для расчета депозита
/// @param [in] sum сумма депозита
/// @param [in] mounth количество месяцев размещения кредита
/// @param [in] interest процентная ставка по депозиту
/// @param [in] periodPays переодичность выплат процентов по депозиту в месяцах
/// @param [in] Capitalization тип поведения (перевкладывать проценты или
/// снимать)
/// @param [in] addPay переодичность пополнения депозита в месяцах
/// @param [in] addSum сумма пополнения
/// @param [in] snyatie переодичность вывода средств с депозита в месяцах
/// @param [in] withdrawals сумма вывода
typedef struct {
  double sum;
  int mounth;
  double interest;
  double tax;
  int periodPays;
  int Capitalization;
  int addPay;
  double addSum;
  int snyatie;
  double withdrawals;
} depositInput;

/// @brief Функция вычисляет данные кредита
/// @param input Структура с данными для вычисления кредита
/// @return двумерный масив строк с данными платежей по кредиту
std::vector<std::vector<std::string>> credit(creditInput input);

/// @brief Функция вычисляет проценты и налоги для депозитного счета
/// @param input Структура с данными для вычисления процентов по депозиту
/// @return Массив с данными депозита к концу срока
std::vector<double> deposit(depositInput input);

/// @brief Функция вычисляет налог с процентов, начисленых в последний, не
/// полный год
/// @param mounth срок размещения депозита в месяцах
/// @param interestCharges начисленные проценты
/// @param taxSale сумма не дохода не облагаемая налогом
/// @param taxAmount сумма налога
/// @param interestPerYear проценты за текущий год
/// @param interestAtTheBegin проценты за предыдущие года
/// @param deposit сумма на вкладе
/// @param capitalization реинвестировать или выплачивать проценты
/// @return taxAmount и deposit с учетом входных данных
std::pair<double, double> calc_tax_remainder(int mounth, double interestCharges,
                                             double taxSale, double taxAmount,
                                             double interestPerYear,
                                             double interestAtTheBegin,
                                             double deposit,
                                             int capitalization);

}  // namespace s21

#endif  //  __S21_SMARTCLC_V2_MODEL_ECONOMY_H__
