#include <iostream>
#include <string>
#include <stack>

using namespace std;

struct Nodo
{
	Nodo(int v)
	{
		valor = v;
		color = true; // color "rojo"
		padre = nullptr;
		izq = nullptr;
		der = nullptr;
	}

	int valor;
	bool color;
	Nodo* padre;
	Nodo* izq;
	Nodo* der;
};

class RBtree
{
public:
	RBtree()
	{
		root = nullptr;
	}

	bool Find(Nodo**& ptr, int v)
	{
		while (!s.empty())
		{
			s.pop();
		}

		ptr = &root;
		while (*ptr && (*ptr)->valor != v)
		{
			s.push(*ptr);
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

	Nodo* Tio(Nodo* papa, Nodo**ptr)
	{
		Nodo* tio = nullptr;
		if (!papa)
		{
			return;
		}
		else
		{
			if (papa->izq == (*ptr))
			{
				tio = papa->der;
			}
			else
			{
				tio = papa->izq;
			}
		}
		return tio;
	}

	bool Insert(int val)
	{
		Nodo** ptr;
		if (Find(ptr, val))
		{
			return 0;
		}
		else
		{
			*ptr = new Nodo(val);
			s.pop();
			(*ptr)->padre = s.empty() ? nullptr : s.top();
			Nodo* papa = (*ptr)->padre;

			if (*ptr == root)
			{
				(*ptr)->color = false;
			}
			if ((*ptr)->color == true)
			{
				if ((*ptr)->izq && (*ptr)->izq->color == true)
				{
					Nodo* tio = Tio(papa, ptr);
					if (tio->color == true)
					{
						papa->color = true;
						tio->color = false;
						(*ptr)->color = false;
					}
					if (tio->color == false)
					{

					}
				}
			}

			return 1;
		}
	}

	Nodo** Reemplazo(Nodo** q)
	{
		Nodo** ptr = q;
		if (rand() % 2 == 0)
		{
			q = &(*q)->izq;
			while ((*q)->der)
			{
				q = &((*q)->der);
			}
		}
		else
		{
			q = &(*q)->der;
			while ((*q)->izq)
			{
				q = &((*q)->izq);
			}
		}
		return q;
	}

	bool Remove(int val)
	{
		Nodo** ptr;
		if (!Find(ptr, val))
		{
			return 0;
		}
		else
		{
			if ((*ptr)->izq && (*ptr)->der)
			{
				Nodo** q = Reemplazo(ptr);
				(*ptr)->valor = (*q)->valor;
				ptr = q;
			}
			Nodo* temp = *ptr;
			if ((*ptr)->izq)
			{
				*ptr = temp->izq;
			}
			else
			{
				*ptr = temp->der;
			}
			delete temp;
			return 1;
		}
	}

private:
	Nodo* root;
	stack<Nodo*>s;
};

int main()
{

}