// PSS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//to avoid warnings with strtok 
//TODO change later to strtok_s
#define _CRT_SECURE_NO_WARNINGS

#include "Siso.h"
#include "Arx.h"
#include "Regulator.h"
#include "Generator.h"
#include "controllerPID.h"
#include "Exceptions.h"
#include "Manager.h"


#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
#include <cstring>
#include <chrono>
#include <format>
#include <tuple>

using namespace std;

const int INPUT_PARAMS_MAX_LENGTH = 30;
const int OBJECT_OUTPUT_LIMIT = 1000000;




int main()
{
	srand(time(NULL));

	int degA, degB, degk;
	double x, y;
	vector< double > A; 
	vector< double > B;

	Manager FileManager;
	if(not FileManager.ReadParametersFile(1))
	{
		return 0;
	}
	
	tie(degA, degB, degk) = FileManager.getDegrees();
	Arx modelArx(degA, degB, degk);

	modelArx.setParameters(FileManager.getA(), FileManager.getB());

	double output = 0;
	int simTime = 0;
	int stopTime = 20;

	//Generator generator("kronecker", 1 , 1);
	controllerPID controller(1, 1, 0.5);
	Generator signalgenerator;
	//signalgenerator.Sinus(2, 10);
	signalgenerator.Kronecker();
	signalgenerator.Sinus(10, 10);

	double SP = 5;
	double error = 0;

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

		error = SP - output;

		output = controller.simulate(error);

		output = signalgenerator.generate();
		cout << output << endl;
		FileManager.SaveToFile(output);
		simTime++;
		if (simTime == 20) { break; }
	}

	//freeing memory and closing files

	return 0;
}

