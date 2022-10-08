// toyRobot.cpp : Defines the entry point for the console application.
//
#include "robot.h"
#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Translator.h"

using namespace std;

//we could custimise the size of the table top here. 5 x 5 by default.
const int boundary_x = 5, boundary_y = 5;

int main()
{
	try
	{
		//to define a 5 units x 5 units square table top
		TableTop tabletop(boundary_x, boundary_y);
		//create a robot toy
		Robot robot = Robot(tabletop);
		Translator translator;

		vector<string> vec_temp;
		while (true)
		{
			string inputLine;
			string sub_string;
			string parsedLine;
			int index = -1;
			vec_temp.clear();
			getline(cin, inputLine);
			parsedLine = translator.parse(inputLine, vec_temp);

			string outputLine = "";
			//robot process each command
			int result = robot.processCmd(parsedLine, vec_temp, outputLine);
			if (1 == result)
			{
				if (outputLine.size() > 0)//print only if there is a non empty string
					cout << outputLine << endl;
			}
			else if (-1 == result)
			{
				break; //stop the app
			}
			else if (0 == result)
			{
				continue; //normal status including right inputs and wrong inputs
			}
		}

		return 0;
	}
	catch (invalid_argument& e)
	{
		cerr << e.what() << endl;
		return 1;
	}
	catch (...)
	{
		cerr << "exception occurred!" << endl;
		return 1;
	}
}

