#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->pushButton_0, SIGNAL(clicked()), this,
          SLOT(GetOperatorNumberFromButton()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this,
          SLOT(GetOperatorNumberFromButton()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this,
          SLOT(GetOperatorNumberFromButton()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this,
          SLOT(GetOperatorNumberFromButton()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this,
          SLOT(GetOperatorNumberFromButton()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this,
          SLOT(GetOperatorNumberFromButton()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this,
          SLOT(GetOperatorNumberFromButton()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this,
          SLOT(GetOperatorNumberFromButton()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this,
          SLOT(GetOperatorNumberFromButton()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this,
          SLOT(GetOperatorNumberFromButton()));

  connect(ui->pushButton_left_bracket, SIGNAL(clicked()), this,
          SLOT(GetOperatorNumberFromButton()));
  connect(ui->pushButton_right_bracket, SIGNAL(clicked()), this,
          SLOT(GetOperatorNumberFromButton()));

  connect(ui->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(GetOperatorNumberFromButton()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(GetOperatorNumberFromButton()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this,
          SLOT(GetOperatorNumberFromButton()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this,
          SLOT(GetOperatorNumberFromButton()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this,
          SLOT(GetOperatorNumberFromButton()));
  connect(ui->pushButton_point, SIGNAL(clicked()), this,
          SLOT(GetOperatorNumberFromButton()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this,
          SLOT(GetOperatorNumberFromButton()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this,
          SLOT(GetFunctionFromButton()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this,
          SLOT(GetFunctionFromButton()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this,
          SLOT(GetFunctionFromButton()));

  connect(ui->pushButton_sin, SIGNAL(clicked()), this,
          SLOT(GetFunctionFromButton()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this,
          SLOT(GetFunctionFromButton()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this,
          SLOT(GetFunctionFromButton()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this,
          SLOT(GetFunctionFromButton()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this,
          SLOT(GetFunctionFromButton()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this,
          SLOT(GetFunctionFromButton()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::GetOperatorNumberFromButton() {
  if (symbol_flag == 1) {
    ui->lineEdit->setText("");
    symbol_flag = 0;
  }
  QPushButton *button = (QPushButton *)sender();
  ui->lineEdit->setText(ui->lineEdit->text() + button->text());
}

void MainWindow::GetFunctionFromButton() {
  if (symbol_flag == 1) {
    ui->lineEdit->setText("");
    symbol_flag = 0;
  }
  QPushButton *button = (QPushButton *)sender();
  ui->lineEdit->setText(ui->lineEdit->text() + button->text() + '(');
}

void MainWindow::on_pushButton_graph_clicked() {
  graph_window graph;
  graph.setModal(true);
  graph.exec();
}

void MainWindow::on_pushButton_equal_clicked() {
  QString result_str = ui->lineEdit->text();

  try {
    S21Converter calc_converter;
    S21Converter::CalcInputApi input_calc_struct = {result_str.toStdString()};
    calc_converter.CalculatorResult(input_calc_struct);

    S21Converter::CalcOutputApi output_calc_struct = calc_converter.calc_result;
    ui->lineEdit->setText(QString::number(output_calc_struct.calc_result, 'g'));
    this->symbol_flag = 1;
  } catch (S21CalcException &ex) {
    QString error_msg = QString::fromStdString(ex.get_message());
    QMessageBox::warning(this, "Error", error_msg);
  }
}

void MainWindow::on_pushButton_delete_clicked() { ui->lineEdit->setText(""); }

void MainWindow::on_pushButton_credit_clicked() {
  credit_calc calc;
  calc.setModal(true);
  calc.exec();
}

void MainWindow::on_pushButton_contribution_clicked() {
  Contribution_calc calc;
  calc.setModal(true);
  calc.exec();
}
