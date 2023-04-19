#pragma once
#include "Siso.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
using namespace std;

class Arx : Siso {

public:
	Arx(int ndA, int ndB, int nk);
	~Arx();
	void setParameters(double* A, double* B);
	double simulate(double input);

protected:
	//double output;
	//double input;
	//double noise;
	int dA, dB, k;
private:
	double* inputBuffer, * outputBuffer;
	double* paramA, * paramB;

};

//creating arrays of given size while initializing an object and filling them with zeroes
Arx::Arx(int ndA, int ndB, int nk)
{
	dA = ndA;
	dB = ndB;
	k = nk;
	paramA = new double[ndA];
	paramB = new double[ndB];
	inputBuffer = new double[ndB + nk];
	outputBuffer = new double[ndA];

	fill_n(paramA, ndA, 0);
	fill_n(paramB, ndB, 0);
	fill_n(inputBuffer, ndB + nk, 0);
	fill_n(outputBuffer, ndA, 0);
}

Arx::~Arx() {
	delete[] paramA;
	delete[] paramB;
	delete[] inputBuffer;
	delete[] outputBuffer;
}
void Arx::setParameters(double* A, double* B)
{
	//paramA = A;
	//paramB = B;

	for (int i = 0; i < dA; i++)
	{
		paramA[i] = A[i];
	}
	for (int i = 0; i < dB; i++)
	{
		paramB[i] = B[i];
	}

}

// copying parameters


//y(i) = u(i) * (b0 + b1*z^(-1) + ... + bdB*z^(-dB)) * z^(-k) + e - y(i) * (a1*z^(-1) + ... + adA*z^(-dA))
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
