#include <stdio.h>

/* global variable */
const unsigned short int status = '0';

int main(int argc, char *argv[]){
	/* set of local variables */
	unsigned char a;
	int b, c, d;
	float e;
	double f = 0.000025;
	int x, w, y, z;
	z = 10;
	w = 9;
	y = 5;

	fprintf(stdout, "This my first lection from this book.\n");
	fprintf(stdout, "Global status: %c, and local double: %.6f\n",status, f);

	/* arithmetic operations */
	x=((++z)-(w--)) % 100;
	printf("Integer x is %d\n", x);

	/* x = x*(y + 2) */
	x *= y + 2;
	printf("x after evalution of x*(y + 2) is: %d \n",x);

	/* order of priority
	 * ( )  [  ]  -> .
		 !  $\sim$ - * & sizeof cast ++ -
		       (these are right->left)
		 * / %
		 + -
		 < <= >= >
		 == !=
		 &
		 $\wedge$		 |
		 &&
		 ||
		 ?:        (right->left)
		 = += -= (right->left)
		 ,   (comma)*/

	/* ( a < 10 ) && ( ( 2 * b ) < c ) */
	d = a < 10 && 2 * b < c;
	printf("d is: %i",d);

	fflush(stdout);
	return (0);
}
