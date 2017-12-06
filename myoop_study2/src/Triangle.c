#include <stdio.h>
#include <stdlib.h>

#include "Triangle.h"

triangle_type_k Triangle = {
	new,
	circuit,
	triangle_destroy
};

triangle_t*
new(double a, double b, double c){
	triangle_t *self;
	self = (triangle_t*) malloc(sizeof(triangle_t));
	self->a = a;
	self->b = b;
	self->c = c;

	return self;
}

void
triangle_destroy(triangle_t *self){
	free(self);
}

double
circuit(triangle_t *self){
	double circuit;
	circuit = self->a + self->b + self->c;
	return circuit;
}
