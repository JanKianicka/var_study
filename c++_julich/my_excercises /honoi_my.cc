#include <iostream>
int the_other(int i, int j) {return 3-i-j;}

void transfer(unsigned n, int from, int to)
{
  int oth=the_other(from,to);
  if (n>1) transfer(n-1,from,oth);
  std::cout << n << ": "<<from<<"->"<<to<<"\n";
  if (n>1) transfer(n-1,oth,to);
}

int main()
{
  transfer(2,0,1);
}
