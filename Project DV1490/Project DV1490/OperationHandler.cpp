#include "OperationHandler.h"
#include <iostream>
#include <ctime>

void OperationHandler::expand()
{
	this->nrOfPossibleOperations *= 2;
	Operation **temp = new Operation*[this->roomsOverDays];
	for (int i = 0; i < this->roomsOverDays; i++)
	{
		temp[i] = new Operation[this->nrOfPossibleOperations];
	}

	for (int i = 0; i < this->roomsOverDays; i++)
	{
		for (int j = 0; j < this->nrOfPossibleOperations; i++)
		{
			temp[i][j].setTime(this->operationRooms[i][j].getTime());
			temp[i][j].setType(this->operationRooms[i][j].getType());
			temp[i][j].setID(this->operationRooms[i][j].getID());
		}
	}
	
	for (int i = 0; i < this->roomsOverDays; i++)
	{
		delete[] operationRooms[i];
	}
	delete[] operationRooms;

	operationRooms = temp;
}

OperationHandler::OperationHandler(int rooms, int time, bool sametime, int dayAmmount)
{
	this->days = dayAmmount;
	this->rooms = rooms;
	this->roomsOverDays = dayAmmount * rooms;
	this->nrOfPossibleOperations = CAP;
	this->operationRooms = new Operation*[this->roomsOverDays];

	// Varje operationssal får 20 "operationspass" från start.

	for (int i = 0; i < this->roomsOverDays; i++)
	{
		this->operationRooms[i] = new Operation[nrOfPossibleOperations];
	}

	// Vill användaren ha samma tid på samtliga salar läggs vald tid i timeLeft-arrayens alla platser.
	if (sametime)
	{
		this->timeLeft = new int[this->roomsOverDays];
		this->totalTimeOfDay = new int[this->roomsOverDays];
		for (int i = 0; i < this->roomsOverDays; i++)
		{
			this->timeLeft[i] = time;
			this->totalTimeOfDay[i] = time;
		}
	}
	else 
	{
		// Om användaren istället önskar olika värden på varje sal gås varje rum igenom och användaren matar in önskad tid.
		int differentTime;
		this->timeLeft = new int[this->roomsOverDays];
		this->totalTimeOfDay = new int[this->roomsOverDays];
		for (int i = 0; i < this->rooms; i++)
		{
			cout << "How long time is room " << i << " open in minutes? ";
			cin >> differentTime;
			cout << endl;
			for (int j = 0 + i; j < this->roomsOverDays; j)
			{
				this->timeLeft[j] = differentTime;
				this->totalTimeOfDay[j] = differentTime;
				j = j + this->rooms;
			}
			
		}
		getchar();
	}
	
	this->shortTime = 0;
}

OperationHandler::~OperationHandler()
{
	for (int i = 0; i < this->roomsOverDays; i++)
	{
		delete[] this->operationRooms[i];
	}
	delete[] operationRooms;
	delete[] timeLeft;
	delete[] totalTimeOfDay;
}

OperationHandler::OperationHandler(const OperationHandler & other)
{
	for (int i = 0; i < this->roomsOverDays; i++)
	{
		delete[] this->operationRooms[i];
	}
	delete[] operationRooms;
	delete[] timeLeft;
	delete[] totalTimeOfDay;

	this->rooms = other.rooms;
	this->days = other.days;
	this->roomsOverDays = other.roomsOverDays;

	this->timeLeft = new int[other.roomsOverDays];
	for (int i = 0; i < other.roomsOverDays; i++)
	{
		this->timeLeft[i] = other.timeLeft[i];
	}
	this->totalTimeOfDay = new int[other.roomsOverDays];
	for (int i = 0; i < other.roomsOverDays; i++)
	{
		this->totalTimeOfDay[i] = other.totalTimeOfDay[i];
	}
	
	this->shortTime = other.shortTime;
	this->nrOfPossibleOperations = other.nrOfPossibleOperations;
	this->returnList = other.returnList;
	this->theOperations = other.theOperations;
	this->operationRooms = new Operation*[other.roomsOverDays];
	for (int i = 0; i < other.roomsOverDays; i++)
	{
		this->operationRooms[i] = new Operation[other.nrOfPossibleOperations];
	}
	for (int i = 0; i < other.roomsOverDays; i++)
	{
		for (int j = 0; j < other.nrOfPossibleOperations; j++)
		{
			this->operationRooms[i][j] = other.operationRooms[i][j];
		}
	}
}

void OperationHandler::readOperations(string filename)
{
	string line = " ";
	int shortestTime = INT_MAX;

	ifstream myFile;
	myFile.open(filename);

	// Läser igenom hela filen.
	while (!myFile.eof())
	{
		// Sparar ner linjen från filen till line.
		getline(myFile, line);

		if (!myFile.eof() && line != "")
		{
			int pos = line.find(",");
			// Delar upp strängen i två delar, en med hela originalsträngen samt en med enbart karaktärerna efter första kommatecknet.
			string newLine = line.substr(pos + 1);
			// Hittar andra kommatecknet.
			int pos2 = newLine.find(",");

			// Placerar på listans sista plats en operation med ID, tid och typ.
			this->theOperations.insertAt(theOperations.length(), Operation(stoi(line.substr(0, pos)), stoi(newLine.substr(pos2 + 1)), newLine.substr(0, pos2)));
			if (stoi(newLine.substr(pos2 + 1)) < shortestTime)
			{
				// Söker upp kortaste operationen som kommer användas som kontroll vid schemaläggning.
				shortestTime = stoi(newLine.substr(pos2 + 1));
			}
		}
	}
	myFile.close();

	this->shortTime = shortestTime;
}

void OperationHandler::schedule(int updatesPerDay)
{
	clock_t startOp;
	clock_t endOp;
	bool timeFind = false;
	int counterRooms = 0;
	int nrOffOperations = this->theOperations.length();
	int *counterDayOrder = new int[this->roomsOverDays];
	for (int i = 0; i < this->roomsOverDays; i++)
	{
		counterDayOrder[i] = 0;
	}
	Operation holder;
	
	for (int currentDay = 1; currentDay <= this->days; currentDay++)
	{
	//	for (int updates = 0; updates < updatesPerDay; updates++)
	//	{
			 /*<< "----- ROUND " << updates + 1*/ 
			cout << endl << "----- ROUND 1" << " DAY " << currentDay << " -----" << endl;
			startOp = clock();
			int stopLoop = 0;
			// Läser in operationer så länge det går på samtliga operationssalar.
			for (int i = 0; i < nrOffOperations && this->theOperations.length() != 0 && stopLoop != this->rooms; i++)
			{
				stopLoop = 0;
				for (int roomAmmount = (this->rooms * this->days) - this->rooms; roomAmmount < this->rooms * this->days; roomAmmount++)
				{
					if (this->timeLeft[roomAmmount] < this->shortTime)
					{
						stopLoop++;
					}
				}

				counterRooms = (this->rooms * currentDay) - this->rooms;
				// Skapar en operation med första elementet från listan.
				try
				{
					holder = theOperations.takeFirst();
				}
				catch (const char *e)
				{
					cout << "error: " << e << endl;
				}

				while (!timeFind)
				{
					// Om det finns tillräckligt med tid för att schemalägga operationen placeras den i lämpligt rum och på rätt plats
					// sedan ökar "ordningssiffran" i samma rum med ett. Slutligen minskas tiden som är kvar och while-loopen avbryts.
					if (this->timeLeft[counterRooms] >= holder.getTime())
					{
						if (this->nrOfPossibleOperations <= counterDayOrder[counterRooms])
						{
							expand();
						}
						else
						{
							cout << "CHANGE: Adding operation with ID " << holder.getID() << " to operationroom " << counterRooms << "." << endl;
							this->operationRooms[counterRooms][counterDayOrder[counterRooms]] = holder;
							counterDayOrder[counterRooms]++;
							this->timeLeft[counterRooms] -= holder.getTime();
							timeFind = true;
						}

					}

					// Har elementet inte fått en lämplig plats läggs det i en separat lista.
					if (!timeFind && counterRooms == (this->rooms * currentDay) - 1)
					{
						this->returnList.insertAt(0, holder);
						timeFind = true;
					}
					else
					{
						counterRooms++;
					}
				}
				// Börjar om tills dess att samtliga element placeras.
				timeFind = false;
			}
			// Flyttar tillbaka borttagna element till operationslistan.
			for (int i = this->returnList.length(); i > 0; i--)
			{
				this->theOperations.insertAt(0, this->returnList.takeFirst());
			}
			endOp = clock();
			printOperations();
			cout << endl << "Time Round 1: " << endOp - startOp << endl;
			cout << endl << "----- ROUND 2" << " DAY " << currentDay << " -----" << endl;
			startOp = clock();
			for (int currentRoom = (this->rooms * currentDay) - this->rooms; currentRoom < (this->rooms * currentDay); currentRoom++)
			{
				for (int currentOperation = 0; currentOperation < counterDayOrder[currentRoom] && this->timeLeft[currentRoom] != 0; currentOperation++)
				{
					for (int roomToSwap = (this->rooms * currentDay) - this->rooms; roomToSwap < (this->rooms * currentDay) && this->timeLeft[currentRoom] != 0; roomToSwap++)
					{
						if (roomToSwap != currentRoom)
						{
							for (int operationToSwap = 0; operationToSwap < counterDayOrder[roomToSwap] && this->timeLeft[roomToSwap] != 0 && this->timeLeft[currentRoom] != 0; operationToSwap++)
							{
								if (this->operationRooms[currentRoom][currentOperation].getTime() + this->timeLeft[currentRoom] == this->operationRooms[roomToSwap][operationToSwap].getTime())
								{
									this->timeLeft[currentRoom] = this->timeLeft[currentRoom] + this->operationRooms[currentRoom][currentOperation].getTime() - this->operationRooms[roomToSwap][operationToSwap].getTime();
									this->timeLeft[roomToSwap] = this->timeLeft[roomToSwap] - this->operationRooms[currentRoom][currentOperation].getTime() + this->operationRooms[roomToSwap][operationToSwap].getTime();
									cout << "CHANGE: Swapping operation with ID " << this->operationRooms[currentRoom][currentOperation].getID() << " with operation " << this->operationRooms[roomToSwap][operationToSwap].getID() << "." << endl;
									swap(this->operationRooms[currentRoom][currentOperation], this->operationRooms[roomToSwap][operationToSwap]);
								}
							}
						}
					}
				}
			}
			endOp = clock();
			printOperations();
			cout << endl << "Time Round 2: " << endOp - startOp << endl;
			cout << endl << "----- ROUND 3" << " DAY " << currentDay << " -----" << endl;
			// Kontrollerar om det går att byta med listan för att få optimal tid.
			startOp = clock();
			for (int currentRoom = (currentDay * this->rooms) - this->rooms; currentRoom < (this->rooms * currentDay); currentRoom++)
			{
				for (int nrOfOperationsInList = this->theOperations.length(); nrOfOperationsInList > 0 && this->timeLeft[currentRoom] != 0; nrOfOperationsInList--)
				{
					try
					{
						holder = theOperations.takeFirst();
					}
					catch (const char *e)
					{
						cout << "error: " << e << endl;
					}
					for (int currentOperation = 0; currentOperation < counterDayOrder[currentRoom] && !timeFind; currentOperation++)
					{
						if (holder.getTime() - this->timeLeft[currentRoom] == this->operationRooms[currentRoom][currentOperation].getTime())
						{
							cout << "CHANGE: Swapping operation with ID " << this->operationRooms[currentRoom][currentOperation].getID() << " with operation " << holder.getID() << "." << endl;
							this->timeLeft[currentRoom] = this->timeLeft[currentRoom] + this->operationRooms[currentRoom][currentOperation].getTime() - holder.getTime();
							this->theOperations.insertAt(0, this->operationRooms[currentRoom][currentOperation]);
							this->operationRooms[currentRoom][currentOperation] = holder;
							timeFind = true;
						}
					}
					if (timeLeft[currentRoom] >= holder.getTime() && !timeFind)
					{
						cout << "CHANGE: Adding operation with ID " << holder.getID() << " to operationroom " << counterRooms << "." << endl;
						this->timeLeft[currentRoom] -= holder.getTime();
						this->operationRooms[counterRooms][counterDayOrder[counterRooms]] = holder;
						timeFind = true;
					}
					if (!timeFind)
					{
						this->returnList.insertAt(0, holder);
					}
					timeFind = false;
				}
				// Flyttar tillbaka borttagna element till operationslistan.
				for (int i = this->returnList.length(); i > 0; i--)
				{
					this->theOperations.insertAt(0, this->returnList.takeFirst());
				}
			}
			endOp = clock();
			printOperations();
			cout << endl << "Time Round 3: " << endOp - startOp << endl;
		//}
	}

	delete[] counterDayOrder;
}

void OperationHandler::printOperations()
{
	cout << endl << "Order:" << endl;
	for (int i = 0; i < this->roomsOverDays; i++)
	{
		for (int j = 0; j < this->nrOfPossibleOperations && this->operationRooms[i][j].getTime() != 0; j++)
		{
			// Skriver ut operationernas ID i den ordning de blivit placerade.
			cout << this->operationRooms[i][j].getID() << " ";
		}
		cout << endl;
	}

	// Skriver ut tiden som är kvar för varje rum.
	cout << endl;
	cout << "Time left for each room..." << endl;
	for (int currentDay = 1; currentDay <= this->days; currentDay++)
	{
		cout << "Day: " << currentDay << endl;

		for (int i = (this->rooms * currentDay) - rooms; i < (this->rooms * currentDay); i++)
		{
			cout << "Room " << i << ": " << timeLeft[i] << endl;
			cout << "Procent of day used: " << ((float)(totalTimeOfDay[i] - timeLeft[i]) / totalTimeOfDay[i]) * 100 << "%" << endl;
		}
	}
}

void OperationHandler::swap(Operation &one, Operation &two)
{
	Operation temp = one;
	one = two;
	two = temp;
}

OperationHandler & OperationHandler::operator=(const OperationHandler & origObj)
{
	if (this != &origObj)
	{
		this->rooms = origObj.rooms;
		this->days = origObj.days;
		this->roomsOverDays = origObj.roomsOverDays;
		for (int i = 0; i < origObj.roomsOverDays; i++)
		{
			this->timeLeft[i] = origObj.timeLeft[i];
		}
		for (int i = 0; i < origObj.roomsOverDays; i++)
		{
			this->totalTimeOfDay[i] = origObj.totalTimeOfDay[i];
		}
		this->shortTime = origObj.shortTime;
		this->nrOfPossibleOperations = origObj.nrOfPossibleOperations;
		this->returnList = origObj.returnList;
		this->theOperations = origObj.theOperations;
	
		for (int i = 0; i < origObj.roomsOverDays; i++)
		{
			for (int j = 0; j < origObj.nrOfPossibleOperations; j++)
			{
				this->operationRooms[i][j] = origObj.operationRooms[i][j];
			}
		}
	}

	return *this;
}
