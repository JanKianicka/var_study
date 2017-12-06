#ifndef SQUARE_H
#define SQUARE_H

typedef struct square_
{
	double a;
} square_t;

typedef struct square_type_
{
	square_t *(*new)(double a);
	double (*circuit)(square_t *self);
	void (*destruct)(square_t *self);
} square_type_k ;

extern square_type_k Square;

square_t * square_new(double a);
double square_circuit(square_t *self);
void square_destroy(square_t *self);

#endif
