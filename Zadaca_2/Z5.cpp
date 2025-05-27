// TP 2022/2023: Zadaća 2, Zadatak 5
#include <array>
#include <cmath>
#include <deque>
#include <iostream>
#include <list>
#include <type_traits>
#include <vector>

template <typename IterTip1, typename IterTip2>
auto KreirajTablicuSabiranja(IterTip1 p1, IterTip1 p2, IterTip2 p3)
    -> std::common_type_t<decltype(*p1 + *p1), decltype(*p3 + *p3)> ** {

  typedef std::common_type_t<decltype(*p1 + *p1), decltype(*p3 + *p3)> NekiTip;

  int duzina = 0;
duzina=std::distance(p1,p2);
  NekiTip **pok = {};
  NekiTip **povratni = {};
  try {
    pok = new NekiTip *[duzina] {};
    povratni = pok;

    // izracunati broj elemenata ukupan
    int broj_el = duzina*(duzina+1)/2, broj = 1;
    
    pok[0] = new NekiTip[broj_el];

    for (int i = 1; i < duzina; i++) {
      pok[i] = pok[i - 1] + i;
    }
    // rasporedili smo pokazivace
    IterTip2 temp = p3;
    for (int i = 0; i < duzina; i++) {
      p3 = temp;
      for (int j = 0; j < 1 + i; j++) {
        pok[i][j] = *p1 + *p3;
        if (*p1 + *p3 != *p3 + *p1) {
          throw std::logic_error(
              "Nije ispunjena pretpostavka o komutativnosti");
        }
        p3++;
      }
      p1++;
    }
  } catch (std::logic_error) {
    delete[] povratni[0];
    delete[] povratni;
    throw;
  }
  catch(std::bad_alloc){
      delete[] povratni;
      throw std::range_error("Nema dovoljno memorije!");
  }
  return povratni;
}

int main() {

  int n = 0;
  std::cout << "Duzina sekvenci: ";
  std::cin >> n;

  try {
    std::vector<double> v(n);
    std::cout << "Elementi prve sekvence: ";
    for (int i = 0; i < n; i++) {
      std::cin >> v.at(i);
    }

    std::deque<double> dek(n);
    std::cout << "Elementi druge sekvence: ";
    for (int i = 0; i < n; i++) {
      std::cin >> dek.at(i);
    }

    double **p = KreirajTablicuSabiranja(v.begin(), v.end(), dek.begin());

    std::cout << "Tablica sabiranja:\n";
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < i + 1; j++) {
        std::cout << p[i][j] << " ";
      }
      std::cout << std::endl;
    }
    delete[] p[0];
    delete[] p;
  } catch (std::range_error e) {
    std::cout << "Izuzetak: " << e.what() << std::endl;
  } catch (std::logic_error e) {
    std::cout << "Izuzetak: " << e.what() << std::endl;
  }
  catch(std::bad_alloc e){
      std::cout<<"Nedovoljno memorije"<<std::endl;
  }

  return 0;
}
