#include "OperationHandler.h"
#include <ctime>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	clock_t start; 
	clock_t end;

	OperationHandler handler(3,  660);
	OperationHandler handler2(3, 660);
	OperationHandler handler3(3, 660, false, 2);

	cout << "***** HANDLER 1 *****" << endl;
	handler.readOperations("Operationer_1a.txt");
	start = clock();
	handler.schedule(3);
	end = clock();

	cout << endl << "Time Handler 1: " << end - start << endl;

	cout << "***** HANDLER 2 *****" << endl;
	handler2.readOperations("Operationer_1b.txt");
	start = clock();
	handler2.schedule(3);
	end = clock();

	cout << endl << "Time Handler 2: " << end - start << endl;

	cout << "***** HANDLER 3 *****" << endl;
	handler3.readOperations("Operationer_2.txt");
	start = clock();
	handler3.schedule(3);
	end = clock();

	cout << endl << "Time Handler 3: " << end - start << endl;

	getchar();
	return 0;
}