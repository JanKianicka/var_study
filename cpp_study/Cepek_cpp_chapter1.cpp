#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <cmath>
#include <stdbool.h>

#include "Cepek_cpp_chapter1.h"

using namespace std;

void cycles()
{
	// numerical computation of sqare of the positive number
	double N = 3;
	double x = N/2;

	while (fabs(x*x - N)/N > 1e-6)
		x = 0.5 * ( x + N/x);

	cout << "Sqare of " << N << " is " << x << ", precision " << x*x - N << endl;

	// quadratic equation
	// a*x2 + b*x + c
	double a = 3;
	double b = 2;
	double c = 1;

	double D = b*b - 4*a*c;
	// printf("%.3f",D);

	cout << "Roots of quadratic equation:" << endl;
	if (D >= 0){
		D = sqrt(D);

		cout << "x1 = " << (-b + D) / (2*a) << " "
			 << "x2 = " << (-b - D)/ (2*a) << endl;
	}
	else {

		D = sqrt(-D);
		cout << "x12 = " << -b / (2*a) << " +-i " << D/(2*a) << endl;
	}
}

int read_write_file(const char *in_file, const char *out_file)
{
	ifstream Input(in_file);
	ofstream Output(out_file);

	int index;
	Input >> index;
	cout << "Read index from file: " << index << endl;

	double a, b, c;
	Input >> a >> b >> c;
	Output << "and read three numbers of double type: " << a << endl;
	Output << b << endl;
	Output << c << endl;

	/* Formated output */
	Output.setf(ios::fixed);
	Output.precision(4);
	Output << "c with precision 4: " << c << endl;
	Output << "c with precission 7:" << setw(30) << setprecision(7) << c << endl;

	return EXIT_SUCCESS;
}

int reference_return_values(double rho, double phi, double &coord_x, double &coord_y)
{
	coord_x = rho * cos(phi);
	coord_y = rho * sin(phi);

	return true;
}


int main()
{
	int i_var = 12;
	cout << "variable i_var = " << i_var << endl;
	int octal   = 010;
	cout << "octal value 010 is " << octal << " in decimal system. " << endl;

	int x;
	cout << "value of x is not defined! x = " << x << endl;
	double Q = 12.3;
	char q = 'P';
	cout << "Q is " << Q << " and q variable contains " << q << endl;

	cout << 7/3 << " " << 7.0/3 << endl;

//	int number;
//	cout << "Give natural number:";
//	cin >> number;
//	cout << "You have given number " << number << endl;

	const char* in_file = "input1.txt";
	const char* out_file = "output1.txt";

	string test = "test";

	read_write_file(in_file, out_file);

	cycles();

	double coord_x;
	double coord_y;
	bool ret;

	ret = reference_return_values(3, 4, coord_x, coord_y);
	cout << "Function with references in use." << endl;
	cout << "ret " << ret << " coord_x " << coord_x << " coord_y " << coord_y << endl;

}
