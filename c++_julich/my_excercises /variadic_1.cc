#include <iostream>
#include <typeinfo>
#include <string>

template <typename ... Types> void f(Types ... args);
template <typename Type1, typename ... Types> void f(Type1 arg1, Types ... rest) {
    std::cout <<typeid(arg1).name()<<": "<< arg1 << "\n";
    f(rest ...);
}
template <> void f() {}

int main()
{
    int i{3},j{};
    size_t k{},l{9};
    const char * cst{"abc"};
    std::string cppst{"def"};
    f(i,j,true,k,l,cst,cppst);
}

