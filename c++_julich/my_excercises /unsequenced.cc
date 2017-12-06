#include <iostream>

void f(int i, int j)
{
    std::cout << "Function f(): received arguments "<<i<<" and "<<j<<"\n";
}

int main()
{
    int i=0;
    std::cout << "i = " << i << "\n";
    i = ++i + i++; // undefined behaviour
    std::cout << "After i = ++i + i++;\n";
    std::cout << "i = " << i << "\n";
    i = i++ + 1; // undefined behaviour
    std::cout << "After i = i++ + 1;\n";
    std::cout << "i = " << i << "\n";
    std::cout << "Calling f(++i,++i);\n";
    f(++i,++i);// Arguments the function receives might be a surprise!
    std::cout << "i = " << i << "\n";
    std::cout << "incrementing i between << operators : "<<i<<' '<<i++<<' '<<i++<<'\n';
    int a[10];
    for (i=0;i<10;) a[i]=i++; // undefined behaviour
    std::cout << "a=[";
    for (auto j: a) std::cout << j << ", ";
    std::cout << "]\n";
    // On the other hand, the following is ok!
    i=0;
    int b[10]={i++,i++,i++,i++,i++,i++,i++,i++,i++,i++};
    std::cout << "b=[";
    for (auto j: b) std::cout << j << ", ";
    std::cout << "]\n";
}

