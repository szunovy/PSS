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
const int OBJECT_OUTPUT_LIMIT = 100000000;




int main()
{
	srand(time(NULL));

	int degA, degB, degk; //degrees of polynomials and delay
	double x, y;
	vector< double > A;  //polynomial parameters
	vector< double > B; //polynomial parameters
	double output = 0;  //output of the ARX model
	int simTime = 0;	//incremented simulation time (Steps)
	int stopTime = 20; //stop time of simulation, amount of steps/ set to -1 to drive infinitely 
	double SP = 5;	//setpoint
	double error = 0; //error in the loop
	double input = 0; //input to the ARX object, (output of the regulator when present)

	Manager FileManager;	//initializing filemanager
	if(not FileManager.ReadParametersFile(1)) //assuring that parameters reading goes without error
	{
		return 0;
	}
	
	tie(degA, degB, degk) = FileManager.getDegrees(); //obtaining and unpacking tuple of degrees
	Arx modelArx(degA, degB, degk); //initializing ARX model object
	modelArx.setParameters(FileManager.getA(), FileManager.getB()); //setting arx polynomials

	controllerPID controller(1, 1, 0.5);
	Generator signalgenerator;

	signalgenerator.Kronecker(); //enabling kronecker signal
	signalgenerator.Sinus(10, 10);



	while (1)
	{
		try 
		{
			//put the simulation of the control system here

			error = SP - output;
			input = controller.simulate(error);
			output = modelArx.simulate(input);



			if (abs(output) > OBJECT_OUTPUT_LIMIT) { throw UnstableObj("Object unstable, output values exceeded limit.");}

			cout << output << endl;
			FileManager.SaveToFile(output);

		}
		catch(UnstableObj)
		{
			//printing message and stopping the simulation, its possible to print message to txt file calling Menager.SaveToFile()
			cout << "Object unstable, output values exceeded limit." << endl; 
			break;
		}

		simTime++;
		if (simTime == 20) { break; }
	}

	//freeing memory and closing files

	return 0;
}

