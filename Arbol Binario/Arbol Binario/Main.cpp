#include <iostream>

using namespace std;

struct Node
{
	Node(int v)
	{
		valor = v;
		izq = nullptr;
		der = nullptr;
	}
	int valor;
	Node* izq;
	Node* der;
};

class ArbBin
{
public:

	ArbBin()
	{
		raiz = nullptr;
	}

	bool Find(int v, Node**& ptr)
	{
		ptr = &raiz;
		while (*ptr && (*ptr)->valor != v)
		{
			if ((*ptr)->valor > v)
			{
				ptr = &((*ptr)->izq);
			}
			else
			{
				ptr = &((*ptr)->der);
			}
		}
		return *ptr != nullptr;
	}
	bool Insert(int v)
	{
		Node** ptr;
		if (Find(v, ptr))
		{
			return 0;
		}
		else
		{
			*ptr = new Node(v);
			return 1;
		}
	}

	Node** remplazo(Node** ptr)
	{
		for (ptr = &((*ptr)->der); *ptr && (*ptr)->izq; ptr = &((*ptr)->izq));
		return ptr;
	}

	bool Remove(int v)
	{
		/*hay 3 casos
			- no tiene hijos
			- tiene un solo hijo
			- tiene ambos hijos
		*/
		Node** ptr;
		if (!Find(v, ptr))
		{
			return 0;
		}
		if ((*ptr)->der && (*ptr)->izq)
		{
			Node** q = remplazo(ptr);
			(*ptr)->valor = (*q)->valor;
			ptr = q;
		}
		Node* temp = *ptr;
		if ((*ptr)->der)
		{
			*ptr = temp->der;
		}
		else
		{
			*ptr = temp->izq;
		}
		delete temp;
		return 1;
	}

	void InOrder(Node* n)
	{
		if (!n)
		{
			return;
		}
		InOrder(n->izq);
		cout << n->valor << " ";
		InOrder(n->der);
	}

	void printInOrder()
	{
		Node* n = raiz;
		InOrder(n);
		cout << endl;
	}

private:
	Node* raiz;
};

int main()
{
	ArbBin bin;
	cout << "------------------------------Arbol Binario------------------------------" << endl;
	cout << "Agregando elementos con Insert" << endl;
	bin.Insert(2);	bin.printInOrder();
	bin.Insert(1);	bin.printInOrder();
	bin.Insert(3);	bin.printInOrder();
	bin.Insert(0);	bin.printInOrder();
	cout << "Eliminando elementos con Remove" << endl;
	cout << "caso 1 (tiene un solo hijo)" << endl;
	bin.Remove(1);	bin.printInOrder();
	cout << "caso 2 (tiene dos hijos)" << endl;
	bin.Remove(2);	bin.printInOrder();
	cout << "caso 0 (no tiene hijos)" << endl;
	bin.Remove(3);	bin.printInOrder();
	cout << "-------------------------------------------------------------------------" << endl;

	return 0;
}