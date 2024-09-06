#include "../model/calculate.h"
#include "../model/economy.h"
#include "gtest/gtest.h"

TEST(single, numeric1) {
  std::string infix = "7";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_DOUBLE_EQ(semple.calculate(infix, 0), 7);
}

TEST(single, numeric2) {
  std::string infix = "(1)";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_DOUBLE_EQ(semple.calculate(infix, 0), 1);
}

TEST(single, numeric3) {
  std::string infix = "x";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_DOUBLE_EQ(semple.calculate(infix, 7), 7);
}

TEST(single, numeric4) {
  std::string infix = "()";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(single, numeric5) {
  std::string infix = "-5";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_DOUBLE_EQ(semple.calculate(infix, 7), -5);
}

TEST(single, numeric6) {
  std::string infix = "-.5";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_DOUBLE_EQ(semple.calculate(infix, 7), -.5);
}

TEST(single, numeric7) {
  std::string infix = "-x";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_DOUBLE_EQ(semple.calculate(infix, 7), -7);
}

TEST(single, numeric8) {
  std::string infix = "+x";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_DOUBLE_EQ(semple.calculate(infix, 7), 7);
}

TEST(single, numeric9) {
  std::string infix = "+5";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_DOUBLE_EQ(semple.calculate(infix, 7), 5);
}

TEST(single, numeric10) {
  std::string infix = "+.5";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_DOUBLE_EQ(semple.calculate(infix, 7), .5);
}

TEST(single, numeric11) {
  std::string infix = "+()5";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(single, unare1) {
  std::string infix = "sin()";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(single, unare2) {
  std::string infix = "cos()";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(single, unare3) {
  std::string infix = "tan(.)";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(single, unare4) {
  std::string infix = "acos(-)";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(single, unare5) {
  std::string infix = "acin()";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(single, unare6) {
  std::string infix = "+(.)1";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(single, unare7) {
  std::string infix = "---1";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_DOUBLE_EQ(semple.calculate(infix, 7), -1);
}

TEST(binori, calc1) {
  std::string infix = "3+7";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_DOUBLE_EQ(semple.calculate(infix, 7), 10);
}

TEST(binori, calc2) {
  std::string infix = "3*2";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_DOUBLE_EQ(semple.calculate(infix, 7), 6);
}

TEST(binori, calc3) {
  std::string infix = "4/4";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_DOUBLE_EQ(semple.calculate(infix, 7), 1);
}

TEST(binori, calc4) {
  std::string infix = "12-2";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_DOUBLE_EQ(semple.calculate(infix, 7), 10);
}

TEST(binori, calc5) {
  std::string infix = "2mod2";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_DOUBLE_EQ(semple.calculate(infix, 7), 0);
}

TEST(binori, calc6) {
  std::string infix = "2^2";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_DOUBLE_EQ(semple.calculate(infix, 7), 4);
}

TEST(binori, calc7) {
  std::string infix = "2+(2)";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_DOUBLE_EQ(semple.calculate(infix, 7), 4);
}

TEST(binori, calc8) {
  std::string infix = "2--2";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_DOUBLE_EQ(semple.calculate(infix, 7), 4);
}

TEST(some_case, other1) {
  std::string infix = "2(-2)";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other2) {
  std::string infix = "4/0";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other3) {
  std::string infix = "4/x";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other4) {
  std::string infix = "mo";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other5) {
  std::string infix = "2 - 2";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other6) {
  std::string infix = "()()";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other7) {
  std::string infix = "ln-2";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other8) {
  std::string infix = "sin(9";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other9) {
  std::string infix = "tnn2";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other10) {
  std::string infix = "*5";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other11) {
  std::string infix = "/2";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other12) {
  std::string infix = "^2";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other13) {
  std::string infix = "2^";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other14) {
  std::string infix = "2/";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other15) {
  std::string infix = "2+";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other16) {
  std::string infix = "2*";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other17) {
  std::string infix = "2(-2)";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other18) {
  std::string infix = "2(2)";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other19) {
  std::string infix = "2mod";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other20) {
  std::string infix = "mod2";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other21) {
  std::string infix = "acos";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other22) {
  std::string infix = "3mod0";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other23) {
  std::string infix = "sqrt-1";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other24) {
  std::string infix = "(-1)^.5";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other25) {
  std::string infix = "(.)(.)";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other26) {
  std::string infix = "()*()";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other27) {
  std::string infix = "./.";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other28) {
  std::string infix = ")))8(((";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other29) {
  std::string infix = "..0";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other30) {
  std::string infix = "5cos(1)";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other31) {
  std::string infix = "x(56)";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other32) {
  std::string infix = "x(5**6)";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other33) {
  std::string infix =
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other34) {
  std::string infix =
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other35) {
  std::string infix = "START_TEST(calc_49){";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other36) {
  std::string infix = "\n\t\0";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(some_case, other37) {
  std::string infix = "sin-ln";
  s21::S21CalCoolAtions semple(infix);
  ASSERT_ANY_THROW(semple.calculate(infix, 0));
}

TEST(credit, test_1) {
  s21::creditInput cond;
  std::vector<std::vector<std::string>> ckeck(5, std::vector<std::string>(1));
  std::vector<std::vector<std::string>> ans(5, std::vector<std::string>(12));
  ckeck[1][0] = "10831";
  ckeck[2][0] = "1500";
  ckeck[3][0] = "9311";
  ckeck[4][0] = "110669";
  cond.sum = 120000;
  cond.interest = 15;
  cond.mounth = 12;
  cond.type = 0;
  ans = credit(cond);
  ASSERT_NEAR(stod(ans[1][0]), stod(ckeck[1][0]), stod(ckeck[1][0]) / 20);
  ASSERT_NEAR(stod(ans[2][0]), stod(ckeck[2][0]), stod(ckeck[2][0]) / 20);
  ASSERT_NEAR(stod(ans[3][0]), stod(ckeck[3][0]), stod(ckeck[3][0]) / 20);
  ASSERT_NEAR(stod(ans[4][0]), stod(ckeck[4][0]), stod(ckeck[4][0]) / 20);
}

TEST(credit, test_2) {
  s21::creditInput cond;
  std::vector<std::vector<std::string>> ckeck(5, std::vector<std::string>(1));
  std::vector<std::vector<std::string>> ans(5, std::vector<std::string>(12));
  ckeck[1][0] = "11500";
  ckeck[2][0] = "1500";
  ckeck[3][0] = "10000";
  ckeck[4][0] = "110000";
  cond.sum = 120000;
  cond.interest = 15;
  cond.mounth = 12;
  cond.type = 1;
  ans = credit(cond);
  ASSERT_NEAR(stod(ans[1][0]), stod(ckeck[1][0]), stod(ckeck[1][0]) / 20);
  ASSERT_NEAR(stod(ans[2][0]), stod(ckeck[2][0]), stod(ckeck[2][0]) / 20);
  ASSERT_NEAR(stod(ans[3][0]), stod(ckeck[3][0]), stod(ckeck[3][0]) / 20);
  ASSERT_NEAR(stod(ans[4][0]), stod(ckeck[4][0]), stod(ckeck[4][0]) / 20);
}

TEST(credit, test_3) {
  s21::creditInput cond;
  std::vector<std::vector<std::string>> ans(5, std::vector<std::string>(12));
  cond.sum = 0;
  cond.interest = 1;
  cond.mounth = 0;
  cond.type = 1;
  ASSERT_ANY_THROW(credit(cond));
}

TEST(credit, test_4) {
  s21::creditInput cond;
  std::vector<std::vector<std::string>> ans(5, std::vector<std::string>(12));
  cond.sum = 1;
  cond.interest = 0;
  cond.mounth = 1;
  cond.type = 0;
  ASSERT_ANY_THROW(credit(cond));
}

TEST(deposit, test_1) {
  s21::depositInput cond;
  std::vector<double> ans(3);
  cond.sum = 100000;
  cond.mounth = 12;
  cond.interest = 10;
  cond.periodPays = 1;
  cond.Capitalization = 0;
  cond.addPay = 0;
  cond.addSum = 0;
  cond.snyatie = 0;
  cond.withdrawals = 0;
  cond.tax = 12;

  ans = deposit(cond);

  ASSERT_NEAR(ans[0], 10000.04, 500);
  ASSERT_NEAR(ans[1], 0, 1);
  ASSERT_NEAR(ans[2], 100000, 500);
}

TEST(deposit, test_2) {
  s21::depositInput cond;
  std::vector<double> ans(3);
  cond.sum = 100000;
  cond.mounth = 12;
  cond.interest = 10;
  cond.periodPays = 1;
  cond.Capitalization = 1;
  cond.addPay = 0;
  cond.snyatie = 0;
  cond.tax = 12;

  ans = deposit(cond);

  ASSERT_NEAR(ans[0], 10471.37, 500);
  ASSERT_NEAR(ans[1], 0, 1);
  ASSERT_NEAR(ans[2], 110471.37, 500);
}

TEST(deposit, test_3) {
  s21::depositInput cond;
  std::vector<double> ans(3);
  cond.sum = 1000000;
  cond.mounth = 20;
  cond.interest = 30;
  cond.periodPays = 3;
  cond.Capitalization = 1;
  cond.addPay = 1;
  cond.addSum = 100;
  cond.snyatie = 1;
  cond.withdrawals = 10;
  cond.tax = 12;

  ans = deposit(cond);

  ASSERT_NEAR(ans[0], 638671.28, 25000);
  ASSERT_NEAR(ans[1], 51827.27, 1000);
  ASSERT_NEAR(ans[2], 1566844.01, 80000);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
