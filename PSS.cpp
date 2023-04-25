// PSS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//to avoid warnings with strtok 
//TODO change later to strtok_s
#define _CRT_SECURE_NO_WARNINGS


#include "Siso.h"
#include "Arx.h"
#include "Regulator.h"

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include<string>
#include <cstring>
using namespace std;

const int INPUT_PARAMS_LINE_LENGTH = 30;

int main()
{
	srand(time(NULL));

	int degA = 2, degB = 2, degk = 0;
	double x, y;
 

	//cout << "Set nA, nB and k parameters" << endl;
	//cin >> nA, nB, k;

	double A[2] = { 1, 5 }, B[2] = { 7, 3 };

	//cout << "Set A and B" << endl;
	//cin >> A, B;

	Arx modelArx(degA, degB, degk);

	modelArx.setParameters(A, B);

	double output = 0;
	int simTime = 0;
	int stopTime = 20;
	//while (simTime<stopTime)
	//while(1)
	//{
	//	//x = rand() % 5;
	//	x = 3;
	//	output = modelArx.simulate(x);
	//	cout << output;
	//	cout << endl;
	//	simTime++;
	//}
	ifstream input_file("data\\input_parameters.txt");
	//input_file.open;
	string parameters_file_line;
	int lineno = 0;
	//getting params from txt file line by line until, each line is a new model
	//params sets are separated by semicolon, and each parameter is separated by whitespace
	//e.g 
	//a1 a2 a3 ...;b0 b1 b2 b3 ...	    //[model no.1]
	//a1 a2 a3...;b0 b1 b2 b3...		//[model no.2]
	//... etc.
	while(getline(input_file, parameters_file_line)) 
	{
		lineno++;  //counting lines to choose model
		char* line_array = new char[parameters_file_line.length() + 1];
		strcpy(line_array, parameters_file_line.c_str());
		//cout << parameters_file_line<<endl;

		//obtaining parameters sets (Arx: A and B) from line by semicolon separator
		char* p = strtok(line_array, ";");
		while (p != NULL)
		{
			cout <<"sizeof line "<< sizeof( p) << endl;
			
			//obtaining each parameter
			char* parameter_from_line = strtok(p, " ");
			cout << "parametry z jednej lini" << endl;
			while (parameter_from_line != NULL)
			{
				//string final_parameter(parameter_from_line);
				cout << stod(parameter_from_line) << endl;
				parameter_from_line = strtok(NULL, " ");
			}

			p = strtok(NULL, ";");
		}
		delete[] line_array;
	}

	input_file.close();



	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
