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
#include <chrono>

using namespace std;

const int INPUT_PARAMS_MAX_LENGTH = 30;

int main()
{
	srand(time(NULL));

	int degA, degB, degk;
	double x, y;
	double* Abuffer = new double[INPUT_PARAMS_MAX_LENGTH];
	double* Bbuffer = new double[INPUT_PARAMS_MAX_LENGTH];

	//cout << "Set nA, nB and k parameters" << endl;
	//cin >> nA, nB, k;
	//double A[2] = { 1, 5 }, B[2] = { 7, 3 };
	//cout << "Set A and B" << endl;
	//cin >> A, B;

	//creating object that obtains data from file
	ifstream input_file("data\\input_parameters.txt");

	//strings for parameters sets
	string line_pA;
	string line_pB;
	string line_pk;
	int lineno = 0; //variable indicating number of current loaded line


	
	//obtaining three groups of parameters separated with semicolon (A;B;nk)
	//getting params from txt file line by line until getting desired model number, each line is a new model
	//params sets are separated by semicolon, and each parameter is separated by whitespace
	//e.g 
	//a1 a2 a3 ...;b0 b1 b2 b3 ...;nk	    //[model no.1]
	//a1 a2 a3...;b0 b1 b2 b3...;nk     	//[model no.2]
	//... etc.
	while(getline(input_file, line_pA, ';') && std::getline(input_file, line_pB, ';') && std::getline(input_file, line_pk, ';'))
	{
		int chosen_model_number = 1;  //number of chosen model (meaning the line in txt file)
		lineno++;  //counting lines to choose model


		//data obtained from desired model
		if (lineno == chosen_model_number)
		{
			degk = stoi(line_pk);
			degA = 0;
			degB = 0;
			double* tempA = new double[line_pA.length()];
			double* tempB = new double[line_pB.length()];

			char* params_A_array = new char[line_pA.length() + 1];
			strcpy(params_A_array, line_pA.c_str());
			char* p = strtok(params_A_array, " ");
			while (p != NULL)
			{
				tempA[degA] = stod(p);
				//cout << p << endl;
				p = strtok(NULL, " ");
				degA++;
			}
			delete[] params_A_array;

			char* params_B_array = new char[line_pB.length() + 1];
			strcpy(params_B_array, line_pB.c_str());
			p = strtok(params_B_array, " ");
			while (p != NULL)
			{
				tempB[degB] = stod(p);  //local array
				//Bbuffer[degB] = stod(p); //array outside function
				degB++;
				p = strtok(NULL, " ");
			}

			//double* A = new double[degA];
			//double* B = new double[degB];
			copy(tempA, tempA + degA, Abuffer);
			copy(tempB, tempB + degB, Bbuffer);


			delete[] params_B_array;
			delete[] tempA;
			delete[] tempB;
			break;
		}
		//	//cout << "set_no " << param_set_number << endl;
		//	cout << p << endl;
		//	if(param_set_number == 1) 
		//	{
		//		cout << "paramA" <<endl;
		//	}
		//	if(param_set_number == 2)
		//	{
		//		cout << "paramB" << endl;
		//	}
		//	//cout <<"sizeof line "<< sizeof( p) << endl;
		//	
		//	//obtaining each parameter
		//	//char* parameter_from_line = strtok(p, " ");
		//	//while (parameter_from_line != NULL)
		//	//{
		//	//	//string final_parameter(parameter_from_line);
		//	//	cout << stod(parameter_from_line) << endl;
		//	//	parameter_from_line = strtok(NULL, " ");
		//	//}
		//	param_set_number+=1;
		//	//cout << "set2no " << param_set_number << endl;
		//}
		//delete[] line_array;
	}
	//cout << "B[1] " << B[1];
	input_file.close();

	double* A = new double[degA];
	double* B = new double[degB];
	copy(Abuffer, Abuffer + degA, A);
	copy(Bbuffer, Bbuffer + degB, B);

	Arx modelArx(degA, degB, degk);

	modelArx.setParameters(A, B);

	double output = 0;
	int simTime = 0;
	int stopTime = 20;

	//creating file for saving results
	ofstream output_file("data\\result.txt");

	while (simTime<stopTime)
	//while(1)
	{
		//x = rand() % 5;
		x = 3;
		output = modelArx.simulate(x);
		cout << output << endl;
		output_file << x << ";" << output << endl;

		//cout << output;
		//cout << endl;
		simTime++;
	}

	//freeing memory and closing files
	delete[] Abuffer;
	delete[] Bbuffer;
	delete[] A;
	delete[] B;
	output_file.close();
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
