#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_10, &QPushButton::clicked, this,
          &MainWindow::digits_numbers);
  connect(ui->pushButton_1, &QPushButton::clicked, this,
          &MainWindow::digits_numbers);
  connect(ui->pushButton_2, &QPushButton::clicked, this,
          &MainWindow::digits_numbers);
  connect(ui->pushButton_3, &QPushButton::clicked, this,
          &MainWindow::digits_numbers);
  connect(ui->pushButton_4, &QPushButton::clicked, this,
          &MainWindow::digits_numbers);
  connect(ui->pushButton_5, &QPushButton::clicked, this,
          &MainWindow::digits_numbers);
  connect(ui->pushButton_6, &QPushButton::clicked, this,
          &MainWindow::digits_numbers);
  connect(ui->pushButton_7, &QPushButton::clicked, this,
          &MainWindow::digits_numbers);
  connect(ui->pushButton_8, &QPushButton::clicked, this,
          &MainWindow::digits_numbers);
  connect(ui->pushButton_9, &QPushButton::clicked, this,
          &MainWindow::digits_numbers);

  connect(ui->pushButton_add, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_open_bracket, SIGNAL(clicked()), this,
          SLOT(operations()));
  connect(ui->pushButton_close_bracket, SIGNAL(clicked()), this,
          SLOT(operations()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_sqr, SIGNAL(clicked()), this, SLOT(operations()));

  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->lineEdit, SIGNAL(returnPressed()), this,
          SLOT(on_pushButton_eqv_clicked()));
  connect(ui->pushButton_credit, SIGNAL(clicked()), this, SLOT(calc_credit()));
  connect(ui->pushButton_deposit, SIGNAL(clicked()), this,
          SLOT(calc_deposit()));
  ui->tableCredit->setColumnWidth(0, 60);
  ui->tableCredit->setColumnWidth(1, 100);
  ui->tableCredit->setColumnWidth(3, 100);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  ui->lineEdit->insert(button->text());
}

void MainWindow::operations() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label;
  new_label = ui->lineEdit->text();

  if (button->text() == "÷" && !(ui->lineEdit->text().endsWith("/"))) {
    new_label += "/";
  } else if (button->text() == "x" && !(ui->lineEdit->text().endsWith("*"))) {
    new_label += "*";
  } else if (button->text() == "+" && !(ui->lineEdit->text().endsWith("+"))) {
    new_label += "+";
  } else if (button->text() == "-" && !(ui->lineEdit->text().endsWith("-"))) {
    new_label += "-";
  } else if (button->text() == "^" && !(ui->lineEdit->text().endsWith("^"))) {
    new_label += "^";
  } else if (button->text() == "mod" &&
             !(ui->lineEdit->text().endsWith("mod"))) {
    new_label += "mod";
  } else if (button->text() == "(") {
    new_label += "(";
  } else if (button->text() == ")") {
    new_label += ")";
  }

  ui->lineEdit->setText(new_label);
}

void MainWindow::functions() {
  QPushButton *button = (QPushButton *)sender();

  ui->lineEdit->insert(button->text() + "(");
}

void MainWindow::on_pushButton_dot_clicked() {
  if (!(ui->lineEdit->text().endsWith(".")))
    ui->lineEdit->setText(ui->lineEdit->text() + ".");
}

void MainWindow::on_pushButton_AC_clicked() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  if (button != nullptr) {
    ui->lineEdit->backspace();
  }
}

void MainWindow::on_pushButton_C_clicked() {
  ui->lineEdit->setText("");
  ui->statusbar->showMessage("");
}

void MainWindow::on_pushButton_sqrt_clicked() { ui->lineEdit->insert("sqrt("); }

void MainWindow::on_pushButton_X_clicked() { ui->lineEdit->insert("x"); }

void MainWindow::on_pushButton_graph_clicked() { build_graf(); }

void MainWindow::build_graf() {
  double vXMin = ui->doubleSpinBox_Xmin->value();
  double vXMax = ui->doubleSpinBox_Xmax->value();
  double vYMin = ui->doubleSpinBox_Ymin->value();
  double vYMax = ui->doubleSpinBox_Ymax->value();
  const std::string errorMessage = "";
  QVector<double> x, y;
  std::vector<std::vector<double>> answer;
  if (ui->lineEdit->text() != "") {
    try {
      answer = s21::calculate_graph(vXMin, vXMax, vYMin, vYMax,
                                    ui->spinBox_points->value(),
                                    ui->lineEdit->text().toStdString());
      for (int i = 0; i < ui->spinBox_points->value(); i++) {
        x.push_back(answer[0][i]);
        y.push_back(answer[1][i]);
      }
    } catch (std::exception const &errorMessage) {
      ui->statusbar->showMessage(
          "ОШИБКА: возможно " + QString::fromStdString(errorMessage.what()),
          3000);
    }
    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x, y);
    if (ui->comboBox_2->currentIndex()) {
      ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
      ui->widget->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);
    } else {
      ui->widget->graph(0)->setLineStyle(QCPGraph::lsLine);
    }
    ui->widget->xAxis->setRange(vXMin, vXMax);
    ui->widget->yAxis->setRange(vYMin, vYMax);
    ui->widget->replot();
    ui->widget->setInteraction(QCP::iRangeZoom, true);
    ui->widget->setInteraction(QCP::iRangeDrag, true);
  }
}

void MainWindow::calc_credit() {
  double vOverpayment = 0;
  s21::creditInput vConditions = {0};
  vConditions.sum = ui->doubleSpinBox_credit_summ->value();
  vConditions.mounth = ui->spinBox_number_of_mouth->value();
  vConditions.interest = ui->doubleSpinBox_interest_rate->value();
  vConditions.type = ui->comboBox->currentIndex();
  ui->tableCredit->setColumnCount(5);
  std::vector<std::vector<std::string>> vAnswer(
      5, std::vector<std::string>(vConditions.mounth));
  ui->label_overpayment_monthly_payment->clear();
  ui->label_overpayment->clear();
  ui->label_overpayment_total_payment->clear();
  if (ui->comboBox->currentIndex()) {
    ui->label_8->setText("Платеж в первый месяц");
  } else {
    ui->label_8->setText("Ежемесячный платеж");
  }
  try {
    vAnswer = s21::calculate_credit(vConditions);
    ui->tableCredit->setRowCount(vConditions.mounth);
    ui->label_overpayment_monthly_payment->setText(
        QString::fromStdString(vAnswer[1][0]));
    for (int row = 0; row < vConditions.mounth; row++) {
      vOverpayment = vOverpayment + std::stod(vAnswer[2][row]);
      for (int column = 1; column < 5; column++) {
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setTextAlignment(Qt::AlignRight);
        item->setText(QString::fromStdString(vAnswer[column][row]));
        ui->tableCredit->setItem(row, column, item);
      }
    }
    ui->label_overpayment->setText(QString::number(vOverpayment, 'f', 2));
    ui->label_overpayment_total_payment->setText(
        QString::number((vOverpayment + vConditions.sum), 'f', 2));
    ui->tableCredit->resizeColumnsToContents();
  } catch (...) {
    ui->statusbar->showMessage("Не коректно введены данные для расчета кредита",
                               3000);
  }
}

void MainWindow::calc_deposit() {
  s21::depositInput conditions = {0};
  std::vector<double> vAswer(3);
  conditions.sum = ui->doubleSpinBox_deposit_amount->value();
  conditions.mounth = ui->spinBox_period_of_placement->value();
  conditions.interest = ui->doubleSpinBox_interest_rate_d->value();
  conditions.tax = ui->doubleSpinBox_tax_rate->value();
  conditions.periodPays = period_pays();
  conditions.Capitalization = ui->radioButton_add->isChecked();
  if (ui->combobox_deposit_addpay->currentIndex() == 0) {
    conditions.addPay = 0;
  } else if (ui->combobox_deposit_addpay->currentIndex() == 1) {
    conditions.addPay = 1;
  } else if (ui->combobox_deposit_addpay->currentIndex() == 2) {
    conditions.addPay = 3;
  } else if (ui->combobox_deposit_addpay->currentIndex() == 3) {
    conditions.addPay = 6;
  } else {
    conditions.addPay = 12;
  }
  conditions.addSum = ui->doubleSpinBox_add_sum->value();
  if (ui->combobox_deposit_snyatie->currentIndex() == 0) {
    conditions.snyatie = 0;
  } else if (ui->combobox_deposit_snyatie->currentIndex() == 1) {
    conditions.snyatie = 1;
  } else if (ui->combobox_deposit_snyatie->currentIndex() == 2) {
    conditions.snyatie = 3;
  } else if (ui->combobox_deposit_snyatie->currentIndex() == 3) {
    conditions.snyatie = 6;
  } else {
    conditions.snyatie = 12;
  }
  conditions.withdrawals = ui->doubleSpinBox_withdrawals->value();
  try {
    vAswer = s21::deposit(conditions);
    ui->label_interest_charges->clear();
    ui->label_interest_charges->setText(QString::number(vAswer[0], 'f', 2));
    ui->label_tax_amount->clear();
    ui->label_tax_amount->setText(QString::number(vAswer[1], 'f', 2));
    ui->label_deposit_amount->clear();
    ui->label_deposit_amount->setText(QString::number(vAswer[2], 'f', 2));
  } catch (...) {
    ui->statusbar->showMessage("Не коректно введены данные для расчета вклада",
                               3000);
  }
}

int MainWindow::period_pays() {
  int period = 0;
  if (ui->comboBox_period_pays->currentIndex() == 0) {
    period = ui->spinBox_period_of_placement->value();
  } else if (ui->comboBox_period_pays->currentIndex() == 1) {
    period = 1;
  } else if (ui->comboBox_period_pays->currentIndex() == 2) {
    period = 3;
  } else if (ui->comboBox_period_pays->currentIndex() == 3) {
    period = 6;
  } else {
    period = 12;
  }
  return period;
}

void MainWindow::on_pushButton_eqv_clicked() {
  double vAnswer = 0;
  if (ui->lineEdit->text() != "") {
    try {
      vAnswer = s21::calculate_example(ui->lineEdit->text().toStdString(),
                                       ui->doubleSpinBox_X->value());
      ui->lineEdit->setText("");
      ui->lineEdit->setText(QString::number(vAnswer, 'f', 8));
    } catch (std::exception const &vErrorMessage) {
      ui->statusbar->showMessage(
          "ОШИБКА: возможно " + QString::fromStdString(vErrorMessage.what()),
          3000);
    }
  }
}

void MainWindow::on_lineEdit_textEdited(const QString &arg1) {
  if (arg1.endsWith("=", Qt::CaseInsensitive)) {
    ui->lineEdit->backspace();
    on_pushButton_eqv_clicked();
  }
}
