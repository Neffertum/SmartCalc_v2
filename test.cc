#include <gtest/gtest.h>

#include <cmath>

#include "CalcController.h"

s21::Controller result;

TEST(Testing, Default) {
  double x = 0;
  std::string my_str = "-45.2114+14.0";
  double res = -45.2114 + 14.0;
  double my_res = result.polish(my_str, x);
  EXPECT_NEAR(res, my_res, 1e-7);
}

TEST(Testing, Cos) {
  double x = 235.134;
  std::string my_str = "cos(x)";
  double res = cos(x);
  double my_res = result.polish(my_str, x);
  EXPECT_NEAR(res, my_res, 1e-7);
}

TEST(Testing, Atan) {
  double x = 0;
  std::string my_str = "atan(12)";
  double res = atan(12);
  double my_res = result.polish(my_str, x);
  EXPECT_NEAR(res, my_res, 1e-7);
}

TEST(Testing, Mod) {
  double x = -235.012;
  std::string my_str = "cos(x)+(-124mod124.46)";
  double res = cos(x) + fmod(-124, 124.46);
  double my_res = result.polish(my_str, x);
  EXPECT_NEAR(res, my_res, 1e-7);
}

TEST(Testing, Div) {
  double x = -235.012;
  std::string my_str = "36/0.1244";
  double res = 36 / 0.1244;
  double my_res = result.polish(my_str, x);
  EXPECT_NEAR(res, my_res, 1e-7);
}

TEST(Testing, Ln) {
  double x = 124124.03105;
  std::string my_str = "sin(x)-ln(x)";
  double res = sin(x) - log(x);
  double my_res = result.polish(my_str, x);
  EXPECT_NEAR(res, my_res, 1e-7);
}

TEST(Testing, Sin) {
  double x = 124;
  std::string my_str = "5235.1*sin(5-(124^15.15155))";
  double res = 5235.1 * sin(5 - pow(124, 15.15155));
  double my_res = result.polish(my_str, x);
  EXPECT_NEAR(res, my_res, 1e-7);
}

TEST(Testing, TanLog) {
  double x = 0.21455;
  std::string my_str = "-tan(x)-(-0+log(x))";
  double res = -tan(x) - (-0 + log10(x));
  double my_res = result.polish(my_str, x);
  EXPECT_NEAR(res, my_res, 1e-7);
}

TEST(Testing, SubSum) {
  double x = 0.21455;
  std::string my_str = "+(-14)";
  double res = +(-14);
  double my_res = result.polish(my_str, x);
  EXPECT_NEAR(res, my_res, 1e-7);
}

TEST(Testing, Acos) {
  double x = -13515667.12515;
  std::string my_str = "acos(x)/x";
  double res = acos(x) / x;
  double my_res = result.polish(my_str, x);
  int res_flag = 0;
  int myres_flag = 0;
  if (res == NAN) {
    res_flag = 1;
  }
  if (my_res == NAN) {
    myres_flag = 1;
  }
  EXPECT_EQ(res_flag, myres_flag);
}

TEST(Testing, Asin) {
  double x = 0.21455;
  std::string my_str = "-46-(+266714.241*asin(-0.15))";
  double res = -46 - (+266714.241 * asin(-0.15));
  double my_res = result.polish(my_str, x);
  EXPECT_NEAR(res, my_res, 1e-7);
}

TEST(Testing, X) {
  double x = 257781425.12;
  std::string my_str = "xmodatan(0.12356)";
  double res = fmod(x, atan(0.12356));
  double my_res = result.polish(my_str, x);
  EXPECT_NEAR(res, my_res, 1e-7);
}

TEST(Testing, Mega) {
  double x = 257781425.12;
  std::string my_str = "(x+(136236*x^0.124/(1551-(12356-0.1637458))))";
  double res = (x + (136236 * pow(x, 0.124) / (1551 - (12356 - 0.1637458))));
  double my_res = result.polish(my_str, x);
  EXPECT_NEAR(res, my_res, 1e-7);
}

TEST(Testing, SinCosTan) {
  double x = 257781425.12;
  std::string my_str = "sin(x)-cos(x)*tan(x)";
  double res = sin(x) - cos(x) * tan(x);
  double my_res = result.polish(my_str, x);
  EXPECT_NEAR(res, my_res, 1e-7);
}

TEST(Testing, Log) {
  double x = 0.12516247;
  std::string my_str = "-ln(x)-(-log(x))";
  double res = -log(x) - (-log10(x));
  double my_res = result.polish(my_str, x);
  EXPECT_NEAR(res, my_res, 1e-7);
}

TEST(Testing, ManyDefault) {
  double x = 0.12516247;
  std::string my_str = "1513-236263+23626*213592.23264/0.12516";
  double res = 1513 - 236263 + 23626 * 213592.23264 / 0.12516;
  double my_res = result.polish(my_str, x);
  EXPECT_NEAR(res, my_res, 1e-7);
}

TEST(Testing, Sqrt) {
  double x = -125;
  std::string my_str = "sqrt(x)+(+9+155123.2366)";
  double res = sqrt(x) + (9 + 155123.2366);
  double my_res = result.polish(my_str, x);
  int res_flag = 0;
  int myres_flag = 0;
  if (res == NAN) {
    res_flag = 1;
  }
  if (my_res == NAN) {
    myres_flag = 1;
  }
  EXPECT_EQ(res_flag, myres_flag);
}

TEST(Testing, Sqrt2) {
  double x = 125;
  std::string my_str = "sqrt(x)+(+9+155123.2366)";
  double res = sqrt(x) + (9 + 155123.2366);
  double my_res = result.polish(my_str, x);
  EXPECT_NEAR(res, my_res, 1e-7);
}

TEST(Testing, ManySyb) {
  double x = 125;
  std::string my_str = "-(-(-(-(-2346))))";
  double res = -(-(-(-(-2346))));
  double my_res = result.polish(my_str, x);
  EXPECT_NEAR(res, my_res, 1e-7);
}

TEST(Testing, ManySum) {
  double x = 125;
  std::string my_str = "+(+(+(+x)))";
  double res = +(+(+(+x)));
  double my_res = result.polish(my_str, x);
  EXPECT_NEAR(res, my_res, 1e-7);
}

TEST(Testing, SqrtSin) {
  double x = 125;
  std::string my_str = "sqrt(sin(x-31))";
  double res = sqrt(sin(x - 31));
  double my_res = result.polish(my_str, x);
  int res_flag = 0;
  int myres_flag = 0;
  if (res == NAN) {
    res_flag = 1;
  }
  if (my_res == NAN) {
    myres_flag = 1;
  }
  EXPECT_EQ(res_flag, myres_flag);
}

TEST(Testing, SinCosLn) {
  double x = 125;
  std::string my_str = "sin(1)-cos(0)+ln(235)/log(0.124)";
  double res = sin(1) - cos(0) + log(235) / log10(0.124);
  double my_res = result.polish(my_str, x);
  EXPECT_NEAR(res, my_res, 1e-7);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}