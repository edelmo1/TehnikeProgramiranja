#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <new>
#include <stdexcept>
#include <string>

template <typename TipEl> class Matrica {
  char ime_matrice;
  int br_redova, br_kolona;
  TipEl **elementi;
  static TipEl **AlocirajMemoriju(int br_redova, int br_kolona);
  static void DealocirajMemoriju(TipEl **elementi, int br_redova);
  void KopirajElemente(TipEl **elementi);

public:
  Matrica(int br_redova, int br_kolona, char ime = 0);
  Matrica(const Matrica &m);
  Matrica(Matrica &&m);
  ~Matrica() { DealocirajMemoriju(elementi, br_redova); }
  Matrica &operator=(const Matrica &m);
  Matrica &operator=(Matrica &&m);
  friend std::istream &operator>>(std::istream &tok, Matrica<TipEl> &mat) {
    for (int i = 0; i < mat.br_redova; i++) {
      for (int j = 0; j < mat.br_kolona; j++) {
        std::cout << mat.ime_matrice << "(" << i + 1 << "," << j + 1 << ") = ";
        tok >> mat.elementi[i][j];
      }
    }
    return tok;
  };
  friend std::ostream &operator<<(std::ostream &tok,
                                  const Matrica<TipEl> &mat) {
    int sirina_ispisa = tok.width();
    for (int i = 0; i < mat.br_redova; i++) {
      for (int j = 0; j < mat.br_kolona; j++) {
        tok << std::setw(sirina_ispisa) << mat.elementi[i][j];
      }
      tok << std::endl;
    }
    return tok;
  };
  template <typename Tip2>
  friend Matrica<Tip2> operator+(const Matrica<Tip2> &m1,
                                 const Matrica<Tip2> &m2);
  template <typename Tip2>
  friend Matrica<Tip2> operator-(const Matrica<Tip2> &mat1,
                                 const Matrica<Tip2> &mat2);
  template <typename Tip2>
  friend Matrica<Tip2> operator*(const Matrica<Tip2> &mat1,
                                 const Matrica<Tip2> &mat2);
  template <typename Tip2>
  friend Matrica<Tip2> operator*(const Matrica<Tip2> &mat, double n);
  template <typename Tip2>
  friend Matrica<Tip2> operator*(double n, const Matrica<Tip2> &mat);
  template <typename Tip2>
  friend Matrica<Tip2> &operator+=(Matrica<Tip2> &mat1,
                                   const Matrica<Tip2> &mat2);
  template <typename Tip2>
  friend Matrica<Tip2> &operator-=(Matrica<Tip2> &mat1,
                                   const Matrica<Tip2> &mat2);
  template <typename Tip2>
  friend Matrica<Tip2> &operator*=(Matrica<Tip2> &mat1,
                                   const Matrica<Tip2> &mat2);
  template <typename Tip2>
  friend Matrica<Tip2> &operator*=(Matrica<Tip2> &mat1, int n);
  TipEl *operator[](int x) { return elementi[x]; };
  TipEl *operator[](int x) const { return elementi[x]; };
  TipEl &operator()(int x, int y) {
    if (x < 1 || y < 1)
      throw std::range_error("Neispravan indeks");
    return elementi[x - 1][y - 1];
  };
  TipEl operator()(int x, int y) const {
    if (x < 1 || y < 1)
      throw std::range_error("Neispravan indeks");
    return elementi[x - 1][y - 1];
  };
  operator std::string();

  void SacuvajUTekstualnuDatoteku(std::string ime_datoteke) const;
  void SacuvajUBinarnuDatoteku(std::string ime_datoteke) const;
  void ObnoviIzTekstualneDatoteke(std::string ime_datoteke);
  void ObnoviIzBinarneDatoteke(std::string ime_datoteke);
  Matrica(std::string ime_datoteke, bool d);
};

template <typename TipEl> Matrica<TipEl>::operator std::string() {

  std::stringstream ss;
  ss << "{{";
  for (int i = 0; i < br_redova; i++) {
    for (int j = 0; j < br_kolona; j++) {
      ss << std::fixed << std::setprecision(0) << elementi[i][j];
      if (j != br_kolona - 1)
        ss << ',';
    }
    if (i != br_redova - 1)
      ss << "},{";
  }
  ss << "}}";
  return ss.str();
}

template <typename TipEl2>
Matrica<TipEl2> operator*(const Matrica<TipEl2> &mat1,
                          const Matrica<TipEl2> &mat2) {
  if (mat1.br_kolona != mat2.br_redova)
    throw std::domain_error("Matrice nisu saglasne za mnozenje");

  Matrica<TipEl2> temp(mat1.br_redova, mat2.br_kolona);
  for (int i = 0; i < temp.br_redova; i++) {
    for (int j = 0; j < temp.br_kolona; j++) {
      temp.elementi[i][j] = 0;
    }
  }
  for (int i = 0; i < temp.br_redova; i++) {
    for (int j = 0; j < temp.br_kolona; j++) {

      for (int k = 0; k < mat1.br_kolona; k++)
        temp.elementi[i][j] += mat1.elementi[i][k] * mat2.elementi[k][j];
    }
  }
  return temp;
}
template <typename TipEl>
Matrica<TipEl> operator*(const Matrica<TipEl> &mat, double n) {
  Matrica<TipEl> temp(mat.br_redova, mat.br_kolona);
  for (int i = 0; i < temp.br_redova; i++) {
    for (int j = 0; j < temp.br_kolona; j++)
      temp.elementi[i][j] = mat.elementi[i][j] * n;
  }
  return temp;
}
template <typename TipEl>
Matrica<TipEl> operator*(double n, const Matrica<TipEl> &mat) {
  Matrica<TipEl> temp(mat.br_redova, mat.br_kolona);
  for (int i = 0; i < temp.br_redova; i++) {
    for (int j = 0; j < temp.br_kolona; j++)
      temp.elementi[i][j] = mat.elementi[i][j] * n;
  }
  return temp;
}

template <typename TipEl>
TipEl **Matrica<TipEl>::AlocirajMemoriju(int br_redova, int br_kolona) {
  TipEl **elementi = new TipEl *[br_redova] {};
  try {
    for (int i = 0; i < br_redova; i++)
      elementi[i] = new TipEl[br_kolona];
  } catch (...) {
    DealocirajMemoriju(elementi, br_redova);
    throw;
  }
  return elementi;
}
template <typename TipEl>
void Matrica<TipEl>::DealocirajMemoriju(TipEl **elementi, int br_redova) {
  for (int i = 0; i < br_redova; i++)
    delete[] elementi[i];
  delete[] elementi;
}
template <typename TipEl>
Matrica<TipEl>::Matrica(int br_redova, int br_kolona, char ime)
    : br_redova(br_redova), br_kolona(br_kolona), ime_matrice(ime),
      elementi(AlocirajMemoriju(br_redova, br_kolona)) {}
template <typename TipEl>
void Matrica<TipEl>::KopirajElemente(TipEl **elementi) {
  for (int i = 0; i < br_redova; i++)
    for (int j = 0; j < br_kolona; j++)
      Matrica::elementi[i][j] = elementi[i][j];
}
template <typename TipEl>
Matrica<TipEl>::Matrica(const Matrica<TipEl> &m)
    : br_redova(m.br_redova), br_kolona(m.br_kolona),
      ime_matrice(m.ime_matrice),
      elementi(AlocirajMemoriju(m.br_redova, m.br_kolona)) {
  KopirajElemente(m.elementi);
}
template <typename TipEl>
Matrica<TipEl>::Matrica(Matrica<TipEl> &&m)
    : br_redova(m.br_redova), br_kolona(m.br_kolona), elementi(m.elementi),
      ime_matrice(m.ime_matrice) {
  m.br_redova = 0;
  m.elementi = nullptr;
}
template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator=(const Matrica<TipEl> &m) {
  if (br_redova < m.br_redova || br_kolona < m.br_kolona) {
    TipEl **novi_prostor = AlocirajMemoriju(m.br_redova, m.br_kolona);
    DealocirajMemoriju(elementi, br_redova);
    elementi = novi_prostor;
  } else if (br_redova > m.br_redova)
    for (int i = m.br_redova; i < br_redova; i++)
      delete elementi[i];
  br_redova = m.br_redova;
  br_kolona = m.br_kolona;
  ime_matrice = m.ime_matrice;
  KopirajElemente(m.elementi);
  return *this;
}
template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator=(Matrica<TipEl> &&m) {
  std::swap(br_redova, m.br_redova);
  std::swap(br_kolona, m.br_kolona);
  std::swap(ime_matrice, m.ime_matrice);
  std::swap(elementi, m.elementi);
  return *this;
}
template <typename TipEl>
Matrica<TipEl> operator+(const Matrica<TipEl> &m1, const Matrica<TipEl> &m2) {
  if (m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
    throw std::domain_error("Matrice nemaju jednake dimenzije!");
  Matrica<TipEl> m3(m1.br_redova, m1.br_kolona);
  for (int i = 0; i < m1.br_redova; i++)
    for (int j = 0; j < m1.br_kolona; j++)
      m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
  return m3;
}
template <typename TipEl>
Matrica<TipEl> operator-(const Matrica<TipEl> &mat1,
                         const Matrica<TipEl> &mat2) {
  if (mat1.br_redova != mat2.br_redova || mat1.br_kolona != mat2.br_kolona)
    throw std::domain_error("Matrice nemaju jednake dimenzije!");
  Matrica<TipEl> temp(mat1.br_redova, mat1.br_kolona);
  for (int i = 0; i < temp.br_redova; i++) {
    for (int j = 0; j < temp.br_kolona; j++) {
      temp.elementi[i][j] = mat1.elementi[i][j] - mat2.elementi[i][j];
    }
  }
  return temp;
}

template <typename TipEl>
Matrica<TipEl> &operator+=(Matrica<TipEl> &mat1, const Matrica<TipEl> &mat2) {
  return mat1 = mat1 + mat2; // nije efikasno, ali mi se zuri
}

template <typename TipEl>
Matrica<TipEl> &operator-=(Matrica<TipEl> &mat1, const Matrica<TipEl> &mat2) {
  return mat1 = mat1 - mat2;
}

template <typename TipEl>
Matrica<TipEl> &operator*=(Matrica<TipEl> &mat1, const Matrica<TipEl> &mat2) {
  return mat1 = mat1 * mat2;
}

template <typename TipEl>
Matrica<TipEl> &operator*=(Matrica<TipEl> &mat1, int n) {
  return mat1 = mat1 * n;
}

template <typename TipEl>
void Matrica<TipEl>::SacuvajUTekstualnuDatoteku(
    std::string ime_datoteke) const {

  std::ofstream izlazni_tok(ime_datoteke);
  if (!izlazni_tok)
    throw std::logic_error("Problemi sa upisom u datoteku");

  for (int i = 0; i < br_redova; i++) {

    for (int j = 0; j < br_kolona; j++) {
      izlazni_tok << elementi[i][j];
      if (!izlazni_tok)
        throw std::logic_error("Problemi sa upisom u datoteku");
      if (j != br_kolona - 1)
        izlazni_tok << ",";
    }
    izlazni_tok << std::endl;
  }
  if (!izlazni_tok)
    throw std::logic_error("Problemi sa upisom u datoteku");
  izlazni_tok.close();
}

template <typename TipEl>
void Matrica<TipEl>::SacuvajUBinarnuDatoteku(std::string ime_datoteke) const {

  std::ofstream izlazni_tok(ime_datoteke, std::ios::binary);
  if (!izlazni_tok)
    throw std::logic_error("Problemi sa upisom u datoteku");

  izlazni_tok.write(reinterpret_cast<const char *>(this), sizeof *this);
  if (!izlazni_tok)
    throw std::logic_error("Problemi sa upisom u datoteku");
  for (int i = 0; i < br_redova; i++) {
    for (int j = 0; j < br_kolona; j++) {
      izlazni_tok.write(reinterpret_cast<const char *>(&elementi[i][j]),
                        sizeof elementi[i][j]);
      if (!izlazni_tok)
        throw std::logic_error("Problemi sa upisom u datoteku");
    }
  }
  if (!izlazni_tok)
    throw std::logic_error("Problemi sa upisom u datoteku");
  izlazni_tok.close();
}

template <typename TipEl>
void Matrica<TipEl>::ObnoviIzTekstualneDatoteke(std::string ime_datoteke) {

  std::ifstream ulazni_tok(ime_datoteke);
  if (!ulazni_tok)
    throw std::logic_error("Trazena datoteka ne postoji");

  // provjera dimenzija
  int redovi = 0, kolone = 0, duzina_reda = 0;
  for (;;) {
    TipEl broj;
    ulazni_tok >> broj;
    char znak;
    znak = ulazni_tok.get();
    kolone++;
    if (znak == '\n')
      break;
    if (!ulazni_tok)
      break;
    if (znak != ',' && znak != '\n' && ulazni_tok)
      throw std::logic_error("Datoteka sadrzi besmislene podatke");
    if (znak != ',' && ulazni_tok) {
      if (duzina_reda != br_kolona)
        throw std::logic_error("Datoteka sadrzi besmislene podatke");
      break;
    }
  }
  if (ulazni_tok.eof()) {
    if (redovi != br_redova)
      throw std::logic_error("Datoteka sadrzi besmislene podatke");
  } else if (ulazni_tok.bad())
    throw std::logic_error("Problemi pri citanju datoteke");
  else if (ulazni_tok.eof() == false && ulazni_tok.bad() == false &&
           !ulazni_tok)
    throw std::logic_error("Problemi pri citanju datoteke");
  ulazni_tok.clear();
  ulazni_tok.seekg(0);
  duzina_reda = kolone;
  for (;;) {
    if (kolone != duzina_reda)
      throw std::logic_error("Datoteka sadrzi besmislene podatke");
    duzina_reda = 0;
    char znak;
    for (;;) {
      TipEl broj;
      ulazni_tok >> broj;
      znak = ulazni_tok.get();
      if (!ulazni_tok)
        break;
      if (znak != ',' && znak != '\n' && ulazni_tok)
        throw std::logic_error("Datoteka sadrzi besmislene podatke");
      duzina_reda++;
      if (znak != ',' && ulazni_tok) {
        if (duzina_reda != br_kolona)
          throw std::logic_error("Datoteka sadrzi besmislene podatke");
        break;
      }
    }
    if (!ulazni_tok){
        redovi++;
      break;
    }
    redovi++;
  }
  if (ulazni_tok.eof()) {
    if (redovi != br_redova)
      throw std::logic_error("Datoteka sadrzi besmislene podatke");
  } else if (ulazni_tok.bad())
    throw std::logic_error("Problemi pri citanju datoteke");
  else if (ulazni_tok.eof() == false && ulazni_tok.bad() == false)
    throw std::logic_error("Problemi pri citanju datoteke");

  // datoteka je ispravna,ucitajmo je
  // prvo trebamo unistiti prethodni sadrzaj

  DealocirajMemoriju(elementi, br_redova);
  elementi=AlocirajMemoriju(redovi, kolone);
  br_redova=redovi;
  br_kolona=kolone;
  ulazni_tok.clear();
  ulazni_tok.seekg(0);
  for (int i = 0; i < redovi; i++) {
    for (int j = 0; j < kolone; j++) {
      char znak;
      ulazni_tok >> elementi[i][j];
      znak = ulazni_tok.get();
    }
  }
  ulazni_tok.clear();
  ulazni_tok.close();
}

template <typename TipEl>
void Matrica<TipEl>::ObnoviIzBinarneDatoteke(std::string ime_datoteke) {

  std::ifstream ulazni_tok(ime_datoteke, std::ios::binary);
  if (!ulazni_tok)
    throw std::logic_error("Trazena datoteka ne postoji");

  DealocirajMemoriju(elementi, br_redova);
  ulazni_tok.read(reinterpret_cast<char *>(this), sizeof *this);
  if (!ulazni_tok) {
    throw std::logic_error("Problem pri citanju datoteke");
  } // provjeri je li taj izuzetak
  elementi=AlocirajMemoriju(br_redova, br_kolona);

  for (int i = 0; i < br_redova; i++) {
    for (int j = 0; j < br_kolona; j++) {
      ulazni_tok.read(reinterpret_cast<char *>(&elementi[i][j]),
                      sizeof elementi[i][j]);
      if (!ulazni_tok) {
        throw std::logic_error("Problem pri citanju datoteke");
      } // provjeri je li taj izuzetak
    }
  }
}

template <typename TipEl>
Matrica<TipEl>::Matrica(std::string ime_datoteke, bool d) {

  if (d == false) {

    std::ifstream ulazni_tok(ime_datoteke);
    if (!ulazni_tok)
      throw std::logic_error("Trazena datoteka ne postoji");

    // provjera dimenzija
    int redovi = 0, kolone = 0, duzina_reda = 0;
    for (;;) {
      TipEl broj;
      ulazni_tok >> broj;
      char znak;
      znak = ulazni_tok.get();
      kolone++;
      if (znak == '\n')
        break;
      if (!ulazni_tok)
        break;
      if (znak != ',' && znak != '\n' && ulazni_tok)
        throw std::logic_error("Datoteka sadrzi besmislene podatke");
    }

    if (ulazni_tok.bad())
      throw std::logic_error("Problemi pri citanju datoteke");
    else if (ulazni_tok.eof() == false && ulazni_tok.bad() == false &&
             !ulazni_tok)
      throw std::logic_error("Problemi pri citanju datoteke");
    ulazni_tok.clear();
    ulazni_tok.seekg(0);
    duzina_reda = kolone;
    for (;;) {
      if (kolone != duzina_reda)
        throw std::logic_error("Datoteka sadrzi besmislene podatke");
      duzina_reda = 0;
      char znak;
      for (;;) {
        TipEl broj;
        ulazni_tok >> broj;
        znak = ulazni_tok.get();
        if (!ulazni_tok)
          break;
        if (znak != ',' && znak != '\n' && ulazni_tok)
          throw std::logic_error("Datoteka sadrzi besmislene podatke");
        duzina_reda++;
        if (znak != ',' && ulazni_tok) {
          break;
        }
      }
      if (!ulazni_tok) {
        redovi++;
        break;
      }
      redovi++;
    }
    if (ulazni_tok.bad())
      throw std::logic_error("Problemi pri citanju datoteke");
    else if (ulazni_tok.eof() == false && ulazni_tok.bad() == false)
      throw std::logic_error("Problemi pri citanju datoteke");

    // datoteka je ispravna,ucitajmo je
    // prvo trebamo unistiti prethodni sadrzaj

    elementi=AlocirajMemoriju(redovi, kolone);
    br_redova=redovi;
    br_kolona=kolone;
    ulazni_tok.clear();
    ulazni_tok.seekg(0);
    for (int i = 0; i < redovi; i++) {
      for (int j = 0; j < kolone; j++) {
        char znak;
        ulazni_tok >> elementi[i][j];
        znak = ulazni_tok.get();
      }
    }
    ulazni_tok.clear();
    ulazni_tok.close();

  } else{
      
      std::ifstream tok(ime_datoteke, std::ios::binary);
  if (!tok)
    throw std::logic_error("Trazena datoteka ne postoji");

  tok.read(reinterpret_cast<char *>(this), sizeof *this);
  if (!tok) {
    throw std::logic_error("Problem pri citanju datoteke");
  } // provjeri je li taj izuzetak
  elementi=AlocirajMemoriju(br_redova, br_kolona);

  for (int i = 0; i < br_redova; i++) {
    for (int j = 0; j < br_kolona; j++) {
      tok.read(reinterpret_cast<char *>(&elementi[i][j]),
                      sizeof elementi[i][j]);
      if (!tok) {
        throw std::logic_error("Problem pri citanju datoteke");
      } // provjeri je li taj izuzetak
    }
  }
}
}
int main() {
  int m, n;
  std::cout << "Unesi broj redova i kolona za matrice:\n";
  std::cin >> m >> n;
  Matrica<double> a(m, n, 'A'), b(m, n, 'B');
  std::cout << "Unesi matricu A:\n";
  std::cin >> a;
  a.SacuvajUTekstualnuDatoteku("IZVJESTAJ.TXT");
  b.ObnoviIzTekstualneDatoteke("IZVJESTAJ.TXT");
  std::cout << a << std::endl;
  std::cout << b << std::endl;

  return 0;
}