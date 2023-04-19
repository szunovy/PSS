// PSS.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "Siso.h"
#include "Arx.h"
#include "Regulator.h"

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
using namespace std;


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
	while (simTime<stopTime)
	//while(1)
	{
		//x = rand() % 5;
		x = 3;
		output = modelArx.simulate(x);
		cout << output;
		cout << endl;
		simTime++;
	}


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
