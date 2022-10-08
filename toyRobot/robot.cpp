#include "robot.h"
#include <string>
#include <vector>

using namespace std;

Robot::Robot(const TableTop& tableTop)
	:m_tableTop(tableTop)
	,m_coordinates()
	,m_iHeading(NORTH)
	,m_bActivated(false)
{
	m_vDirection = {"NORTH","EAST","SOUTH","WEST"};
}

void Robot::setCoordinates(int x, int y)
{
	m_coordinates.pos_x = x;
	m_coordinates.pos_y = y;
}

void Robot::setHeading(int heading)
{
	//only when the heading is in the 
	if(heading >= NORTH && heading <= WEST)
		m_iHeading = heading;
}

const Coordinates Robot::getCurCoordinates() const
{
	return m_coordinates;
}

const int Robot::getCurHeading() const
{
	return m_iHeading;
}

const bool Robot::isRobotReady() const
{
	return m_bActivated;
}

void Robot::place(int x, int y, int heading)
{
	//place the robot on the table top, otherwise ignore it.
	if (isOnTableTop(x, y))
	{
		setCoordinates(x, y);
		setHeading(heading);

		//if the robot has not been placed on the top yet, then activate it and prepare for 
		//the next command.
		if (!m_bActivated)
			m_bActivated = true;
	}
}

//just move one step in the direction of heading
void Robot::move()
{
	if (!m_bActivated)//if the robot has not been placed on the table top yet, ignore it.
		return;

	//initialized by current postion
	int next_x = m_coordinates.pos_x;
	int next_y = m_coordinates.pos_y;

	processForMovement(next_x, next_y);

	//only if the robot is still on the table top, it will move a step.
	if (isOnTableTop(next_x, next_y))
	{
		setCoordinates(next_x, next_y);
	}

	//notice that move does not change the direction, so do not use setHeading().
}

//process for move based on the rules
void Robot::processForMovement(int &x, int &y)
{
	switch (m_iHeading)
	{
	case NORTH:
		y += 1;
		break;
	case EAST:
		x += 1;
		break;
	case SOUTH:
		y -= 1;
		break;
	case WEST:
		x -= 1;
		break;
	}
}

void Robot::rotate(int rotation)
{
	if (!m_bActivated)//if the robot has not been placed on the table top yet, ignore it.
		return;

	if (LEFT == rotation)
	{
		m_iHeading -= 1; //anti clockwise rotation: N->W->S->E->N (0->3->2->1->0)
		if (m_iHeading < 0)
			m_iHeading = WEST;
	}
	else if (RIGHT == rotation)
	{
		m_iHeading += 1; //clockwise rotation: N->E->S->W->N (0->1->2->3->0)
		if (m_iHeading > 3)
			m_iHeading = NORTH;
	}
}

string Robot::report()
{
	if (!m_bActivated)//if the robot has not been placed on the table top yet, ignore it.
		return "";

	string result = "Output: ";

	string s_x = to_string(m_coordinates.pos_x);
	string s_y = to_string(m_coordinates.pos_y);
	string s_heading = m_vDirection[m_iHeading];

	result.append(s_x);
	result.append(",");
	result.append(s_y);
	result.append(",");
	result.append(s_heading);

	return result;
}

//process each input command
int Robot::processCmd(string sCommand, const std::vector<std::string>& v_placeParam, string& sOutputLine)
{
	//respond to input command
	if ("MOVE" == sCommand)
	{
		move();
		return 0;
	}
	else if ("LEFT" == sCommand)
	{
		rotate(LEFT);
		return 0;
	}
	else if ("RIGHT" == sCommand)
	{
		rotate(RIGHT);
		return 0;
	}
	else if ("REPORT" == sCommand)
	{
		sOutputLine = report();
		return 1;
	}
	else if ("PLACE" == sCommand)
	{
		int x, y, heading = 0;
		x = stoi(v_placeParam[0]);
		y = stoi(v_placeParam[1]);
		int i_heading = getHeading(v_placeParam[2]);
		if (-1 != i_heading)//the valid heading
		{
			place(x, y, i_heading);
			return 0;
		}
		return 0;
	}
	else if ("QUIT" == sCommand)
	{
		return -1; //stop the app
	}

	return 0;
}

bool Robot::isOnTableTop(int x, int y)
{
	return ((x >= 0) && (y >= 0) && (x <= m_tableTop.boundary_x) && (y <= m_tableTop.boundary_y));
}

int Robot::getHeading(string sHeading)
{
	int result = -1;

	if ("NORTH" == sHeading)
		result = NORTH;
	else if("EAST" == sHeading)
		result = EAST;
	else if ("SOUTH" == sHeading)
		result = SOUTH;
	else if ("WEST" == sHeading)
		result = WEST;
	
	return result;
}
