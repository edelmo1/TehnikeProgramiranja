// TP 2022/2023: Zadaća 4, Zadatak 3
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <stdexcept>

class Polazak {

  std::string odrediste;
  std::string oznaka_voznje;
  int broj_perona; // opsegu od 1 do 15
  int sat_polaska;
  int minute_polaska;
  int trajanje_voznje; // u minutama
  int kasnjenje;       // u minutama
public:
  Polazak(std::string odrediste, std::string oznaka_voznje, int broj_perona,
          int sat_polaska, int minute_polaska, int trajanje_voznje);
  void PostaviKasnjenje(int kasnjenje) {
    if (kasnjenje < 0)
      throw std::logic_error("Neregularna vrijednost kasnjenja");
    Polazak::kasnjenje = kasnjenje;
  };
  bool DaLiKasni() const {
    if (kasnjenje != 0) {
      return true;
    }
    return false;
  };
  int DajTrajanje() const { return trajanje_voznje; };
  void OcekivanoVrijemePolaska(int &sati, int &minute) const;
  void OcekivanoVrijemeDolaska(int &sati, int &minute) const;
  void Ispisi() const;
};

// konstruktor
Polazak::Polazak(std::string odrediste, std::string oznaka_voznje,
                 int broj_perona, int sat_polaska, int minute_polaska,
                 int trajanje_voznje)
    : odrediste(odrediste), oznaka_voznje(oznaka_voznje),
      broj_perona(broj_perona), sat_polaska(sat_polaska),
      minute_polaska(minute_polaska), trajanje_voznje(trajanje_voznje),
      kasnjenje(0) {
  if (broj_perona < 1 || broj_perona > 15 || sat_polaska < 0 ||
      sat_polaska > 24 || minute_polaska < 0 || minute_polaska > 59 ||
      trajanje_voznje < 0)
    throw std::domain_error("Neispravni parametri konstruktora!");
}

void Polazak::OcekivanoVrijemePolaska(int &sati, int &minute) const {

  sati = Polazak::sat_polaska;
  minute = Polazak::minute_polaska + kasnjenje;
  if (minute >= 60) {
    for (;;) {
      minute -= 60;
      sati++;
      if (minute < 60)
        break;
    }
  }
}

void Polazak::OcekivanoVrijemeDolaska(int &sati, int &minute) const {

  int delta = trajanje_voznje + kasnjenje;
  int sat = Polazak::sat_polaska, min = Polazak::minute_polaska + delta;
  if (min >= 60) {
    for (;;) {
      min -= 60;
      sat++;
      if (min < 60)
        break;
    }
  }
  if (sat >= 24)
    sat = 0;
  sati = sat;
  minute = min;
}

void Polazak::Ispisi() const {
  int min, sat;
  OcekivanoVrijemeDolaska(sat, min); 
  if (kasnjenje == 0)
    std::cout <<std::setfill(' ')<< std::setw(10) << std::left << oznaka_voznje << std::setw(30)
              << std::left << odrediste << "     " << std::setw(2)<<std::setfill(' ')
              << std::right << sat_polaska << ":"
              << std::setfill('0') << std::setw(2) << std::right
              << minute_polaska << "     " << std::setw(2) 
              << std::right<<std::setfill(' ') << sat << ":" << std::setfill('0') << std::setw(2)
              << std::right << min << std::right << std::setfill(' ')
              << std::setw(8) << std::right << broj_perona << std::endl;
  else {
    int s, m;
    OcekivanoVrijemePolaska(s, m);
    std::cout <<std::setfill(' ')<< std::setw(10) <<std::left<< oznaka_voznje << std::setw(30) << odrediste
              << "     " << std::right<<std::setw(2) << s << ":"
              << std::setfill('0') <<std::right<< std::setw(2) << m << " (Planirano "
              << std::setw(2) << std::setfill(' ') << sat_polaska << ":"
              << std::setfill('0') << std::setw(2) << minute_polaska
              << ", Kasni " << kasnjenje << " min)" << std::endl;
  }
}

class Polasci {

  int max_broj_polazaka;
  Polazak **p; 
public:
  explicit Polasci(int max_broj_polazaka);
  Polasci(std::initializer_list<Polazak> lista_polazaka);
  ~Polasci();
  Polasci(const Polasci &polasci);
  Polasci(Polasci &&polasci);
  Polasci &operator=(const Polasci &polasci);
  Polasci &operator=(Polasci &&polasci);
  void RegistrirajPolazak(std::string odrediste, std::string oznaka_voznje,
                          int broj_perona, int sat_polaska, int minute_polaska,
                          int trajanje_voznje);
  void RegistrirajPolazak(Polazak *polazak);
  int DajBrojPolazaka() const;
  int DajBrojPolazakaKojiKasne() const;
  Polazak &DajPrviPolazak();
  Polazak DajPrviPolazak() const;
  Polazak &DajPosljednjiPolazak();
  Polazak DajPosljednjiPolazak() const;
  void Ispisi() const;
  void IsprazniKolekciju();
};

// konstruktor
Polasci::Polasci(int max_broj_polazaka)
    : max_broj_polazaka(max_broj_polazaka),
      p(new Polazak *[max_broj_polazaka] {}){};

// sekvencijski konstruktor
Polasci::Polasci(std::initializer_list<Polazak> lista_polazaka) {
  auto it = lista_polazaka.begin();
  max_broj_polazaka=lista_polazaka.size();
  try {
    p = new Polazak *[lista_polazaka.size()] {};
    for (int i = 0; i < lista_polazaka.size(); i++) {
      p[i] = new Polazak(*it);
      it++;
    }
  } catch (...) {
    for (int i = 0; i < max_broj_polazaka; i++)
      delete p[i];
    delete[] p;
  }
}

// destruktor
Polasci::~Polasci() {
    if(p==nullptr) return;
  for (int i = 0; i < max_broj_polazaka; i++)
    delete p[i];
  delete[] p;
}

// kopirajuci konst
Polasci::Polasci(const Polasci &polasci)
    : max_broj_polazaka(polasci.max_broj_polazaka),
      p(new Polazak *[max_broj_polazaka] {}) {
  try {
    for (int i = 0; i < max_broj_polazaka; i++) {
        if(polasci.p[i]==nullptr) break;
      p[i] = new Polazak((*(polasci.p[i]))); 
    }
  } catch (...) {
    for (int i = 0; i < max_broj_polazaka; i++)
      delete p[i];
    delete[] p;
  }
}

// pomjerajuci konst
Polasci::Polasci(Polasci &&polasci)
    : max_broj_polazaka(polasci.max_broj_polazaka), p(polasci.p) {
  polasci.p = nullptr;
}

// kopirajuci operator dodjele
Polasci &Polasci::operator=(const Polasci &polasci) {

    if(&polasci==this) return *this;

for(int i=0;i<DajBrojPolazaka();i++) delete p[i];
delete[] p;

max_broj_polazaka=polasci.max_broj_polazaka;
p=new Polazak*[max_broj_polazaka]{};
for(int i=0;i<polasci.DajBrojPolazaka();i++){
    p[i]=new Polazak(*(polasci.p[i]));
}
  return *this;
}

// pomjerajuci operator dodjele
Polasci &Polasci::operator=(Polasci &&polasci) {
  std::swap(max_broj_polazaka, polasci.max_broj_polazaka);
  std::swap(p, polasci.p);
  return *this;
}

void Polasci::RegistrirajPolazak(std::string odrediste,
                                 std::string oznaka_voznje, int broj_perona,
                                 int sat_polaska, int minute_polaska,
                                 int trajanje_voznje) {

  bool nema = true; // nema prostora
  for (int i = 0; i < max_broj_polazaka; i++) {
    if (p[i] == nullptr) {
      nema = false;
      break;
    }
  }
  if (nema == true)
    throw std::range_error("Dostignut maksimalni broj polazaka");

  for (int i = 0; i < max_broj_polazaka; i++) {
    if (p[i] == nullptr) {
      p[i] = new Polazak(odrediste, oznaka_voznje, broj_perona, sat_polaska,
                         minute_polaska, trajanje_voznje);
      break;
    }
  }
}

void Polasci::RegistrirajPolazak(Polazak *polazak) {

  bool nema = true; // nema prostora
  for (int i = 0; i < max_broj_polazaka; i++) {
    if (p[i] == nullptr) {
      nema = false;
      break;
    }
  }
  if (nema == true)
    throw std::range_error("Dostignut maksimalni broj polazaka");

  for (int i = 0; i < max_broj_polazaka; i++) {
    if (p[i] == nullptr) {
      p[i] = polazak;
      break;
    }
  }
  polazak=nullptr;
}

int Polasci::DajBrojPolazaka() const {

  int broj = 0;
  for (int i = 0; i < max_broj_polazaka; i++) {
    if (p[i] != nullptr)
      broj++;
  }
  return broj;
}

int Polasci::DajBrojPolazakaKojiKasne() const {

  int br = 0;
  for (int i = 0; i < max_broj_polazaka; i++) {
    if (p[i] == nullptr)
      break;
    br++;
  }

  int broj = std::count_if(p, p + br, [](Polazak *p) {
    if (p->DaLiKasni())
      return true;
    return false;
  });
  return broj;
}

Polazak &Polasci::DajPrviPolazak() {

  int br = 0;
  for (int i = 0; i < max_broj_polazaka; i++) {
    if (p[i] == nullptr)
      break;
    br++;
  }

  Polazak **pok = std::max_element(p, p + br, [](Polazak *p1, Polazak *p2) {
    int s1, m1, s2, m2;
    p1->OcekivanoVrijemePolaska(s1, m1);
    p2->OcekivanoVrijemePolaska(s2, m2);
    m1 += s1 * 60;
    m2 += s2 * 60;
    return m1 > m2;
  });
  return **pok;
}

Polazak Polasci::DajPrviPolazak() const {

  int br = 0;
  for (int i = 0; i < max_broj_polazaka; i++) {
    if (p[i] == nullptr)
      break;
    br++;
  }
  Polazak **pok = std::max_element(p, p + br, [](Polazak *p1, Polazak *p2) {
    int s1, m1, s2, m2;
    p1->OcekivanoVrijemePolaska(s1, m1);
    p2->OcekivanoVrijemePolaska(s2, m2);
    m1 += s1 * 60;
    m2 += s2 * 60;
    return m1 > m2;
  });
  return **pok;
}

Polazak &Polasci::DajPosljednjiPolazak() {

  int br = 0;
  for (int i = 0; i < max_broj_polazaka; i++) {
    if (p[i] == nullptr)
      break;
    br++;
  }
  Polazak **pok = std::min_element(p, p + br, [](Polazak *p1, Polazak *p2) {
    int s1, m1, s2, m2;
    p1->OcekivanoVrijemePolaska(s1, m1);
    p2->OcekivanoVrijemePolaska(s2, m2);
    m1 += s1 * 60;
    m2 += s2 * 60;
    return m1 > m2;
  });
  return **pok;
}

Polazak Polasci::DajPosljednjiPolazak() const {

  int br = 0;
  for (int i = 0; i < max_broj_polazaka; i++) {
    if (p[i] == nullptr)
      break;
    br++;
  }
  Polazak **pok = std::min_element(p, p + br, [](Polazak *p1, Polazak *p2) {
    int s1, m1, s2, m2;
    p1->OcekivanoVrijemePolaska(s1, m1);
    p2->OcekivanoVrijemePolaska(s2, m2);
    m1 += s1 * 60;
    m2 += s2 * 60;
    return m1 > m2;
  });
  return **pok;
}

void Polasci::Ispisi() const {

  int br = 0;
  for (int i = 0; i < max_broj_polazaka; i++) {
    if (p[i] == nullptr)
      break;
    br++;
  }
  std::sort(p, p + br, [](Polazak *p1, Polazak *p2) {
    int s1, m1, s2, m2;
    p1->OcekivanoVrijemePolaska(s1, m1);
    p2->OcekivanoVrijemePolaska(s2, m2);
    m1 += s1 * 60;
    m2 += s2 * 60;
    return m1 < m2;
  });

  std::cout << std::right << std::setfill(' ') << std::setw(10) << "Voznja"
            << std::setw(30) << "Odrediste" << std::setw(10) << "Polazak"
            << std::setw(10) << "Dolazak" << std::setw(8) << "Peron"
            << std::right << std::endl;
            for(int i=0;i<70;i++)std::cout <<"-";
           std::cout << std::endl;
  for (int i = 0; i < max_broj_polazaka; i++) {
    if (p[i] == nullptr)
      break;
    p[i]->Ispisi();
  }
}

void Polasci::IsprazniKolekciju() {
  for (int i = 0; i < max_broj_polazaka; i++){
    delete p[i];
    p[i]=nullptr;
}
}
int main() {

  Polazak p1("Sarajevo", "ktrans", 5, 7, 30, 120);
  Polazak p2("Mostar", "strans", 8, 8, 0, 120);
  p1.Ispisi();
  std::cout << std::endl;
  std::cout << "Trajanje putovanja 2 je: " << p2.DajTrajanje() << " minuta"
            << std::endl;
  ;
  Polasci po(2);
  po.RegistrirajPolazak("Sarajevo", "ktrans", 5, 7, 30, 120);
  po.RegistrirajPolazak("Mostar", "strans", 8, 8, 0, 120);
  Polasci po2(po);
  po2.Ispisi();
  std::cout << std::endl;
  Polasci po3(3);
  po3 = po;
  po3.Ispisi();

  return 0;
}
