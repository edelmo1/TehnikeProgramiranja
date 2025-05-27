// TP 2022/2023: Zadaća 3, Zadatak 3
#include <cmath>
#include <iomanip>
#include <iostream>
#include <new>
#include <stdexcept>

template <typename TipElemenata> struct Matrica {
  char ime_matrice;
  int br_redova, br_kolona;
  TipElemenata **elementi = nullptr;
};

template <typename TipElemenata>
void UnistiMatricu(Matrica<TipElemenata> &mat) {
  if (!mat.elementi)
    return;
  for (int i = 0; i < mat.br_redova; i++)
    delete[] mat.elementi[i];
  delete[] mat.elementi;
  mat.elementi = nullptr;
}

template <typename TipElemenata>
Matrica<TipElemenata> StvoriMatricu(int br_redova, int br_kolona,
                                    char ime = 0) {
  Matrica<TipElemenata> mat;
  mat.br_redova = br_redova;
  mat.br_kolona = br_kolona;
  mat.ime_matrice = ime;
  try{
  mat.elementi = new TipElemenata *[br_redova] {};
  try {
    for (int i = 0; i < br_redova; i++)
      mat.elementi[i] = new TipElemenata[br_kolona];
  } catch (...) {
    UnistiMatricu(mat);
    throw;
  }
  }
  catch(std::bad_alloc){
      UnistiMatricu(mat);
      throw;
  }
  return mat;
}

template <typename TipElemenata> void UnesiMatricu(Matrica<TipElemenata> &mat) {
  for (int i = 0; i < mat.br_redova; i++)
    for (int j = 0; j < mat.br_kolona; j++) {
      std::cout << mat.ime_matrice << "(" << i + 1 << "," << j + 1 << ") = ";
      std::cin >> mat.elementi[i][j];
      std::cout<<std::endl;
    }
}

template <typename TipElemenata>
void IspisiMatricu(const Matrica<TipElemenata> &mat, int sirina_ispisa,
                   int preciznost = 6, bool treba_brisati = false) {
  for (int i = 0; i < mat.br_redova; i++) {
    for (int j = 0; j < mat.br_kolona; j++)
      std::cout << std::setw(sirina_ispisa) << std::setprecision(preciznost)
                << mat.elementi[i][j];
    std::cout << std::endl;
  }
  if (treba_brisati == true){
     Matrica<TipElemenata> temp=mat;
    UnistiMatricu(temp);
    }
}

template <typename TipElemenata>
Matrica<TipElemenata> ZbirMatrica(const Matrica<TipElemenata> &m1,
                                  const Matrica<TipElemenata> &m2) {
  if (m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
    throw std::domain_error("Matrice nemaju jednake dimenzije!");
  auto m3 = StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona);
  for (int i = 0; i < m1.br_redova; i++)
    for (int j = 0; j < m1.br_kolona; j++)
      m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
  return m3;
}

// provjeri opet da li treba biti genericka ali trebala bi!!!

template <typename TipElemenata>
Matrica<TipElemenata> ProduktMatrica(const Matrica<TipElemenata> &m1,
                                     const Matrica<TipElemenata> &m2) {

  if (m1.br_kolona != m2.br_redova )
    throw std::domain_error("Matrice nisu saglasne za mnozenje");

  auto m3 = StvoriMatricu<TipElemenata>(m1.br_redova, m2.br_kolona);
  for(int i=0;i<m3.br_redova;i++){
      for(int j=0;j<m3.br_kolona;j++){
          m3.elementi[i][j]=TipElemenata();
      }
  }
  for (int i = 0; i < m3.br_redova; i++) {
    for (int j = 0; j < m3.br_kolona; j++) {
      for (int k = 0; k < m1.br_kolona; k++)
        m3.elementi[i][j] += m1.elementi[i][k] * m2.elementi[k][j];
    }
  }
  return m3;
}

template <typename TipElemenata>
void ProizvodSkalaraIMatrice(Matrica<TipElemenata> &m, double n) {

  for (int i = 0; i < m.br_redova; i++) {
    for (int j = 0; j < m.br_kolona; j++) {
      m.elementi[i][j] *= n;
    }
  }
}

template <typename TipElemenata>
Matrica<TipElemenata> MatricniHarmonijskiPolinom(const Matrica<TipElemenata> &m,
                                                 int n) {

  // provjera za dimenzije, vidi treba li jos neka!!
  if (m.br_redova != m.br_kolona)
    throw std::domain_error("Matrica nije kvadratna");
  if (n < 0)
    throw std::domain_error("Pogresan parametar n");
    Matrica<TipElemenata> suma;
  suma = StvoriMatricu<TipElemenata>(m.br_redova, m.br_kolona);

Matrica<TipElemenata> clan;
  for (int i = 0; i < m.br_redova;
       i++) { // stvorili matricu i sve elemente postavili na podrazum. v
    for (int j = 0; j < m.br_kolona; j++) {
      suma.elementi[i][j] = TipElemenata();
    }
  }
  clan= StvoriMatricu<TipElemenata>(m.br_redova, m.br_kolona);
  
  for (int i = 1; i <= n; i++) {
    for (int i = 0; i < m.br_redova; i++) { // matrica clan=mat(A)
      for (int j = 0; j < m.br_kolona; j++) {
        clan.elementi[i][j] = m.elementi[i][j];
      }
    }
   
    for (int j = 2; j <= i; j++) { // posto je matrica clan=A to polazimo tek od j=2
      Matrica<TipElemenata> temp ;
      try{
      temp=ProduktMatrica(m, clan);
      }
      catch(std::bad_alloc){
          UnistiMatricu(clan);
          UnistiMatricu(suma);
          throw;
      }
      for (int i = 0; i <  clan.br_redova; i++) {
        for (int j = 0; j < clan.br_kolona; j++) {
          clan.elementi[i][j] = temp.elementi[i][j];
        }
      }
      UnistiMatricu(temp);
    }
    ProizvodSkalaraIMatrice(clan, 1. / i);
    
    for (int k = 0; k < m.br_redova; k++) {
      for (int z = 0; z < m.br_kolona; z++) {

        suma.elementi[k][z] += clan.elementi[k][z];
      }
    }
  }
  UnistiMatricu(clan);
  return suma;
}

int main() {

  Matrica<double> a, b;
  int m, red;
  std::cout << "Unesite dimenziju kvadratne matrice: ";
  std::cin >> m;
  std::cout << "Unesite elemente matrice A:\n";
  try {
    a = StvoriMatricu<double>(m, m, 'A');
    UnesiMatricu(a);
   /* std::cout<<"PROVJERA: ";
    IspisiMatricu(ZbirMatrica(a,a),5);*/
   std::cout << "Unesite red polinoma: ";
    std::cin >> red;
    std::cout << "Matricni harmonijski polinom:\n";
    b = MatricniHarmonijskiPolinom(a, red);
    IspisiMatricu(b, 10);
  } catch (std::bad_alloc e) {
    std::cout << e.what()<<std::endl;
  }
  catch(std::domain_error e){
      std::cout << e.what()<<std::endl;
  }
  catch(std::logic_error e){
      std::cout << e.what()<<std::endl;
  }
  UnistiMatricu(a);
  UnistiMatricu(b);
  return 0;
}
