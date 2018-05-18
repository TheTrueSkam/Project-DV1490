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

	// Operation *operationRooms[3]; // F�rsta array t�cker antalet salar, i v�rt fall 3. Andra v�rdet antalet "operationspass".
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
	void schedule(int timeToSchedule, int roomAmmount); // H�r sker sj�lva "algoritmen"
	void printOperations();
};
#endif // !OPERATIONHANDLER_H
