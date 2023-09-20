#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sum, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_ce, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_back, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_start, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_end, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_eq, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_graph, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->cgo_a, SIGNAL(clicked()), this, SLOT(credit()));
  connect(ui->cgo_d, SIGNAL(clicked()), this, SLOT(credit()));
  connect(ui->dgo, SIGNAL(clicked()), this, SLOT(deposit()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label;

  if (ui->result_show->text() == "0") {
    new_label = (button->text());
    if (new_label != '.' && new_label != ')' && new_label != '=' &&
        new_label != 'C' && new_label != '^' && new_label != '*' &&
        new_label != '/' && new_label != "<-" && new_label != "make graph" &&
        new_label != "mod") {
      ui->result_show->setText(new_label);
      check_text();
    }
  } else if (button->text() == "C") {
    on_c();
  } else if (button->text() == "<-") {
    my_back();
  } else if (button->text() == "make graph") {
    my_graph();
  } else if (button->text() == '=') {
    my_magic();
  } else {
    new_label = (ui->result_show->text() + button->text());
    ui->result_show->setText(new_label);
    check_text();
  }
}

void MainWindow::check_text() {
  QString str = ui->result_show->text();

  int flag_start = 0;
  int flag_end = 0;
  int flag_dot = 0;

  for (int i = 0; i != str.size(); i++) {
    if (str[i] == '(') {
      flag_start++;
      on_func();
      on_digit();
      ui->pushButton_x->setEnabled(true);
      on_sumsub();
      off_multdivpow();
      ui->pushButton_eq->setEnabled(false);
      ui->pushButton_graph->setEnabled(false);
    }
    if (str[i] == ')') {
      flag_end++;
      off_digit();
      ui->pushButton_x->setEnabled(false);
      off_func();
      on_sumsub();
      on_multdivpow();
      ui->pushButton_eq->setEnabled(true);
      ui->pushButton_graph->setEnabled(true);
    }
    if (str[i].isDigit() || str[i] == 'x') {
      on_digit();
      ui->pushButton_x->setEnabled(false);
      on_sumsub();
      on_multdivpow();
      off_func();
      ui->pushButton_start->setEnabled(false);
      ui->pushButton_end->setEnabled(true);
      ui->pushButton_eq->setEnabled(true);
      ui->pushButton_graph->setEnabled(true);
      if (str[i] == 'x') {
        off_digit();
      }
      if (str[i].isDigit()) {
        if (flag_dot == 0) {
          ui->pushButton_dot->setEnabled(true);
        } else {
          ui->pushButton_dot->setEnabled(false);
        }
      }
    } else {
      flag_dot = 0;
      ui->pushButton_dot->setEnabled(false);
    }
    if (str[i] == '.') {
      flag_dot = 1;
      ui->pushButton_eq->setEnabled(false);
      ui->pushButton_graph->setEnabled(false);
    }
    if (str[i] == 'n' || str[i] == 's' || str[i] == 'g' || str[i] == 't') {
      off_func();
      off_multdivpow();
      off_digit();
      ui->pushButton_x->setEnabled(false);
      off_sumsub();
      ui->pushButton_start->setEnabled(true);
      ui->pushButton_end->setEnabled(false);
      ui->pushButton_eq->setEnabled(false);
      ui->pushButton_graph->setEnabled(false);
    }
    if (str[i] == '-' || str[i] == '+' || str[i] == '*' || str[i] == '/' ||
        str[i] == '^' || str[i] == 'd') {
      on_func();
      on_digit();
      ui->pushButton_x->setEnabled(true);
      off_multdivpow();
      off_sumsub();
      ui->pushButton_start->setEnabled(true);
      ui->pushButton_end->setEnabled(false);
      ui->pushButton_eq->setEnabled(false);
      ui->pushButton_graph->setEnabled(false);
    }
    if (flag_start <= flag_end) {
      ui->pushButton_end->setEnabled(false);
    }
  }

  if (flag_start != flag_end) {
    ui->pushButton_eq->setEnabled(false);
    ui->pushButton_graph->setEnabled(false);
  }
}

void MainWindow::my_magic() {
  std::string my_str = ui->result_show->text().toStdString();
  double value_x = 0.0;
  QString x_value = ui->value->text();
  bool my_status = true;

  for (int i = 0; my_str[i]; ++i) {
    if (my_str[i] == 'x') {
      value_x = x_value.toDouble(&my_status);
    }
  }

  if (!my_status) {
    ui->result_show->setText("Wrong input X");
  } else {
    s21::Controller polController;
    double result = polController.polish(my_str, value_x);
    if (result == NAN) {
      ui->result_show->setText("nan");
    } else {
      ui->result_show->setText(QString::number(result, 'f', 2));
    }
  }
}

void MainWindow::my_graph() {
  std::string my_str = ui->result_show->text().toStdString();
  int flag_x = 0;
  for (int i = 0; my_str[i]; ++i) {
    if (my_str[i] == 'x') {
      flag_x = 1;
    }
  }
  if (flag_x == 0) {
    ui->result_show->setText("Need input with X");
  } else {
    double h = 0.1;
    bool xBegin_status = true;
    bool xEnd_status = true;
    double xBegin = ui->xBegin_ui->text().toDouble(&xBegin_status);
    double xEnd = ui->xEnd_ui->text().toDouble(&xEnd_status);
    if (xBegin_status == false || xEnd_status == false) {
      ui->graph_str->setText("Wrong input. Please, only digits.");
    } else {
      if (xBegin > xEnd) {
        double temp_x = xBegin;
        xBegin = xEnd;
        xEnd = temp_x;
      }
      ui->widget->clearGraphs();
      ui->widget->yAxis->setRange(1, -1);
      s21::Controller yBeginController;
      double yBegin = yBeginController.polish(my_str, xBegin);
      s21::Controller yEndController;
      double yEnd = yEndController.polish(my_str, xEnd);
      double temp_y = 0.0;
      QVector<double> x, y;
      s21::Controller temp_y_controller;
      for (double X = xBegin; X <= xEnd; X += h) {
        x.push_back(X);
        temp_y = temp_y_controller.polish(my_str, X);
        y.push_back(temp_y);
        if (temp_y < yBegin) {
          yBegin = temp_y;
        } else if (temp_y > yEnd) {
          yEnd = temp_y;
        }
      }

      ui->widget->xAxis->setRange(xBegin, xEnd);
      ui->widget->yAxis->setRange(yBegin, yEnd);
      ui->widget->addGraph();
      ui->widget->graph(0)->addData(x, y);
      ui->widget->replot();
      ui->graph_str->setText(ui->result_show->text());
    }
  }
}

void MainWindow::my_back() {
  QString str = ui->result_show->text();
  if (str.size() == 1) {
    on_c();
  } else if (str[str.size() - 1] == 'n' || str[str.size() - 1] == 's' ||
             str[str.size() - 1] == 'd' || str[str.size() - 1] == 'g') {
    if (str.size() == 2) {
      on_c();
    } else if (str[str.size() - 2] == 'l') {
      str.chop(2);
      ui->result_show->setText(str);
      check_text();
    } else if (str.size() == 3) {
      on_c();
    } else if (str[str.size() - 3] == 's' || str[str.size() - 3] == 'c' ||
               str[str.size() - 3] == 't' || str[str.size() - 3] == 'm' ||
               str[str.size() - 3] == 'l') {
      if (str[str.size() - 4] != 'a') {
        str.chop(3);
        ui->result_show->setText(str);
        check_text();
      } else {
        if (str.size() == 4) {
          on_c();
        } else {
          str.chop(4);
          ui->result_show->setText(str);
          check_text();
        }
      }
    }
  } else if (str[str.size() - 1] == 't') {
    if (str.size() == 4) {
      on_c();
    } else {
      str.chop(4);
      ui->result_show->setText(str);
      check_text();
    }
  } else {
    str.chop(1);
    ui->result_show->setText(str);
    check_text();
  }
}

void MainWindow::off_func() {
  ui->pushButton_sqrt->setEnabled(false);
  ui->pushButton_log->setEnabled(false);
  ui->pushButton_ln->setEnabled(false);
  ui->pushButton_sin->setEnabled(false);
  ui->pushButton_cos->setEnabled(false);
  ui->pushButton_tan->setEnabled(false);
  ui->pushButton_asin->setEnabled(false);
  ui->pushButton_acos->setEnabled(false);
  ui->pushButton_atan->setEnabled(false);
}

void MainWindow::on_func() {
  ui->pushButton_sqrt->setEnabled(true);
  ui->pushButton_log->setEnabled(true);
  ui->pushButton_ln->setEnabled(true);
  ui->pushButton_sin->setEnabled(true);
  ui->pushButton_cos->setEnabled(true);
  ui->pushButton_tan->setEnabled(true);
  ui->pushButton_asin->setEnabled(true);
  ui->pushButton_acos->setEnabled(true);
  ui->pushButton_atan->setEnabled(true);
}

void MainWindow::off_digit() {
  ui->pushButton_0->setEnabled(false);
  ui->pushButton_1->setEnabled(false);
  ui->pushButton_2->setEnabled(false);
  ui->pushButton_3->setEnabled(false);
  ui->pushButton_4->setEnabled(false);
  ui->pushButton_5->setEnabled(false);
  ui->pushButton_6->setEnabled(false);
  ui->pushButton_7->setEnabled(false);
  ui->pushButton_8->setEnabled(false);
  ui->pushButton_9->setEnabled(false);
}

void MainWindow::on_digit() {
  ui->pushButton_0->setEnabled(true);
  ui->pushButton_1->setEnabled(true);
  ui->pushButton_2->setEnabled(true);
  ui->pushButton_3->setEnabled(true);
  ui->pushButton_4->setEnabled(true);
  ui->pushButton_5->setEnabled(true);
  ui->pushButton_6->setEnabled(true);
  ui->pushButton_7->setEnabled(true);
  ui->pushButton_8->setEnabled(true);
  ui->pushButton_9->setEnabled(true);
}

void MainWindow::off_sumsub() {
  ui->pushButton_sum->setEnabled(false);
  ui->pushButton_sub->setEnabled(false);
}

void MainWindow::on_sumsub() {
  ui->pushButton_sum->setEnabled(true);
  ui->pushButton_sub->setEnabled(true);
}

void MainWindow::off_multdivpow() {
  ui->pushButton_mod->setEnabled(false);
  ui->pushButton_mult->setEnabled(false);
  ui->pushButton_div->setEnabled(false);
  ui->pushButton_pow->setEnabled(false);
}

void MainWindow::on_multdivpow() {
  ui->pushButton_mod->setEnabled(true);
  ui->pushButton_mult->setEnabled(true);
  ui->pushButton_div->setEnabled(true);
  ui->pushButton_pow->setEnabled(true);
}

void MainWindow::on_c() {
  ui->result_show->setText("0");
  on_digit();
  on_func();
  off_multdivpow();
  on_sumsub();
  ui->pushButton_start->setEnabled(true);
  ui->pushButton_end->setEnabled(false);
  ui->pushButton_eq->setEnabled(false);
  ui->pushButton_x->setEnabled(true);
  ui->pushButton_graph->setEnabled(false);
}

void MainWindow::credit() {
  bool rate_status = true;
  bool amount_status = true;
  bool years_status = true;
  double rate = ui->c_rate->text().toDouble(&rate_status);
  double amount = ui->c_amount->text().toDouble(&amount_status);
  double years = ui->c_years->text().toDouble(&years_status);

  if (rate_status == false || amount_status == false || years_status == false) {
    ui->c_mpay->setText("Please, only digits!");
    ui->c_opay->setText("Please, only digits!");
    ui->c_tpay->setText("Please, only digits!");
  } else {
    QPushButton *button = (QPushButton *)sender();
    int month = years * 12;
    if (button->text() == "CALCULATE THE ANNUITY CREDIT!") {
      double mrate = rate / (100 * 12);
      double my_pow = pow((1 + mrate), month);
      double mpay = amount * ((mrate * my_pow) / (my_pow - 1));
      double tpay = mpay * month;
      double opay = tpay - amount;
      ui->c_mpay->setText(QString::number(mpay, 'f', 2));
      ui->c_opay->setText(QString::number(opay, 'f', 2));
      ui->c_tpay->setText(QString::number(tpay, 'f', 2));
    } else if (button->text() == "CALCULATE THE DIFFERENTIATED CREDIT!") {
      double mpay = amount / month;
      double mpay_over = 0.0;
      double amount_remain = amount;
      double mpay_start = 0.0;
      double mpay_end = 0.0;
      double tpay = 0.0;
      for (int i = 0; i < month; i++) {
        mpay_over = mpay + (amount_remain * rate / 100 * 365 / 12 / 365);
        tpay = tpay + mpay_over;
        if (i == 0) {
          mpay_end = mpay_over;
        } else {
          mpay_start = mpay_over;
        }
        amount_remain = amount_remain - mpay;
      }
      mpay_over = tpay - amount;
      QString mpay_st = QString::number(mpay_start, 'f', 2);
      QString mpay_en = QString::number(mpay_end, 'f', 2);
      ui->c_mpay->setText(mpay_st + " - " + mpay_en);
      ui->c_opay->setText(QString::number(mpay_over, 'f', 2));
      ui->c_tpay->setText(QString::number(tpay, 'f', 2));
    }
  }
}

void MainWindow::deposit() {
  bool rate_status = true;
  bool amount_status = true;
  bool years_status = true;
  bool tax_status = true;
  bool fpay_status = true;
  bool addlist_status = true;
  bool dellist_status = true;
  int capi = 3;

  double rate = ui->d_rate->text().toDouble(&rate_status);
  double amount = ui->d_amount->text().toDouble(&amount_status);
  double years = ui->d_years->text().toDouble(&years_status);
  double tax = ui->d_tax->text().toDouble(&tax_status);
  double fpay = ui->d_fpay->text().toDouble(&fpay_status);
  double addlist = 0.0;
  double dellist = 0.0;
  if (ui->d_capi->text() == "yes") {
    capi = 1;
  } else if (ui->d_capi->text() == "no") {
    capi = 0;
  }
  int j = 0;
  QString str = ui->d_add->text();
  for (int i = 0; i < str.size(); i++) {
    if (i != 0) {
      if (str[i] != ',' || str[i + 1] != ' ') {
        addlist_status = false;
        break;
      } else {
        i = i + 2;
      }
    }
    j = 0;
    for (; i + j < str.size() && str[i + j] != ','; j++) {
    }
    addlist = addlist + str.mid(i, j).toDouble(&addlist_status);
    i = i + j - 1;
    if (addlist_status == false) {
      break;
    }
  }
  QString str2 = ui->d_del->text();
  for (int i = 0; i < str2.size(); i++) {
    if (i != 0) {
      if (str2[i] != ',' || str2[i + 1] != ' ') {
        dellist_status = false;
        break;
      } else {
        i = i + 2;
      }
    }
    j = 0;
    for (; i + j < str2.size() && str2[i + j] != ','; j++) {
    }
    dellist = dellist + str2.mid(i, j).toDouble(&dellist_status);
    i = i + j - 1;
    if (dellist_status == false) {
      break;
    }
  }
  if (rate < 0 || amount < 0 || years < 0 || tax < 0 || fpay < 0) {
    rate_status = false;
  } else if (addlist < 0 || dellist < 0) {
    addlist_status = false;
  }
  if (rate_status == false || amount_status == false || years_status == false ||
      tax_status == false || fpay_status == false) {
    ui->d_opay->setText(
        "Please, only positive digits: rate, amount, years, tax");
    ui->d_ttax->setText(
        "Please, only positive digits: rate, amount, years, tax");
    ui->d_tpay->setText(
        "Please, only positive digits: rate, amount, years, tax");
  } else if (addlist_status == false || dellist_status == false) {
    ui->d_opay->setText("Wrong input add list or remove list");
    ui->d_ttax->setText("Wrong input add list or remove list");
    ui->d_tpay->setText("Wrong input add list or remove list");
  } else if (capi == 3) {
    ui->d_opay->setText("Wrong input of capitalization");
    ui->d_ttax->setText("Wrong input of capitalization");
    ui->d_tpay->setText("Wrong input of capitalization");
  } else {
    amount = amount + addlist - dellist;
    double tpay = 0.0;
    double opay = 0.0;
    double ptax = 0.0;
    double ttax = 0.0;
    if (capi == 0) {
      opay = (amount * rate * years) / 100;
      tpay = amount;
    } else {
      tpay = (amount * pow((1 + rate / 100 / 12), years * 12));
      opay = tpay - amount;
    }
    if (opay / years > 75000) {
      ptax = (opay / years - 75000) * tax / 100;
    }
    if (ptax * (years - static_cast<int>(years)) > 75000 &&
        years != static_cast<int>(years)) {
      ttax = ((ptax * (years - static_cast<int>(years))) - 75000) * tax / 100;
    }
    ttax = ttax + (ptax * static_cast<int>(years));
    opay = opay - ttax;
    ui->d_opay->setText(QString::number(opay, 'f', 2));
    ui->d_ttax->setText(QString::number(ttax, 'f', 2));
    ui->d_tpay->setText(QString::number(tpay, 'f', 2));
  }
}
