#include <iostream>

using namespace std;

struct Node
{
	Node(int v)
	{
		valor = v;
		next = nullptr;
	}
	Node* next;
	int valor;
};

class ListaMerge
{
public:
	ListaMerge()
	{
		head = nullptr;
	}
	bool Find(int v, Node** ptr);
	bool Insert(int v);
	void Merge(Node* A, Node* B);
	void print();
private:
	Node* head;
};

int main()
{

}