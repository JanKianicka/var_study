#include <stdio.h>

#include "new.h"
#include "Object.h"
#include "Set.h"

int main ()
{
	int i;
	void *x;
	void * s = new(Set);
	void * a = add(s, new(Object));
	void * b = add(s, new(Object));
	void * c = new(Object);
	for(i=0; i<5; i++){
		x = add(s, new(Object));
	}

	if (contains(s, a) && contains(s, b))
		puts("ok");

	if (contains(s, x))
		puts("contains?");

	if (differ(a, add(s, a)))
		puts("differ?");

	if (contains(s, drop(s, a)))
		puts("drop?");

	delete(drop(s, b));
	delete(drop(s, c));

	return 0;
}
