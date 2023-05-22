#pragma once
#include "Siso.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <strstream>
using namespace std;
//srand(time(NULL));

/// Class of generator. 
///
/// Class for generating excitacion signal
class Generator : Siso {

public:
	Generator(string ntype, double npar1, double npar2);
	~Generator();
	double generate();


protected:
	int type;	///< type of generated signal
	double par1; ///< value of first parameter
	double par2;  ///< value of seond parameter
	int step;  ///< value of current program iteration
	double output;
	int sign;
};


Generator::Generator(string ntype, double npar1, double npar2)
{
	par1 = npar1;
	par2 = npar2;
	step = 0;
	sign = -1;
	if (ntype == "kronecker") { type = 1; };
	if (ntype == "sine") { type = 2; };
	if (ntype == "rectangular") { type = 3; };
	if (ntype == "noise") { type = 4; };
}

Generator::~Generator() {

}


double Generator::generate()
{


	switch (type)
	{

	case 1:
		if (step > 0)
			output = 0;
		else
			output = 1;
			break;

	case 2: //param1 - amplitude, param2 - frequency
		output = - (par1 * sin(2 * 3.14 * step * par2)); 
			break;

	case 3: //param1 - amplitude, param2 - wave width
		if (step % int(par2) == 0)
			sign = sign * (-1);
		output = sign * par1;
			break;

	case 4:
		output = ((double)rand() / (double)(RAND_MAX)); //param1 - maximum noise value, param2 and step - not used
			break;

	default:
		output = 1;
	}

	step++;
	return output;
}
