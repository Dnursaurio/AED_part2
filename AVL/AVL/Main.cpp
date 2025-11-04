#include <iostream>
#include <stack>
#include <stdlib.h>

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
		return *ptr != NULL;
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

	int diferencia_de_alturas(Nodo* n)
	{
		if (!n)
		{
			return 0;
		}
		return Alturas(n->izq) - Alturas(n->der);
	}

	void RR(Nodo* par,Nodo* padre_par)
	{
		Nodo* A = par;
		Nodo* B = par->der;
		Nodo* temp = B->izq;

		A->der = temp;
		B->izq = A;

		Nodo* tmp = B;
		if (padre_par)
		{
			if (padre_par->izq == par)
			{
				padre_par->izq = tmp;
				return;
			}
			else
			{
				padre_par->der = tmp;
				return;
			}
		}
		else
		{
			raiz = tmp;
			return;
		}
	}

	void RL(Nodo* par, Nodo* padre_par)
	{
		Nodo* A = par;
		Nodo* C = A->der;
		Nodo* B = C->izq;
		Nodo* temp1 = B->izq;
		Nodo* temp2 = B->der;

		A->der = temp1;
		C->izq = temp2;
		B->izq = A;
		B->der = C;
		Nodo* tmp = B;
		if (padre_par)
		{
			if (padre_par->izq == par)
			{
				padre_par->izq = tmp;
				return;
			}
			else
			{
				padre_par->der = tmp;
				return;
			}
		}
		else
		{
			raiz = tmp;
			return;
		}
	}

	void LL(Nodo* par, Nodo* padre_par)
	{
		Nodo* C = par;
		Nodo* B = C->izq;
		Nodo* temp = B->der;
		C->izq = temp;
		B->der = C;
		Nodo* tmp = B;
		if (padre_par)
		{
			if (padre_par->izq == par)
			{
				padre_par->izq = tmp;
				return;
			}
			else
			{
				padre_par->der = tmp;
				return;
			}
		}
		else
		{
			raiz = tmp;
			return;
		}
	}

	void LR(Nodo* par, Nodo* padre_par)
	{
		Nodo* C = par;
		Nodo* A = C->izq;
		Nodo* B = A->der;
		Nodo* temp1 = B->izq;
		Nodo* temp2 = B->der;

		A->der = temp1;
		C->izq = temp2;
		B->izq = A;
		B->der = C;
		Nodo* tmp = B;
		if (padre_par)
		{
			if (padre_par->izq == par)
			{
				padre_par->izq = tmp;
				return;
			}
			else
			{
				padre_par->der = tmp;
				return;
			}
		}
		else
		{
			raiz = tmp;
			return;
		}
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
			//aqui hacemos la subida y el balanceo
			while (!s.empty())
			{
				Nodo* par = s.top();
				s.pop();
				Nodo* padre_par = nullptr;
				if (!s.empty())
				{
					padre_par = s.top();
				}
				int dif = diferencia_de_alturas(par);
				if (dif < -1)
				{
					//aca entran los casos de RR y RL
					if (diferencia_de_alturas(par->der) <= 0)
					{
						RR(par, padre_par);
					}
					if (diferencia_de_alturas(par->der) > 0)
					{
						RL(par, padre_par);
					}
				}
				if (dif > 1)
				{
					if (diferencia_de_alturas(par->izq) >= 0)
					{
						LL(par, padre_par);
					}
					if (diferencia_de_alturas(par->izq) < 0)
					{
						LR(par, padre_par);
					}
				}
			}
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
			s.pop();
			Nodo* par = nullptr;
			Nodo* padre_par = nullptr;
			if (!s.empty())
			{
				par = s.top();
				s.pop();
				padre_par = s.top();
			}
			
			return 1;
		}
	}

	void InOrder(Nodo* n)
	{
		if (!n)
		{
			return;
		}
		else
		{
			InOrder(n->izq);
			cout << n->valor << " ";
			InOrder(n->der);
		}
	}

	void PrintInOrder()
	{
		InOrder(raiz);
		cout << endl;
	}

private:
	Nodo* raiz;
	stack<Nodo*>s;
};

int main()
{
	AVL avl;
	avl.Insert(10);
	avl.Insert(4);
	avl.Insert(8);
	avl.Insert(0);
	avl.Insert(1);
	avl.Insert(30);
	avl.Insert(15);
	avl.PrintInOrder();
}