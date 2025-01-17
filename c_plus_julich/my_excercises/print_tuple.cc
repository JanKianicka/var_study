#include <tuple>
#include <iostream>

template <int idx, int MAX, typename... Args>
struct PRINT_TUPLE
{
    static void print(std::ostream & strm, const std::tuple<Args...> & t)
    {
        strm << std::get<idx>(t) << (idx+1==MAX ? "" : ", ");
        PRINT_TUPLE<idx+1,MAX,Args...>::print(strm,t);
    }
};

template <int MAX, typename... Args>
struct PRINT_TUPLE<MAX,MAX,Args...>
{
    static void print(std::ostream &strm, const std::tuple<Args...> &t)
    {
    }
};

template <typename ... Args>
std::ostream & operator<<(std::ostream & strm, const std::tuple<Args...> & t)
{
    strm << "[";
    PRINT_TUPLE<0,sizeof...(Args),Args...>::print(strm,t);
    return strm <<"]";
}

/*
int main(){
  std::tuple<int,int,std::string> name_i_j{0,1,"Uralic"};
  auto t3=std::make_tuple<int,bool,std::string>(2,false,"Hello my dear.");
  std::cout << name_i_j << '\n';
  std::cout << t3 << '\n';
  
  return 0;
}
*/

