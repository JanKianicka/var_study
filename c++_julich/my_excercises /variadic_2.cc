#include <iostream>

template <typename ... Types> void f(Types ... args);
template <typename Type1, typename ... Types> void f(Type1 arg1, Types ... rest) {
    std::cout <<" The first argument is "<<arg1 
              <<". Remainder argument list has "<<sizeof...(Types)<< " elements.\n";
    f(rest ...);
}
template <> void f() {}
template <typename ... Types> void g(Types ... args) {
    std::cout << "Inside g: going to call function f with the sizes of my arguments\n";
    f(sizeof(args)...);
}

int main()
{
    std::cout << R"hoho(Calling f(0,true,"123");)hoho" <<'\n';
    f(0,true,"123");
    std::cout << R"hoho(Calling g(0,true,"123");)hoho" <<'\n';
    g(0,true,"123");
}

