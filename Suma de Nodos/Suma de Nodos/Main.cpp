#include <iostream>
#include <vector>

using namespace std;

struct Nodo
{
	Nodo(int v)
	{
		valor = v;
		der = nullptr;
		izq = nullptr;
	}

	int valor;
	Nodo* der;
	Nodo* izq;
};

void InOrder(Nodo* n)
{
	if (!n)
	{
		return;
	}
	InOrder(n->izq);
	cout << n->valor << " ";
	InOrder(n->der);
}

Nodo* CrearArbol(int* ini, int* fin)
{
	vector<Nodo*> c;
	for (int* p = ini; p < fin; p++)
	{
		Nodo* n = new Nodo(*p);
		c.push_back(n);
	}
	while (c.size() > 1)
	{
		int nuevo_valor = c[0]->valor + c[1]->valor;
		Nodo* nuevo = new Nodo(nuevo_valor);
		nuevo->izq = c[0];
		nuevo->der = c[1];
		c.erase(c.begin());
		c.erase(c.begin());
		c.push_back(nuevo);
	}

	Nodo* raiz = c.front();
	InOrder(raiz);
	return raiz;
}

int main()
{
	int arr[16] = { 2,4,7,9,10,15,3,25,38,74,1,5,10,13,11,35 };
	int* ini = arr;
	int* fin = arr + 16;
	CrearArbol(ini, fin);

	return 0;
}