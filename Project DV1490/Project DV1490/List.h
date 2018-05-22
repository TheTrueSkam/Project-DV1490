#pragma once

template<typename T>
class List
{
private:
	class Node
	{
	public:
		T element;
		Node* next;
		Node(T element, Node* next)
		{
			this->element = element;
			this->next = next;
		}
		~Node() { }
	};
	Node* first;
	Node* last;
	int nrOfNode;

public:
	List();
	virtual ~List();
	List(const List& other);
	List& operator=(const List& other);
	void insertAt(int pos, const T& element) throw(...);
	T getAt(int pos) const throw(...);
	void removeAt(int pos) throw(...);
	bool removeElement(const T& element);
	bool findElement(const T& toFind) const;
	int length() const;
	void getAll(T arr[], int cap) throw(...);
	void insertAtLast(const T& element);
	T takeFirst() throw(...);
};

template<typename T>
List<T>::List()
{
	this->nrOfNode = 0;
	this->first = nullptr;
	this->last = nullptr;
}

template<typename T>
List<T>::~List()
{
	//Om det finns Nodes i listan
	if (this->nrOfNode > 0)
	{
		//Skapa en pekare som kan vandra i listan
		Node* walker = nullptr;
		//Lopa lika många gånger som det finns nodes i listan
		for (int i = this->nrOfNode; i > 0; i--)
		{
			//Walker vandrar till sista objektet
			walker = this->first;
			for (int j = 0; j < this->nrOfNode - 1; j++)
			{
				walker = walker->next;
			}
			//Deletar sista objektet och sen minskar ner antalet nodes med 1
			delete walker;
			this->nrOfNode--;
		}
	}
}

template<typename T>
List<T>::List(const List & other)
{
	this->first = nullptr;
	this->last = nullptr;
	this->nrOfNode = other.nrOfNode;

	Node* oldWalker = other.first;
	Node* newWalker = this->first;

	for (int i = 0; i < this->nrOfNode; i++)
	{
		Node* newNode = new Node(oldWalker->element, nullptr);
		if (i == 0)
		{
			this->first = newNode;
			newWalker = this->first;
		}
		else
		{
			newWalker->next = newNode;
			newWalker = newWalker->next;
		}
		this->last = newWalker;
		oldWalker = oldWalker->next;
	}
}

template<typename T>
List<T> & List<T>::operator=(const List & other)
{
	//Om det inte är samma lista
	if (this != &other)
	{
		//Kontrolera om listan redan har nodes i sig och i så fall deleta nodesen (kolla destruktorn)
		if (this->nrOfNode > 0)
		{
			Node* walker = nullptr;
			for (int i = this->nrOfNode; i > 0; i--)
			{
				walker = this->first;
				for (int j = 0; j < this->nrOfNode - 1; j++)
				{
					walker = walker->next;
				}
				delete walker;
				this->nrOfNode--;
			}
		}
		//Gör first pekaren till nullpointer och sätt antal nodes till lika som den man vill ta värden ifrån
		this->first = nullptr;
		this->last = nullptr;
		this->nrOfNode = other.nrOfNode;

		Node* oldWalker;
		Node* newWalker;
		oldWalker = other.first;
		newWalker = this->first;
		for (int i = 0; i < this->nrOfNode; i++)
		{
			Node* newNode = new Node(oldWalker->element, nullptr);
			if (i == 0)
			{
				this->first = newNode;
				newWalker = this->first;
			}
			else
			{
				newWalker->next = newNode;
				newWalker = newWalker->next;
			}
			this->last = newWalker;
			oldWalker = oldWalker->next;
		}
	}
	return *this;
}

template<typename T>
void List<T>::insertAt(int pos, const T & element) throw(...)
{
	//Kontrolera så man kan stoppa in den på platsen man valt
	if (this->nrOfNode < pos || pos < 0)
	{
		throw "Posistion don't work";
	}

	//Om platsen är 0 så skapa en node som pekar på det first pekade på och sen låt first peka på den nya noden
	if (pos == 0)
	{
		Node* newNode = new Node(element, this->first);
		this->first = newNode;
		if (this->nrOfNode == pos)
		{
			this->last = newNode;
		}
	}
	else if (pos == 1) //Om platsen man valt är 1 skapa en ny node med pekaren på det first-next pekar på, sen låt first next peka på den nya objektet
	{
		Node* newNode = new Node(element, this->first->next);
		this->first->next = newNode;
		if (this->nrOfNode == pos)
		{
			this->last = newNode;
		}
	}
	else
	{
		//Skapa en walker som börjar från den första noden
		Node* walker;
		walker = this->first;
		//Låt den gå så många steg som platsen - 1 
		for (int i = 0; i < pos - 1; i++)
		{
			walker = walker->next;
		}
		//Skapa en ny node som pekar på det walker-next pekar på och sen sätt walker-next till den nya noden
		Node* newNode = new Node(element, walker->next);
		walker->next = newNode;
		if (this->nrOfNode == pos)
		{
			this->last = newNode;
		}
	}
	//Öka antalet nodes med 1
	this->nrOfNode++;
}

template<typename T>
T List<T>::getAt(int pos) const throw(...)
{
	//Kolla om platsen finns
	if (this->nrOfNode - 1 < pos || pos < 0)
	{
		throw "Posistion don't work";
	}

	//Skapa en walker som börjar på första noden
	Node* walker;
	walker = this->first;
	//walkern går till platsen om platsen inte 1
	for (int i = 0; i < pos; i++)
	{
		walker = walker->next;
	}
	//Returna elementet som walker pekar på
	return walker->element;
}

template<typename T>
void List<T>::removeAt(int pos) throw(...)
{
	//Kolla om platsen finns eller om listan är tom
	if (this->nrOfNode < pos || pos < 0 || this->first == nullptr)
	{
		throw "Posistion don't exist";
	}
	//Skapa två pekare som kan vadra i listan och sätt den första walker till first och andra till nullptr
	Node* walker;
	Node* secWalker;
	walker = this->first;
	secWalker = nullptr;
	//Gå till posistionen med första walker och walker 2 ett steg efter
	for (int i = 0; i < pos; i++)
	{
		secWalker = walker;
		walker = walker->next;
	}
	//Om den andra walker är en nullptr så är det det första noden
	if (secWalker == nullptr)
	{
		//ändra first till andra noden sen delita första
		this->first = walker->next;
		if (walker == this->last)
		{
			this->last = secWalker;
		}
		delete walker;
	}
	else
	{
		//ändra noden innan den som ska förstöras till noden efter den som ska försöras sen delita noden
		secWalker->next = walker->next;
		if (walker == this->last)
		{
			this->last = secWalker;
		}
		delete walker;
	}
	//Minska antal nodes med 1
	this->nrOfNode--;
}

template<typename T>
bool List<T>::removeElement(const T & element)
{
	bool removed = false;
	//Kolla så inte listan är tom
	if (nrOfNode > 0)
	{
		//Skapa två walkers första pekar på det first pekan pekar på den andra nullptr
		Node* walker;
		Node* secWalker;
		walker = this->first;
		secWalker = nullptr;
		//Vandra walker tills den hittar elementet eller bli nullptr och andra walkern ett steg efter
		while (walker->next != nullptr && walker->element != element)
		{
			secWalker = walker;
			walker = walker->next;
		}
		//Om den hittar ett element
		if (walker->element == element)
		{
			//Om den andra walker är en nullptr så är det det första noden
			if (secWalker == nullptr)
			{
				//ändra first till andra noden sen delita första
				this->first = walker->next;
				if (walker == this->last)
				{
					this->last = secWalker;
				}
				delete walker;
			}
			else
			{
				//ändra noden innan den som ska förstöras till noden efter den som ska försöras sen delita noden
				secWalker->next = walker->next;
				if (walker == this->last)
				{
					this->last = secWalker;
				}
				delete walker;
			}
			//Minska antal nodes med 1 och sätt removed till true
			this->nrOfNode--;
			removed = true;
		}
	}
	return removed;
}

template<typename T>
bool List<T>::findElement(const T & toFind) const
{
	bool find = false;
	//Kolla så inte listan är tom
	if (nrOfNode > 0)
	{
		//Skapa en walker och sätt den på första noden
		Node* walker;
		walker = this->first;
		//Gå igenom alla nodes till den hittar elementet eller blir en nullptr
		while (walker->next != nullptr && walker->element != toFind)
		{
			walker = walker->next;
		}
		//Kolla om den har hittat elementet
		if (walker->element == toFind)
		{
			find = true;
		}
	}
	return find;
}

template<typename T>
int List<T>::length() const
{
	//Returna antalet nodes som finns
	return this->nrOfNode;
}

template<typename T>
void List<T>::getAll(T arr[], int cap) throw(...)
{
	//Kolla så capasiteten är tillräckligt stor
	if (this->nrOfNode > cap)
	{
		throw "Cap is not enuth";
	}
	//Kopiera alla nodes element in i arraien
	for (int i = 0; i < this->nrOfNode; i++)
	{
		arr[i] = this->getAt(i);
	}
}

template<typename T>
void List<T>::insertAtLast(const T & element)
{
	Node* newNode = new Node(element, nullptr);
	if (this->nrOfNode == 0)
	{
		this->first = newNode;
	}
	else
	{
		this->last->next = newNode;
	}
	this->last = newNode;
	this->nrOfNode++;
}

template<typename T>
T List<T>::takeFirst()
{
	if (this->nrOfNode <= 0)
	{
		throw "List is empty!";
	}

	T temp = this->first->element;
	Node *walker = this->first;

	this->first = walker->next;
	if (walker == this->last)
	{
		this->last = nullptr;
	}
	delete walker;
	this->nrOfNode--;

	return temp;
}
