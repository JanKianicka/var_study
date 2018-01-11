#include <iostream>
#include <string>

int main()
{
  std::string message{R"(OBJ=a.o \
    .o\
    .o
)"}; // you write exactly as it is seen in the code

  std::string message2{R"delim((OBJ=a.o \
    .o\
    .o()
))delim"}; // now with delim


    std::cout << "Use a single backslash character at the end of the line to continue input to the next line, as shown ...\n"
      //              << "OBJ=a.o \\\n\tb.o\\\n\tc.o\n";
	      << message;
    std::cout << message2;

}
