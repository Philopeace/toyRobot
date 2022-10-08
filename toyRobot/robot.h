#pragma once

/*
* @brief     the implementation of the robot Class
* @author    David Wang
* @date      06 Oct 2022
*/

#include <string>
#include <vector>

enum Direction
{
	NORTH,
	EAST,    
	SOUTH,   
	WEST,  
};

enum Rotation
{
	LEFT,
	RIGHT,
};

//Table: to define a square table top
class TableTop
{
public:
	TableTop(int x, int y) : boundary_x(x), boundary_y(y) {}
	int boundary_x;
	int boundary_y;
};

//Coordinates: to define a coordinates represent the position
class Coordinates
{
public:
	Coordinates() : pos_x(-1), pos_y(-1) {} // init to (-1,-1)
	int pos_x;	
	int pos_y;	
};

//Robot: to define a robot that could have some movements
class Robot
{
public:

	Robot(const TableTop& tableTop);
	~Robot(){};

	//set position and heading functions
	void setCoordinates(int x, int y);
	void setHeading(int heading);

	//logic functions
	bool isOnTableTop(int x, int y);
	void processForMovement(int &x, int &y);

	//robot command response functions
	void place(int x, int y, int heading);
	void move();
	void rotate(int rotation);
	std::string report();
	int processCmd(std::string sCommand, const std::vector<std::string> & v_placeParam, std::string& sOutputLine);//return value: -1, quit the app; 0, normal; 1, cout message;

	//get heading from string
	int getHeading(std::string sHeading);

	//for unit tests
	//get current coordinates and heading
	const Coordinates getCurCoordinates() const;
	const int getCurHeading() const;
	const bool isRobotReady() const;

private:
	TableTop m_tableTop;
	Coordinates m_coordinates;
	int m_iHeading;
	bool m_bActivated;//represent if the robot is on the table top already.
	std::vector<std::string> m_vDirection;
};

