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

/// <summary>
/// Class PID regulator
/// 
/// Depending on set parameters works as P, PI, PD, PID. Set values to desirde parts and leave rest as 0
/// </summary>
class controllerPID : Regulator {

public:
	/// <summary>
	/// Constructor of PID regulator.
	/// </summary>
	/// <param name="nP">Proportional Gain</param>
	/// <param name="nI">Integral Gain</param>
	/// <param name="nD">Derivative Gain</param>
	controllerPID(double nP, double nI, double nD);
	~controllerPID();

	/// <summary>
	/// Calculate response of regulator to the given error
	/// </summary>
	/// <param name="error">Error, input signal for regulator</param>
	/// <returns>Output value of regulator</returns>
	double simulate(double input);

protected:
	double output = 0; ///< Output of regulator to be returned
	double P; ///< Proportional Gain
	double I; ///< Integral Gain
	double D; ///< Derivative Gain
	double integral = 0; ///< Value of calulated integral
	double derivative = 0; ///< Value of calculated derivative
	double dt = 0.01; ///< sampling itme
	double prevError = 0; ///< Value for storing previous error
	int MAX = 1000000;
	int MIN = -1000000;
};
