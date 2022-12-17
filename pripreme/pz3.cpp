#include <iostream>
using namespace std;/*mrzim ovo, ali moram zbog testa 4*/

/*odradjeno na prosloj pripremi*/
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
    Cvor(const Tip &el, Cvor *s): element(el), sljedeci(s) {}
};

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

void TestiranjeSteka(){
    Stek<int> s;
    for(int i=0;i<10;i++)
        s.stavi(i);//0-9 u steku
    while(s.brojElemenata() > 0)
        std::cout << s.skini() << ", ";
    std::cout<<std::endl;

    for(int i=0;i<10;i++)
        s.stavi(i);//0-9 u steku
    std::cout << s.vrh() << std::endl;
    Stek<int> s2;
    s2 = s;
    std::cout << s2.vrh() << std::endl;
    s2.brisi();
    s.brisi();
}

int main(){
    TestiranjeSteka();
    return 0;
}
