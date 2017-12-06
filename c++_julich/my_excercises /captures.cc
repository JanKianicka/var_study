#include <iostream>
int main()
{
    int p=5;
    auto L=[p](int i){std::cout << i*3+p<<"\n";};
    L(3); // result : prints out 14
//    auto M=[p](int i){return p+=i*3;}; // syntax error! p is read-only!
    auto N=[p](int i)mutable{return p+=i*3;};
    std::cout <<N(1)<<" ";
    std::cout <<N(2)<<" ";
    std::cout <<p<<"\n";
    // result : prints out "8 14 5"
    auto R=[&p](int i){return p+=i*3;};
    std::cout <<R(1)<<" ";
    std::cout <<R(2)<<" ";
    std::cout <<p<<"\n";
    // result : prints out "8 14 14"
}

