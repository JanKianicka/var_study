#include <iostream>
#include <string>
#include <cmath>

// "const" variables can be initialised using function
// calls and mathematical operations.
const double pi=acos(-1);
const double twoPi=2*pi;

// whereas acos is not available during compile type for gcc
// we could not put constexpr here.
// We can replace it like this:
// constexpr const double pi=3.14159265359;
// constexpr const double twoPi=2*pi;

class Angle
{
private:
    double vl{0};
    bool showdeg{false};
    // A private function
    void map_to_period();
public:
    // Default constructor. Default value for "Angle"s
    constexpr Angle() = default;
    // Constructor assigning a value in radians
    Angle(double val);
    // Constructor taking value and a showdegree flag
    Angle(double val, bool flg);
    // Copy and move constructors
    constexpr Angle(const Angle &)=default;
    constexpr Angle(Angle &&)=default;
    // Function to set a flag to show degrees instead of radians    
    inline void show_degrees(bool vl) { showdeg=vl; }
    // Get the value
    inline constexpr double value() const { return vl; }
    // Set the value
    void value(double v);
    // Assign an angle to another.
    // Why should one have the assignment operator return 
    // a reference rather than an ordinary variable ?
    // ANS: that we can concatenate a = b = 1;
    // f(a=6) - would make copy 
    constexpr Angle & operator=(const Angle &) = default;
    constexpr Angle & operator=(Angle &&) = default;
    // Add two angles
    Angle operator+(const Angle &a) const;
    // Increment by another angle
    Angle & operator+=(const Angle &a);
    // Multiplying an angle with a double
    Angle operator*(double x) const;
    
    // This one is not a member function! It is a friend.
    // A function declared as a friend inside a class can
    // access the private members of the class. Try to
    // compile with and without this friend declaration, and
    // see what the compiler says!
    // ANS: not access to the private members:
    // angles.cc:120:15: error: 'bool Angle::showdeg' is private within this context
    // if (not a.showdeg) {

    friend std::ostream & operator<<(std::ostream &os, 
                                     const Angle &a);
};

// Implementation of constructor with a value in radians
Angle::Angle(double val) : Angle{val,false} {}

Angle::Angle(double val, bool flg) : showdeg{flg}
{
    value(val);
}

// Implementation of set value
void Angle::value(double v) {
    vl=v;
    map_to_period();
}

// Implementation of the increment operator
Angle & Angle::operator+=(const Angle &a)
{
    value(vl+a.vl);
    return *this;
}

// Addition
Angle Angle::operator+(const Angle &a) const
{
    return {vl+a.vl};
}

// Implementation of multiplication with a double
Angle Angle::operator*(double factor) const
{
    return {vl*factor, showdeg};
}

// Implementation of left multiplication with a double
// This function allows you to write Angle a,b; a=0.5*b;
// Since 0.5*b has a double on the left side, it can not
// be treated by a member function of class Angle. Member
// operators put the class on the left. But a function like
// this one, outside the class declaration should do the job.
Angle operator*(double factor, const Angle &a)
{
    return a*factor;
}

// Implementation of private function map_to_period()
void Angle::map_to_period()
{
    if (fabs(vl)>pi) {
        while (vl>pi) vl -= twoPi;
        while (vl<-pi) vl += twoPi;
    }
}

// Implementation of operator << for output
// Also, try to compile without the "friend" line in the class
// declaration.
std::ostream & operator<<(std::ostream &os, const Angle &a)
{
    if (not a.showdeg) {
        os << a.vl << " radians ";
    } else {
        os << a.vl*180/pi << " degrees ";
    }
    return os;
}

int main()
{
    Angle a,b(0.5*pi),c;
    a=0.5*b;
    
    std::cout << " a = " << a 
              << " b = " << b
              << " c = " << c
              << '\n';
              
    c.show_degrees(true);
    std::cout << " a = " << a 
              << " b = " << b
              << " c = " << c
              << '\n';

    c=b=a;
    std::cout << " a = " << a 
              << " b = " << b
              << " c = " << c
              << '\n';
              
}
