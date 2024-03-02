#ifndef GRAPH_WINDOW_H
#define GRAPH_WINDOW_H

#include <QDialog>
#include <QMessageBox>

#include "../back/api.h"
#include "qcustomplot.h"
#include "ui_graph_window.h"

namespace Ui {
class graph_window;
}

class graph_window : public QDialog {
  Q_OBJECT

 public:
  explicit graph_window(QWidget *parent = nullptr);
  ~graph_window();

 private slots:
  void show_graph();

 private:
  Ui::graph_window *ui;
};

#endif  // GRAPH_WINDOW_H
