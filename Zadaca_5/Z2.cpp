//TP 2022/2023: Zadaća 5, Zadatak 2
#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include <iterator>
#include <algorithm>

class Padavine {
int max_kolicina_padavina;  //MOZDA I NE TREBA STATIC?????
std::vector<int> padavine;  //u cm
public:
explicit Padavine(int max_kolicina_padavina);
void RegistrirajPadavine(int padavina);
int DajBrojRegistriranihPadavina() const {return padavine.size();};
void BrisiSve(){padavine.resize(0);};
int DajMinimalnuKolicinuPadavina() const;
int DajMaksimalnuKolicinuPadavina() const;
int DajBrojDanaSaPadavinamaVecimOd(int padavina) const;  
void Ispisi() const;
int operator [](int i) const {if(i<1 || i>padavine.size()) throw std::range_error("Neispravan indeks");return padavine[i-1];};
Padavine &operator ++();
Padavine operator ++(int);
friend Padavine operator +(const Padavine &X,int Y);
friend Padavine operator +(int Y, const Padavine &X);
friend Padavine operator -(const Padavine &X,int Y);
friend Padavine operator -( int Y, const Padavine &X);
friend Padavine operator -(const Padavine  &X, const Padavine &Y);
//zabrana ostalih oblika x+y i x-y?
Padavine &operator +=(int Y) {return *this=*this+Y;};
//operator += i  nema smisla kada su X i Y padavine?
Padavine &operator -=(int Y){return *this=*this-Y;};
Padavine &operator -=(const Padavine &Y) {return *this=*this-Y;};
friend Padavine operator -(const Padavine &X);
friend bool operator ==(const Padavine &X, const Padavine &Y);
friend bool operator !=(const Padavine &X, const Padavine &Y);
};

//int Padavine::max_kolicina_padavina=0;

//konstruktor
Padavine::Padavine(int max_kolicina_padavina){

if(max_kolicina_padavina<0) throw std::range_error("Ilegalna maksimalna kolicina");
Padavine::max_kolicina_padavina=max_kolicina_padavina;
}

void Padavine::RegistrirajPadavine(int padavina){

if(padavina<0 || padavina>max_kolicina_padavina) throw std::range_error("Ilegalna kolicina padavina");
padavine.push_back(padavina);
}

int Padavine::DajMinimalnuKolicinuPadavina() const{

if(padavine.size()==0) throw std::range_error("Nema registriranih padavina");
auto p=std::min_element(padavine.begin(),padavine.end());
return *p;
}

int Padavine::DajMaksimalnuKolicinuPadavina() const{

if(padavine.size()==0) throw std::range_error("Nema registriranih padavina");
auto p=std::max_element(padavine.begin(),padavine.end());
return *p;
}

int Padavine::DajBrojDanaSaPadavinamaVecimOd(int padavina) const{

if(padavine.size()==0) throw std::range_error("Nema registriranih padavina");
//DODATI OVDJE, VIDI MOZE LI COUNT_IF I GREATER???
int broj=std::count_if(padavine.begin(),padavine.end(),std::bind(std::greater<int>(),std::placeholders::_1,padavina));
return broj;
}

void Padavine::Ispisi() const {

Padavine temp=*this; //??
std::sort(temp.padavine.begin(),temp.padavine.end(),std::greater<int>());
std::copy(temp.padavine.begin(),temp.padavine.end(),std::ostream_iterator<int>(std::cout," "));
}

Padavine &Padavine::operator ++(){

max_kolicina_padavina++;
std::vector<int> v(padavine.size(),1); //za plus 1
std::transform(padavine.begin(),padavine.end(),v.begin(),padavine.begin(),std::plus<int>());  
return *this;
}

Padavine Padavine::operator ++(int){
//temp objekat vracamo, tj stanje prije izmjene
Padavine temp(max_kolicina_padavina);
temp.padavine.resize(padavine.size());
std::copy(padavine.begin(),padavine.end(),temp.padavine.begin());
//sada mijenjamo objekat nad kojim je pozvana
max_kolicina_padavina++;
std::vector<int> v(padavine.size(),1);
std::transform(padavine.begin(),padavine.end(),v.begin(),padavine.begin(),std::plus<int>());
return temp;
}

//X+Y, X-padavine,Y-cijeli broj
Padavine operator +(const Padavine &X,int Y){

Padavine temp(X.max_kolicina_padavina);
temp.max_kolicina_padavina+=Y;            //PROVJERI JE LI MISLI NA POVECANJE SA 1 ILI Y??
temp.padavine.resize(X.padavine.size());
std::vector<int> v(X.padavine.size(),Y);
std::transform(X.padavine.begin(),X.padavine.end(),v.begin(),temp.padavine.begin(),std::plus<int>());
std::vector<int> v2(X.padavine.size(),0);
if(!(std::equal(temp.padavine.begin(),temp.padavine.end(),v2.begin(),std::greater_equal<int>()))) throw std::domain_error("Nekorektan rezultat operacije");

return temp;
}

//Y+X
inline Padavine operator +(int Y, const Padavine &X){
    return X+Y;
}

//X-Y, X-padavine, Y-cijeli broj
Padavine operator -(const Padavine &X,int Y){

Padavine temp(X.max_kolicina_padavina);
temp.max_kolicina_padavina-=Y;            //PROVJERI JE LI MISLI NA SMANJENJE SA 1 ILI Y??
temp.padavine.resize(X.padavine.size());
std::vector<int> v(X.padavine.size(),Y);
std::transform(X.padavine.begin(),X.padavine.end(),v.begin(),temp.padavine.begin(),std::minus<int>());
std::vector<int> v2(X.padavine.size(),0);
if(!(std::equal(temp.padavine.begin(),temp.padavine.end(),v2.begin(),std::greater_equal<int>()))) throw std::domain_error("Nekorektan rezultat operacije");

return temp;
}

//Y-X, Y-int,X-padavine
Padavine operator -( int Y, const Padavine &X){

Padavine temp(Y);
temp.padavine.resize(X.padavine.size());
std::vector<int> v(X.padavine.size(),Y);
std::transform(v.begin(),v.end(),X.padavine.begin(),temp.padavine.begin(),std::minus<int>());
std::vector<int> v2(X.padavine.size(),0);
if(!(std::equal(temp.padavine.begin(),temp.padavine.end(),v2.begin(),std::greater_equal<int>()))) throw std::domain_error("Nekorektan rezultat operacije");

return temp;
}

//X-Y, X,Y-padavine
Padavine operator -(const Padavine  &X, const Padavine &Y){

if(X.padavine.size()!=Y.padavine.size()) throw std::domain_error("Nesaglasni operandi");
if(!(std::equal(X.padavine.begin(),X.padavine.end(),Y.padavine.begin(),std::greater_equal<int>()))) throw std::domain_error("Nesaglasni operandi");
Padavine temp(X.max_kolicina_padavina);
temp.padavine.resize(X.padavine.size());
std::transform(X.padavine.begin(),X.padavine.end(),Y.padavine.begin(),temp.padavine.begin(),std::minus<int>());
return temp;
}

Padavine operator -(const Padavine &X){

Padavine temp(X.max_kolicina_padavina);
temp.padavine.resize(X.padavine.size());
std::vector<int> v(temp.padavine.size(),X.max_kolicina_padavina);
std::transform(v.begin(),v.end(),X.padavine.begin(),temp.padavine.begin(),std::minus<int>());
return temp;
}

bool operator ==(const Padavine &X, const Padavine &Y){

if(X.padavine.size()!=Y.padavine.size()) return false;
if(!(std::equal(Y.padavine.begin(),Y.padavine.end(),X.padavine.begin(),std::equal_to<int>()))) return false;
return true;
}

inline bool operator !=(const Padavine &X, const Padavine &Y){
return !(X==Y);
}







int main ()
{

Padavine p(100);
p.RegistrirajPadavine(20);
p.RegistrirajPadavine(50);
p.RegistrirajPadavine(19);
p.RegistrirajPadavine(77);
p.Ispisi();
std::cout<<"Minimalna kolicina padavia iznosi "<<p.DajMinimalnuKolicinuPadavina()<<", a maksimalna je "<<p.DajMaksimalnuKolicinuPadavina()<<"."<<std::endl;
std::cout<<"Prognoza za iducu sedmicu najavljuje padavine do 40cm, tako da je broj dana sa vecom kolicinom padavina "<<p.DajBrojDanaSaPadavinamaVecimOd(40)<<std::endl;
p+=10;
std::cout<<"Sada minimalna kolicina padavina iznosi "<<p.DajMinimalnuKolicinuPadavina()<<std::endl;
Padavine p2(50);
p2.RegistrirajPadavine(13);
p2.RegistrirajPadavine(22);
p2.RegistrirajPadavine(15);
p2.RegistrirajPadavine(34);
try{
p2=p-p2;
std::cout<<p2.DajBrojDanaSaPadavinamaVecimOd(40)<<std::endl;
}
catch(std::domain_error e){
    std::cout<<e.what()<<std::endl;
}

	return 0;
}
