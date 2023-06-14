#include "Generator.h"

Generator::Generator()
{
	step = 0;
	sign = -1;
	kronecker = 0;
	sinAmp = 0;
	sinFreq = 0;
	rectAmp = 0;
	rectFreq = 0;
	noiseVar = 0;
	output = 0;
	//type = 0;
};

Generator::~Generator() {
};


void Generator::Kronecker() {
	kronecker = 1;
};


void Generator::Sinus(double nsinAmp, double  nsinFreq) {
	sinAmp = nsinAmp;
	sinFreq = nsinFreq;
};


void Generator::Rectangle(double nrectAmp, double  nrectFreq) {
	rectAmp = nrectAmp;
	rectFreq = nrectFreq;
};


void Generator::Noise(double nnoiseVar) {
	noiseVar = nnoiseVar;
};



double Generator::generate()
{
	output = 0;
	if (kronecker != 0) {
		if (step > 0)
			output += 0;
		else
			output += 1;
	}
	if (sinAmp != 0) {
		//param1 - amplitude, param2 - frequency
		output += -(sinAmp * sin(2 * 3.14 * step * sinFreq));
	}

	if (rectAmp != 0) { //param1 - amplitude, param2 - wave width
		if (step % int(rectFreq) == 0)
			sign = sign * (-1);
		output += sign * rectAmp;
	}
	if (noiseVar != 0) {
		output = ((double)rand() / (double)(RAND_MAX)); //param1 - maximum noise value, param2 and step - not used
	}
	step++;
	return output;
};

