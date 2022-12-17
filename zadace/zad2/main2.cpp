#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template<typename Tip>
struct Cvor{

    Tip element;
    Cvor *sljedeci;
    Cvor(){
        sljedeci = nullptr;
    }
    Cvor(const Cvor &c){
        element = c.element;
        sljedeci = c.sljedeci;
    }
    Cvor(const Tip &el, Cvor *sl) : element(el), sljedeci(sl) {};
};

/*IMPLEMENTIRANO NA PRIPREMI 3*/
template <typename Tip>
class Stek {
    Cvor<Tip> *peek = nullptr;
    int vel = 0;
public:
    Stek(){};
    ~Stek(){
        brisi();
        delete peek;
    }
    Stek(const Stek &s){
        vel = s.vel;
        peek = 0;
        Cvor<Tip> *tmp;
        Cvor<Tip> *tmp_brojac = s.peek;//za petlju
        while(tmp_brojac != 0){
            Cvor<Tip> *tmp2 = new Cvor<Tip>(tmp_brojac->element, 0);
            if(peek ==0)
                peek = tmp2;
            else
                tmp->sljedeci = tmp2;
            tmp = tmp2;
            tmp_brojac = tmp_brojac->sljedeci;
        }
    }
    Stek &operator =(const Stek &s){
        if(&s == this)
            return *this;
        vel = s.vel;
        peek = 0;
        Cvor<Tip> *tmp;
        Cvor<Tip> *tmp_brojac = s.peek;//za petlju
        while(tmp_brojac != 0){
            Cvor<Tip> *tmp2 = new Cvor<Tip>(tmp_brojac->element, 0);
            if(peek ==0)
                peek = tmp2;
            else
                tmp->sljedeci = tmp2;
            tmp = tmp2;
            tmp_brojac = tmp_brojac->sljedeci;
        }
        return *this;
    }

    //brise sve elemente steka
    void brisi(){
        while(peek!=0)
            skini();
    }
    //stalja element na vrh steka
    void stavi(const Tip &el){
        Cvor<Tip> *novi = new Cvor<Tip>(el, peek);
        peek=novi;
        vel++;
    }
    //skida element sa steka i vraca ga
    Tip skini(){
        if(peek == nullptr)
            throw("Stek je prazan");
        Tip el = peek->element;
        Cvor<Tip> *novi = peek->sljedeci;
        delete peek;
        peek = novi;
        vel--;
        return el;
    }
    //vraca vrh steka
    Tip &vrh() const {
        if(peek ==0)
            throw("Stek je prazan");
        return peek->element;
    }
    int brojElemenata(){
        return vel;
    }
};

/*TRAZENA FUNKCIJA*/
void pretraga(Stek<std::vector<int>> &s, int trazeni){
    if(s.brojElemenata() == 0){
        std::cout << "Nema elementa" << std::endl;
        return;
    }
    auto v = s.skini();
    int br_elemenata = v.size();
    bool postoji(false);
    if(br_elemenata != 0 && trazeni >= v.at(0)){
        auto poc = v.begin();
        auto kraj = v.end()-1;
        int idx;
        while(poc <= kraj){
            auto sred = poc + (kraj - poc)/2;
            idx = sred - v.begin();
            if(*sred < trazeni)
                poc = sred + 1;
            else if(*sred > trazeni)
                kraj = sred - 1;
            else {
                postoji = true;
                std::cout << idx << " " << s.brojElemenata();
                break;
            }
        }
        if(!postoji)
            std::cout << "Nema elementa" << std::endl;
    }
    else {
        pretraga(s,trazeni);
    }
    s.stavi(v);
}

void test1()
{
    Stek<std::vector<int>> s;
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {6, 7, 8, 9, 10};
    std::vector<int> v3 = {11, 12, 13, 14, 15};
    std::vector<int> v4 = {16, 17, 18, 19, 20};
    s.stavi(v1);
    s.stavi(v2);
    s.stavi(v3);
    s.stavi(v4);
    int trazeni = 3;
    pretraga(s, trazeni);
    trazeni = 14;
    pretraga(s, trazeni);
    trazeni = 7;
    pretraga(s, trazeni);
}

void test2()
{
    Stek<std::vector<int>> s;
    std::vector<int> a = {2, 7, 9, 11};
    std::vector<int> b = { 15, 18, 22, 25};
    std::vector<int> c = {27, 56, 101, 278, 987};
    s.stavi(a);
    s.stavi(b);
    s.stavi(c);
    int trazeni = 5;
    pretraga(s, trazeni); 
    trazeni = 101;
    pretraga(s, trazeni);
}

void test3()
{
    Stek<std::vector<int>> s;
    std::vector<int> x = {11, 22, 33, 44, 55, 66, 77, 88, 99};
    std::vector<int> y = {111, 222, 333, 444, 555, 666, 777, 888, 999};
    std::vector<int> z = {1111, 2222, 3333, 4444, 5555, 6666, 7777, 8888, 9999};
    s.stavi(x);
    s.stavi(y);
    s.stavi(z);
    int trazeni = 5555;
    pretraga(s, trazeni);
    trazeni = 556;
    pretraga(s, trazeni); 
    trazeni = 11;
    pretraga(s, trazeni);;
}

int main(){
    test1();
    test2();
    test3();
    return 0;
}
