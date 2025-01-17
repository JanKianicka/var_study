/* This example is taken from:
 * http://timmurphy.org/2010/05/04/pthreads-in-c-a-minimal-working-example/
 * and slightly modified to see how joining of threads works. */

#include <pthread.h>
#include <stdio.h>
#include <math.h>

/* this function is run by the second thread */
void *inc_x(void *x_void_ptr)
{
double t=12.56;
int i;

/* increment x to 100 */
int *x_ptr = (int *)x_void_ptr;
while(++(*x_ptr) < 100);
sleep(5);
for(i=0; i<100;i++){
	sin(t);
	cos(t);
	printf("tan t: %.3f\n",tan(t));
}
printf("x increment finished\n");
printf("i:%.3f\n",i);

/* the function must return something - NULL will do */
return NULL;

}


int  main()
{
	int x = 0, y = 0;

	/* show the initial values of x and y */
	printf("x: %d, y: %d\n", x, y);

	/* this variable is our reference to the second thread */
	pthread_t inc_x_thread;

	/* create a second thread which executes inc_x(&x) */
	if(pthread_create(&inc_x_thread, NULL, inc_x, &x)) {

	fprintf(stderr, "Error creating thread\n");
	return 1;

	}
	/* increment y to 100 in the first thread */
	while(++y < 100);

	printf("y increment finished\n");

	/* wait for the second thread to finish */
	if(pthread_join(inc_x_thread, NULL)) {

	fprintf(stderr, "Error joining thread\n");
	return 2;

	}

	/* show the results - x is now 100 thanks to the second thread */
	printf("x: %d, y: %d\n", x, y);

	return 0;
}
