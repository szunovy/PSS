#pragma once
#include "Siso.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;

/// Class of ArX model. 
///
/// Class for creating arx models of objects.
class Arx : Siso {

public:
	Arx(int ndA, int ndB, int nk);
	~Arx();
	void setParameters(vector<double> A, vector<double> B);
	double simulate(double input);

protected:
	//double output;
	//double input;
	//double noise;
	int dA;	///< order of polynomial A
	int dB; ///< order of polynomial B
	int k;  ///< input output delay

private:
	vector< double > paramA; ///< vector of parameters of polynomial A
	vector< double > paramB; ///< vector of parameters of polynomial B
	vector< double > inputBuffer; ///< buffer for input values, for simulation purposes
	vector< double > outputBuffer; ///< buffer for output values, for simulation purposes
};

//creating arrays of given size while initializing an object and filling them with zeroes

/// <summary>
/// Constructor of Arx class
/// </summary>
/// <param name="ndA">Order of polynomial A</param>
/// <param name="ndB">Order of polynomial B</param>
/// <param name="nk">input-output delay</param>
Arx::Arx(int ndA, int ndB, int nk)
{
	dA = ndA;
	dB = ndB;
	k = nk;
	paramA.resize(ndA);
	paramB.resize(ndB);
	inputBuffer.resize(ndB + nk);
	outputBuffer.resize(ndA);
	
	//paramA2 = new double[ndA];
	//paramB2 = new double[ndB];
	//inputBuffer2 = new double[ndB + nk];
	//outputBuffer2 = new double[ndA];

	//fill_n(paramA, ndA, 0);
	//fill_n(paramB, ndB, 0);
	//fill_n(inputBuffer, ndB + nk, 0);
	//fill_n(outputBuffer, ndA, 0);
}

Arx::~Arx() {
	//delete[] paramA;
	//delete[] paramB;
	//delete[] inputBuffer;
	//delete[] outputBuffer;+
}

/// <summary>
/// Set values of models parameters. 
/// </summary>
/// <param name="A">vector of parameters A</param>
/// <param name="B">vector of parameters B</param>
/// @returns nothing
void Arx::setParameters(vector<double> A, vector<double> B)
{
	paramA = A;
	paramB = B;
	
	//for (int i = 0; i < A.size(); i++)
	//	paramA.push_back(A[i]);
	//for (int i = 0; i < A.size(); i++)
	//	paramB.push_back(B[i]);
}

// copying parameters





/// <summary>
/// Simulating output of the Arx model. 
/// 
/// Formula for the output **y** in the moment **i**:
/// [ y(i) = u(i) * (b0 + b1*z^(-1) + ... + bdB*z^(-dB)) * z^(-k) + e - y(i) * (a1*z^(-1) + ... + adA*z^(-dA)) ]
/// where **a** and **b** are parameters of the polynomial A and B
/// </summary>
/// <param name="input"> Input to the model <double> </param>
/// <returns>Output of the model <doublel> </returns>
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
