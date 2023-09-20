#ifndef CPP3_SMARTCALC_V2_0_CALCMODEL_H_
#define CPP3_SMARTCALC_V2_0_CALCMODEL_H_

#include <cmath>
#include <iostream>
#include <stack>
#include <string>
namespace s21 {
class Model {
 public:
  Model(){};
  ~Model(){};
  double magic_of_polish(std::string &str, double x);
  int find_priority(char a);
  int is_digit(char a);
  double my_math(double a, double b, char c);
};
}  // namespace s21

#endif  //  CPP3_SMARTCALC_V2_0_CALCMODEL_H_
