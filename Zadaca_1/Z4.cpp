// TP 2022/2023: Zadaća 1, Zadatak 4
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::string Cenzura(std::string recenica, std::vector<std::string> v) {

  int duzina = v.size();
  if (recenica.length() == 0) {
    throw std::logic_error("Neispravna rečenica!");
  }
  // provjera vektora
  for (int i = 0; i < duzina; i++) {
    int duzina_stringa = v.at(i).length();
    for (int j = 0; j < duzina_stringa; j++) {
      if ((v.at(i).at(j) >= '0' && v.at(i).at(j) <= '9') ||
          (v.at(i).at(j) >= 'A' && v.at(i).at(j) <= 'Z') ||
          (v.at(i).at(j) >= 'a' && v.at(i).at(j) <= 'z') ||
          (v.at(i).at(j) == '.' || v.at(i).at(j) == ',')) {
        continue;
      } else {
        throw std::logic_error("Neispravna riječ");
      }
    }
  }


  int duzina_recenice = recenica.length();
  int pocetak = 0;
  int broj_slova = 0;
 

  for (int i = 0; i < duzina_recenice; i++) {
    if (recenica.at(i) == '.' || recenica.at(i) == '?' ||
        recenica.at(i) == '!' || recenica.at(i) == '\n')
      break;
    if (recenica.at(i) < '0' || recenica.at(i) > '9' && recenica.at(i) < 'A' ||
        recenica.at(i) > 'Z' && recenica.at(i) < 'a' || recenica.at(i) > 'z') {
      
      for (int x= i; x < duzina_recenice; x++) {
        if (recenica.at(x) >= '0' && recenica.at(x) <= '9' ||
            recenica.at(x) >= 'A' && recenica.at(x) <= 'Z' ||
            recenica.at(x) >= 'a' && recenica.at(x) <= 'z') {
           i=x;
          break;
        }
      }
    
    }

    if (recenica.at(i) >= '0' && recenica.at(i) <= '9' ||
        recenica.at(i) >= 'A' && recenica.at(i) <= 'Z' ||
        recenica.at(i) >= 'a' && recenica.at(i) <= 'z') {
      pocetak = i;
      broj_slova = 0;
      
      for (int z = i; z < duzina_recenice; i=++z) {
        if (recenica.at(z) < '0' ||
            recenica.at(z) > '9' && recenica.at(z) < 'A' ||
            recenica.at(z) > 'Z' && recenica.at(z) < 'a' ||
            recenica.at(z) > 'z') {

          break;
        }
        
        broj_slova++;
      }
      
      // poredimo sa rijecima
      std::string rijec = recenica.substr(pocetak, broj_slova);
      for (int k = 0; k < duzina; k++) {
        if (rijec.length() != v.at(k).length())
          continue;

        std::string rijec2 = v.at(k);
        for (int z = 0; z < rijec2.length(); z++) {
          rijec2.at(z) = std::toupper(rijec2.at(z));
        }
        for (int z = 0; z < rijec.length(); z++) {
          rijec.at(z) = std::toupper(rijec.at(z));
        }

        if (rijec == rijec2) {
          recenica.erase(pocetak, broj_slova);
          recenica.insert(pocetak, std::string(broj_slova, '*'));
        }
      }
    }
  }

  return recenica;
}

int main() {
 
  std::string s;
  std::cout << "Unesite recenicu: ";
  std::getline(std::cin, s);

  std::vector<std::string> v;

  std::cout << "\nUnesite zabranjene rijeci (. za kraj): ";
  for (int i = 0;; i++) {
    std::string s1;
    std::cin >> s1;

    if (s1.at(0) == '.') {
      break;
    } else {
      v.push_back(s1);
    }
  }
  try {
    std::string recenica = Cenzura(s, v);
    std::cout << std::endl;
    std::cout << "Cenzurisana recenica: " << recenica << std::endl;

  } catch (std::logic_error e) {
    std::cout << "\nGRESKA: Nelegalne zabranjene rijeci!\n";
  }

  return 0;
}
