#include <iostream>
#include <list>

template <typename ... Types> void f(Types & ... args) {}
template <typename ... Types> void g(Types & ... args) { f(++args...); }
template <typename ... Types> void h(Types ... args) { 
    std::cout << "Printing parameters passed to h \n";
    f(std::cout<<args<<"\t"...); // this will work in oposite order for gcc
    [=,&args ...]{ return g(args...); }();
    std::cout << "\nModified value due to call to g through lambda \n";
    f(std::cout<<args<<"\t"...); 
    int t[sizeof...(args)]={args ...};
    int s=0;
    for (auto i : t) s+=i;
    std::cout << "\nsum = "<<s <<"\n";
}
int main()
{
    int i=0;
    std::list<int> l{0,2,4,8,16};
    std::list<int>::iterator it = l.begin();
    std::cout << i << "; "<<(*it)<<"\n";
    g(i,it);
    std::cout << i << "; "<<(*it)<<"\n";
    std::cout << "Calling h(1,2,3,4)\n";
    h(1,2,3,4);
}

