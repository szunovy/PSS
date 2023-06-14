#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Exceptions.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <string>
#include <cstring>
#include <chrono>
#include <format>
#include <tuple>


using namespace std;

class Manager{

public:
	/// <summary>
	/// Constructor. Creates file for saving results. Default path is \results\'current date and time.txt'.
	/// </summary>
	Manager();

	/// <summary>
	/// Reads chosen parameters of ARX object from file.
	/// 
	///Obtains chosen three groups of parameters separated with semicolon (A;B;nk)
	///User specifies number of desired model, each model is placed in a new line. 
	///Params sets are separated by semicolon, and each parameter is separated by whitespace.
	//e.g 
	//a1 a2 a3 ...;b0 b1 b2 b3 ...;nk	    //[model no.1]
	//a1 a2 a3...;b0 b1 b2 b3...;nk     	//[model no.2]
	//... etc.
	/// </summary>
	/// <param name="modelNumber">Number of chosen model from file</param>
	/// <returns>1 if everything worked correctly, 0 if some error occured</returns>
	int ReadParametersFile(int modelNumber);
	//void ReadParametersFile(int modelNumber, string path);

	/// <summary>
	/// Returns tuple of degrees of ARX parameters in given form (degA, degB, degk).
	/// </summary>
	/// <returns>tuple of degrees of parameters (degA, degB, degk)</returns>
	/// 
	tuple<int, int, int> getDegrees();
	/// <summary>
	/// Returns vector of parameters A
	/// </summary>
	/// <returns>vector of parameters A</returns>
	vector<double> getA();
	/// <summary>
	/// Returns vector of parameters B
	/// </summary>
	/// <returns>vector of parameters B</returns>
	/// 
	vector<double> getB();
	/// <summary>
	/// Saves text message to results file. Default path is \results\'current date and time.txt'.
	/// </summary>
	/// <param name="message">Text to be saved to file</param>
	/// 
	void SaveToFile(string message);
	/// <summary>
	/// Saves value to results file. Default path is \results\'current date and time.txt'.
	/// </summary>
	/// <param name="value">Value to be saved to file</param>
	void SaveToFile(double value);
private:
	vector< double > paramsA; ///< vector for holding parameters of polynomial A
	vector< double > paramsB; ///< vector for holding parameters of polynomial A
	int degreeA; ///< degree of polynomial A
	int degreeB; ///< degree of polynomial B
	int degreek; ///< deegree of delay
	char fileName[80]; ///< file name
	ofstream outputFile; ///< output stream object for saving to file
};

