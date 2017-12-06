#include <stdio.h>
#include <stdlib.h>

#include "Square.h"

square_type_k Square = {
	square_new,
	square_circuit,
	square_destroy
};

square_t*
square_new(double a){
	square_t *self;
	self = (square_t*) malloc(sizeof(square_t));
	self->a = a;

	return self;
}

void
square_destroy(square_t *self){
	free(self);
}

double
square_circuit(square_t *self){
	double circuit;
	circuit = 4*self->a;
	return circuit;
}
