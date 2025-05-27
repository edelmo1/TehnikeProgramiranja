// TP 2022/2023: Zadaća 1, Zadatak 2
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#include <stdexcept>

typedef std::vector<std::vector<double>> Matrica;

Matrica UsrednjavajuciFilter(Matrica m, int N) {

  if (N < 0) { 
    throw std::domain_error("Neispravan red filtriranja");
  }
  Matrica m1;

  int duzina = m.size();
  m1.resize(duzina);
  for (int i = 0; i < duzina; i++) {
    int sirina = m.at(i).size();
    for (int j = 0; j < sirina; j++) {

      int brojac = 0;
      double suma = 0;
      int sirina2=0;
      for (int k = i - N; k <= i + N; k++) {
          if(k<0 || k>=duzina) {
              continue;
          }
          else {         
            sirina2=m.at(k).size();
          }
        for (int z = j - N; z <= j + N; z++) {
          if (k < 0 || k >= duzina || z < 0 || z >= sirina2) {
            continue;
          }

          brojac++;
          suma += m.at(k).at(z);
        }
      }
      m1.at(i).push_back(suma / brojac);
    }
  }

  return m1;
}

int main() {

   int M=0, N=0;
   std::cout << "Unesite broj redova i kolona matrice: ";
   std::cin >> M >> N;
   std::cout << "Unesite elemente matrice:\n";

Matrica m(M, std::vector<double>(N));
  for (int i = 0; i < M; i++) {
    for (int j = 0; j <N ; j++) {
      std::cin >> m.at(i).at(j);
    }
  }

  int n=0;
  std::cout << "Unesite red filtriranja: ";
  std::cin >> n;

  try {
    m = UsrednjavajuciFilter(m, n);
    std:: cout<<"Matrica nakon filtriranja:";
std::cout<<std::endl;
    for (int i = 0; i < M; i++) {
      for (int j = 0; j <N ; j++) {
        std::cout << std::setw(7) << std::fixed << std::setprecision(2)
                  << m.at(i).at(j);
      }
      std::cout << std::endl;
    }
  } catch (std::domain_error e) {
    std::cout << "GRESKA: " << e.what() << "!" << std::endl;
  }

  return 0;
}
