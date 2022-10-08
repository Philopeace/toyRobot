/*
* @brief     the implementation of the unit test for robot
* @author    David Wang
* @date      07 Oct 2022
*/

#include "gtest/gtest.h"
#include "robot.h"
#include "Translator.h"
#include <string>

using namespace std;

TEST(testRobot, TestSetCoordinatesFunction)
{
	TableTop tabletop(5, 5);
	//create a robot toy
	Robot robot = Robot(tabletop);

	//initial position is (-1,-1)
	Coordinates curPos = robot.getCurCoordinates();
	EXPECT_EQ(-1, curPos.pos_x);
	EXPECT_EQ(-1, curPos.pos_y);

	//set position (4,4)
	robot.setCoordinates(4, 4);
	curPos = robot.getCurCoordinates();
	EXPECT_EQ(4, curPos.pos_x);
	EXPECT_EQ(4, curPos.pos_y);

	//set position (6,6) out of (5,5)
	//this function should not have the boundary restriction.
	robot.setCoordinates(6, 6);
	curPos = robot.getCurCoordinates();
	EXPECT_EQ(6, curPos.pos_x);
	EXPECT_EQ(6, curPos.pos_y);
}

TEST(testRobot, TestSetHeadingFunction)
{
	TableTop tabletop(5, 5);
	//create a robot toy
	Robot robot = Robot(tabletop);

	//initial heading is NORTH
	int heading = robot.getCurHeading();
	EXPECT_EQ(NORTH, heading);

	//set a correct value
	robot.setHeading(WEST);
	heading = robot.getCurHeading();
	EXPECT_EQ(WEST, heading);

	//set an incorrect value, ignore it
	robot.setHeading(800);
	heading = robot.getCurHeading();
	EXPECT_EQ(WEST, heading);

	//set a correct value again
	robot.setHeading(EAST);
	heading = robot.getCurHeading();
	EXPECT_EQ(EAST, heading);
}

TEST(testRobot, TestPlaceFunction)
{
	TableTop tabletop(5, 5);
	//create a robot toy
	Robot robot = Robot(tabletop);

	//initial position is (-1,-1), initial heading is NORTH
	Coordinates curPos = robot.getCurCoordinates();
	EXPECT_EQ(-1, curPos.pos_x);
	EXPECT_EQ(-1, curPos.pos_y);
	int heading = robot.getCurHeading();
	EXPECT_EQ(NORTH, heading);
	//initial activated flag is false
	bool bActivated = robot.isRobotReady();
	EXPECT_FALSE(bActivated);

	//place the robot out side of the table, ignore it
	robot.place(-2, -1, NORTH);
	curPos = robot.getCurCoordinates();
	EXPECT_EQ(-1, curPos.pos_x);
	EXPECT_EQ(-1, curPos.pos_y);
	heading = robot.getCurHeading();
	EXPECT_EQ(NORTH, heading);
	bActivated = robot.isRobotReady();
	EXPECT_FALSE(bActivated);

	//place the robot on the table top, the robot is activated
	robot.place(0, 0, NORTH);
	curPos = robot.getCurCoordinates();
	EXPECT_EQ(0, curPos.pos_x);
	EXPECT_EQ(0, curPos.pos_y);
	heading = robot.getCurHeading();
	EXPECT_EQ(NORTH, heading);
	bActivated = robot.isRobotReady();
	EXPECT_TRUE(bActivated);

	//place the robot on the table top 
	robot.place(4, 3, EAST);
	curPos = robot.getCurCoordinates();
	EXPECT_EQ(4, curPos.pos_x);
	EXPECT_EQ(3, curPos.pos_y);
	heading = robot.getCurHeading();
	EXPECT_EQ(EAST, heading);
	bActivated = robot.isRobotReady();
	EXPECT_TRUE(bActivated);

	//place the robot out side of the table again, ignore it
	robot.place(6, 7, SOUTH);
	curPos = robot.getCurCoordinates();
	EXPECT_EQ(4, curPos.pos_x);
	EXPECT_EQ(3, curPos.pos_y);
	heading = robot.getCurHeading();
	EXPECT_EQ(EAST, heading);
	bActivated = robot.isRobotReady();
	EXPECT_TRUE(bActivated);

	//place the robot on the table top again
	robot.place(2, 2, WEST);
	curPos = robot.getCurCoordinates();
	EXPECT_EQ(2, curPos.pos_x);
	EXPECT_EQ(2, curPos.pos_y);
	heading = robot.getCurHeading();
	EXPECT_EQ(WEST, heading);
	bActivated = robot.isRobotReady();
	EXPECT_TRUE(bActivated);

}

TEST(testRobot, TestRotateFunction)
{
	TableTop tabletop(5, 5);
	//create a robot toy
	Robot robot = Robot(tabletop);

	//initial activated flag is false
	bool bActivated = robot.isRobotReady();
	EXPECT_FALSE(bActivated);
	//initial heading is NORTH
	int heading = robot.getCurHeading();
	EXPECT_EQ(NORTH, heading);

	//turn left, ignore it
	robot.rotate(LEFT);
	heading = robot.getCurHeading();
	EXPECT_EQ(NORTH, heading);
	bActivated = robot.isRobotReady();
	EXPECT_FALSE(bActivated);

	//place the robot on the table top, the robot is activated
	robot.place(1, 1, EAST);
	heading = robot.getCurHeading();
	EXPECT_EQ(EAST, heading);
	bActivated = robot.isRobotReady();
	EXPECT_TRUE(bActivated);
	//turn left
	robot.rotate(LEFT);
	heading = robot.getCurHeading();
	EXPECT_EQ(NORTH, heading);
	robot.rotate(LEFT);
	heading = robot.getCurHeading();
	EXPECT_EQ(WEST, heading);
	bActivated = robot.isRobotReady();
	EXPECT_TRUE(bActivated);

	//rotate the incorrect value, ignore it.
	robot.rotate(300);
	heading = robot.getCurHeading();
	EXPECT_EQ(WEST, heading);
	bActivated = robot.isRobotReady();
	EXPECT_TRUE(bActivated);

	//place to another place, then trun right
	robot.place(4, 1, EAST);
	heading = robot.getCurHeading();
	EXPECT_EQ(EAST, heading);
	bActivated = robot.isRobotReady();
	EXPECT_TRUE(bActivated);
	robot.rotate(RIGHT);
	heading = robot.getCurHeading();
	EXPECT_EQ(SOUTH, heading);
	robot.rotate(RIGHT);
	heading = robot.getCurHeading();
	EXPECT_EQ(WEST, heading);
	bActivated = robot.isRobotReady();
	EXPECT_TRUE(bActivated);
}

TEST(testRobot, TestMoveFunction)
{
	TableTop tabletop(5, 5);
	//create a robot toy
	Robot robot = Robot(tabletop);

	//initial position is (-1,-1), initial heading is NORTH
	Coordinates curPos = robot.getCurCoordinates();
	EXPECT_EQ(-1, curPos.pos_x);
	EXPECT_EQ(-1, curPos.pos_y);
	int heading = robot.getCurHeading();
	EXPECT_EQ(NORTH, heading);
	//initial activated flag is false
	bool bActivated = robot.isRobotReady();
	EXPECT_FALSE(bActivated);

	//Move, ignore it
	robot.move();
	curPos = robot.getCurCoordinates();
	EXPECT_EQ(-1, curPos.pos_x);
	EXPECT_EQ(-1, curPos.pos_y);
	heading = robot.getCurHeading();
	EXPECT_EQ(NORTH, heading);
	//initial activated flag is false
	bActivated = robot.isRobotReady();
	EXPECT_FALSE(bActivated);

	//place the robot on the table top, the robot is activated
	robot.place(3, 2, SOUTH);
	curPos = robot.getCurCoordinates();
	EXPECT_EQ(3, curPos.pos_x);
	EXPECT_EQ(2, curPos.pos_y);
	heading = robot.getCurHeading();
	EXPECT_EQ(SOUTH, heading);
	bActivated = robot.isRobotReady();
	EXPECT_TRUE(bActivated);
	
	//Move
	robot.move();
	curPos = robot.getCurCoordinates();
	EXPECT_EQ(3, curPos.pos_x);
	EXPECT_EQ(1, curPos.pos_y);
	heading = robot.getCurHeading();
	EXPECT_EQ(SOUTH, heading);
	bActivated = robot.isRobotReady();
	EXPECT_TRUE(bActivated);

	//Move many times
	for (size_t i = 0; i < 10; ++i)
	{
		robot.move();
	}
	curPos = robot.getCurCoordinates();
	EXPECT_EQ(3, curPos.pos_x);
	EXPECT_EQ(0, curPos.pos_y);
	heading = robot.getCurHeading();
	EXPECT_EQ(SOUTH, heading);
	bActivated = robot.isRobotReady();
	EXPECT_TRUE(bActivated);

	//Turn Left then Move many times
	robot.rotate(LEFT);
	for (size_t i = 0; i < 10; ++i)
	{
		robot.move();
	}
	curPos = robot.getCurCoordinates();
	EXPECT_EQ(5, curPos.pos_x);
	EXPECT_EQ(0, curPos.pos_y);
	heading = robot.getCurHeading();
	EXPECT_EQ(EAST, heading);
	bActivated = robot.isRobotReady();
	EXPECT_TRUE(bActivated);
}

TEST(testRobot, TestReportFunction)
{
	TableTop tabletop(5, 5);
	//create a robot toy
	Robot robot = Robot(tabletop);

	//initial position is (-1,-1), initial heading is NORTH
	Coordinates curPos = robot.getCurCoordinates();
	EXPECT_EQ(-1, curPos.pos_x);
	EXPECT_EQ(-1, curPos.pos_y);
	int heading = robot.getCurHeading();
	EXPECT_EQ(NORTH, heading);
	string sResult = robot.report();
	string sExpect = "";
	EXPECT_TRUE(sExpect == sResult);

	//place the robot on the table top, the robot is activated
	robot.place(5, 5, WEST);
	curPos = robot.getCurCoordinates();
	EXPECT_EQ(5, curPos.pos_x);
	EXPECT_EQ(5, curPos.pos_y);
	heading = robot.getCurHeading();
	EXPECT_EQ(WEST, heading);

	sResult = robot.report();
	sExpect = "Output: ";
	sExpect.append("5,5,WEST");
	EXPECT_TRUE(sExpect == sResult);

	//place the robot out of the table top, the robot ignore it.
	robot.place(7, 7, EAST);
	sResult = robot.report();
	sExpect = "Output: ";
	sExpect.append("5,5,WEST");
	EXPECT_TRUE(sExpect == sResult);

	//place the robot on the table top again
	robot.place(5, 5, SOUTH);
	robot.move();
	sResult = robot.report();
	sExpect = "Output: ";
	sExpect.append("5,4,SOUTH");
	EXPECT_TRUE(sExpect == sResult);
	robot.rotate(RIGHT);
	sResult = robot.report();
	sExpect = "Output: ";
	sExpect.append("5,4,WEST");
}

TEST(testRobot, TestIsOnTableTopFunction)
{
	TableTop tabletop(5, 5);
	//create a robot toy
	Robot robot = Robot(tabletop);

	//initial position is (-1,-1), initial heading is NORTH
	bool bOnTable = robot.isOnTableTop(-1, -1);
	EXPECT_FALSE(bOnTable);

	//place the robot on the table top, the robot is activated
	bOnTable = robot.isOnTableTop(1, 4);
	EXPECT_TRUE(bOnTable);

	//place the robot out of the table top
	bOnTable = robot.isOnTableTop(6, 9);
	EXPECT_FALSE(bOnTable);

	TableTop tabletopNew(10, 10);
	//create a robot toy
	Robot robotNew = Robot(tabletopNew);

	bOnTable = robotNew.isOnTableTop(6, 9);
	EXPECT_TRUE(bOnTable);
}

TEST(testRobot, TestGetHeadingFunction)
{
	TableTop tabletop(5, 5);
	//create a robot toy
	Robot robot = Robot(tabletop);

	int heading = robot.getHeading("EAST");
	EXPECT_EQ(EAST, heading);

	heading = robot.getHeading("NORTH");
	EXPECT_EQ(NORTH, heading);

	//input the incorrect value, return -1
	heading = robot.getHeading("RUN");
	EXPECT_TRUE(-1 == heading);

	heading = robot.getHeading("SOUTH");
	EXPECT_EQ(SOUTH, heading);
}


