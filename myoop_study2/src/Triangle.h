#ifndef TRIANGLE_H
#define TRIANGLE_H

typedef struct triangle_
{
	double a;
	double b;
	double c;
} triangle_t;

typedef struct triangle_type_
{
	triangle_t *(*new)(double a, double b, double c);
	double (*circuit)(triangle_t *self);
	void (*destruct)(triangle_t *self);
} triangle_type_k ;

extern triangle_type_k Triangle;

triangle_t * new(double a, double b, double c);
double circuit(triangle_t *self);
void triangle_destroy(triangle_t *self);

#endif
