#include <iostream>
#include <stack>

using namespace std;

struct Nodo
{
	Nodo(int v)
	{
		valor = v;
		caminos[0] = nullptr;
		caminos[1] = nullptr;
	}
	int valor;
	Nodo* caminos[2];
};

class AVL
{
public:

	AVL()
	{
		raiz = nullptr;
	}

	bool Insert(int v)
	{
		Nodo** ptr;
		if (Find(v, ptr))
		{
			return 0;
		}
		else
		{
			*ptr = new Nodo(v);
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
				if (dif > 1)
				{
					if (diferencia_de_alturas(par->caminos[1]) >= 0)
					{
						RR(par, padre_par);
					}
					if (diferencia_de_alturas(par->caminos[1]) < 0)
					{
						RL(par, padre_par);
					}
				}
				if (dif < -1)
				{
					if (diferencia_de_alturas(par->caminos[0]) <= 0)
					{
						LL(par, padre_par);
					}
					if (diferencia_de_alturas(par->caminos[0]) > 0)
					{
						LR(par, padre_par);
					}
				}
			}
			return 1;
		}
	}

	bool Remove(int v)
	{
		Nodo** ptr;
		if (!Find(v, ptr))
		{
			return 0;
		}
		else
		{
			if ((*ptr)->caminos[0] && (*ptr)->caminos[1])
			{
				Nodo** q = reemplazo(ptr);
				(*ptr)->valor = (*q)->valor;
				ptr = q;
			}
			Nodo* temp = *ptr;
			if (temp->caminos[1])
			{
				*ptr = temp->caminos[1];
			}
			else
			{
				*ptr = temp->caminos[0];
			}
			delete temp;
			s.pop();
			Nodo* par = nullptr;
			Nodo* padre_par = nullptr;
			if (!s.empty())
			{
				par = s.top();
				padre_par = s.top();
				int dif = diferencia_de_alturas(par);
				if (dif > 1)
				{
					if (diferencia_de_alturas(par->caminos[1]) >= 0)
					{
						RR(par, padre_par);
					}
					if (diferencia_de_alturas(par->caminos[1]) < 0)
					{
						RL(par, padre_par);
					}
				}
				if (dif < -1)
				{
					if (diferencia_de_alturas(par->caminos[0]) <= 0)
					{
						LL(par, padre_par);
					}
					if (diferencia_de_alturas(par->caminos[0]) > 0)
					{
						LR(par, padre_par);
					}
				}
			}
			return 1;
		}
	}

	void print()
	{
		InOrder(raiz);
		cout << endl;
	}
private:
	Nodo* raiz;
	stack<Nodo*>s;

	bool Find(int v, Nodo**& ptr)
	{
		while (!s.empty())
		{
			s.pop();
		}

		for (ptr = &raiz; *ptr && (*ptr)->valor != v; ptr = &((*ptr)->caminos[(*ptr)->valor < v]))
		{
			s.push(*ptr);
		}
		return *ptr != nullptr;
	}

	Nodo** reemplazo(Nodo** ptr)
	{
		Nodo** q = ptr;
		if (rand() % 2 == 1)
		{
			for (ptr = &((*ptr)->caminos[1]); *ptr && (*ptr)->caminos[0]; ptr = &((*ptr)->caminos[0]));
		}
		else
		{
			for (ptr = &((*ptr)->caminos[0]); *ptr && (*ptr)->caminos[1]; ptr = &((*ptr)->caminos[1]));
		}
		return ptr;
	}

	int alturas(Nodo* n)
	{
		if (!n)
		{
			return 0;
		}
		int izq = alturas(n->caminos[0]);
		int der = alturas(n->caminos[1]);
		return max(izq, der) + 1;
	}

	int diferencia_de_alturas(Nodo* n)
	{
		if (!n)
		{
			return 0;
		}
		return alturas(n->caminos[1]) - alturas(n->caminos[0]);
	}

	void RR(Nodo* par, Nodo* padre_par)
	{
		Nodo* A = par;
		Nodo* B = A->caminos[1];
		A->caminos[1] = B->caminos[0];
		B->caminos[0] = A;
		Nodo* tmp = B;
		if (padre_par)
		{
			if (padre_par->caminos[0] == par)
			{
				padre_par->caminos[0] = tmp;
				return;
			}
			if (padre_par->caminos[1] == par)
			{
				padre_par->caminos[1] = tmp;
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
		Nodo* C = A->caminos[1];
		Nodo* B = C->caminos[0];
		A->caminos[1] = B->caminos[0];
		B->caminos[0] = A;
		C->caminos[0] = B->caminos[1];
		B->caminos[1] = C;
		Nodo* tmp = B;
		if (padre_par)
		{
			if (padre_par->caminos[0] == par)
			{
				padre_par->caminos[0] = tmp;
				return;
			}
			if (padre_par->caminos[1] == par)
			{
				padre_par->caminos[1] = tmp;
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
		Nodo* B = C->caminos[0];
		C->caminos[0] = B->caminos[1];
		B->caminos[1] = C;
		Nodo* tmp = B;
		if (padre_par)
		{
			if (padre_par->caminos[0] == par)
			{
				padre_par->caminos[0] = tmp;
				return;
			}
			if (padre_par->caminos[1] == par)
			{
				padre_par->caminos[1] = tmp;
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
		Nodo* A = C->caminos[0];
		Nodo* B = A->caminos[1];
		C->caminos[0] = B->caminos[1];
		A->caminos[1] = B->caminos[0];
		B->caminos[0] = A;
		B->caminos[1] = C;
		Nodo* tmp = B;
		if (padre_par)
		{
			if (padre_par->caminos[0] == par)
			{
				padre_par->caminos[0] = tmp;
				return;
			}
			if (padre_par->caminos[1] == par)
			{
				padre_par->caminos[1] = tmp;
				return;
			}
		}
		else
		{
			raiz = tmp;
			return;
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
			InOrder(n->caminos[0]);
			cout << n->valor << " ";
			InOrder(n->caminos[1]);
		}
	}
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
	avl.print();
	avl.Remove(1);
	avl.print();
	avl.Remove(10);
	avl.Remove(0);
	avl.Remove(4);
	avl.print();
}