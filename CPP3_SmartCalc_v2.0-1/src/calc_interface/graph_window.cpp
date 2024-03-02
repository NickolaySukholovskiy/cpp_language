#include "graph_window.h"

graph_window::graph_window(QWidget *parent)
    : QDialog(parent), ui(new Ui::graph_window) {
  ui->setupUi(this);

  connect(ui->pushButton_show_graph, SIGNAL(clicked()), this,
          SLOT(show_graph()));
}

graph_window::~graph_window() { delete ui; }

void graph_window::show_graph() {
  try {
    S21Converter calc_converter;
    S21Converter::MasGraphInputApi input_graph_struct = {
        ui->lineEdit->text().toStdString(), ui->doubleSpinBox_x_min->value(),
        ui->doubleSpinBox_x_max->value()};
    calc_converter.GraphResult(input_graph_struct);
    QVector<double> mas_of_x_points =
        QVector<double>(calc_converter.graph_result.mas_of_x.begin(),
                        calc_converter.graph_result.mas_of_x.end());
    QVector<double> mas_of_y_points =
        QVector<double>(calc_converter.graph_result.mas_of_y.begin(),
                        calc_converter.graph_result.mas_of_y.end());

    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(mas_of_x_points, mas_of_y_points);
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");

    double minY = mas_of_y_points[0], maxY = mas_of_y_points[0];
    for (int i = 1; i < calc_converter.graph_result.number_of_points; i++) {
      if (mas_of_y_points[i] < minY) minY = mas_of_y_points[i];
      if (mas_of_y_points[i] > maxY) maxY = mas_of_y_points[i];
    }

    ui->widget->yAxis->setRange(-20, 20);  // Для оси Oy
    ui->widget->xAxis->setRange(ui->doubleSpinBox_x_min->value(),
                                ui->doubleSpinBox_x_max->value());
    ui->widget->replot();
  } catch (S21CalcException &ex) {
    QString error_msg = QString::fromStdString(ex.get_message());
    QMessageBox::warning(this, "Error", error_msg);
  }
}
