#pragma once
#include "Siso.h"
#include "Exceptions.h"
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
/// Class for generating excitacion signal. Outputs sum of enabled signals. Signals are enabled and set by using appropriate method.
class Generator : Siso {

public:
	Generator();
	~Generator();

	/// <summary>
	/// Calculates sum of desired signals.
	/// </summary>
	/// <returns>Sum of enabled signals</returns>
	/// 
	double generate();
	/// <summary>
	/// Enabling Kronoecker signal
	/// </summary>
	void Kronecker();

	/// <summary>
	/// Enabling and setting parameters of sine wave. To disable set parameters to 0.
	/// </summary>
	/// <param name="nsinAmp">Amplitude of sine wave</param>
	/// <param name="nsinFreq">Frequency of sine wave</param>
	void Sinus(double nsinAmp, double nsinFreq);

	/// <summary>
	/// Enabling and setting parameters of rectangle wave. To disable set parameters to 0.
	/// </summary>
	/// <param name="nsinAmp">Amplitude of sine wave</param>
	/// <param name="nsinFreq">Frequency of sine wave</param>
	void Rectangle(double nrectAmp, double nrectFreq);

	/// <summary>
	/// Enabling noise signal
	/// </summary>
	/// <param name="nnoiseVar">noise variation</param>
	void Noise(double nnoiseVar);
	
private:
	//int type;	///< type of generated signal
	//double par1; ///< value of first parameter
	//double par2;  ///< value of seond parameter
	int step;  ///< value of current program iteration
	double output; ///< value of output to be returned
	int sign; ///< sign paramtere for rectangle signal
	int kronecker; ///< parameter for enabling kronecker signal
	double sinAmp; ///< Amplitude of sine wave
	double sinFreq; ///< Frequency of sine wave
	double rectAmp; ///< Amplitude of rectangle wave
	double rectFreq;///< Frequency of rectangle wave
	double noiseVar; ///< variation of noise
};
