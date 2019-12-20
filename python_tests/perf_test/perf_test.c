#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <time.h>

main(int argc, char *argv[])
{
	printf("Start\n");
	int64_t size = 100000000;
	// we have to allocate the array on heap not on stack
	double *array = (double *) malloc(size*sizeof(double));
	double i=0.0;
	int64_t j;
	double out;
	clock_t start, end;
	double cpu_time_used;
	printf("size: %d\n",size);
	start = clock();
	for( j=0; j<size; j++ ){
		array[j] = i;
		i = i+0.0001;
	}

	for( j=0; j<size; j++ ){
		out = sin(array[j]);
	}

	free(array);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Duration: %.2f\n", cpu_time_used);
	printf("Exited\n");
}
