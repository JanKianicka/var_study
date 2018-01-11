#include <random>
#include <functional>
#include <iostream>
#include <vector>
#include <map>

#include <algorithm>
#include <iomanip>

#include <valarray>

double my_mean(std::vector<double> arr){
  double m;
  m = (accumulate(arr.begin(), arr.end(), 0.0))/arr.size();

  return m;
}

int main()
{
  double mean = 40.4;
  double var  = 5;
  unsigned size = 1000000;
  
  double res_mean = 0.0;

  std::normal_distribution<double> distribution(mean,var);
  std::default_random_engine engine;
  auto generator = std::bind(distribution, engine);
  
  std::vector<double> numbers(size,0);
  std::valarray<double> numbers_val(0.,size); // watch out, this constructor is different
  
  double val = 0.0;

  for (unsigned i=0; i<size; i++){
    val =  generator();
    numbers[i] = val;
    numbers_val[i] = val;
  }
  
  res_mean = my_mean(numbers);
  std::cout << "Mean: " << std::fixed << std::setw( 11 ) 
	    << std::setprecision( 6 ) << res_mean << '\n';
  std::cout << "Calculation with valarray:\n";

  res_mean = numbers_val.sum()/size;
  std::cout << "Mean: " << std::fixed << std::setw( 11 ) 
	    << std::setprecision( 6 ) << res_mean << '\n';

  std::nth_element(numbers.begin(), numbers.begin() + numbers.size()/2, numbers.end());
  std::cout << "The median is " << numbers[numbers.size()/2] << '\n';

  std::sort(numbers.begin(), numbers.end());
  for (unsigned i=0; i<size; i += 10000){
    std::cout << numbers[i] << '\n';
  }

  // From sorted array
  // std::cout << "Median from sorted array: " << numbers[size/2] << '\n';
  auto M = [=](){return numbers[size/2];}; // we make small lambda exercise

  std::cout << "Median from sorted array: " << M() << '\n';
}
