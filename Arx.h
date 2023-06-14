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
	/// <summary>
	/// Constructor of Arx class
	/// </summary>
	/// <param name="ndA">Order of polynomial A</param>
	/// <param name="ndB">Order of polynomial B</param>
	/// <param name="nk">input-output delay</param>
	Arx(int ndA, int ndB, int nk);
	~Arx();


	/// <summary>
	/// Set values of models parameters. 
	/// </summary>
	/// <param name="A">vector of parameters A</param>
	/// <param name="B">vector of parameters B</param>
	/// @returns nothing
	void setParameters(vector<double> A, vector<double> B);

	/// <summary>
	/// Simulating output of the Arx model. 
	/// 
	/// Formula for the output **y** in the moment **i**:
	/// [ y(i) = u(i) * (b0 + b1*z^(-1) + ... + bdB*z^(-dB)) * z^(-k) + e - y(i) * (a1*z^(-1) + ... + adA*z^(-dA)) ]
	/// where **a** and **b** are parameters of the polynomial A and B
	/// </summary>
	/// <param name="input"> Input to the model <double> </param>
	/// <returns>Output of the model <doublel> </returns>
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
