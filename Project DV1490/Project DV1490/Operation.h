#ifndef OPERATION_H
#define OPERATION_H

#include <iostream>
#include <string>

using namespace std;

class Operation
{
private:
	int id;
	int time;
	string type;
public:
	Operation(int id = 0, int time = 0, string type = " ");
	~Operation();
	void setID(int id);
	int getID();
	void setTime(int time);
	int getTime();
	void setType(string type);
	string getType();
	string getInformation();
};
#endif // !OPERATION_H