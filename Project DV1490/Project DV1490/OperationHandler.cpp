#include "OperationHandler.h"
#include <iostream>

void OperationHandler::expand()
{
	this->nrOffPosibleOperations *= 2;
	Operation **temp = new Operation*[this->rooms];
	for (int i = 0; i < this->rooms; i++)
	{
		temp[i] = new Operation[this->nrOffPosibleOperations];
	}

	for (int i = 0; i < this->rooms; i++)
	{
		for (int j = 0; j < this->nrOffPosibleOperations; i++)
		{
			temp[i][j] = this->operationRooms[i][j];
		}
	}
	
	for (int i = 0; i < rooms; i++)
	{
		delete[] operationRooms[i];
	}
	delete[] operationRooms;

	operationRooms = temp;
}

OperationHandler::OperationHandler(int rooms, int time, bool sametime)
{
	this->rooms = rooms;
	this->nrOffPosibleOperations = CAP;
	this->operationRooms = new Operation*[rooms];

	// Varje operationssal f�r 20 "operationspass" fr�n start.
	for (int i = 0; i < rooms; i++)
	{
		this->operationRooms[i] = new Operation[nrOffPosibleOperations];
	}

	// Vill anv�ndaren ha samma tid p� samtliga salar l�ggs vald tid i timeLeft-arrayens alla platser.
	if (sametime)
	{
		this->timeLeft = new int[rooms];
		for (int i = 0; i < rooms; i++)
		{
			this->timeLeft[i] = time;
		}
	}
	else 
	{
		// Om anv�ndaren ist�llet �nskar olika v�rden p� varje sal g�s varje rum igenom och anv�ndaren matar in �nskad tid.
		int diffrentTime;
		this->timeLeft = new int[rooms];
		for (int i = 0; i < rooms; i++)
		{
			cout << "How long time is room " << i << " open in minutes? ";
			cin >> diffrentTime;
			cout << endl;
			this->timeLeft[i] = diffrentTime;
		}
	}
	this->shortTime = 0;
}

OperationHandler::~OperationHandler()
{
	for (int i = 0; i < this->rooms; i++)
	{
		delete[] this->operationRooms[i];
	}
	delete[] operationRooms;
	delete[] timeLeft;
}

void OperationHandler::readOperations(string filename)
{
	string line = " ";
	int shortestTime = INT_MAX;

	ifstream myFile;
	myFile.open(filename);

	// L�ser igenom hela filen.
	while (!myFile.eof())
	{
		// Sparar ner linjen fr�n filen till line.
		getline(myFile, line);

		if (!myFile.eof())
		{
			int pos = line.find(",");
			// Delar upp str�ngen i tv� delar, en med hela originalstr�ngen samt en med enbart karakt�rerna efter f�rsta kommatecknet.
			string newLine = line.substr(pos + 1);
			// Hittar andra kommatecknet.
			int pos2 = newLine.find(",");

			// Placerar p� listans sista plats en operation med ID, tid och typ.
			this->theOperations.insertAt(theOperations.length(), Operation(stoi(line.substr(0, pos)), stoi(newLine.substr(pos2 + 1)), newLine.substr(0, pos2)));
			if (stoi(newLine.substr(pos2 + 1)) < shortestTime)
			{
				// S�ker upp kortaste operationen som kommer anv�ndas som kontroll vid schemal�ggning.
				shortestTime = stoi(newLine.substr(pos2 + 1));
			}
		}
	}
	myFile.close();

	this->shortTime = shortestTime;
}

void OperationHandler::schedule()
{
	bool timeFind = false;
	int counterRooms = 0;
	int nrOffOperations = this->theOperations.length();
	int *counterDayOrder = new int[this->rooms];
	for (int i = 0; i < this->rooms; i++)
	{
		counterDayOrder[i] = 0;
	}
	Operation holder;
	for (int appdates = 0; appdates < 3; appdates++)
	{
		for (int currentRoom = 0; currentRoom < this->rooms; currentRoom++)
		{
			for (int currentOperation = 0; currentOperation < counterDayOrder[currentRoom] && this->timeLeft[currentRoom] != 0; currentOperation++)
			{
				for (int roomToSwap = 0; roomToSwap < this->rooms && this->timeLeft[currentRoom] != 0; roomToSwap++)
				{
					if (roomToSwap != currentRoom)
					{
						for (int operationToSwap = 0; operationToSwap < counterDayOrder[roomToSwap] && this->timeLeft[currentRoom] != 0; operationToSwap++)
						{
							if (this->operationRooms[currentRoom][currentOperation].getTime() + this->timeLeft[currentRoom] == this->operationRooms[roomToSwap][operationToSwap].getTime())
							{
								swap(this->operationRooms[currentRoom][currentOperation], this->operationRooms[roomToSwap][operationToSwap]);
								this->timeLeft[currentRoom] = this->timeLeft[currentRoom] + this->operationRooms[currentRoom][currentOperation].getTime() - this->operationRooms[roomToSwap][operationToSwap].getTime();
								this->timeLeft[roomToSwap] = this->timeLeft[roomToSwap] - this->operationRooms[currentRoom][currentOperation].getTime() + this->operationRooms[roomToSwap][operationToSwap].getTime();
							}
						}
					}
				}
			}
		}
		// L�ser in operationer s� l�nge det g�r p� samtliga operationssalar.
		for (int i = 0; i < nrOffOperations; i++)
		{
			// Skapar en operation med f�rsta elementet fr�n listan.
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
				// Om det finns tillr�ckligt med tid f�r att schemal�gga operationen placeras den i l�mpligt rum och p� r�tt plats
				// sedan �kar "ordningssiffran" i samma rum med ett. Slutligen minskas tiden som �r kvar och while-loopen avbryts.
				if (this->timeLeft[counterRooms] >= holder.getTime())
				{
					this->operationRooms[counterRooms][counterDayOrder[counterRooms]] = holder;
					counterDayOrder[counterRooms]++;
					this->timeLeft[counterRooms] -= holder.getTime();
					timeFind = true;
				}
	
				// Har elementet inte f�tt en l�mplig plats l�ggs det i en separat lista.
				if (!timeFind && counterRooms == this->rooms)
				{
					this->returnList.insertAt(0, holder);
					timeFind = true;
				}
				else
				{
					counterRooms++;
				}
			}
			// B�rjar om tills dess att samtliga element placeras.
			counterRooms = 0;
			timeFind = false;
		}
		// Flyttar tillbaka borttagna element till operationslistan.
		for (int i = this->returnList.length(); i > 0; i--)
		{
			this->theOperations.insertAt(0, this->returnList.takeFirst());
		}
		//printOperations();
	
		// Kontrollerar om det g�r att byta f�r att f� optimal tid.
		for (int i = 0; i < this->rooms; i++)
		{
			if (this->timeLeft[i] != 0)
			{
				for (int j = 0; j < this->theOperations.length(); j++)
				{
					try
					{
						holder = theOperations.takeFirst();
					}
					catch (const char *e)
					{
						cout << "error: " << e << endl;
					}
					if (this->timeLeft[i] >= holder.getTime())
					{
						this->operationRooms[i][counterDayOrder[i]] = holder;
						counterDayOrder[i]++;
						this->timeLeft[i] -= holder.getTime();
					}
					else
					{
						for (int k = 0; k < counterDayOrder[i] && !timeFind; k++)
						{
							if (holder.getTime() - this->timeLeft[i] == this->operationRooms[i][k].getTime())
							{
								this->theOperations.insertAt(0, this->operationRooms[i][k]);
								this->operationRooms[i][k] = holder;
							}
							else
							{
								this->returnList.insertAt(0, holder);
							}
						}
					}
				}
			}
	
		}
		// Flyttar tillbaka borttagna element till operationslistan.
		for (int i = this->returnList.length(); i > 0; i--)
		{
			this->theOperations.insertAt(0, this->returnList.takeFirst());
		}
		//printOperations();
		// Har kontrollerat listan f�r byte
		cout << "----- ROUND " << appdates + 1 << " -----" << endl;
		printOperations();
	}
	delete[] counterDayOrder;
}

void OperationHandler::printOperations()
{
	for (int i = 0; i < this->rooms; i++)
	{
		for (int j = 0; j < this->nrOffPosibleOperations; j++)
		{
			// Skriver ut operationernas ID i den ordning de blivit placerade.
			cout << this->operationRooms[i][j].getID() << " ";
		}
		cout << endl;
	}

	// Skriver ut tiden som �r kvar f�r varje rum.
	cout << endl;
	for (int i = 0; i < this->rooms; i++)
		cout << "Room " << i << ": " << timeLeft[i] << endl;
}

void OperationHandler::swap(Operation &one, Operation &two)
{
	Operation temp = one;
	one = two;
	two = temp;
}
