#include <iostream>
#include <cmath>

struct complex_number {
    double real=0, imaginary=0;
    complex_number conjugate()
    {
        return {real,-imaginary};
    }
    double modulus()
    {
        return sqrt(real*real+imaginary*imaginary);
    }

    //    complex_number add(complex_number b)
    complex_number operator+(complex_number b)
    {
        return {real+b.real, imaginary+b.imaginary};
    }
    complex_number multiply(complex_number b)
    {
        return {real*b.real-imaginary*b.imaginary, real*b.imaginary+imaginary*b.real};
    }
    complex_number operator*(complex_number b)
    {
      // A.r*B.r - A.i*B.i, A.r*B.i + A.i*B.r - multiplication 
      return {real*b.real-imaginary*b.imaginary, real*b.imaginary+imaginary*b.real};
    }
    
};

int main()
{
  complex_number z1{4.9,0.3},z2{1.2,0.23},z3,z4,z5, z6;
    z3=z1.multiply(z2);
    z4=z3.conjugate();
    z5=z1+z2;
    z6=z1*z2;

    std::cout<<"z3 = ("
             <<z3.real<<", "<<z3.imaginary<<")"<<std::endl;
    std::cout<<"z4 = ("
             <<z4.real<<", "<<z4.imaginary<<")"<<std::endl;
    std::cout<<"z5 = ("
             <<z5.real<<", "<<z5.imaginary<<")"<<std::endl;
    std::cout<<"z6 = ("
             <<z6.real<<", "<<z6.imaginary<<")"<<std::endl;
}
