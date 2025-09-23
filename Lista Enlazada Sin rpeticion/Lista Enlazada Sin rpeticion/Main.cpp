#include <iostream>

using namespace std;

struct Node
{
	Node(int v)
	{
		valor = v;
		next = nullptr;
	}
	Node* next;
	int valor;
};

class ListaOrdenada
{
public:
	ListaOrdenada()
	{
		head = nullptr;
	}
	~ListaOrdenada()
	{
		return;
	}
	bool Find(int v, Node**& buscador)
	{
		//esto determina la posicion de v
		for (buscador = &head; *buscador && (*buscador)->valor < v; buscador = &((*buscador)->next));
		return *buscador && (*buscador)->valor == v;
	}
	bool Insertar(int v)
	{
		Node** ptr;
		if (Find(v,ptr))
		{
			return 0;
		}
		else
		{
			Node* n = new Node(v);
			n->next = *ptr;
			*ptr = n;
			return 1;
		}
	}
	bool Remover(int v)
	{
		Node** ptr;
		if (!Find(v, ptr))
		{
			return 0;
		}
		else
		{
			Node* temp = *ptr;
			*ptr = (*ptr)->next;
			delete temp;
			return 1;
		}
	}
	void Print()
	{
		for (Node* ptr = head; ptr; ptr = ptr->next)
		{
			cout << ptr->valor << " -> ";
		}
		cout << "NULL";
		cout << endl;
	}
private:
	Node* head;
};

int main()
{
	ListaOrdenada l;
	cout << "----------------------------Lista Ordenada---------------------------" << endl;
	cout << "Agregando elementos con Insertar" << endl;
	l.Insertar(1);	l.Print();
	l.Insertar(4);	l.Print();
	l.Insertar(9);	l.Print();
	l.Insertar(2);	l.Print();
	l.Insertar(0);	l.Print();
	cout << "Eliminando elementos con Remove" << endl;
	l.Remover(9);	l.Print();
	cout << "---------------------------------------------------------------------" << endl;

	return 0;
}
