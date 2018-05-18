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

int Operation::getID()
{
	return this->id;
}

int Operation::getTime()
{
	return this->time;
}

string Operation::getType()
{
	return this->type;
}

string Operation::getInformation()
{
	return "Operation " + to_string(this->id) + ": " + this->type + " Time: " + to_string(this->time);
}
