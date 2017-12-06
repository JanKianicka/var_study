#include <iostream>

using namespace std;

class Vbose
{
public:
    Vbose(string gs);
    Vbose();
    Vbose(const Vbose &);
    Vbose & operator=(const Vbose &v);
    Vbose(Vbose &&);
    Vbose & operator=(Vbose &&v);
    Vbose operator+(const Vbose &v);
    ~Vbose();
    inline string getval() const { return nm; }
    inline void setval(const std::string &nw) { nm=nw; }
private:
    string nm;
};

Vbose::Vbose() : nm("Uninitialized")
{
    cout << "Default constructor of object at "<<((size_t)this)<<endl;
}

Vbose::Vbose(const Vbose & v) : nm(v.nm)
{
    cout << "Copy constructor of object at "<<((size_t)this)<<". ";
    cout << "Source for copy is at "<<((size_t) &v)<<endl;
}
Vbose::Vbose(Vbose && v) : nm(std::move(v.nm))
{
    cout << "Move constructor of object at "<<((size_t)this)<<". ";
    cout << "Source for move is at "<<((size_t) &v)<<endl;
}

Vbose::Vbose(string gs) : nm(gs)
{
    cout << "Constructor of object at "<<((size_t)this)<<",";
    cout << " using string "<<gs<<endl;
}

Vbose & Vbose::operator=(const Vbose &v)
{
    cout << "Assignment operator: LHS @ "<<((size_t)this) <<"("<<nm<<"), "; 
    cout << "RHS @ "<<((size_t)&v) <<"("<<v.nm<<")\n"; 
    if (this!=&v) {
        nm=v.nm;
    }
    return *this;
}

Vbose & Vbose::operator=(Vbose &&v)
{
    cout << "Move assignment operator: LHS @ "<<((size_t)this) <<"("<<nm<<"), "; 
    cout << "RHS @ "<<((size_t)&v) <<"("<<v.nm<<")\n"; 
    std::swap(nm,v.nm);
    return *this;
}

Vbose::~Vbose()
{
  double *arrayloc = nullptr;
  
  cout << "Destructor of object at "<<((size_t) this) << " with data "<<nm<<endl;
  delete [] arrayloc;
}

Vbose Vbose::operator+(const Vbose &v)
{
    cout << "Inside operator + ()\n";
    return nm+"+"+v.nm;
}

Vbose f(string a)
{
    cout << "Entering f()\n";
    Vbose tmp(a);
    if (tmp.getval()=="") {
        cerr << "Warning! Empty string used to construct object!\n";
    }
    cout << "Leaving f()\n";
    return tmp;
}

void g(Vbose v)
{
    std::cout << "Called g with "<<((size_t) &v)<<"("<<v.getval()<<")\n";
    v.setval(v.getval()+"_modified");
    std::cout << "g() : Modified v to "<<v.getval()<<endl;
}


int main()
{
    cout << "Entering main()\n";
    cout << "Constructing a and b\n";
    Vbose a,b("Mercury");
    {
        Vbose c("UnusedVar");
    }
    cout << "Calling f and assigning result to a\n";
    a=f("Venus");

    cout << "Calling f without assigning the result\n";
    f("Jupitor");
    cout << "Statement after calling f without assigning result\n";

    cout << "Calling g with b\n";
    g(b);
    cout << "Statement after calling g with b\n";
    cout << "Value of b, after call to g, is "<< b.getval()<<endl;

    cout << "Calling g with a+b\n";
    g(a+b);

    cout << "Calling g with std::move(a)\n";
    g(std::move(a));
    cout << "Leaving main()\n";
}

