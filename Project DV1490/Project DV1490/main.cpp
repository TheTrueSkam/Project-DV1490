#include "OperationHandler.h"
#include <ctime>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	clock_t start; 
	clock_t end;

	OperationHandler handler(3,  660);
	OperationHandler handler2(3, 660);

	handler.readOperations("Operationer_1a.txt");
	handler.schedule();

	handler2.readOperations("Operationer_1b.txt");
	start = clock();
	handler2.schedule();
	end = clock();

	cout << "Time: " << end - start << endl;

	getchar();
	return 0;
}