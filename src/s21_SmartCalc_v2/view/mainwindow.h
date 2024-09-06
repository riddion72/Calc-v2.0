#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QtMath>

#include "../controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;

 private slots:
  /// @brief печатает цифру с кнопки в строку
  void digits_numbers();
  /// @brief печатает опеватор в строку
  void operations();
  /// @brief печатает функцию с открывающей скобкой в строку
  void functions();
  /// @brief печатает точку в строку
  void on_pushButton_dot_clicked();
  /// @brief удаляет символ из строки
  void on_pushButton_AC_clicked();
  /// @brief удаляет всё из строки и statusbar
  void on_pushButton_C_clicked();
  /// @brief печатает функцию sqrt с открывающей скобкой в строку
  void on_pushButton_sqrt_clicked();
  /// @brief печатает Х в строку ввода
  void on_pushButton_X_clicked();
  /// @brief запускает функцию построения графика
  void on_pushButton_graph_clicked();
  /// @brief строит график
  void build_graf();
  /// @brief производит подсчет кредита по заданым параметрам
  void calc_credit();
  /// @brief производит подсчет суммы вклада к концу срока
  void calc_deposit();
  /// @brief устанавливает период выплат согласно выбранной опции
  /// @return период выплат в месяцах
  int period_pays();
  /// @brief производит подсчет выражения введённого во входную строку
  void on_pushButton_eqv_clicked();
  /// @brief отслеживает нажатие клавиши "=" на клавиатуре
  void on_lineEdit_textEdited(const QString &arg1);
};
#endif  // MAINWINDOW_H
