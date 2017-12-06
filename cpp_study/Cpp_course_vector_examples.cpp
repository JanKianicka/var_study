// Taken on 16.12.2016 from
// https://www.tutorialspoint.com/cplusplus/cpp_stl_tutorial.htm

#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

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

int main() {
   // create a vector to store int
   vector<int> vec;
   int i;

   // display the original size of vec
   cout << "vector size = " << vec.size() << endl;

   // push 5 values into the vector
   for(i = 0; i < 5; i++){
      vec.push_back(i);
   }

   // display extended size of vec
   cout << "extended vector size = " << vec.size() << endl;

   // access 5 values from the vector
   for(i = 0; i < 5; i++){
      cout << "value of vec [" << i << "] = " << vec[i] << endl;
   }

   // use iterator to access the values
   vector<int>::iterator v = vec.begin();
   while( v != vec.end()) {
      cout << "value of v = " << *v << endl;
      v++;
   }

   // my own experiments - lets try vector of custom objects
   vector<Point*> vec_of_points;
   cout << "Initial size of vec_of_points:" << vec_of_points.size() << endl;
   for(i=0; i<7; i++){
	   Point *p = new Point(33+(double)i, 44+(double)i, 55+(double)i);
	   vec_of_points.push_back(p);
   }

//   Iterator did not work for me ...
//   vector<Point*>::iterator p_iter = vec_of_points.begin();
//   while( p_iter != vec_of_points.end()) {
//         cout << "value of point = " << p_iter << endl;
//         p_iter++;
//   }
   // this construct cause the system crash
   for(i=0; i<7; i++){
	   // vec_of_points[i]->toString(); - this has caused the system crash - memory allocation or CPU
	   Point *pp = vec_of_points.at(i);
	   cout << pp->toString() << endl;
   }


   return 0;
}
