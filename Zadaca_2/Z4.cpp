// TP 2022/2023: Zadaća 2, Zadatak 4
#include <algorithm>
#include <cctype>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

template <typename Tip>
bool Kriterij(std::vector<Tip> v1, std::vector<Tip> v2) {

if(v1.size()==0) return 0;  //inace ne mozemo pristupati elementima
if(v2.size()==0) return 0; 

  Tip proizvod1 = v1.at(0);
  int duzina1 = v1.size();
  for (int i = 1; i < duzina1; i++) {
    proizvod1 =proizvod1* v1.at(i);
  }

  Tip proizvod2 = v2.at(0);
  int duzina2 = v2.size();
  for (int i = 1; i < duzina2; i++) {
    proizvod2 =proizvod2* v2.at(i);
  }

  if (proizvod1 == proizvod2) {

    if (duzina1 >= duzina2) {

      for (int i = 0; i < duzina2; i++) {
        if (v1.at(i) == v2.at(i))
          continue;
        return v1.at(i) < v2.at(i);
      }
      return false;
    } else if (duzina2 > duzina1) {

      for (int i = 0; i < duzina1; i++) {
        if (v1.at(i) == v2.at(i))
          continue;
        return v1.at(i) < v2.at(i);
      }
      return false;
    }
  }
  return proizvod1 <= proizvod2;
}

template <typename NekiTip>
void SortirajPoProizvoduRedova(std::vector<std::vector<NekiTip>> &mat) {

  std::sort(mat.begin(), mat.end(), Kriterij<NekiTip>);
}

int main() {

  std::cout << "Unesi elemente (* za kraj reda, * na pocetku reda za kraj "
               "unosa): \n";

  std::vector<std::vector<int>> mat;

  for (int i = 0; i != -1; i++) {
    int temp;
    char temp2;
    bool prvi = true, ne_dodaji = false;
    std::vector<int> v;
    for (int j = 0; j != -1; j++) {
      if (j == 1)
        prvi = false;

      if (std::cin >> temp) {
        v.push_back(temp);
      } else if (std::cin.clear(), std::cin >> temp2 && prvi == true) {
        ne_dodaji = true;
        i = -2;
        break;
      } else {
        j = -2;
        continue;
      }
    }
    if (ne_dodaji == false) {
      mat.push_back(v);
    }
  }
  SortirajPoProizvoduRedova(mat);

  std::cout << "\nMatrica nakon sortiranja:\n";
  int velicina = mat.size();
  for (int i = 0; i < velicina; i++) {
    int duzina = mat.at(i).size();
    for (int j = 0; j < duzina; j++) {
      std::cout << mat.at(i).at(j) << " ";
    }
    std::cout << std::endl;
  }
  std::cin.ignore(1000, '\n');

  std::cout << "\nUnesite elemente sekvence koja se trazi (* za kraj reda): ";
  std::vector<int> v;
  for (;;) {
    int broj;
    char temp;
    if (std::cin >> broj) {
    } else if (std::cin.clear(), std::cin >> temp) {
      break;
    }
    v.push_back(broj);
  }

  bool sekvenca = std::binary_search(mat.begin(), mat.end(), v, Kriterij<int>);

if(sekvenca==true){
  std::vector<std::vector<int>>::iterator it =
      std::lower_bound(mat.begin(), mat.end(), v, Kriterij<int>);
  int indeks = it - mat.begin() + 1;

  if (indeks == mat.size() + 1) {
    std::cout << "\nTrazena sekvenca se ne nalazi u matrici\n";
  } else {
    std::cout << "\nTrazena sekvenca se nalazi u " << indeks
              << ". redu (nakon sortiranja)\n";
  }
}
else {
    std::cout<<"\nTrazena sekvenca se ne nalazi u matrici\n";
}
  return 0;
}
