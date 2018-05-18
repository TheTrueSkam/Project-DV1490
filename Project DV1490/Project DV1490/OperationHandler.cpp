#include "OperationHandler.h"

OperationHandler::OperationHandler()
{
	this->operationRoom1 = new Operation[20];
	this->operationRoom2 = new Operation[20];
	this->operationRoom3 = new Operation[20];
	this->timeLeft = new int[3];

	this->timeLeft[0] = 660;
	this->timeLeft[1] = 660;
	this->timeLeft[2] = 660;

	this->shortTime = 0;
}

OperationHandler::~OperationHandler()
{
	delete[] operationRoom1;
	delete[] operationRoom2;
	delete[] operationRoom3;
	delete[] timeLeft;
}

void OperationHandler::readOperations(string filename)
{
	string line = " ";
	int shortestTime = INT_MAX;

	ifstream myFile;
	myFile.open(filename);

	while (!myFile.eof())
	{
		getline(myFile, line);

		if (!myFile.eof())
		{
			int pos = line.find(",");
			string newLine = line.substr(pos + 1);
			int pos2 = newLine.find(",");

			this->theOperations.insertAt(theOperations.length(), Operation(stoi(line.substr(0, pos)), stoi(newLine.substr(pos2 + 1)), newLine.substr(0, pos2)));
			if (stoi(newLine.substr(pos2 + 1)) < shortestTime)
			{
				shortestTime = stoi(newLine.substr(pos2 + 1));
			}
		}
	}
	myFile.close();

	this->shortTime = shortestTime;
}

void OperationHandler::schedule(int timeToSchedule, int roomAmmount)
{
	int *timeLeft = new int[roomAmmount];
	int counter = 0;
	for (int i = 0; i < roomAmmount; i++)
	{
		timeLeft[i] = timeToSchedule;
	}

	while (timeLeft[0] > this->shortTime && timeLeft[0] > theOperations.getAt(0).getTime())
	{
		timeLeft[0] = timeLeft[0] - theOperations.getAt(0).getTime();
		this->operationRoom1[counter] = this->theOperations.takeFirst().getID();
		counter++;
	}
	counter = 0;
	while (timeLeft[1] > this->shortTime && timeLeft[1] > theOperations.getAt(0).getTime())
	{
		timeLeft[1] = timeLeft[1] - theOperations.getAt(0).getTime();
		this->operationRoom2[counter] = this->theOperations.takeFirst().getID();
		counter++;
	}
	counter = 0;
	while (timeLeft[2] > this->shortTime && timeLeft[2] > theOperations.getAt(0).getTime())
	{
		timeLeft[2] = timeLeft[2] - theOperations.getAt(0).getTime();
		this->operationRoom3[counter] = this->theOperations.takeFirst().getID();
		counter++;
	}

	for (int i = 0; i < 10; i++)
	{
		cout << operationRoom1[i].getID() << " ";
	}
	cout << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << operationRoom2[i].getID() << " ";
	}
	cout << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << operationRoom3[i].getID() << " ";
	}
	cout << endl;
	cout << "Room 1: " << timeLeft[0] << endl;
	cout << "Room 2: " << timeLeft[1] << endl;
	cout << "Room 3: " << timeLeft[2] << endl;

	delete[] timeLeft;
}

void OperationHandler::printOperations()
{
	
}
