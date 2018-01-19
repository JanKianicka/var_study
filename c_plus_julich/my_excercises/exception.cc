#include <iostream>
#include <string>
#include <exception>

class myexception : public std::exception
{
    public:
    myexception(double vl) noexcept : x(vl) {}
    const char * what() const noexcept override
    {
        std::string msg=("bad parameter value ")+
                        std::to_string(x);
        return msg.c_str();
    }
    private:
    double x=0;
};

class myexception2: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Bad parameter value.";
  }
} myex2;

double f(double x) 
{
    double answer=1;
    if (x>=0 and x<10) {
        while (x>0) {
            answer*=x;
            x-=1;
        }
    } else {
      throw(myexception(x));
      // throw myex2;
    }
    return answer;
}


int main()
{
    double x=9.0;
    /*    try {
        std::cout<<"Enter start point : ";
        std::cin >> x;
	while(x<0 or x>10){
	  std::cout << "Give number between 0 and 10" << std::endl;
	  std::cin >> x;
	}
        auto res=f(x);
        std::cout <<"The result is "<<res<<'\n';

    } catch (myexception &ex) 
    {
        
        std::cerr<<"Cought exception "<<ex.what()<<'\n';
	
    }*/

    // Zoltan's solution with infinite while loop
    bool invalid_value = true;
    while(invalid_value){
      try {
        std::cout<<"Enter start point : ";
        std::cin >> x;
        auto res=f(x);
        std::cout <<"The result is "<<res<<'\n';
	
	invalid_value = false;

      } catch (myexception &ex) 
	{
        
        std::cerr<<"Cought exception "<<ex.what()<<'\n';
	
	}
    }


}


