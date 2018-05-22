#include "Operation.h"

Operation::Operation(int id, int time, string type)
{
	this->id = id;
	this->time = time;
	this->type = type;
}

Operation::~Operation()
{
}

void Operation::setID(int id)
{
	this->id = id;
}

int Operation::getID()
{
	return this->id;
}

void Operation::setTime(int time)
{
	this->time = time;
}

int Operation::getTime()
{
	return this->time;
}

void Operation::setType(string type)
{
	this->type = type;
}

string Operation::getType()
{
	return this->type;
}

string Operation::getInformation()
{
	return "Operation " + to_string(this->id) + ": " + this->type + " Time: " + to_string(this->time);
}




