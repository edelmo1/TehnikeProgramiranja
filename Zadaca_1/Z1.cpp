// TP 2022/2023: Zadaća 1, Zadatak 1
#include <array>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

enum class TretmanNegativnih { IgnorirajZnak, Odbaci, PrijaviGresku };

int MultiplikativniDigitalniKorijen(long long int broj, int B) {

  if (broj < 0) {
    broj = broj * (-1);
  }

  if (B < 2) {
    throw std::domain_error("Neispravna baza");
  }

 long long int proizvod_cifara = 1;
  bool nula = true;
  while (broj != 0) {
    proizvod_cifara *= (broj % B);
    broj = broj / B;
    nula = false;
  }
  
if(nula==false) {
  while (proizvod_cifara > (B - 1)) {

    long long int temp = proizvod_cifara;
    proizvod_cifara = 1;

    while (temp != 0) {
      proizvod_cifara *= (temp % B);
      temp = temp / B;
    }
  }
  return proizvod_cifara;
}
return  0;
}
std::array<std::vector<long long int>, 10>
RazvrstajBrojeve(std::vector<long long int> v, TretmanNegativnih uslov) {

  if (int(uslov) == 2) {
    throw std::domain_error(
        "Nije predvidjeno razvrstavanje negativnih brojeva");
  }
  std::array<std::vector<long long int>, 10> niz;
  int velicina = v.size();
  for (int i = 0; i < velicina; i++) {
    if (v.at(i) < 0) {
      if (int(uslov) == 0) {
        v.at(i) = -1 * v.at(i);
      }
      if (int(uslov) == 1)
        continue;
    }
    int indeks = MultiplikativniDigitalniKorijen(v.at(i), 10);
    niz.at(indeks).push_back(v.at(i));
  }
  return niz;
}

int main() {

  long long int broj;
  std::vector<long long int> v;
  std::cout << "Unesite brojeve (bilo koji ne-broj oznacava kraj): ";
  while (std::cin >> broj ) {
    if (broj < 0) {  //kako je u autotestu realan broj?
      std::cout << "Nije podrzano razvrstavanje negativnih brojeva!"
                << std::endl;
      return 0;
    }
    v.push_back(broj);
  }

  try {
    std::array<std::vector<long long int>, 10> niz;
    niz = RazvrstajBrojeve(v, TretmanNegativnih::IgnorirajZnak);
    std::cout
        << "Rezultati razvrstavanja po multiplikativnom digitalnom korijenu:\n";
    for (int i = 0; i < 10; i++) {
      int vel = niz.at(i).size();
      if (vel == 0)
        continue;
      std::cout << i << ":";
      for (int j = 0; j < vel; j++) {
        std::cout << " " << niz.at(i).at(j);
      }
      std::cout << std::endl;
    }

  } catch (std::domain_error e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
