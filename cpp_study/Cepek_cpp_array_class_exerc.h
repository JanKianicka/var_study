#ifndef CEPEK_CPP_ARRAY_CLASS_EXERC
#define CEPEK_CPP_ARRAY_CLASS_EXERC

#include <string>
#include <sstream>

#define PI 3.14

using namespace std;

inline int add_pi(int size, double *p){
	int i;
	for(i = 0; i<size;i++){
		p[i] = PI+p[i];
	}
	return(0);
}

namespace gps{
	class Point{
	public:
		Point(double x_in, double y_in, double z_in){
			x = x_in;
			y = y_in;
			z = z_in;
		}
		string toString(){
			stringstream ss;
			ss.precision(17);
			ss << x << "," << y << "," << z;
			return ss.str();
		}
	private:
		double x;
		double y;
		double z;
	};
}

namespace carto{
	class Point{
	public:
		Point(double phi_in, double lamda_in){
			phi = phi_in;
			lamda = lamda_in;
		}
		string toString(){
			stringstream ss;
			ss.precision(17);
			ss << phi << "," << lamda;
			return ss.str();
		}
	private:
		double phi;
		double lamda;
	};
}

// Using static attributes to share information among
// class instances - for example counter of instances

namespace static_study{

class S {
	public:
		S() { counter++;}
		~S() { counter--;}
		static int amount_of_instances() { return counter; }

	private:
		static int counter; // declaration of static attribute
};


}




#endif
