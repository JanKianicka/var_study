/*
 * Questions and challenges
 *
 * 1. Whereas I have one name space I can not have new() function for each object. Or it is possible to declare one new() function,
 * one destroy, one destroy function? But even though particular implementations would have to be genuine.
 *
 * 2. What about polymorphism? Can I have array of pointers which point to either square or triangle and to run
 * some sum() function for this array and calculate overall circuits (or content if implemented). How to do this
 * when we do not want to know exact particular type of each element?
 *
 */


#include <stdio.h>
#include <stdlib.h>

#include "Triangle.h"
#include "Square.h"

int main(void) {
	double a = 10;
	double b = 3;
	double c = 5;

	double circuit;

	triangle_t *my_triangle=NULL;
	triangle_t *second_triangle=NULL;
	square_t *first_square=NULL;
	square_t *second_square=NULL;

	my_triangle = Triangle.new(a,b,c);
	second_triangle = Triangle.new(a*2, b*2, c*2);

	first_square = Square.new(a);
	second_square = Square.new(a*2);

	printf("Defined triangle: %.2f, %.2f, %.2f\n", my_triangle->a, my_triangle->b, my_triangle->c);
	printf("Second triangle: %.2f, %.2f, %.2f\n", second_triangle->a, second_triangle->b, second_triangle->c);

	circuit = Triangle.circuit(my_triangle);
	printf("Circuit of my triangle: %.2f \n", circuit);

	circuit = Square.circuit(first_square);
	printf("Circuit of my first square: %.2f \n", circuit);

	Triangle.destruct(my_triangle);
	Triangle.destruct(second_triangle);

	Square.destruct(first_square);
	Square.destruct(second_square);


	/*puts("Hello World"); /*
	 *
	 * prints Hello World */
	return EXIT_SUCCESS;
}
