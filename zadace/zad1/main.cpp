#include <iostream>
using namespace std;//test 16 zeza zbog ovog :(

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
    Cvor<Tip> *prvi = nullptr;
    Cvor<Tip> *posljednji = nullptr;
    Cvor<Tip> *tekuci = nullptr;
public:
    DvostrukaLista() {}

    DvostrukaLista(const DvostrukaLista &dl)
    {
        broj_elemenata = dl.broj_elemenata;
        if(broj_elemenata == 0) return;
        prvi = new Cvor<Tip>(*dl.prvi);
        Cvor<Tip> *pom = prvi;
        while(pom->sljedeci != nullptr) {
            pom->sljedeci = new Cvor<Tip>(*pom->sljedeci);
            pom = pom->sljedeci;
        }
        posljednji = dl.posljednji;
    }

    DvostrukaLista(DvostrukaLista &&dl)
    {
        broj_elemenata = dl.broj_elemenata;
        prvi = dl.prvi;
        posljednji = dl.posljednji;
        tekuci = dl.tekuci;
        dl.broj_elemenata = 0;
        dl.prvi = nullptr;
        dl.tekuci = nullptr;
        dl.posljednji = nullptr;
    }

    ~DvostrukaLista()
    {
        Cvor<Tip> *pom = prvi;
        Cvor<Tip> *pom2 = prvi;
        while(pom != nullptr) {
            pom2 = pom->sljedeci;
            delete pom;
            pom = pom2;
        }
    }

    DvostrukaLista &operator =(const DvostrukaLista &dl)
    {
        if(&dl != this) {
            Cvor<Tip> *pom = prvi;
            if(pom != nullptr)
                while(pom->sljedeci != nullptr) {
                    prvi = prvi->sljedeci;
                    delete pom;
                    pom = prvi;
                }

            broj_elemenata = dl.broj_elemenata;
            if(broj_elemenata != 0) {
                prvi = new Cvor<Tip>(*dl.prvi);
                Cvor<Tip> *pom2 = prvi;
                while (pom2->sljedeci != nullptr) {
                    pom2->sljedeci = new Cvor<Tip>(*pom2->sljedeci);
                    pom2 = pom2->sljedeci;
                }
            } else {
                prvi = nullptr;
                tekuci = nullptr;
                posljednji = nullptr;
            }
        }

        return *this;
    }

    DvostrukaLista &operator =(DvostrukaLista &&dl)
    {
        if(&dl != this) {
            broj_elemenata = dl.broj_elemenata;
            tekuci = dl.tekuci;
            Cvor<Tip> *pom = dl.prvi;
            while(pom->sljedeci != nullptr) {
                dl.prvi = dl.prvi->sljedeci;
                delete pom;
                pom = prvi;
            }
            prvi = dl.prvi;
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
        if(broj_elemenata == 0) 
            throw std::domain_error("Lista je prazna");
        return tekuci->element;
    }

    Tip trenutni() const
    {
        if(broj_elemenata == 0) 
            throw std::domain_error("Lista je prazna");
        return tekuci->element;
    }

    bool prethodni()
    {
        if(broj_elemenata == 0) 
            throw std::domain_error("Lista je prazna");
        if(tekuci == prvi) return false;
        tekuci = tekuci->prethodni;
        return true;
    }

    bool sljedeci()
    {
        if(broj_elemenata == 0) 
            throw std::domain_error("Lista je prazna");
        if(tekuci->sljedeci == nullptr) 
            return false;
        tekuci = tekuci->sljedeci;
        return true;
    }

    void pocetak()
    {
        if(broj_elemenata == 0) 
            throw std::domain_error("Lista je prazna");
        tekuci = prvi;
    }

    void kraj()
    {
        if(broj_elemenata == 0) 
            throw std::domain_error("Lista je prazna");
        tekuci = posljednji;
    }

    void obrisi()
    {
        if(broj_elemenata == 0) 
            throw std::domain_error("Lista je prazna");
        if(prvi == tekuci) {
            Cvor<Tip> *pom = prvi;
            tekuci = prvi->sljedeci;
            delete pom;
            prvi=tekuci;
        } else {
            posljednji = posljednji->prethodni;
            Cvor<Tip> *pom = tekuci->prethodni;
            pom->sljedeci = tekuci->sljedeci;
            delete tekuci;
            if(pom->sljedeci != nullptr) 
                tekuci = pom->sljedeci;
            else tekuci = pom;
        }
        broj_elemenata--;
    }

    void dodajIspred(const Tip& el)
    {
        if(prvi == tekuci) {
            Cvor<Tip> *pom = new Cvor<Tip>;
            pom->element = el;
            pom->sljedeci = prvi;
            if(broj_elemenata != 0) 
                prvi->prethodni = pom;
            prvi = pom;
            if(tekuci == nullptr) {
                tekuci = prvi;
                posljednji = prvi;
            }
        } else {
            Cvor<Tip> *p = new Cvor<Tip>;
            p->element = el;
            tekuci->prethodni->sljedeci = p;
            p->prethodni = tekuci->prethodni;
            tekuci->prethodni = p;
            p->sljedeci = tekuci;
            if(tekuci->sljedeci == nullptr) posljednji = tekuci;
        }
        broj_elemenata++;
    }

    void dodajIza(const Tip& el)
    {
        if(broj_elemenata == 0) {
            Cvor<Tip> *p = new Cvor<Tip>;
            p->element = el;
            p->sljedeci = nullptr;
            p->prethodni = nullptr;
            prvi = p;
            tekuci = prvi;
            posljednji = prvi;
        } else {
            Cvor<Tip> *p = tekuci->sljedeci;
            tekuci->sljedeci = new Cvor<Tip>;
            tekuci->sljedeci->element = el;
            tekuci->sljedeci->sljedeci = p;
            tekuci->sljedeci->prethodni = tekuci;
            if(tekuci == posljednji) posljednji = tekuci->sljedeci;
            if(p != nullptr) {
                p->prethodni = tekuci->sljedeci;
                if(p->sljedeci == nullptr) posljednji = p;
            }
        }
        broj_elemenata++;

    }

    Tip &operator [](int i)
    {
        Cvor<Tip> *pom = prvi;
        for(int j = 0; j < i; j++)
            pom = pom->sljedeci;
        return pom->element;
    }

    Tip operator [] (int i) const
    {
        Cvor<Tip> *pom = prvi;
        for(int j = 0; j < i; j++)
            pom = pom->sljedeci;
        return pom->element;
    }

};

template<typename Tip>
Tip dajMaksimum(const Lista<Tip>& n)
{
    DvostrukaLista<Tip> l = DvostrukaLista<Tip>(*((DvostrukaLista<Tip>*)(&n)));
    l.pocetak();
    Tip max = l.trenutni();
    while(l.sljedeci()) {
        if(l.trenutni() > max) max = l.trenutni();
    }
    return max;
}

/*Testovi kao u Javi/Mavenu za metode*/
void brojElemenataTest()
{
    DvostrukaLista<int> lista;
    for(int i = 1; i <= 10; i++)
        lista.dodajIza(i);
    std::cout << "Broj elemenata: " << lista.brojElemenata(); 
}

void trenutniTest()
{
    DvostrukaLista<int> lista;
    for(int i = 1; i <= 10; i++)
        lista.dodajIza(i);
    std::cout << "Trenutni: " << lista.trenutni(); 
}

void prethodniTest()
{
    DvostrukaLista<int> lista;
    for(int i = 1; i <= 10; i++) {
        lista.dodajIza(i);
        lista.sljedeci();
    }
    lista.kraj();
    lista.prethodni();
    std::cout << "Trenutni: " << lista.trenutni(); 
}

void sljedeciTest()
{
    DvostrukaLista<int> lista;
    for(int i = 1; i <= 10; i++) {
        lista.dodajIza(i);
        lista.sljedeci();
    }
    lista.pocetak();
    lista.sljedeci();
    std::cout << "Sljedeci: " << lista.trenutni();
}

void pocetakTest()
{
    DvostrukaLista<int> lista;
    for(int i = 1; i <= 10; i++)
        lista.dodajIza(i);
    lista.pocetak();
    std::cout <<"Pocetak: "<< lista.trenutni(); 
}

void krajTest()
{
    DvostrukaLista<int> lista;
    for(int i = 1; i <= 10; i++) {
        lista.dodajIza(i);
        lista.sljedeci();
    }
    lista.kraj();
    std::cout << "Kraj: " << lista.trenutni(); 
}

void obrisiTest()
{
    DvostrukaLista<int> lista;
    for(int i = 1; i <= 10; i++)
        lista.dodajIza(i);
    std::cout << "Broj elemenata prije brisanja trenutnog: " << lista.brojElemenata() << std::endl;
    lista.obrisi();
    std::cout << "Broj elemenata poslije brisanja trenutnog: " << lista.brojElemenata() << std::endl;
}

void dodajIspredTest()
{
    DvostrukaLista<int> lista;
    for(int i = 1; i <= 10; i++) {
        lista.dodajIspred(i);
        lista.pocetak();
    }
    lista.pocetak();
    lista.dodajIspred(10); 
    for(int i = 0; i < lista.brojElemenata(); i++)
        std::cout << lista[i] << std::endl;

}

void dodajIzaTest()
{
    DvostrukaLista<int> lista;
    for(int i = 1; i <= 10; i++) {
        lista.dodajIza(i);
        lista.sljedeci();
    }
    lista.pocetak();
    lista.dodajIza(10); 
    for(int i = 0; i < lista.brojElemenata(); i++)
        std::cout << lista[i] << std::endl;
}

void operatoriTest()
{
    DvostrukaLista<int> l1;
    for(int i  = 1; i <= 10; i++) {
        l1.dodajIza(i);
        l1.sljedeci();
    }
    DvostrukaLista<int> l2 = l1;
    for(int i = 0; i < l2.brojElemenata(); i++)
        std::cout << l2[i] << std::endl;
}

void dajMaximumTest()
{
    DvostrukaLista<int> lista;
    for(int i = 1; i <= 5; i++)
        lista.dodajIza(i);
    std::cout << "Maximum: " << dajMaksimum(lista) << std::endl;
}


int main()
{
    std::cout << "Test brojElemenata: ";
    brojElemenataTest();
    std::cout << std::endl;
    std::cout << "Test trenutni: ";
    trenutniTest();
    std::cout << std::endl;
    std::cout << "Test prethodni: ";
    prethodniTest();
    std::cout << std::endl;
    std::cout << "Test sljedeci: ";
    sljedeciTest();
    std::cout << std::endl;
    std::cout << "Test pocetak: ";
    pocetakTest();
    std::cout << std::endl;
    std::cout << "Test kraj: ";
    krajTest();
    std::cout << std::endl;
    std::cout << "Test obrisi: ";
    obrisiTest();
    std::cout << std::endl;
    std::cout << "Test dodajIspred: ";
    dodajIspredTest();
    std::cout << "Test dodajIza: ";
    dodajIzaTest();
    std::cout << "Test operatori: ";
    operatoriTest();
    std::cout << "Test dajMaksimum: ";
    dajMaximumTest();
    return 0;
}
