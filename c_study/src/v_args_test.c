#include <stdio.h>
#include <stdarg.h>

int funct(char *string, ...)
{
	char *text;
	va_list ap;

	va_start(ap, string);
	printf("%s\n", string);

	while(*string){
		switch (*string++) {
		   case 's':              /* string */
			   text = va_arg(ap, char *);
			   printf("%s\n", text);
		}
	}
	va_end(ap);
}


int main(){
	funct("First string", "Second string", "Third string");
}
