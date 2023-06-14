#include "Arx.h"

Arx::Arx(int ndA, int ndB, int nk)
{
	dA = ndA;
	dB = ndB;
	k = nk;
	paramA.resize(ndA);
	paramB.resize(ndB);
	inputBuffer.resize(ndB + nk);
	outputBuffer.resize(ndA);

}

Arx::~Arx() {
}

void Arx::setParameters(vector<double> A, vector<double> B)
{
	paramA = A;
	paramB = B;
}

double Arx::simulate(double input)
{
	double output = 0;

	//moving all the elements one position to ther right
	for (int i = dB + k - 1; i > 0; i--)
	{
		inputBuffer[i] = inputBuffer[i - 1];
	}
	//setting input as first value in buffer and adding its part to output
	inputBuffer[0] = input;

	//calculating part of output (minding the delay)
	for (int i = 0; i < dB; i++)
	{
		output += inputBuffer[i + k] * paramB[i];
	}

	//first calculating then moving one pos to the right, paramA starts from a1z^(-1)
	for (int i = dA - 1; i > 0; i--)
	{
		output -= outputBuffer[i] * paramA[i];
		outputBuffer[i] = outputBuffer[i - 1];
	}
	//add noise to the signal
	//output += rand() % 3;

	//saving current output or next iterations
	outputBuffer[0] = output;

	return output;
}
