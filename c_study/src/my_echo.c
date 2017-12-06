/* myecho.c */
/* example subprocess file from execve man page */

#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
   int j;

   for (j = 0; j < argc; j++)
	   printf("argv[%d]: %s\n", j, argv[j]);
   fprintf(stderr, "my_echo message to sterr.\n");

   exit(EXIT_SUCCESS);
}
