#include <random>
#include <functional>
#include <iostream>
#include <map>

int main()
{
    std::poisson_distribution<> distribution(8.5);
    std::mt19937 engine;
    auto generator = std::bind(distribution,engine);
    std::map<int,double> H;
    for (unsigned i=0;i<5000;++i) H[generator()]++;
    for (auto & i : H) std::cout<<i.first<<" "<<i.second<<std::endl;
    return 0;
}

