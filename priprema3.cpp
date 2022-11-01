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
        delete vrh;
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

