#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

int main()
{
  std::string filename;
  std::cout << "Enter filename:";
  std::cin >> filename;

  std::ifstream fin(filename);

  std::string s;
  std::map<std::string,unsigned> freq;

  while (fin >> s) freq[s]++;
  freq["a"] = 1;

  for (auto i : freq) 
    std::cout << std::setw(20) << i.first 
              << std::setw(4)  << ':'
              << std::setw(12) << i.second 
              << '\n';

  bool is_empty = freq.empty();
  std::cout << "Is empty:" << std::setw(10) << is_empty << '\n';

  std::map<std::string,unsigned>::key_compare mycomp = freq.key_comp();
  // mycomp(0,'the'); -- this does not work
  // mycomp(freq.begin());
  std::cout << freq["a"]; 

  std::map<unsigned, std::string> mymap;
  mymap[0] = "This first word.";

  // Algorithms
  int myints[] = { 10, 20, 30, 40 };
  std::vector<int> myvector (myints,myints+4);
  std::vector<int>::iterator it;

  it = std::find(myvector.begin(), myvector.end(),0);
}

