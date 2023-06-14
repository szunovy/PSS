#include "controllerPID.h"


controllerPID::controllerPID(double nP, double nI, double nD)
{
	P = nP;
	I = nI;
	D = nD;
};

controllerPID::~controllerPID() {
};


double controllerPID::simulate(double error)
{
	integral += error * dt;
	derivative = (error - prevError) / dt;

	output = P * error + I * integral + D * derivative;

	if (output > MAX)
	{
		output = MAX;
	}

	if (output < MIN)
	{
		output = MIN;
	}

	prevError = error;
	return output;
};
