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
		//Lopa lika m�nga g�nger som det finns nodes i listan
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
	//Om det inte �r samma lista
	if (this != &other)
	{
		//Kontrolera om listan redan har nodes i sig och i s� fall deleta nodesen (kolla destruktorn)
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
		//G�r first pekaren till nullpointer och s�tt antal nodes till lika som den man vill ta v�rden ifr�n
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
	//Kontrolera s� man kan stoppa in den p� platsen man valt
	if (this->nrOfNode < pos || pos < 0)
	{
		throw "Posistion don't work";
	}

	//Om platsen �r 0 s� skapa en node som pekar p� det first pekade p� och sen l�t first peka p� den nya noden
	if (pos == 0)
	{
		Node* newNode = new Node(element, this->first);
		this->first = newNode;
		if (this->nrOfNode == pos)
		{
			this->last = newNode;
		}
	}
	else if (pos == 1) //Om platsen man valt �r 1 skapa en ny node med pekaren p� det first-next pekar p�, sen l�t first next peka p� den nya objektet
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
		//Skapa en walker som b�rjar fr�n den f�rsta noden
		Node* walker;
		walker = this->first;
		//L�t den g� s� m�nga steg som platsen - 1 
		for (int i = 0; i < pos - 1; i++)
		{
			walker = walker->next;
		}
		//Skapa en ny node som pekar p� det walker-next pekar p� och sen s�tt walker-next till den nya noden
		Node* newNode = new Node(element, walker->next);
		walker->next = newNode;
		if (this->nrOfNode == pos)
		{
			this->last = newNode;
		}
	}
	//�ka antalet nodes med 1
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

	//Skapa en walker som b�rjar p� f�rsta noden
	Node* walker;
	walker = this->first;
	//walkern g�r till platsen om platsen inte 1
	for (int i = 0; i < pos; i++)
	{
		walker = walker->next;
	}
	//Returna elementet som walker pekar p�
	return walker->element;
}

template<typename T>
void List<T>::removeAt(int pos) throw(...)
{
	//Kolla om platsen finns eller om listan �r tom
	if (this->nrOfNode < pos || pos < 0 || this->first == nullptr)
	{
		throw "Posistion don't exist";
	}
	//Skapa tv� pekare som kan vadra i listan och s�tt den f�rsta walker till first och andra till nullptr
	Node* walker;
	Node* secWalker;
	walker = this->first;
	secWalker = nullptr;
	//G� till posistionen med f�rsta walker och walker 2 ett steg efter
	for (int i = 0; i < pos; i++)
	{
		secWalker = walker;
		walker = walker->next;
	}
	//Om den andra walker �r en nullptr s� �r det det f�rsta noden
	if (secWalker == nullptr)
	{
		//�ndra first till andra noden sen delita f�rsta
		this->first = walker->next;
		if (walker == this->last)
		{
			this->last = secWalker;
		}
		delete walker;
	}
	else
	{
		//�ndra noden innan den som ska f�rst�ras till noden efter den som ska f�rs�ras sen delita noden
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
	//Kolla s� inte listan �r tom
	if (nrOfNode > 0)
	{
		//Skapa tv� walkers f�rsta pekar p� det first pekan pekar p� den andra nullptr
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
			//Om den andra walker �r en nullptr s� �r det det f�rsta noden
			if (secWalker == nullptr)
			{
				//�ndra first till andra noden sen delita f�rsta
				this->first = walker->next;
				if (walker == this->last)
				{
					this->last = secWalker;
				}
				delete walker;
			}
			else
			{
				//�ndra noden innan den som ska f�rst�ras till noden efter den som ska f�rs�ras sen delita noden
				secWalker->next = walker->next;
				if (walker == this->last)
				{
					this->last = secWalker;
				}
				delete walker;
			}
			//Minska antal nodes med 1 och s�tt removed till true
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
	//Kolla s� inte listan �r tom
	if (nrOfNode > 0)
	{
		//Skapa en walker och s�tt den p� f�rsta noden
		Node* walker;
		walker = this->first;
		//G� igenom alla nodes till den hittar elementet eller blir en nullptr
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
	//Kolla s� capasiteten �r tillr�ckligt stor
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
