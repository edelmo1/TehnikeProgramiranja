// TP 2022/2023: Zadaća 3, Zadatak 4
#include <cmath>
#include <iostream>
#include <list>
#include <stdexcept>
#include <vector>

int Poglavica(int N, int M, bool ispis = false) {

  if (N <= 0 || M <= 0)
    return 0;

  std::list<int> lista;
  int broj = 1;
  for (int i = 1; i <= N; i++)
    lista.push_back(i);

  broj = 1;
  int broj_izbacenih = 0, ukupno = N;
  auto it = lista.begin();
  bool nadjen = false;
  for (;;) {

    if (it == lista.end()) {
      it = lista.begin();
    }

    nadjen = false;

    if (M == broj) {
      nadjen = true;
      broj_izbacenih++;
    if ( ispis == true) {
        std::cout << *it << ", ";
      }
      N--;
      if (N == 0)
        return *it;
      it = lista.erase(it);
      broj = 1;
    }

    if (N == 1) {
      it++;
      if (it == lista.end()) {
        it = lista.begin();
      }
      return *it;
    }

    if (nadjen == true) {
      continue;
    }

    broj++;
    it++;
  }
  return 1;
}

int SigurnoMjesto(int M, int N1, int N2) {

if(M<=0 || N1<=0 || N2<=0 || N1>N2) return 0;

  std::vector<int> v(N2 - N1 + 1);

  for (int N = N1, i = 0; N <= N2; N++, i++) {
    v.at(i) = Poglavica(N, M);
  }

  for (int i = N1; i < N2; i++) {
    bool postoji = false;
    for (int j = 0; j < v.size(); j++) {
      if (i == v.at(j)) {
        postoji = true;
        break;
      }
    }
    if (postoji == false)
      return i;
  }

  return 0;
}

int main() {

  int M = 0, N1 = 0, N2 = 0, N = 0;

  std::cout << "Unesite broj punoljetnih clanova za odabir poglavice plemena "
               "Wabambe: ";
  std::cin >> N;
  std::cout << "Unesite korak razbrajanja: ";
  std::cin >> M;
  std::cout << "Unesite raspon za odabir (N1 i N2): ";
  std::cin >> N1 >> N2;
  std::cout << "Redni broj osobe koja postaje poglavica: " << Poglavica(N, M)
            << std::endl;
  int pozicija = SigurnoMjesto(M, N1, N2);
  if (pozicija != 0) {
    std::cout << "Mbebe Mgogo, stani na sigurno mjesto  " << pozicija
              << " da ne bi bio poglavica!" << std::endl;
    return 0;
  }
  std::cout << "Zao mi je Mbebe Mgogo, ali nema sigurnog mjesta." << std::endl;

  return 0;
}
