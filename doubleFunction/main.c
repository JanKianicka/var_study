/*
 * main.c
 *
 *  Created on: Oct 23, 2013
 *      Author: kianicka
 */

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "printWrapp.h"
#include "printOrig.h"

int main()
{
    int a = 1;
    printf("Hello world.\n");
    printWrapp(a);
    Orig.printWrapp();
    some_func(a);
    printWrapWrap();
    //int *int_arrray;

    int int_array[4] = {1,2,3,4};
    TestStruct strctureElement;
    strctureElement.D       = 15.23;
    strncpy(strctureElement.Name,"A",10);
    strctureElement.I       = 15452;
    TestStruct testS[]    = {strctureElement, strctureElement, strctureElement};
//    //TestStruct *testS = (TestStruct*)NULL;
//    TestStruct *testS = (TestStruct *)malloc(10*sizeof(TestStruct));
//    //testS[2].D = 132343.4324;
//    testStructArray(testS);
    int arraySize;
    int structSize;
    int testSSize;
    int arrayLength;

    arraySize   = sizeof(int_array);
    structSize  = sizeof(strctureElement); ///sizeof(testS[0]);
    testSSize   = sizeof(testS);

    printf("Original Sizeof int_array is: %d\n",arraySize);
    printf("Original Sizeof strctureElement is: %d\n",structSize);
    printf("Original Sizeof testS is: %d\n",testSSize);
    printf("Array length in main is: %d\n",sizeof(testS)/sizeof(testS[0]));

    testStructArray(testS);

//    free(testS);
}
