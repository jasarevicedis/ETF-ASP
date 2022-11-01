/*
Napisati funkciju:
int presjek(Stek<Tip> s1, Stek<Tip> s2)
koja prima dva sortirana generička steka (tako da se na vrhu steka nalazi najmanji element), a vraća
broj elemenata u njihovom presjeku odnosno broj elemenata koji se javljaju u oba steka.
Pretpostaviti da se elementi ne ponavljaju u istom steku.
Primjer: Neka su u prvom steku elementi A C D F, a u drugom B C D E F G. Funkcija treba vratiti
broj 3 pošto postoje tri elementa koji se nalaze u oba steka (a to su C D F).
*/
#include <iostream>

template <typename Tip> 
class Cvor {
public:
    Tip element;
    Cvor *sljedeci;
    Cvor(){ sljedeci = nullptr; }
    Cvor(const Cvor &cvor){
        element = cvor.element;
        sljedeci = cvor.sljedeci;
    }
    Cvor(const Tip &el, Cvor *s): element(el), sljedeci(s) {};
};

template <typename Tip>
class Stek {
    Cvor<Tip> *peek = nullptr; //vrh je zauzeto za metodu
    int vel = 0;
public:
    Stek(){};
    Stek(const Stek &s){
        vel = s.vel;
        Cvor<Tip> *p1;
        Cvor<Tip> *p2 = s.peek;
        peek=0;
        while(p2 != 0){
            Cvor<Tip> *n = new Cvor<Tip>(p2->element, 0);
            if(peek == 0)
                peek = n;
            else
                p1->sljedeci = n;
            p1 =n;
            p2 = p2->sljedeci;
        }
    }
    ~Stek(){
        brisi();
        delete peek;
    }
    Stek &operator =(const Stek &s){
        vel = s.vel;
        if(&s == this)
            return *this;
        brisi();
        Cvor<Tip> *p1;
        Cvor<Tip> *p2 = s.peek;
        peek=0;
        while(p2 != 0){
            Cvor<Tip> *n = new Cvor<Tip>(p2->element, 0);
            if(peek == 0)
                peek = n;
            else
                p1->sljedeci = n;
            p1 =n;
            p2 = p2->sljedeci;
        }
        return *this;
    }
    
    /*Brise sve elemente iz steka */
    void brisi(){
        while(peek != 0)
            skini();
    }
    /*Stavlja elemenet na vrh steka */
    void stavi(const Tip& el){
        Cvor<Tip> *n = new Cvor<Tip>(el,peek);
        peek = n;
        vel++;
    }
    /*Vraca vrh steka i ujedno ga brise */
    Tip skini(){
        if(peek == nullptr)
            throw("Stek je prazan");
        Tip el = peek->element;
        Cvor<Tip> *n = peek->sljedeci;
        delete peek;
        peek = n;
        vel--;
        return el;
    }
    /*Vraca referencu na vrh steka, ali ga ne brise */
    Tip &vrh(){
        if(peek == 0)
            throw("Stek je prazan");
        return peek->element;
    }
    int brojElemenata(){
        return vel;
    }
};

template <typename Tip>
void Kopiraj(Stek<Tip>s, Stek<Tip> &tmp){
    auto el = s.skini();
    tmp.stavi(el);
}
template <typename Tip>
int presjek(Stek<Tip> s1, Stek<Tip> s2){
    int brojac_presjeka(0);
    Tip el1=s1.skini();
    while(el1!= 0){
        Stek<Tip> tmp;
        Kopiraj(s2,tmp);
        Tip el2 = tmp.skini();
        while(el2 != 0 ){
            if(el1 == el2){
                brojac_presjeka++;
                break;
            }
            el2 = tmp.skini();
        }
    }
    return brojac_presjeka;
}
int main(){
    Stek<int> s1;
    Stek<int> s2;
    s1.stavi(1);
    s1.stavi(3); 
    s1.stavi(2); 
    s1.stavi(5); 

    s2.stavi(1); 
    s2.stavi(4); 
    s2.stavi(3); 
    std::cout << presjek(s1,s2);
}
