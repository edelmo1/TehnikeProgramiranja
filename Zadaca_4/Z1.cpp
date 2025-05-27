// TP 2022/2023: Zadaća 4, Zadatak 1
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

class Krug {

  double poluprecnik;
  std::pair<double, double> centar;
  static bool Test(double x, double y) {
    double EPSILON = 1e-10;
    if (std::fabs(x - y) < EPSILON )
      return true;
    return false;
  }

public:
  explicit Krug(double poluprecnik = 0) : poluprecnik(poluprecnik) {
    if (poluprecnik < 0)
      throw std::domain_error("Nedozvoljen poluprecnik");
    centar.first = 0;
    centar.second = 0;
  };
  explicit Krug(const std::pair<double, double> &centar, double poluprecnik = 0)
      : poluprecnik(poluprecnik) {
    if (poluprecnik < 0)
      throw std::domain_error(
          "Nedozvoljen poluprecnik"); 
    Krug::centar.first = centar.first;
    Krug::centar.second = centar.second;
  }
  std::pair<double, double> DajCentar() const { return centar; };
  double DajPoluprecnik() const { return poluprecnik; };
  double DajObim() const {
    const double PI = 4 * atan(1);
    return 2 * poluprecnik * PI;
  };
  double DajPovrsinu() const {
    const double PI = 4 * atan(1);
    return poluprecnik * poluprecnik * PI;
  };
  Krug &PostaviCentar(const std::pair<double, double> &centar) {
    Krug::centar.first = centar.first;
    Krug::centar.second = centar.second;
    return *this;
  };
  Krug &PostaviPoluprecnik(double poluprecnik) {
    if (poluprecnik < 0)
      throw std::domain_error("Nedozvoljen poluprecnik");
    Krug::poluprecnik = poluprecnik;
    return *this;
  };
  void Ispisi() const {
    std::cout << "{(" << centar.first << "," << centar.second << "),"
              << poluprecnik << "}";
  };
  Krug &Transliraj(double delta_x, double delta_y) {
    double x = centar.first + delta_x;
    double y = centar.second + delta_y;
    centar.first = x;
    centar.second = y;
    return *this;
  };
  Krug &Rotiraj(double alpha);
  Krug &Rotiraj(const std::pair<double, double> &centar_rotacije, double alpha);
  static double RastojanjeCentara(const Krug &k1, const Krug &k2);
  static bool DaLiSuIdenticni(const Krug &k1, const Krug &k2);
  static bool DaLiSuPodudarni(const Krug &k1, const Krug &k2);
  static bool DaLiSuKoncentricni(const Krug &k1, const Krug &k2);
  static bool DaLiSeDodirujuIzvani(const Krug &k1, const Krug &k2);
  static bool DaLiSeDodirujuIznutri(const Krug &k1, const Krug &k2);
  static bool DaLiSePreklapaju(const Krug &k1, const Krug &k2);
  static bool DaLiSeSijeku(const Krug &k1, const Krug &k2);
  bool DaLiSadrzi(const Krug &k) const;
  friend Krug TransliraniKrug(const Krug &k, double delta_x, double delta_y);
  friend Krug RotiraniKrug(const Krug &k, double alpha);
  friend Krug RotiraniKrug(const Krug &k,
                           const std::pair<double, double> &centar_rotacije,
                           double alpha);
};

Krug &Krug::Rotiraj(double alpha) {

  double x = (centar.first) * cos(alpha) - (centar.second) * sin(alpha);
  double y = (centar.first) * sin(alpha) + (centar.second) * cos(alpha);
  centar.first = x;
  centar.second = y;
  return *this;
}

Krug &Krug::Rotiraj(const std::pair<double, double> &centar_rotacije,
                    double alpha) {

  double x = centar_rotacije.first +
             (centar.first - centar_rotacije.first) * std::cos(alpha) -
             (centar.second - centar_rotacije.second) * std::sin(alpha);
  double y = centar_rotacije.second +
             (centar.first - centar_rotacije.first) * std::sin(alpha) +
             (centar.second - centar_rotacije.second) * std::cos(alpha);
  centar.first = x;
  centar.second = y;
  return *this;
}

double Krug::RastojanjeCentara(const Krug &k1, const Krug &k2) {

  double razlika_x = k2.centar.first - k1.centar.first;
  double razlika_y = k2.centar.second - k1.centar.second;
  return std::sqrt(razlika_x * razlika_x + razlika_y * razlika_y);
}

bool Krug::DaLiSuIdenticni(const Krug &k1, const Krug &k2) {

  if (Test(k1.poluprecnik, k2.poluprecnik) == false)
    return false;
  if (Test(k1.centar.first, k2.centar.first) == false)
    return false;
  if (Test(k1.centar.second, k2.centar.second) == false)
    return false;
  return true;
}

bool Krug::DaLiSuPodudarni(const Krug &k1, const Krug &k2) {

  if (Test(k1.poluprecnik, k2.poluprecnik) == false)
    return false;
  return true;
}

bool Krug::DaLiSuKoncentricni(const Krug &k1, const Krug &k2) {

  if (Test(k1.centar.first, k2.centar.first) == false)
    return false;
  if (Test(k1.centar.second, k2.centar.second) == false)
    return false;
  return true;
}

bool Krug::DaLiSeDodirujuIzvani(const Krug &k1, const Krug &k2) {

  double EPSILON = 1e-10;
  double x = RastojanjeCentara(k1, k2);
 // if(Test(x,k1.poluprecnik+k2.poluprecnik)==true) return true;
  if (std::fabs(x - (k1.poluprecnik + k2.poluprecnik)) < EPSILON)
    return true;
  return false;
}

bool Krug::DaLiSeDodirujuIznutri(const Krug &k1, const Krug &k2) {
  double EPSILON = 1e-20;
  double x = RastojanjeCentara(k1, k2);
/*  if(Test(x,k1.poluprecnik-k2.poluprecnik)==true || Test(x,k2.poluprecnik-k1.poluprecnik)==true)
  return true;*/
  if (std::fabs(x - (k1.poluprecnik - k2.poluprecnik)) < EPSILON ||
      std::fabs(x - (k2.poluprecnik - k1.poluprecnik)) < EPSILON)
    return true;
  return false;
}

bool Krug::DaLiSePreklapaju(const Krug &k1, const Krug &k2) {

  if (DaLiSuKoncentricni(k1, k2) ||
      DaLiSeDodirujuIznutri(k1, k2) || k1.DaLiSadrzi(k2) || k2.DaLiSadrzi(k1))
    return true;
  if (DaLiSeDodirujuIzvani(k1, k2) == true)
    return false;

  double x = RastojanjeCentara(k1, k2);
  double y = 0;
  if (k1.poluprecnik - k2.poluprecnik > 0)
    y = k1.poluprecnik;
  else {
    y = k2.poluprecnik;
  }

  if (x - y > 0)
    return false;
  return true;
}

bool Krug::DaLiSeSijeku(const Krug &k1, const Krug &k2) {
  if (DaLiSuKoncentricni(k1, k2) || DaLiSeDodirujuIzvani(k1, k2) ||
      DaLiSeDodirujuIznutri(k1, k2) || k1.DaLiSadrzi(k2) || k2.DaLiSadrzi(k1))
    return false;
  double x = RastojanjeCentara(k1, k2);
  double y = k1.poluprecnik + k2.poluprecnik;

  if (x < y)
    return true;
  return false;
}

bool Krug::DaLiSadrzi(const Krug &k) const {

  double x = RastojanjeCentara(*this, k);
  double y = poluprecnik;

  if (x + k.poluprecnik < this->poluprecnik)
    return true;
  return false;
}

Krug TransliraniKrug(const Krug &k, double delta_x, double delta_y) {

  Krug k_novi(k.centar, k.poluprecnik);
  k_novi.Transliraj(delta_x, delta_y);
  return k_novi;
}

Krug RotiraniKrug(const Krug &k, double alpha) {

  Krug k_novi(k.centar, k.poluprecnik);
  k_novi.Rotiraj(alpha);
  return k_novi;
}

Krug RotiraniKrug(const Krug &k,
                  const std::pair<double, double> &centar_rotacije,
                  double alpha) {
  Krug k_novi(k.centar, k.poluprecnik);
  k_novi = k_novi.Rotiraj(centar_rotacije, alpha);
  return k_novi;
}

int main() {
  int n = 0;
  std::cout << "Unesite broj krugova: ";
  std::cin >> n;
  if (n <= 0) {
    std::cout << "\nUneseni broj nije prirodan!\n";
    return 0;
  }
  Krug **p = nullptr;
  bool bio_c = false;
  try {
    p = new Krug *[n] {};
    for (int i = 0; i < n; i++) {
      double x, y, r;
      std::cout << "Unesite centar " << i + 1 << ". kruga: ";
      if (bio_c == false && (!(std::cin >> x) || std::cin.peek() != ' ')) {
        std::cout << "Neispravne koordinate centra! Pokusajte ponovo:\n\n";
        i--;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        continue;
      }
      if (bio_c == false && (!(std::cin >> y) || std::cin.peek() != '\n')) {
        std::cout << "Neispravne koordinate centra! Pokusajte ponovo:\n\n";
        i--;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        continue;
      }
      std::cout << "Unesite poluprecnik " << i + 1 << ". kruga: ";
      if (!(std::cin >> r) || std::cin.peek() != '\n' || r < 0) {
        std::cout << "Neispravan poluprecnik! Pokusajte ponovo:\n\n";
        i--;
        continue;
      }
      bio_c = true;
      std::pair<double, double> centar(x, y);
      try {
        p[i] = new Krug(centar, r);
      } catch (...) {
        std::cout << "Problemi sa alokacijom memorije!\n";
        for (int i = 0; i < n; i++)
          delete p[i];
        delete[] p;
        return 0;
      }
      bio_c = false;
    }
  } catch (...) {
    std::cout << "Problemi sa alokacijom memorije!\n";
    return 0;
  }

  double delta_x = 0, delta_y = 0;
  std::cout << "Unesite parametre translacije (delta_x,delta_y): ";
  std::cin >> delta_x >> delta_y;
  std::transform(p, p + n, p, [delta_x, delta_y](Krug *p1) {
    p1->Transliraj(delta_x, delta_y);
    return p1;
  });
  double ugao_rotacije = 0;
  std::cout << "Unesite ugao rotacije oko tacke (0,0) u stepenima: ";
  std::cin >> ugao_rotacije;
  double PI = 4 * atan(1);
  double r = ugao_rotacije * PI / 180.;
  std::transform(p, p + n, p, [r](Krug *p1) {
    p1->Rotiraj(r);
    return p1;
  });
  std::sort(p, p + n, [](const Krug *p1, const Krug *p2) {
    return p1->DajPovrsinu() < p2->DajPovrsinu();
  });
  std::cout << "Parametri krugova nakon obavljene transformacije su: \n";
  std::for_each(p, p + n, [](const Krug *p1) {
    p1->Ispisi();
    std::cout << std::endl;
  });
  Krug **max_el =
      std::max_element(p, p + n, [](const Krug *p1, const Krug *p2) {
        return p1->DajObim() < p2->DajObim();
      });
  std::cout << "Krug sa najvecim obimom je: ";
  (*max_el)->Ispisi();
  std::vector<std::pair<Krug, Krug>> parovi2; // svi moguci parovi
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++)
      parovi2.push_back({*p[i], *p[j]});
  }
  std::vector<std::pair<Krug, Krug>> parovi; // parovi pronadjenih krugova
  bool pronadjen = false;
  std::for_each(p, p + n, [&parovi2, &parovi, p, &pronadjen, n](Krug *p1) {
    std::for_each(p, p + n, [&parovi, &parovi2, &pronadjen, p1](Krug *p2) {
      if (p1 != p2 && Krug::DaLiSeSijeku(*p1, *p2)) {
        pronadjen = true;
        bool bio = false;
        for (int i = 0; i < parovi.size(); i++) {
          if (parovi[i].first.DajCentar() == p2->DajCentar() &&
              parovi[i].first.DajPoluprecnik() == p2->DajPoluprecnik() &&
              parovi[i].second.DajCentar() == p1->DajCentar() &&
              parovi[i].second.DajPoluprecnik() == p1->DajPoluprecnik()) {
            bio = true;
            break;
          }
        }
        if (bio == false)
          parovi.push_back({*p1, *p2});
      }
    });
  });
  if (pronadjen == false)
    std::cout << "\nNe postoje krugovi koji se presjecaju!\n";

  if (pronadjen == true) {

    for (int i = 0; i < parovi.size(); i++) {
      std::cout << "\nPresjecaju se krugovi:\n";
      parovi[i].first.Ispisi();
      std::cout << " i ";
      parovi[i].second.Ispisi();
      std::cout << std::endl;
    }
  }
  for (int i = 0; i < n; i++)
    delete p[i];
  delete[] p;
  return 0;
}
