// Hello World!
// for compilation use --std=c++14 -pedantic
#include <iostream>
#include <list>
#include <vector>
#include <math.h>

#include <array>

// standard library
#include <chrono>

#include <type_traits>
#include <typeinfo>

double sqr(double a)
{
    return a*a;
}

// new type of function implementation
auto f2(double x, double y)->double
{
	return x*y;
}

// overloading functions
int power(int x, unsigned int n)
{
	int ans=1;
	for(;n>0;--n) ans+=x;
	return ans;
}

double power(double x, double y)
{
	return exp(y*log(x));
}

// classes on the stack
struct Vector3 {
	double x, y, z;
	inline double dot(Vector3 other)
	{
	   return x*other.x + 
		  y*other.y +
		  z*other.z;
	}
};

struct Cat {
	int tail;
	int head;
	int leg[4];
	Cat();
	void move_tail();
	Cat *which_cat_is_this();
	Cat operator+(Cat b); // oveloading + operator, but does not obey symetry
};

Cat * Cat::which_cat_is_this()
{
	return this;
}

// read_data(int *i, int *j, data)
// read_data2(int &i, int &j, data) -- C/C++ is making copy of input arguments
// calling
// read_data(&i,&j)
// read_data2(i,j)

// constant reference
struct Truck{
	int tires[4];
};

int count_bad_tires(const Truck &t)
{
	int n = 0;
	// evaluation of tires
}

// R-value references
//std::ostream & operator<<(std::ostream &os, complex_number &a){
//	os<<a.real;
//	if (a.imaginary<0) os<<a.imaginary<<" i ";
// not finished
 
// }

// Constructors - initialization functions
// can be more initialization functions with different input 
// arguments

struct complex_number
{
  complex_number(double re, double im)
  {
    real=re;
    imaginary=im;
  }
  complex_number()
  {
    real=imaginary=0;
  }
  double real,imaginary;
};

// other options
struct darray
{
  double *data=nullptr;
  size_t sz=0;

  // contructor which initialize sz attribute
  darray(size_t N):sz{N} {
     data = new double[sz];
  }

  // there is only one destructor
  ~darray() {
    if (data) delete [] data;
  }
};

// copy contructor
class darray1 {
  int len;
  double *x = nullptr;

  darray1(darray1 &&); // move contructor
  darray1 & operator=(darray1 &&); // move assignemt
};

darray1::darray1(darray1 && other)
{
  len=other.len;
  x = other.x;
  other.x=nullptr;
}

darray1 & darray1::operator=(darray1 && other)
{
  len=other.len;
  x = other.x;
  other.x=nullptr;
  return *this;
}

// Metaprogramming in C++
// generic class for all types
template <class T>
class vector {

};

// class paticularly for bool type
template <>
class vector<bool> {

};

// Functions for compiler
template <int i, int j>
struct mult {
  static const int value = i*j;
};

// Type functions - not fully understood 
// template <typename T1, typename T2>
// std::is_same<T1,T2>::value;
template <class T2>
class someCalc
{
  static_assert(std::is_arithmetic<T2>::value,
		"argument T2 must be of arithmetic type.");
};

// Variadic template programming
template<typename ... Args>
int countArgs(Args ... args)
{
  return (sizeof...(args));
}

template <typename ... Types> void f3(Types ... args);
template <typename Type1, typename ... Types> void f3(Type1 arg1, Types ... rest){
  std::cout << typeid(arg1).name() << ": " << arg1 << "\n";
  f3(rest ...);
}
template <> void f3() {}


int main()
{
    int n_particles{1000};
    const double G{6.67408-11}; // this is initialization in C++
    int i=23;
    int j={23}; // i{2.3} cause compiler error - use curly bracket for initialization
    char user_choice = 'y';
    bool yes = true;

    // Collections
    std::list<double> masses{0.533, 990.3, 5454.4343};
    std::vector<int> scores{667, 1}; // two values
    std::vector<int> lows(250, 0);  // 250 elements with zero value
    
    // writing big numbers
    size_t is=20'000'000; // grouping in C++14
    
    // other initialization tips
    decltype(i) g{9}; // new variable g of type i
    auto positron_mass = n_particles;
    auto f = sqr; // Without "auto" we would need 
    // (*f)(int) = &sqrt;
    
    std::cout<<"Hello, world!\n";
    

    // compile static assertion
    unsigned long L;
    static_assert(sizeof(L) >=8, "long type must be at least 8 bytes.");

    // enumerators (not just ordered integers as in C)
    enum class color { red, green, blue};
    
    // pointers and references
    int k{5};
    int * iptr(&k);
    k += 1;
    std::cout << *iptr << std::endl;
    (*iptr) = 0;
    std::cout << k << std::endl;
    // reference
    int & iref(k); // iref "reference" to i
    iref = 4;  // you change i
    std::cout << k << std::endl; // 4
    
    // arrays
    std::array<double, 10> A;
    
    // ternary operator
    int N = 22;
    int x = N>10 ? 1 : 0;
    printf("x is %d\n",x);


    // range based loop, can be also C-stype array
    std::list<int> cont_A{0,2,3,3,4};
    char *AA = "string nasty one";
    int II[] = {0,2,55,45};

    for (auto c: cont_A) {
	    std::cout<< c << ", ";
    }
    // for (auto c: AA) std::cout << c; -- this does not work

    // New way of writing functions in C++
    f2(3.3, 5.6);

    // cin
    int xx;
    std::string mm;
    // std::cin >> xx >> mm;
    std::cout<< xx << "  " << mm << std::endl;

    // using compile time template function
    // I do not know here.
    //    std::array<int,int> my_array;

    std::cout << "Compile time function template: " << mult<19,21>::value << '\n';

    // parameter pack usage
    int i_p{3}, j_p{10};
    f3(i_p,j_p);

    return(0);
    
}
