#ifndef OPERATIONHANDLER_H
#define OPERATIONHANDLER_H

#define CAP 20

#include "Operation.h"
#include "List.h"
#include <fstream>

class OperationHandler
{
private:
	List<Operation> theOperations;
	List<Operation> returnList;

	// Operation *operationRooms[3]; // Första array täcker antalet salar, i vårt fall 3. Andra värdet antalet "operationspass".
	Operation **operationRooms;
	int days;
	int rooms;
	int roomsOverDays;
	int *timeLeft;
	int *totalTimeOfDay;
	int shortTime;
	int nrOfPossibleOperations;
	void expand();
public:
	OperationHandler(int rooms = 0, int time = 0, bool sametime = true, int dayAmmount = 1);
	~OperationHandler();
	OperationHandler(const OperationHandler& other);
	void readOperations(string filename);
	void schedule(int updatesPerDay); // Här sker själva "algoritmen"
	void printOperations();
	void swap(Operation &one, Operation &two);
	OperationHandler& operator=(const OperationHandler &origObj);
};
#endif // !OPERATIONHANDLER_H
