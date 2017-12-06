#include <tuple>
#include <iostream>
#include <iomanip>
#include <string>

int main()
{
    std::tuple<int,int,std::string> name_i_j{0,1,"Uralic"};
    auto t3=std::make_tuple<int,bool>(2,false);
    auto t4=std::tuple_cat(name_i_j,t3);
    std::cout << "Name field in t4 is "<<std::get<2>(t4) <<'\n';
    bool flg;
    std::string name;
    std::tie(std::ignore,std::ignore,name,std::ignore,flg)=t4;
    std::cout << name <<'\t'<< std::boolalpha << flg << "\n";
}
