// PSS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//to avoid warnings with strtok 
//TODO change later to strtok_s
#define _CRT_SECURE_NO_WARNINGS

#include "Siso.h"
#include "Arx.h"
#include "Regulator.h"
#include "Generator.h"
#include "controllerP.h"

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
#include <cstring>
#include <chrono>
#include <format>

using namespace std;

const int INPUT_PARAMS_MAX_LENGTH = 30;
const int OBJECT_OUTPUT_LIMIT = 1000000;

class UnstableObj{
	const char* name;
public:
	UnstableObj(const char* n = 0) : name(n) {}
};

class DelayZero{
	const char* name;
public:
	DelayZero(const char* n = 0) : name(n) {}
};


int main()
{
	srand(time(NULL));

	int degA, degB, degk;
	double x, y;
	vector< double > A; 
	vector< double > B;

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
	try {
		while (getline(input_file, line_pA, ';') && std::getline(input_file, line_pB, ';') && std::getline(input_file, line_pk, '\n'))
		{
			int chosen_model_number = 1;  //number of chosen model (meaning the line in txt file)
			lineno++;  //counting lines to choose model


			//data obtained from desired model
			if (lineno == chosen_model_number)
			{
				degk = stoi(line_pk);
				degA = 0;
				degB = 0;

				char* params_A_array = new char[line_pA.length() + 1];
				strcpy(params_A_array, line_pA.c_str());
				char* p = strtok(params_A_array, " ");
				while (p != NULL)
				{
					//tempA[degA] = stod(p);
					A.push_back(stod(p));
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
					//tempB[degB] = stod(p);  //local array
					B.push_back(stod(p));
					//Bbuffer[degB] = stod(p); //array outside function
					degB++;
					p = strtok(NULL, " ");
				}
				break;
			}

		}
		if (degk == 0) { throw DelayZero("Delay shouldn't be 0"); }
	}
	catch(DelayZero) {
		cout << "Delay shouldn't be 0, set by default to 1" << endl;
		degk = 1;
	}
	catch(invalid_argument) {
		cout << "Wrong input parameters" << endl;
		return 0;
	}
	//cout << "B[1] " << B[1];
	input_file.close();

	Arx modelArx(degA, degB, degk);

	modelArx.setParameters(A, B);

	double output = 0;
	int simTime = 0;
	int stopTime = 20;

	//creating file for saving results

	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, 80, "data//results//%Y.%m.%d_%H.%M.%S.txt", timeinfo);
	//cout<<buffer<<endl;
	//cout << strftime("%Y-%m-%dT%H-%M-%S.txt", timeinfo) << endl;

	ofstream output_file(buffer);

	Generator generator("noise", 1 , 1);

	while (1)
	//while(1)
	{
		////x = rand() % 5;
		//x = 3;
		//try 
		//{
		//	output = modelArx.simulate(x);
		//	if (abs(output) > OBJECT_OUTPUT_LIMIT) { throw UnstableObj("Object unstable, output values exceeded limit."); }
		//}
		//catch(UnstableObj)
		//{
		//	//printing message and stopping the simulation
		//	cout << "Object unstable, output values exceeded limit." << endl;
		//	output_file << "Object unstable, output values exceeded limit." << endl;
		//	break;
		//}
		//output_file << output << endl;

		////cout << output;
		////cout << endl;


		cout << generator.generate() << endl;
		simTime++;
	}

	//freeing memory and closing files
	output_file.close();
	return 0;
}

