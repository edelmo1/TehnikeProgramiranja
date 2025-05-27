// TP 2022/2023: Zadaća 4, Zadatak 4
#include <cmath>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>


class Korisnik {

  int clanski_broj;
  std::string ime_i_prezime;
  std::string adresa;
  std::string broj_telefona;

public:
  Korisnik(int clanski_broj, std::string ime_i_prezime, std::string adresa,
           std::string broj_telefona);
  int DajClanskiBroj() const;
  std::string DajImeIPrezime() const;
  std::string DajAdresu() const;
  std::string DajTelefon() const;
  void Ispisi() const;
};

Korisnik::Korisnik(int clanski_broj, std::string ime_i_prezime,
                   std::string adresa, std::string broj_telefona)
    : clanski_broj(clanski_broj), ime_i_prezime(ime_i_prezime), adresa(adresa),
      broj_telefona(broj_telefona){};
int Korisnik::DajClanskiBroj() const { return clanski_broj; };
std::string Korisnik::DajImeIPrezime() const { return ime_i_prezime; };
std::string Korisnik::DajAdresu() const { return adresa; };
std::string Korisnik::DajTelefon() const { return broj_telefona; };
void Korisnik::Ispisi() const {

  std::cout << "Clanski broj: " << clanski_broj << std::endl;
  std::cout << "Ime i prezime: " << ime_i_prezime << std::endl;
  std::cout << "Adresa: " << adresa << std::endl;
  std::cout << "Telefon: " << broj_telefona << std::endl;
}

class Film {

  int evidencijski_broj;
  int godina;
  bool video; // PROVJERI OVO!!
  Korisnik *korisnik;
  std::string naziv;
  std::string zanr;

public:
  Film(int evidencijski_broj, bool video, std::string naziv, std::string zanr,
       int godina);
  int DajEvidencijskiBroj() const { return evidencijski_broj; };
  std::string DajNaziv() const { return naziv; };
  int DajGodinuProdukcije() const { return godina; };
  std::string DajZanr() const { return zanr; };
  bool DaLiJeDVD() const {
    if (video == true) {
      return true;
    }
    return false;
  }; // STA JE TACNO, A STA NETACNO?
  void ZaduziFilm(Korisnik &korisnik) { Film::korisnik = &korisnik; };
  void RazduziFilm() { korisnik = nullptr; };
  bool DaLiJeZaduzen() const {
    if (korisnik == nullptr) {
      return false;
    }
    return true;
  };
  Korisnik &DajKodKogaJe() const;
  Korisnik *DajPokKodKogaJe() const;
  void Ispisi() const;
};

// konstruktor
Film::Film(int evidencijski_broj, bool video, std::string naziv,
           std::string zanr, int godina)
    : evidencijski_broj(evidencijski_broj), video(video), naziv(naziv),
      zanr(zanr), godina(godina), korisnik(nullptr) {}

Korisnik &Film::DajKodKogaJe() const {
  if (DaLiJeZaduzen() == false)
    throw std::domain_error("Film nije zaduzen");
  return *korisnik;
}

Korisnik *Film::DajPokKodKogaJe() const {
  if (DaLiJeZaduzen() == false)
    return nullptr;
  return korisnik;
}

void Film::Ispisi() const {

  std::cout << "Evidencijski broj: " << evidencijski_broj << std::endl;
  std::cout << "Medij: ";
  if (DaLiJeDVD() == true)
    std::cout << "DVD" << std::endl;
  else {
    std::cout << "Video traka" << std::endl;
  }
  std::cout << "Naziv filma: " << naziv << std::endl;
  std::cout << "Zanr: " << zanr << std::endl;
  std::cout << "Godina produkcije: " << godina << std::endl;
}

class Videoteka {

  std::map<int, std::shared_ptr<Korisnik>> korisnici;
  std::map<int, std::shared_ptr<Film>> filmovi;

public:
  Videoteka() = default; //??????
  Videoteka(const Videoteka &videoteka);
  Videoteka(Videoteka &&videoteka);
  Videoteka &operator=(const Videoteka &videoteka);
  Videoteka &operator=(Videoteka &&videoteka);
  void RegistrirajNovogKorisnika(int clanski_broj, std::string ime_i_prezime,
                                 std::string adresa, std::string broj_telefona);
  void RegistrirajNoviFilm(int evidencijski_broj, bool video, std::string naziv,
                           std::string zanr, int godina);
  Korisnik &NadjiKorisnika(int clanski_broj);
  Film &NadjiFilm(int evidencijski_broj);
  void IzlistajKorisnike() const;
  void IzlistajFilmove() const;
  void ZaduziFilm(int evidencijski_broj, int clanski_broj);
  void RazduziFilm(int evidencijski_broj);
  void PrikaziZaduzenja(int clanski_broj) const;
};

// kopirajuci konstruktor
Videoteka::Videoteka(const Videoteka &videoteka) {

  for (auto it = videoteka.korisnici.begin(); it != videoteka.korisnici.end();
       it++) {
    std::shared_ptr<Korisnik> pok;
    pok = std::make_shared<Korisnik>(
        (*it).second->DajClanskiBroj(), (*it).second->DajImeIPrezime(),
        (*it).second->DajAdresu(), (*it).second->DajTelefon());
    korisnici[it->first] = pok;
  }

  for (auto it = videoteka.filmovi.begin(); it != videoteka.filmovi.end();
       it++) {
    std::shared_ptr<Film> p;
    p = std::make_shared<Film>(
        (*it).second->DajEvidencijskiBroj(), (*it).second->DaLiJeDVD(),
        (*it).second->DajNaziv(), (*it).second->DajZanr(),
        (*it).second->DajGodinuProdukcije());
        if((*it).second->DaLiJeZaduzen()==true){
            p->ZaduziFilm((*it).second->DajKodKogaJe());
        }
    filmovi[it->first] = p;
  }
}

// pomjerajuci konstruktor
Videoteka::Videoteka(Videoteka &&videoteka) {
std::swap(korisnici,videoteka.korisnici);
std::swap(filmovi,videoteka.filmovi);
}

// kopirajuci operator dodjele
Videoteka &Videoteka::operator=(const Videoteka &videoteka) {

korisnici.clear();
  for (auto it = videoteka.korisnici.begin(); it != videoteka.korisnici.end();
       it++) {
    std::shared_ptr<Korisnik> pok;
    pok = std::make_shared<Korisnik>(
        (*it).second->DajClanskiBroj(), (*it).second->DajImeIPrezime(),
        (*it).second->DajAdresu(), (*it).second->DajTelefon());
    korisnici[it->first] = pok;
  }

  filmovi.clear();

  for (auto it = videoteka.filmovi.begin(); it != videoteka.filmovi.end();
       it++) {
    std::shared_ptr<Film> pok;
    pok = std::make_shared<Film>(
        (*it).second->DajEvidencijskiBroj(), (*it).second->DaLiJeDVD(),
        (*it).second->DajNaziv(), (*it).second->DajZanr(),
        (*it).second->DajGodinuProdukcije());
         if((*it).second->DaLiJeZaduzen()==true){
            pok->ZaduziFilm((*it).second->DajKodKogaJe());
        }
    filmovi[it->first] = pok;
  }
  return *this;
}

// pomjerajuci operator dodjele
Videoteka &Videoteka::operator=(Videoteka &&videoteka) {

  std::swap(korisnici, videoteka.korisnici); // moze li ovako??
  std::swap(filmovi, videoteka.filmovi);
  return *this;
}

void Videoteka::RegistrirajNovogKorisnika(int clanski_broj,
                                          std::string ime_i_prezime,
                                          std::string adresa,
                                          std::string broj_telefona) {

  if (korisnici.count(clanski_broj) != 0)
    throw std::logic_error("Vec postoji korisnik s tim clanskim brojem");
  std::shared_ptr<Korisnik> p = std::make_shared<Korisnik>(
      clanski_broj, ime_i_prezime, adresa, broj_telefona);
  korisnici[clanski_broj] = p;
}

void Videoteka::RegistrirajNoviFilm(int evidencijski_broj, bool video,
                                    std::string naziv, std::string zanr,
                                    int godina) {

  if (filmovi.count(evidencijski_broj) != 0)
    throw std::logic_error("Film s tim evidencijskim brojem vec postoji");
  std::shared_ptr<Film> p =
      std::make_shared<Film>(evidencijski_broj, video, naziv, zanr, godina);
  filmovi[evidencijski_broj] = p;
}

Korisnik &Videoteka::NadjiKorisnika(int clanski_broj) {
  // da li vraca korisnika ili par?
  if (korisnici.count(clanski_broj) == 0)
    throw std::logic_error("Korisnik nije nadjen");
  auto it = korisnici.find(clanski_broj);
  return *(it->second);
}

Film &Videoteka::NadjiFilm(int evidencijski_broj) {

  if (filmovi.count(evidencijski_broj) == 0)
    throw std::logic_error("Film nije nadjen");
  auto it = filmovi.find(evidencijski_broj);
  return *(it->second);
}

void Videoteka::IzlistajKorisnike() const {

  for (auto it = korisnici.begin(); it != korisnici.end(); it++) {
    ((*it).second)->Ispisi();
    std::cout << std::endl;
  }
}

void Videoteka::IzlistajFilmove() const {

  for (auto it = filmovi.begin(); it != filmovi.end(); it++) {
    ((*it).second)->Ispisi();
    if (((*it).second)->DaLiJeZaduzen() == true) {
      std::cout << "Zaduzen kod korisnika: ";
      std::cout << ((*it).second)->DajKodKogaJe().DajImeIPrezime() << " ("
                << ((*it).second)->DajKodKogaJe().DajClanskiBroj() << ")"
                << std::endl;
    }
    std::cout << std::endl;
  }
}

void Videoteka::ZaduziFilm(int evidencijski_broj, int clanski_broj) {

  if (filmovi.count(evidencijski_broj) == 0)
    throw std::logic_error("Film nije nadjen");
  auto x = filmovi.find(evidencijski_broj);
  if ((*x).second->DaLiJeZaduzen() == true)
    throw std::logic_error("Film vec zaduzen");
  if (korisnici.count(clanski_broj) == 0)
    throw std::logic_error("Korisnik nije nadjen");
  auto y = korisnici.find(clanski_broj);
  (*x).second->ZaduziFilm(*((*y).second));
}

void Videoteka::RazduziFilm(int evidencijski_broj) {

  if (filmovi.count(evidencijski_broj) == 0)
    throw std::logic_error("Film nije nadjen");
  auto x = filmovi.find(evidencijski_broj);
  if ((*x).second == nullptr)
    throw std::logic_error("Film nije zaduzen");
  (*x).second->RazduziFilm(); 
}

void Videoteka::PrikaziZaduzenja(int clanski_broj) const {

  if (korisnici.count(clanski_broj) == 0)
    throw std::logic_error("Korisnik nije nadjen");

  int broj = 0;
  for (auto it = filmovi.begin(); it != filmovi.end(); it++) {

    if (((*it).second)->DaLiJeZaduzen() == true) {
      if (((*it).second)->DajKodKogaJe().DajClanskiBroj() == clanski_broj) {
        ((*it).second)->Ispisi();
        std::cout << std::endl;
        broj++;
      }
    }
  }
  if (broj == 0)
    std::cout << "Korisnik nema zaduzenja!" << std::endl;
}

int main() {
  Videoteka videoteka;
  int evidencijski_broj, clanski_broj, godina;
  bool video;
  std::string ime_i_prezime, adresa, broj_telefona, zanr, naziv;
  for (;;) {
    std::cout << "\nMoguce opcije su:\n1.Registriraj novog korisnika\n2. "
                 "Registriraj fovi film\n3.Nadji korisnika\n4.Nadji "
                 "film\n5.Izlistaj korisnike\n6.Izlistaj filmove\n7.Zaduzi "
                 "Film\n8.Razduzi film\n9.Prikazi zaduzenja\n10.Kraj\n";
    std::cout << "Odaberi opciju: ";
    int opcija;
    std::cin >> opcija;
    switch (opcija) {

    case 1:
      std::cout << "Unesite clanski broj: ";
      std::cin >> clanski_broj;
      std::cin.ignore(10000, '\n');
      std::cout << "Unesite ime i prezime: ";
      std::getline(std::cin, ime_i_prezime);
      std::cout << "Unesite adresu: ";
      std::getline(std::cin, adresa);
      std::cout << "Unesite broj telefona: ";
      std::getline(std::cin, broj_telefona);
      try {
        videoteka.RegistrirajNovogKorisnika(clanski_broj, ime_i_prezime, adresa,
                                            broj_telefona);
      } catch (std::logic_error e) {
        std::cout << e.what() << std::endl;
      }
      break;

    case 2:
      std::cout << "Unesite evidencijski broj: ";
      std::cin >> evidencijski_broj;
      std::cout << "Da li je DVD?(Ako jeste unesite 1, ako nije 0)";
      int temp;
      std::cin >> temp;
      if (temp == 1)
        video = true;
      else {
        video = false;
      }
      std::cout << "Unesite naziv filma: ";
      std::cin.ignore(10000, '\n');
      std::getline(std::cin, naziv);
      std::cout << "Unesite zanr: ";
      std::getline(std::cin, zanr);
      std::cout << "Unesite godinu izdavanja: ";
      std::cin.ignore(10000, '\n');
      std::cin >> godina;
      try {
        videoteka.RegistrirajNoviFilm(evidencijski_broj, video, naziv, zanr,
                                      godina);
      } catch (std::logic_error e) {
        std::cout << e.what() << std::endl;
      }
      int znak;
      std::cin >> znak;
      break;

    case 3:
      std::cout << "Unesite clanski broj korisnika: ";
      std::cin >> clanski_broj;
      try {
        videoteka.NadjiKorisnika(clanski_broj).Ispisi();
      } catch (std::logic_error e) {
        std::cout << e.what() << std::endl;
      }
      break;

    case 4:
      std::cout << "Unesite evidencijski broj filma: ";
      std::cin >> evidencijski_broj;
      try {
        videoteka.NadjiFilm(evidencijski_broj).Ispisi();
      } catch (std::logic_error e) {
        std::cout << e.what() << std::endl;
      }
      break;

    case 5:
      std::cout << std::endl;
      videoteka.IzlistajKorisnike();
      break;

    case 6:
      std::cout << std::endl;
      videoteka.IzlistajFilmove();
      break;

    case 7:
      std::cout << "Unesite evidencijski broj filma koji zelite zaduziti: ";
      std::cin >> evidencijski_broj;
      std::cout << "Unesite clanski broj: ";
      std::cin >> clanski_broj;
      try {
        videoteka.ZaduziFilm(evidencijski_broj, clanski_broj);
      } catch (std::logic_error e) {
        std::cout << e.what() << std::endl;
      }
      break;

    case 8:
      std::cout << "Unesite evidencijski broj filma koji zelite razduziti: ";
      std::cin >> evidencijski_broj;
      try {
        videoteka.RazduziFilm(evidencijski_broj);
      } catch (std::logic_error e) {
        std::cout << e.what() << std::endl;
      }
      break;

    case 9:
      std::cout << "Unesite clanski broj: ";
      std::cin >> clanski_broj;
      try {
        videoteka.PrikaziZaduzenja(clanski_broj);
      } catch (std::logic_error e) {
        std::cout << e.what() << std::endl;
      }
      break;

    case 10:
      return 0;
    }
  }

  return 0;
}
