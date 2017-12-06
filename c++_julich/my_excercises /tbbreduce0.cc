#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <tbb/tbb.h>

inline double f(double x)
{
    return tanh(x)*cos(x)*sin(x);
}

int main()
{
    constexpr const double llim=10.;
    constexpr const double ulim=120.;
    constexpr const double dx=1.0e-6;
    size_t N=(size_t) (ulim-llim)/dx;
    std::cout << "Starting serial computation.\n";
    auto t0 = std::chrono::high_resolution_clock::now();
    double ans_ser = [&](){
        double tmp=0;
        for (size_t i=0;i<N;++i) tmp+=f(llim+i*dx)*dx;
        return tmp;
    }();
    std::cout << "Integral with single thread = "<<ans_ser << '\n';
    auto t1 = std::chrono::high_resolution_clock::now();
    auto tser = std::chrono::duration<double>(t1-t0).count();
    std::cout << "Serial computation took " << tser <<'\n';
    auto t2 = std::chrono::high_resolution_clock::now();
    double resn = tbb::parallel_reduce(
                      tbb::blocked_range<size_t>(0,N),
                      double{},
                      [&](tbb::blocked_range<size_t> r,double in) {
                          for (auto i=r.begin();i!=r.end();++i) in+=f(llim+i*dx)*dx;
                          return in;
                      },
                      std::plus<double>()
                  );
    //resn -= f(llim)*dx/2;
      
    std::cout << "Integral = " << resn << '\n';
    auto t3 = std::chrono::high_resolution_clock::now();
    auto tpar = std::chrono::duration<double>(t3-t2).count();
    std::cout << "Parallel computation took " << tpar <<'\n';
    std::cout << "Observed speedup vs serial = "<<100.0*tser/tpar<<" %\n";
}


