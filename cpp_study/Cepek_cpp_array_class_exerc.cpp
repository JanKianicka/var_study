// This stupid file has disappeared
// So once more:
// we try namespaces, dynamical arrays and basics of classes
// I should have probably just go through some lessons
// not to do everything at once.
#include <iostream>

#include "Cepek_cpp_array_class_exerc.h"

using namespace std;

class dArray{
public:
	dArray (int dim) {
		N = dim;
		p = new double[N];
	}
	~dArray() { delete[] p;}
	double& getMember(int i) { return p[i];}
	void manipul(){
		add_pi(N,p);
	}
	int dim() const { return N;}
private:
	int N;
	double* p;
};

// It is neccessary to allocated memory (define the variable)
// this has to be outside of main() function
int static_study::S::counter = 0;

int main(){
	double mem;
	dArray* array1 = new dArray(3);
	mem = array1->getMember(0);
	cout << "mem: " << mem << endl;
	array1->manipul();
	mem = array1->getMember(0);
	cout << "mem: " << mem << endl;

	// namespaces
	gps::Point *gps_point = new gps::Point(1263727.34, 5435465.43, 764356565.34);
	carto::Point *carto_point = new carto::Point(23.45, 16.34);
	cout << gps_point->toString() << endl;
	cout << carto_point->toString() << endl;

	// static attribute counter
	cout << "number of objects S when starting:" << static_study::S::amount_of_instances() << endl;
	static_study::S *loc_S = new static_study::S;
	cout << "number of objects S after creating one instance:" << static_study::S::amount_of_instances() << endl;
	delete loc_S;
	cout << "number of objects S after deletion:" << static_study::S::amount_of_instances() << endl;

}
