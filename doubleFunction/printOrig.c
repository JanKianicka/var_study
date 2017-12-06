/*
 * printOrig.c
 *
 *  Created on: Oct 23, 2013
 *      Author: kianicka
 */

#include <stdio.h>
#include "printOrig.h"
//#include "printWrapSoruce.h"

static void printWrapp(void){
    printf("This is original wrapp.\n");
}

void printWrapWrap(void){
    printf("Calling of local Orig funcion.\n");
    some_func();
}

//static void printWrapp(void) {
//    printf("This is original wrapp.\n");
//}

namespace_struct const Orig = { printWrapp };

void testStructArray(TestStruct *structures)
{
    int arrayLength;
    printf("I am in testStructArray.\n");
    arrayLength = sizeof(structures)/sizeof(structures[0]);
    printf("Sizeof structures in function: %d\n", sizeof(structures));
    printf("Array length in function: %d\n", arrayLength);
}

