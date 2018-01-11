#include <list>
#include <iostream>
#include <algorithm>

template <typename InputIterator, typename OutputIterator>
OutputIterator
blahacopy(InputIterator first, InputIterator last, OutputIterator result)
{
  while (first != last) *result++ = *first++;
  return result;
}

struct Proxy {
  template <typename T>
  Proxy& operator=(const T &t) {
    std::cout <<"Output through proxy: "<< t <<"\n";
    return *this;
  }
};

struct FakeItr {
  using value_type = Proxy;
  FakeItr & operator++(int) {return *this;}
  FakeItr & operator++() {return *this;}
  Proxy operator*() { return Proxy{}; }
};

int main()
{
  std::list<int> region2{1,2,3,4,5,6};
  FakeItr it;
  blahacopy(region2.begin(), region2.end(), it);
  // Fake destination iterator works with std::copy as well!
  std::copy(region2.begin(), region2.end(), it);
}

