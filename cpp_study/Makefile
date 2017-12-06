CXXFLAGS =	-O2 -g -Wall -fmessage-length=0
CPPUNIT_PATH=/usr/lib64
CPPUNIT_INCLUDE=/usr/include/cppunit

OBJS =		cpp_hello_world.o

LIBS =

TARGET =  cpp_hello_world
TARGET += ftest
TARGET += Cepek_cpp_chapter1
TARGET += Cepek_cpp_chapter2
TARGET += Cepek_cpp_array_class_exerc
TARGET += Cpp_course_vector_examples

#$(TARGET):	$(OBJS)
#	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

ftest: ftest.o fractiontest.o Fraction.o
	gcc -o ftest ftest.o fractiontest.o Fraction.o -L${CPPUNIT_PATH}/lib -lstdc++ -lcppunit -ldl

Fraction.o: Fraction.cc fraction.h
	gcc -c Fraction.cc
	
fractiontest.o: fractiontest.cc
	gcc -c fractiontest.cc -I${CPPUNIT_INCLUDE}

ftest.o: ftest.cc
	gcc -c ftest.cc -I${CPPUNIT_INCLUDE}

Cepek_cpp_chapter1: Cepek_cpp_chapter1.o
	g++ -o Cepek_cpp_chapter1 Cepek_cpp_chapter1.o

Cepek_cpp_chapter1.o: Cepek_cpp_chapter1.cpp Cepek_cpp_chapter1.h
	g++ -c Cepek_cpp_chapter1.cpp

Cepek_cpp_chapter2: Cepek_cpp_chapter2.o
	g++ -o Cepek_cpp_chapter2 Cepek_cpp_chapter2.o

Cepek_cpp_chapter2.o: Cepek_cpp_chapter2.cpp Cepek_cpp_chapter2.h
	g++ -c Cepek_cpp_chapter2.cpp

Cepek_cpp_array_class_exerc: Cepek_cpp_array_class_exerc.o
	g++ -o Cepek_cpp_array_class_exerc Cepek_cpp_array_class_exerc.o
	
Cepek_cpp_array_class_exerc.o: Cepek_cpp_array_class_exerc.cpp Cepek_cpp_array_class_exerc.h 
	g++ -c -g Cepek_cpp_array_class_exerc.cpp

Cpp_course_vector_examples:Cpp_course_vector_examples.cpp
	g++ -o Cpp_course_vector_examples Cpp_course_vector_examples.cpp

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) ftest *.o
