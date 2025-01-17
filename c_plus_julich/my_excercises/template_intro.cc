#include <iostream>

template <class itr>
void mycopy(itr start, itr end, itr start2)
{
    for (;start!=end; ++start,++start2) {
        *start2=*start;
    }
}

int main()
{
    double x[10],y[10];
    for (double & num : x) num=1;
    mycopy(x,x+10,y);
    for (double & num : y) std::cout << num << std::endl;

    std::string anames[5]={"a","b","c","d","e"};
    std::string bnames[5]={" "," "," "," "," "};

    mycopy(anames,anames+5,bnames);
    for (std::string & name : bnames) std::cout << name << std::endl;
    
    std::cout<<bnames[0];

    return 0;
}

