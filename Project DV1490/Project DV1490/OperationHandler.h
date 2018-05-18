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
	Operation *operationRoom1;
	Operation *operationRoom2;
	Operation *operationRoom3;

	int *timeLeft;
	int shortTime;
public:
	OperationHandler();
	~OperationHandler();
	// OperationHandler(const OperationHandler& other);
	void readOperations(string filename);
	void schedule(int timeToSchedule, int roomAmmount); // Här sker själva "algoritmen"
	void printOperations();
};
#endif // !OPERATIONHANDLER_H
