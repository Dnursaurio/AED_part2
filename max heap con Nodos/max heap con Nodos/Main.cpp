#include <iostream>
#include <queue>

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

class MaxHeap
{
public:

	MaxHeap()
	{
		raiz = nullptr;
	}

	bool Insert(int v)
	{
		if (!raiz)
		{
			raiz = new Nodo(v);
			return 1;
		}
		else
		{
			Nodo* padre;
			bool dir;
			Encontrar_Insert(padre, dir);
			padre->caminos[dir] = new Nodo(v);
			elevar(padre->caminos[dir]);
			return 1;
		}
	}

	//recuerda esto remuve la raiz
	bool Remove()
	{
		if(!raiz)
		{
			return 0;
		}
		if (!raiz->caminos[0] && !raiz->caminos[1])
		{
			delete raiz;
			raiz = nullptr;
			return 1;
		}
		//necesito hallar el ultimo nodo (el menor)
		Nodo* ultimo = nullptr;
		//usaremos a su padre para luego hundirlo
		Nodo* padre_ultimo = nullptr;

		queue < Nodo*>q;
		q.push(raiz);

		while (!q.empty())
		{
			Nodo* actual = q.front();
			q.pop();

			if (actual->caminos[0])
			{
				padre_ultimo = actual;
				q.push(actual->caminos[0]);
			}
			if (actual->caminos[1])
			{
				padre_ultimo = actual;
				q.push(actual->caminos[1]);
			}
			ultimo = actual;
		}

		if (!ultimo || !padre_ultimo)
		{
			return 0;
		}

		//cambiar la raiz con el ultimo nodo
		swap(raiz->valor, ultimo->valor);

		if (padre_ultimo && padre_ultimo->caminos[0] == ultimo) 
		{
			padre_ultimo->caminos[0] = nullptr;
		}
		else
		{
			padre_ultimo->caminos[1] = nullptr;
		}

		delete ultimo;

		hundir(raiz);

		return 1;
	}

	void PreOrder(Nodo* n)
	{
		if (!n)
		{
			return;
		}
		else
		{
			cout << n->valor << " ";
			PreOrder(n->caminos[0]);
			PreOrder(n->caminos[1]);
		}
	}

	void print()
	{
		Nodo* n = raiz;
		PreOrder(n);
		cout<<endl;
	}

private:
	Nodo* raiz;

	void Encontrar_Insert(Nodo*& padre, bool& dir)
	{
		queue<Nodo*>q;
		q.push(raiz);
		while (!q.empty())
		{
			Nodo* actual = q.front();
			q.pop();

			if (!actual->caminos[0])
			{
				padre = actual;
				dir = 0;
				return;
			}

			if (!actual->caminos[1])
			{
				padre = actual;
				dir = 1;
				return;
			}

			q.push(actual->caminos[0]);
			q.push(actual->caminos[1]);
		}
	}

	void elevar(Nodo* nodo)
	{
		if (!nodo || nodo == raiz)
		{
			return;
		}
		else
		{
			while (Nodo* padre = Obtener_padre(raiz, nodo))
			{
				if (padre->valor < nodo->valor)
				{
					swap(padre->valor, nodo->valor);
				}
				else
				{
					break;
				}
				nodo = padre;
			}
		}
	}

	Nodo* Obtener_padre(Nodo* ini, Nodo* hijo)
	{
		queue<Nodo*>q;
		q.push(ini);
		while (!q.empty())
		{
			Nodo* actual = q.front();
			q.pop();
			if (actual->caminos[0] == hijo || actual->caminos[1] == hijo)
			{
				return actual;
			}
			if (actual->caminos[0])
			{
				q.push(actual->caminos[0]);
			}
			if (actual->caminos[1])
			{
				q.push(actual->caminos[1]);
			}
		}
		return nullptr;
	}

	void hundir(Nodo* n)
	{
		while (true)
		{
			Nodo* mayor = n;

			if (n->caminos[0] && n->caminos[0]->valor > mayor->valor)
			{
				mayor = n->caminos[0];
			}
			if (n->caminos[1] && n->caminos[1]->valor > mayor->valor)
			{
				mayor = n->caminos[1];
			}
			if (mayor == n)
			{
				break;
			}
			swap(n->valor, mayor->valor);
			//hay que seguir hundiendo n hasta que no se pueda mas
			n = mayor;
		}
	}
};

int main()
{
	MaxHeap mh;
	int arr[16] = { 2,4,7,5,19,10,21,14,11,13,12,12,10,1,6,18 };
	for (int i = 0; i < 16; i++)
	{
		mh.Insert(arr[i]);
	}
	mh.print();
	mh.Remove();
	mh.print();
	mh.Remove();
	mh.print();

	return 0;
}