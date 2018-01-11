#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

enum Weekday {
  Monday=0, Tuesday=1, Wednesday=2, Thursday=3, Friday=4, Saturday=5, Sunday=6
};

int main()
{
  std::vector<unsigned> days{1,3,43,144,151,187,264,343};
  std::vector<Weekday> wdays(days.size());
  std::transform(days.begin(),days.end(),wdays.begin(), [](unsigned i) {
    return (Weekday) (i%7);
  });
  std::string daynames[]{ "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
  for (auto i : wdays) {
    std::cout << daynames[i] <<"\n";
  }
}
