#include "Manager.h"


Manager::Manager()
{
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(fileName, 80, "data//results//%Y.%m.%d_%H.%M.%S.txt", timeinfo);
	outputFile.open(fileName);
};


int Manager::ReadParametersFile(int modelNumber)
{
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
				degreek = stoi(line_pk);
				degreeA = 0;
				degreeB = 0;

				char* params_A_array = new char[line_pA.length() + 1];
				strcpy(params_A_array, line_pA.c_str());
				char* p = strtok(params_A_array, " ");
				while (p != NULL)
				{
					//tempA[degA] = stod(p);
					paramsA.push_back(stod(p));
					//cout << p << endl;
					p = strtok(NULL, " ");
					degreeA++;
				}
				delete[] params_A_array;

				char* params_B_array = new char[line_pB.length() + 1];
				strcpy(params_B_array, line_pB.c_str());
				p = strtok(params_B_array, " ");
				while (p != NULL)
				{
					//tempB[degB] = stod(p);  //local array
					paramsB.push_back(stod(p));
					//Bbuffer[degB] = stod(p); //array outside function
					degreeB++;
					p = strtok(NULL, " ");
				}
				break;
			}

		}
		if (degreek == 0) { throw DelayZero("Delay shouldn't be 0"); }
	}
	catch (DelayZero) {
		cout << "Delay shouldn't be 0, set by default to 1" << endl;
		degreek = 1;
	}
	catch (invalid_argument) {
		cout << "Wrong input parameters" << endl;
		return 0;
	}
	//cout << "B[1] " << B[1];
	input_file.close();
	return 1;
};


tuple<int, int, int> Manager::getDegrees()
{
	return make_tuple(degreeA, degreeB, degreek);
};

vector<double> Manager::getA()
{
	return this->paramsA;
};

vector<double> Manager::getB()
{
	return this->paramsB;
};

void Manager::SaveToFile(string message)
{
	outputFile << message << endl;
}

void Manager::SaveToFile(double value)
{
	outputFile << value << endl;
}
