#include <iostream>
#include <string>

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

	bool Find(Nodo** ptr, int v)
	{
		ptr = &root;
		while (*ptr && (*ptr)->valor != v)
		{
			if ((*ptr)->valor < v)
			{
				ptr = &((*ptr)->izq);
			}
			else
			{
				ptr = &((*ptr)->izq);
			}
		}
		return *ptr != nullptr;
	}

	bool Insert(int val)
	{

	}

	bool Remove(int val)
	{

	}

private:
	Nodo* root;
};

int main()
{

}