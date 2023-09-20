#include "CalcModel.h"

double s21::Model::magic_of_polish(std::string &str, double x) {
  double res = 0.0;
  std::stack<char> s_stack;
  std::stack<double> v_stack;
  double temp_one = 0.0;
  double temp_two = 0.0;
  int prev_sign = 0;
  int new_sign = 0;
  for (int i = 0; str[i]; i++) {
    if (str[i] == '(') {
      std::string buffer(100, 'R');
      int t = 1;
      int flag = 0;
      for (; flag != 1; t++) {
        if (str[i + t] == '(') {
          flag--;
        } else if (str[i + t] == ')') {
          flag++;
        }
        if (flag != 1) {
          buffer[t - 1] = str[i + t];
        }
      }
      buffer.erase(buffer.find_first_of('R'));
      v_stack.push(s21::Model::magic_of_polish(buffer, x));
      i = i + buffer.length() + 1;
    } else if (s21::Model::is_digit(str[i]) == 1) {
      if (i == 0 || str[i - 1] == ' ') {
        std::string new_digit(50, 'R');
        int j = 0;
        for (; str[i + j] != ' '; j++) {
          new_digit[j] = str[i + j];
        }
        new_digit.erase(new_digit.find_first_of('R'));
        v_stack.push(std::stod(new_digit));
      }
    } else if (str[i] == 'x') {
      v_stack.push(x);
    } else if (s21::Model::find_priority(str[i]) > 0) {
      new_sign = s21::Model::find_priority(str[i]);
      while (new_sign <= prev_sign && s_stack.empty() == false) {
        temp_two = v_stack.top();
        v_stack.pop();
        if (s21::Model::find_priority(s_stack.top()) == 4 ||
            s21::Model::find_priority(s_stack.top()) == 5) {
          temp_one = 0.0;
        } else {
          temp_one = v_stack.top();
          v_stack.pop();
        }
        v_stack.push(s21::Model::my_math(temp_one, temp_two, s_stack.top()));
        s_stack.pop();
        if (!s_stack.empty()) {
          prev_sign = s21::Model::find_priority(s_stack.top());
        }
      }
      if (new_sign > prev_sign || s_stack.empty()) {
        s_stack.push(str[i]);
        prev_sign = s21::Model::find_priority(str[i]);
      }
    }
  }
  while (s_stack.empty() == false) {
    temp_two = v_stack.top();
    v_stack.pop();
    if (s21::Model::find_priority(s_stack.top()) == 4 ||
        s21::Model::find_priority(s_stack.top()) == 5) {
      temp_one = 0.0;
    } else {
      temp_one = v_stack.top();
      v_stack.pop();
    }
    v_stack.push(s21::Model::my_math(temp_one, temp_two, s_stack.top()));
    s_stack.pop();
  }
  res = v_stack.top();
  v_stack.pop();
  return res;
}

int s21::Model::find_priority(char a) {
  int flag = 0;
  if (a == '+' || a == '-') {
    flag = 1;
  } else if (a == '*' || a == '/' || a == '%') {
    flag = 2;
  } else if (a == '^') {
    flag = 3;
  } else if (a == '~' || a == '#') {
    flag = 4;
  } else if (a == 'c' || a == 'C' || a == 's' || a == 'S' || a == 't' ||
             a == 'T' || a == 'l' || a == 'n' || a == 'q') {
    flag = 5;
  }
  return flag;
}

int s21::Model::is_digit(char a) {
  int flag = 0;
  if (a >= '0' && a <= '9') {
    flag = 1;
  }
  return flag;
}

double s21::Model::my_math(double a, double b, char c) {
  double result = 0.0;
  if (c == '+') {
    result = a + b;
  } else if (c == '-') {
    result = a - b;
  } else if (c == '*') {
    result = a * b;
  } else if (c == '/') {
    result = a / b;
  } else if (c == '%') {
    result = fmod(a, b);
  } else if (c == '^') {
    result = pow(a, b);
  } else if (c == '~') {
    result = b * (-1);
  } else if (c == '#') {
    result = b * 1;
  } else if (c == 'c') {
    result = cos(b);
  } else if (c == 'C') {
    result = acos(b);
  } else if (c == 's') {
    result = sin(b);
  } else if (c == 'S') {
    result = asin(b);
  } else if (c == 't') {
    result = tan(b);
  } else if (c == 'T') {
    result = atan(b);
  } else if (c == 'l') {
    result = log10(b);
  } else if (c == 'n') {
    result = log(b);
  } else if (c == 'q') {
    result = sqrt(b);
  }
  return result;
}
