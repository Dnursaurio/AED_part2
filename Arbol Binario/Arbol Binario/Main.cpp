#include <iostream>

using namespace std;

struct Node
{
	Node(int v)
	{
		valor = v;
		direcciones[0] = nullptr;
		direcciones[1] = nullptr;
	}
	int valor;
	Node* direcciones[2];
};

class ArbBin
{
public:
	bool Find(int v, Node**& ptr)
	{
		for (ptr = &raiz; *ptr && (*ptr)->valor != v; ptr = &((*ptr)->direcciones[(*ptr)->valor < v]));
		return *ptr && (*ptr)->valor == v;
	}
	bool Insert(int v)
	{
		Node** ptr;
		if (Find(v, ptr))
		{
			return 0;
		}
		else
		{
			Node* n = new Node(v);
			*ptr = n;
			return 1;
		}
	}
	bool Remove(int v);
private:
	Node* raiz;
};

int main()
{
	ArbBin bin;
	bin.Insert(2);

	return 0;
}