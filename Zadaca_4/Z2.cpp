// TP 2022/2023: Zadaća 4, Zadatak 2
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>


class NepreklapajuciKrug {

  double poluprecnik;
  std::pair<double, double> centar;
  NepreklapajuciKrug *prethodni;
  static NepreklapajuciKrug *posljednji;
  static bool Test(double x, double y) {
    double EPSILON = 10e-10;
    if (std::fabs(x - y) > EPSILON * (std::fabs(x) + std::fabs(y)))
      return false;
    return true;
  }
  static bool DaLiSePreklapaju(const NepreklapajuciKrug &krug);

public:
  // mislim da ne moze i da se static atribut mora inicijalizirati u k.i.l
  explicit NepreklapajuciKrug(double poluprecnik = 0)
      : poluprecnik(poluprecnik) {
    if (poluprecnik < 0)
      throw std::domain_error("Nedozvoljen poluprecnik");
    centar.first = 0;
    centar.second = 0;
    auto temp = posljednji;
    posljednji = prethodni;
    prethodni = temp;
    posljednji = this;
    if (DaLiSePreklapaju(*this))
      throw std::logic_error("Nedozvoljeno preklapanje");
  };
  explicit NepreklapajuciKrug(const std::pair<double, double> &centar,
                              double poluprecnik = 0)
      : poluprecnik(poluprecnik) {
    if (poluprecnik < 0)
      throw std::domain_error(
          "Nedozvoljen poluprecnik"); // ako padalo izbaci konst.listu skroz
    NepreklapajuciKrug::centar.first = centar.first;
    NepreklapajuciKrug::centar.second = centar.second;
    if (DaLiSePreklapaju(*this))
      throw std::logic_error("Nedozvoljeno preklapanje");
    auto temp = posljednji;
    posljednji = prethodni;
    prethodni = temp;
    posljednji = this;
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
  NepreklapajuciKrug &PostaviCentar(const std::pair<double, double> &centar) {
   double f= NepreklapajuciKrug::centar.first;
   double s= NepreklapajuciKrug::centar.second;
   NepreklapajuciKrug::centar.first=centar.first;
   NepreklapajuciKrug::centar.second=centar.second;
   if (DaLiSePreklapaju(*this)){
        NepreklapajuciKrug::centar.first=f;
         NepreklapajuciKrug::centar.second=s;
      throw std::logic_error("Nedozvoljeno preklapanje");
   }
    return *this;
  };
  NepreklapajuciKrug &PostaviPoluprecnik(double poluprecnik) {
    if (poluprecnik < 0)
      throw std::domain_error("Nedozvoljen poluprecnik");
      double r=NepreklapajuciKrug::poluprecnik;
    NepreklapajuciKrug::poluprecnik = poluprecnik;
    if (DaLiSePreklapaju(*this)){
        NepreklapajuciKrug::poluprecnik=r;
      throw std::logic_error("Nedozvoljeno preklapanje");
    }
    return *this;
  };
  void Ispisi() const {
    std::cout << "{(" << centar.first << "," << centar.second << "),"
              << poluprecnik << "}" << std::endl;
  };
  NepreklapajuciKrug &Transliraj(double delta_x, double delta_y) {
      double x=centar.first;
      double y=centar.second;
    centar.first += delta_x;
    centar.second += delta_y;
    if(DaLiSePreklapaju(*this)==true){
        centar.first=x;
        centar.second=y;
        throw std::logic_error("Nedozvoljeno preklapanje");
    }
    return *this;
  };
  NepreklapajuciKrug &Rotiraj(double alpha);
  NepreklapajuciKrug &Rotiraj(const std::pair<double, double> &centar_rotacije,
                              double alpha);
  static double RastojanjeCentara(const NepreklapajuciKrug &k1,
                                  const NepreklapajuciKrug &k2);
  NepreklapajuciKrug(const NepreklapajuciKrug &krug) = delete;
  NepreklapajuciKrug &operator=(const NepreklapajuciKrug &krug) = delete;
  NepreklapajuciKrug(NepreklapajuciKrug &&krug) = delete;
  NepreklapajuciKrug &operator=(NepreklapajuciKrug &&krug) = delete;
  ~NepreklapajuciKrug();
};
NepreklapajuciKrug *NepreklapajuciKrug::posljednji = nullptr;
// destruktor
NepreklapajuciKrug::~NepreklapajuciKrug() {
  if (prethodni == nullptr) {
    auto it = posljednji;
    for (it = posljednji; it != this; it = it->prethodni) {
      if (it->prethodni == this)
        break;
    } // kreces se unazad
    it->prethodni = nullptr;
  } else if (posljednji == this) {
    prethodni->posljednji = prethodni;
  } else {
    auto it = posljednji->prethodni;
    auto it2 = posljednji;
    for (it2 = posljednji; it != this;
         it2 = it2->prethodni, it = it->prethodni) {
      if (it2->prethodni == this)
        break;
    }
    it2->prethodni = it->prethodni;
  }
}
NepreklapajuciKrug &NepreklapajuciKrug::Rotiraj(double alpha) {

double PI=4*atan(1);
alpha=(alpha*PI)/180.;
  double x = (centar.first) * cos(alpha) - (centar.second) * sin(alpha);
 double y= (centar.first) * sin(alpha) + (centar.second) * cos(alpha);
  double temp_x=centar.first,temp_y=centar.second;               
  centar.first=x;
  centar.second=y;
  if(DaLiSePreklapaju(*this)==true){
      centar.first=temp_x;
      centar.second=temp_y;
       throw std::logic_error("Nedozvoljeno preklapanje");
  }
  return *this;
}

NepreklapajuciKrug &
NepreklapajuciKrug::Rotiraj(const std::pair<double, double> &centar_rotacije,
                            double alpha) {

double PI=4*atan(1);
alpha=(alpha*PI)/180.;
  double x= centar_rotacije.first +
                 (centar.first - centar_rotacije.first) * cos(alpha) -
                 (centar.second - centar_rotacije.second) * sin(alpha);
  double y= centar_rotacije.second +
                  (centar.first - centar_rotacije.first) * sin(alpha) +
                  (centar.second - centar_rotacije.second) * cos(alpha);
   double temp_x=centar.first,temp_y=centar.second;               
  centar.first=x;
  centar.second=y;
  if(DaLiSePreklapaju(*this)==true){
      centar.first=temp_x;
      centar.second=temp_y;
       throw std::logic_error("Nedozvoljeno preklapanje");
  }
  return *this;
}

double NepreklapajuciKrug::RastojanjeCentara(const NepreklapajuciKrug &k1,
                                             const NepreklapajuciKrug &k2) {

  double razlika_x = k2.centar.first - k1.centar.first;
  double razlika_y = k2.centar.second - k1.centar.second;
  return std::sqrt(razlika_x * razlika_x + razlika_y * razlika_y);
}

bool NepreklapajuciKrug::DaLiSePreklapaju(const NepreklapajuciKrug &krug) {

  for (auto p = posljednji; p != nullptr; p = p->prethodni) {
    // ako je udaljenost centara manja od poluprecnika vece kruznice preklapaju
    // se
    double polup = 0;
    double EPSILON = 0.000001;
    if (&krug == p)
      continue;
    if (krug.poluprecnik - p->poluprecnik > 0)
      polup = krug.poluprecnik;
    else
      polup = p->poluprecnik;
    double rastojanje = RastojanjeCentara(krug, *p);
    if (rastojanje - (p->poluprecnik + krug.poluprecnik) < 0 ||
        std::fabs(rastojanje - (p->poluprecnik + krug.poluprecnik)) < EPSILON)
      return true;
  }
  return false;
}

int main() {

  int n = 0;
  std::cout << "Unesite broj krugova: ";
  for (;;) {
    if (!(std::cin >> n) || std::cin.peek() != '\n' || n <= 0) {
      std::cout << "Neispravan broj krugova, unesite ponovo! ";
      continue;
    }
    break;
  }
  std::vector<std::shared_ptr<NepreklapajuciKrug>> v;

  bool unijet_x = false, unijet_y = false, unijet_r = false;
  double x = 0, y = 0, r = 0;
  bool bio = false, bio_x = false, bio_y = false;
  for (int i = 0; i < n; i++) {

    if (bio_x == false && bio_y == false && unijet_x == false &&
        unijet_y == false)
      std::cout << "Unesite centar za " << i + 1 << ". krug: ";
    if (unijet_x == false && (!(std::cin >> x) || std::cin.peek() != ' ')) {
      std::cout << "Neispravan centar!\n";
      std::cout << "Unesite ponovo centar za " << i + 1 << ". krug: ";
      bio_x = true;
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      i--;
      continue;
    }
    std::cin >> std::ws;
    if (unijet_y == false && (!(std::cin >> y) || std::cin.peek() != '\n')) {
      std::cout << "Neispravan centar!\n";
      std::cout << "Unesite ponovo centar za " << i + 1 << ". krug: ";
      bio_y = true;
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      i--;
      continue;
    }
    if (bio == false)
      std::cout << "Unesite poluprecnik: ";
    unijet_x = true;
    unijet_y = true;
    std::cin >> r;
    if (!(std::cin) || std::cin.peek() != '\n' || r < 0) {
      std::cout << "Neispravan poluprecnik!\n";
      std::cout << "Unesite ponovo poluprecnik za " << i + 1 << ". krug: ";
      bio = true;
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      i--;
      continue;
    }
    std::pair<double, double> centar(x, y);
    std::shared_ptr<NepreklapajuciKrug> p = nullptr;
    try {
      p = std::make_shared<NepreklapajuciKrug>(centar, r);
    } catch (std::logic_error e) {
      std::cout << e.what() << std::endl;
      bio = false;
      bio_x = false;
      bio_y = false;
      unijet_x = false;
      unijet_y = false;
      i--;
      continue;
    }
    v.push_back(p);
    bio = false;
    bio_x = false;
    bio_y = false;
    unijet_x = false;
    unijet_y = false;
  }
  std::cout << "Krugovi nakon obavljenog sortiranja: ";
  std::sort(v.begin(), v.end(),
            [](std::shared_ptr<NepreklapajuciKrug> p1,
               std::shared_ptr<NepreklapajuciKrug> p2) {
              std::pair<double, double> c1 = p1->DajCentar();
              std::pair<double, double> c2 = p2->DajCentar();
              if (std::fabs(p1->DajPovrsinu() - p2->DajPovrsinu()) < 0.00001) {
                return c1.second >
                       c2.second; // nigdje nema definisano na osnovu cega ih
                                  // porediti u slucaju = povrsina, a u AT se
                                  // onda poredi po y osi
              }
              return p1->DajPovrsinu() > p2->DajPovrsinu();
            });

  for (int i = 0; i < v.size(); i++) {
    v.at(i)->Ispisi();
  }

  return 0;
}