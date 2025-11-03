#include <iostream>
#include <stack>
#include <stdlib.h>
#include <utility>

using namespace std;

struct Nodo
{
	Nodo(int v)
	{
		valor = v;
		izq = nullptr;
		der = nullptr;
	}

	int valor;
	Nodo* izq;
	Nodo* der;
};

class AVL
{
public:
	AVL()
	{
		raiz = nullptr;
	}

	bool Find(Nodo**& ptr, int v)
	{
		while (!s.empty())
		{
			s.pop();
		}
		ptr = &raiz;
		while (*ptr && (*ptr)->valor != v)
		{
			//guardamos la ruta de la bajada e iniciamo la difencia de alturas en 0
			s.push(make_pair(*ptr,0));
			if ((*ptr)->valor > v)
			{
				ptr = &((*ptr)->izq);
			}
			else
			{
				ptr = &((*ptr)->der);
			}
		}
		return *ptr != NULL;
	}

	bool Insert(int v)
	{
		Nodo** ptr;
		if (Find(ptr, v))
		{
			return 0;
		}
		else
		{
			*ptr = new Nodo(v);
			return 1;
		}
	}

	Nodo** reemplazo(Nodo** ptr)
	{
		Nodo** q = ptr;
		if (rand() % 2 == 1)
		{
			for (ptr = &((*ptr)->der); *ptr && (*ptr)->izq; ptr = &((*ptr)->izq));
		}
		else
		{
			for (ptr = &((*ptr)->izq); *ptr && (*ptr)->der; ptr = &((*ptr)->der));
		}
		return ptr;
	}

	bool Remove(int v)
	{
		Nodo** ptr;
		if (!Find(ptr, v))
		{
			return 0;
		}
		else
		{
			if ((*ptr)->izq && (*ptr)->der)
			{
				Nodo** q = reemplazo(ptr);
				//en este omento q eesta en la pocicion de ptr
				(*ptr)->valor = (*q)->valor;
				ptr = q;
			}
			Nodo* temp = *ptr;
			if (temp->der)
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
	}

	int Alturas(Nodo*n)
	{
		if (!n)
		{
			return 0;
		}
		int izq = Alturas(n->izq);
		int der = Alturas(n->der);
		return max(izq, der) + 1;
	}

private:
	Nodo* raiz;
	stack<pair<Nodo*,int>>s;
};

int main()
{

}