// TP 2022/2023: Zadaća 3, Zadatak 2
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

typedef std::map<std::string, std::vector<std::string>> Knjiga;
typedef std::map<std::string, std::set<std::tuple<std::string, int, int>>>
    IndeksPojmova;

std::string PretvoriUMala(std::string s) {
  for (int i = 0; i < s.length(); i++) {
    if (s.at(i) >= 'A' && s.at(i) <= 'Z')
      s.at(i) += 32;
  }
  return s;
}
// i+1-broj stranice
IndeksPojmova KreirajIndeksPojmova(Knjiga knjiga) {

  IndeksPojmova mapa;
  int i = 0;
  for (auto it = knjiga.begin(); it != knjiga.end(); it++) {
    for (int k = 0; k < it->second.size(); k++) {
      i = k; // OVDJE JE PROBLEM
      for (int j = 0; j < it->second.at(i).size();
           j++) { // element vektora koji je stranica

        if (it->second.at(i).at(j) < '0' ||
            it->second.at(i).at(j) > '9' && it->second.at(i).at(j) < 'A' ||
            it->second.at(i).at(j) > 'Z' && it->second.at(i).at(j) < 'a' ||
            it->second.at(i).at(j) > 'z') {
          int k = 0;
          for (k = j; k < it->second.at(i).size(); k++) {
            if (it->second.at(i).at(k) >= '0' &&
                    it->second.at(i).at(k) <= '9' ||
                it->second.at(i).at(k) >= 'A' &&
                    it->second.at(i).at(k) <= 'Z' ||
                it->second.at(i).at(k) >= 'a' && it->second.at(i).at(k) <= 'z')
              break;
          }
          j = k;
        }

        int pocetak = j;
        int duzina = 0;
        if (it->second.at(i).at(j) >= '0' && it->second.at(i).at(j) <= '9' ||
            it->second.at(i).at(j) >= 'A' && it->second.at(i).at(j) <= 'Z' ||
            it->second.at(i).at(j) >= 'a' && it->second.at(i).at(j) <= 'z') {
          int k = 0;
          for (k = j; k < it->second.at(i).size(); k++) {
            if (it->second.at(i).at(k) < '0' ||
            it->second.at(i).at(k) > '9' && it->second.at(i).at(k) < 'A' ||
            it->second.at(i).at(k) > 'Z' && it->second.at(i).at(k) < 'a' ||
            it->second.at(i).at(k) > 'z')
              break;
            duzina++;
          }
          j = k;
        }
        std::string rijec =
            it->second.at(i).substr(pocetak, duzina); // nasli smo rijec
        rijec = PretvoriUMala(rijec);
        if (!mapa.count(rijec)) {
          std::set<std::tuple<std::string, int, int>> skup;
          skup.insert({it->first, k + 1, pocetak});
          mapa[rijec] = skup;
        } else {
          mapa[rijec].insert({it->first, k + 1, pocetak});
        }
      }
      i++;
    }
  }
  return mapa;
}

std::set<std::tuple<std::string, int, int>>
PretraziIndeksPojmova(std::string rijec, IndeksPojmova mapa) {

  rijec = PretvoriUMala(rijec);
  if (!mapa.count(rijec))
    throw std::logic_error("Pojam nije nadjen");

  std::set<std::tuple<std::string, int, int>> skup;
  auto it = mapa.find(rijec);
  int broj = 0;
  for (auto pocetak = it->second.begin(); pocetak != it->second.end();
       pocetak++) {
    skup.insert(
        {std::get<0>(*pocetak), std::get<1>(*pocetak), std::get<2>(*pocetak)});
  }
  return skup;
}
// PROVJERI OPET PRENOSE PARAMETARA DA LI CONST REF!
void IspisiIndeksPojmova(const IndeksPojmova &mapa) {
  for (auto it = mapa.begin(); it != mapa.end(); it++) {
    std::cout << it->first << ": ";
    for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
      if (std::distance(it2, it->second.end()) != 1) { // vidi je li 1 ili 0
        std::cout << std::get<0>(*it2) << "/" << std::get<1>(*it2) << "/"
                  << std::get<2>(*it2) << ", ";
      } else {
        std::cout << std::get<0>(*it2) << "/" << std::get<1>(*it2) << "/"
                  << std::get<2>(*it2) << std::endl;
      }
    }
  }
}

int main() {

  Knjiga knjiga;
  for (;;) {
    std::string poglavlje;
    std::cout << "\nUnesite naziv poglavlja: ";
    std::getline(std::cin, poglavlje);
    if (poglavlje.at(0) == '.')
      break;
    std::vector<std::string> v;
    int i = 0;
    for (;;) {
      std::cout << "\nUnesite sadrzaj stranice " << i + 1 << ": ";
      std::string temp;
      std::getline(std::cin, temp);
      if (temp.at(0) == '.')
        break;
      v.push_back(temp);
      i++;
    }
    knjiga.insert({poglavlje, v});
  }
  std::cout << std::endl;
  IndeksPojmova mapa = KreirajIndeksPojmova(knjiga);
  std::cout << "Kreirani indeks pojmova:\n";
  IspisiIndeksPojmova(mapa);

  for (;;) {
    std::cout << "Unesite rijec: ";
    std::string rijec;
    std::cin >> rijec;
    if (rijec.at(0) == '.')
      break;
    std::set<std::tuple<std::string, int, int>> skup;
    try {
      skup = PretraziIndeksPojmova(rijec, mapa);
    } catch (...) {
      std::cout << "\nUnesena rijec nije nadjena!\n";
      continue;
    }
    if (skup.begin() == skup.end())
      std::cout << "\nUnesena rijec nije nadjena!";
    else {
      for (auto it2 = skup.begin(); it2 != skup.end(); it2++) {
        std::cout << std::get<0>(*it2) << "/" << std::get<1>(*it2) << "/"
                  << std::get<2>(*it2) << " ";
      }
      std::cout << std::endl;
    }
  }
  return 0;
}
