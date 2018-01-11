#include <iostream>
#include <initializer_list>
template <typename T>
class darray {
private:
  // swap function
  void swap(darray &oth) {
    std::swap(arr,oth.arr);
    std::swap(sz,oth.sz);
  }
  T *arr=nullptr;
  size_t sz=0;
public:
// read-only access for array elements
  T operator[](size_t i) const { return arr[i]; }
// read-write access for array elements
  T &operator[](size_t i) { return arr[i]; }
// This is needed if you want to use range based for loops on your class
  T * begin() const { return arr; }
// This is needed if you want to use range based for loops on your class
  T * end() const { return arr+size(); }
// returns the size : Observe this new alternative syntax for functions in C++11
  auto size() const ->decltype(sz) { return sz; }
// Sums up array and returns the result
  T sum() const {
    T a{};
    for (auto el : (*this)) {a+=el;} // Use the range based for loop. //Well, why not!
    return a;
  }
  // Default constructor, also defaulted. This means, members stay at the values given at the point of declaration.
  darray() = default;
  // Constructor with size given
  darray(size_t N) {
    if (N!=0) {
      arr=new T [N];
      sz=N;
    }
  }
  // Destructor. Check if the array was not nullptr, and delete it.
  ~darray() { if (arr) delete [] arr; }
  // Move constructor, using the swap function below.
  darray(darray<T> &&oth) {
    swap(oth);
  }
  // Copy constructor
  darray(const darray<T> &oth) {
    if (oth.sz!=0) {
      sz=oth.sz;
      arr=new T[sz];
    }
    for (size_t i=0;i<sz;++i) arr[i]=oth.arr[i];
  }
  // Initialiser list constructor
  darray(std::initializer_list<T> l) {
    arr=new T[l.size()];
    sz=l.size();
    size_t i=0;
    for (auto el : l) arr[i++]=el;
  }
  // Assignment operator using the copy and swap idiom
  darray & operator=(darray d) {
    swap(d);
    return *this;
  }
};
// Output operator. No need to make it a friend, since we can use only
// public functions of the class to do all the work!
template <typename T>
std::ostream &operator<<(std::ostream &os,const darray<T> &d) {
  os << '[';
  for (size_t i=0;i<d.size();++i) {
    os << d[i] ;
    if (i!=(d.size()-1)) os << ',';
  }
  os << ']';
  return os; // This function returns os so that you can write cout << d1 << " other things\n";
  // That is interpreted as (cout << d1) << " other things\n";
}

int main()
{
  darray<int> d1{1,2,3,4,5};
  darray<std::string> d2{"a","b","c"};
  auto d3=d1; // Copy construction with auto type determination
  darray<int> d4{10}; // This and the following line have a subtle difference
  darray<int> d5(10); // This is the only situation where constructor calls with {} and () mean different things.
  darray<std::string> d6{std::move(d2)}; // d2 should be empty and d6 must have all data after this.
  std::cout << "d1 = "<<d1<<"\n";
  std::cout << "d2 = "<<d2<<"\n";
  std::cout << "d3 = "<<d3<<"\n";
  std::cout << "d4 = "<<d4<<"\n";
  std::cout << "d5 = "<<d5<<"\n";
  std::cout << "d6 = "<<d6<<"\n";

  darray<double> d_double{0.1254, 2.236, 2.1, 0.0};
  std::cout << "d_double = " <<d_double<<"\n";

  darray<double> d_double2{std::move(d_double)};
  std::cout << "d_double = " <<d_double<<"\n";
  std::cout << "d_double2 = " <<d_double2<<"\n";

}
