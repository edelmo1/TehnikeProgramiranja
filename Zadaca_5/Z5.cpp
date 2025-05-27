// TP 2022/2023: Zadaća 5, Zadatak 5
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <vector>
#include <stdexcept>

template <typename TipElemenata> class DatotecniKontejner {

  std::fstream tok;

public:
  DatotecniKontejner(const std::string &ime_datoteke);
  void DodajNoviElement(const TipElemenata &element);
  int DajBrojElemenata();
  TipElemenata DajElement(int pozicija);
  void IzmijeniElement(int pozicija, const TipElemenata &element);
  void Sortiraj(std::function<bool(const TipElemenata &, const TipElemenata &)>
                    kriterij = std::less<TipElemenata>());
};

template <typename TipElemenata>
DatotecniKontejner<TipElemenata>::DatotecniKontejner(
    const std::string &ime_datoteke) {

  tok.open(ime_datoteke,
           std::ios::binary | std::ios::in | std::ios::out |
               std::ios::app);//std::ios::app); // app sluzi da ne bi izbrisao vec postojecu
                               // datoteku, vidi je li to ok
  if (!tok)
    throw std::logic_error(
        "Problemi prilikom otvaranja ili kreiranja datoteke");
  tok.close();
  tok.open(ime_datoteke,
           std::ios::binary | std::ios::in | std::ios::out );
}

template <typename TipElemenata>
void DatotecniKontejner<TipElemenata>::DodajNoviElement(
    const TipElemenata &element) {
        tok.seekp(0,std::ios::end);
  tok.write(reinterpret_cast<const char *>(&element), sizeof element);
  if (!tok)
    throw std::logic_error("Problemi prilikom pristupa datoteci");
  tok.flush();
}

template <typename TipElemenata>
int DatotecniKontejner<TipElemenata>::DajBrojElemenata() {

  tok.seekg(0, std::ios::end);
  int duzina = tok.tellg();
  int broj_el = duzina / sizeof(TipElemenata);
  if (!tok)
    throw std::logic_error("Problemi prilikom pristupa datoteci");
  tok.flush();
  return broj_el;
}

template <typename TipElemenata>
TipElemenata DatotecniKontejner<TipElemenata>::DajElement(int pozicija) {

  int duzina = DajBrojElemenata();
  if (pozicija < 0 || pozicija >= duzina)
    throw std::range_error("Neispravna pozicija");
  tok.seekg(pozicija * sizeof(TipElemenata));
  TipElemenata element;
  tok.read(reinterpret_cast<char *>(&element), sizeof element);
  if (!tok)
    throw std::logic_error("Problemi prilikom pristupa datoteci");
  tok.flush();
  return element;
}

template <typename TipElemenata>
void DatotecniKontejner<TipElemenata>::IzmijeniElement(
    int pozicija, const TipElemenata &element) {

  int duzina = DajBrojElemenata();
  if (pozicija < 0 || pozicija >= duzina)
    throw std::range_error("Neispravna pozicija");

  tok.seekp(pozicija * sizeof(TipElemenata),std::ios::beg);
  // TipElemenata elementi=DajElement(pozicija);
tok.write(reinterpret_cast<const char *>(&element), sizeof (TipElemenata));
  if (!tok)
    throw std::logic_error("Problemi prilikom pristupa datoteci");
  tok.flush();
}

template <typename TipElemenata>
void DatotecniKontejner<TipElemenata>::Sortiraj(
    std::function<bool(const TipElemenata &, const TipElemenata &)> kriterij) {

int broj_el=DajBrojElemenata();
  for (int i = 0; i < broj_el; i++) {
    tok.seekg(i * sizeof(TipElemenata));
    TipElemenata element;
    tok.read(reinterpret_cast<char *>(&element), sizeof element);
    for (int j = i + 1; j < broj_el; j++) {

      tok.seekg(j * sizeof(TipElemenata));
      TipElemenata element2;
      tok.read(reinterpret_cast<char *>(&element2), sizeof element2);

      if (kriterij(element, element2) ==
          false) { // znaci da nisu u dobrom poretku
        TipElemenata temp = element;
        element = element2;
        element2 = temp;
      }
      tok.seekp(j * sizeof(TipElemenata));
      tok.write(reinterpret_cast<char *>(&element2), sizeof element2);
    }
    tok.seekp(i * sizeof(TipElemenata));
    tok.write(reinterpret_cast<char *>(&element), sizeof element);
  }
  tok.flush();
}

int main() {
  DatotecniKontejner<int> dki("BINARNA.DAT");

  std::cout << "U datoteci se nalazi: " << dki.DajBrojElemenata()
            << " elemenata.\n";
  std::cout << "Prvi element je " << dki.DajElement(0) << std::endl;
  dki.Sortiraj(std::greater<int>());
  std::cout << "Sada je prvi element " << dki.DajElement(0) << std::endl;

  return 0;
}
