#include <iostream>
#include <list>
#include <algorithm>

int main()
{
    std::list<int> l(20,0);
    for (auto x : l) std::cout << x << " ";
    std::cout << "\n";
    
    int cumul = 0;
    int cumul1 = 1;
    
    //    std::generate(l.begin(),l.end(),[&cumul]{ 
    //    return cumul++; 
    // });

    std::generate(l.begin(),l.end(),[=]()mutable{ 
        auto tmp_1 = cumul + cumul1;
	cumul = cumul1;
	cumul1 = tmp_1;
	return tmp_1;
    });

    for (auto x : l) std::cout << x << " ";
    std::cout << "\n";
}

