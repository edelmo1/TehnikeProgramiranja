// TP 2022/2023: Zadaća 2, Zadatak 3
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

template <typename Tip1, typename Tip2, typename FunTip1, typename FunTip2>
auto GeneraliziraniMatricniProizvod(std::vector<std::vector<Tip1>> A,
                                    std::vector<std::vector<Tip2>> B, FunTip1 f,
                                    FunTip2 g) {
  typedef decltype(g(A.at(0).at(0), B.at(0).at(0)) +
                   g(A.at(0).at(0), B.at(0).at(0))) PovratniTip;
  // provjera dimenzija

  if (A.size() == 0) {
    std::vector<std::vector<PovratniTip>> M(
        B.size(), std::vector<PovratniTip>(B.at(0).size()));
    return M;
  } else if (B.size() == 0) {
    std::vector<std::vector<PovratniTip>> M(
        A.size(), std::vector<PovratniTip>(A.at(0).size()));
    return M;
  }
  bool greska = false;
  int sirina = A.at(0).size();
  for (int i = 0; i < A.size(); i++) { // da li je grbava
    if (A.at(i).size() != sirina) {
      greska = true;
      break;
    }
  }
  if (greska == true) {
    throw std::domain_error("Matrice nisu saglasne za mnozenje");
  }

  int sirina2 = B.at(0).size();
  for (int i = 0; i < B.size(); i++) { // da li je grbava
    if (B.at(i).size() != sirina2) {
      greska = true;
      break;
    }
  }
  if (greska == true) {
    throw std::domain_error("Matrice nisu saglasne za mnozenje");
  }

  if (sirina != B.size()) {
    throw std::domain_error("Matrice nisu saglasne za mnozenje");
  }

  std::vector<std::vector<PovratniTip>> M(A.size(),
                                          std::vector<PovratniTip>(sirina2));

  for (int i = 0; i < M.size(); i++) {
    for (int j = 0; j < M.at(0).size(); j++) {

      PovratniTip suma = g(A.at(i).at(0), B.at(0).at(j));
      for (int k = 1; k < A.at(i).size(); k++) {
        try {
          suma = f(suma, (g(A.at(i).at(k), B.at(k).at(j))));
        } catch (...) {
          throw std::runtime_error("Neocekivani problemi pri racunanju");
        }
      }
      M.at(i).at(j) = suma;
    }
  }

  return M;
}
int main() {

  int m = 0, n = 0, p = 0;
  std::cout << "Unesite broj redova prve matrice: ";
  std::cin >> m;
  std::cout
      << "Unesite broj kolona prve matrice, ujedno broj redova druge matrice: ";
  std::cin >> n;
  std::cout << "Unesite broj kolona druge matrice: ";
  std::cin >> p;

  std::vector<std::vector<std::string>> A(m, std::vector<std::string>(n));
  std::vector<std::vector<std::string>> B(n, std::vector<std::string>(p));

  std::cout << "\nUnesite elemente prve matrice: ";
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> A.at(i).at(j);
    }
  }

  std::cout << "\nUnesite elemente druge matrice: ";
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < p; j++) {
      std::cin >> B.at(i).at(j);
    }
  }
  try {
    std::vector<std::vector<std::string>> M = GeneraliziraniMatricniProizvod(
        A, B,
        [](std::string s1, std::string s2) {
          s1.push_back('+');
          s1 += s2;
          return s1;
        },
        [](std::string s1, std::string s2) {
          s1.push_back('*');
          s1 += s2;
          return s1;
        });
        
    int sirina = 0;
    for (int i = 0; i < M.size(); i++) {
      if (M.at(0).size() == 0)
        continue;
      for (int j = 0; j < M.at(0).size(); j++) {
        if (M.at(i).at(j).size() > sirina)
          sirina = M.at(i).at(j).size();
      }
    }
    std::cout << "\nMatricni proizvod:\n";
    for (int i = 0; i < M.size(); i++) {
      for (int j = 0; j < M.at(0).size(); j++) {
        std::cout << std::left << std::setw(sirina + 1) << M.at(i).at(j);
      }
      std::cout << std::endl;
    }
  } catch (std::domain_error) {
    std::cout << "GRESKA: Matrice nisu saglasne za mnozenje.\n";
  } catch (std::runtime_error) {
    std::cout << "GRESKA: Neocekivani problemi pri racunanju.\n";
  }
  return 0;
}
