#include "OperationHandler.h"

int main()
{
	OperationHandler handler;

	handler.readOperations("Operationer_1a.txt");
	handler.schedule(660, 3);

	getchar();
	return 0;
}