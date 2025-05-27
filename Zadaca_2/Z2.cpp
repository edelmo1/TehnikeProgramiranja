// TP 2022/2023: Zadaća 2, Zadatak 2
#include <cmath>
#include <iostream>
#include <vector>
bool DaLiJeProst(int n){
    bool prost=true;
    for(int i=2;i<=std::sqrt(n);i++){
     if(n%i==0){
         return false;
     }
    }
    return true;
}
bool DaLiJeSlobodan(int n) {
  std::vector<int> v;
  for (int i = 2; i <= std::sqrt(n); i++) {
    if (n % i == 0) {
      n /= i;
      v.push_back(i);
      i--;
    }
  }

  for (int i = 0; i < v.size(); i++) {
    for (int j = i + 1; j < v.size(); j++) {
      if (v.at(i) == v.at(j)) {
        return false;
      }
    }
  }

  return true;
}

void RastavaBroja(int n, int &p, int &q) {

  if (n == 0) { 
    p = 0, q = 1;
    return;
  }

  bool negativan = false;
  if (n < 0) {
    negativan = true;
    n *= (-1);
  }

  if(DaLiJeProst(n)==true){
      p=n;
      q=1;
      if(negativan==true) p=-p;
      return;
  }
  
  for (int i = 1; i <= n; i++) {
    if (n % i == 0 && DaLiJeSlobodan(i) == true) {
      double provjera = n / i;
      provjera = std::sqrt(provjera);
      if (std::fabs(provjera - int(provjera) < 0.000001)) {
        p = i;
        q = provjera;
        if (negativan == true)
          p =-p;
        return;
      }
    }
  }

}
int main() {

  int n = 0;
  std::cout << "Unesi broj: ";

  if (!(std::cin >> n) || std::cin.peek() != '\n') {
    std::cout << "Neispravan unos!";
    return 0;
  }
  int p = 0, q = 0;
  RastavaBroja(n, p, q);
  std::cout << "\n" << n << " = " << p << "*" << q << "^2\n";

  return 0;
}
