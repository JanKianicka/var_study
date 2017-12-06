// piece-wise continuos linear function
//

#include <iostream>
#include <vector>

class PieceWise
{
private:
  double x;
  double y;
  double **vector = nullptr;
  int size;

public:
  PieceWise() = default;
  
  ~PieceWise(){
    if (vector) delete [] vector;
  }
   

};

// Here implement reading of the vector



int main()
{
  std::cout<<"Reading vector of values." << std::endl;
  PieceWise A;
}
