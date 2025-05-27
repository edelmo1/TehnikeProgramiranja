// TP 2022/2023: Zadaća 5, Zadatak 3
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

class ApstraktnoVozilo {
protected:
  int tezina;

public:
  ApstraktnoVozilo(int tezina) : tezina(tezina){};
  virtual ~ApstraktnoVozilo(){};
  virtual int DajTezinu() const { return tezina; };
  virtual int DajUkupnuTezinu() const = 0;
  virtual ApstraktnoVozilo *DajKopiju() const = 0;
  virtual void IspisiPodatke() const = 0;
};

// AUTOMOBIL
class Automobil : public ApstraktnoVozilo {
  std::vector<int> tezine_putnika;

public:
  Automobil(int tezina, std::vector<int> tezine)
      : ApstraktnoVozilo(tezina), tezine_putnika(tezine.size()) {
    for (int i = 0; i < tezine.size(); i++)
      tezine_putnika.at(i) = tezine.at(i);
  }
  int DajUkupnuTezinu() const override;
  ApstraktnoVozilo *DajKopiju() const override {
    return new Automobil(this->tezina, this->tezine_putnika);
  };
  void IspisiPodatke() const override;
};

int Automobil::DajUkupnuTezinu() const {
  int teret = tezina;
  for (int i = 0; i < tezine_putnika.size(); i++)
    teret += tezine_putnika.at(i);
  return teret;
}

void Automobil::IspisiPodatke() const {
  std::cout << "Vrsta vozila: Automobil" << std::endl;
  std::cout << "Vlastita tezina: " << tezina << " kg" << std::endl;
  std::cout << "Tezine putnika: ";
  for (int i = 0; i < tezine_putnika.size(); i++) {
    std::cout << tezine_putnika.at(i) << " kg";
    if (i != tezine_putnika.size() - 1)
      std::cout << ", ";
    else {
      std::cout << " ";
    }
  }
  std::cout << std::endl;
  std::cout << "Ukupna tezina: " << DajUkupnuTezinu() << " kg" << std::endl;
}

// KAMION
class Kamion : public ApstraktnoVozilo {
  int tezina_tereta;

public:
  Kamion(int tezina, int tezina_tereta)
      : ApstraktnoVozilo(tezina), tezina_tereta(tezina_tereta){};
  int DajUkupnuTezinu() const override { return tezina + tezina_tereta; };
  ApstraktnoVozilo *DajKopiju() const override {
    return new Kamion(this->tezina, this->tezina_tereta);
  };
  void IspisiPodatke() const override;
};

void Kamion::IspisiPodatke() const {

  std::cout << "Vrsta vozila: Kamion" << std::endl;
  std::cout << "Vlastita tezina: " << tezina << " kg" << std::endl;
  std::cout << "Tezina tereta: " << tezina_tereta << " kg" << std::endl;
  std::cout << "Ukupna tezina: " << DajUkupnuTezinu() << " kg" << std::endl;
}

// AUTOBUS
class Autobus : public ApstraktnoVozilo {

  int broj_putnika;
  int prosjecna_tezina;

public:
  Autobus(int tezina, int broj_putnika, int prosjecna_tezina)
      : ApstraktnoVozilo(tezina), broj_putnika(broj_putnika),
        prosjecna_tezina(prosjecna_tezina){};
  int DajUkupnuTezinu() const override {
    return tezina + (broj_putnika * prosjecna_tezina);
  };
  ApstraktnoVozilo *DajKopiju() const override {
    return new Autobus(this->tezina, this->broj_putnika,
                       this->prosjecna_tezina);
  };
  void IspisiPodatke() const override;
};

void Autobus::IspisiPodatke() const {

  std::cout << "Vrsta vozila: Autobus" << std::endl;
  std::cout << "Vlastita tezina: " << tezina << " kg" << std::endl;
  std::cout << "Broj putnika: " << broj_putnika << std::endl;
  std::cout << "Prosjecna tezina putnika: " << prosjecna_tezina << " kg"
            << std::endl;
  std::cout << "Ukupna tezina: " << DajUkupnuTezinu() << " kg" << std::endl;
}

class Vozilo {

  ApstraktnoVozilo *p;
  void Test() const {
    if (!p)
      throw std::logic_error("Nespecificiran lik");
  };

public:
  Vozilo() : p(nullptr){};
  ~Vozilo() {
    delete p;
    p = nullptr;
  };
  Vozilo(const ApstraktnoVozilo &v) : p(v.DajKopiju()){};
  Vozilo(const Vozilo &v) { p = v.DajKopiju(); };
  Vozilo(Vozilo &&v) {
    p = v.p;
    v.p = nullptr;
  };
  Vozilo &operator=(const Vozilo &v) {
    delete p;
    p = nullptr;
    if (v.p != nullptr)
      p = v.DajKopiju();
    return *this;
  }
  Vozilo &operator=(Vozilo &&v) {
    std::swap(p, v.p);
    return *this;
  }
  int DajTezinu() const {
    Test();
    return p->DajTezinu();
  };
  int DajUkupnuTezinu() const {
    Test();
    return p->DajUkupnuTezinu();
  };
  ApstraktnoVozilo *DajKopiju() const {
    Test();
    return p->DajKopiju();
  };
  void IspisiPodatke() const {
    Test();
    p->IspisiPodatke();
  };
};

int main() {

  std::ifstream ulazni_tok("VOZILA.TXT");
  if (!ulazni_tok) {
    throw std::logic_error("Otvaranje datoteke nije uspjelo");
  }
  std::vector<Vozilo> vozila;
  vozila.resize(0);

  for (;;) {

    char znak;
    int broj1, broj2, broj3;
    ulazni_tok >> znak;
    if (!ulazni_tok)
      break;
    if (znak == 'A') {
      std::vector<int> tezine_putnika(0);
      int tezina_vozila = 0;
      bool prvi = true;
      ulazni_tok >> broj1;
      znak = ulazni_tok.get();
      if (broj1 < 0 || (znak != ' ' && znak != '\n')) {
        throw std::logic_error("Neispravan sadrzaj datoteke");
      };
      if (!ulazni_tok)
        break;
      int broj4;
      ulazni_tok >> broj4;
      znak = ulazni_tok.get();
      tezina_vozila = broj1;

      for (int i = 0; i < broj4; i++) {
        ulazni_tok >> broj1;
        znak = ulazni_tok.get();
        tezine_putnika.push_back(broj1);
      }
      Automobil car(tezina_vozila, tezine_putnika);
      Vozilo vozilo(car);
      vozila.push_back(vozilo);
    } else if (znak == 'K') {
      ulazni_tok >> broj1;
      znak = ulazni_tok.get();
      if (broj1 < 0 || znak != ' ') {
        throw std::logic_error("Neispravan sadrzaj datoteke");
      };
      if (!ulazni_tok)
        break;
      ulazni_tok >> broj2;
      if (broj1 < 0 || znak != ' ') {
        throw std::logic_error("Neispravan sadrzaj datoteke");
      };
      if (!ulazni_tok)
        break;
      Kamion kamion(broj1, broj2);
      Vozilo vozilo(kamion);
      vozila.push_back(vozilo);
    } else if (znak == 'B') {
      char znak2;
      ulazni_tok >> broj1;
      znak = ulazni_tok.get();
      ulazni_tok >> broj2;
      znak2 = ulazni_tok.get();
      ulazni_tok >> broj3;
      if (broj1 < 0 || znak != ' ' || broj2 < 0 ||
          (znak2 != ' ' && znak2 != '\n') || broj3 < 0) {
        throw std::logic_error("Neispravan sadrzaj datoteke");
      };
      if (!ulazni_tok)
        break;
      Autobus bus(broj1, broj2, broj3);
      Vozilo vozilo(bus);
      vozila.push_back(vozilo);
      // ulazni_tok >> znak;
      if (znak == '\n')
        break;
    } else {
      std::cout<<"Izuzetak: NEPOSTOJECE VOZILO!\n";
      return 0;
    }
    if (!ulazni_tok)
      break;
  }

  if (ulazni_tok.bad()) {
    std::cout << "Izvrsena nedozvoljena operacija\n";
    return 0;
  } else if (ulazni_tok.bad() == false && ulazni_tok.eof() == false) {
    std::cout << "Rad sa nedozvoljenim podacima\n";
    return 0;
  }
  ulazni_tok.close();

  std::sort(vozila.begin(), vozila.end(), [](Vozilo v1, Vozilo v2) {
    return v1.DajUkupnuTezinu() < v2.DajUkupnuTezinu();
  });
  for (int i = 0; i < vozila.size(); i++) {
    std::cout << vozila.at(i).DajUkupnuTezinu() << std::endl;
  }
  return 0;
}
