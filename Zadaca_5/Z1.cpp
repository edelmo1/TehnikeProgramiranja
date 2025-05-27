//TP 2022/2023: Zadaća 5, Zadatak 1
#include <iostream>
#include <cmath>
#include <tuple>
#include <stdexcept>
#include <complex>

class Sinusoida {

double amplituda;
double frekvencija; //SVE SE ZADAJU U RADIJANIMA
double faza;
public:
Sinusoida(double amplituda,double frekvencija,double faza);
double DajAmplitudu() const {return amplituda;};
double DajFrekvenciju() const {return frekvencija;};     //PROVJERI DA LI TREBAJU DVIJE VERZIJE OVIH F-JA, TJ REFERENCA
double DajFazu() const {return faza;};
std::tuple<double,double,double> DajParametre() const {return {amplituda,frekvencija,faza};};
Sinusoida &PostaviAmplitudu(double A);
Sinusoida&PostaviFrekvenciju(double f);
Sinusoida &PostaviFazu(double f);
Sinusoida &PostaviParametre(std::tuple<double,double,double> trojka);
friend Sinusoida operator +(const Sinusoida &s1, const Sinusoida &s2);
friend Sinusoida operator -(const Sinusoida &s1, const Sinusoida &s2);
friend Sinusoida operator -(const Sinusoida &s);
friend Sinusoida operator *(const Sinusoida &s, double n);
friend Sinusoida operator *(double n, const Sinusoida &s);
friend Sinusoida operator /(const Sinusoida &s, double n);
friend Sinusoida &operator +=(Sinusoida &s1, const Sinusoida &s2);
friend Sinusoida &operator -=(Sinusoida &s1, const Sinusoida &s2);
friend Sinusoida &operator *=(Sinusoida &s,double n);
friend Sinusoida &operator /=(Sinusoida &s,double n);
double operator [] (std::string s) const;
double &operator [] (std::string s);
double operator ()(double t);
};

//konstruktor
Sinusoida::Sinusoida(double amplituda,double frekvencija,double faza):amplituda(amplituda),frekvencija(frekvencija),faza(faza){
double PI=4*atan(1);
if(this->frekvencija<0){
    this->frekvencija=-this->frekvencija;
    this->faza=-this->faza;
    this->amplituda=-this->amplituda;
}
if(this->amplituda<0){
    this->amplituda=-this->amplituda;
    this->faza-=PI;
}
if(this->faza+PI<0){ //ako je manja od -pi
for(;;){
    if(this->faza+PI>0) break;
    this->faza+=2*PI;
}
}
if(this->faza-PI>0){
    for(;;){
        if(this->faza-PI<0)break;
        this->faza-=2*PI;
    }
}
}

Sinusoida &Sinusoida::PostaviAmplitudu(double A){
double PI=4*atan(1);
amplituda=A;
if(amplituda<0){
    amplituda=-amplituda;
    faza-=PI;
}
return *this;
}

Sinusoida &Sinusoida::PostaviFrekvenciju(double f){
double PI=4*atan(1);
frekvencija=f;
if(frekvencija<0){
    frekvencija=-frekvencija;
    faza=-faza;
    amplituda=-amplituda;
}
if(amplituda<0){
    amplituda=-amplituda;
    faza-=PI;
}
return *this;
}

Sinusoida &Sinusoida::PostaviFazu(double f){
double PI=4*atan(1);
faza=f;
if(faza+PI<0){ //ako je manja od -pi
for(;;){
    if(faza+PI>0) break;
    faza+=2*PI;
}
}
if(faza-PI>0){
    for(;;){
        if(faza-PI<0)break;
        faza-=2*PI;
    }
}
return *this;
}

Sinusoida &Sinusoida::PostaviParametre(std::tuple<double,double,double> trojka){

PostaviAmplitudu(std::get<0>(trojka));
PostaviFrekvenciju(std::get<1>(trojka));
PostaviFazu(std::get<2>(trojka));
return *this;
}

//operator +
Sinusoida operator +(const Sinusoida &s1, const Sinusoida &s2){

double EPSILON=1e-10;
if(std::fabs(s1.frekvencija-s2.frekvencija)>EPSILON) throw std::domain_error("Razlicite frekvencije");

std::complex<double> z1=std::polar(s1.amplituda,s1.faza);
std::complex<double> z2=std::polar(s2.amplituda,s2.faza);
std::complex<double> z3=z1+z2;
Sinusoida s(std::abs(z3),s1.frekvencija,std::arg(z3));
s.PostaviAmplitudu(s.amplituda);
s.PostaviFrekvenciju(s.frekvencija);
s.PostaviFazu(s.faza);
return s;
}

//operator -
Sinusoida operator -(const Sinusoida &s1, const Sinusoida &s2){

double EPSILON=1e-10;
if(std::fabs(s1.frekvencija-s2.frekvencija)>EPSILON) throw std::domain_error("Razlicite frekvencije");

std::complex<double> z1=std::polar(s1.amplituda,s1.faza);
std::complex<double> z2=std::polar(s2.amplituda,s2.faza);
std::complex<double> z3=z1-z2;
Sinusoida s(std::abs(z3),s1.frekvencija,std::arg(z3));
s.PostaviAmplitudu(s.amplituda);
s.PostaviFrekvenciju(s.frekvencija);
s.PostaviFazu(s.faza);
return s;
}

Sinusoida operator -(const Sinusoida &s){

Sinusoida temp(-s.amplituda,s.frekvencija,s.faza);
/*temp.amplituda=-temp.amplituda;
temp.PostaviAmplitudu(s.amplituda);
temp.PostaviFrekvenciju(s.frekvencija);
temp.PostaviFazu(s.faza);*/
return temp;
}

Sinusoida operator *(const Sinusoida &s, double n){

Sinusoida temp(n*s.amplituda,s.frekvencija,s.faza);
return temp;
}


inline Sinusoida operator *(double n, const Sinusoida &s){  //ako slucajno ne bude radilo posebno otkucaj
    return s*n;  
}

Sinusoida operator /(const Sinusoida &s, double n){

Sinusoida temp(s.amplituda/n,s.frekvencija,s.faza);

return temp;
}

Sinusoida &operator +=(Sinusoida &s1, const Sinusoida &s2){
    
double EPSILON=1e-10;
if(std::fabs(s1.frekvencija-s2.frekvencija)>EPSILON) throw std::domain_error("Razlicite frekvencije");

std::complex<double> z1=std::polar(s1.amplituda,s1.faza);
std::complex<double> z2=std::polar(s2.amplituda,s2.faza);
std::complex<double> z3=z1+z2;
s1.amplituda=std::abs(z3);
s1.faza=std::arg(z3);
s1.PostaviAmplitudu(s1.amplituda);
s1.PostaviFrekvenciju(s1.frekvencija);
s1.PostaviFazu(s1.faza);
return s1;
}

Sinusoida &operator -=(Sinusoida &s1, const Sinusoida &s2){
    double EPSILON=1e-10;
if(std::fabs(s1.frekvencija-s2.frekvencija)>EPSILON) throw std::domain_error("Razlicite frekvencije");

std::complex<double> z1=std::polar(s1.amplituda,s1.faza);
std::complex<double> z2=std::polar(s2.amplituda,s2.faza);
std::complex<double> z3=z1-z2;
s1.amplituda=std::abs(z3);
s1.faza=std::arg(z3);
s1.PostaviAmplitudu(s1.amplituda);
s1.PostaviFrekvenciju(s1.frekvencija);
s1.PostaviFazu(s1.faza);
return s1;
}

Sinusoida &operator *=(Sinusoida &s,double n){

s.amplituda*=n;
s.PostaviAmplitudu(s.amplituda);
s.PostaviFrekvenciju(s.frekvencija);
s.PostaviFazu(s.faza);
return s;
}

Sinusoida &operator /=(Sinusoida &s,double n){

s.amplituda/=n;
s.PostaviAmplitudu(s.amplituda);
s.PostaviFrekvenciju(s.frekvencija);
s.PostaviFazu(s.faza);
return s;
}

double &Sinusoida::operator [](std::string s) {

if(s!="A" && s!="omega" && s!="phi" && s!="w" && s!="fi") throw std::domain_error("Neispravan naziv parametra");

if(s=="omega" || s=="w") return frekvencija;
if(s=="phi" || s=="fi") return faza;
return amplituda;
}

double Sinusoida::operator [](std::string s)const {

if(s!="A" && s!="omega" && s!="phi" && s!="w" && s!="fi") throw std::domain_error("Neispravan naziv parametra");

if(s=="omega" || s=="w") return frekvencija;
if(s=="phi" || s=="fi") return faza;
return amplituda;
}


double Sinusoida::operator ()(double t){
return amplituda*std::sin(frekvencija*t + faza);
}


int main ()
{
Sinusoida s(5,3.14,3.14);
std::cout<<"Pocetno stanje sinusoide je:\n";
std::cout<<"Amplituda: "<<s.DajAmplitudu()<<std::endl;
std::cout<<"Frekvencija: "<<s.DajFrekvenciju()<<std::endl;
std::cout<<"Faza: "<<s.DajFazu()<<std::endl;
s.PostaviAmplitudu(1);
s.PostaviFrekvenciju(1.57);
s.PostaviFazu(6.28);
std::cout<<"Sada stanje nakon izmjene iznosi: \n";
std::cout<<"Amplituda: "<<s["A"]<<std::endl;
std::cout<<"Frekvencija: "<<s["omega"]<<std::endl;
std::cout<<"Faza: "<<s["fi"]<<std::endl;



	return 0;
}
