// TP 2022/2023: Zadaća 3, Zadatak 5
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

struct Cvor {
  int redni_broj;
  Cvor *sljedeci;
};

int Poglavica(int N, int M, bool ispis = false) {

  if (N <= 0 || M <= 0)
    return 0;

  Cvor *pocetni = nullptr;
  Cvor *prethodni = nullptr;

  for (int i = 1; i <= N; i++) {

    Cvor *novi = nullptr;
    try {
      novi = new Cvor{i, nullptr};
    } catch (std::bad_alloc e) {
      auto p = pocetni;
      p = p->sljedeci;
      for (p = p; pocetni != nullptr; p = p->sljedeci) {
        delete pocetni;
        pocetni = p;
      }
      throw;
    }
    if (pocetni == nullptr) {
      pocetni = novi;
    } else {
      prethodni->sljedeci = novi;
    }

    prethodni = novi;
  }
  prethodni->sljedeci = pocetni;

  bool nadjen = false;
  int broj = 1;
  int broj_izbacenih = 0, ukupno = N;
  for (Cvor *p = pocetni;; p = p->sljedeci) {

    nadjen = false;

    if (M == broj) {
      nadjen = true;
      broj_izbacenih++;
      N--;

      if (broj_izbacenih != ukupno && ispis == true)
        std::cout << p->redni_broj << ", ";

      if (N == 0) {
        prethodni->sljedeci = nullptr;
        int povrat = p->redni_broj;
        delete p;
        return povrat;
      }
      broj = 1;
      prethodni->sljedeci = p->sljedeci;
      delete p;
    }

    if (nadjen == true) {
      p = prethodni;
      continue;
    }

    broj++;
    prethodni = prethodni->sljedeci;
  }
  return 0;
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

  int M = 0, N = 0, N1 = 0, N2 = 0;

  std::cout << "Unesite broj punoljetnih clanova za odabir poglavice plemena "
               "Wabambe: ";
  std::cin >> N;
  std::cout << "Unesite korak razbrajanja: ";
  std::cin >> M;
  std::cout << "Unesite raspon za odabir (N1 i N2): ";
  std::cin >> N1 >> N2;
  try {
    std::cout << "Redni broj osobe koja postaje poglavica: " << Poglavica(N, M)
              << std::endl;
    int pozicija = SigurnoMjesto(M, 1, N);
    if (pozicija != 0) {
      std::cout << "Mbebe Mgogo, stani na sigurno mjesto " << pozicija
                << " da ne bi bio poglavica!" << std::endl;
      return 0;
    }
    std::cout << "Zao mi je Mbebe Mgogo, ali nema sigurnog mjesta."
              << std::endl;
  } catch (std::logic_error e) {
    std::cout << e.what() << std::endl;
  } catch (std::bad_alloc e) {
    std::cout << "Problemi s memorijom";
  }
  return 0;
}