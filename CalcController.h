#ifndef CPP3_SMARTCALC_V2_0_CALCCONTROLLER_H_
#define CPP3_SMARTCALC_V2_0_CALCCONTROLLER_H_

#include "CalcModel.h"

namespace s21 {
class Controller {
 public:
  Controller(){};
  ~Controller(){};
  double polish(std::string &str, double x);
};
}  // namespace s21

#endif  //  CPP3_SMARTCALC_V2_0_CALCCONTROLLER_H_
