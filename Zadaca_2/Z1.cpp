// TP 2022/2023: Zadaća 2, Zadatak 1
#include <cmath>
#include <iostream>
#include <vector>

enum class Pravci {
  Sjever,
  Sjeveroistok,
  Istok,
  Jugoistok,
  Jug,
  Jugozapad,
  Zapad,
  Sjeverozapad
};
enum class KodoviGresaka {
  PogresnaKomanda,
  NedostajeParametar,
  SuvisanParametar,
  NeispravanParametar
};
enum class Komande { Idi, Rotiraj, Sakrij, Otkrij, PrikaziTeren, Kraj };

std::vector<std::vector<char>> M(23, std::vector<char>(63, ' '));
bool vidljivost = true, vidljivost2 = true, v_ispod_nule= true;

void Idi(int &x, int &y, Pravci orijentacija, int korak) {

  if (vidljivost2 == true || vidljivost==true)
    M.at(11 - y).at(31 + x) = '*';
  else if (v_ispod_nule == true) {
    M.at(11 - y).at(31 + x) = '*';
  } else {
    M.at(11 - y).at(31 + x) = ' ';
  }
   vidljivost2=vidljivost;
  bool negativan = false;
  if (korak < 0) {
    negativan = true;
    switch (orijentacija) {
    case Pravci::Sjever: {
      orijentacija = Pravci::Jug;
      break;
    }
    case Pravci::Sjeveroistok: {
      orijentacija = Pravci::Jugozapad;
      break;
    }
    case Pravci::Istok: {
      orijentacija = Pravci::Zapad;
      break;
    }
    case Pravci::Jugoistok: {
      orijentacija = Pravci::Sjeverozapad;
      break;
    }
    case Pravci::Jug: {
      orijentacija = Pravci::Sjever;
      break;
    }
    case Pravci::Jugozapad: {
      orijentacija = Pravci::Sjeveroistok;
      break;
    }
    case Pravci::Zapad: {
      orijentacija = Pravci::Istok;
      break;
    }
    case Pravci::Sjeverozapad: {
      orijentacija = Pravci::Jugoistok;
      break;
    }
    }
  }
  switch (orijentacija) {
  case Pravci::Sjever: {
    if (negativan == true)
      korak = -korak;
    for (int i = 0; i < korak; i++) {
      y++;
      if (y > 10)
        y = -10;
      if (vidljivost == true) {
        if (vidljivost == true)
          M.at(11 - y).at(31 + x) = '*';
      }
    }
    if (korak < 0)
      orijentacija = Pravci::Jug;
  } break;

  case Pravci::Sjeveroistok: {
    if (negativan == true)
      korak = -korak;
    for (int i = 0; i < korak; i++) {
      x++, y++;
      if (x > 30)
        x = -30;
      if (y > 10)
        y = -10;
      if (vidljivost == true) {
        if (vidljivost == true)
          M.at(11 - y).at(31 + x) = '*';
      }
    }
    if (korak < 0)
      orijentacija = Pravci::Jugozapad;
    break;
  }

  case Pravci::Istok: {
    if (negativan == true)
      korak = -korak;
    for (int i = 0; i < korak; i++) {
      x++;
      if (x > 30)
        x = -30;
      if (vidljivost == true) {
        M.at(11 - y).at(31 + x) = '*';
      }
    }
    if (korak < 0)
      orijentacija = Pravci::Zapad;
    break;
  }

  case Pravci::Jugoistok: {
    if (negativan == true)
      korak = -korak;
    for (int i = 0; i < korak; i++) {
      x++, y--;
      if (x > 30)
        x = -30;
      if (y < -10)
        y = 10;
      if (vidljivost == true) {
        if (vidljivost == true)
          M.at(11 - y).at(31 + x) = '*';
      }
    }
    if (korak < 0)
      orijentacija = Pravci::Sjeverozapad;
    break;
  }

  case Pravci::Jug: {
    if (negativan == true)
      korak = -korak;
    for (int i = 0; i < korak; i++) {
      y--;
      if (y < -10)
        y = 10;
      if (vidljivost == true) {
        M.at(11 - y).at(31 + x) = '*';
      }
    }
    if (korak < 0)
      orijentacija = Pravci::Sjever;
    break;
  }

  case Pravci::Jugozapad: {
    if (negativan == true)
      korak = -korak;
    for (int i = 0; i < korak; i++) {
      x--, y--;
      if (x < -30)
        x = 30;
      if (y < -10)
        y = 10;
      if (vidljivost == true) {
        M.at(11 - y).at(31 + x) = '*';
      }
    }
    if (korak < 0)
      orijentacija = Pravci::Sjeveroistok;
    break;
  }

  case Pravci::Zapad: {
    if (negativan == true)
      korak = -korak;
    for (int i = 0; i < korak; i++) {
      x--;
      if (x < -30)
        x = 30;
      if (vidljivost == true) {
        M.at(11 - y).at(31 + x) = '*';
      }
    }
    if (korak < 0)
      orijentacija = Pravci::Istok;
    break;
  }

  case Pravci::Sjeverozapad: {
    if (negativan == true)
      korak = -korak;
    for (int i = 0; i < korak; i++) {
      x--, y++;
      if (x < -30)
        x = 30;
      if (y > 10)
        y = -10;
      if (vidljivost == true) {
        M.at(11 - y).at(31 + x) = '*';
      }
    }
    if (korak < 0)
      orijentacija = Pravci::Jugoistok;
    break;
  }
  }
  if (M.at(11 - y).at(31 + x) == '*')
    v_ispod_nule = true;
  else {
     v_ispod_nule = false;
  }
  M.at(11 - y).at(31 + x) = 'O';
}

void Rotiraj(Pravci &orijentacija, int ugao) {

  bool lijevo = true;
  if (ugao < 0) {
    lijevo = false;
    ugao *= (-1);
  }
  ugao *= 45;
  while (ugao > 360) {
    ugao = ugao - 360;
  }
  ugao /= 45;

  std::vector<Pravci> v{Pravci::Sjever, Pravci::Sjeveroistok,
                        Pravci::Istok,  Pravci::Jugoistok,
                        Pravci::Jug,    Pravci::Jugozapad,
                        Pravci::Zapad,  Pravci::Sjeverozapad};
  for (int i = 0; i < 8; i++) {
    if (v.at(i) == orijentacija) {
      if (lijevo == true) {
        int indeks = i - ugao;
        if (indeks < 0)
          indeks = 8 + indeks;
        orijentacija = v.at(indeks);
        break;
      }
      if (lijevo == false) {
        int indeks = i + ugao;
        if (indeks > 7)
          indeks = indeks - 8;
        orijentacija = v.at(indeks);
        break;
      }
    }
  }
}

void PostaviVidljivost(bool vidljiv) { vidljivost = vidljiv; }

void IspisiPoziciju(int x, int y, Pravci orijentacija) {

  std::cout << "Robot je ";
  if (vidljivost == true)
    std::cout << "vidljiv";
  else {
    std::cout << "nevidljiv";
  }
  std::cout << ", nalazi se na poziciji (" << x << "," << y << ") i gleda na ";
  switch (orijentacija) {
  case Pravci::Sjever: {
    std::cout << "sjever.";
    break;
  }
  case Pravci::Sjeveroistok: {
    std::cout << "sjeveroistok.";
    break;
  }
  case Pravci::Istok: {
    std::cout << "istok.";
    break;
  }
  case Pravci::Jugoistok: {
    std::cout << "jugoistok.";
    break;
  }
  case Pravci::Jug: {
    std::cout << "jug.";
    break;
  }
  case Pravci::Jugozapad: {
    std::cout << "jugozapad.";
    break;
  }
  case Pravci::Zapad: {
    std::cout << "zapad.";
    break;
  }
  case Pravci::Sjeverozapad: {
    std::cout << "sjeverozapad.";
    break;
  }
  }
  std::cout << std::endl;
}

void PrikaziTeren() {

  for (int i = 0; i < 23; i++) {
    for (int j = 0; j < 63; j++) {
      if (i == 0 || j == 0 || i == 22 || j == 62) {
        M.at(i).at(j) = '#';
      }
    }
  }
  for (int i = 0; i < 23; i++) {
    for (int j = 0; j < 63; j++) {
      std::cout << M.at(i).at(j);
    }
    std::cout << std::endl;
  }
}

void PrijaviGresku(KodoviGresaka kod_greske) {

  switch (kod_greske) {

  case KodoviGresaka::PogresnaKomanda: {
    std::cout << "Nerazumljiva komanda!\n";
    break;
  }
  case KodoviGresaka::NedostajeParametar: {
    std::cout << "Komanda trazi parametar koji nije naveden!\n";
    break;
  }
  case KodoviGresaka::NeispravanParametar: {
    std::cout << "Parametar komande nije ispravan!\n";
    break;
  }
  case KodoviGresaka::SuvisanParametar: {
    std::cout << "Zadan je suvisan parametar nakon komande!\n";
    break;
  }
  }
}

void IzvrsiKomandu(Komande komanda, int parametar, int &x, int &y,
                   Pravci &orijentacija) {

  switch (komanda) {

  case Komande::Idi: {
    Idi(x, y, orijentacija, parametar);
    break;
  }
  case Komande::Rotiraj: {
    Rotiraj(orijentacija, parametar);
    break;
  }
  case Komande::Sakrij: {
    PostaviVidljivost(false);
    break;
  }
  case Komande::Otkrij: {
    PostaviVidljivost(true);
    break;
  }
  case Komande::PrikaziTeren: {
    PrikaziTeren();
    break;
  }
  default:
    return;
  }
}

bool UnosKomande(Komande &komanda, int &parametar, KodoviGresaka &kod_greske) {

  char c;
  int broj = 0;
  std::cin >> c;
  switch (c) {

  case 'I': {
    char temp2;
    bool razmak = false;
    if (std::cin.peek() == ' ') {
      razmak = true;
    }
    while (razmak == true && std::cin.peek() == ' ' &&
           std::cin.peek() != '\n') {
      temp2 = std::cin.get();
    }
    if (std::cin.peek() == '\n') {
      kod_greske = KodoviGresaka::NedostajeParametar;
      std::cin.ignore(10000, '\n');
      return false;
    } else if (std::cin >> broj) {
      if (std::cin.peek() != '\n') {
        if (std::cin.peek() == ' ' && std::cin >> temp2) {
          kod_greske = KodoviGresaka::SuvisanParametar;
          std::cin.ignore(10000, '\n');
          return false;
        }
        kod_greske = KodoviGresaka::NeispravanParametar;
        std::cin.clear(), std::cin.ignore(10000, '\n');
        return false;
      }
      parametar = broj;
      komanda = Komande::Idi;
    } else if (std::cin.clear(), std::cin >> temp2) {
      kod_greske = KodoviGresaka::NeispravanParametar;
      std::cin.ignore(10000, '\n');
      return false;
    }
    break;
  }

  case 'R': {
    char temp2;
    bool razmak = false;
    if (std::cin.peek() == ' ')
      razmak = true;
    while (razmak == true && std::cin.peek() == ' ' &&
           std::cin.peek() != '\n') {
      temp2 = std::cin.get();
    }
    if (std::cin.peek() == '\n') {
      kod_greske = KodoviGresaka::NedostajeParametar;
      std::cin.ignore(10000, '\n');
      return false;
    } else if (std::cin >> broj) {
      parametar = broj;
      komanda = Komande::Rotiraj;
    } else if (std::cin.clear(), std::cin >> temp2) {
      kod_greske = KodoviGresaka::NeispravanParametar;
      std::cin.ignore(10000, '\n');
      return false;
    }
    break;
  }
  case 'S': {

    if (std::cin.peek() == '+') {
      char temp = std::cin.get();
      if (std::cin.peek() != '\n') {
        kod_greske = KodoviGresaka::SuvisanParametar;
        std::cin.ignore(10000, '\n');
        return false;
      }
      komanda = Komande::Sakrij;
    } else if (std::cin.peek() == '-') {
      char temp = std::cin.get();
      if (std::cin.peek() != '\n') {
        kod_greske = KodoviGresaka::SuvisanParametar;
        std::cin.ignore(10000, '\n');
        return false;
      }
      komanda = Komande::Otkrij;
    } else {
      kod_greske = KodoviGresaka::PogresnaKomanda;
      std::cin.ignore(10000, '\n');
      return false;
    }
    break;
  }
  case 'T': {
    if (std::cin.peek() != '\n') {
      kod_greske = KodoviGresaka::SuvisanParametar;
      std::cin.ignore(10000, '\n');
      return false;
    }
    komanda = Komande::PrikaziTeren;
    break;
  }
  case 'K': {
    if (std::cin.peek() != '\n') {
      kod_greske = KodoviGresaka::SuvisanParametar;
      std::cin.ignore(10000, '\n');
      return false;
    }
    komanda = Komande::Kraj;
    break;
  }
  default:
    kod_greske = KodoviGresaka::PogresnaKomanda;
    std::cin.ignore(10000, '\n');
    return false;
  }

  return true;
}

int main() {
  vidljivost = true;
  int x = 0, y = 0;
  M.at(11 - y).at(31 + x) = 'O';
  Pravci orijentacija = Pravci::Sjever;
  int parametar;
  KodoviGresaka kod_greske;
  IspisiPoziciju(x, y, orijentacija);
  for (;;) {
    std::cout << "Unesi komandu: ";
    Komande komanda;
    if (UnosKomande(komanda, parametar, kod_greske) == true) {
      if (komanda == Komande::Kraj) {
        std::cout << "Dovidjenja!\n";
        break;
      }
      IzvrsiKomandu(komanda, parametar, x, y, orijentacija);
      if (komanda != Komande::PrikaziTeren)
        IspisiPoziciju(x, y, orijentacija);
    } else {
      PrijaviGresku(kod_greske);
    }
  }

  return 0;
}
