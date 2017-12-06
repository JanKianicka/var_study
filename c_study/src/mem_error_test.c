#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void my_test_loop();

int main(int argc, char **argv)
{
	const char *text = "Here I am.\n";
	char *text3;
	int i;

	//text = (char*)malloc(12*sizeof(char));
	// sprintf(text, "%s","Here I am.\n");
	char *text2 = strdup(text);
	printf("Pointer to text is: %s, %p\n", text);

	printf("Pointer to text2 is: %s, %p\n", text2);

	free(text2);
	for(i=0;i<10;i++)
	{
		text3 = (char*)malloc(1*sizeof(char));
		free(text3);
	}

	my_test_loop();

	return(0);
}

void my_test_loop()
{
	int i;
	char *buf;

	for(i=0; i<10; i++)
	{
		buf = (char*)malloc(3*sizeof(char));
	}
}
