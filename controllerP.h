#pragma once
#include "Regulator.h"
#include "Siso.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <stdio.h>

using namespace std;

//srand(time(NULL));

/// Class of generator. 
///
/// Class for creating arx models of objects.
class controllerP : Regulator {

public:
	controllerP(double nP);
	~controllerP();
	double simulate(double input);

protected:
	double output;
	double P;
};


controllerP::controllerP(double nP)
{
	double P = nP;
};

controllerP::~controllerP() {
};


double controllerP::simulate(double input)
{
	output = P * input;
	return output;
};
