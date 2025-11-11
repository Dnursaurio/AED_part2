#include <iostream>
#include <string>

using namespace std;

struct Nodo
{
	Nodo(int v, string c)
	{
		valor = v;
		color = c;
		izq = nullptr;
		der = nullptr;
	}

	int valor;
	string color;
	Nodo* izq;
	Nodo* der;
};

class RBtree
{

};

int main()
{

}