#include <iostream>
#include <stack>
#include <queue>
#include <utility>

using namespace std;

struct Node
{
	Node(int v)
	{
		valor = v;
		izq = nullptr;
		der = nullptr;
	}
	int valor;
	Node* izq;
	Node* der;
};

class ArbBin
{
public:

	ArbBin()
	{
		raiz = nullptr;
	}

	bool Find(int v, Node**& ptr)
	{
		ptr = &raiz;
		while (*ptr && (*ptr)->valor != v)
		{
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
	bool Insert(int v)
	{
		Node** ptr;
		if (Find(v, ptr))
		{
			return 0;
		}
		else
		{
			*ptr = new Node(v);
			return 1;
		}
	}

	Node** remplazo(Node** ptr)
	{
		Node** q = ptr;
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
		/*hay 3 casos
			- no tiene hijos
			- tiene un solo hijo
			- tiene ambos hijos
		*/
		Node** ptr;
		if (!Find(v, ptr))
		{
			return 0;
		}
		if ((*ptr)->der && (*ptr)->izq)
		{
			Node** q = remplazo(ptr);
			(*ptr)->valor = (*q)->valor;
			ptr = q;
		}
		Node* temp = *ptr;
		if ((*ptr)->der)
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

	void InOrder(Node* n)
	{
		if (!n)
		{
			return;
		}
		InOrder(n->izq);
		cout << n->valor << " ";
		InOrder(n->der);
	}

	void Altura(Node* n, int altura, int& altura_max)
	{
		if (!n)
		{
			return;
		}
		if (altura > altura_max)
		{
			altura_max = altura;
		}
		Altura(n->izq, altura + 1, altura_max);
		Altura(n->der, altura + 1, altura_max);
	}

	int printAltura(Node* n)
	{
		int altura_max = 0;
		Altura(raiz, 1, altura_max);
		return altura_max;
	}

	int altura2(Node* n)
	{
		if (!n)
		{
			return 0;
		}
		int izq = altura2(n->izq);
		int der = altura2(n->der);
		return max(izq, der) + 1;
	}

	void printInOrder()
	{
		Node* n = raiz;
		InOrder(n);
		cout << "altura: " << printAltura(n) << " ";
		cout << "altura2: " << altura2(n);
		cout << endl;
	}

	void InOrderStack(Node* n)
	{
		stack<pair<Node*, int>> s;
		s.push(make_pair(n, 0));
		while (!s.empty())
		{
			switch (s.top().second)
			{
				case 0:
					if (n->izq)
					{	
						s.push(make_pair(n->izq, 0));
					}
					else
					{
						n = s.top().first;
						s.top().second += 1;
						break;
					}
					s.top().second += 1;
					n = s.top().first;
					break;
				case 1:
					cout << n->valor << " ";
					s.top().second += 1;
					break;
				case 2:
					s.top().second += 1;
					if (n->der)
					{
						s.push(make_pair(n->der, 0));
						n = s.top().first;
					}
					break;
				case 3:
					s.pop();
					break;
			}
		}
	}

	void printInOrderStack()
	{
		InOrderStack(raiz);
		cout << "altura: " << printAltura(raiz);
		cout << endl;
	}

	void PrintLevel(Node* n)
	{
		if (!n)
		{
			return;
		}
		queue<Node*>s;
		s.push(n);
		while (!s.empty())
		{
			Node* x = s.front();
			cout << s.front()->valor << " ";
			if (x->izq)
			{
				s.push(x->izq);
			}
			if (x->der)
			{
				s.push(x->der);
			}
			s.pop();
		}
	}

	void ImprimirNivel()
	{
		PrintLevel(raiz);
		cout << endl;
	}

private:
	Node* raiz;
};

int main()
{
	ArbBin bin;
	cout << "------------------------------Arbol Binario------------------------------" << endl;
	cout << "Agregando elementos con Insert" << endl;
	bin.Insert(2);	bin.printInOrder();
	bin.Insert(1);	bin.printInOrder();
	bin.Insert(3);	bin.printInOrder();
	bin.Insert(0);	bin.printInOrder();
	cout << "Eliminando elementos con Remove" << endl;
	cout << "caso 1 (tiene un solo hijo)" << endl;
	bin.Remove(1);	bin.printInOrder();
	cout << "caso 2 (tiene dos hijos)" << endl;
	bin.Remove(2);	bin.printInOrder();
	cout << "caso 0 (no tiene hijos)" << endl;
	bin.Remove(3);	bin.printInOrder();
	cout << "Agregando elementos con InOrderStack" << endl;
	bin.Insert(8);	bin.printInOrderStack();
	bin.Insert(-1);	bin.printInOrderStack();
	bin.Insert(16);	bin.printInOrderStack();
	bin.Insert(19);	bin.printInOrderStack();
	bin.Insert(32);	bin.printInOrderStack();
	bin.Insert(7);	bin.printInOrderStack();
	bin.Insert(6);	bin.printInOrderStack();
	bin.Insert(-3);	bin.printInOrderStack();
	bin.Insert(-2);	bin.printInOrderStack();
	cout << "Utilizando impresion por niveles" << endl;
	bin.ImprimirNivel();
	cout << "-------------------------------------------------------------------------" << endl;

	return 0;
}