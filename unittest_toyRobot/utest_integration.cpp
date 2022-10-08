/*
* @brief     the implementation of the integration tests
* @author    David Wang
* @date      07 Oct 2022
*/

#include "gtest/gtest.h"
#include "robot.h"
#include "Translator.h"
#include <string>
#include <vector>

using namespace std;

TEST(testWholeProcess, TestIntegration1)
{
	TableTop tabletop(5, 5);
	//create a robot toy
	Robot robot = Robot(tabletop);

	Translator translator;
	vector<string> vec_temp;
	string parsedLine;
	int index = -1;
	vec_temp.clear();

	vector<string> inputLine;
	inputLine.push_back("PLACE 0,0,NORTH");
	inputLine.push_back("MOVE");
	inputLine.push_back("REPORT");

	string outputLine = "";
	for (const auto& item : inputLine)
	{
		parsedLine = translator.parse(item, vec_temp);

		//robot process each command
		int result = robot.processCmd(parsedLine, vec_temp, outputLine);
	}

	string sExpect = "Output: 0,1,NORTH";
	EXPECT_TRUE(sExpect == outputLine);
}

TEST(testWholeProcess, TestIntegration2)
{
	TableTop tabletop(5, 5);
	//create a robot toy
	Robot robot = Robot(tabletop);

	Translator translator;
	vector<string> vec_temp;
	string parsedLine;
	int index = -1;
	vec_temp.clear();

	vector<string> inputLine;
	inputLine.push_back("PLACE 0,0,NORTH");
	inputLine.push_back("LEFT");
	inputLine.push_back("REPORT");

	string outputLine = "";
	for (const auto& item : inputLine)
	{
		parsedLine = translator.parse(item, vec_temp);

		//robot process each command
		int result = robot.processCmd(parsedLine, vec_temp, outputLine);
	}

	string sExpect = "Output: 0,0,WEST";
	EXPECT_TRUE(sExpect == outputLine);
}

TEST(testWholeProcess, TestIntegration3)
{
	TableTop tabletop(5, 5);
	//create a robot toy
	Robot robot = Robot(tabletop);

	Translator translator;
	vector<string> vec_temp;
	string parsedLine;
	int index = -1;
	vec_temp.clear();

	vector<string> inputLine;
	inputLine.push_back("PLACE 1,2,EAST");
	inputLine.push_back("MOVE");
	inputLine.push_back("MOVE");
	inputLine.push_back("LEFT");
	inputLine.push_back("MOVE");
	inputLine.push_back("REPORT");

	string outputLine = "";
	for (const auto& item : inputLine)
	{
		parsedLine = translator.parse(item, vec_temp);

		//robot process each command
		int result = robot.processCmd(parsedLine, vec_temp, outputLine);
	}

	string sExpect = "Output: 3,3,NORTH";
	EXPECT_TRUE(sExpect == outputLine);
}

TEST(testWholeProcess, TestIntegration4)
{
	TableTop tabletop(5, 5);
	//create a robot toy
	Robot robot = Robot(tabletop);

	Translator translator;
	vector<string> vec_temp;
	string parsedLine;
	int index = -1;
	vec_temp.clear();

	vector<string> inputLine;
	inputLine.push_back("MOVE");
	inputLine.push_back("LEFT");
	inputLine.push_back("PLACE 5,6,WEST");
	inputLine.push_back("MOVE");
	inputLine.push_back("MOVE");
	inputLine.push_back("PLACE 1,2,EAST");
	inputLine.push_back("MOVE");
	inputLine.push_back("MOVE");
	inputLine.push_back("LEFT");
	inputLine.push_back("MOVE");
	inputLine.push_back("REPORT");

	string outputLine = "";
	for (const auto& item : inputLine)
	{
		parsedLine = translator.parse(item, vec_temp);

		//robot process each command
		int result = robot.processCmd(parsedLine, vec_temp, outputLine);
	}

	string sExpect = "Output: 3,3,NORTH";
	EXPECT_TRUE(sExpect == outputLine);
}

	