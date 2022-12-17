#include <iostream>
using namespace std;/*opet moram radi testa 4....*/

/*PZ2*/
template <typename Tip> 
struct Cvor {
    Tip element;
    Cvor *sljedeci;
    Cvor() { 
        sljedeci = nullptr; 
    }
    Cvor(const Cvor &c) {
        element = c.element;
        sljedeci = c.sljedeci;
    }
};

template <typename Tip>
class Red {
    int broj_elemenata=0;
    Cvor<Tip> *prvi = nullptr;
    Cvor<Tip> *posljednji = nullptr;
    void TestirajVelicinu(){
        if(broj_elemenata ==0)
            throw std::domain_error("Red je prazan");
    }
public:
    Red(){}
    ~Red(){
        Cvor<Tip> *it = prvi;
        if(it != nullptr){
            while(it->sljedeci != nullptr){
                prvi = prvi->sljedeci;
                delete it;
                it = prvi;
            }
            delete posljednji;
        }
    }
    Red(const Red &red){
        broj_elemenata = red.broj_elemenata;
        if(broj_elemenata == 0)
            return;
        prvi = new Cvor<Tip>(*red.prvi);
        Cvor<Tip> *it = prvi;
        while(it->sljedeci != nullptr){
            it->sljedeci = new Cvor<Tip>(*it->sljedeci);
            it = it->sljedeci;
        }
        posljednji = red.posljednji;
    }
    Red &operator =(const Red &red){
        if(&red != this){
            //brisi();
            Cvor<Tip> *tmp = prvi;
            if(tmp!=nullptr){
                while(tmp->sljedeci != nullptr){
                    prvi = prvi->sljedeci;
                    delete tmp;
                    tmp=prvi;
                }
                delete posljednji;
            }
            broj_elemenata=red.broj_elemenata;
            if(broj_elemenata != 0){
                prvi = new Cvor<Tip>(*red.prvi);
                Cvor<Tip> *it = prvi;
                while(it->sljedeci != nullptr){
                    it->sljedeci = new Cvor<Tip>(*it->sljedeci);
                    it = it->sljedeci;
                }
            }
            else {
                prvi = nullptr;
                posljednji = nullptr;
            }
        }
        return *this;
    }
    Red &operator =(Red &&red){
        if(&red !=this){
            broj_elemenata = red.broj_elemenata;
            posljednji = red.posljednji;
            Cvor<Tip> *it = red.prvi;
            while(it->sljedeci != nullptr){
                red.prvi = red.prvi->sljedeci;
                delete it;
                it = red.prvi;
            }
            prvi = red.prvi;
        }
        return *this;
    }
    void brisi(){
        TestirajVelicinu();
        broj_elemenata=0;
        Cvor<Tip> *it = prvi;
        while(prvi->sljedeci != nullptr){
            prvi = prvi->sljedeci;
            delete it;
            it=prvi;
        }
        delete posljednji;
    }
    void stavi(const Tip &el){
        Cvor<Tip> *novi = new Cvor<Tip>;
        novi->element = el;
        novi->sljedeci=nullptr;
        if(broj_elemenata ==0){
            prvi = novi;
            posljednji = novi;
        }   
        else {
            posljednji->sljedeci = novi;
            posljednji = posljednji->sljedeci;
        }
        broj_elemenata++;
    }
    Tip skini(){
        TestirajVelicinu();
        Tip pocetak = prvi->element;
        Cvor<Tip> *vrh = prvi;
        prvi = prvi->sljedeci;
        delete vrh;
        broj_elemenata--;
        return pocetak;
    }
    Tip &celo(){
        TestirajVelicinu();
        return prvi->element;
    }
    int brojElemenata(){
        return broj_elemenata;
    }
};

void testbrojElemenata()
{
    Red<int> red;
    for(int i = 1; i <=5; i++)
        red.stavi(i);
    std::cout << red.brojElemenata() << std::endl; // treba ispisati 5
}

void teststavi()
{
    Red<int> red;
    for(int i = 1; i <= 10; i++) // treba staviti 5 elemenata u red
        red.stavi(i);
    int br = red.brojElemenata();
    for(int i = 0; i < br; i++) // ispisuje elemente i skida
        std::cout << red.skini() << std::endl;
}

void testskini()
{
    Red<int> red;
    for(int i = 1; i <= 5; i++)
        red.stavi(i);
    std::cout << "Broj elemenata prije izbacivanja: " << red.brojElemenata() << std::endl; // treba ispisati 5
    int br = red.brojElemenata();
    for(int i = 0; i < br ; i++) // treba redom ispisivati elemente
        std::cout << red.skini() << " ";
    std::cout << "Broj elemenata poslije skini: " << red.brojElemenata() << std::endl; // treba ispisati 0
}

void testbrisi()
{
    Red<int> red;
    for(int i = 1; i <= 5; i++)
        red.stavi(i);
    std::cout << "Broj elemenata prije brisanja: " << red.brojElemenata() << std::endl; // treba ispisati 5
    red.brisi();
    std::cout << "Broj elemenata poslije brisanja: " << red.brojElemenata() << std::endl; //treba ispisati 0
}

void testcelo()
{
    Red<int> red;
    for(int i = 1; i <= 5; i++)
        red.stavi(i);
    std::cout << "Celo: " << red.celo() << std:: endl; //treba ispisati 1
}

void testoperatori()
{
    Red<int> red1;
    for(int i =1; i <= 5; i++)
        red1.stavi(i);
    Red<int> red2 = red1;
    int br = red2.brojElemenata();
    for(int i  = 0; i < br; i++)
        std::cout << red2.skini() << std::endl;
}
int main(){
    std::cout << "Pripremna Zadaca Za Vjezbu 4, Zadatak 1" << std::endl;
    std::cout << "Test brisi: ";
    testbrisi();
    std::cout << "Test brojElemenata: ";
    testbrojElemenata();
    std::cout << "Test celo: ";
    testcelo();
    std::cout << "Test operator: ";
    testoperatori();
    std::cout << "Test skini: ";
    testskini();
    std::cout << "Test stavi: ";
    teststavi();
    
    return 0;
}
