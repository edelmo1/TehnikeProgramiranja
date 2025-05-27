// TP 2022/2023: Zadaća 3, Zadatak 1
#include <cmath>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>

std::function<double(double)>
LagrangeovaInterpolacija(std::vector<std::pair<double, double>> v) {

  const double EPSILON = 0.000001;
  for (int i = 0; i < v.size(); i++) {
    for (int j = i + 1; j < v.size(); j++) {
      if (std::fabs(v.at(i).first - v.at(j).first) < EPSILON) {
        throw std::domain_error("Neispravni cvorovi");
      }
    }
  }

  return [v](double x) {
    double suma = 0;
    for (int i = 0; i < v.size(); i++) {
      double proizvod = 1;
      for (int j = 0; j < v.size(); j++) {
        if (i == j)
          continue;
        proizvod *= (x - v.at(j).first) / (v.at(i).first - v.at(j).first);
      }
      suma += v.at(i).second * proizvod;
    }
    return suma;
  };
}

std::function<double(double)>
LagrangeovaInterpolacija(std::function<double(double)> f, double x_min,
                         double x_max, double delta) {

  if (x_max - x_min < 0 || delta <= 0)
    throw std::domain_error("Nekorektni parametri");

  std::vector<std::pair<double, double>> v;

  for (int i = 0; i <= (x_max - x_min) / delta; i++) {
    v.push_back({x_min + i * delta, f(x_min + i * delta)});
  }
  auto F = LagrangeovaInterpolacija(v);
  return F;
}

double TEST(double x) { return x * x + std::sin(x) + std::log(x + 1); }

int main() {
  int izbor = 0;
  std::cout << "Odaberite opciju (1 - unos cvorova, 2 - aproksimacija): ";
  std::cin >> izbor;
  if (izbor != 2 && izbor != 1) {
    std::cout << "Neispravan unos!\n";
    return 0;
  }

  try {

    if (izbor == 1) {

      int br_cvorova = 0;
      std::cout << "Unesite broj cvorova: ";
      std::cin >> br_cvorova;
      std::vector<std::pair<double, double>> v(br_cvorova);
      std::cout << "Unesite cvorove kao parove x y: ";
      for (int i = 0; i < br_cvorova; i++) {
        std::cin >> v.at(i).first >> v.at(i).second;
      }
      auto F = LagrangeovaInterpolacija(v);
      for (;;) {

        double arg = 0;
        std::cout << "Unesite argument (ili \"kraj\" za kraj): ";
        if (!(std::cin >> arg) || std::cin.peek() != '\n')
          return 0;
        std::cout << "f(" << arg << ") = " << F(arg);
        if (arg - v.at(0).first < 0 || arg - v.at(br_cvorova - 1).first > 0)
          std::cout << " [ekstrapolacija]";
        std::cout << std::endl;
      }
    } else {

      double x_min = 0, x_max = 0, korak = 0;
      std::cout << "Unesite krajeve intervala i korak: ";
      std::cin >> x_min >> x_max >> korak;
      if (x_min > x_max || korak <= 0)
        throw std::domain_error("Nekorektni parametri");
      std::vector<std::pair<double, double>> v;

      for (int i = 0; i <= (x_max - x_min) / korak; i++) {
        v.push_back({x_min + i * korak, TEST(x_min + i * korak)});
      }
      auto F = TEST;
      auto P = LagrangeovaInterpolacija(TEST, x_min, x_max, korak);
      for (;;) {

        double arg = 0;
        std::cout << "Unesite argument (ili \"kraj\" za kraj): ";
        if (!(std::cin >> arg) || std::cin.peek() != '\n')
          return 0;
        std::cout << "f(" << arg << ") = " << F(arg) << " P(" << arg
                  << ") = " << P(arg);
        if (arg - x_min < 0 || arg - x_max > 0)
          std::cout << " [ekstrapolacija]";
        std::cout << std::endl;
      }
    }
  } catch (std::domain_error e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
