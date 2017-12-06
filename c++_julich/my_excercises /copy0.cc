// Source: http://www.boost.org/community/generic_programming.html
// Modified.

#include <list>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <array>

// The name was changed to blahacopy to ensure that we are not using
// any system copy function!

template <typename InputIterator, typename OutputIterator>
OutputIterator
blahacopy(InputIterator first, InputIterator last, OutputIterator result)
{
  while (first != last) *result++ = *first++;
  return result;
}

int main()
{
  const int N = 3;
  std::list<int> region2{1,0,3};
  std::vector<int> region1(region2.size(),0);

  blahacopy(region2.begin(), region2.end(), region1.begin());

  for (auto i : region1) std::cout << i << " ";
  std::cout << '\n';

  std::string s1="AAAA AAAA";
  std::string s2="BBBB BBBB";

  blahacopy(s1.begin(), s1.end(), s2.begin());
  for(auto i: s1) std::cout << i << std::endl;
  for(auto i: s2) std::cout << i << std::endl;
  
  for(std::string::iterator it=s1.begin();
      it!=s1.end(); ++it)
    {
      std::cout << *it << " ";
      //      std::cout << &*it;
      printf("%d\n",it);
      //      std::cout << (std::string) it;
      std::cout << typeid(it).name() << '\n';

    }
  
  std::array<int,300> test_array1;
  test_array1.fill(4);


}
