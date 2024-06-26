#include <random>
#include <functional>
#include <iostream>
#include <vector>
#include <map>


int main()
{
  double mean = 10.4;
  double var  = 5;
  // unsigned size = 1000000; --on the stuck this has failed
  unsigned size = 1000000;

  std::normal_distribution<double> distribution(mean,var);
  std::default_random_engine engine;
  auto generator = std::bind(distribution, engine);
  
  std::vector<float> numbers(size,0); // allocates on stack
  // std::vector<double>* numbers1 = new std::vector<double>(size); // -- should be on the heap
  // auto numbers = numbers1[0];

  for (unsigned i=0; i<size; i++){
    numbers[i] = generator();

    // numbers.push_back(generator());
    //    numbers1[0][i] = generator();
    // std::cout << numbers[i] << '\n';
  }
  
  // now we have filled the vector
  double hist_min = 0;
  double hist_max = 100;
  double hist_step = 1;
  int hist_size = (int) (hist_max - hist_min)/hist_step;

  std::vector<long int> hist(hist_size,0);
  for (auto &v:numbers){

    unsigned long int ihist = (unsigned long int) floor((v-hist_min)/hist_step);
    //std::cout << v << ' ' << ihist << '\n';
    if (ihist < hist_size) ++hist[ihist];
  }
  
  std::cout << "Histogram:" << "\n";
  for (auto &h:hist) std::cout << h << '\n';
  
}
