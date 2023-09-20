#include "CalcController.h"

double s21::Controller::polish(std::string &a, double x) {
  std::string result(a.length() * 3, 'R');
  int j = 0;
  s21::Model aModel;
  for (int i = 0; a[i]; i++) {
    if (a[i] == '.' || aModel.is_digit(a[i]) == 1 || a[i] == 'x') {
      result[j] = a[i];
    } else {
      result[j] = ' ';
      j++;
      if (a[i] == 'a') {
        if (a[i + 1] == 'c') {
          result[j] = 'C';
          i = i + 3;
        } else if (a[i + 1] == 's') {
          result[j] = 'S';
          i = i + 3;
        } else if (a[i + 1] == 't') {
          result[j] = 'T';
          i = i + 3;
        }
      } else if (i == 0 || a[i - 1] != 'a') {
        if (a[i] == 'c' && a[i + 1] == 'o') {
          result[j] = 'c';
          i = i + 2;
        } else if (a[i] == 's' && a[i + 1] == 'i') {
          result[j] = 's';
          i = i + 2;
        } else if (a[i] == 't' && a[i + 1] == 'a') {
          result[j] = 't';
          i = i + 2;
        } else if (a[i] == 's' && a[i + 1] == 'q') {
          result[j] = 'q';
          i = i + 3;
        } else if (a[i] == 'l' && a[i + 1] == 'n') {
          result[j] = 'n';
          i = i + 1;
        } else if (a[i] == 'l' && a[i + 1] == 'o') {
          result[j] = 'l';
          i = i + 2;
        } else if (a[i] == 'm' && a[i + 1] == 'o') {
          result[j] = '%';
          i = i + 2;
        } else if (a[i] == '+' && (a[i - 1] == '(' || i == 0)) {
          result[j] = '#';
        } else if (a[i] == '-' && (a[i - 1] == '(' || i == 0)) {
          result[j] = '~';
        } else {
          result[j] = a[i];
        }
      }
      j++;
      result[j] = ' ';
    }
    j++;
  }
  result[j] = ' ';
  result.erase(result.find_first_of('R'));
  s21::Model magicModel;
  double value = magicModel.magic_of_polish(result, x);
  if (std::isnan(value)) {
    value = NAN;
  }
  return value;
}
