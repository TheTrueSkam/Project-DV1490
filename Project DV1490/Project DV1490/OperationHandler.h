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
	Operation **operationRooms;
	int rooms;
	int *timeLeft;
	int shortTime;
	int nrOffPosibleOperations;
	void expand();
public:
	OperationHandler(int rooms = 0, int time = 0, bool sametime = true);
	~OperationHandler();
	// OperationHandler(const OperationHandler& other);
	void readOperations(string filename);
	void schedule(); // H�r sker sj�lva "algoritmen"
	void printOperations();
	void swap(Operation &one, Operation &two);
};
#endif // !OPERATIONHANDLER_H
