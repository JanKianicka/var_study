#ifndef _PRINTORIG_
#define _PRINTORIG_

#define some_func(...) printWrapp(__VA_ARGS__)

//void printWrapp(double a);
typedef struct testStruct{
    double D;
    char Name[10];
    long int I;
}TestStruct;

typedef struct {
  //int (* const bar)(int, char *);
  void (* printWrapp)(void);
} namespace_struct;
extern namespace_struct const Orig;

void testStructArray(TestStruct *structures);


#endif /* _PRINTORIG_*/
