// Here we provide brief description of all C++ header files.
// using the book and this reference: http://www.cplusplus.com/reference

#include <algorithm>  // Defines a collection of functions especially designed to be used on ranges of elements - iterators, containers.
#include <bitset>     // Header that defines the bitset class. The class emulates an array of bool elements, but optimized for space allocation.
#include <complex>    // The complex library implements the complex class to contain complex numbers in cartesian form and several functions and overloads to operate with them.
#include <deque>      // Header that defines the deque container class. Double-ended queues are sequence containers with dynamic sizes that can be expanded or contracted on both ends (either its front or its back).
#include <exception>  // This header defines the base class for all exceptions thrown by the elements of the standard library.
#include <fstream>    // Header providing file stream classes.
#include <functional> // Function objects are objects specifically designed to be used with a syntax similar to that of functions.
#include <iomanip>    // Header providing parametric manipulators.
#include <ios>        // Header providing base classes and types for the IOStream hierarchy of classes.
#include <iosfwd>     // This header provides forward declarations for the types of the standard input/output library.
#include <iostream>   // Header that defines the standard input/output stream objects.
#include <istream>    // Header providing the standard input and combined input/output stream classes.
#include <iterator>   // An iterator is any object that, pointing to some element in a range of elements (such as an array or a container),
                      // has the ability to iterate through the elements of that range using a set of operators
                      // (with at least the increment (++) and dereference (*) operators).
#include <limits>     // This header defines elements with the characteristics of arithmetic types.
#include <list>       // Header that defines the list container class.
#include <locale>     // A locale is a set of features that are culture-specific, which can be used by programs to be more portable internationally.
#include <map>        // Header that defines the map and multimap container classes.
#include <memory>     // This header defines general utilities to manage dynamic memory.
#include <new>        // This header describes functions used to manage dynamic storage in C++.
#include <numeric>    // This header describes a set of algorithms to perform certain operations on sequences of numeric values.
#include <ostream>    // Header providing the standard output stream class.
#include <queue>      // Header that defines the queue and priority_queue container adaptor classes.
#include <set>        // Header that defines the set and multiset container classes.
#include <sstream>    // Header providing string stream classes.
#include <stack>      // Header that defines the stack container class.
#include <stdexcept>  // This header defines a set of standard exceptions that both the library and programs can use to report common errors.
#include <streambuf>  // Header providing the streambuf buffer class, to be used in combination with input/output streams.
#include <string>     // This header introduces string types, character traits and a set of converting functions.
#include <typeinfo>   // This header defines types used related to operators typeid and dynamic_cast.
#include <utility>    // This header contains utilities in unrelated domains (e.g swap).
#include <valarray>   // This header declares the valarray class and its auxiliary classes and functions (operation is e.g. pow).
#include <vector>     // Header that defines the vector container class.

#include "Cepek_cpp_chapter2.h"

using namespace std;

int main(int argc, char **argv)
{
	cout << "Max of 2 and 3 is: "<< max(2,3) << endl;
	return(0);
}
