// TP 2022/2023: Zadaća 1, Zadatak 3
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> Matrica;

int DUZINA(int n) {
int broj_cifara_a=0;
while(n!=0){
    n=n/10;
    broj_cifara_a++;
}
return broj_cifara_a;
}

int NajvecaSirina(Matrica m){
if(m.size()==0) {
    return 0;
}

int broj_redova = m.size(), broj_kolona=0 , broj_cifara_max=0;
for(int i=0 ; i<broj_redova ; i++) {

broj_kolona=m.at(i).size();
for(int j=0 ; j<broj_kolona ; j++) {
    if(DUZINA(m.at(i).at(j))>=broj_cifara_max){
        broj_cifara_max=DUZINA(m.at(i).at(j));
        if(m.at(i).at(j)<0) {
            broj_cifara_max++;
        }
    }
}
}
return broj_cifara_max;
}

Matrica KreirajSpiralnuMatricu(int M, int N, int k, bool vrsta) {

  Matrica m;
  if (M <= 0 || N <= 0) {
    return m;
  } else {
    m.resize(M);
    for (int i = 0; i < M; i++) {
      m.at(i).resize(N);
    }
  }

  int kolona1 = 0, kolona2 = N - 1, red1 = 0, red2 = M - 1;
  int brojac = 0, broj_max = M * N, uslov = k;

  if (vrsta == true) {

    while (k <= (M * N + uslov - 1)) {

      for (int i = kolona1; i < kolona2; i++) {
        m.at(red1).at(i) = k;
        k++;
        brojac++;
        if (brojac == broj_max) {
          return m;
        }
      }

      for (int i = red1; i < red2; i++) {
        m.at(i).at(kolona2) = k;
        k++;
        brojac++;
        if (brojac == broj_max) {
          return m;
        }
      }

      for (int i = kolona2; i > kolona1; i--) {
        m.at(red2).at(i) = k;
        k++;
        brojac++;
        if (brojac == broj_max) {
          return m;
        }
      }

      for (int i = red2; i > red1; i--) {
        m.at(i).at(kolona1) = k;
        k++;
        brojac++;
        if (brojac == broj_max) {
          return m;
        }
      }
      if (red1 == red2 && kolona1 == kolona2) {
        m.at(red1).at(kolona1) = k;
        k++;
        brojac++;
        if (brojac == broj_max) {
          return m;
        }
      }
      red1++;
      red2--;
      kolona1++;
      kolona2--;
    }
  } else if (vrsta == false) {

    while (k <= (M * N + uslov - 1)) {

      for (int i = red1; i < red2; i++) {
        m.at(i).at(kolona1) = k;
        k++;
        brojac++;
        if (brojac == broj_max)
          return m;
      }

      for (int i = kolona1; i < kolona2; i++) {
        m.at(red2).at(i) = k;
        k++;
        brojac++;
        if (brojac == broj_max)
          return m;
      }

      for (int i = red2; i > red1; i--) {
        m.at(i).at(kolona2) = k;
        k++;
        brojac++;
        if (brojac == broj_max)
          return m;
      }

      for (int i = kolona2; i > kolona1; i--) {
        m.at(red1).at(i) = k;
        k++;
        brojac++;
        if (brojac == broj_max)
          return m;
      }

    if(red1==red2 && kolona1==kolona2) {
        m.at(red1).at(kolona1)=k;
        k++;
        brojac++;
        if(brojac==broj_max) return m;
    }


      red1++;
      red2--;
      kolona1++;
      kolona2--;
    }
  }

  return m;
}

bool DaLiJeSpiralnaMatrica (Matrica m){


int M=m.size();

//test grbave matrice
for(int i=0 ; i<M ; i++){
    if(m.at(i).size()!=m.at(0).size()){
        return false;
    }
}
 
int razlika_desno=m.at(0).at(1)-m.at(0).at(0) ;
int razlika_lijevo=m.at(1).at(0)-m.at(0).at(0);
int N=m.at(0).size();
int kolona1 = 0, kolona2 = N - 1, red1 = 0, red2 = M - 1;
bool nije_desna=false , nije_lijeva=false;
int k=m.at(0).at(0);
int uslov=k;
bool centar=false,pozitivna=false;
if(m.at(0).at(0)>=0) {
    pozitivna=true;
}

while(centar!=true){
for(int i=kolona1 ; i<kolona2 ; i++){
    if(m.at(red1).at(i+1)-m.at(red1).at(i)!=razlika_desno || (pozitivna==true && m.at(red1).at(i)<0)){
        nije_desna=true;
        break;
    }
}
if(nije_desna==true) break;
for(int i=red1;i<red2 ; i++){
    if(m.at(i+1).at(kolona2)-m.at(i).at(kolona2)!=razlika_desno || (pozitivna==true && m.at(i).at(kolona2)<0)){
        nije_desna=true;
        break;
    }
}
if(nije_desna==true) break;

for(int i=kolona2 ; i>kolona1 ; i--){
    if(m.at(red2).at(i-1)-m.at(red2).at(i)!=razlika_desno || (pozitivna==true && m.at(red2).at(i)<0)){
        nije_desna=true;
        break;
    }
}
if(nije_desna==true) break;

for(int i=red2 ; i>red1 ; i--){
    if(m.at(i-1).at(kolona1)-m.at(i).at(kolona1)!=razlika_desno && i>red1+1 || (pozitivna==true && m.at(i).at(kolona1)<0)){
        nije_desna=true;
        break;
    }
}
if(nije_desna==true) break;

if(red1==red2 && kolona1==kolona2){
   centar=true;
   if(m.at(red1).at(kolona1)!=M*N+uslov-1 || (pozitivna==true && m.at(red1).at(kolona1)<0)) {
       nije_desna=true;
       break;
   }
   else if(red1>red2 && kolona1>kolona2) {
       break;
   }
}
red1++;
red2--;
kolona1++;
kolona2--;
}

centar=false;
red1=0;
red2=M-1;
kolona1=0;
kolona2=N-1;
while(centar!=true){
    for(int i=red1;i<red2;i++){
        if(m.at(i+1).at(kolona1)-m.at(i).at(kolona1)!=razlika_lijevo || (pozitivna==true && m.at(i).at(kolona1)<0)){
            nije_lijeva=true;
            break;
        }
    }
if(nije_lijeva==true)break;
for(int i=kolona1 ; i<kolona2 ; i++){
    if(m.at(red2).at(i+1)-m.at(red2).at(i)!=razlika_lijevo || (pozitivna==true && m.at(red2).at(i)<0)){
        nije_lijeva=true;
    break;
    }
}
if(nije_lijeva==true)break;
for(int i=red2 ; i>red1 ; i--){
    if(m.at(i-1).at(kolona2)-m.at(i).at(kolona2)!=razlika_lijevo || (pozitivna==true && m.at(i).at(kolona2)<0)){
        nije_lijeva=true;
        break;
    }
}
if(nije_lijeva==true)break;
for(int i=kolona2 ; i>kolona1 ; i--){
    if(m.at(red1).at(i-1)-m.at(red1).at(i)!=razlika_lijevo && i>kolona1+1 || (pozitivna==true && m.at(red1).at(i)<0)){
        nije_lijeva=true;
        break;
    }
    if(nije_lijeva==true)break;

    if(red1==red2 && kolona1==kolona2 ){
        centar=true;
        if(m.at(red1).at(kolona1)!=M*N+uslov-1 || (pozitivna==true && m.at(red1).at(kolona1)<0)){
            nije_lijeva=true;
        }
        else if(red1>red2 && kolona1>kolona2){
            break;
        }
    }
red1++;
red2--;
kolona1++;
kolona2--;
}
}


if(nije_desna==true && nije_lijeva==true){
    return false;
}
return true;
}


int main() {

int M,N;
std::cout<<"Unesite broj redova i kolona matrice: ";
std::cin>>M>>N;

if(M<0 || N<0){
    std::cout<<"Neispravne dimenzije matrice!\n";
    return 0;
}
//vidi treba li i za M=0 ili N=0 neispravan unos
int k;
std::cout<<"Unesite pocetnu vrijednost: ";
std::cin>>k;

char slovo;
std::cout<<"Unesite L za lijevu, a D za desnu spiralnu matricu: ";
std::cin>>slovo;

Matrica m;
std::cout<<"\nKreirana spiralna matrica:\n";
if(slovo=='L'){
    m=KreirajSpiralnuMatricu(M,N,k,false);
}
else if(slovo=='D'){
     m=KreirajSpiralnuMatricu(M,N,k,true);
}
else {
    std::cout<<"Neispravan unos!\n";
    return 0;
}

for(int i=0 ; i<M ; i++) {
    for(int j=0 ; j<N ; j++) {
std::cout<<std::setw(NajvecaSirina(m)+1)<<m.at(i).at(j);
    }
    std::cout<<std::endl;
}

  return 0;
}
 