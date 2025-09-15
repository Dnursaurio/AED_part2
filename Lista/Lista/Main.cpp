#include <iostream>

using namespace std;

struct Node
{
	Node(int valor)
	{
		v = valor;
		next = nullptr;
		prev = nullptr;
	}
	Node* next;
	Node* prev;
	int v;
};

class CList
{
public:
	CList()
	{
		head = nullptr;
		nro_elem = 0;
	}
	void push_front(int x)
	{
		Node* n = new Node(x);
		n->next = head;
		head == nullptr ? n->prev = nullptr : head->prev = n;
		head = n;
		nro_elem++;
	}
	void push_back(int x);
	void pop_front();
	void pop_back();
	int operator[](int i);
	void print();
private:
	Node* head;
	int nro_elem;
};

int main()
{
	cout << "-----------------------------Lista-----------------------------" << endl;
	CList l;
	l.push_front(3);
	l.push_front(4);
	l.push_front(5);
	cout << "---------------------------------------------------------------" << endl;

	return 0;
}