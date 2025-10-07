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
	InOrder(n->izq);
	cout << n->valor << " ";
	InOrder(n->der);
}

Nodo* CrearArbol(int* ini, int* fin)
{
	Nodo* inicio_cola;
	Nodo* fin_cola;
	Nodo* raiz;
	vector<Nodo*> c;
	for (ini; ini < fin; ini++)
	{
		Nodo* n = new Nodo(*ini);
		c.push_back(n);
	}
	inicio_cola = c.front();
	fin_cola = c.back();
	while (c.size() != 1)
	{
		int nuevo_valor = c[0]->valor + c[1]->valor;
		Nodo* nuevo = new Nodo(nuevo_valor);
		nuevo->izq = c.front();
		c.erase(c.begin());
		inicio_cola = c.front();
		nuevo->der = c.front();
		c.erase(c.begin());
		inicio_cola = c.front();
		c.push_back(nuevo);
		fin_cola = c.back();
		
	}
	if (c.size() == 1)
	{
		raiz = c.front();
		InOrder(raiz);
		return raiz;
	}
}

int main()
{
	int arr[16] = { 2,4,7,9,10,15,3,25,38,74,1,5,10,13,11,35 };
	int* ini = arr;
	int* fin = arr + 16;
	CrearArbol(ini, fin);

	return 0;
}