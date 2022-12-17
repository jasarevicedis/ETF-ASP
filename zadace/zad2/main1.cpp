#include <iostream>

template <typename Tip>
class Lista
{
public:
    virtual ~Lista() {};
    virtual int brojElemenata() const = 0;
    virtual Tip &trenutni() = 0;
    virtual Tip trenutni() const = 0;
    virtual bool prethodni() = 0;
    virtual bool sljedeci() = 0;
    virtual void pocetak() = 0;
    virtual void kraj() = 0;
    virtual void obrisi() = 0;
    virtual void dodajIspred(const Tip& el) = 0;
    virtual void dodajIza(const Tip& el) = 0;
    virtual Tip &operator [](int i) = 0;
    virtual Tip operator [](int i) const = 0;
};

template<typename Tip>
class Cvor
{
public:
    Tip element;
    Cvor *prethodni;
    Cvor *sljedeci;
    Cvor()
    {
        prethodni = nullptr;
        sljedeci = nullptr;
    }

    Cvor(const Cvor &c)
    {
        element = c.element;
        prethodni = c.prethodni;
        sljedeci = c.sljedeci;
    }
};

template<typename Tip>
class DvostrukaLista : public Lista<Tip>
{
private:
    int broj_elemenata = 0;
    Cvor<Tip> *poc = nullptr;
    Cvor<Tip> *posljednji = nullptr;
    Cvor<Tip> *tekuci = nullptr;
public:
    DvostrukaLista() {}

    DvostrukaLista(const DvostrukaLista<Tip> &l)
    {
        broj_elemenata = l.broj_elemenata;
        if(broj_elemenata == 0) return;
        poc = new Cvor<Tip>(*l.poc);
        Cvor<Tip> *pom = poc;
        Cvor<Tip> *pr = nullptr;
        while(pom->sljedeci != nullptr) {
            pom->sljedeci = new Cvor<Tip>(*pom->sljedeci);
            pom->prethodni = pr;
            pr = pom;
            pom = pom->sljedeci;
        }
        posljednji = pom;
        //tekuci = poc;
    }

    DvostrukaLista(DvostrukaLista<Tip> &&dl)
    {
        broj_elemenata = dl.broj_elemenata;
        poc = dl.poc;
        posljednji = dl.posljednji;
        tekuci = dl.tekuci;
        dl.broj_elemenata = 0;
        dl.poc = nullptr;
        dl.tekuci = nullptr;
        dl.posljednji = nullptr;
    }

    ~DvostrukaLista()
    {
        Cvor<Tip> *pom = poc;
        Cvor<Tip> *pom2 = poc;
        while(pom != nullptr) {
            pom2 = pom->sljedeci;
            delete pom;
            pom = pom2;
        }
    }

    DvostrukaLista &operator =(const DvostrukaLista<Tip> &dl)
    {
        if(&dl != this) {
            Cvor<Tip> *pom = poc;
            while(pom != nullptr) {
                poc = pom->sljedeci;
                delete pom;
                pom = poc;
            }

            broj_elemenata = dl.broj_elemenata;
            if(broj_elemenata != 0) {
                poc = new Cvor<Tip>(*dl.poc);
                Cvor<Tip> *pom2 = poc;
                Cvor<Tip> *pr = nullptr;
                while (pom2->sljedeci != nullptr) {
                    pom2->sljedeci = new Cvor<Tip>(*pom2->sljedeci);
                    pom2->prethodni = pr;
                    pr = pom2;
                    pom2 = pom2->sljedeci;
                }
                posljednji = pom2;
            } else {
                poc = nullptr;
                tekuci = nullptr;
                posljednji = nullptr;
            }
        }

        return *this;
    }

    DvostrukaLista &operator =(DvostrukaLista<Tip> &&dl)
    {
        if(&dl != this) {
            broj_elemenata = dl.broj_elemenata;
            tekuci = dl.tekuci;
            Cvor<Tip> *pom = poc;
            while(pom != nullptr) {
                poc = poc->sljedeci;
                delete pom;
                pom = poc;
            }
            poc = dl.poc;
            posljednji = dl.posljednji;
        }
        return *this;
    }

    int brojElemenata() const
    {
        return broj_elemenata;
    }

    Tip &trenutni()
    {
        if(broj_elemenata == 0) throw std::domain_error("Lista je prazna");
        return tekuci->element;
    }

    Tip trenutni() const
    {
        if(broj_elemenata == 0) throw std::domain_error("Lista je prazna");
        return tekuci->element;
    }

    bool prethodni()
    {
        if(broj_elemenata == 0) throw std::domain_error("Lista je prazna");
        if(tekuci == poc) return false;
        tekuci = tekuci->prethodni;
        return true;
    }

    bool sljedeci()
    {
        if(broj_elemenata == 0) throw std::domain_error("Lista je prazna");
        if(tekuci->sljedeci == nullptr) return false;
        tekuci = tekuci->sljedeci;
        return true;
    }

    void pocetak()
    {
        if(broj_elemenata == 0) throw std::domain_error("Lista je prazna");
        tekuci = poc;
    }

    void kraj()
    {
        if(broj_elemenata == 0) throw std::domain_error("Lista je prazna");
        tekuci = posljednji;
    }

    void obrisi()
    {
        if(broj_elemenata == 0) throw std::domain_error("Lista je prazna");
        if(poc == tekuci) {
            Cvor<Tip> *pom = poc;
            poc = poc->sljedeci;
            delete pom;
            tekuci = poc;
        } else {
            Cvor<Tip> *pom = tekuci->prethodni;
            pom->sljedeci = tekuci->sljedeci;
            delete tekuci;
            if(pom->sljedeci != nullptr) tekuci = pom->sljedeci;
            else {
                tekuci = pom;
                posljednji = pom;
            }
        }
        broj_elemenata--;
    }

    void dodajIspred(const Tip& el)
    {
        if(poc == tekuci) {
            Cvor<Tip> *pom = new Cvor<Tip>;
            pom->element = el;
            pom->sljedeci = poc;
            if(broj_elemenata != 0) poc->prethodni = pom;
            poc = pom;
            if(tekuci == nullptr) {
                tekuci = poc;
                posljednji = poc;
            }
        } else {
            Cvor<Tip> *p = new Cvor<Tip>;
            p->element = el;
            tekuci->prethodni->sljedeci = p;
            p->prethodni = tekuci->prethodni;
            tekuci->prethodni = p;
            p->sljedeci = tekuci;
        }
        broj_elemenata++;
    }

    void dodajIza(const Tip& el)
    {
        if(broj_elemenata == 0) {
            Cvor<Tip> *p = new Cvor<Tip>;
            p->element = el;
            poc = p;
            tekuci = poc;
            posljednji = poc;
        } else {
            Cvor<Tip> *p = tekuci->sljedeci;
            tekuci->sljedeci = new Cvor<Tip>;
            tekuci->sljedeci->element = el;
            tekuci->sljedeci->sljedeci = p;
            tekuci->sljedeci->prethodni = tekuci;
            if(tekuci == posljednji) 
                posljednji= tekuci->sljedeci;
            if(p != nullptr)
                p->prethodni = tekuci->sljedeci;
        }
        broj_elemenata++;

    }

    Tip &operator [](int i)
    {
        Cvor<Tip> *pom = poc;
        for(int j = 0; j < i; j++)
            pom = pom->sljedeci;
        return pom->element;
    }

    Tip operator [] (int i) const
    {
        Cvor<Tip> *pom = poc;
        for(int j = 0; j < i; j++)
            pom = pom->sljedeci;
        return pom->element;
    }

};

/*KLASA KOJA SE TRAZI */
template <typename Tip>
class DvostraniRed {
    DvostrukaLista<Tip> elementi;
public:
    DvostraniRed(){};
    ~DvostraniRed(){}
    DvostraniRed(const DvostraniRed<Tip> &dr): elementi(dr.elementi){}
    DvostraniRed &operator =(const DvostraniRed &dr){
        elementi = dr.elementi;
        return *this;
    }
    DvostraniRed &operator =(DvostraniRed &&dr){
        elementi = dr.elementi;
        return *this;
    }
    
    int brojElemenata(){
        return elementi.brojElemenata();
    }
    void staviNaCelo(const Tip &el){
        if(elementi.brojElemenata() != 0)
            elementi.kraj();//stavlja tekuci na posljednji
        elementi.dodajIza(el);
    }
    Tip skiniSaCela(){
        if(elementi.brojElemenata() != 0)
            elementi.kraj();//stavlja tekuci na posljednji
        Tip el = elementi.trenutni();
        elementi.obrisi();//brise trenutni
        return el;
    }
    void staviNaVrh(const Tip &el){
        if(elementi.brojElemenata() != 0)
            elementi.pocetak();
        elementi.dodajIspred(el);
    }
    Tip skiniSaVrha(){
        if(elementi.brojElemenata() != 0)
            elementi.pocetak();
        Tip el = elementi.trenutni();
        elementi.obrisi();
        return el;
    }
    Tip &celo(){
        if(elementi.brojElemenata() != 0)
            elementi.kraj();
        return elementi.trenutni();
    }
    Tip vrh(){
        if(elementi.brojElemenata() != 0)
            elementi.pocetak();
        return elementi.trenutni();
    }
    void brisi(){
        while(elementi.brojElemenata() != 0)
            elementi.obrisi();
    }
};

/*UNIT TESTOVI ZA SVAKU METODU*/
void brisiTest()
{
    DvostraniRed<int> dr;
    for(int i = 1; i <= 10; i++)
        dr.staviNaCelo(i);
    std::cout << "Prije brisanja: " << dr.brojElemenata() << std::endl; 
    dr.brisi();
    std::cout << "Poslije brisanja: " << dr.brojElemenata() << std::endl; 
}

void staviNaCeloTest()
{
    DvostraniRed<int> dr;
    for(int i = 1; i<=10; i++)
        dr.staviNaCelo(i);
    std::cout << "5 stavljanja na celo: " << dr.brojElemenata() << std::endl; 
}

void staviNaVrhTest()
{
    DvostraniRed<int> dr;
    for(int i = 1; i <= 10; i++)
        dr.staviNaVrh(i);
    std::cout << " 5 stavljanja na vrh: " << dr.brojElemenata() << std::endl; 
}

void skiniSaCelaTest()
{
    DvostraniRed<int> dr;
    for(int i  = 1; i <= 5; i++)
        dr.staviNaCelo(i);
    std::cout << "Broj elemenata prije skidanja sa cela: " << dr.brojElemenata() << std::endl; 
    std::cout << "Skini sa cela: " << dr.skiniSaCela() << std::endl; 
    std::cout << "Broj elemenata poslije skidanja sa cela: " << dr.brojElemenata() <<std::endl; 
}

void skiniSaVrhaTest(){
    DvostraniRed<int> dr;
    for(int i = 1; i <= 5; i++)
        dr.staviNaCelo(i);
    std::cout << "Broj elemenata prije skidanja sa vrha: " << dr.brojElemenata() << std::endl; 
    std::cout << "Skini sa vrha: " << dr.skiniSaVrha() << std::endl; 
    std::cout << "Broj elemenata poslije skidanja sa vrha: " << dr.brojElemenata() <<std::endl; 
}

void brojElemenataTest()
{
    DvostraniRed<int> dr;
    for(int i = 1; i <= 5; i++)
        dr.staviNaCelo(i);
    std::cout << "Broj elemenata u dvostranom redu: " << dr.brojElemenata() << std::endl; 
}

void celoTest()
{
    DvostraniRed<int> dr;
    for(int i  = 1; i <= 5; i++)
        dr.staviNaCelo(i);
    std::cout << "Element na celu dvostranog reda je: " << dr.celo() << std::endl; 
}

void vrhTest()
{
    DvostraniRed<int> dr;
     for(int i  = 1; i <= 5; i++)
        dr.staviNaCelo(i);
    std::cout << "Element na vrhu dvostranog reda je: " << dr.vrh() << std::endl; 

}
int main(){

    brisiTest();
    staviNaCeloTest();
    staviNaVrhTest();
    skiniSaCelaTest();
    skiniSaVrhaTest();
    brojElemenataTest();
    celoTest();
    vrhTest();
    return 0;
}
