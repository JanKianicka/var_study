#include <stdio.h>

int main(){
	int i=0;
	int j=2;
	int z = 1;
	int o;
	char a = 'A';
	int numberofvowels, numberofspaces, numberofconstants = 0;

	printf("Marshal: conditionals. \n");
	o = (i == 0) ? j : z;
	printf("o:%d\n",o);


	switch (a){
		case 'A':
		case 'E':
		case 'I':
		case 'O':
		case 'U':
			numberofvowels++;
			break;
		case ' ':
			numberofspaces++;
			break;
		default:
			numberofconstants++;
			break;
	}
	printf("Number of vowels: %d \n", numberofvowels);

	return (0);
}
